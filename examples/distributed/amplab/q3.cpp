#define MAIN_PROGRAM

#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include <external/strtk.hpp>
#include <external/json_spirit_reader_template.h>

#include "Collections.hpp"
#include "Common.hpp"
#include "Dispatch.hpp"
#include "Engine.hpp"
#include "Literals.hpp"
#include "MessageProcessor.hpp"
#include "Serialization.hpp"

using namespace std;
using namespace K3;
using namespace K3::BoostSerializer;
using std::begin;
using std::end;



Engine engine = Engine();

using K3::Collection;

template <class _T0,class _T1> class R_pageRank_count_pageRank_total;

template <class _T0,class _T1> class R_key_value;

template <class _T0> class R_key;

template <class _T0,class _T1,class _T2> class R_avgDuration_pageRank_pageURL;

template <class _T0> class R_arg;

template <class _T0> class R_addr;

template <class _T0,class _T1,class _T2> class R_adRevenue_total_pageRank_count_pageRank_total;

template <class _T0,class _T1,class _T2> class R_adRevenue_total_pageRank_avg_sourceIP;

template <class _T0,class _T1,class _T2,class _T3,class _T4,class _T5,class _T6,class _T7,class _T8> class R_adRevenue_countryCode_destURL_duration_languageCode_searchWord_sourceIP_userAgent_visitDate;

template <class CONTENT> class _Map;

template <class CONTENT> class _Collection;

unit_t atExit(unit_t);

unit_t atInit(unit_t);

unit_t processRole(unit_t);

unit_t initDecls(unit_t);

unit_t global_max(R_adRevenue_total_pageRank_avg_sourceIP<double, double, string>);

unit_t do_global_groupBy(unit_t);

unit_t global_group_receive(unit_t);

unit_t global_group(R_key_value<string, R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>>);

unit_t do_groupBy(unit_t);

unit_t rk_partitions_received(unit_t);

unit_t rk_partition_receive(R_key_value<string, R_pageRank_count_pageRank_total<double, double>>);

unit_t uv_partitions_received(unit_t);

unit_t uv_partition_receive(R_key_value<string, _Map<R_key_value<string, double>>>);

unit_t rk_partition(unit_t);

unit_t uv_partition(unit_t);

template <class v61,class v67> std::function<std::function<unit_t(std::function<unit_t(v67)>)>(v61)> getAt(_Map<R_key_value<v61, v67>>);

template <class CONTENT>
class _Collection: public K3::Collection<CONTENT> {
    public:
        _Collection(): K3::Collection<CONTENT>(&engine) {}

        _Collection(const _Collection& c): K3::Collection<CONTENT>(c) {}

        _Collection(const K3::Collection<CONTENT>& c): K3::Collection<CONTENT>(c) {}

        template <class archive>
        void serialize(archive& _archive,const unsigned int) {

            _archive & boost::serialization::base_object<K3::Collection<CONTENT>>(*this);
        }

};
namespace K3 {
    template <class E>
    struct patcher<_Collection<E>> {
        static void patch(string s,_Collection<E>& c) {
            collection_patcher<_Collection,E>::patch(s,c);
        }
    };
}

template <class CONTENT>
class _Map: public K3::Map<CONTENT> {
    public:
        _Map(): K3::Map<CONTENT>(&engine) {}

        _Map(const _Map& c): K3::Map<CONTENT>(c) {}

        _Map(const K3::Map<CONTENT>& c): K3::Map<CONTENT>(c) {}

        template <class archive>
        void serialize(archive& _archive,const unsigned int) {

            _archive & boost::serialization::base_object<K3::Map<CONTENT>>(*this);
        }

};
namespace K3 {
    template <class E>
    struct patcher<_Map<E>> {
        static void patch(string s,_Map<E>& c) {
            collection_patcher<_Map,E>::patch(s,c);
        }
    };
}

template <class K, class V>
std::function<std::function<std::function<unit_t(std::function<const V&(const V&)>)>(const V&)>(const K&)>
insert_with(_Map<R_key_value<K, V>>& m) {
  return [&] (const K& key) {
    return [&] (const V& value) {
      return [&] (std::function<const V&(const V&)> f) {
        shared_ptr<V> vp = lookup(m)(key);
        if (vp != nullptr) {
          m.insert(R_key_value<K, V> { key, f(*vp) });
        } else {
          m.insert(R_key_value<K, V> { key, f(value) });
        }

        return unit_t();
      };
    };
  };
}

template <class K, class V>
std::function<std::function<std::function<unit_t(std::function<unit_t(const V&)>)>(const V&)>(const K&)>
modify_with(const _Map<R_key_value<K, V>>& m) {
  return [&] (const K& key) {
    return [&] (const V& value) {
      return [&] (std::function<unit_t(const V&)> f) {
        shared_ptr<V> vp = lookup(m)(key);
        if (vp != nullptr) {
          f(*vp);
        } else {
          f(value);
        }

        return unit_t();
      };
    };
  };
}

#ifndef K3_R_adRevenue_countryCode_destURL_duration_languageCode_searchWord_sourceIP_userAgent_visitDate
#define K3_R_adRevenue_countryCode_destURL_duration_languageCode_searchWord_sourceIP_userAgent_visitDate
template <class _T0,class _T1,class _T2,class _T3,class _T4,class _T5,class _T6,class _T7,class _T8>
class R_adRevenue_countryCode_destURL_duration_languageCode_searchWord_sourceIP_userAgent_visitDate {
    public:
        R_adRevenue_countryCode_destURL_duration_languageCode_searchWord_sourceIP_userAgent_visitDate() {}
        R_adRevenue_countryCode_destURL_duration_languageCode_searchWord_sourceIP_userAgent_visitDate(_T0 _adRevenue
                                                                                                     ,_T1 _countryCode
                                                                                                     ,_T2 _destURL
                                                                                                     ,_T3 _duration
                                                                                                     ,_T4 _languageCode
                                                                                                     ,_T5 _searchWord
                                                                                                     ,_T6 _sourceIP
                                                                                                     ,_T7 _userAgent
                                                                                                     ,_T8 _visitDate): adRevenue(_adRevenue), countryCode(_countryCode), destURL(_destURL), duration(_duration), languageCode(_languageCode), searchWord(_searchWord), sourceIP(_sourceIP), userAgent(_userAgent), visitDate(_visitDate) {}
        R_adRevenue_countryCode_destURL_duration_languageCode_searchWord_sourceIP_userAgent_visitDate(const R_adRevenue_countryCode_destURL_duration_languageCode_searchWord_sourceIP_userAgent_visitDate<_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8>& _r): adRevenue(_r.adRevenue), countryCode(_r.countryCode), destURL(_r.destURL), duration(_r.duration), languageCode(_r.languageCode), searchWord(_r.searchWord), sourceIP(_r.sourceIP), userAgent(_r.userAgent), visitDate(_r.visitDate) {}
        bool operator==(R_adRevenue_countryCode_destURL_duration_languageCode_searchWord_sourceIP_userAgent_visitDate _r) {
            if (adRevenue == _r.adRevenue&& countryCode == _r.countryCode&& destURL == _r.destURL&& duration == _r.duration&& languageCode == _r.languageCode&& searchWord == _r.searchWord&& sourceIP == _r.sourceIP&& userAgent == _r.userAgent&& visitDate == _r.visitDate)
                return true;
            return false;
        }
        template <class archive>
        void serialize(archive& _archive,const unsigned int) {
            _archive & adRevenue;
            _archive & countryCode;
            _archive & destURL;
            _archive & duration;
            _archive & languageCode;
            _archive & searchWord;
            _archive & sourceIP;
            _archive & userAgent;
            _archive & visitDate;

        }
        _T0 adRevenue;
        _T1 countryCode;
        _T2 destURL;
        _T3 duration;
        _T4 languageCode;
        _T5 searchWord;
        _T6 sourceIP;
        _T7 userAgent;
        _T8 visitDate;
};
#endif // K3_R_adRevenue_countryCode_destURL_duration_languageCode_searchWord_sourceIP_userAgent_visitDate
namespace K3 {
    template <class _T0,class _T1,class _T2,class _T3,class _T4,class _T5,class _T6,class _T7,class _T8>
    struct patcher<R_adRevenue_countryCode_destURL_duration_languageCode_searchWord_sourceIP_userAgent_visitDate<_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8>> {
        static void patch(string s,
        R_adRevenue_countryCode_destURL_duration_languageCode_searchWord_sourceIP_userAgent_visitDate<_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8>& r) {
            shallow<string::iterator> _shallow;;
            qi::rule<string::iterator, qi::space_type> _adRevenue = (qi::lit("adRevenue") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                              ,r.adRevenue);})];
            qi::rule<string::iterator, qi::space_type> _countryCode = (qi::lit("countryCode") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                                  ,r.countryCode);})];
            qi::rule<string::iterator, qi::space_type> _destURL = (qi::lit("destURL") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                          ,r.destURL);})];
            qi::rule<string::iterator, qi::space_type> _duration = (qi::lit("duration") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                            ,r.duration);})];
            qi::rule<string::iterator, qi::space_type> _languageCode = (qi::lit("languageCode") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                                    ,r.languageCode);})];
            qi::rule<string::iterator, qi::space_type> _searchWord = (qi::lit("searchWord") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                                ,r.searchWord);})];
            qi::rule<string::iterator, qi::space_type> _sourceIP = (qi::lit("sourceIP") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                            ,r.sourceIP);})];
            qi::rule<string::iterator, qi::space_type> _userAgent = (qi::lit("userAgent") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                              ,r.userAgent);})];
            qi::rule<string::iterator, qi::space_type> _visitDate = (qi::lit("visitDate") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                              ,r.visitDate);})];
            qi::rule<string::iterator, qi::space_type> _field = _adRevenue |
            _countryCode |
            _destURL |
            _duration |
            _languageCode |
            _searchWord |
            _sourceIP |
            _userAgent |
            _visitDate;
            qi::rule<string::iterator, qi::space_type> _parser = '{' >> (_field % ',') >> '}';
            qi::phrase_parse(std::begin(s),std::end(s),_parser,qi::space);
        }
    };
}

#ifndef K3_R_adRevenue_total_pageRank_avg_sourceIP
#define K3_R_adRevenue_total_pageRank_avg_sourceIP
template <class _T0,class _T1,class _T2>
class R_adRevenue_total_pageRank_avg_sourceIP {
    public:
        R_adRevenue_total_pageRank_avg_sourceIP() {}
        R_adRevenue_total_pageRank_avg_sourceIP(_T0 _adRevenue_total
                                               ,_T1 _pageRank_avg
                                               ,_T2 _sourceIP): adRevenue_total(_adRevenue_total), pageRank_avg(_pageRank_avg), sourceIP(_sourceIP) {}
        R_adRevenue_total_pageRank_avg_sourceIP(const R_adRevenue_total_pageRank_avg_sourceIP<_T0, _T1, _T2>& _r): adRevenue_total(_r.adRevenue_total), pageRank_avg(_r.pageRank_avg), sourceIP(_r.sourceIP) {}
        bool operator==(R_adRevenue_total_pageRank_avg_sourceIP _r) {
            if (adRevenue_total == _r.adRevenue_total&& pageRank_avg == _r.pageRank_avg&& sourceIP == _r.sourceIP)
                return true;
            return false;
        }
        template <class archive>
        void serialize(archive& _archive,const unsigned int) {
            _archive & adRevenue_total;
            _archive & pageRank_avg;
            _archive & sourceIP;

        }
        _T0 adRevenue_total;
        _T1 pageRank_avg;
        _T2 sourceIP;
};
#endif // K3_R_adRevenue_total_pageRank_avg_sourceIP
namespace K3 {
    template <class _T0,class _T1,class _T2>
    struct patcher<R_adRevenue_total_pageRank_avg_sourceIP<_T0, _T1, _T2>> {
        static void patch(string s,R_adRevenue_total_pageRank_avg_sourceIP<_T0, _T1, _T2>& r) {
            shallow<string::iterator> _shallow;;
            qi::rule<string::iterator, qi::space_type> _adRevenue_total = (qi::lit("adRevenue_total") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                                          ,r.adRevenue_total);})];
            qi::rule<string::iterator, qi::space_type> _pageRank_avg = (qi::lit("pageRank_avg") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                                    ,r.pageRank_avg);})];
            qi::rule<string::iterator, qi::space_type> _sourceIP = (qi::lit("sourceIP") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                            ,r.sourceIP);})];
            qi::rule<string::iterator, qi::space_type> _field = _adRevenue_total |
            _pageRank_avg |
            _sourceIP;
            qi::rule<string::iterator, qi::space_type> _parser = '{' >> (_field % ',') >> '}';
            qi::phrase_parse(std::begin(s),std::end(s),_parser,qi::space);
        }
    };
}

#ifndef K3_R_adRevenue_total_pageRank_count_pageRank_total
#define K3_R_adRevenue_total_pageRank_count_pageRank_total
template <class _T0,class _T1,class _T2>
class R_adRevenue_total_pageRank_count_pageRank_total {
    public:
        R_adRevenue_total_pageRank_count_pageRank_total() {}
        R_adRevenue_total_pageRank_count_pageRank_total(_T0 _adRevenue_total
                                                       ,_T1 _pageRank_count
                                                       ,_T2 _pageRank_total): adRevenue_total(_adRevenue_total), pageRank_count(_pageRank_count), pageRank_total(_pageRank_total) {}
        R_adRevenue_total_pageRank_count_pageRank_total(const R_adRevenue_total_pageRank_count_pageRank_total<_T0, _T1, _T2>& _r): adRevenue_total(_r.adRevenue_total), pageRank_count(_r.pageRank_count), pageRank_total(_r.pageRank_total) {}
        bool operator==(R_adRevenue_total_pageRank_count_pageRank_total _r) {
            if (adRevenue_total == _r.adRevenue_total&& pageRank_count == _r.pageRank_count&& pageRank_total == _r.pageRank_total)
                return true;
            return false;
        }
        template <class archive>
        void serialize(archive& _archive,const unsigned int) {
            _archive & adRevenue_total;
            _archive & pageRank_count;
            _archive & pageRank_total;

        }
        _T0 adRevenue_total;
        _T1 pageRank_count;
        _T2 pageRank_total;
};
#endif // K3_R_adRevenue_total_pageRank_count_pageRank_total
namespace K3 {
    template <class _T0,class _T1,class _T2>
    struct patcher<R_adRevenue_total_pageRank_count_pageRank_total<_T0, _T1, _T2>> {
        static void patch(string s,
        R_adRevenue_total_pageRank_count_pageRank_total<_T0, _T1, _T2>& r) {
            shallow<string::iterator> _shallow;;
            qi::rule<string::iterator, qi::space_type> _adRevenue_total = (qi::lit("adRevenue_total") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                                          ,r.adRevenue_total);})];
            qi::rule<string::iterator, qi::space_type> _pageRank_count = (qi::lit("pageRank_count") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                                        ,r.pageRank_count);})];
            qi::rule<string::iterator, qi::space_type> _pageRank_total = (qi::lit("pageRank_total") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                                        ,r.pageRank_total);})];
            qi::rule<string::iterator, qi::space_type> _field = _adRevenue_total |
            _pageRank_count |
            _pageRank_total;
            qi::rule<string::iterator, qi::space_type> _parser = '{' >> (_field % ',') >> '}';
            qi::phrase_parse(std::begin(s),std::end(s),_parser,qi::space);
        }
    };
}

#ifndef K3_R_addr
#define K3_R_addr
template <class _T0>
class R_addr {
    public:
        R_addr() {}
        R_addr(_T0 _addr): addr(_addr) {}
        R_addr(const R_addr<_T0>& _r): addr(_r.addr) {}
        bool operator==(R_addr _r) {
            if (addr == _r.addr)
                return true;
            return false;
        }
        template <class archive>
        void serialize(archive& _archive,const unsigned int) {
            _archive & addr;

        }
        _T0 addr;
};
#endif // K3_R_addr
namespace K3 {
    template <class _T0>
    struct patcher<R_addr<_T0>> {
        static void patch(string s,R_addr<_T0>& r) {
            shallow<string::iterator> _shallow;;
            qi::rule<string::iterator, qi::space_type> _addr = (qi::lit("addr") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                    ,r.addr);})];
            qi::rule<string::iterator, qi::space_type> _field = _addr;
            qi::rule<string::iterator, qi::space_type> _parser = '{' >> (_field % ',') >> '}';
            qi::phrase_parse(std::begin(s),std::end(s),_parser,qi::space);
        }
    };
}

#ifndef K3_R_arg
#define K3_R_arg
template <class _T0>
class R_arg {
    public:
        R_arg() {}
        R_arg(_T0 _arg): arg(_arg) {}
        R_arg(const R_arg<_T0>& _r): arg(_r.arg) {}
        bool operator==(R_arg _r) {
            if (arg == _r.arg)
                return true;
            return false;
        }
        template <class archive>
        void serialize(archive& _archive,const unsigned int) {
            _archive & arg;

        }
        _T0 arg;
};
#endif // K3_R_arg
namespace K3 {
    template <class _T0>
    struct patcher<R_arg<_T0>> {
        static void patch(string s,R_arg<_T0>& r) {
            shallow<string::iterator> _shallow;;
            qi::rule<string::iterator, qi::space_type> _arg = (qi::lit("arg") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                  ,r.arg);})];
            qi::rule<string::iterator, qi::space_type> _field = _arg;
            qi::rule<string::iterator, qi::space_type> _parser = '{' >> (_field % ',') >> '}';
            qi::phrase_parse(std::begin(s),std::end(s),_parser,qi::space);
        }
    };
}

#ifndef K3_R_avgDuration_pageRank_pageURL
#define K3_R_avgDuration_pageRank_pageURL
template <class _T0,class _T1,class _T2>
class R_avgDuration_pageRank_pageURL {
    public:
        R_avgDuration_pageRank_pageURL() {}
        R_avgDuration_pageRank_pageURL(_T0 _avgDuration
                                      ,_T1 _pageRank
                                      ,_T2 _pageURL): avgDuration(_avgDuration), pageRank(_pageRank), pageURL(_pageURL) {}
        R_avgDuration_pageRank_pageURL(const R_avgDuration_pageRank_pageURL<_T0, _T1, _T2>& _r): avgDuration(_r.avgDuration), pageRank(_r.pageRank), pageURL(_r.pageURL) {}
        bool operator==(R_avgDuration_pageRank_pageURL _r) {
            if (avgDuration == _r.avgDuration&& pageRank == _r.pageRank&& pageURL == _r.pageURL)
                return true;
            return false;
        }
        template <class archive>
        void serialize(archive& _archive,const unsigned int) {
            _archive & avgDuration;
            _archive & pageRank;
            _archive & pageURL;

        }
        _T0 avgDuration;
        _T1 pageRank;
        _T2 pageURL;
};
#endif // K3_R_avgDuration_pageRank_pageURL
namespace K3 {
    template <class _T0,class _T1,class _T2>
    struct patcher<R_avgDuration_pageRank_pageURL<_T0, _T1, _T2>> {
        static void patch(string s,R_avgDuration_pageRank_pageURL<_T0, _T1, _T2>& r) {
            shallow<string::iterator> _shallow;;
            qi::rule<string::iterator, qi::space_type> _avgDuration = (qi::lit("avgDuration") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                                  ,r.avgDuration);})];
            qi::rule<string::iterator, qi::space_type> _pageRank = (qi::lit("pageRank") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                            ,r.pageRank);})];
            qi::rule<string::iterator, qi::space_type> _pageURL = (qi::lit("pageURL") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                          ,r.pageURL);})];
            qi::rule<string::iterator, qi::space_type> _field = _avgDuration | _pageRank | _pageURL;
            qi::rule<string::iterator, qi::space_type> _parser = '{' >> (_field % ',') >> '}';
            qi::phrase_parse(std::begin(s),std::end(s),_parser,qi::space);
        }
    };
}

#ifndef K3_R_key
#define K3_R_key
template <class _T0>
class R_key {
    public:
        R_key() {}
        R_key(_T0 _key): key(_key) {}
        R_key(const R_key<_T0>& _r): key(_r.key) {}
        bool operator==(R_key _r) {
            if (key == _r.key)
                return true;
            return false;
        }
        template <class archive>
        void serialize(archive& _archive,const unsigned int) {
            _archive & key;

        }
        _T0 key;
};
#endif // K3_R_key
namespace K3 {
    template <class _T0>
    struct patcher<R_key<_T0>> {
        static void patch(string s,R_key<_T0>& r) {
            shallow<string::iterator> _shallow;;
            qi::rule<string::iterator, qi::space_type> _key = (qi::lit("key") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                  ,r.key);})];
            qi::rule<string::iterator, qi::space_type> _field = _key;
            qi::rule<string::iterator, qi::space_type> _parser = '{' >> (_field % ',') >> '}';
            qi::phrase_parse(std::begin(s),std::end(s),_parser,qi::space);
        }
    };
}

#ifndef K3_R_key_value
#define K3_R_key_value
template <class _T0,class _T1>
class R_key_value {
    public:
        R_key_value() {}
        R_key_value(_T0 _key,_T1 _value): key(_key), value(_value) {}
        R_key_value(const R_key_value<_T0, _T1>& _r): key(_r.key), value(_r.value) {}
        bool operator==(R_key_value _r) {
            if (key == _r.key&& value == _r.value)
                return true;
            return false;
        }
        template <class archive>
        void serialize(archive& _archive,const unsigned int) {
            _archive & key;
            _archive & value;

        }
        _T0 key;
        _T1 value;
};
#endif // K3_R_key_value
namespace K3 {
    template <class _T0,class _T1>
    struct patcher<R_key_value<_T0, _T1>> {
        static void patch(string s,R_key_value<_T0, _T1>& r) {
            shallow<string::iterator> _shallow;;
            qi::rule<string::iterator, qi::space_type> _key = (qi::lit("key") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                  ,r.key);})];
            qi::rule<string::iterator, qi::space_type> _value = (qi::lit("value") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                      ,r.value);})];
            qi::rule<string::iterator, qi::space_type> _field = _key | _value;
            qi::rule<string::iterator, qi::space_type> _parser = '{' >> (_field % ',') >> '}';
            qi::phrase_parse(std::begin(s),std::end(s),_parser,qi::space);
        }
    };
}

#ifndef K3_R_pageRank_count_pageRank_total
#define K3_R_pageRank_count_pageRank_total
template <class _T0,class _T1>
class R_pageRank_count_pageRank_total {
    public:
        R_pageRank_count_pageRank_total() {}
        R_pageRank_count_pageRank_total(_T0 _pageRank_count
                                       ,_T1 _pageRank_total): pageRank_count(_pageRank_count), pageRank_total(_pageRank_total) {}
        R_pageRank_count_pageRank_total(const R_pageRank_count_pageRank_total<_T0, _T1>& _r): pageRank_count(_r.pageRank_count), pageRank_total(_r.pageRank_total) {}
        bool operator==(R_pageRank_count_pageRank_total _r) {
            if (pageRank_count == _r.pageRank_count&& pageRank_total == _r.pageRank_total)
                return true;
            return false;
        }
        template <class archive>
        void serialize(archive& _archive,const unsigned int) {
            _archive & pageRank_count;
            _archive & pageRank_total;

        }
        _T0 pageRank_count;
        _T1 pageRank_total;
};
#endif // K3_R_pageRank_count_pageRank_total
namespace K3 {
    template <class _T0,class _T1>
    struct patcher<R_pageRank_count_pageRank_total<_T0, _T1>> {
        static void patch(string s,R_pageRank_count_pageRank_total<_T0, _T1>& r) {
            shallow<string::iterator> _shallow;;
            qi::rule<string::iterator, qi::space_type> _pageRank_count = (qi::lit("pageRank_count") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                                        ,r.pageRank_count);})];
            qi::rule<string::iterator, qi::space_type> _pageRank_total = (qi::lit("pageRank_total") >> ':' >> _shallow)[([&r] (string _string) {do_patch(_string
                                                                                                                                                        ,r.pageRank_total);})];
            qi::rule<string::iterator, qi::space_type> _field = _pageRank_count | _pageRank_total;
            qi::rule<string::iterator, qi::space_type> _parser = '{' >> (_field % ',') >> '}';
            qi::phrase_parse(std::begin(s),std::end(s),_parser,qi::space);
        }
    };
}

#include "Builtins.hpp"





































Address me;

_Collection<R_addr<Address>> peers;

tuple<_Collection<R_arg<string>>, _Collection<R_key_value<string, string>>> args;

string role;

Address master;



int peer_count;


Address peer_by_hash(const string& s) {
  auto& container = peers.getContainer();
  size_t h = std::hash<string>()(s); 
  return container[h % container.size()].addr;
}




template <class v61,class v67>
std::function<std::function<unit_t(std::function<unit_t(v67)>)>(v61)> getAt(_Map<R_key_value<v61, v67>> c) {
    return [c] (v61 a) -> std::function<unit_t(std::function<unit_t(v67)>)> {
        return [c,a] (std::function<unit_t(v67)> f) -> unit_t {
            std::shared_ptr<v67> __0;


            __0 = lookup<v61, v67>(c)(a);
            if (__0) {
                v67 k;
                k = *__0;
                return f(k);
            } else {
                return unit_t();
            }
        };
    };
}

_Collection<R_adRevenue_countryCode_destURL_duration_languageCode_searchWord_sourceIP_userAgent_visitDate<double, string, string, int, string, string, string, string, int>> user_visits;

_Collection<R_avgDuration_pageRank_pageURL<int, int, string>> rankings;

_Map<R_key_value<string, _Map<R_key_value<string, double>>>> uv_partitions;

unit_t uv_partition(unit_t _) {


    user_visits.iterate([] (R_adRevenue_countryCode_destURL_duration_languageCode_searchWord_sourceIP_userAgent_visitDate<double, string, string, int, string, string, string, string, int> u) -> unit_t {





        return modify_with<string, _Map<R_key_value<string, double>>>(uv_partitions)(u.destURL)(_Map<R_key_value<string, double>>())([u] (_Map<R_key_value<string, double>> v) -> unit_t {




            return insert_with<string, double>(v)(u.sourceIP)(0.0)([u] (double w) -> double {
                return w + u.adRevenue;
            });
        });
    });

    uv_partitions.iterate([] (R_key_value<string, _Map<R_key_value<string, double>>> up) -> unit_t {




        auto d = make_shared<DispatcherImpl<R_key_value<string, _Map<R_key_value<string, double>>>>>(uv_partition_receive
                                                                                                    ,up);
        engine.send(peer_by_hash(up.key),8,d);return unit_t();
    });

    return peers.iterate([] (R_addr<Address> a) -> unit_t {



        auto d = make_shared<DispatcherImpl<unit_t>>(uv_partitions_received,unit_t());
        engine.send(a.addr,7,d);return unit_t();
    });
}

_Map<R_key_value<string, R_pageRank_count_pageRank_total<double, double>>> rk_partitions;

unit_t rk_partition(unit_t _) {

    rankings.iterate([] (R_avgDuration_pageRank_pageURL<int, int, string> r) -> unit_t {






        return insert_with<string, R_pageRank_count_pageRank_total<double, double>>(rk_partitions)(r.pageURL)(R_pageRank_count_pageRank_total<double, double>{0.0,
        0.0})([r] (R_pageRank_count_pageRank_total<double, double> v) -> R_pageRank_count_pageRank_total<double, double> {

            return R_pageRank_count_pageRank_total<double, double>{v.pageRank_count + 1,
            v.pageRank_total + r.pageRank};
        });
    });


    rk_partitions.iterate([] (R_key_value<string, R_pageRank_count_pageRank_total<double, double>> rp) -> unit_t {




        auto d = make_shared<DispatcherImpl<R_key_value<string, R_pageRank_count_pageRank_total<double, double>>>>(rk_partition_receive
                                                                                                                  ,rp);
        engine.send(peer_by_hash(rp.key),6,d);return unit_t();
    });

    return peers.iterate([] (R_addr<Address> a) -> unit_t {



        auto d = make_shared<DispatcherImpl<unit_t>>(rk_partitions_received,unit_t());
        engine.send(a.addr,5,d);return unit_t();
    });
}

_Map<R_key_value<string, _Map<R_key_value<string, double>>>> uv_candidates;

unit_t uv_partition_receive(R_key_value<string, _Map<R_key_value<string, double>>> up) {





    return modify_with<string, _Map<R_key_value<string, double>>>(uv_candidates)(up.key)(_Map<R_key_value<string, double>>())([&up] (_Map<R_key_value<string, double>> v) -> unit_t {

        return up.value.iterate([&v] (R_key_value<string,double> uc) -> unit_t {




            return insert_with<string, double>(v)(uc.key)(0.0)([] (double w) -> double {
                return w + 0.0;
            });
        });
    });
}

int uv_received;

int rk_received;

unit_t uv_partitions_received(unit_t _) {
    uv_received = uv_received + 1;
    if (uv_received == peer_count && rk_received == peer_count) {



        auto d = make_shared<DispatcherImpl<unit_t>>(do_groupBy,unit_t());
        engine.send(me,4,d);return unit_t();
    } else {
        return unit_t();
    }
}

_Map<R_key_value<string, R_pageRank_count_pageRank_total<double, double>>> rk_candidates;

unit_t rk_partition_receive(R_key_value<string, R_pageRank_count_pageRank_total<double, double>> rp) {






  return insert_with<string, R_pageRank_count_pageRank_total<double, double>>(rk_candidates)(rp.key)(R_pageRank_count_pageRank_total<double, double>{0,
    0})([rp] (R_pageRank_count_pageRank_total<double, double> v) -> R_pageRank_count_pageRank_total<double, double> {

        return R_pageRank_count_pageRank_total<double, double>{v.pageRank_count + 1,
        v.pageRank_total + rp.value.pageRank_total};
    });
}

unit_t rk_partitions_received(unit_t _) {
    rk_received = rk_received + 1;
    if (uv_received == peer_count && rk_received == peer_count) {



        auto d = make_shared<DispatcherImpl<unit_t>>(do_groupBy,unit_t());
        engine.send(me,4,d);return unit_t();
    } else {
        return unit_t();
    }
}

_Map<R_key_value<string, R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>>> local_group;

unit_t do_groupBy(unit_t _) {

    uv_candidates.iterate([] (R_key_value<string, _Map<R_key_value<string, double>>> uc) -> unit_t {
        {
            R_pageRank_count_pageRank_total<double, double> rk;
            std::shared_ptr<R_pageRank_count_pageRank_total<double, double>> __1;



            __1 = lookup<R_key_value<string, R_pageRank_count_pageRank_total<double, double>>>(rk_candidates)(uc.key);
            if (__1) {
                R_pageRank_count_pageRank_total<double, double> r;
                r = *__1;rk = r;
            } else {

                rk = R_pageRank_count_pageRank_total<double, double>{0,0};
            }

            return uc.value.iterate([rk] (R_key_value<string, double> sar) -> unit_t {





                return local_group.insert(R_key_value<string, R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>>{sar.key,
                R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>{sar.value,
                rk.pageRank_count,
                rk.pageRank_total}});
            });
        }
    });


    local_group.iterate([] (R_key_value<string, R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>> g) -> unit_t {




        auto d = make_shared<DispatcherImpl<R_key_value<string, R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>>>>(global_group
                                                                                                                                          ,g);
        engine.send(peer_by_hash(g.key),3,d);return unit_t();
    });

    return peers.iterate([] (R_addr<Address> p) -> unit_t {



        auto d = make_shared<DispatcherImpl<unit_t>>(global_group_receive,unit_t());
        engine.send(p.addr,2,d);return unit_t();
    });
}

_Map<R_key_value<string, R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>>> global_groups;

unit_t global_group(R_key_value<string, R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>> g) {

    return global_groups.insert(g);
}

int global_received;

unit_t global_group_receive(unit_t _) {
    global_received = global_received + 1;
    if (global_received == peer_count) {



        auto d = make_shared<DispatcherImpl<unit_t>>(do_global_groupBy,unit_t());
        engine.send(me,1,d);return unit_t();
    } else {
        return unit_t();
    }
}

_Map<R_key_value<string, R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>>> global_groupBy_result;

unit_t do_global_groupBy(unit_t _) {


    global_groups.iterate([] (R_key_value<string, R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>> r) -> unit_t {







        return insert_with<string, R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>>(global_groupBy_result)(r.key)(R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>{0.0,
        0.0,
        0.0})([r] (R_adRevenue_total_pageRank_count_pageRank_total<double, double, double> w) -> R_adRevenue_total_pageRank_count_pageRank_total<double, double, double> {



            return R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>{w.adRevenue_total + r.value.adRevenue_total,
            w.pageRank_count + r.value.pageRank_count,
            w.pageRank_total + r.value.pageRank_total};
        });
    });







    auto d = make_shared<DispatcherImpl<R_adRevenue_total_pageRank_avg_sourceIP<double, double, string>>>(global_max
                                                                                                         ,global_groupBy_result.fold<R_adRevenue_total_pageRank_avg_sourceIP<double, double, string>>([] (R_adRevenue_total_pageRank_avg_sourceIP<double, double, string> a) -> std::function<R_adRevenue_total_pageRank_avg_sourceIP<double, double, string>(R_key_value<string, R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>>)> {

                                                                                                             return [a] (R_key_value<string, R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>> r) -> R_adRevenue_total_pageRank_avg_sourceIP<double, double, string> {


                                                                                                                 if (r.value.adRevenue_total > a.adRevenue_total) {




                                                                                                                     return R_adRevenue_total_pageRank_avg_sourceIP<double, double, string>{r.value.adRevenue_total,
                                                                                                                     r.value.pageRank_total / r.value.pageRank_count,
                                                                                                                     r.key};
                                                                                                                 }
                                                                                                                 else {

                                                                                                                     return a;
                                                                                                                 }
                                                                                                             };
                                                                                                         })(R_adRevenue_total_pageRank_avg_sourceIP<double, double, string>{0.0,
                                                                                                         0.0,
                                                                                                         string("")}));
    engine.send(master,0,d);return unit_t();
}

R_adRevenue_total_pageRank_avg_sourceIP<double, double, string> max_result;

unit_t global_max(R_adRevenue_total_pageRank_avg_sourceIP<double, double, string> r) {
    if (r.adRevenue_total > max_result.adRevenue_total) {
        max_result = r;return unit_t();
    } else {
        return unit_t();
    }
}

unit_t initDecls(unit_t _) {
    return unit_t();
}

unit_t processRole(unit_t _) {
    return unit_t();
}

unit_t atInit(unit_t _) {

    initDecls(unit_t());

    return processRole(unit_t());
}

unit_t atExit(unit_t _) {
    return unit_t();
}

unit_t initGlobalDecls() {

    master = make_address(string("127.0.0.1"),30001);peer_count = 0;uv_received = 0;rk_received = 0;
    global_received = 0;

    max_result = R_adRevenue_total_pageRank_avg_sourceIP<double, double, string>{0.0,
    0.0,
    string("")};return unit_t();
}

void populate_dispatch() {
    dispatch_table.resize(11);
    dispatch_table[0] = make_tuple(make_shared<DispatcherImpl<R_adRevenue_total_pageRank_avg_sourceIP<double, double, string>>>(global_max), "global_max");
    dispatch_table[1] = make_tuple(make_shared<DispatcherImpl<unit_t>>(do_global_groupBy), "do_global_groupBy");
    dispatch_table[2] = make_tuple(make_shared<DispatcherImpl<unit_t>>(global_group_receive), "global_group_receive");
    dispatch_table[3] = make_tuple(make_shared<DispatcherImpl<R_key_value<string, R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>>>>(global_group), "global_group");
    dispatch_table[4] = make_tuple(make_shared<DispatcherImpl<unit_t>>(do_groupBy), "do_groupBy");
    dispatch_table[5] = make_tuple(make_shared<DispatcherImpl<unit_t>>(rk_partitions_received), "rk_partitions_received");
    dispatch_table[6] = make_tuple(make_shared<DispatcherImpl<R_key_value<string, R_pageRank_count_pageRank_total<double, double>>>>(rk_partition_receive), "rk_partition_receive");
    dispatch_table[7] = make_tuple(make_shared<DispatcherImpl<unit_t>>(uv_partitions_received), "uv_partitions_received");
    dispatch_table[8] = make_tuple(make_shared<DispatcherImpl<R_key_value<string, _Map<R_key_value<string, double>>>>>(uv_partition_receive), "uv_partition_receive");
    dispatch_table[9] = make_tuple(make_shared<DispatcherImpl<unit_t>>(rk_partition), "rk_partition");
    dispatch_table[10] = make_tuple(make_shared<DispatcherImpl<unit_t>>(uv_partition), "uv_partition");
}

map<string,string> show_globals() {
    map<string,string> result;
    result["max_result"] = "{" + ("sourceIP:" + max_result.sourceIP + "," + "adRevenue_total:" + to_string(max_result.adRevenue_total) + "," + "pageRank_avg:" + to_string(max_result.pageRank_avg) + "}");
    result["global_groupBy_result"] = ([] (_Map<R_key_value<string, R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>>> coll) {
        ostringstream oss;
        auto f = [&] (R_key_value<string, R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>> elem) {oss << "{" + ("key:" + elem.key + "," + "value:" + "{" + ("pageRank_total:" + to_string(elem.value.pageRank_total) + "," + "pageRank_count:" + to_string(elem.value.pageRank_count) + "," + "adRevenue_total:" + to_string(elem.value.adRevenue_total) + "}") + "}") << ",";
        return unit_t();};
        coll.iterate(f);
        return "[" + oss.str() + "]";
    }(global_groupBy_result));
    result["global_received"] = to_string(global_received);
    result["global_groups"] = ([] (_Map<R_key_value<string, R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>>> coll) {
        ostringstream oss;
        auto f = [&] (R_key_value<string, R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>> elem) {oss << "{" + ("key:" + elem.key + "," + "value:" + "{" + ("pageRank_total:" + to_string(elem.value.pageRank_total) + "," + "pageRank_count:" + to_string(elem.value.pageRank_count) + "," + "adRevenue_total:" + to_string(elem.value.adRevenue_total) + "}") + "}") << ",";
        return unit_t();};
        coll.iterate(f);
        return "[" + oss.str() + "]";
    }(global_groups));
    result["local_group"] = ([] (_Map<R_key_value<string, R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>>> coll) {
        ostringstream oss;
        auto f = [&] (R_key_value<string, R_adRevenue_total_pageRank_count_pageRank_total<double, double, double>> elem) {oss << "{" + ("key:" + elem.key + "," + "value:" + "{" + ("pageRank_total:" + to_string(elem.value.pageRank_total) + "," + "pageRank_count:" + to_string(elem.value.pageRank_count) + "," + "adRevenue_total:" + to_string(elem.value.adRevenue_total) + "}") + "}") << ",";
        return unit_t();};
        coll.iterate(f);
        return "[" + oss.str() + "]";
    }(local_group));
    result["rk_candidates"] = ([] (_Map<R_key_value<string, R_pageRank_count_pageRank_total<double, double>>> coll) {
        ostringstream oss;
        auto f = [&] (R_key_value<string, R_pageRank_count_pageRank_total<double, double>> elem) {oss << "{" + ("key:" + elem.key + "," + "value:" + "{" + ("pageRank_total:" + to_string(elem.value.pageRank_total) + "," + "pageRank_count:" + to_string(elem.value.pageRank_count) + "}") + "}") << ",";
        return unit_t();};
        coll.iterate(f);
        return "[" + oss.str() + "]";
    }(rk_candidates));
    result["rk_received"] = to_string(rk_received);
    result["uv_received"] = to_string(uv_received);
    result["uv_candidates"] = ([] (_Map<R_key_value<string, _Map<R_key_value<string, double>>>> coll) {
        ostringstream oss;
        auto f = [&] (R_key_value<string, _Map<R_key_value<string, double>>> elem) {oss << "{" + ("key:" + elem.key + "," + "value:" + ([] (_Map<R_key_value<string, double>> coll) {
            ostringstream oss;
            auto f = [&] (R_key_value<string, double> elem) {oss << "{" + ("key:" + elem.key + "," + "value:" + to_string(elem.value) + "}") << ",";
            return unit_t();};
            coll.iterate(f);
            return "[" + oss.str() + "]";
        }(elem.value)) + "}") << ",";
        return unit_t();};
        coll.iterate(f);
        return "[" + oss.str() + "]";
    }(uv_candidates));
    result["rk_partitions"] = ([] (_Map<R_key_value<string, R_pageRank_count_pageRank_total<double, double>>> coll) {
        ostringstream oss;
        auto f = [&] (R_key_value<string, R_pageRank_count_pageRank_total<double, double>> elem) {oss << "{" + ("key:" + elem.key + "," + "value:" + "{" + ("pageRank_total:" + to_string(elem.value.pageRank_total) + "," + "pageRank_count:" + to_string(elem.value.pageRank_count) + "}") + "}") << ",";
        return unit_t();};
        coll.iterate(f);
        return "[" + oss.str() + "]";
    }(rk_partitions));
    result["uv_partitions"] = ([] (_Map<R_key_value<string, _Map<R_key_value<string, double>>>> coll) {
        ostringstream oss;
        auto f = [&] (R_key_value<string, _Map<R_key_value<string, double>>> elem) {oss << "{" + ("key:" + elem.key + "," + "value:" + ([] (_Map<R_key_value<string, double>> coll) {
            ostringstream oss;
            auto f = [&] (R_key_value<string, double> elem) {oss << "{" + ("key:" + elem.key + "," + "value:" + to_string(elem.value) + "}") << ",";
            return unit_t();};
            coll.iterate(f);
            return "[" + oss.str() + "]";
        }(elem.value)) + "}") << ",";
        return unit_t();};
        coll.iterate(f);
        return "[" + oss.str() + "]";
    }(uv_partitions));
    result["rankings"] = ([] (_Collection<R_avgDuration_pageRank_pageURL<int, int, string>> coll) {
        ostringstream oss;
        auto f = [&] (R_avgDuration_pageRank_pageURL<int, int, string> elem) {oss << "{" + ("pageURL:" + elem.pageURL + "," + "pageRank:" + to_string(elem.pageRank) + "," + "avgDuration:" + to_string(elem.avgDuration) + "}") << ",";
        return unit_t();};
        coll.iterate(f);
        return "[" + oss.str() + "]";
    }(rankings));
    result["user_visits"] = ([] (_Collection<R_adRevenue_countryCode_destURL_duration_languageCode_searchWord_sourceIP_userAgent_visitDate<double, string, string, int, string, string, string, string, int>> coll) {
        ostringstream oss;
        auto f = [&] (R_adRevenue_countryCode_destURL_duration_languageCode_searchWord_sourceIP_userAgent_visitDate<double, string, string, int, string, string, string, string, int> elem) {oss << "{" + ("sourceIP:" + elem.sourceIP + "," + "destURL:" + elem.destURL + "," + "visitDate:" + to_string(elem.visitDate) + "," + "adRevenue:" + to_string(elem.adRevenue) + "," + "userAgent:" + elem.userAgent + "," + "countryCode:" + elem.countryCode + "," + "languageCode:" + elem.languageCode + "," + "searchWord:" + elem.searchWord + "," + "duration:" + to_string(elem.duration) + "}") << ",";
        return unit_t();};
        coll.iterate(f);
        return "[" + oss.str() + "]";
    }(user_visits));
    result["peer_count"] = to_string(peer_count);
    result["master"] = addressAsString(master);
    result["role"] = role;
    result["args"] = "("
    +
    ([] (_Collection<R_arg<string>> coll) {
        ostringstream oss;
        auto f = [&] (R_arg<string> elem) {oss << "{" + ("arg:" + elem.arg + "}") << ",";
        return unit_t();};
        coll.iterate(f);
        return "[" + oss.str() + "]";
    }(get<0>(args))) + "," + ([] (_Collection<R_key_value<string, string>> coll) {
        ostringstream oss;
        auto f = [&] (R_key_value<string, string> elem) {oss << "{" + ("key:" + elem.key + "," + "value:" + elem.value + "}") << ",";
        return unit_t();};
        coll.iterate(f);
        return "[" + oss.str() + "]";
    }(get<1>(args)))
    +
    ")";
    result["peers"] = ([] (_Collection<R_addr<Address>> coll) {
        ostringstream oss;
        auto f = [&] (R_addr<Address> elem) {oss << "{" + ("addr:" + addressAsString(elem.addr) + "}") << ",";
        return unit_t();};
        coll.iterate(f);
        return "[" + oss.str() + "]";
    }(peers));
    result["me"] = addressAsString(me);
    return result;
}

F<unit_t(K3::Collection<R_avgDuration_pageRank_pageURL<int, int, string>>&)>rankingsLoader(string filepath){
    F<unit_t(K3::Collection<R_avgDuration_pageRank_pageURL<int, int, string>>&)> r = [filepath] (K3::Collection<R_avgDuration_pageRank_pageURL<int, int, string>> & c){
        R_avgDuration_pageRank_pageURL<int, int, string> rec;
        strtk::for_each_line(filepath,
        [&](const std::string& str){
            if (strtk::parse(str,",",rec.avgDuration,rec.pageRank,rec.pageURL)){
                c.insert(rec);
            }
            else{
                std::cout << "Failed to parse a row" << std::endl;
            }
        });
        return unit_t();
    };
    return r;
}

F<unit_t(K3::Collection<R_adRevenue_countryCode_destURL_duration_languageCode_searchWord_sourceIP_userAgent_visitDate<double, string, string, int, string, string, string, string, string>>&)>uservisitsLoader(string filepath){
    F<unit_t(K3::Collection<R_adRevenue_countryCode_destURL_duration_languageCode_searchWord_sourceIP_userAgent_visitDate<double, string, string, int, string, string, string, string, string>>&)> r = [filepath] (K3::Collection<R_adRevenue_countryCode_destURL_duration_languageCode_searchWord_sourceIP_userAgent_visitDate<double, string, string, int, string, string, string, string, string>> & c){
        R_adRevenue_countryCode_destURL_duration_languageCode_searchWord_sourceIP_userAgent_visitDate<double, string, string, int, string, string, string, string, string> rec;
        strtk::for_each_line(filepath,
        [&](const std::string& str){
            if (strtk::parse(str,",",rec.sourceIP,rec.destURL,rec.visitDate,rec.adRevenue,rec.userAgent,rec.countryCode,rec.languageCode,rec.searchWord,rec.duration)){
                c.insert(rec);
            }
            else{
                std::cout << "Failed to parse a row" << std::endl;
            }
        });
        return unit_t();
    };
    return r;
}

int main(int argc,char** argv) {
    initGlobalDecls();
    Options opt;
    if (opt.parse(argc,argv)) return 0;
    populate_dispatch();
    map<string,std::function<void(string)>> matchers;
    matchers["max_result"] = [] (string _s) {do_patch(_s,max_result);};
    matchers["global_groupBy_result"] = [] (string _s) {do_patch(_s,global_groupBy_result);};
    matchers["global_received"] = [] (string _s) {do_patch(_s,global_received);};
    matchers["global_groups"] = [] (string _s) {do_patch(_s,global_groups);};
    matchers["local_group"] = [] (string _s) {do_patch(_s,local_group);};
    matchers["rk_candidates"] = [] (string _s) {do_patch(_s,rk_candidates);};
    matchers["rk_received"] = [] (string _s) {do_patch(_s,rk_received);};
    matchers["uv_received"] = [] (string _s) {do_patch(_s,uv_received);};
    matchers["uv_candidates"] = [] (string _s) {do_patch(_s,uv_candidates);};
    matchers["rk_partitions"] = [] (string _s) {do_patch(_s,rk_partitions);};
    matchers["uv_partitions"] = [] (string _s) {do_patch(_s,uv_partitions);};
    matchers["rankings"] = [] (string _s) {do_patch(_s,rankings);};
    matchers["user_visits"] = [] (string _s) {do_patch(_s,user_visits);};
    matchers["peer_count"] = [] (string _s) {do_patch(_s,peer_count);};
    matchers["master"] = [] (string _s) {do_patch(_s,master);};
    matchers["role"] = [] (string _s) {do_patch(_s,role);};
    matchers["args"] = [] (string _s) {do_patch(_s,args);};
    matchers["peers"] = [] (string _s) {do_patch(_s,peers);};
    matchers["me"] = [] (string _s) {do_patch(_s,me);};
    string parse_arg = opt.peer_strings[0];;
    map<string,string> bindings = parse_bindings(parse_arg);
    match_patchers(bindings,matchers);
    list<Address> addr_l;
    addr_l.push_back(me);
    SystemEnvironment se = defaultEnvironment(addr_l);
    engine.configure(opt.simulation
                    ,se
                    ,make_shared<DefaultInternalCodec>(DefaultInternalCodec())
                    ,opt.log_level);
    processRole(unit_t());
    DispatchMessageProcessor dmp = DispatchMessageProcessor(show_globals);;
    engine.runEngine(make_shared<DispatchMessageProcessor>(dmp));
    return 0;
}
