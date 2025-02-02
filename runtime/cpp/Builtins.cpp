#include <functional>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <time.h>
#include <stdio.h>

#include "Common.hpp"
#include "Engine.hpp"
#include "BaseTypes.hpp"
#include "dataspace/Dataspace.hpp"
#include "BaseCollections.hpp"
#include "Builtins.hpp"

namespace K3 {
  using std::endl;
  using std::to_string;

  boost::mutex __standard_context::mutex_;

  // Standard context implementations
  __standard_context::__standard_context(Engine& __engine)
    : __k3_context(__engine)
  {
  	srand (time(NULL));
  }

  unit_t __tcmalloc_context::tcmallocStart(unit_t) {
    #ifdef K3_TCMALLOC
    HeapProfilerStart("K3");
      #ifdef K3_HEAP_SERIES
      auto init = []() {
        auto start = time_milli();
        auto start_str = to_string( ( start - (start % 250) ) % 100000 );
        return std::string("K3." + start_str + ".");
      };
      auto body = [](std::string& name, int i){
        std::string heapName = name + to_string(i);
        HeapProfilerDump(heapName.c_str());
      };
      heap_series_start(init, body);
      #endif
    #else
    std::cout << "tcmallocStart: K3_TCMALLOC is not defined. not starting." << std::endl;
    #endif
    return unit_t {};
  }

  unit_t __tcmalloc_context::tcmallocStop(unit_t) {
    #ifdef K3_TCMALLOC
      #ifdef K3_HEAP_SERIES
      heap_series_stop();
      #endif
    HeapProfilerDump("End of Program");
    HeapProfilerStop();
    #endif
    return unit_t {};
  }

  unit_t __jemalloc_context::jemallocStart(unit_t) {
    #ifdef K3_JEMALLOC
    bool enable = true;
    mallctl("prof.active", NULL, 0, &enable, sizeof(enable));
      #ifdef K3_HEAP_SERIES
      auto init = [](){
        const char* hp_prefix;
        size_t hp_sz = sizeof(hp_prefix);
        mallctl("opt.prof_prefix", &hp_prefix, &hp_sz, NULL, 0);
        auto start = time_milli();
        auto start_str = to_string( ( start - (start % 250) ) % 100000 );
        return std::string(hp_prefix) + "." + start_str + ".0.t";
      };
      auto body = [](std::string& name, int i){
        std::string heapName = name + to_string(i) + ".heap";
        const char* hnPtr = heapName.c_str();
        mallctl("prof.dump", NULL, 0, &hnPtr, sizeof(hnPtr));
      };
      heap_series_start(init, body);
      #endif
    #else
    std::cout << "jemallocStart: JEMALLOC is not defined. not starting." << std::endl;
    #endif
    return unit_t {};
  }

  unit_t __jemalloc_context::jemallocStop(unit_t) {
    #ifdef K3_JEMALLOC
      #ifdef K3_HEAP_SERIES
      heap_series_stop();
      #endif
    mallctl("prof.dump", NULL, 0, NULL, 0);
    bool enable = false;
    mallctl("prof.active", NULL, 0, &enable, sizeof(enable));
    #endif
    return unit_t {};
  }

  unit_t __jemalloc_context::jemallocDump(unit_t) {
    #ifdef K3_JEMALLOC
    mallctl("prof.dump", NULL, 0, NULL, 0);
    #endif
    return unit_t {};
  }

  unit_t __standard_context::openBuiltin(string_impl ch_id, string_impl builtin_ch_id, string_impl fmt) {
    __engine.openBuiltin(ch_id, builtin_ch_id, fmt);
    return unit_t();
  }

  unit_t __standard_context::openFile(string_impl ch_id, string_impl path, string_impl fmt, string_impl mode) {
    IOMode iomode = __engine.ioMode(mode);
    __engine.openFile(ch_id, path, fmt, iomode);
    return unit_t();
  }

  unit_t __standard_context::openSocket(string_impl ch_id, Address a, string_impl fmt, string_impl mode) {
    IOMode iomode = __engine.ioMode(mode);
    __engine.openSocket(ch_id, a, fmt, iomode);
    return unit_t();
  }

  bool __standard_context::hasRead(string_impl ch_id) {
    return  __engine.hasRead(std::string(ch_id));
  }

  template<typename T>
  T __standard_context::doRead(string_impl ch_id) {
    shared_ptr<T> v = __engine.doReadExternal<T>(std::string(ch_id));
    if ( v ) { return *v; }
    T r;
    return r;
  }

  template<typename T>
  Collection<R_elem<T>> __standard_context::doReadBlock(string_impl ch_id, int block_size) {
    return  __engine.doReadExternalBlock<T>(std::string(ch_id), block_size);
  }

  bool __standard_context::hasWrite(string_impl ch_id) {
   return  __engine.hasWrite(std::string(ch_id));
  }

  template<typename T>
  unit_t  __standard_context::doWrite(string_impl ch_id, T& val) {
   __engine.doWriteExternal<T>(std::string(ch_id), val);
   return unit_t{};
  }

  unit_t __standard_context::close(string_impl chan_id) {
      __engine.close(chan_id);
      return unit_t();
  }

  int __standard_context::random(int n) {
    //throw std::runtime_error("Not implemented: random");
    return (rand () % n);
  }

  double __standard_context::randomFraction(unit_t) {
    //throw std::runtime_error("Not implemented: random");
    return ((rand())*1.0)/RAND_MAX ;
  }

  unit_t __standard_context::print(string_impl message) {
    boost::lock_guard<boost::mutex> lock(mutex_);
    std::cout << message;
    return unit_t();
  }

  unit_t __standard_context::haltEngine(unit_t) {
    __engine.forceTerminateEngine();
    return unit_t();
  }

  unit_t __standard_context::drainEngine(unit_t) {
    throw std::runtime_error("Not implemented: drainEngine");
  }

  unit_t __standard_context::sleep(int n) {
    std::this_thread::sleep_for(std::chrono::milliseconds(n));
    return unit_t();
  }


  __pcm_context::__pcm_context() {}

  __pcm_context::~__pcm_context() {}

  unit_t __pcm_context::pcmStart(unit_t) {
    #ifdef K3_PCM
    instance = PCM::getInstance();
    if (instance->program() != PCM::Success) {
      std::cout << "PCM startup error!" << std::endl;
    }
    initial_state = std::make_shared<SystemCounterState>(getSystemCounterState());
    #else
    std::cout << "pcmStart: PCM not set. not starting." << std::endl;
    #endif
    return unit_t();
  }

  unit_t __pcm_context::pcmStop(unit_t) {
    #ifdef K3_PCM
    SystemCounterState after_sstate = getSystemCounterState();
    std::cout << "QPI Incoming: " << getAllIncomingQPILinkBytes(*initial_state, after_sstate) << std::endl;
    std::cout << "QPI Outgoing: " << getAllOutgoingQPILinkBytes(*initial_state, after_sstate) << std::endl;
    std::cout << "L2 cache hit ratio:" << getL2CacheHitRatio(*initial_state,after_sstate) << std::endl;
    std::cout << "L3 cache hit ratio:" << getL3CacheHitRatio(*initial_state,after_sstate) << std::endl;
    std::cout << "Instructions per clock:" << getIPC(*initial_state,after_sstate) << std::endl;
    instance->cleanup();
    #endif
    return unit_t();
  }

  // TODO fix copies related to base_str / std::sring conversion
  F<Collection<R_elem<string_impl>>(const string_impl &)> __string_context::regex_matcher(const string_impl& regex) {
    auto pattern = make_shared<RE2>(regex);
    return [pattern] (const string_impl& in_str) {
      std::string str = in_str;
      re2::StringPiece input(str);
      Collection<R_elem<string_impl>> results;
      std::string s;
      while(RE2::FindAndConsume(&input, *pattern, &s)) {
        results.insert(string_impl(s));
      }
      return results;
    };

  }

  Collection<R_elem<string_impl>> __string_context::regex_matcher_q4(const string_impl& in_str) {
    if (!pattern) {
      pattern = make_shared<RE2>("(?P<url>https?://[^\\s]+)");
    }
    std::string str = in_str;
    re2::StringPiece input(str);
    Collection<R_elem<string_impl>> results;
    std::string s;
    while(RE2::FindAndConsume(&input, *pattern, &s)) {
      results.insert(string_impl(s));
    }
    return results;

  }

  Vector<R_elem<double>> __standard_context::zeroVector(int i) {
    Vector<R_elem<double>> result;
    auto& c = result.getContainer();
    c.resize(i);
    for(int j = 0; j < i; j++) {
     c[j] = R_elem<double>{0.0};
    }
    return result;

  }

  // TODO -> Done
  // Elements must have random values in [0,1)
  Vector<R_elem<double>> __standard_context::randomVector(int i) {
    Vector<R_elem<double>> result;
    auto& c = result.getContainer();
    c.resize(i);
    for(int j = 0; j < i; j++) {
       srand(time(NULL));
       c[j] = R_elem<double>{(rand()/(RAND_MAX+ 1.))};
    }
    return result;
  }

  // Time:
  __time_context::__time_context() {}

  int __time_context::now_int(unit_t) {
    return time_milli();
  }


  // String operations:
  __string_context::__string_context() {}
  string_impl __string_context::itos(int i) {
    return string_impl(to_string(i));
  }

  string_impl __string_context::rtos(double d) {
    return string_impl(to_string(d));
  }

  string_impl __string_context::atos(Address a) {
    return string_impl(addressAsString(a));
  }

  // Split a string by substrings
  Seq<R_elem<string_impl>> __string_context::splitString(string_impl s, const string_impl& splitter) {
    return s.splitString(splitter);
  }

  // Splitter is a single char for now
  string_impl __string_context::takeUntil(const string_impl& s, const string_impl& splitter) {
      char * pch;
      char delim = splitter.c_str()[0];
      const char* buf = s.c_str();
      if (!buf) {
        return string_impl();
      }
      int n = 0;
      while ((*buf != 0) && (*buf != delim)) {
        buf++;
        n++;
      }
      return string_impl(buf, n);

  }

  // Splitter is a single char for now
  int __string_context::countChar(const string_impl& s, const string_impl& splitter) {
      char * pch;
      char delim = splitter.c_str()[0];
      const char* buf = s.c_str();
      if (!buf) {
        return 0;
      }
      int n = 0;
      while ((*buf != 0)) {
        buf++;
        if (*buf == delim) {
          n++;
        }
      }
      return n;
  }

  int __string_context::tpch_date(const string_impl& s) {
    char delim = '-';
    const char* buf = s.c_str();
    if (!buf) {
      return 0;
    }
    char date[9];
    int i = 0;
    for ( ; *buf != 0 && i < 8; buf++ ) {
      if ( *buf != delim ) { date[i] = *buf; i++; }
    }
    date[i] = 0;
    return std::atoi(date);
  }

  string_impl __string_context::tpch_date_to_string(const int& date) {
    std::string tmp = std::to_string(date);
    std::string year = tmp.substr(0, 4);
    std::string month = tmp.substr(4, 2);
    std::string day = tmp.substr(6, 2);
    return year + "-" + month + "-" + day;

  }

} // namespace K3
