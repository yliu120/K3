#!/usr/bin/env python3
#
# Generate a schema for mosaic
import argparse
import subprocess
import re
import os

def do_schema(k3_file, out_file=None):
    sand_path = subprocess.check_output('find .cabal-sandbox -name "*packages.conf.d"',shell=True)
    sand_arg = '--mpargs package-db=' + sand_path.decode("utf-8")
    sand_arg = sand_arg[:-1] # remove newline
    args = ['./dist/build/k3/k3', '-I ./lib/k3', '-I ./examples/sql', 'compile',
        '-l ktrace',
        '--fstage none=True',
        sand_arg,
        '--mpsearch ./src',
        k3_file,
        '2>&1']
    args2 = " ".join(args)
    output = subprocess.check_output(args2, shell=True, stderr=subprocess.STDOUT)
    output = output.decode("utf-8")
    # search for 'drop table' as a start signal
    mo = re.search('(drop table.*)', output, flags=re.DOTALL)
    # from this point to the end
    if mo:
        schema = mo.group(1)
        if out_file:
            with open(out_file, 'w') as f:
                f.write(schema)
        else:
            print(schema)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("k3_file", type=str, help="Specify path of k3 file")
    args = parser.parse_args()
    do_schema(args.k3_file)

if __name__=='__main__':
  main ()
