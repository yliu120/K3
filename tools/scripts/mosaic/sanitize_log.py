#!/usr/bin/env python

from optparse import OptionParser
import re
import sys
from os.path import basename

import clean_log_hash

# focus on the region we care about in the log file
def reduce_region(lines):
  out = []
  take = False
  for line in lines:
    if not take:
      if re.match("^ *TRIGGER .*$", line):
        take = True
        out += [line]
    elif take:
      if re.match("^Mode:.*$", line) or re.match("^ *EVENT LOOP.*$", line):
        take = False
      else:
        out += [line]
  return out

def group_triggers(lines):
  out = []
  group = []
  for line in lines:
    if re.match("^ *TRIGGER .*$", line):
      if group != []:
        out += [group]
      group = [line]
    else:
      group += [line]
  if group != []:
    out += [group]
  return out

# Take a group of lines representing a trigger and convert them to proper output
def lines_of_trig(log_name, trig_num, trig):
  mobj =  re.match(r'^TRIGGER (.+) (.+) {', trig[0])
  if mobj:
    name, addr = mobj.group(1), mobj.group(2)
    if name and addr:
      pairs = []
      lastval = None
      lastkey = None
      for i, line in enumerate(trig):
        if i == 1:
          mobj = re.match(r'^(Args): (.*)$', trig[1])
        else:
          mobj = re.match(r'^(.*) => (.*)$', line)
        if mobj:
          if lastkey and lastval:
            pairs.append((lastkey, lastval))
          lastkey = mobj.group(1)
          lastval = mobj.group(2)
          # check for weird args var, and translate Args to args
          if i == 1 and lastkey == 'Args': lastkey = 'args'
          elif lastkey == 'args': lastkey = None
        else: # maybe a continued line?
          mobj = re.match(r'^.. (.*)$', line)
          if mobj:
            # grow our value
            if lastkey and lastval:
              lastval += mobj.group(1)
            else:
              raise ValueError("Continued line without first line: \n" + line)

      # last members if we missed them
      if lastkey and lastval:
        pairs.append((lastkey, lastval))

      # convert pairs to lines
      out = ['/'.join([log_name, str(trig_num), addr, name, pair[0], pair[1]]) for pair in pairs]
      return out

# clean a line by removing initial whitespace, \n, long whitespace
def clean(line):
  line = line.replace('\n','')
  line = re.sub(r'\s+', ' ', line)
  line = re.sub(r'^ ', '', line)
  return line

def main(options, filename):
  with open(filename, "r") as f:
    if f:
      lines = f.readlines()
      lines = [clean(l) for l in lines]
      lines = reduce_region(lines)
      trigs = group_triggers(lines)
      trigs = [lines_of_trig(options.log_name, i, t) for i, t in enumerate(trigs, start=1)]
      out = []
      for t in trigs:
        out += t
      out = '\n'.join(out)
      if options.unhash:
        out = clean_log_hash.unhash(out)
      print(out)
    else:
      print("File {filename} not found".format(**locals()))

if __name__ == '__main__':
  usage = "Usage: {0} [options] <log file>".format(basename(sys.argv[0]))
  parser = OptionParser(usage=usage)
  parser.add_option("-n", "--name", type="string", dest="log_name",
                    default="log", help="Specify desired name of log (for comparing different logs)")
  parser.add_option("-s", "--unhash", action='store_true', dest="unhash",
                    default=False, help="Clarify the log by removing timestamp hashes")
  (options, args) = parser.parse_args()
  if args:
    main(options, args[0])
  else:
    print usage

