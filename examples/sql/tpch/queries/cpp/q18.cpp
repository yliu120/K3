#include "functional"
#include "map"
#include "memory"
#include "sstream"
#include "string"
#include "tuple"
#include "boost/multi_index_container.hpp"
#include "boost/multi_index/ordered_index.hpp"
#include "boost/multi_index/member.hpp"
#include "boost/multi_index/composite_key.hpp"
#include "BaseTypes.hpp"
#include "BaseString.hpp"
#include "Common.hpp"
#include "Context.hpp"
#include "Dispatch.hpp"
#include "Engine.hpp"
#include "MessageProcessor.hpp"
#include "Literals.hpp"
#include "Serialization.hpp"
#include "Builtins.hpp"
#include "Run.hpp"
#include "Prettify.hpp"
#include "dataspace/Dataspace.hpp"
#include "strtk.hpp"
using K3::unit_t;
using K3::Address;
using K3::Engine;
using K3::string_impl;
using K3::Options;
using K3::ValDispatcher;
using K3::Dispatcher;
using K3::virtualizing_message_processor;
using K3::make_address;
using K3::__k3_context;
using K3::runProgram;
using K3::SystemEnvironment;
using K3::processRoles;
using K3::do_patch;
using K3::defaultEnvironment;
using K3::createContexts;
using K3::getAddrs;
using K3::DefaultInternalCodec;
using std::make_tuple;
using std::make_shared;
using std::shared_ptr;
using std::get;
using std::map;
using std::list;
using std::ostringstream;
#ifndef K3_R_acctbal_address_availqty_brand_clerk_comments_commitdate_container_custkey_d_size_discount_event_extendedprice_linenumber_linestatus_mfgr_mktsegment_name_nationkey_oid_orderdate_orderkey_orderpriority_orderstatus_partkey_phone_quantity_receiptdate_regionkey_retailprice_returnflag_schema_shipdate_shipinstruct_shipmode_shippriority_suppkey_supplycost_tax_totalprice_type2_hash_value
#define K3_R_acctbal_address_availqty_brand_clerk_comments_commitdate_container_custkey_d_size_discount_event_extendedprice_linenumber_linestatus_mfgr_mktsegment_name_nationkey_oid_orderdate_orderkey_orderpriority_orderstatus_partkey_phone_quantity_receiptdate_regionkey_retailprice_returnflag_schema_shipdate_shipinstruct_shipmode_shippriority_suppkey_supplycost_tax_totalprice_type2_hash_value
template <class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7,
class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15,
class _T16, class _T17, class _T18, class _T19, class _T20, class _T21, class _T22, class _T23,
class _T24, class _T25, class _T26, class _T27, class _T28, class _T29, class _T30, class _T31,
class _T32, class _T33, class _T34, class _T35, class _T36, class _T37, class _T38, class _T39,
class _T40>
class R_acctbal_address_availqty_brand_clerk_comments_commitdate_container_custkey_d_size_discount_event_extendedprice_linenumber_linestatus_mfgr_mktsegment_name_nationkey_oid_orderdate_orderkey_orderpriority_orderstatus_partkey_phone_quantity_receiptdate_regionkey_retailprice_returnflag_schema_shipdate_shipinstruct_shipmode_shippriority_suppkey_supplycost_tax_totalprice_type2 {
  public:
      R_acctbal_address_availqty_brand_clerk_comments_commitdate_container_custkey_d_size_discount_event_extendedprice_linenumber_linestatus_mfgr_mktsegment_name_nationkey_oid_orderdate_orderkey_orderpriority_orderstatus_partkey_phone_quantity_receiptdate_regionkey_retailprice_returnflag_schema_shipdate_shipinstruct_shipmode_shippriority_suppkey_supplycost_tax_totalprice_type2(): acctbal(),
      address(), availqty(), brand(), clerk(), comments(), commitdate(), container(), custkey(),
      d_size(), discount(), event(), extendedprice(), linenumber(), linestatus(), mfgr(),
      mktsegment(), name(), nationkey(), oid(), orderdate(), orderkey(), orderpriority(),
      orderstatus(), partkey(), phone(), quantity(), receiptdate(), regionkey(), retailprice(),
      returnflag(), schema(), shipdate(), shipinstruct(), shipmode(), shippriority(), suppkey(),
      supplycost(), tax(), totalprice(), type2()  {}
      template <class __T0, class __T1, class __T2, class __T3, class __T4, class __T5, class __T6,
      class __T7, class __T8, class __T9, class __T10, class __T11, class __T12, class __T13,
      class __T14, class __T15, class __T16, class __T17, class __T18, class __T19, class __T20,
      class __T21, class __T22, class __T23, class __T24, class __T25, class __T26, class __T27,
      class __T28, class __T29, class __T30, class __T31, class __T32, class __T33, class __T34,
      class __T35, class __T36, class __T37, class __T38, class __T39, class __T40>
      R_acctbal_address_availqty_brand_clerk_comments_commitdate_container_custkey_d_size_discount_event_extendedprice_linenumber_linestatus_mfgr_mktsegment_name_nationkey_oid_orderdate_orderkey_orderpriority_orderstatus_partkey_phone_quantity_receiptdate_regionkey_retailprice_returnflag_schema_shipdate_shipinstruct_shipmode_shippriority_suppkey_supplycost_tax_totalprice_type2(__T0&& _acctbal,
      __T1&& _address, __T2&& _availqty, __T3&& _brand, __T4&& _clerk, __T5&& _comments,
      __T6&& _commitdate, __T7&& _container, __T8&& _custkey, __T9&& _d_size, __T10&& _discount,
      __T11&& _event, __T12&& _extendedprice, __T13&& _linenumber, __T14&& _linestatus,
      __T15&& _mfgr, __T16&& _mktsegment, __T17&& _name, __T18&& _nationkey, __T19&& _oid,
      __T20&& _orderdate, __T21&& _orderkey, __T22&& _orderpriority, __T23&& _orderstatus,
      __T24&& _partkey, __T25&& _phone, __T26&& _quantity, __T27&& _receiptdate, __T28&& _regionkey,
      __T29&& _retailprice, __T30&& _returnflag, __T31&& _schema, __T32&& _shipdate,
      __T33&& _shipinstruct, __T34&& _shipmode, __T35&& _shippriority, __T36&& _suppkey,
      __T37&& _supplycost, __T38&& _tax, __T39&& _totalprice,
      __T40&& _type2): acctbal(std::forward<__T0>(_acctbal)), address(std::forward<__T1>(_address)),
      availqty(std::forward<__T2>(_availqty)), brand(std::forward<__T3>(_brand)),
      clerk(std::forward<__T4>(_clerk)), comments(std::forward<__T5>(_comments)),
      commitdate(std::forward<__T6>(_commitdate)), container(std::forward<__T7>(_container)),
      custkey(std::forward<__T8>(_custkey)), d_size(std::forward<__T9>(_d_size)),
      discount(std::forward<__T10>(_discount)), event(std::forward<__T11>(_event)),
      extendedprice(std::forward<__T12>(_extendedprice)),
      linenumber(std::forward<__T13>(_linenumber)), linestatus(std::forward<__T14>(_linestatus)),
      mfgr(std::forward<__T15>(_mfgr)), mktsegment(std::forward<__T16>(_mktsegment)),
      name(std::forward<__T17>(_name)), nationkey(std::forward<__T18>(_nationkey)),
      oid(std::forward<__T19>(_oid)), orderdate(std::forward<__T20>(_orderdate)),
      orderkey(std::forward<__T21>(_orderkey)), orderpriority(std::forward<__T22>(_orderpriority)),
      orderstatus(std::forward<__T23>(_orderstatus)), partkey(std::forward<__T24>(_partkey)),
      phone(std::forward<__T25>(_phone)), quantity(std::forward<__T26>(_quantity)),
      receiptdate(std::forward<__T27>(_receiptdate)), regionkey(std::forward<__T28>(_regionkey)),
      retailprice(std::forward<__T29>(_retailprice)), returnflag(std::forward<__T30>(_returnflag)),
      schema(std::forward<__T31>(_schema)), shipdate(std::forward<__T32>(_shipdate)),
      shipinstruct(std::forward<__T33>(_shipinstruct)), shipmode(std::forward<__T34>(_shipmode)),
      shippriority(std::forward<__T35>(_shippriority)), suppkey(std::forward<__T36>(_suppkey)),
      supplycost(std::forward<__T37>(_supplycost)), tax(std::forward<__T38>(_tax)),
      totalprice(std::forward<__T39>(_totalprice)), type2(std::forward<__T40>(_type2))  {}
      bool operator==(const R_acctbal_address_availqty_brand_clerk_comments_commitdate_container_custkey_d_size_discount_event_extendedprice_linenumber_linestatus_mfgr_mktsegment_name_nationkey_oid_orderdate_orderkey_orderpriority_orderstatus_partkey_phone_quantity_receiptdate_regionkey_retailprice_returnflag_schema_shipdate_shipinstruct_shipmode_shippriority_suppkey_supplycost_tax_totalprice_type2<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17,
      _T18, _T19, _T20, _T21, _T22, _T23, _T24, _T25, _T26, _T27, _T28, _T29, _T30, _T31, _T32,
      _T33, _T34, _T35, _T36, _T37, _T38, _T39, _T40>& __other) const {
        return acctbal == (__other.acctbal) && address == (__other.address) && availqty == (__other.availqty) && brand == (__other.brand) && clerk == (__other.clerk) && comments == (__other.comments) && commitdate == (__other.commitdate) && container == (__other.container) && custkey == (__other.custkey) && d_size == (__other.d_size) && discount == (__other.discount) && event == (__other.event) && extendedprice == (__other.extendedprice) && linenumber == (__other.linenumber) && linestatus == (__other.linestatus) && mfgr == (__other.mfgr) && mktsegment == (__other.mktsegment) && name == (__other.name) && nationkey == (__other.nationkey) && oid == (__other.oid) && orderdate == (__other.orderdate) && orderkey == (__other.orderkey) && orderpriority == (__other.orderpriority) && orderstatus == (__other.orderstatus) && partkey == (__other.partkey) && phone == (__other.phone) && quantity == (__other.quantity) && receiptdate == (__other.receiptdate) && regionkey == (__other.regionkey) && retailprice == (__other.retailprice) && returnflag == (__other.returnflag) && schema == (__other.schema) && shipdate == (__other.shipdate) && shipinstruct == (__other.shipinstruct) && shipmode == (__other.shipmode) && shippriority == (__other.shippriority) && suppkey == (__other.suppkey) && supplycost == (__other.supplycost) && tax == (__other.tax) && totalprice == (__other.totalprice) && type2 == (__other.type2);
      }
      bool operator!=(const R_acctbal_address_availqty_brand_clerk_comments_commitdate_container_custkey_d_size_discount_event_extendedprice_linenumber_linestatus_mfgr_mktsegment_name_nationkey_oid_orderdate_orderkey_orderpriority_orderstatus_partkey_phone_quantity_receiptdate_regionkey_retailprice_returnflag_schema_shipdate_shipinstruct_shipmode_shippriority_suppkey_supplycost_tax_totalprice_type2<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17,
      _T18, _T19, _T20, _T21, _T22, _T23, _T24, _T25, _T26, _T27, _T28, _T29, _T30, _T31, _T32,
      _T33, _T34, _T35, _T36, _T37, _T38, _T39, _T40>& __other) const {
        return std::tie(acctbal, address, availqty, brand, clerk, comments, commitdate, container,
        custkey, d_size, discount, event, extendedprice, linenumber, linestatus, mfgr, mktsegment,
        name, nationkey, oid, orderdate, orderkey, orderpriority, orderstatus, partkey, phone,
        quantity, receiptdate, regionkey, retailprice, returnflag, schema, shipdate, shipinstruct,
        shipmode, shippriority, suppkey, supplycost, tax, totalprice,
        type2) != std::tie(__other.acctbal, __other.address, __other.availqty, __other.brand,
        __other.clerk, __other.comments, __other.commitdate, __other.container, __other.custkey,
        __other.d_size, __other.discount, __other.event, __other.extendedprice, __other.linenumber,
        __other.linestatus, __other.mfgr, __other.mktsegment, __other.name, __other.nationkey,
        __other.oid, __other.orderdate, __other.orderkey, __other.orderpriority,
        __other.orderstatus, __other.partkey, __other.phone, __other.quantity, __other.receiptdate,
        __other.regionkey, __other.retailprice, __other.returnflag, __other.schema,
        __other.shipdate, __other.shipinstruct, __other.shipmode, __other.shippriority,
        __other.suppkey, __other.supplycost, __other.tax, __other.totalprice, __other.type2);
      }
      bool operator<(const R_acctbal_address_availqty_brand_clerk_comments_commitdate_container_custkey_d_size_discount_event_extendedprice_linenumber_linestatus_mfgr_mktsegment_name_nationkey_oid_orderdate_orderkey_orderpriority_orderstatus_partkey_phone_quantity_receiptdate_regionkey_retailprice_returnflag_schema_shipdate_shipinstruct_shipmode_shippriority_suppkey_supplycost_tax_totalprice_type2<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17,
      _T18, _T19, _T20, _T21, _T22, _T23, _T24, _T25, _T26, _T27, _T28, _T29, _T30, _T31, _T32,
      _T33, _T34, _T35, _T36, _T37, _T38, _T39, _T40>& __other) const {
        return std::tie(acctbal, address, availqty, brand, clerk, comments, commitdate, container,
        custkey, d_size, discount, event, extendedprice, linenumber, linestatus, mfgr, mktsegment,
        name, nationkey, oid, orderdate, orderkey, orderpriority, orderstatus, partkey, phone,
        quantity, receiptdate, regionkey, retailprice, returnflag, schema, shipdate, shipinstruct,
        shipmode, shippriority, suppkey, supplycost, tax, totalprice,
        type2) < std::tie(__other.acctbal, __other.address, __other.availqty, __other.brand,
        __other.clerk, __other.comments, __other.commitdate, __other.container, __other.custkey,
        __other.d_size, __other.discount, __other.event, __other.extendedprice, __other.linenumber,
        __other.linestatus, __other.mfgr, __other.mktsegment, __other.name, __other.nationkey,
        __other.oid, __other.orderdate, __other.orderkey, __other.orderpriority,
        __other.orderstatus, __other.partkey, __other.phone, __other.quantity, __other.receiptdate,
        __other.regionkey, __other.retailprice, __other.returnflag, __other.schema,
        __other.shipdate, __other.shipinstruct, __other.shipmode, __other.shippriority,
        __other.suppkey, __other.supplycost, __other.tax, __other.totalprice, __other.type2);
      }
      bool operator>(const R_acctbal_address_availqty_brand_clerk_comments_commitdate_container_custkey_d_size_discount_event_extendedprice_linenumber_linestatus_mfgr_mktsegment_name_nationkey_oid_orderdate_orderkey_orderpriority_orderstatus_partkey_phone_quantity_receiptdate_regionkey_retailprice_returnflag_schema_shipdate_shipinstruct_shipmode_shippriority_suppkey_supplycost_tax_totalprice_type2<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17,
      _T18, _T19, _T20, _T21, _T22, _T23, _T24, _T25, _T26, _T27, _T28, _T29, _T30, _T31, _T32,
      _T33, _T34, _T35, _T36, _T37, _T38, _T39, _T40>& __other) const {
        return std::tie(acctbal, address, availqty, brand, clerk, comments, commitdate, container,
        custkey, d_size, discount, event, extendedprice, linenumber, linestatus, mfgr, mktsegment,
        name, nationkey, oid, orderdate, orderkey, orderpriority, orderstatus, partkey, phone,
        quantity, receiptdate, regionkey, retailprice, returnflag, schema, shipdate, shipinstruct,
        shipmode, shippriority, suppkey, supplycost, tax, totalprice,
        type2) > std::tie(__other.acctbal, __other.address, __other.availqty, __other.brand,
        __other.clerk, __other.comments, __other.commitdate, __other.container, __other.custkey,
        __other.d_size, __other.discount, __other.event, __other.extendedprice, __other.linenumber,
        __other.linestatus, __other.mfgr, __other.mktsegment, __other.name, __other.nationkey,
        __other.oid, __other.orderdate, __other.orderkey, __other.orderpriority,
        __other.orderstatus, __other.partkey, __other.phone, __other.quantity, __other.receiptdate,
        __other.regionkey, __other.retailprice, __other.returnflag, __other.schema,
        __other.shipdate, __other.shipinstruct, __other.shipmode, __other.shippriority,
        __other.suppkey, __other.supplycost, __other.tax, __other.totalprice, __other.type2);
      }
      template <class archive>
      void serialize(archive& _archive, const unsigned int _version)  {
        _archive & acctbal;
        _archive & address;
        _archive & availqty;
        _archive & brand;
        _archive & clerk;
        _archive & comments;
        _archive & commitdate;
        _archive & container;
        _archive & custkey;
        _archive & d_size;
        _archive & discount;
        _archive & event;
        _archive & extendedprice;
        _archive & linenumber;
        _archive & linestatus;
        _archive & mfgr;
        _archive & mktsegment;
        _archive & name;
        _archive & nationkey;
        _archive & oid;
        _archive & orderdate;
        _archive & orderkey;
        _archive & orderpriority;
        _archive & orderstatus;
        _archive & partkey;
        _archive & phone;
        _archive & quantity;
        _archive & receiptdate;
        _archive & regionkey;
        _archive & retailprice;
        _archive & returnflag;
        _archive & schema;
        _archive & shipdate;
        _archive & shipinstruct;
        _archive & shipmode;
        _archive & shippriority;
        _archive & suppkey;
        _archive & supplycost;
        _archive & tax;
        _archive & totalprice;
        _archive & type2;
      }
      _T0 acctbal;
      _T1 address;
      _T2 availqty;
      _T3 brand;
      _T4 clerk;
      _T5 comments;
      _T6 commitdate;
      _T7 container;
      _T8 custkey;
      _T9 d_size;
      _T10 discount;
      _T11 event;
      _T12 extendedprice;
      _T13 linenumber;
      _T14 linestatus;
      _T15 mfgr;
      _T16 mktsegment;
      _T17 name;
      _T18 nationkey;
      _T19 oid;
      _T20 orderdate;
      _T21 orderkey;
      _T22 orderpriority;
      _T23 orderstatus;
      _T24 partkey;
      _T25 phone;
      _T26 quantity;
      _T27 receiptdate;
      _T28 regionkey;
      _T29 retailprice;
      _T30 returnflag;
      _T31 schema;
      _T32 shipdate;
      _T33 shipinstruct;
      _T34 shipmode;
      _T35 shippriority;
      _T36 suppkey;
      _T37 supplycost;
      _T38 tax;
      _T39 totalprice;
      _T40 type2;
};
#endif
namespace K3 {
  template <class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7,
  class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15,
  class _T16, class _T17, class _T18, class _T19, class _T20, class _T21, class _T22, class _T23,
  class _T24, class _T25, class _T26, class _T27, class _T28, class _T29, class _T30, class _T31,
  class _T32, class _T33, class _T34, class _T35, class _T36, class _T37, class _T38, class _T39,
  class _T40>
  class patcher<R_acctbal_address_availqty_brand_clerk_comments_commitdate_container_custkey_d_size_discount_event_extendedprice_linenumber_linestatus_mfgr_mktsegment_name_nationkey_oid_orderdate_orderkey_orderpriority_orderstatus_partkey_phone_quantity_receiptdate_regionkey_retailprice_returnflag_schema_shipdate_shipinstruct_shipmode_shippriority_suppkey_supplycost_tax_totalprice_type2<_T0,
  _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18,
  _T19, _T20, _T21, _T22, _T23, _T24, _T25, _T26, _T27, _T28, _T29, _T30, _T31, _T32, _T33, _T34,
  _T35, _T36, _T37, _T38, _T39, _T40>> {
    public:
        static void patch(std::string _input,
        R_acctbal_address_availqty_brand_clerk_comments_commitdate_container_custkey_d_size_discount_event_extendedprice_linenumber_linestatus_mfgr_mktsegment_name_nationkey_oid_orderdate_orderkey_orderpriority_orderstatus_partkey_phone_quantity_receiptdate_regionkey_retailprice_returnflag_schema_shipdate_shipinstruct_shipmode_shippriority_suppkey_supplycost_tax_totalprice_type2<_T0,
        _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17,
        _T18, _T19, _T20, _T21, _T22, _T23, _T24, _T25, _T26, _T27, _T28, _T29, _T30, _T31, _T32,
        _T33, _T34, _T35, _T36, _T37, _T38, _T39, _T40>& _record)  {
          shallow<string::iterator> _shallow;
          qi::rule<string::iterator,
          qi::space_type> _acctbal = (qi::lit("acctbal") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.acctbal);
          })];
          qi::rule<string::iterator,
          qi::space_type> _address = (qi::lit("address") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.address);
          })];
          qi::rule<string::iterator,
          qi::space_type> _availqty = (qi::lit("availqty") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.availqty);
          })];
          qi::rule<string::iterator,
          qi::space_type> _brand = (qi::lit("brand") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.brand);
          })];
          qi::rule<string::iterator,
          qi::space_type> _clerk = (qi::lit("clerk") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.clerk);
          })];
          qi::rule<string::iterator,
          qi::space_type> _comments = (qi::lit("comments") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.comments);
          })];
          qi::rule<string::iterator,
          qi::space_type> _commitdate = (qi::lit("commitdate") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.commitdate);
          })];
          qi::rule<string::iterator,
          qi::space_type> _container = (qi::lit("container") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.container);
          })];
          qi::rule<string::iterator,
          qi::space_type> _custkey = (qi::lit("custkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.custkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _d_size = (qi::lit("d_size") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.d_size);
          })];
          qi::rule<string::iterator,
          qi::space_type> _discount = (qi::lit("discount") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.discount);
          })];
          qi::rule<string::iterator,
          qi::space_type> _event = (qi::lit("event") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.event);
          })];
          qi::rule<string::iterator,
          qi::space_type> _extendedprice = (qi::lit("extendedprice") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.extendedprice);
          })];
          qi::rule<string::iterator,
          qi::space_type> _linenumber = (qi::lit("linenumber") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.linenumber);
          })];
          qi::rule<string::iterator,
          qi::space_type> _linestatus = (qi::lit("linestatus") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.linestatus);
          })];
          qi::rule<string::iterator,
          qi::space_type> _mfgr = (qi::lit("mfgr") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.mfgr);
          })];
          qi::rule<string::iterator,
          qi::space_type> _mktsegment = (qi::lit("mktsegment") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.mktsegment);
          })];
          qi::rule<string::iterator,
          qi::space_type> _name = (qi::lit("name") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.name);
          })];
          qi::rule<string::iterator,
          qi::space_type> _nationkey = (qi::lit("nationkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.nationkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _oid = (qi::lit("oid") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.oid);
          })];
          qi::rule<string::iterator,
          qi::space_type> _orderdate = (qi::lit("orderdate") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.orderdate);
          })];
          qi::rule<string::iterator,
          qi::space_type> _orderkey = (qi::lit("orderkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.orderkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _orderpriority = (qi::lit("orderpriority") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.orderpriority);
          })];
          qi::rule<string::iterator,
          qi::space_type> _orderstatus = (qi::lit("orderstatus") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.orderstatus);
          })];
          qi::rule<string::iterator,
          qi::space_type> _partkey = (qi::lit("partkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.partkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _phone = (qi::lit("phone") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.phone);
          })];
          qi::rule<string::iterator,
          qi::space_type> _quantity = (qi::lit("quantity") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.quantity);
          })];
          qi::rule<string::iterator,
          qi::space_type> _receiptdate = (qi::lit("receiptdate") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.receiptdate);
          })];
          qi::rule<string::iterator,
          qi::space_type> _regionkey = (qi::lit("regionkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.regionkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _retailprice = (qi::lit("retailprice") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.retailprice);
          })];
          qi::rule<string::iterator,
          qi::space_type> _returnflag = (qi::lit("returnflag") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.returnflag);
          })];
          qi::rule<string::iterator,
          qi::space_type> _schema = (qi::lit("schema") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.schema);
          })];
          qi::rule<string::iterator,
          qi::space_type> _shipdate = (qi::lit("shipdate") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.shipdate);
          })];
          qi::rule<string::iterator,
          qi::space_type> _shipinstruct = (qi::lit("shipinstruct") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.shipinstruct);
          })];
          qi::rule<string::iterator,
          qi::space_type> _shipmode = (qi::lit("shipmode") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.shipmode);
          })];
          qi::rule<string::iterator,
          qi::space_type> _shippriority = (qi::lit("shippriority") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.shippriority);
          })];
          qi::rule<string::iterator,
          qi::space_type> _suppkey = (qi::lit("suppkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.suppkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _supplycost = (qi::lit("supplycost") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.supplycost);
          })];
          qi::rule<string::iterator,
          qi::space_type> _tax = (qi::lit("tax") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.tax);
          })];
          qi::rule<string::iterator,
          qi::space_type> _totalprice = (qi::lit("totalprice") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.totalprice);
          })];
          qi::rule<string::iterator,
          qi::space_type> _type2 = (qi::lit("type2") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.type2);
          })];
          qi::rule<string::iterator,
          qi::space_type> _field = _acctbal | _address | _availqty | _brand | _clerk | _comments | _commitdate | _container | _custkey | _d_size | _discount | _event | _extendedprice | _linenumber | _linestatus | _mfgr | _mktsegment | _name | _nationkey | _oid | _orderdate | _orderkey | _orderpriority | _orderstatus | _partkey | _phone | _quantity | _receiptdate | _regionkey | _retailprice | _returnflag | _schema | _shipdate | _shipinstruct | _shipmode | _shippriority | _suppkey | _supplycost | _tax | _totalprice | _type2;
          qi::rule<string::iterator, qi::space_type> _parser = ('{') >> _field % (',') >> ('}');
          qi::phrase_parse(std::begin(_input), std::end(_input), _parser, qi::space);
        }
  };
}
#ifndef K3_R_acctbal_address_availqty_brand_clerk_comments_commitdate_container_custkey_d_size_discount_event_extendedprice_linenumber_linestatus_mfgr_mktsegment_name_nationkey_oid_orderdate_orderkey_orderpriority_orderstatus_partkey_phone_quantity_receiptdate_regionkey_retailprice_returnflag_schema_shipdate_shipinstruct_shipmode_shippriority_suppkey_supplycost_tax_totalprice_type2
#define K3_R_acctbal_address_availqty_brand_clerk_comments_commitdate_container_custkey_d_size_discount_event_extendedprice_linenumber_linestatus_mfgr_mktsegment_name_nationkey_oid_orderdate_orderkey_orderpriority_orderstatus_partkey_phone_quantity_receiptdate_regionkey_retailprice_returnflag_schema_shipdate_shipinstruct_shipmode_shippriority_suppkey_supplycost_tax_totalprice_type2
template <class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7,
class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15,
class _T16, class _T17, class _T18, class _T19, class _T20, class _T21, class _T22, class _T23,
class _T24, class _T25, class _T26, class _T27, class _T28, class _T29, class _T30, class _T31,
class _T32, class _T33, class _T34, class _T35, class _T36, class _T37, class _T38, class _T39,
class _T40>
std::size_t hash_value(const R_acctbal_address_availqty_brand_clerk_comments_commitdate_container_custkey_d_size_discount_event_extendedprice_linenumber_linestatus_mfgr_mktsegment_name_nationkey_oid_orderdate_orderkey_orderpriority_orderstatus_partkey_phone_quantity_receiptdate_regionkey_retailprice_returnflag_schema_shipdate_shipinstruct_shipmode_shippriority_suppkey_supplycost_tax_totalprice_type2<_T0,
_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18,
_T19, _T20, _T21, _T22, _T23, _T24, _T25, _T26, _T27, _T28, _T29, _T30, _T31, _T32, _T33, _T34,
_T35, _T36, _T37, _T38, _T39, _T40>& r)  {
  boost::hash<std::tuple<_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13,
  _T14, _T15, _T16, _T17, _T18, _T19, _T20, _T21, _T22, _T23, _T24, _T25, _T26, _T27, _T28, _T29,
  _T30, _T31, _T32, _T33, _T34, _T35, _T36, _T37, _T38, _T39, _T40>> hasher;
  return hasher(std::tie(r.acctbal, r.address, r.availqty, r.brand, r.clerk, r.comments,
  r.commitdate, r.container, r.custkey, r.d_size, r.discount, r.event, r.extendedprice,
  r.linenumber, r.linestatus, r.mfgr, r.mktsegment, r.name, r.nationkey, r.oid, r.orderdate,
  r.orderkey, r.orderpriority, r.orderstatus, r.partkey, r.phone, r.quantity, r.receiptdate,
  r.regionkey, r.retailprice, r.returnflag, r.schema, r.shipdate, r.shipinstruct, r.shipmode,
  r.shippriority, r.suppkey, r.supplycost, r.tax, r.totalprice, r.type2));
}
#endif
#ifndef K3_R_addr_hash_value
#define K3_R_addr_hash_value
template <class _T0>
class R_addr {
  public:
      R_addr(): addr()  {}
      R_addr(const _T0& _addr): addr(_addr)  {}
      R_addr(_T0&& _addr): addr(std::move(_addr))  {}
      bool operator==(const R_addr<_T0>& __other) const {
        return addr == (__other.addr);
      }
      bool operator!=(const R_addr<_T0>& __other) const {
        return std::tie(addr) != std::tie(__other.addr);
      }
      bool operator<(const R_addr<_T0>& __other) const {
        return std::tie(addr) < std::tie(__other.addr);
      }
      bool operator>(const R_addr<_T0>& __other) const {
        return std::tie(addr) > std::tie(__other.addr);
      }
      template <class archive>
      void serialize(archive& _archive, const unsigned int _version)  {
        _archive & addr;
      }
      _T0 addr;
};
#endif
namespace K3 {
  template <class _T0>
  class patcher<R_addr<_T0>> {
    public:
        static void patch(std::string _input, R_addr<_T0>& _record)  {
          shallow<string::iterator> _shallow;
          qi::rule<string::iterator,
          qi::space_type> _addr = (qi::lit("addr") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.addr);
          })];
          qi::rule<string::iterator, qi::space_type> _field = _addr;
          qi::rule<string::iterator, qi::space_type> _parser = ('{') >> _field % (',') >> ('}');
          qi::phrase_parse(std::begin(_input), std::end(_input), _parser, qi::space);
        }
  };
}
#ifndef K3_R_addr
#define K3_R_addr
template <class _T0>
std::size_t hash_value(const R_addr<_T0>& r)  {
  boost::hash<std::tuple<_T0>> hasher;
  return hasher(std::tie(r.addr));
}
#endif
#ifndef K3_R_arg_hash_value
#define K3_R_arg_hash_value
template <class _T0>
class R_arg {
  public:
      R_arg(): arg()  {}
      R_arg(const _T0& _arg): arg(_arg)  {}
      R_arg(_T0&& _arg): arg(std::move(_arg))  {}
      bool operator==(const R_arg<_T0>& __other) const {
        return arg == (__other.arg);
      }
      bool operator!=(const R_arg<_T0>& __other) const {
        return std::tie(arg) != std::tie(__other.arg);
      }
      bool operator<(const R_arg<_T0>& __other) const {
        return std::tie(arg) < std::tie(__other.arg);
      }
      bool operator>(const R_arg<_T0>& __other) const {
        return std::tie(arg) > std::tie(__other.arg);
      }
      template <class archive>
      void serialize(archive& _archive, const unsigned int _version)  {
        _archive & arg;
      }
      _T0 arg;
};
#endif
namespace K3 {
  template <class _T0>
  class patcher<R_arg<_T0>> {
    public:
        static void patch(std::string _input, R_arg<_T0>& _record)  {
          shallow<string::iterator> _shallow;
          qi::rule<string::iterator,
          qi::space_type> _arg = (qi::lit("arg") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.arg);
          })];
          qi::rule<string::iterator, qi::space_type> _field = _arg;
          qi::rule<string::iterator, qi::space_type> _parser = ('{') >> _field % (',') >> ('}');
          qi::phrase_parse(std::begin(_input), std::end(_input), _parser, qi::space);
        }
  };
}
#ifndef K3_R_arg
#define K3_R_arg
template <class _T0>
std::size_t hash_value(const R_arg<_T0>& r)  {
  boost::hash<std::tuple<_T0>> hasher;
  return hasher(std::tie(r.arg));
}
#endif
#ifndef K3_R_c_acctbal_c_address_c_comments_c_custkey_c_mktsegment_c_name_c_nationkey_c_phone_hash_value
#define K3_R_c_acctbal_c_address_c_comments_c_custkey_c_mktsegment_c_name_c_nationkey_c_phone_hash_value
template <class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7>
class R_c_acctbal_c_address_c_comments_c_custkey_c_mktsegment_c_name_c_nationkey_c_phone {
  public:
      R_c_acctbal_c_address_c_comments_c_custkey_c_mktsegment_c_name_c_nationkey_c_phone(): c_acctbal(),
      c_address(), c_comments(), c_custkey(), c_mktsegment(), c_name(), c_nationkey(), c_phone()  {}
      template <class __T0, class __T1, class __T2, class __T3, class __T4, class __T5, class __T6,
      class __T7>
      R_c_acctbal_c_address_c_comments_c_custkey_c_mktsegment_c_name_c_nationkey_c_phone(__T0&& _c_acctbal,
      __T1&& _c_address, __T2&& _c_comments, __T3&& _c_custkey, __T4&& _c_mktsegment,
      __T5&& _c_name, __T6&& _c_nationkey,
      __T7&& _c_phone): c_acctbal(std::forward<__T0>(_c_acctbal)),
      c_address(std::forward<__T1>(_c_address)), c_comments(std::forward<__T2>(_c_comments)),
      c_custkey(std::forward<__T3>(_c_custkey)), c_mktsegment(std::forward<__T4>(_c_mktsegment)),
      c_name(std::forward<__T5>(_c_name)), c_nationkey(std::forward<__T6>(_c_nationkey)),
      c_phone(std::forward<__T7>(_c_phone))  {}
      bool operator==(const R_c_acctbal_c_address_c_comments_c_custkey_c_mktsegment_c_name_c_nationkey_c_phone<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6, _T7>& __other) const {
        return c_acctbal == (__other.c_acctbal) && c_address == (__other.c_address) && c_comments == (__other.c_comments) && c_custkey == (__other.c_custkey) && c_mktsegment == (__other.c_mktsegment) && c_name == (__other.c_name) && c_nationkey == (__other.c_nationkey) && c_phone == (__other.c_phone);
      }
      bool operator!=(const R_c_acctbal_c_address_c_comments_c_custkey_c_mktsegment_c_name_c_nationkey_c_phone<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6, _T7>& __other) const {
        return std::tie(c_acctbal, c_address, c_comments, c_custkey, c_mktsegment, c_name,
        c_nationkey, c_phone) != std::tie(__other.c_acctbal, __other.c_address, __other.c_comments,
        __other.c_custkey, __other.c_mktsegment, __other.c_name, __other.c_nationkey,
        __other.c_phone);
      }
      bool operator<(const R_c_acctbal_c_address_c_comments_c_custkey_c_mktsegment_c_name_c_nationkey_c_phone<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6, _T7>& __other) const {
        return std::tie(c_acctbal, c_address, c_comments, c_custkey, c_mktsegment, c_name,
        c_nationkey, c_phone) < std::tie(__other.c_acctbal, __other.c_address, __other.c_comments,
        __other.c_custkey, __other.c_mktsegment, __other.c_name, __other.c_nationkey,
        __other.c_phone);
      }
      bool operator>(const R_c_acctbal_c_address_c_comments_c_custkey_c_mktsegment_c_name_c_nationkey_c_phone<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6, _T7>& __other) const {
        return std::tie(c_acctbal, c_address, c_comments, c_custkey, c_mktsegment, c_name,
        c_nationkey, c_phone) > std::tie(__other.c_acctbal, __other.c_address, __other.c_comments,
        __other.c_custkey, __other.c_mktsegment, __other.c_name, __other.c_nationkey,
        __other.c_phone);
      }
      template <class archive>
      void serialize(archive& _archive, const unsigned int _version)  {
        _archive & c_acctbal;
        _archive & c_address;
        _archive & c_comments;
        _archive & c_custkey;
        _archive & c_mktsegment;
        _archive & c_name;
        _archive & c_nationkey;
        _archive & c_phone;
      }
      _T0 c_acctbal;
      _T1 c_address;
      _T2 c_comments;
      _T3 c_custkey;
      _T4 c_mktsegment;
      _T5 c_name;
      _T6 c_nationkey;
      _T7 c_phone;
};
#endif
namespace K3 {
  template <class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7>
  class patcher<R_c_acctbal_c_address_c_comments_c_custkey_c_mktsegment_c_name_c_nationkey_c_phone<_T0,
  _T1, _T2, _T3, _T4, _T5, _T6, _T7>> {
    public:
        static void patch(std::string _input,
        R_c_acctbal_c_address_c_comments_c_custkey_c_mktsegment_c_name_c_nationkey_c_phone<_T0, _T1,
        _T2, _T3, _T4, _T5, _T6, _T7>& _record)  {
          shallow<string::iterator> _shallow;
          qi::rule<string::iterator,
          qi::space_type> _c_acctbal = (qi::lit("c_acctbal") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.c_acctbal);
          })];
          qi::rule<string::iterator,
          qi::space_type> _c_address = (qi::lit("c_address") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.c_address);
          })];
          qi::rule<string::iterator,
          qi::space_type> _c_comments = (qi::lit("c_comments") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.c_comments);
          })];
          qi::rule<string::iterator,
          qi::space_type> _c_custkey = (qi::lit("c_custkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.c_custkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _c_mktsegment = (qi::lit("c_mktsegment") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.c_mktsegment);
          })];
          qi::rule<string::iterator,
          qi::space_type> _c_name = (qi::lit("c_name") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.c_name);
          })];
          qi::rule<string::iterator,
          qi::space_type> _c_nationkey = (qi::lit("c_nationkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.c_nationkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _c_phone = (qi::lit("c_phone") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.c_phone);
          })];
          qi::rule<string::iterator,
          qi::space_type> _field = _c_acctbal | _c_address | _c_comments | _c_custkey | _c_mktsegment | _c_name | _c_nationkey | _c_phone;
          qi::rule<string::iterator, qi::space_type> _parser = ('{') >> _field % (',') >> ('}');
          qi::phrase_parse(std::begin(_input), std::end(_input), _parser, qi::space);
        }
  };
}
#ifndef K3_R_c_acctbal_c_address_c_comments_c_custkey_c_mktsegment_c_name_c_nationkey_c_phone
#define K3_R_c_acctbal_c_address_c_comments_c_custkey_c_mktsegment_c_name_c_nationkey_c_phone
template <class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7>
std::size_t hash_value(const R_c_acctbal_c_address_c_comments_c_custkey_c_mktsegment_c_name_c_nationkey_c_phone<_T0,
_T1, _T2, _T3, _T4, _T5, _T6, _T7>& r)  {
  boost::hash<std::tuple<_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7>> hasher;
  return hasher(std::tie(r.c_acctbal, r.c_address, r.c_comments, r.c_custkey, r.c_mktsegment,
  r.c_name, r.c_nationkey, r.c_phone));
}
#endif
#ifndef K3_R_ck_nm_od_ok_tp_hash_value
#define K3_R_ck_nm_od_ok_tp_hash_value
template <class _T0, class _T1, class _T2, class _T3, class _T4>
class R_ck_nm_od_ok_tp {
  public:
      R_ck_nm_od_ok_tp(): ck(), nm(), od(), ok(), tp()  {}
      template <class __T0, class __T1, class __T2, class __T3, class __T4>
      R_ck_nm_od_ok_tp(__T0&& _ck, __T1&& _nm, __T2&& _od, __T3&& _ok,
      __T4&& _tp): ck(std::forward<__T0>(_ck)), nm(std::forward<__T1>(_nm)),
      od(std::forward<__T2>(_od)), ok(std::forward<__T3>(_ok)), tp(std::forward<__T4>(_tp))  {}
      bool operator==(const R_ck_nm_od_ok_tp<_T0, _T1, _T2, _T3, _T4>& __other) const {
        return ck == (__other.ck) && nm == (__other.nm) && od == (__other.od) && ok == (__other.ok) && tp == (__other.tp);
      }
      bool operator!=(const R_ck_nm_od_ok_tp<_T0, _T1, _T2, _T3, _T4>& __other) const {
        return std::tie(ck, nm, od, ok, tp) != std::tie(__other.ck, __other.nm, __other.od,
        __other.ok, __other.tp);
      }
      bool operator<(const R_ck_nm_od_ok_tp<_T0, _T1, _T2, _T3, _T4>& __other) const {
        return std::tie(ck, nm, od, ok, tp) < std::tie(__other.ck, __other.nm, __other.od,
        __other.ok, __other.tp);
      }
      bool operator>(const R_ck_nm_od_ok_tp<_T0, _T1, _T2, _T3, _T4>& __other) const {
        return std::tie(ck, nm, od, ok, tp) > std::tie(__other.ck, __other.nm, __other.od,
        __other.ok, __other.tp);
      }
      template <class archive>
      void serialize(archive& _archive, const unsigned int _version)  {
        _archive & ck;
        _archive & nm;
        _archive & od;
        _archive & ok;
        _archive & tp;
      }
      _T0 ck;
      _T1 nm;
      _T2 od;
      _T3 ok;
      _T4 tp;
};
#endif
namespace K3 {
  template <class _T0, class _T1, class _T2, class _T3, class _T4>
  class patcher<R_ck_nm_od_ok_tp<_T0, _T1, _T2, _T3, _T4>> {
    public:
        static void patch(std::string _input, R_ck_nm_od_ok_tp<_T0, _T1, _T2, _T3, _T4>& _record)  {
          shallow<string::iterator> _shallow;
          qi::rule<string::iterator,
          qi::space_type> _ck = (qi::lit("ck") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.ck);
          })];
          qi::rule<string::iterator,
          qi::space_type> _nm = (qi::lit("nm") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.nm);
          })];
          qi::rule<string::iterator,
          qi::space_type> _od = (qi::lit("od") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.od);
          })];
          qi::rule<string::iterator,
          qi::space_type> _ok = (qi::lit("ok") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.ok);
          })];
          qi::rule<string::iterator,
          qi::space_type> _tp = (qi::lit("tp") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.tp);
          })];
          qi::rule<string::iterator, qi::space_type> _field = _ck | _nm | _od | _ok | _tp;
          qi::rule<string::iterator, qi::space_type> _parser = ('{') >> _field % (',') >> ('}');
          qi::phrase_parse(std::begin(_input), std::end(_input), _parser, qi::space);
        }
  };
}
#ifndef K3_R_ck_nm_od_ok_tp
#define K3_R_ck_nm_od_ok_tp
template <class _T0, class _T1, class _T2, class _T3, class _T4>
std::size_t hash_value(const R_ck_nm_od_ok_tp<_T0, _T1, _T2, _T3, _T4>& r)  {
  boost::hash<std::tuple<_T0, _T1, _T2, _T3, _T4>> hasher;
  return hasher(std::tie(r.ck, r.nm, r.od, r.ok, r.tp));
}
#endif
#ifndef K3_R_key_value_hash_value
#define K3_R_key_value_hash_value
template <class _T0, class _T1>
class R_key_value {
  public:
      R_key_value(): key(), value()  {}
      template <class __T0, class __T1>
      R_key_value(__T0&& _key, __T1&& _value): key(std::forward<__T0>(_key)),
      value(std::forward<__T1>(_value))  {}
      bool operator==(const R_key_value<_T0, _T1>& __other) const {
        return key == (__other.key) && value == (__other.value);
      }
      bool operator!=(const R_key_value<_T0, _T1>& __other) const {
        return std::tie(key, value) != std::tie(__other.key, __other.value);
      }
      bool operator<(const R_key_value<_T0, _T1>& __other) const {
        return std::tie(key, value) < std::tie(__other.key, __other.value);
      }
      bool operator>(const R_key_value<_T0, _T1>& __other) const {
        return std::tie(key, value) > std::tie(__other.key, __other.value);
      }
      template <class archive>
      void serialize(archive& _archive, const unsigned int _version)  {
        _archive & key;
        _archive & value;
      }
      _T0 key;
      _T1 value;
};
#endif
namespace K3 {
  template <class _T0, class _T1>
  class patcher<R_key_value<_T0, _T1>> {
    public:
        static void patch(std::string _input, R_key_value<_T0, _T1>& _record)  {
          shallow<string::iterator> _shallow;
          qi::rule<string::iterator,
          qi::space_type> _key = (qi::lit("key") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.key);
          })];
          qi::rule<string::iterator,
          qi::space_type> _value = (qi::lit("value") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.value);
          })];
          qi::rule<string::iterator, qi::space_type> _field = _key | _value;
          qi::rule<string::iterator, qi::space_type> _parser = ('{') >> _field % (',') >> ('}');
          qi::phrase_parse(std::begin(_input), std::end(_input), _parser, qi::space);
        }
  };
}
#ifndef K3_R_key_value
#define K3_R_key_value
template <class _T0, class _T1>
std::size_t hash_value(const R_key_value<_T0, _T1>& r)  {
  boost::hash<std::tuple<_T0, _T1>> hasher;
  return hasher(std::tie(r.key, r.value));
}
#endif
#ifndef K3_R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax_hash_value
#define K3_R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax_hash_value
template <class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7,
class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15>
class R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax {
  public:
      R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax(): l_comments(),
      l_commitdate(), l_discount(), l_extendedprice(), l_linenumber(), l_linestatus(), l_orderkey(),
      l_partkey(), l_quantity(), l_receiptdate(), l_returnflag(), l_shipdate(), l_shipinstruct(),
      l_shipmode(), l_suppkey(), l_tax()  {}
      template <class __T0, class __T1, class __T2, class __T3, class __T4, class __T5, class __T6,
      class __T7, class __T8, class __T9, class __T10, class __T11, class __T12, class __T13,
      class __T14, class __T15>
      R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax(__T0&& _l_comments,
      __T1&& _l_commitdate, __T2&& _l_discount, __T3&& _l_extendedprice, __T4&& _l_linenumber,
      __T5&& _l_linestatus, __T6&& _l_orderkey, __T7&& _l_partkey, __T8&& _l_quantity,
      __T9&& _l_receiptdate, __T10&& _l_returnflag, __T11&& _l_shipdate, __T12&& _l_shipinstruct,
      __T13&& _l_shipmode, __T14&& _l_suppkey,
      __T15&& _l_tax): l_comments(std::forward<__T0>(_l_comments)),
      l_commitdate(std::forward<__T1>(_l_commitdate)), l_discount(std::forward<__T2>(_l_discount)),
      l_extendedprice(std::forward<__T3>(_l_extendedprice)),
      l_linenumber(std::forward<__T4>(_l_linenumber)),
      l_linestatus(std::forward<__T5>(_l_linestatus)), l_orderkey(std::forward<__T6>(_l_orderkey)),
      l_partkey(std::forward<__T7>(_l_partkey)), l_quantity(std::forward<__T8>(_l_quantity)),
      l_receiptdate(std::forward<__T9>(_l_receiptdate)),
      l_returnflag(std::forward<__T10>(_l_returnflag)),
      l_shipdate(std::forward<__T11>(_l_shipdate)),
      l_shipinstruct(std::forward<__T12>(_l_shipinstruct)),
      l_shipmode(std::forward<__T13>(_l_shipmode)), l_suppkey(std::forward<__T14>(_l_suppkey)),
      l_tax(std::forward<__T15>(_l_tax))  {}
      bool operator==(const R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14,
      _T15>& __other) const {
        return l_comments == (__other.l_comments) && l_commitdate == (__other.l_commitdate) && l_discount == (__other.l_discount) && l_extendedprice == (__other.l_extendedprice) && l_linenumber == (__other.l_linenumber) && l_linestatus == (__other.l_linestatus) && l_orderkey == (__other.l_orderkey) && l_partkey == (__other.l_partkey) && l_quantity == (__other.l_quantity) && l_receiptdate == (__other.l_receiptdate) && l_returnflag == (__other.l_returnflag) && l_shipdate == (__other.l_shipdate) && l_shipinstruct == (__other.l_shipinstruct) && l_shipmode == (__other.l_shipmode) && l_suppkey == (__other.l_suppkey) && l_tax == (__other.l_tax);
      }
      bool operator!=(const R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14,
      _T15>& __other) const {
        return std::tie(l_comments, l_commitdate, l_discount, l_extendedprice, l_linenumber,
        l_linestatus, l_orderkey, l_partkey, l_quantity, l_receiptdate, l_returnflag, l_shipdate,
        l_shipinstruct, l_shipmode, l_suppkey, l_tax) != std::tie(__other.l_comments,
        __other.l_commitdate, __other.l_discount, __other.l_extendedprice, __other.l_linenumber,
        __other.l_linestatus, __other.l_orderkey, __other.l_partkey, __other.l_quantity,
        __other.l_receiptdate, __other.l_returnflag, __other.l_shipdate, __other.l_shipinstruct,
        __other.l_shipmode, __other.l_suppkey, __other.l_tax);
      }
      bool operator<(const R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14,
      _T15>& __other) const {
        return std::tie(l_comments, l_commitdate, l_discount, l_extendedprice, l_linenumber,
        l_linestatus, l_orderkey, l_partkey, l_quantity, l_receiptdate, l_returnflag, l_shipdate,
        l_shipinstruct, l_shipmode, l_suppkey, l_tax) < std::tie(__other.l_comments,
        __other.l_commitdate, __other.l_discount, __other.l_extendedprice, __other.l_linenumber,
        __other.l_linestatus, __other.l_orderkey, __other.l_partkey, __other.l_quantity,
        __other.l_receiptdate, __other.l_returnflag, __other.l_shipdate, __other.l_shipinstruct,
        __other.l_shipmode, __other.l_suppkey, __other.l_tax);
      }
      bool operator>(const R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14,
      _T15>& __other) const {
        return std::tie(l_comments, l_commitdate, l_discount, l_extendedprice, l_linenumber,
        l_linestatus, l_orderkey, l_partkey, l_quantity, l_receiptdate, l_returnflag, l_shipdate,
        l_shipinstruct, l_shipmode, l_suppkey, l_tax) > std::tie(__other.l_comments,
        __other.l_commitdate, __other.l_discount, __other.l_extendedprice, __other.l_linenumber,
        __other.l_linestatus, __other.l_orderkey, __other.l_partkey, __other.l_quantity,
        __other.l_receiptdate, __other.l_returnflag, __other.l_shipdate, __other.l_shipinstruct,
        __other.l_shipmode, __other.l_suppkey, __other.l_tax);
      }
      template <class archive>
      void serialize(archive& _archive, const unsigned int _version)  {
        _archive & l_comments;
        _archive & l_commitdate;
        _archive & l_discount;
        _archive & l_extendedprice;
        _archive & l_linenumber;
        _archive & l_linestatus;
        _archive & l_orderkey;
        _archive & l_partkey;
        _archive & l_quantity;
        _archive & l_receiptdate;
        _archive & l_returnflag;
        _archive & l_shipdate;
        _archive & l_shipinstruct;
        _archive & l_shipmode;
        _archive & l_suppkey;
        _archive & l_tax;
      }
      _T0 l_comments;
      _T1 l_commitdate;
      _T2 l_discount;
      _T3 l_extendedprice;
      _T4 l_linenumber;
      _T5 l_linestatus;
      _T6 l_orderkey;
      _T7 l_partkey;
      _T8 l_quantity;
      _T9 l_receiptdate;
      _T10 l_returnflag;
      _T11 l_shipdate;
      _T12 l_shipinstruct;
      _T13 l_shipmode;
      _T14 l_suppkey;
      _T15 l_tax;
};
#endif
namespace K3 {
  template <class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7,
  class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15>
  class patcher<R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax<_T0,
  _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15>> {
    public:
        static void patch(std::string _input,
        R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax<_T0,
        _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14,
        _T15>& _record)  {
          shallow<string::iterator> _shallow;
          qi::rule<string::iterator,
          qi::space_type> _l_comments = (qi::lit("l_comments") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.l_comments);
          })];
          qi::rule<string::iterator,
          qi::space_type> _l_commitdate = (qi::lit("l_commitdate") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.l_commitdate);
          })];
          qi::rule<string::iterator,
          qi::space_type> _l_discount = (qi::lit("l_discount") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.l_discount);
          })];
          qi::rule<string::iterator,
          qi::space_type> _l_extendedprice = (qi::lit("l_extendedprice") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.l_extendedprice);
          })];
          qi::rule<string::iterator,
          qi::space_type> _l_linenumber = (qi::lit("l_linenumber") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.l_linenumber);
          })];
          qi::rule<string::iterator,
          qi::space_type> _l_linestatus = (qi::lit("l_linestatus") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.l_linestatus);
          })];
          qi::rule<string::iterator,
          qi::space_type> _l_orderkey = (qi::lit("l_orderkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.l_orderkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _l_partkey = (qi::lit("l_partkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.l_partkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _l_quantity = (qi::lit("l_quantity") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.l_quantity);
          })];
          qi::rule<string::iterator,
          qi::space_type> _l_receiptdate = (qi::lit("l_receiptdate") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.l_receiptdate);
          })];
          qi::rule<string::iterator,
          qi::space_type> _l_returnflag = (qi::lit("l_returnflag") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.l_returnflag);
          })];
          qi::rule<string::iterator,
          qi::space_type> _l_shipdate = (qi::lit("l_shipdate") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.l_shipdate);
          })];
          qi::rule<string::iterator,
          qi::space_type> _l_shipinstruct = (qi::lit("l_shipinstruct") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.l_shipinstruct);
          })];
          qi::rule<string::iterator,
          qi::space_type> _l_shipmode = (qi::lit("l_shipmode") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.l_shipmode);
          })];
          qi::rule<string::iterator,
          qi::space_type> _l_suppkey = (qi::lit("l_suppkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.l_suppkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _l_tax = (qi::lit("l_tax") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.l_tax);
          })];
          qi::rule<string::iterator,
          qi::space_type> _field = _l_comments | _l_commitdate | _l_discount | _l_extendedprice | _l_linenumber | _l_linestatus | _l_orderkey | _l_partkey | _l_quantity | _l_receiptdate | _l_returnflag | _l_shipdate | _l_shipinstruct | _l_shipmode | _l_suppkey | _l_tax;
          qi::rule<string::iterator, qi::space_type> _parser = ('{') >> _field % (',') >> ('}');
          qi::phrase_parse(std::begin(_input), std::end(_input), _parser, qi::space);
        }
  };
}
#ifndef K3_R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax
#define K3_R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax
template <class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7,
class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15>
std::size_t hash_value(const R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax<_T0,
_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15>& r)  {
  boost::hash<std::tuple<_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13,
  _T14, _T15>> hasher;
  return hasher(std::tie(r.l_comments, r.l_commitdate, r.l_discount, r.l_extendedprice,
  r.l_linenumber, r.l_linestatus, r.l_orderkey, r.l_partkey, r.l_quantity, r.l_receiptdate,
  r.l_returnflag, r.l_shipdate, r.l_shipinstruct, r.l_shipmode, r.l_suppkey, r.l_tax));
}
#endif
#ifndef K3_R_n_comments_n_name_n_nationkey_n_regionkey_hash_value
#define K3_R_n_comments_n_name_n_nationkey_n_regionkey_hash_value
template <class _T0, class _T1, class _T2, class _T3>
class R_n_comments_n_name_n_nationkey_n_regionkey {
  public:
      R_n_comments_n_name_n_nationkey_n_regionkey(): n_comments(), n_name(), n_nationkey(),
      n_regionkey()  {}
      template <class __T0, class __T1, class __T2, class __T3>
      R_n_comments_n_name_n_nationkey_n_regionkey(__T0&& _n_comments, __T1&& _n_name,
      __T2&& _n_nationkey, __T3&& _n_regionkey): n_comments(std::forward<__T0>(_n_comments)),
      n_name(std::forward<__T1>(_n_name)), n_nationkey(std::forward<__T2>(_n_nationkey)),
      n_regionkey(std::forward<__T3>(_n_regionkey))  {}
      bool operator==(const R_n_comments_n_name_n_nationkey_n_regionkey<_T0, _T1, _T2,
      _T3>& __other) const {
        return n_comments == (__other.n_comments) && n_name == (__other.n_name) && n_nationkey == (__other.n_nationkey) && n_regionkey == (__other.n_regionkey);
      }
      bool operator!=(const R_n_comments_n_name_n_nationkey_n_regionkey<_T0, _T1, _T2,
      _T3>& __other) const {
        return std::tie(n_comments, n_name, n_nationkey,
        n_regionkey) != std::tie(__other.n_comments, __other.n_name, __other.n_nationkey,
        __other.n_regionkey);
      }
      bool operator<(const R_n_comments_n_name_n_nationkey_n_regionkey<_T0, _T1, _T2,
      _T3>& __other) const {
        return std::tie(n_comments, n_name, n_nationkey, n_regionkey) < std::tie(__other.n_comments,
        __other.n_name, __other.n_nationkey, __other.n_regionkey);
      }
      bool operator>(const R_n_comments_n_name_n_nationkey_n_regionkey<_T0, _T1, _T2,
      _T3>& __other) const {
        return std::tie(n_comments, n_name, n_nationkey, n_regionkey) > std::tie(__other.n_comments,
        __other.n_name, __other.n_nationkey, __other.n_regionkey);
      }
      template <class archive>
      void serialize(archive& _archive, const unsigned int _version)  {
        _archive & n_comments;
        _archive & n_name;
        _archive & n_nationkey;
        _archive & n_regionkey;
      }
      _T0 n_comments;
      _T1 n_name;
      _T2 n_nationkey;
      _T3 n_regionkey;
};
#endif
namespace K3 {
  template <class _T0, class _T1, class _T2, class _T3>
  class patcher<R_n_comments_n_name_n_nationkey_n_regionkey<_T0, _T1, _T2, _T3>> {
    public:
        static void patch(std::string _input, R_n_comments_n_name_n_nationkey_n_regionkey<_T0, _T1,
        _T2, _T3>& _record)  {
          shallow<string::iterator> _shallow;
          qi::rule<string::iterator,
          qi::space_type> _n_comments = (qi::lit("n_comments") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.n_comments);
          })];
          qi::rule<string::iterator,
          qi::space_type> _n_name = (qi::lit("n_name") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.n_name);
          })];
          qi::rule<string::iterator,
          qi::space_type> _n_nationkey = (qi::lit("n_nationkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.n_nationkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _n_regionkey = (qi::lit("n_regionkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.n_regionkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _field = _n_comments | _n_name | _n_nationkey | _n_regionkey;
          qi::rule<string::iterator, qi::space_type> _parser = ('{') >> _field % (',') >> ('}');
          qi::phrase_parse(std::begin(_input), std::end(_input), _parser, qi::space);
        }
  };
}
#ifndef K3_R_n_comments_n_name_n_nationkey_n_regionkey
#define K3_R_n_comments_n_name_n_nationkey_n_regionkey
template <class _T0, class _T1, class _T2, class _T3>
std::size_t hash_value(const R_n_comments_n_name_n_nationkey_n_regionkey<_T0, _T1, _T2, _T3>& r)  {
  boost::hash<std::tuple<_T0, _T1, _T2, _T3>> hasher;
  return hasher(std::tie(r.n_comments, r.n_name, r.n_nationkey, r.n_regionkey));
}
#endif
#ifndef K3_R_o_clerk_o_comments_o_custkey_o_orderdate_o_orderkey_o_orderpriority_o_orderstatus_o_shippriority_o_totalprice_hash_value
#define K3_R_o_clerk_o_comments_o_custkey_o_orderdate_o_orderkey_o_orderpriority_o_orderstatus_o_shippriority_o_totalprice_hash_value
template <class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7,
class _T8>
class R_o_clerk_o_comments_o_custkey_o_orderdate_o_orderkey_o_orderpriority_o_orderstatus_o_shippriority_o_totalprice {
  public:
      R_o_clerk_o_comments_o_custkey_o_orderdate_o_orderkey_o_orderpriority_o_orderstatus_o_shippriority_o_totalprice(): o_clerk(),
      o_comments(), o_custkey(), o_orderdate(), o_orderkey(), o_orderpriority(), o_orderstatus(),
      o_shippriority(), o_totalprice()  {}
      template <class __T0, class __T1, class __T2, class __T3, class __T4, class __T5, class __T6,
      class __T7, class __T8>
      R_o_clerk_o_comments_o_custkey_o_orderdate_o_orderkey_o_orderpriority_o_orderstatus_o_shippriority_o_totalprice(__T0&& _o_clerk,
      __T1&& _o_comments, __T2&& _o_custkey, __T3&& _o_orderdate, __T4&& _o_orderkey,
      __T5&& _o_orderpriority, __T6&& _o_orderstatus, __T7&& _o_shippriority,
      __T8&& _o_totalprice): o_clerk(std::forward<__T0>(_o_clerk)),
      o_comments(std::forward<__T1>(_o_comments)), o_custkey(std::forward<__T2>(_o_custkey)),
      o_orderdate(std::forward<__T3>(_o_orderdate)), o_orderkey(std::forward<__T4>(_o_orderkey)),
      o_orderpriority(std::forward<__T5>(_o_orderpriority)),
      o_orderstatus(std::forward<__T6>(_o_orderstatus)),
      o_shippriority(std::forward<__T7>(_o_shippriority)),
      o_totalprice(std::forward<__T8>(_o_totalprice))  {}
      bool operator==(const R_o_clerk_o_comments_o_custkey_o_orderdate_o_orderkey_o_orderpriority_o_orderstatus_o_shippriority_o_totalprice<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8>& __other) const {
        return o_clerk == (__other.o_clerk) && o_comments == (__other.o_comments) && o_custkey == (__other.o_custkey) && o_orderdate == (__other.o_orderdate) && o_orderkey == (__other.o_orderkey) && o_orderpriority == (__other.o_orderpriority) && o_orderstatus == (__other.o_orderstatus) && o_shippriority == (__other.o_shippriority) && o_totalprice == (__other.o_totalprice);
      }
      bool operator!=(const R_o_clerk_o_comments_o_custkey_o_orderdate_o_orderkey_o_orderpriority_o_orderstatus_o_shippriority_o_totalprice<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8>& __other) const {
        return std::tie(o_clerk, o_comments, o_custkey, o_orderdate, o_orderkey, o_orderpriority,
        o_orderstatus, o_shippriority, o_totalprice) != std::tie(__other.o_clerk,
        __other.o_comments, __other.o_custkey, __other.o_orderdate, __other.o_orderkey,
        __other.o_orderpriority, __other.o_orderstatus, __other.o_shippriority,
        __other.o_totalprice);
      }
      bool operator<(const R_o_clerk_o_comments_o_custkey_o_orderdate_o_orderkey_o_orderpriority_o_orderstatus_o_shippriority_o_totalprice<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8>& __other) const {
        return std::tie(o_clerk, o_comments, o_custkey, o_orderdate, o_orderkey, o_orderpriority,
        o_orderstatus, o_shippriority, o_totalprice) < std::tie(__other.o_clerk, __other.o_comments,
        __other.o_custkey, __other.o_orderdate, __other.o_orderkey, __other.o_orderpriority,
        __other.o_orderstatus, __other.o_shippriority, __other.o_totalprice);
      }
      bool operator>(const R_o_clerk_o_comments_o_custkey_o_orderdate_o_orderkey_o_orderpriority_o_orderstatus_o_shippriority_o_totalprice<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8>& __other) const {
        return std::tie(o_clerk, o_comments, o_custkey, o_orderdate, o_orderkey, o_orderpriority,
        o_orderstatus, o_shippriority, o_totalprice) > std::tie(__other.o_clerk, __other.o_comments,
        __other.o_custkey, __other.o_orderdate, __other.o_orderkey, __other.o_orderpriority,
        __other.o_orderstatus, __other.o_shippriority, __other.o_totalprice);
      }
      template <class archive>
      void serialize(archive& _archive, const unsigned int _version)  {
        _archive & o_clerk;
        _archive & o_comments;
        _archive & o_custkey;
        _archive & o_orderdate;
        _archive & o_orderkey;
        _archive & o_orderpriority;
        _archive & o_orderstatus;
        _archive & o_shippriority;
        _archive & o_totalprice;
      }
      _T0 o_clerk;
      _T1 o_comments;
      _T2 o_custkey;
      _T3 o_orderdate;
      _T4 o_orderkey;
      _T5 o_orderpriority;
      _T6 o_orderstatus;
      _T7 o_shippriority;
      _T8 o_totalprice;
};
#endif
namespace K3 {
  template <class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7,
  class _T8>
  class patcher<R_o_clerk_o_comments_o_custkey_o_orderdate_o_orderkey_o_orderpriority_o_orderstatus_o_shippriority_o_totalprice<_T0,
  _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8>> {
    public:
        static void patch(std::string _input,
        R_o_clerk_o_comments_o_custkey_o_orderdate_o_orderkey_o_orderpriority_o_orderstatus_o_shippriority_o_totalprice<_T0,
        _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8>& _record)  {
          shallow<string::iterator> _shallow;
          qi::rule<string::iterator,
          qi::space_type> _o_clerk = (qi::lit("o_clerk") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.o_clerk);
          })];
          qi::rule<string::iterator,
          qi::space_type> _o_comments = (qi::lit("o_comments") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.o_comments);
          })];
          qi::rule<string::iterator,
          qi::space_type> _o_custkey = (qi::lit("o_custkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.o_custkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _o_orderdate = (qi::lit("o_orderdate") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.o_orderdate);
          })];
          qi::rule<string::iterator,
          qi::space_type> _o_orderkey = (qi::lit("o_orderkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.o_orderkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _o_orderpriority = (qi::lit("o_orderpriority") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.o_orderpriority);
          })];
          qi::rule<string::iterator,
          qi::space_type> _o_orderstatus = (qi::lit("o_orderstatus") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.o_orderstatus);
          })];
          qi::rule<string::iterator,
          qi::space_type> _o_shippriority = (qi::lit("o_shippriority") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.o_shippriority);
          })];
          qi::rule<string::iterator,
          qi::space_type> _o_totalprice = (qi::lit("o_totalprice") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.o_totalprice);
          })];
          qi::rule<string::iterator,
          qi::space_type> _field = _o_clerk | _o_comments | _o_custkey | _o_orderdate | _o_orderkey | _o_orderpriority | _o_orderstatus | _o_shippriority | _o_totalprice;
          qi::rule<string::iterator, qi::space_type> _parser = ('{') >> _field % (',') >> ('}');
          qi::phrase_parse(std::begin(_input), std::end(_input), _parser, qi::space);
        }
  };
}
#ifndef K3_R_o_clerk_o_comments_o_custkey_o_orderdate_o_orderkey_o_orderpriority_o_orderstatus_o_shippriority_o_totalprice
#define K3_R_o_clerk_o_comments_o_custkey_o_orderdate_o_orderkey_o_orderpriority_o_orderstatus_o_shippriority_o_totalprice
template <class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7,
class _T8>
std::size_t hash_value(const R_o_clerk_o_comments_o_custkey_o_orderdate_o_orderkey_o_orderpriority_o_orderstatus_o_shippriority_o_totalprice<_T0,
_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8>& r)  {
  boost::hash<std::tuple<_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8>> hasher;
  return hasher(std::tie(r.o_clerk, r.o_comments, r.o_custkey, r.o_orderdate, r.o_orderkey,
  r.o_orderpriority, r.o_orderstatus, r.o_shippriority, r.o_totalprice));
}
#endif
#ifndef K3_R_o_custkey_o_orderdate_o_totalprice_hash_value
#define K3_R_o_custkey_o_orderdate_o_totalprice_hash_value
template <class _T0, class _T1, class _T2>
class R_o_custkey_o_orderdate_o_totalprice {
  public:
      R_o_custkey_o_orderdate_o_totalprice(): o_custkey(), o_orderdate(), o_totalprice()  {}
      template <class __T0, class __T1, class __T2>
      R_o_custkey_o_orderdate_o_totalprice(__T0&& _o_custkey, __T1&& _o_orderdate,
      __T2&& _o_totalprice): o_custkey(std::forward<__T0>(_o_custkey)),
      o_orderdate(std::forward<__T1>(_o_orderdate)),
      o_totalprice(std::forward<__T2>(_o_totalprice))  {}
      bool operator==(const R_o_custkey_o_orderdate_o_totalprice<_T0, _T1, _T2>& __other) const {
        return o_custkey == (__other.o_custkey) && o_orderdate == (__other.o_orderdate) && o_totalprice == (__other.o_totalprice);
      }
      bool operator!=(const R_o_custkey_o_orderdate_o_totalprice<_T0, _T1, _T2>& __other) const {
        return std::tie(o_custkey, o_orderdate, o_totalprice) != std::tie(__other.o_custkey,
        __other.o_orderdate, __other.o_totalprice);
      }
      bool operator<(const R_o_custkey_o_orderdate_o_totalprice<_T0, _T1, _T2>& __other) const {
        return std::tie(o_custkey, o_orderdate, o_totalprice) < std::tie(__other.o_custkey,
        __other.o_orderdate, __other.o_totalprice);
      }
      bool operator>(const R_o_custkey_o_orderdate_o_totalprice<_T0, _T1, _T2>& __other) const {
        return std::tie(o_custkey, o_orderdate, o_totalprice) > std::tie(__other.o_custkey,
        __other.o_orderdate, __other.o_totalprice);
      }
      template <class archive>
      void serialize(archive& _archive, const unsigned int _version)  {
        _archive & o_custkey;
        _archive & o_orderdate;
        _archive & o_totalprice;
      }
      _T0 o_custkey;
      _T1 o_orderdate;
      _T2 o_totalprice;
};
#endif
namespace K3 {
  template <class _T0, class _T1, class _T2>
  class patcher<R_o_custkey_o_orderdate_o_totalprice<_T0, _T1, _T2>> {
    public:
        static void patch(std::string _input, R_o_custkey_o_orderdate_o_totalprice<_T0, _T1,
        _T2>& _record)  {
          shallow<string::iterator> _shallow;
          qi::rule<string::iterator,
          qi::space_type> _o_custkey = (qi::lit("o_custkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.o_custkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _o_orderdate = (qi::lit("o_orderdate") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.o_orderdate);
          })];
          qi::rule<string::iterator,
          qi::space_type> _o_totalprice = (qi::lit("o_totalprice") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.o_totalprice);
          })];
          qi::rule<string::iterator,
          qi::space_type> _field = _o_custkey | _o_orderdate | _o_totalprice;
          qi::rule<string::iterator, qi::space_type> _parser = ('{') >> _field % (',') >> ('}');
          qi::phrase_parse(std::begin(_input), std::end(_input), _parser, qi::space);
        }
  };
}
#ifndef K3_R_o_custkey_o_orderdate_o_totalprice
#define K3_R_o_custkey_o_orderdate_o_totalprice
template <class _T0, class _T1, class _T2>
std::size_t hash_value(const R_o_custkey_o_orderdate_o_totalprice<_T0, _T1, _T2>& r)  {
  boost::hash<std::tuple<_T0, _T1, _T2>> hasher;
  return hasher(std::tie(r.o_custkey, r.o_orderdate, r.o_totalprice));
}
#endif
#ifndef K3_R_od_ok_tp_hash_value
#define K3_R_od_ok_tp_hash_value
template <class _T0, class _T1, class _T2>
class R_od_ok_tp {
  public:
      R_od_ok_tp(): od(), ok(), tp()  {}
      template <class __T0, class __T1, class __T2>
      R_od_ok_tp(__T0&& _od, __T1&& _ok, __T2&& _tp): od(std::forward<__T0>(_od)),
      ok(std::forward<__T1>(_ok)), tp(std::forward<__T2>(_tp))  {}
      bool operator==(const R_od_ok_tp<_T0, _T1, _T2>& __other) const {
        return od == (__other.od) && ok == (__other.ok) && tp == (__other.tp);
      }
      bool operator!=(const R_od_ok_tp<_T0, _T1, _T2>& __other) const {
        return std::tie(od, ok, tp) != std::tie(__other.od, __other.ok, __other.tp);
      }
      bool operator<(const R_od_ok_tp<_T0, _T1, _T2>& __other) const {
        return std::tie(od, ok, tp) < std::tie(__other.od, __other.ok, __other.tp);
      }
      bool operator>(const R_od_ok_tp<_T0, _T1, _T2>& __other) const {
        return std::tie(od, ok, tp) > std::tie(__other.od, __other.ok, __other.tp);
      }
      template <class archive>
      void serialize(archive& _archive, const unsigned int _version)  {
        _archive & od;
        _archive & ok;
        _archive & tp;
      }
      _T0 od;
      _T1 ok;
      _T2 tp;
};
#endif
namespace K3 {
  template <class _T0, class _T1, class _T2>
  class patcher<R_od_ok_tp<_T0, _T1, _T2>> {
    public:
        static void patch(std::string _input, R_od_ok_tp<_T0, _T1, _T2>& _record)  {
          shallow<string::iterator> _shallow;
          qi::rule<string::iterator,
          qi::space_type> _od = (qi::lit("od") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.od);
          })];
          qi::rule<string::iterator,
          qi::space_type> _ok = (qi::lit("ok") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.ok);
          })];
          qi::rule<string::iterator,
          qi::space_type> _tp = (qi::lit("tp") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.tp);
          })];
          qi::rule<string::iterator, qi::space_type> _field = _od | _ok | _tp;
          qi::rule<string::iterator, qi::space_type> _parser = ('{') >> _field % (',') >> ('}');
          qi::phrase_parse(std::begin(_input), std::end(_input), _parser, qi::space);
        }
  };
}
#ifndef K3_R_od_ok_tp
#define K3_R_od_ok_tp
template <class _T0, class _T1, class _T2>
std::size_t hash_value(const R_od_ok_tp<_T0, _T1, _T2>& r)  {
  boost::hash<std::tuple<_T0, _T1, _T2>> hasher;
  return hasher(std::tie(r.od, r.ok, r.tp));
}
#endif
#ifndef K3_R_p_brand_p_comments_p_container_p_mfgr_p_name_p_p_size_p_partkey_p_retailprice_p_type_hash_value
#define K3_R_p_brand_p_comments_p_container_p_mfgr_p_name_p_p_size_p_partkey_p_retailprice_p_type_hash_value
template <class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7,
class _T8>
class R_p_brand_p_comments_p_container_p_mfgr_p_name_p_p_size_p_partkey_p_retailprice_p_type {
  public:
      R_p_brand_p_comments_p_container_p_mfgr_p_name_p_p_size_p_partkey_p_retailprice_p_type(): p_brand(),
      p_comments(), p_container(), p_mfgr(), p_name(), p_p_size(), p_partkey(), p_retailprice(),
      p_type()  {}
      template <class __T0, class __T1, class __T2, class __T3, class __T4, class __T5, class __T6,
      class __T7, class __T8>
      R_p_brand_p_comments_p_container_p_mfgr_p_name_p_p_size_p_partkey_p_retailprice_p_type(__T0&& _p_brand,
      __T1&& _p_comments, __T2&& _p_container, __T3&& _p_mfgr, __T4&& _p_name, __T5&& _p_p_size,
      __T6&& _p_partkey, __T7&& _p_retailprice,
      __T8&& _p_type): p_brand(std::forward<__T0>(_p_brand)),
      p_comments(std::forward<__T1>(_p_comments)), p_container(std::forward<__T2>(_p_container)),
      p_mfgr(std::forward<__T3>(_p_mfgr)), p_name(std::forward<__T4>(_p_name)),
      p_p_size(std::forward<__T5>(_p_p_size)), p_partkey(std::forward<__T6>(_p_partkey)),
      p_retailprice(std::forward<__T7>(_p_retailprice)), p_type(std::forward<__T8>(_p_type))  {}
      bool operator==(const R_p_brand_p_comments_p_container_p_mfgr_p_name_p_p_size_p_partkey_p_retailprice_p_type<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8>& __other) const {
        return p_brand == (__other.p_brand) && p_comments == (__other.p_comments) && p_container == (__other.p_container) && p_mfgr == (__other.p_mfgr) && p_name == (__other.p_name) && p_p_size == (__other.p_p_size) && p_partkey == (__other.p_partkey) && p_retailprice == (__other.p_retailprice) && p_type == (__other.p_type);
      }
      bool operator!=(const R_p_brand_p_comments_p_container_p_mfgr_p_name_p_p_size_p_partkey_p_retailprice_p_type<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8>& __other) const {
        return std::tie(p_brand, p_comments, p_container, p_mfgr, p_name, p_p_size, p_partkey,
        p_retailprice, p_type) != std::tie(__other.p_brand, __other.p_comments, __other.p_container,
        __other.p_mfgr, __other.p_name, __other.p_p_size, __other.p_partkey, __other.p_retailprice,
        __other.p_type);
      }
      bool operator<(const R_p_brand_p_comments_p_container_p_mfgr_p_name_p_p_size_p_partkey_p_retailprice_p_type<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8>& __other) const {
        return std::tie(p_brand, p_comments, p_container, p_mfgr, p_name, p_p_size, p_partkey,
        p_retailprice, p_type) < std::tie(__other.p_brand, __other.p_comments, __other.p_container,
        __other.p_mfgr, __other.p_name, __other.p_p_size, __other.p_partkey, __other.p_retailprice,
        __other.p_type);
      }
      bool operator>(const R_p_brand_p_comments_p_container_p_mfgr_p_name_p_p_size_p_partkey_p_retailprice_p_type<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8>& __other) const {
        return std::tie(p_brand, p_comments, p_container, p_mfgr, p_name, p_p_size, p_partkey,
        p_retailprice, p_type) > std::tie(__other.p_brand, __other.p_comments, __other.p_container,
        __other.p_mfgr, __other.p_name, __other.p_p_size, __other.p_partkey, __other.p_retailprice,
        __other.p_type);
      }
      template <class archive>
      void serialize(archive& _archive, const unsigned int _version)  {
        _archive & p_brand;
        _archive & p_comments;
        _archive & p_container;
        _archive & p_mfgr;
        _archive & p_name;
        _archive & p_p_size;
        _archive & p_partkey;
        _archive & p_retailprice;
        _archive & p_type;
      }
      _T0 p_brand;
      _T1 p_comments;
      _T2 p_container;
      _T3 p_mfgr;
      _T4 p_name;
      _T5 p_p_size;
      _T6 p_partkey;
      _T7 p_retailprice;
      _T8 p_type;
};
#endif
namespace K3 {
  template <class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7,
  class _T8>
  class patcher<R_p_brand_p_comments_p_container_p_mfgr_p_name_p_p_size_p_partkey_p_retailprice_p_type<_T0,
  _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8>> {
    public:
        static void patch(std::string _input,
        R_p_brand_p_comments_p_container_p_mfgr_p_name_p_p_size_p_partkey_p_retailprice_p_type<_T0,
        _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8>& _record)  {
          shallow<string::iterator> _shallow;
          qi::rule<string::iterator,
          qi::space_type> _p_brand = (qi::lit("p_brand") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.p_brand);
          })];
          qi::rule<string::iterator,
          qi::space_type> _p_comments = (qi::lit("p_comments") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.p_comments);
          })];
          qi::rule<string::iterator,
          qi::space_type> _p_container = (qi::lit("p_container") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.p_container);
          })];
          qi::rule<string::iterator,
          qi::space_type> _p_mfgr = (qi::lit("p_mfgr") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.p_mfgr);
          })];
          qi::rule<string::iterator,
          qi::space_type> _p_name = (qi::lit("p_name") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.p_name);
          })];
          qi::rule<string::iterator,
          qi::space_type> _p_p_size = (qi::lit("p_p_size") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.p_p_size);
          })];
          qi::rule<string::iterator,
          qi::space_type> _p_partkey = (qi::lit("p_partkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.p_partkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _p_retailprice = (qi::lit("p_retailprice") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.p_retailprice);
          })];
          qi::rule<string::iterator,
          qi::space_type> _p_type = (qi::lit("p_type") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.p_type);
          })];
          qi::rule<string::iterator,
          qi::space_type> _field = _p_brand | _p_comments | _p_container | _p_mfgr | _p_name | _p_p_size | _p_partkey | _p_retailprice | _p_type;
          qi::rule<string::iterator, qi::space_type> _parser = ('{') >> _field % (',') >> ('}');
          qi::phrase_parse(std::begin(_input), std::end(_input), _parser, qi::space);
        }
  };
}
#ifndef K3_R_p_brand_p_comments_p_container_p_mfgr_p_name_p_p_size_p_partkey_p_retailprice_p_type
#define K3_R_p_brand_p_comments_p_container_p_mfgr_p_name_p_p_size_p_partkey_p_retailprice_p_type
template <class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7,
class _T8>
std::size_t hash_value(const R_p_brand_p_comments_p_container_p_mfgr_p_name_p_p_size_p_partkey_p_retailprice_p_type<_T0,
_T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8>& r)  {
  boost::hash<std::tuple<_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8>> hasher;
  return hasher(std::tie(r.p_brand, r.p_comments, r.p_container, r.p_mfgr, r.p_name, r.p_p_size,
  r.p_partkey, r.p_retailprice, r.p_type));
}
#endif
#ifndef K3_R_path_hash_value
#define K3_R_path_hash_value
template <class _T0>
class R_path {
  public:
      R_path(): path()  {}
      R_path(const _T0& _path): path(_path)  {}
      R_path(_T0&& _path): path(std::move(_path))  {}
      bool operator==(const R_path<_T0>& __other) const {
        return path == (__other.path);
      }
      bool operator!=(const R_path<_T0>& __other) const {
        return std::tie(path) != std::tie(__other.path);
      }
      bool operator<(const R_path<_T0>& __other) const {
        return std::tie(path) < std::tie(__other.path);
      }
      bool operator>(const R_path<_T0>& __other) const {
        return std::tie(path) > std::tie(__other.path);
      }
      template <class archive>
      void serialize(archive& _archive, const unsigned int _version)  {
        _archive & path;
      }
      _T0 path;
};
#endif
namespace K3 {
  template <class _T0>
  class patcher<R_path<_T0>> {
    public:
        static void patch(std::string _input, R_path<_T0>& _record)  {
          shallow<string::iterator> _shallow;
          qi::rule<string::iterator,
          qi::space_type> _path = (qi::lit("path") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.path);
          })];
          qi::rule<string::iterator, qi::space_type> _field = _path;
          qi::rule<string::iterator, qi::space_type> _parser = ('{') >> _field % (',') >> ('}');
          qi::phrase_parse(std::begin(_input), std::end(_input), _parser, qi::space);
        }
  };
}
#ifndef K3_R_path
#define K3_R_path
template <class _T0>
std::size_t hash_value(const R_path<_T0>& r)  {
  boost::hash<std::tuple<_T0>> hasher;
  return hasher(std::tie(r.path));
}
#endif
#ifndef K3_R_ps_availqty_ps_comments_ps_partkey_ps_suppkey_ps_supplycost_hash_value
#define K3_R_ps_availqty_ps_comments_ps_partkey_ps_suppkey_ps_supplycost_hash_value
template <class _T0, class _T1, class _T2, class _T3, class _T4>
class R_ps_availqty_ps_comments_ps_partkey_ps_suppkey_ps_supplycost {
  public:
      R_ps_availqty_ps_comments_ps_partkey_ps_suppkey_ps_supplycost(): ps_availqty(), ps_comments(),
      ps_partkey(), ps_suppkey(), ps_supplycost()  {}
      template <class __T0, class __T1, class __T2, class __T3, class __T4>
      R_ps_availqty_ps_comments_ps_partkey_ps_suppkey_ps_supplycost(__T0&& _ps_availqty,
      __T1&& _ps_comments, __T2&& _ps_partkey, __T3&& _ps_suppkey,
      __T4&& _ps_supplycost): ps_availqty(std::forward<__T0>(_ps_availqty)),
      ps_comments(std::forward<__T1>(_ps_comments)), ps_partkey(std::forward<__T2>(_ps_partkey)),
      ps_suppkey(std::forward<__T3>(_ps_suppkey)),
      ps_supplycost(std::forward<__T4>(_ps_supplycost))  {}
      bool operator==(const R_ps_availqty_ps_comments_ps_partkey_ps_suppkey_ps_supplycost<_T0, _T1,
      _T2, _T3, _T4>& __other) const {
        return ps_availqty == (__other.ps_availqty) && ps_comments == (__other.ps_comments) && ps_partkey == (__other.ps_partkey) && ps_suppkey == (__other.ps_suppkey) && ps_supplycost == (__other.ps_supplycost);
      }
      bool operator!=(const R_ps_availqty_ps_comments_ps_partkey_ps_suppkey_ps_supplycost<_T0, _T1,
      _T2, _T3, _T4>& __other) const {
        return std::tie(ps_availqty, ps_comments, ps_partkey, ps_suppkey,
        ps_supplycost) != std::tie(__other.ps_availqty, __other.ps_comments, __other.ps_partkey,
        __other.ps_suppkey, __other.ps_supplycost);
      }
      bool operator<(const R_ps_availqty_ps_comments_ps_partkey_ps_suppkey_ps_supplycost<_T0, _T1,
      _T2, _T3, _T4>& __other) const {
        return std::tie(ps_availqty, ps_comments, ps_partkey, ps_suppkey,
        ps_supplycost) < std::tie(__other.ps_availqty, __other.ps_comments, __other.ps_partkey,
        __other.ps_suppkey, __other.ps_supplycost);
      }
      bool operator>(const R_ps_availqty_ps_comments_ps_partkey_ps_suppkey_ps_supplycost<_T0, _T1,
      _T2, _T3, _T4>& __other) const {
        return std::tie(ps_availqty, ps_comments, ps_partkey, ps_suppkey,
        ps_supplycost) > std::tie(__other.ps_availqty, __other.ps_comments, __other.ps_partkey,
        __other.ps_suppkey, __other.ps_supplycost);
      }
      template <class archive>
      void serialize(archive& _archive, const unsigned int _version)  {
        _archive & ps_availqty;
        _archive & ps_comments;
        _archive & ps_partkey;
        _archive & ps_suppkey;
        _archive & ps_supplycost;
      }
      _T0 ps_availqty;
      _T1 ps_comments;
      _T2 ps_partkey;
      _T3 ps_suppkey;
      _T4 ps_supplycost;
};
#endif
namespace K3 {
  template <class _T0, class _T1, class _T2, class _T3, class _T4>
  class patcher<R_ps_availqty_ps_comments_ps_partkey_ps_suppkey_ps_supplycost<_T0, _T1, _T2, _T3,
  _T4>> {
    public:
        static void patch(std::string _input,
        R_ps_availqty_ps_comments_ps_partkey_ps_suppkey_ps_supplycost<_T0, _T1, _T2, _T3,
        _T4>& _record)  {
          shallow<string::iterator> _shallow;
          qi::rule<string::iterator,
          qi::space_type> _ps_availqty = (qi::lit("ps_availqty") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.ps_availqty);
          })];
          qi::rule<string::iterator,
          qi::space_type> _ps_comments = (qi::lit("ps_comments") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.ps_comments);
          })];
          qi::rule<string::iterator,
          qi::space_type> _ps_partkey = (qi::lit("ps_partkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.ps_partkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _ps_suppkey = (qi::lit("ps_suppkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.ps_suppkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _ps_supplycost = (qi::lit("ps_supplycost") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.ps_supplycost);
          })];
          qi::rule<string::iterator,
          qi::space_type> _field = _ps_availqty | _ps_comments | _ps_partkey | _ps_suppkey | _ps_supplycost;
          qi::rule<string::iterator, qi::space_type> _parser = ('{') >> _field % (',') >> ('}');
          qi::phrase_parse(std::begin(_input), std::end(_input), _parser, qi::space);
        }
  };
}
#ifndef K3_R_ps_availqty_ps_comments_ps_partkey_ps_suppkey_ps_supplycost
#define K3_R_ps_availqty_ps_comments_ps_partkey_ps_suppkey_ps_supplycost
template <class _T0, class _T1, class _T2, class _T3, class _T4>
std::size_t hash_value(const R_ps_availqty_ps_comments_ps_partkey_ps_suppkey_ps_supplycost<_T0, _T1,
_T2, _T3, _T4>& r)  {
  boost::hash<std::tuple<_T0, _T1, _T2, _T3, _T4>> hasher;
  return hasher(std::tie(r.ps_availqty, r.ps_comments, r.ps_partkey, r.ps_suppkey,
  r.ps_supplycost));
}
#endif
#ifndef K3_R_r_comments_r_name_r_regionkey_hash_value
#define K3_R_r_comments_r_name_r_regionkey_hash_value
template <class _T0, class _T1, class _T2>
class R_r_comments_r_name_r_regionkey {
  public:
      R_r_comments_r_name_r_regionkey(): r_comments(), r_name(), r_regionkey()  {}
      template <class __T0, class __T1, class __T2>
      R_r_comments_r_name_r_regionkey(__T0&& _r_comments, __T1&& _r_name,
      __T2&& _r_regionkey): r_comments(std::forward<__T0>(_r_comments)),
      r_name(std::forward<__T1>(_r_name)), r_regionkey(std::forward<__T2>(_r_regionkey))  {}
      bool operator==(const R_r_comments_r_name_r_regionkey<_T0, _T1, _T2>& __other) const {
        return r_comments == (__other.r_comments) && r_name == (__other.r_name) && r_regionkey == (__other.r_regionkey);
      }
      bool operator!=(const R_r_comments_r_name_r_regionkey<_T0, _T1, _T2>& __other) const {
        return std::tie(r_comments, r_name, r_regionkey) != std::tie(__other.r_comments,
        __other.r_name, __other.r_regionkey);
      }
      bool operator<(const R_r_comments_r_name_r_regionkey<_T0, _T1, _T2>& __other) const {
        return std::tie(r_comments, r_name, r_regionkey) < std::tie(__other.r_comments,
        __other.r_name, __other.r_regionkey);
      }
      bool operator>(const R_r_comments_r_name_r_regionkey<_T0, _T1, _T2>& __other) const {
        return std::tie(r_comments, r_name, r_regionkey) > std::tie(__other.r_comments,
        __other.r_name, __other.r_regionkey);
      }
      template <class archive>
      void serialize(archive& _archive, const unsigned int _version)  {
        _archive & r_comments;
        _archive & r_name;
        _archive & r_regionkey;
      }
      _T0 r_comments;
      _T1 r_name;
      _T2 r_regionkey;
};
#endif
namespace K3 {
  template <class _T0, class _T1, class _T2>
  class patcher<R_r_comments_r_name_r_regionkey<_T0, _T1, _T2>> {
    public:
        static void patch(std::string _input, R_r_comments_r_name_r_regionkey<_T0, _T1,
        _T2>& _record)  {
          shallow<string::iterator> _shallow;
          qi::rule<string::iterator,
          qi::space_type> _r_comments = (qi::lit("r_comments") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.r_comments);
          })];
          qi::rule<string::iterator,
          qi::space_type> _r_name = (qi::lit("r_name") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.r_name);
          })];
          qi::rule<string::iterator,
          qi::space_type> _r_regionkey = (qi::lit("r_regionkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.r_regionkey);
          })];
          qi::rule<string::iterator, qi::space_type> _field = _r_comments | _r_name | _r_regionkey;
          qi::rule<string::iterator, qi::space_type> _parser = ('{') >> _field % (',') >> ('}');
          qi::phrase_parse(std::begin(_input), std::end(_input), _parser, qi::space);
        }
  };
}
#ifndef K3_R_r_comments_r_name_r_regionkey
#define K3_R_r_comments_r_name_r_regionkey
template <class _T0, class _T1, class _T2>
std::size_t hash_value(const R_r_comments_r_name_r_regionkey<_T0, _T1, _T2>& r)  {
  boost::hash<std::tuple<_T0, _T1, _T2>> hasher;
  return hasher(std::tie(r.r_comments, r.r_name, r.r_regionkey));
}
#endif
#ifndef K3_R_s_acctbal_s_address_s_comments_s_name_s_nationkey_s_phone_s_suppkey_hash_value
#define K3_R_s_acctbal_s_address_s_comments_s_name_s_nationkey_s_phone_s_suppkey_hash_value
template <class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6>
class R_s_acctbal_s_address_s_comments_s_name_s_nationkey_s_phone_s_suppkey {
  public:
      R_s_acctbal_s_address_s_comments_s_name_s_nationkey_s_phone_s_suppkey(): s_acctbal(),
      s_address(), s_comments(), s_name(), s_nationkey(), s_phone(), s_suppkey()  {}
      template <class __T0, class __T1, class __T2, class __T3, class __T4, class __T5, class __T6>
      R_s_acctbal_s_address_s_comments_s_name_s_nationkey_s_phone_s_suppkey(__T0&& _s_acctbal,
      __T1&& _s_address, __T2&& _s_comments, __T3&& _s_name, __T4&& _s_nationkey, __T5&& _s_phone,
      __T6&& _s_suppkey): s_acctbal(std::forward<__T0>(_s_acctbal)),
      s_address(std::forward<__T1>(_s_address)), s_comments(std::forward<__T2>(_s_comments)),
      s_name(std::forward<__T3>(_s_name)), s_nationkey(std::forward<__T4>(_s_nationkey)),
      s_phone(std::forward<__T5>(_s_phone)), s_suppkey(std::forward<__T6>(_s_suppkey))  {}
      bool operator==(const R_s_acctbal_s_address_s_comments_s_name_s_nationkey_s_phone_s_suppkey<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6>& __other) const {
        return s_acctbal == (__other.s_acctbal) && s_address == (__other.s_address) && s_comments == (__other.s_comments) && s_name == (__other.s_name) && s_nationkey == (__other.s_nationkey) && s_phone == (__other.s_phone) && s_suppkey == (__other.s_suppkey);
      }
      bool operator!=(const R_s_acctbal_s_address_s_comments_s_name_s_nationkey_s_phone_s_suppkey<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6>& __other) const {
        return std::tie(s_acctbal, s_address, s_comments, s_name, s_nationkey, s_phone,
        s_suppkey) != std::tie(__other.s_acctbal, __other.s_address, __other.s_comments,
        __other.s_name, __other.s_nationkey, __other.s_phone, __other.s_suppkey);
      }
      bool operator<(const R_s_acctbal_s_address_s_comments_s_name_s_nationkey_s_phone_s_suppkey<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6>& __other) const {
        return std::tie(s_acctbal, s_address, s_comments, s_name, s_nationkey, s_phone,
        s_suppkey) < std::tie(__other.s_acctbal, __other.s_address, __other.s_comments,
        __other.s_name, __other.s_nationkey, __other.s_phone, __other.s_suppkey);
      }
      bool operator>(const R_s_acctbal_s_address_s_comments_s_name_s_nationkey_s_phone_s_suppkey<_T0,
      _T1, _T2, _T3, _T4, _T5, _T6>& __other) const {
        return std::tie(s_acctbal, s_address, s_comments, s_name, s_nationkey, s_phone,
        s_suppkey) > std::tie(__other.s_acctbal, __other.s_address, __other.s_comments,
        __other.s_name, __other.s_nationkey, __other.s_phone, __other.s_suppkey);
      }
      template <class archive>
      void serialize(archive& _archive, const unsigned int _version)  {
        _archive & s_acctbal;
        _archive & s_address;
        _archive & s_comments;
        _archive & s_name;
        _archive & s_nationkey;
        _archive & s_phone;
        _archive & s_suppkey;
      }
      _T0 s_acctbal;
      _T1 s_address;
      _T2 s_comments;
      _T3 s_name;
      _T4 s_nationkey;
      _T5 s_phone;
      _T6 s_suppkey;
};
#endif
namespace K3 {
  template <class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6>
  class patcher<R_s_acctbal_s_address_s_comments_s_name_s_nationkey_s_phone_s_suppkey<_T0, _T1, _T2,
  _T3, _T4, _T5, _T6>> {
    public:
        static void patch(std::string _input,
        R_s_acctbal_s_address_s_comments_s_name_s_nationkey_s_phone_s_suppkey<_T0, _T1, _T2, _T3,
        _T4, _T5, _T6>& _record)  {
          shallow<string::iterator> _shallow;
          qi::rule<string::iterator,
          qi::space_type> _s_acctbal = (qi::lit("s_acctbal") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.s_acctbal);
          })];
          qi::rule<string::iterator,
          qi::space_type> _s_address = (qi::lit("s_address") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.s_address);
          })];
          qi::rule<string::iterator,
          qi::space_type> _s_comments = (qi::lit("s_comments") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.s_comments);
          })];
          qi::rule<string::iterator,
          qi::space_type> _s_name = (qi::lit("s_name") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.s_name);
          })];
          qi::rule<string::iterator,
          qi::space_type> _s_nationkey = (qi::lit("s_nationkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.s_nationkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _s_phone = (qi::lit("s_phone") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.s_phone);
          })];
          qi::rule<string::iterator,
          qi::space_type> _s_suppkey = (qi::lit("s_suppkey") >> (':') >> _shallow)[([&_record] (std::string _partial)   {
            do_patch(_partial, _record.s_suppkey);
          })];
          qi::rule<string::iterator,
          qi::space_type> _field = _s_acctbal | _s_address | _s_comments | _s_name | _s_nationkey | _s_phone | _s_suppkey;
          qi::rule<string::iterator, qi::space_type> _parser = ('{') >> _field % (',') >> ('}');
          qi::phrase_parse(std::begin(_input), std::end(_input), _parser, qi::space);
        }
  };
}
#ifndef K3_R_s_acctbal_s_address_s_comments_s_name_s_nationkey_s_phone_s_suppkey
#define K3_R_s_acctbal_s_address_s_comments_s_name_s_nationkey_s_phone_s_suppkey
template <class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6>
std::size_t hash_value(const R_s_acctbal_s_address_s_comments_s_name_s_nationkey_s_phone_s_suppkey<_T0,
_T1, _T2, _T3, _T4, _T5, _T6>& r)  {
  boost::hash<std::tuple<_T0, _T1, _T2, _T3, _T4, _T5, _T6>> hasher;
  return hasher(std::tie(r.s_acctbal, r.s_address, r.s_comments, r.s_name, r.s_nationkey, r.s_phone,
  r.s_suppkey));
}
#endif
template <class __CONTENT>
class _Collection: public K3::Collection<__CONTENT> {
  public:
      _Collection(): K3::Collection<__CONTENT>()  {}
      _Collection(const K3::Collection<__CONTENT>& __other1): K3::Collection<__CONTENT>(__other1)  {}
      _Collection(K3::Collection<__CONTENT>&& __other1): K3::Collection<__CONTENT>(std::move(__other1))  {}
      template <class archive>
      void serialize(archive& _archive, const unsigned int _version)  {
        _archive & boost::serialization::base_object<K3::Collection<__CONTENT>>(*this);
      }
};
namespace K3 {
  template <class __CONTENT>
  class patcher<_Collection<__CONTENT>> {
    public:
        static void patch(std::string _input, _Collection<__CONTENT>& _c)  {
          collection_patcher<_Collection, __CONTENT>::patch(_input, _c);
        }
  };
}
template <class __CONTENT>
class _Map: public K3::Map<__CONTENT> {
  public:
      _Map(): K3::Map<__CONTENT>()  {}
      _Map(const K3::Map<__CONTENT>& __other1): K3::Map<__CONTENT>(__other1)  {}
      _Map(K3::Map<__CONTENT>&& __other1): K3::Map<__CONTENT>(std::move(__other1))  {}
      template <class archive>
      void serialize(archive& _archive, const unsigned int _version)  {
        _archive & boost::serialization::base_object<K3::Map<__CONTENT>>(*this);
      }
};
namespace K3 {
  template <class __CONTENT>
  class patcher<_Map<__CONTENT>> {
    public:
        static void patch(std::string _input, _Map<__CONTENT>& _c)  {
          collection_patcher<_Map, __CONTENT>::patch(_input, _c);
        }
  };
}
class __global_context: public K3::__standard_context, public K3::__string_context,
public K3::__time_context {
  public:
      __global_context(Engine& __engine): K3::__standard_context(__engine), K3::__string_context(),
      K3::__time_context()  {
        dispatch_table[__li_having_scan_tid] = [this] (void* payload)   {
          li_having_scan(*(static_cast<unit_t*>(payload)));
        };
        dispatch_table[__li_having_peer_barrier_tid] = [this] (void* payload)   {
          li_having_peer_barrier(*(static_cast<unit_t*>(payload)));
        };
        dispatch_table[__li_having_merge_tid] = [this] (void* payload)   {
          li_having_merge(*(static_cast<_Collection<R_key_value<int, double>>*>(payload)));
        };
        dispatch_table[__li_having_global_barrier_tid] = [this] (void* payload)   {
          li_having_global_barrier(*(static_cast<unit_t*>(payload)));
        };
        dispatch_table[__shutdown_tid] = [this] (void* payload)   {
          shutdown_(*(static_cast<unit_t*>(payload)));
        };
        dispatch_table[__ready_tid] = [this] (void* payload)   {
          ready(*(static_cast<unit_t*>(payload)));
        };
        dispatch_table[__loc_rhs_scan_tid] = [this] (void* payload)   {
          loc_rhs_scan(*(static_cast<unit_t*>(payload)));
        };
        dispatch_table[__loc_rhs_peer_barrier_tid] = [this] (void* payload)   {
          loc_rhs_peer_barrier(*(static_cast<unit_t*>(payload)));
        };
        dispatch_table[__loc_probe_rhs_tid] = [this] (void* payload)   {
          loc_probe_rhs(*(static_cast<_Collection<R_key_value<int, K3::base_string>>*>(payload)));
        };
        dispatch_table[__loc_lhs_scan_tid] = [this] (void* payload)   {
          loc_lhs_scan(*(static_cast<unit_t*>(payload)));
        };
        dispatch_table[__loc_lhs_peer_barrier_tid] = [this] (void* payload)   {
          loc_lhs_peer_barrier(*(static_cast<unit_t*>(payload)));
        };
        dispatch_table[__loc_global_barrier_tid] = [this] (void* payload)   {
          loc_global_barrier(*(static_cast<unit_t*>(payload)));
        };
        dispatch_table[__loc_build_lhs_tid] = [this] (void* payload)   {
          loc_build_lhs(*(static_cast<_Collection<R_key_value<int,
          _Map<R_key_value<R_od_ok_tp<K3::base_string, int, double>, double>>>>*>(payload)));
        };
        dispatch_table[__load_all_tid] = [this] (void* payload)   {
          load_all(*(static_cast<unit_t*>(payload)));
        };
        dispatch_table[__hello_tid] = [this] (void* payload)   {
          hello(*(static_cast<unit_t*>(payload)));
        };
        dispatch_table[__finished_tid] = [this] (void* payload)   {
          finished(*(static_cast<unit_t*>(payload)));
        };
        dispatch_table[__start_tid] = [this] (void* payload)   {
          start(*(static_cast<unit_t*>(payload)));
        };
        dispatch_table[__log_aggregate_peer_barrier_tid] = [this] (void* payload)   {
          log_aggregate_peer_barrier(*(static_cast<unit_t*>(payload)));
        };
        dispatch_table[__loc_aggregate_tid] = [this] (void* payload)   {
          loc_aggregate(*(static_cast<_Collection<R_key_value<R_ck_nm_od_ok_tp<int, K3::base_string,
          K3::base_string, int, double>, double>>*>(payload)));
        };
        dispatch_table[__lineitem_orders_customer_tid] = [this] (void* payload)   {
          lineitem_orders_customer(*(static_cast<unit_t*>(payload)));
        };
        dispatch_table[__lineitem_orders_tid] = [this] (void* payload)   {
          lineitem_orders(*(static_cast<unit_t*>(payload)));
        };
        dispatch_table[__lineitem_having_tid] = [this] (void* payload)   {
          lineitem_having(*(static_cast<unit_t*>(payload)));
        };
      }
      static int __lineitem_having_tid;
      static int __lineitem_orders_tid;
      static int __lineitem_orders_customer_tid;
      static int __loc_aggregate_tid;
      static int __log_aggregate_peer_barrier_tid;
      static int __start_tid;
      static int __finished_tid;
      static int __hello_tid;
      static int __load_all_tid;
      static int __loc_build_lhs_tid;
      static int __loc_global_barrier_tid;
      static int __loc_lhs_peer_barrier_tid;
      static int __loc_lhs_scan_tid;
      static int __loc_probe_rhs_tid;
      static int __loc_rhs_peer_barrier_tid;
      static int __loc_rhs_scan_tid;
      static int __ready_tid;
      static int __shutdown_tid;
      static int __li_having_global_barrier_tid;
      static int __li_having_merge_tid;
      static int __li_having_peer_barrier_tid;
      static int __li_having_scan_tid;
      Address me;
      _Collection<R_addr<Address>> peers;
      std::tuple<_Collection<R_arg<K3::base_string>>, _Collection<R_key_value<K3::base_string,
      K3::base_string>>> args;
      K3::base_string role;
      _Collection<R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax<K3::base_string,
      K3::base_string, double, double, int, K3::base_string, int, int, double, K3::base_string,
      K3::base_string, K3::base_string, K3::base_string, K3::base_string, int, double>> lineitem;
      _Collection<R_c_acctbal_c_address_c_comments_c_custkey_c_mktsegment_c_name_c_nationkey_c_phone<double,
      K3::base_string, K3::base_string, int, K3::base_string, K3::base_string, int,
      K3::base_string>> customer;
      _Collection<R_o_clerk_o_comments_o_custkey_o_orderdate_o_orderkey_o_orderpriority_o_orderstatus_o_shippriority_o_totalprice<K3::base_string,
      K3::base_string, int, K3::base_string, int, K3::base_string, K3::base_string, int,
      double>> orders;
      _Map<R_key_value<R_ck_nm_od_ok_tp<int, K3::base_string, K3::base_string, int, double>,
      double>> q18_peer_result;
      _Map<R_key_value<int, _Map<R_key_value<R_od_ok_tp<K3::base_string, int, double>,
      double>>>> lo_odtq_by_ck;
      _Map<R_key_value<int, _Map<R_key_value<R_od_ok_tp<K3::base_string, int, double>,
      double>>>> loc_build;
      _Map<R_key_value<R_ck_nm_od_ok_tp<int, K3::base_string, K3::base_string, int, double>,
      double>> loc_q_by_ncodt;
      auto merge_q_by_odt_r(const R_key_value<R_od_ok_tp<K3::base_string, int, double>,
      double>& a)  {
        return [this, &a] (const R_key_value<R_od_ok_tp<K3::base_string, int, double>,
        double>& b) mutable  {
          return R_key_value<R_od_ok_tp<K3::base_string, int, double>, double> {a.key,
          (a.value) + (b.value)};
        };
      }
      auto merge_odtq_by_ck_r(const R_key_value<int, _Map<R_key_value<R_od_ok_tp<K3::base_string,
      int, double>, double>>>& a)  {
        return [this, a = std::move(a)] (const R_key_value<int,
        _Map<R_key_value<R_od_ok_tp<K3::base_string, int, double>, double>>>& b) mutable  {
          return R_key_value<int, _Map<R_key_value<R_od_ok_tp<K3::base_string, int, double>,
          double>>> {a.key,
          (a.value).fold(std::move([this] (_Map<R_key_value<R_od_ok_tp<K3::base_string, int,
          double>, double>> acc) mutable  {
            return [this, acc = std::move(acc)] (const R_key_value<R_od_ok_tp<K3::base_string, int,
            double>, double>& r) mutable  {
              acc.insert_with(std::move(r), std::bind(&__global_context::merge_q_by_odt_r, std::ref(*this), std::placeholders::_1));
              return std::move(acc);
            };
          }), std::move(b.value))};
        };
      }
      auto merge_q_by_ncodt_r(const R_key_value<R_ck_nm_od_ok_tp<int, K3::base_string,
      K3::base_string, int, double>, double>& a)  {
        return [this, &a] (const R_key_value<R_ck_nm_od_ok_tp<int, K3::base_string, K3::base_string,
        int, double>, double>& b) mutable  {
          return R_key_value<R_ck_nm_od_ok_tp<int, K3::base_string, K3::base_string, int, double>,
          double> {a.key, (a.value) + (b.value)};
        };
      }
      unit_t lineitem_having(unit_t _)  {
        return peers.iterate(std::move([this] (const R_addr<Address>& p) mutable  {
          auto d = std::make_shared<K3::ValDispatcher<unit_t>>(unit_t {});
          __engine.send(p.addr, __li_having_scan_tid, d);
          return unit_t {};
        }));
      }
      unit_t lineitem_orders(unit_t _)  {
        return ignore(std::move(orders.fold(std::move([this] (_Collection<R_key_value<int,
        R_o_custkey_o_orderdate_o_totalprice<int, K3::base_string, double>>> acc) mutable  {
          return [this,
          acc = std::move(acc)] (const R_o_clerk_o_comments_o_custkey_o_orderdate_o_orderkey_o_orderpriority_o_orderstatus_o_shippriority_o_totalprice<K3::base_string,
          K3::base_string, int, K3::base_string, int, K3::base_string, K3::base_string, int,
          double>& o) mutable  {
            acc.insert(R_key_value<int, R_o_custkey_o_orderdate_o_totalprice<int, K3::base_string,
            double>> {o.o_orderkey, R_o_custkey_o_orderdate_o_totalprice<int, K3::base_string,
            double> {o.o_custkey, o.o_orderdate, o.o_totalprice}});
            return std::move(acc);
          };
        }), _Collection<R_key_value<int, R_o_custkey_o_orderdate_o_totalprice<int, K3::base_string,
        double>>> {})));
      }
      unit_t lineitem_orders_customer(unit_t _)  {
        return peers.iterate(std::move([this] (const R_addr<Address>& p) mutable  {
          auto d = std::make_shared<K3::ValDispatcher<unit_t>>(unit_t {});
          __engine.send(p.addr, __loc_lhs_scan_tid, d);
          return unit_t {};
        }));
      }
      unit_t loc_aggregate(const _Collection<R_key_value<R_ck_nm_od_ok_tp<int, K3::base_string,
      K3::base_string, int, double>, double>>& vals)  {
        return vals.iterate(std::move([this] (const R_key_value<R_ck_nm_od_ok_tp<int,
        K3::base_string, K3::base_string, int, double>, double>& kv) mutable  {
          return q18_peer_result.insert_with(std::move(kv), std::bind(&__global_context::merge_q_by_ncodt_r, std::ref(*this), std::placeholders::_1));
        }));
      }
      unit_t log_aggregate_peer_barrier(unit_t _)  {
        loc_aggregate_done_cnt = loc_aggregate_done_cnt + (1);
        if (loc_aggregate_done_cnt == peers.size(unit_t {})) {
          print("Query 18 done.");
          auto d = std::make_shared<K3::ValDispatcher<unit_t>>(unit_t {});
          __engine.send(master, __finished_tid, d);
          return unit_t {};
        } else {
          return unit_t {};
        }
      }
      unit_t start(unit_t _)  {
        auto d = std::make_shared<K3::ValDispatcher<unit_t>>(unit_t {});
        __engine.send(me, __load_all_tid, d);
        return unit_t {};
      }
      unit_t rowsProcess(unit_t _)  {
        return [this] (const unit_t& next) mutable  {
          auto d = std::make_shared<K3::ValDispatcher<unit_t>>(next);
          __engine.send(me, __start_tid, d);
          return unit_t {};
        }(unit_t {});
      }
      unit_t processRole(const unit_t& _)  {
        if (role == ("rows")) {
          return rowsProcess(unit_t {});
        } else {
          return unit_t {};
        }
      }
      unit_t lineitemLoader(string file, _Collection<R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax<K3::base_string,
      K3::base_string, double, double, int, K3::base_string, int, int, double, K3::base_string,
      K3::base_string, K3::base_string, K3::base_string, K3::base_string, int, double>>& c)  {
        std::ifstream _in;
        _in.open(file);
        K3::read_records(_in, c, [] (std::istream& in, std::string& tmp_buffer)   {
          R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax<K3::base_string,
          K3::base_string, double, double, int, K3::base_string, int, int, double, K3::base_string,
          K3::base_string, K3::base_string, K3::base_string, K3::base_string, int, double> record;
          std::getline(in, tmp_buffer, '|');
          record.l_orderkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.l_partkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.l_suppkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.l_linenumber = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.l_quantity = std::atof(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.l_extendedprice = std::atof(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.l_discount = std::atof(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.l_tax = std::atof(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.l_returnflag = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.l_linestatus = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.l_shipdate = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.l_commitdate = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.l_receiptdate = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.l_shipinstruct = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.l_shipmode = tmp_buffer;
          std::getline(in, tmp_buffer);
          record.l_comments = tmp_buffer;
          return record;
        });
        return unit_t {};
      }
      unit_t customerLoader(string file,
      _Collection<R_c_acctbal_c_address_c_comments_c_custkey_c_mktsegment_c_name_c_nationkey_c_phone<double,
      K3::base_string, K3::base_string, int, K3::base_string, K3::base_string, int,
      K3::base_string>>& c)  {
        std::ifstream _in;
        _in.open(file);
        K3::read_records(_in, c, [] (std::istream& in, std::string& tmp_buffer)   {
          R_c_acctbal_c_address_c_comments_c_custkey_c_mktsegment_c_name_c_nationkey_c_phone<double,
          K3::base_string, K3::base_string, int, K3::base_string, K3::base_string, int,
          K3::base_string> record;
          std::getline(in, tmp_buffer, '|');
          record.c_custkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.c_name = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.c_address = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.c_nationkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.c_phone = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.c_acctbal = std::atof(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.c_mktsegment = tmp_buffer;
          std::getline(in, tmp_buffer);
          record.c_comments = tmp_buffer;
          return record;
        });
        return unit_t {};
      }
      unit_t ordersLoader(string file,
      _Collection<R_o_clerk_o_comments_o_custkey_o_orderdate_o_orderkey_o_orderpriority_o_orderstatus_o_shippriority_o_totalprice<K3::base_string,
      K3::base_string, int, K3::base_string, int, K3::base_string, K3::base_string, int,
      double>>& c)  {
        std::ifstream _in;
        _in.open(file);
        K3::read_records(_in, c, [] (std::istream& in, std::string& tmp_buffer)   {
          R_o_clerk_o_comments_o_custkey_o_orderdate_o_orderkey_o_orderpriority_o_orderstatus_o_shippriority_o_totalprice<K3::base_string,
          K3::base_string, int, K3::base_string, int, K3::base_string, K3::base_string, int,
          double> record;
          std::getline(in, tmp_buffer, '|');
          record.o_orderkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.o_custkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.o_orderstatus = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.o_totalprice = std::atof(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.o_orderdate = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.o_orderpriority = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.o_clerk = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.o_shippriority = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer);
          record.o_comments = tmp_buffer;
          return record;
        });
        return unit_t {};
      }
      unit_t supplierLoader(string file,
      _Collection<R_s_acctbal_s_address_s_comments_s_name_s_nationkey_s_phone_s_suppkey<double,
      K3::base_string, K3::base_string, K3::base_string, int, K3::base_string, int>>& c)  {
        std::ifstream _in;
        _in.open(file);
        K3::read_records(_in, c, [] (std::istream& in, std::string& tmp_buffer)   {
          R_s_acctbal_s_address_s_comments_s_name_s_nationkey_s_phone_s_suppkey<double,
          K3::base_string, K3::base_string, K3::base_string, int, K3::base_string, int> record;
          std::getline(in, tmp_buffer, '|');
          record.s_suppkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.s_name = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.s_address = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.s_nationkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.s_phone = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.s_acctbal = std::atof(tmp_buffer.c_str());
          std::getline(in, tmp_buffer);
          record.s_comments = tmp_buffer;
          return record;
        });
        return unit_t {};
      }
      unit_t partsuppLoader(string file,
      _Collection<R_ps_availqty_ps_comments_ps_partkey_ps_suppkey_ps_supplycost<int,
      K3::base_string, int, int, double>>& c)  {
        std::ifstream _in;
        _in.open(file);
        K3::read_records(_in, c, [] (std::istream& in, std::string& tmp_buffer)   {
          R_ps_availqty_ps_comments_ps_partkey_ps_suppkey_ps_supplycost<int, K3::base_string, int,
          int, double> record;
          std::getline(in, tmp_buffer, '|');
          record.ps_partkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.ps_suppkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.ps_availqty = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.ps_supplycost = std::atof(tmp_buffer.c_str());
          std::getline(in, tmp_buffer);
          record.ps_comments = tmp_buffer;
          return record;
        });
        return unit_t {};
      }
      unit_t partLoader(string file,
      _Collection<R_p_brand_p_comments_p_container_p_mfgr_p_name_p_p_size_p_partkey_p_retailprice_p_type<K3::base_string,
      K3::base_string, K3::base_string, K3::base_string, K3::base_string, int, int, double,
      K3::base_string>>& c)  {
        std::ifstream _in;
        _in.open(file);
        K3::read_records(_in, c, [] (std::istream& in, std::string& tmp_buffer)   {
          R_p_brand_p_comments_p_container_p_mfgr_p_name_p_p_size_p_partkey_p_retailprice_p_type<K3::base_string,
          K3::base_string, K3::base_string, K3::base_string, K3::base_string, int, int, double,
          K3::base_string> record;
          std::getline(in, tmp_buffer, '|');
          record.p_partkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.p_name = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.p_mfgr = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.p_brand = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.p_type = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.p_p_size = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.p_container = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.p_retailprice = std::atof(tmp_buffer.c_str());
          std::getline(in, tmp_buffer);
          record.p_comments = tmp_buffer;
          return record;
        });
        return unit_t {};
      }
      unit_t nationLoader(string file,
      _Collection<R_n_comments_n_name_n_nationkey_n_regionkey<K3::base_string, K3::base_string, int,
      int>>& c)  {
        std::ifstream _in;
        _in.open(file);
        K3::read_records(_in, c, [] (std::istream& in, std::string& tmp_buffer)   {
          R_n_comments_n_name_n_nationkey_n_regionkey<K3::base_string, K3::base_string, int,
          int> record;
          std::getline(in, tmp_buffer, '|');
          record.n_nationkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.n_name = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.n_regionkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer);
          record.n_comments = tmp_buffer;
          return record;
        });
        return unit_t {};
      }
      unit_t regionLoader(string file, _Collection<R_r_comments_r_name_r_regionkey<K3::base_string,
      K3::base_string, int>>& c)  {
        std::ifstream _in;
        _in.open(file);
        K3::read_records(_in, c, [] (std::istream& in, std::string& tmp_buffer)   {
          R_r_comments_r_name_r_regionkey<K3::base_string, K3::base_string, int> record;
          std::getline(in, tmp_buffer, '|');
          record.r_regionkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.r_name = tmp_buffer;
          std::getline(in, tmp_buffer);
          record.r_comments = tmp_buffer;
          return record;
        });
        return unit_t {};
      }
      unit_t tpchAgendaLoader(string file,
      _Collection<R_acctbal_address_availqty_brand_clerk_comments_commitdate_container_custkey_d_size_discount_event_extendedprice_linenumber_linestatus_mfgr_mktsegment_name_nationkey_oid_orderdate_orderkey_orderpriority_orderstatus_partkey_phone_quantity_receiptdate_regionkey_retailprice_returnflag_schema_shipdate_shipinstruct_shipmode_shippriority_suppkey_supplycost_tax_totalprice_type2<double,
      K3::base_string, int, K3::base_string, K3::base_string, K3::base_string, K3::base_string,
      K3::base_string, int, int, double, int, double, int, K3::base_string, K3::base_string,
      K3::base_string, K3::base_string, int, int, K3::base_string, int, K3::base_string,
      K3::base_string, int, K3::base_string, double, K3::base_string, int, double, K3::base_string,
      K3::base_string, K3::base_string, K3::base_string, K3::base_string, int, int, double, double,
      double, K3::base_string>>& c)  {
        std::ifstream _in;
        _in.open(file);
        K3::read_records(_in, c, [] (std::istream& in, std::string& tmp_buffer)   {
          R_acctbal_address_availqty_brand_clerk_comments_commitdate_container_custkey_d_size_discount_event_extendedprice_linenumber_linestatus_mfgr_mktsegment_name_nationkey_oid_orderdate_orderkey_orderpriority_orderstatus_partkey_phone_quantity_receiptdate_regionkey_retailprice_returnflag_schema_shipdate_shipinstruct_shipmode_shippriority_suppkey_supplycost_tax_totalprice_type2<double,
          K3::base_string, int, K3::base_string, K3::base_string, K3::base_string, K3::base_string,
          K3::base_string, int, int, double, int, double, int, K3::base_string, K3::base_string,
          K3::base_string, K3::base_string, int, int, K3::base_string, int, K3::base_string,
          K3::base_string, int, K3::base_string, double, K3::base_string, int, double,
          K3::base_string, K3::base_string, K3::base_string, K3::base_string, K3::base_string, int,
          int, double, double, double, K3::base_string> record;
          std::getline(in, tmp_buffer, '|');
          record.oid = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.schema = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.event = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.acctbal = std::atof(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.address = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.availqty = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.brand = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.clerk = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.comments = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.commitdate = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.container = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.custkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.discount = std::atof(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.extendedprice = std::atof(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.linenumber = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.linestatus = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.mfgr = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.mktsegment = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.name = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.nationkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.orderdate = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.orderkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.orderpriority = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.orderstatus = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.partkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.phone = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.quantity = std::atof(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.receiptdate = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.regionkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.retailprice = std::atof(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.returnflag = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.shipdate = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.shipinstruct = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.shipmode = tmp_buffer;
          std::getline(in, tmp_buffer, '|');
          record.shippriority = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.d_size = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.suppkey = std::atoi(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.supplycost = std::atof(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.tax = std::atof(tmp_buffer.c_str());
          std::getline(in, tmp_buffer, '|');
          record.totalprice = std::atof(tmp_buffer.c_str());
          std::getline(in, tmp_buffer);
          record.type2 = tmp_buffer;
          return record;
        });
        return unit_t {};
      }
      template <class a>
      unit_t ignore(a _)  {
        return unit_t {};
      }
      _Collection<R_path<K3::base_string>> customerFiles;
      _Collection<R_path<K3::base_string>> dataFiles;
      template <class a>
      int index_by_hash(a s)  {
        {
          int n;
          n = peers.size(unit_t {});
          {
            int h;
            h = hash(std::move(s));
            return (h % n + n) % n;
          }
        }
      }
      _Map<R_key_value<int, double>> li_having_result;
      _Collection<R_path<K3::base_string>> lineitemFiles;
      int loc_aggregate_done_cnt;
      bool __loc_aggregate_done_cnt_set__ = false;
      Address master;
      bool __master_set__ = false;
      _Collection<R_path<K3::base_string>> nationFiles;
      _Collection<R_path<K3::base_string>> ordersFiles;
      _Collection<R_path<K3::base_string>> partFiles;
      _Collection<R_path<K3::base_string>> partsuppFiles;
      _Collection<R_path<K3::base_string>> regionFiles;
      _Collection<R_path<K3::base_string>> supplierFiles;
      unit_t finished(const unit_t& finishArg)  {
        [this] (unit_t _) mutable  {
          return unit_t {};
        }(std::move(finishArg));
        query_done_cnt = query_done_cnt + (1);
        if (query_done_cnt == peers.size(unit_t {})) {
          {
            unit_t result;
            result = peers.iterate(std::move([this] (const R_addr<Address>& p) mutable  {
              auto d = std::make_shared<K3::ValDispatcher<unit_t>>(unit_t {});
              __engine.send(p.addr, __shutdown_tid, d);
              return unit_t {};
            }));
            {
              K3::base_string tag;
              tag = concat(std::move(concat("Query time", "query")), ":");
              query_end_ms = now_int(unit_t {});
              query_elapsed_ms = query_end_ms - query_start_ms;
              print(std::move(concat(std::move(tag), std::move(itos(query_elapsed_ms)))));
              return result;
            }
          }
        } else {
          return unit_t {};
        }
      }
      unit_t hello(unit_t _)  {
        return unit_t {};
      }
      unit_t load_all(unit_t _)  {
        {
          int start;
          start = now_int(unit_t {});
          {
            unit_t result;
            lineitemFiles.iterate(std::move([this] (R_path<K3::base_string> e) mutable  {
              return lineitemLoader(std::move(e.path), lineitem);
            }));
            ordersFiles.iterate(std::move([this] (R_path<K3::base_string> e) mutable  {
              return ordersLoader(std::move(e.path), orders);
            }));
            result = customerFiles.iterate(std::move([this] (R_path<K3::base_string> e) mutable  {
              return customerLoader(std::move(e.path), customer);
            }));
            {
              int end;
              end = now_int(unit_t {});
              {
                int elapsed_str;
                elapsed_str = end - start;
                {
                  K3::base_string tag;
                  tag = concat(std::move(concat("Load time", "loader")), ":");
                  print(std::move(concat(std::move(tag), std::move(itos(std::move(elapsed_str))))));
                }
              }
            }
          }
        }
        auto d = std::make_shared<K3::ValDispatcher<unit_t>>(unit_t {});
        __engine.send(master, __ready_tid, d);
        return unit_t {};
      }
      unit_t loc_build_lhs(const _Collection<R_key_value<int,
      _Map<R_key_value<R_od_ok_tp<K3::base_string, int, double>, double>>>>& vals)  {
        return vals.iterate(std::move([this] (const R_key_value<int,
        _Map<R_key_value<R_od_ok_tp<K3::base_string, int, double>, double>>>& lo) mutable  {
          return loc_build.insert_with(std::move(lo), std::bind(&__global_context::merge_odtq_by_ck_r, std::ref(*this), std::placeholders::_1));
        }));
      }
      unit_t loc_global_barrier(unit_t _)  {
        loc_join_done_cnt = loc_join_done_cnt + (1);
        if (loc_join_done_cnt == peers.size(unit_t {})) {
          print("Hash join done.");
          return print("LI-OR-CS join all nodes finished.");
        } else {
          return unit_t {};
        }
      }
      unit_t loc_lhs_peer_barrier(unit_t _)  {
        print("Hash join LHS finished build.");
        loc_peer_build_done_cnt = loc_peer_build_done_cnt + (1);
        if (loc_peer_build_done_cnt == peers.size(unit_t {})) {
          return peers.iterate(std::move([this] (const R_addr<Address>& p) mutable  {
            auto d = std::make_shared<K3::ValDispatcher<unit_t>>(unit_t {});
            __engine.send(p.addr, __loc_rhs_scan_tid, d);
            return unit_t {};
          }));
        } else {
          return unit_t {};
        }
      }
      unit_t loc_lhs_scan(unit_t _)  {
        (lo_odtq_by_ck.groupBy(std::move([this] (const R_key_value<int,
        _Map<R_key_value<R_od_ok_tp<K3::base_string, int, double>, double>>>& v) mutable  {
          return index_by_hash(std::move(v.key));
        }), std::move([this] (_Collection<R_key_value<int,
        _Map<R_key_value<R_od_ok_tp<K3::base_string, int, double>, double>>>> acc) mutable  {
          return [this, acc = std::move(acc)] (const R_key_value<int,
          _Map<R_key_value<R_od_ok_tp<K3::base_string, int, double>, double>>>& v) mutable  {
            acc.insert(std::move(v));
            return std::move(acc);
          };
        }), _Collection<R_key_value<int, _Map<R_key_value<R_od_ok_tp<K3::base_string, int, double>,
        double>>>> {})).iterate(std::move([this] (const R_key_value<int,
        _Collection<R_key_value<int, _Map<R_key_value<R_od_ok_tp<K3::base_string, int, double>,
        double>>>>>& v) mutable  {
          shared_ptr<R_addr<Address>> __0;
          __0 = peers.at(std::move(v.key));
          if (__0) {
            auto& p = *(__0);
            auto d = std::make_shared<K3::ValDispatcher<_Collection<R_key_value<int,
            _Map<R_key_value<R_od_ok_tp<K3::base_string, int, double>, double>>>>>>(v.value);
            __engine.send(p.addr, __loc_build_lhs_tid, d);
            return unit_t {};
          } else {
            return error<unit_t>(unit_t {});
          }
        }));
        return ignore(std::move(peers.iterate(std::move([this] (const R_addr<Address>& p) mutable  {
          auto d = std::make_shared<K3::ValDispatcher<unit_t>>(unit_t {});
          __engine.send(p.addr, __loc_lhs_peer_barrier_tid, d);
          return unit_t {};
        }))));
      }
      unit_t loc_probe_rhs(const _Collection<R_key_value<int, K3::base_string>>& vals)  {
        return vals.iterate(std::move([this] (const R_key_value<int, K3::base_string>& c) mutable  {
          shared_ptr<R_key_value<int, _Map<R_key_value<R_od_ok_tp<K3::base_string, int, double>,
          double>>>> __1;
          __1 = loc_build.lookup(R_key_value<int, _Map<R_key_value<R_od_ok_tp<K3::base_string, int,
          double>, double>>> {c.key, _Map<R_key_value<R_od_ok_tp<K3::base_string, int, double>,
          double>> {}});
          if (__1) {
            auto& lo = *(__1);
            return (lo.value).iterate(std::move([this,
            &c] (const R_key_value<R_od_ok_tp<K3::base_string, int, double>, double>& kv) mutable  {
              return loc_q_by_ncodt.insert_with(R_key_value<R_ck_nm_od_ok_tp<int, K3::base_string,
              K3::base_string, int, double>, double> {R_ck_nm_od_ok_tp<int, K3::base_string,
              K3::base_string, int, double> {c.key, c.value, (kv.key).od, (kv.key).ok, (kv.key).tp},
              kv.value}, std::bind(&__global_context::merge_q_by_ncodt_r, std::ref(*this), std::placeholders::_1));
            }));
          } else {
            return unit_t {};
          }
        }));
      }
      unit_t loc_rhs_peer_barrier(unit_t _)  {
        loc_rhs_done_cnt = loc_rhs_done_cnt + (1);
        if (loc_rhs_done_cnt == peers.size(unit_t {})) {
          print("Hash join RHS finished probe.");
          print("LI-OR-CS join finished customer probe.");
          (loc_q_by_ncodt.groupBy(std::move([this] (const R_key_value<R_ck_nm_od_ok_tp<int,
          K3::base_string, K3::base_string, int, double>, double>& v) mutable  {
            return index_by_hash(std::move(v.key));
          }), std::move([this] (_Collection<R_key_value<R_ck_nm_od_ok_tp<int, K3::base_string,
          K3::base_string, int, double>, double>> acc) mutable  {
            return [this, acc = std::move(acc)] (const R_key_value<R_ck_nm_od_ok_tp<int,
            K3::base_string, K3::base_string, int, double>, double>& v) mutable  {
              acc.insert(std::move(v));
              return std::move(acc);
            };
          }), _Collection<R_key_value<R_ck_nm_od_ok_tp<int, K3::base_string, K3::base_string, int,
          double>, double>> {})).iterate(std::move([this] (const R_key_value<int,
          _Collection<R_key_value<R_ck_nm_od_ok_tp<int, K3::base_string, K3::base_string, int,
          double>, double>>>& v) mutable  {
            shared_ptr<R_addr<Address>> __2;
            __2 = peers.at(std::move(v.key));
            if (__2) {
              auto& p = *(__2);
              auto d = std::make_shared<K3::ValDispatcher<_Collection<R_key_value<R_ck_nm_od_ok_tp<int,
              K3::base_string, K3::base_string, int, double>, double>>>>(v.value);
              __engine.send(p.addr, __loc_aggregate_tid, d);
              return unit_t {};
            } else {
              return error<unit_t>(unit_t {});
            }
          }));
          ignore(std::move(peers.iterate(std::move([this] (const R_addr<Address>& p) mutable  {
            auto d = std::make_shared<K3::ValDispatcher<unit_t>>(unit_t {});
            __engine.send(p.addr, __log_aggregate_peer_barrier_tid, d);
            return unit_t {};
          }))));
          auto d = std::make_shared<K3::ValDispatcher<unit_t>>(unit_t {});
          __engine.send(master, __loc_global_barrier_tid, d);
          return unit_t {};
        } else {
          return unit_t {};
        }
      }
      unit_t loc_rhs_scan(unit_t _)  {
        loc_lhs_done_cnt = loc_lhs_done_cnt + (1);
        if (loc_lhs_done_cnt == peers.size(unit_t {})) {
          ((customer.fold(std::move([this] (_Collection<R_key_value<int,
          K3::base_string>> acc) mutable  {
            return [this,
            acc = std::move(acc)] (const R_c_acctbal_c_address_c_comments_c_custkey_c_mktsegment_c_name_c_nationkey_c_phone<double,
            K3::base_string, K3::base_string, int, K3::base_string, K3::base_string, int,
            K3::base_string>& c) mutable  {
              acc.insert(R_key_value<int, K3::base_string> {c.c_custkey, c.c_name});
              return std::move(acc);
            };
          }), _Collection<R_key_value<int,
          K3::base_string>> {})).groupBy(std::move([this] (const R_key_value<int,
          K3::base_string>& v) mutable  {
            return index_by_hash(std::move(v.key));
          }), std::move([this] (_Collection<R_key_value<int, K3::base_string>> acc) mutable  {
            return [this, acc = std::move(acc)] (const R_key_value<int,
            K3::base_string>& v) mutable  {
              acc.insert(std::move(v));
              return std::move(acc);
            };
          }), _Collection<R_key_value<int,
          K3::base_string>> {})).iterate(std::move([this] (const R_key_value<int,
          _Collection<R_key_value<int, K3::base_string>>>& v) mutable  {
            shared_ptr<R_addr<Address>> __3;
            __3 = peers.at(std::move(v.key));
            if (__3) {
              auto& p = *(__3);
              auto d = std::make_shared<K3::ValDispatcher<_Collection<R_key_value<int,
              K3::base_string>>>>(v.value);
              __engine.send(p.addr, __loc_probe_rhs_tid, d);
              return unit_t {};
            } else {
              return error<unit_t>(unit_t {});
            }
          }));
          return ignore(std::move(peers.iterate(std::move([this] (const R_addr<Address>& p) mutable  {
            auto d = std::make_shared<K3::ValDispatcher<unit_t>>(unit_t {});
            __engine.send(p.addr, __loc_rhs_peer_barrier_tid, d);
            return unit_t {};
          }))));
        } else {
          return unit_t {};
        }
      }
      unit_t ready(unit_t _)  {
        nodes_ready_cnt = nodes_ready_cnt + (1);
        if (nodes_ready_cnt == peers.size(unit_t {})) {
          query_start_ms = now_int(unit_t {});
          auto d = std::make_shared<K3::ValDispatcher<unit_t>>(unit_t {});
          __engine.send(me, __lineitem_having_tid, d);
          return unit_t {};
        } else {
          return unit_t {};
        }
      }
      unit_t shutdown_(unit_t _)  {
        return haltEngine(unit_t {});
      }
      int loc_join_done_cnt;
      bool __loc_join_done_cnt_set__ = false;
      int loc_lhs_done_cnt;
      bool __loc_lhs_done_cnt_set__ = false;
      int loc_peer_build_done_cnt;
      bool __loc_peer_build_done_cnt_set__ = false;
      int loc_rhs_done_cnt;
      bool __loc_rhs_done_cnt_set__ = false;
      int nodes_ready_cnt;
      bool __nodes_ready_cnt_set__ = false;
      int query_done_cnt;
      bool __query_done_cnt_set__ = false;
      int query_elapsed_ms;
      bool __query_elapsed_ms_set__ = false;
      int query_end_ms;
      bool __query_end_ms_set__ = false;
      int query_start_ms;
      bool __query_start_ms_set__ = false;
      unit_t li_having_global_barrier(unit_t _)  {
        li_having_done_cnt = li_having_done_cnt + (1);
        if (li_having_done_cnt == peers.size(unit_t {})) {
          auto d = std::make_shared<K3::ValDispatcher<unit_t>>(unit_t {});
          __engine.send(me, __lineitem_orders_tid, d);
          return unit_t {};
        } else {
          return unit_t {};
        }
      }
      unit_t li_having_merge(const _Collection<R_key_value<int, double>>& partials)  {
        return partials.iterate(std::move([this] (const R_key_value<int, double>& v) mutable  {
          return [this] (const R_key_value<int, double>& v) mutable  {
            return li_having_result.insert_with(std::move(v),
            std::move([this] (const R_key_value<int, double>& a) mutable  {
              return [this, &a] (const R_key_value<int, double>& b) mutable  {
                return R_key_value<int, double> {a.key, [this] (const double& a) mutable  {
                  return [this, &a] (const double& b) mutable  {
                    return a + b;
                  };
                }(std::move(a.value))(std::move(b.value))};
              };
            }));
          }(std::move(v));
        }));
      }
      unit_t li_having_peer_barrier(unit_t _)  {
        li_having_peer_done_cnt = li_having_peer_done_cnt + (1);
        if (li_having_peer_done_cnt == peers.size(unit_t {})) {
          [this] (const _Map<R_key_value<int, double>>& result) mutable  {
            print("LI shuffle done.");
            li_having_result = result.filter(std::move([this] (const R_key_value<int,
            double>& okq) mutable  {
              return (okq.value) > (300);
            }));
            return unit_t {};
          }(li_having_result);
          auto d = std::make_shared<K3::ValDispatcher<unit_t>>(unit_t {});
          __engine.send(master, __li_having_global_barrier_tid, d);
          return unit_t {};
        } else {
          return unit_t {};
        }
      }
      unit_t li_having_scan(unit_t _)  {
        ((lineitem.groupBy(std::move([this] (const R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax<K3::base_string,
        K3::base_string, double, double, int, K3::base_string, int, int, double, K3::base_string,
        K3::base_string, K3::base_string, K3::base_string, K3::base_string, int,
        double>& li) mutable  {
          return li.l_orderkey;
        }), std::move([this] (const double& acc) mutable  {
          return [this,
          &acc] (const R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax<K3::base_string,
          K3::base_string, double, double, int, K3::base_string, int, int, double, K3::base_string,
          K3::base_string, K3::base_string, K3::base_string, K3::base_string, int,
          double>& li) mutable  {
            return acc + (li.l_quantity);
          };
        }), 0.0)).groupBy(std::move([this] (const R_key_value<int, double>& v) mutable  {
          return index_by_hash(std::move(v.key));
        }), std::move([this] (_Collection<R_key_value<int, double>> acc) mutable  {
          return [this, acc = std::move(acc)] (const R_key_value<int, double>& v) mutable  {
            acc.insert(std::move(v));
            return std::move(acc);
          };
        }), _Collection<R_key_value<int,
        double>> {})).iterate(std::move([this] (const R_key_value<int, _Collection<R_key_value<int,
        double>>>& v) mutable  {
          shared_ptr<R_addr<Address>> __4;
          __4 = peers.at(std::move(v.key));
          if (__4) {
            auto& p = *(__4);
            auto d = std::make_shared<K3::ValDispatcher<_Collection<R_key_value<int,
            double>>>>(v.value);
            __engine.send(p.addr, __li_having_merge_tid, d);
            return unit_t {};
          } else {
            return error<unit_t>(unit_t {});
          }
        }));
        return ignore(std::move(peers.iterate(std::move([this] (const R_addr<Address>& p) mutable  {
          auto d = std::make_shared<K3::ValDispatcher<unit_t>>(unit_t {});
          __engine.send(p.addr, __li_having_peer_barrier_tid, d);
          return unit_t {};
        }))));
      }
      int li_having_done_cnt;
      bool __li_having_done_cnt_set__ = false;
      int li_having_peer_done_cnt;
      bool __li_having_peer_done_cnt_set__ = false;
      unit_t initDecls(unit_t _)  {
        if (!(__loc_aggregate_done_cnt_set__)) {
          loc_aggregate_done_cnt = 0;
          __loc_aggregate_done_cnt_set__ = true;
        }
        if (!(__master_set__)) {
          master = make_address("127.0.0.1", 40000);
          __master_set__ = true;
        }
        if (!(__loc_join_done_cnt_set__)) {
          loc_join_done_cnt = 0;
          __loc_join_done_cnt_set__ = true;
        }
        if (!(__loc_lhs_done_cnt_set__)) {
          loc_lhs_done_cnt = 0;
          __loc_lhs_done_cnt_set__ = true;
        }
        if (!(__loc_peer_build_done_cnt_set__)) {
          loc_peer_build_done_cnt = 0;
          __loc_peer_build_done_cnt_set__ = true;
        }
        if (!(__loc_rhs_done_cnt_set__)) {
          loc_rhs_done_cnt = 0;
          __loc_rhs_done_cnt_set__ = true;
        }
        if (!(__nodes_ready_cnt_set__)) {
          nodes_ready_cnt = 0;
          __nodes_ready_cnt_set__ = true;
        }
        if (!(__query_done_cnt_set__)) {
          query_done_cnt = 0;
          __query_done_cnt_set__ = true;
        }
        if (!(__query_elapsed_ms_set__)) {
          query_elapsed_ms = 0;
          __query_elapsed_ms_set__ = true;
        }
        if (!(__query_end_ms_set__)) {
          query_end_ms = 0;
          __query_end_ms_set__ = true;
        }
        if (!(__query_start_ms_set__)) {
          query_start_ms = 0;
          __query_start_ms_set__ = true;
        }
        if (!(__li_having_done_cnt_set__)) {
          li_having_done_cnt = 0;
          __li_having_done_cnt_set__ = true;
        }
        if (!(__li_having_peer_done_cnt_set__)) {
          li_having_peer_done_cnt = 0;
          __li_having_peer_done_cnt_set__ = true;
        }
        return unit_t {};
      }
      std::map<std::string, std::string> __prettify()  {
        std::map<std::string, std::string> result;
        result["li_having_peer_done_cnt"] = K3::prettify_int(li_having_peer_done_cnt);
        result["li_having_done_cnt"] = K3::prettify_int(li_having_done_cnt);
        result["query_start_ms"] = K3::prettify_int(query_start_ms);
        result["query_end_ms"] = K3::prettify_int(query_end_ms);
        result["query_elapsed_ms"] = K3::prettify_int(query_elapsed_ms);
        result["query_done_cnt"] = K3::prettify_int(query_done_cnt);
        result["nodes_ready_cnt"] = K3::prettify_int(nodes_ready_cnt);
        result["loc_rhs_done_cnt"] = K3::prettify_int(loc_rhs_done_cnt);
        result["loc_peer_build_done_cnt"] = K3::prettify_int(loc_peer_build_done_cnt);
        result["loc_lhs_done_cnt"] = K3::prettify_int(loc_lhs_done_cnt);
        result["loc_join_done_cnt"] = K3::prettify_int(loc_join_done_cnt);
        result["supplierFiles"] = K3::prettify_collection(supplierFiles,
        [] (R_path<K3::base_string> x)   {
          return K3::prettify_record(x, [] (R_path<K3::base_string> x)   {
            ostringstream oss;
            oss << ("{");
            oss << std::string("path:") << K3::prettify_string(x.path);
            oss << ("}");
            return string_impl(oss.str());
          });
        });
        result["regionFiles"] = K3::prettify_collection(regionFiles,
        [] (R_path<K3::base_string> x)   {
          return K3::prettify_record(x, [] (R_path<K3::base_string> x)   {
            ostringstream oss;
            oss << ("{");
            oss << std::string("path:") << K3::prettify_string(x.path);
            oss << ("}");
            return string_impl(oss.str());
          });
        });
        result["partsuppFiles"] = K3::prettify_collection(partsuppFiles,
        [] (R_path<K3::base_string> x)   {
          return K3::prettify_record(x, [] (R_path<K3::base_string> x)   {
            ostringstream oss;
            oss << ("{");
            oss << std::string("path:") << K3::prettify_string(x.path);
            oss << ("}");
            return string_impl(oss.str());
          });
        });
        result["partFiles"] = K3::prettify_collection(partFiles, [] (R_path<K3::base_string> x)   {
          return K3::prettify_record(x, [] (R_path<K3::base_string> x)   {
            ostringstream oss;
            oss << ("{");
            oss << std::string("path:") << K3::prettify_string(x.path);
            oss << ("}");
            return string_impl(oss.str());
          });
        });
        result["ordersFiles"] = K3::prettify_collection(ordersFiles,
        [] (R_path<K3::base_string> x)   {
          return K3::prettify_record(x, [] (R_path<K3::base_string> x)   {
            ostringstream oss;
            oss << ("{");
            oss << std::string("path:") << K3::prettify_string(x.path);
            oss << ("}");
            return string_impl(oss.str());
          });
        });
        result["nationFiles"] = K3::prettify_collection(nationFiles,
        [] (R_path<K3::base_string> x)   {
          return K3::prettify_record(x, [] (R_path<K3::base_string> x)   {
            ostringstream oss;
            oss << ("{");
            oss << std::string("path:") << K3::prettify_string(x.path);
            oss << ("}");
            return string_impl(oss.str());
          });
        });
        result["master"] = K3::prettify_address(master);
        result["loc_aggregate_done_cnt"] = K3::prettify_int(loc_aggregate_done_cnt);
        result["lineitemFiles"] = K3::prettify_collection(lineitemFiles,
        [] (R_path<K3::base_string> x)   {
          return K3::prettify_record(x, [] (R_path<K3::base_string> x)   {
            ostringstream oss;
            oss << ("{");
            oss << std::string("path:") << K3::prettify_string(x.path);
            oss << ("}");
            return string_impl(oss.str());
          });
        });
        result["li_having_result"] = K3::prettify_collection(li_having_result, [] (R_key_value<int,
        double> x)   {
          return K3::prettify_record(x, [] (R_key_value<int, double> x)   {
            ostringstream oss;
            oss << ("{");
            oss << std::string("key:") << K3::prettify_int(x.key);
            oss << ("|");
            oss << std::string("value:") << K3::prettify_real(x.value);
            oss << ("}");
            return string_impl(oss.str());
          });
        });
        result["dataFiles"] = K3::prettify_collection(dataFiles, [] (R_path<K3::base_string> x)   {
          return K3::prettify_record(x, [] (R_path<K3::base_string> x)   {
            ostringstream oss;
            oss << ("{");
            oss << std::string("path:") << K3::prettify_string(x.path);
            oss << ("}");
            return string_impl(oss.str());
          });
        });
        result["customerFiles"] = K3::prettify_collection(customerFiles,
        [] (R_path<K3::base_string> x)   {
          return K3::prettify_record(x, [] (R_path<K3::base_string> x)   {
            ostringstream oss;
            oss << ("{");
            oss << std::string("path:") << K3::prettify_string(x.path);
            oss << ("}");
            return string_impl(oss.str());
          });
        });
        result["loc_q_by_ncodt"] = K3::prettify_collection(loc_q_by_ncodt,
        [] (R_key_value<R_ck_nm_od_ok_tp<int, K3::base_string, K3::base_string, int, double>,
        double> x)   {
          return K3::prettify_record(x, [] (R_key_value<R_ck_nm_od_ok_tp<int, K3::base_string,
          K3::base_string, int, double>, double> x)   {
            ostringstream oss;
            oss << ("{");
            oss << std::string("key:") << K3::prettify_record(x.key, [] (R_ck_nm_od_ok_tp<int,
            K3::base_string, K3::base_string, int, double> x)   {
              ostringstream oss;
              oss << ("{");
              oss << std::string("nm:") << K3::prettify_string(x.nm);
              oss << ("|");
              oss << std::string("ck:") << K3::prettify_int(x.ck);
              oss << ("|");
              oss << std::string("ok:") << K3::prettify_int(x.ok);
              oss << ("|");
              oss << std::string("od:") << K3::prettify_string(x.od);
              oss << ("|");
              oss << std::string("tp:") << K3::prettify_real(x.tp);
              oss << ("}");
              return string_impl(oss.str());
            });
            oss << ("|");
            oss << std::string("value:") << K3::prettify_real(x.value);
            oss << ("}");
            return string_impl(oss.str());
          });
        });
        result["loc_build"] = K3::prettify_collection(loc_build, [] (R_key_value<int,
        _Map<R_key_value<R_od_ok_tp<K3::base_string, int, double>, double>>> x)   {
          return K3::prettify_record(x, [] (R_key_value<int,
          _Map<R_key_value<R_od_ok_tp<K3::base_string, int, double>, double>>> x)   {
            ostringstream oss;
            oss << ("{");
            oss << std::string("key:") << K3::prettify_int(x.key);
            oss << ("|");
            oss << std::string("value:") << K3::prettify_collection(x.value,
            [] (R_key_value<R_od_ok_tp<K3::base_string, int, double>, double> x)   {
              return K3::prettify_record(x, [] (R_key_value<R_od_ok_tp<K3::base_string, int,
              double>, double> x)   {
                ostringstream oss;
                oss << ("{");
                oss << std::string("key:") << K3::prettify_record(x.key,
                [] (R_od_ok_tp<K3::base_string, int, double> x)   {
                  ostringstream oss;
                  oss << ("{");
                  oss << std::string("ok:") << K3::prettify_int(x.ok);
                  oss << ("|");
                  oss << std::string("od:") << K3::prettify_string(x.od);
                  oss << ("|");
                  oss << std::string("tp:") << K3::prettify_real(x.tp);
                  oss << ("}");
                  return string_impl(oss.str());
                });
                oss << ("|");
                oss << std::string("value:") << K3::prettify_real(x.value);
                oss << ("}");
                return string_impl(oss.str());
              });
            });
            oss << ("}");
            return string_impl(oss.str());
          });
        });
        result["lo_odtq_by_ck"] = K3::prettify_collection(lo_odtq_by_ck, [] (R_key_value<int,
        _Map<R_key_value<R_od_ok_tp<K3::base_string, int, double>, double>>> x)   {
          return K3::prettify_record(x, [] (R_key_value<int,
          _Map<R_key_value<R_od_ok_tp<K3::base_string, int, double>, double>>> x)   {
            ostringstream oss;
            oss << ("{");
            oss << std::string("key:") << K3::prettify_int(x.key);
            oss << ("|");
            oss << std::string("value:") << K3::prettify_collection(x.value,
            [] (R_key_value<R_od_ok_tp<K3::base_string, int, double>, double> x)   {
              return K3::prettify_record(x, [] (R_key_value<R_od_ok_tp<K3::base_string, int,
              double>, double> x)   {
                ostringstream oss;
                oss << ("{");
                oss << std::string("key:") << K3::prettify_record(x.key,
                [] (R_od_ok_tp<K3::base_string, int, double> x)   {
                  ostringstream oss;
                  oss << ("{");
                  oss << std::string("ok:") << K3::prettify_int(x.ok);
                  oss << ("|");
                  oss << std::string("od:") << K3::prettify_string(x.od);
                  oss << ("|");
                  oss << std::string("tp:") << K3::prettify_real(x.tp);
                  oss << ("}");
                  return string_impl(oss.str());
                });
                oss << ("|");
                oss << std::string("value:") << K3::prettify_real(x.value);
                oss << ("}");
                return string_impl(oss.str());
              });
            });
            oss << ("}");
            return string_impl(oss.str());
          });
        });
        result["q18_peer_result"] = K3::prettify_collection(q18_peer_result,
        [] (R_key_value<R_ck_nm_od_ok_tp<int, K3::base_string, K3::base_string, int, double>,
        double> x)   {
          return K3::prettify_record(x, [] (R_key_value<R_ck_nm_od_ok_tp<int, K3::base_string,
          K3::base_string, int, double>, double> x)   {
            ostringstream oss;
            oss << ("{");
            oss << std::string("key:") << K3::prettify_record(x.key, [] (R_ck_nm_od_ok_tp<int,
            K3::base_string, K3::base_string, int, double> x)   {
              ostringstream oss;
              oss << ("{");
              oss << std::string("nm:") << K3::prettify_string(x.nm);
              oss << ("|");
              oss << std::string("ck:") << K3::prettify_int(x.ck);
              oss << ("|");
              oss << std::string("ok:") << K3::prettify_int(x.ok);
              oss << ("|");
              oss << std::string("od:") << K3::prettify_string(x.od);
              oss << ("|");
              oss << std::string("tp:") << K3::prettify_real(x.tp);
              oss << ("}");
              return string_impl(oss.str());
            });
            oss << ("|");
            oss << std::string("value:") << K3::prettify_real(x.value);
            oss << ("}");
            return string_impl(oss.str());
          });
        });
        result["orders"] = K3::prettify_collection(orders,
        [] (R_o_clerk_o_comments_o_custkey_o_orderdate_o_orderkey_o_orderpriority_o_orderstatus_o_shippriority_o_totalprice<K3::base_string,
        K3::base_string, int, K3::base_string, int, K3::base_string, K3::base_string, int,
        double> x)   {
          return K3::prettify_record(x,
          [] (R_o_clerk_o_comments_o_custkey_o_orderdate_o_orderkey_o_orderpriority_o_orderstatus_o_shippriority_o_totalprice<K3::base_string,
          K3::base_string, int, K3::base_string, int, K3::base_string, K3::base_string, int,
          double> x)   {
            ostringstream oss;
            oss << ("{");
            oss << std::string("o_orderkey:") << K3::prettify_int(x.o_orderkey);
            oss << ("|");
            oss << std::string("o_custkey:") << K3::prettify_int(x.o_custkey);
            oss << ("|");
            oss << std::string("o_orderstatus:") << K3::prettify_string(x.o_orderstatus);
            oss << ("|");
            oss << std::string("o_totalprice:") << K3::prettify_real(x.o_totalprice);
            oss << ("|");
            oss << std::string("o_orderdate:") << K3::prettify_string(x.o_orderdate);
            oss << ("|");
            oss << std::string("o_orderpriority:") << K3::prettify_string(x.o_orderpriority);
            oss << ("|");
            oss << std::string("o_clerk:") << K3::prettify_string(x.o_clerk);
            oss << ("|");
            oss << std::string("o_shippriority:") << K3::prettify_int(x.o_shippriority);
            oss << ("|");
            oss << std::string("o_comments:") << K3::prettify_string(x.o_comments);
            oss << ("}");
            return string_impl(oss.str());
          });
        });
        result["customer"] = K3::prettify_collection(customer,
        [] (R_c_acctbal_c_address_c_comments_c_custkey_c_mktsegment_c_name_c_nationkey_c_phone<double,
        K3::base_string, K3::base_string, int, K3::base_string, K3::base_string, int,
        K3::base_string> x)   {
          return K3::prettify_record(x,
          [] (R_c_acctbal_c_address_c_comments_c_custkey_c_mktsegment_c_name_c_nationkey_c_phone<double,
          K3::base_string, K3::base_string, int, K3::base_string, K3::base_string, int,
          K3::base_string> x)   {
            ostringstream oss;
            oss << ("{");
            oss << std::string("c_custkey:") << K3::prettify_int(x.c_custkey);
            oss << ("|");
            oss << std::string("c_name:") << K3::prettify_string(x.c_name);
            oss << ("|");
            oss << std::string("c_address:") << K3::prettify_string(x.c_address);
            oss << ("|");
            oss << std::string("c_nationkey:") << K3::prettify_int(x.c_nationkey);
            oss << ("|");
            oss << std::string("c_phone:") << K3::prettify_string(x.c_phone);
            oss << ("|");
            oss << std::string("c_acctbal:") << K3::prettify_real(x.c_acctbal);
            oss << ("|");
            oss << std::string("c_mktsegment:") << K3::prettify_string(x.c_mktsegment);
            oss << ("|");
            oss << std::string("c_comments:") << K3::prettify_string(x.c_comments);
            oss << ("}");
            return string_impl(oss.str());
          });
        });
        result["lineitem"] = K3::prettify_collection(lineitem,
        [] (R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax<K3::base_string,
        K3::base_string, double, double, int, K3::base_string, int, int, double, K3::base_string,
        K3::base_string, K3::base_string, K3::base_string, K3::base_string, int, double> x)   {
          return K3::prettify_record(x,
          [] (R_l_comments_l_commitdate_l_discount_l_extendedprice_l_linenumber_l_linestatus_l_orderkey_l_partkey_l_quantity_l_receiptdate_l_returnflag_l_shipdate_l_shipinstruct_l_shipmode_l_suppkey_l_tax<K3::base_string,
          K3::base_string, double, double, int, K3::base_string, int, int, double, K3::base_string,
          K3::base_string, K3::base_string, K3::base_string, K3::base_string, int, double> x)   {
            ostringstream oss;
            oss << ("{");
            oss << std::string("l_orderkey:") << K3::prettify_int(x.l_orderkey);
            oss << ("|");
            oss << std::string("l_partkey:") << K3::prettify_int(x.l_partkey);
            oss << ("|");
            oss << std::string("l_suppkey:") << K3::prettify_int(x.l_suppkey);
            oss << ("|");
            oss << std::string("l_linenumber:") << K3::prettify_int(x.l_linenumber);
            oss << ("|");
            oss << std::string("l_quantity:") << K3::prettify_real(x.l_quantity);
            oss << ("|");
            oss << std::string("l_extendedprice:") << K3::prettify_real(x.l_extendedprice);
            oss << ("|");
            oss << std::string("l_discount:") << K3::prettify_real(x.l_discount);
            oss << ("|");
            oss << std::string("l_tax:") << K3::prettify_real(x.l_tax);
            oss << ("|");
            oss << std::string("l_returnflag:") << K3::prettify_string(x.l_returnflag);
            oss << ("|");
            oss << std::string("l_linestatus:") << K3::prettify_string(x.l_linestatus);
            oss << ("|");
            oss << std::string("l_shipdate:") << K3::prettify_string(x.l_shipdate);
            oss << ("|");
            oss << std::string("l_commitdate:") << K3::prettify_string(x.l_commitdate);
            oss << ("|");
            oss << std::string("l_receiptdate:") << K3::prettify_string(x.l_receiptdate);
            oss << ("|");
            oss << std::string("l_shipinstruct:") << K3::prettify_string(x.l_shipinstruct);
            oss << ("|");
            oss << std::string("l_shipmode:") << K3::prettify_string(x.l_shipmode);
            oss << ("|");
            oss << std::string("l_comments:") << K3::prettify_string(x.l_comments);
            oss << ("}");
            return string_impl(oss.str());
          });
        });
        result["role"] = K3::prettify_string(role);
        result["args"] = K3::prettify_tuple(args);
        result["peers"] = K3::prettify_collection(peers, [] (R_addr<Address> x)   {
          return K3::prettify_record(x, [] (R_addr<Address> x)   {
            ostringstream oss;
            oss << ("{");
            oss << std::string("addr:") << K3::prettify_address(x.addr);
            oss << ("}");
            return string_impl(oss.str());
          });
        });
        result["me"] = K3::prettify_address(me);
        return result;
      }
      void __patch(std::map<std::string, std::string> bindings)  {
        if (bindings.count("li_having_peer_done_cnt") > (0)) {
          do_patch(bindings["li_having_peer_done_cnt"], li_having_peer_done_cnt);
          __li_having_peer_done_cnt_set__ = true;
        }
        if (bindings.count("li_having_done_cnt") > (0)) {
          do_patch(bindings["li_having_done_cnt"], li_having_done_cnt);
          __li_having_done_cnt_set__ = true;
        }
        if (bindings.count("query_start_ms") > (0)) {
          do_patch(bindings["query_start_ms"], query_start_ms);
          __query_start_ms_set__ = true;
        }
        if (bindings.count("query_end_ms") > (0)) {
          do_patch(bindings["query_end_ms"], query_end_ms);
          __query_end_ms_set__ = true;
        }
        if (bindings.count("query_elapsed_ms") > (0)) {
          do_patch(bindings["query_elapsed_ms"], query_elapsed_ms);
          __query_elapsed_ms_set__ = true;
        }
        if (bindings.count("query_done_cnt") > (0)) {
          do_patch(bindings["query_done_cnt"], query_done_cnt);
          __query_done_cnt_set__ = true;
        }
        if (bindings.count("nodes_ready_cnt") > (0)) {
          do_patch(bindings["nodes_ready_cnt"], nodes_ready_cnt);
          __nodes_ready_cnt_set__ = true;
        }
        if (bindings.count("loc_rhs_done_cnt") > (0)) {
          do_patch(bindings["loc_rhs_done_cnt"], loc_rhs_done_cnt);
          __loc_rhs_done_cnt_set__ = true;
        }
        if (bindings.count("loc_peer_build_done_cnt") > (0)) {
          do_patch(bindings["loc_peer_build_done_cnt"], loc_peer_build_done_cnt);
          __loc_peer_build_done_cnt_set__ = true;
        }
        if (bindings.count("loc_lhs_done_cnt") > (0)) {
          do_patch(bindings["loc_lhs_done_cnt"], loc_lhs_done_cnt);
          __loc_lhs_done_cnt_set__ = true;
        }
        if (bindings.count("loc_join_done_cnt") > (0)) {
          do_patch(bindings["loc_join_done_cnt"], loc_join_done_cnt);
          __loc_join_done_cnt_set__ = true;
        }
        if (bindings.count("supplierFiles") > (0)) {
          do_patch(bindings["supplierFiles"], supplierFiles);
        }
        if (bindings.count("regionFiles") > (0)) {
          do_patch(bindings["regionFiles"], regionFiles);
        }
        if (bindings.count("partsuppFiles") > (0)) {
          do_patch(bindings["partsuppFiles"], partsuppFiles);
        }
        if (bindings.count("partFiles") > (0)) {
          do_patch(bindings["partFiles"], partFiles);
        }
        if (bindings.count("ordersFiles") > (0)) {
          do_patch(bindings["ordersFiles"], ordersFiles);
        }
        if (bindings.count("nationFiles") > (0)) {
          do_patch(bindings["nationFiles"], nationFiles);
        }
        if (bindings.count("master") > (0)) {
          do_patch(bindings["master"], master);
          __master_set__ = true;
        }
        if (bindings.count("loc_aggregate_done_cnt") > (0)) {
          do_patch(bindings["loc_aggregate_done_cnt"], loc_aggregate_done_cnt);
          __loc_aggregate_done_cnt_set__ = true;
        }
        if (bindings.count("lineitemFiles") > (0)) {
          do_patch(bindings["lineitemFiles"], lineitemFiles);
        }
        if (bindings.count("li_having_result") > (0)) {
          do_patch(bindings["li_having_result"], li_having_result);
        }
        if (bindings.count("dataFiles") > (0)) {
          do_patch(bindings["dataFiles"], dataFiles);
        }
        if (bindings.count("customerFiles") > (0)) {
          do_patch(bindings["customerFiles"], customerFiles);
        }
        if (bindings.count("loc_q_by_ncodt") > (0)) {
          do_patch(bindings["loc_q_by_ncodt"], loc_q_by_ncodt);
        }
        if (bindings.count("loc_build") > (0)) {
          do_patch(bindings["loc_build"], loc_build);
        }
        if (bindings.count("lo_odtq_by_ck") > (0)) {
          do_patch(bindings["lo_odtq_by_ck"], lo_odtq_by_ck);
        }
        if (bindings.count("q18_peer_result") > (0)) {
          do_patch(bindings["q18_peer_result"], q18_peer_result);
        }
        if (bindings.count("orders") > (0)) {
          do_patch(bindings["orders"], orders);
        }
        if (bindings.count("customer") > (0)) {
          do_patch(bindings["customer"], customer);
        }
        if (bindings.count("lineitem") > (0)) {
          do_patch(bindings["lineitem"], lineitem);
        }
        if (bindings.count("role") > (0)) {
          do_patch(bindings["role"], role);
        }
        if (bindings.count("args") > (0)) {
          do_patch(bindings["args"], args);
        }
        if (bindings.count("peers") > (0)) {
          do_patch(bindings["peers"], peers);
        }
        if (bindings.count("me") > (0)) {
          do_patch(bindings["me"], me);
        }
      }
      void __dispatch(int trigger_id, void* payload)  {
        dispatch_table[trigger_id](payload);
      }
  protected:
      std::map<int, std::function<void(void*)>> dispatch_table;
};
int __global_context::__lineitem_having_tid;
int __global_context::__lineitem_orders_tid;
int __global_context::__lineitem_orders_customer_tid;
int __global_context::__loc_aggregate_tid;
int __global_context::__log_aggregate_peer_barrier_tid;
int __global_context::__start_tid;
int __global_context::__finished_tid;
int __global_context::__hello_tid;
int __global_context::__load_all_tid;
int __global_context::__loc_build_lhs_tid;
int __global_context::__loc_global_barrier_tid;
int __global_context::__loc_lhs_peer_barrier_tid;
int __global_context::__loc_lhs_scan_tid;
int __global_context::__loc_probe_rhs_tid;
int __global_context::__loc_rhs_peer_barrier_tid;
int __global_context::__loc_rhs_scan_tid;
int __global_context::__ready_tid;
int __global_context::__shutdown_tid;
int __global_context::__li_having_global_barrier_tid;
int __global_context::__li_having_merge_tid;
int __global_context::__li_having_peer_barrier_tid;
int __global_context::__li_having_scan_tid;
int main(int argc, char** argv)  {
  __global_context::__lineitem_having_tid = 0;
  __global_context::__lineitem_orders_tid = 1;
  __global_context::__lineitem_orders_customer_tid = 2;
  __global_context::__loc_aggregate_tid = 3;
  __global_context::__log_aggregate_peer_barrier_tid = 4;
  __global_context::__start_tid = 5;
  __global_context::__finished_tid = 6;
  __global_context::__hello_tid = 7;
  __global_context::__load_all_tid = 8;
  __global_context::__loc_build_lhs_tid = 9;
  __global_context::__loc_global_barrier_tid = 10;
  __global_context::__loc_lhs_peer_barrier_tid = 11;
  __global_context::__loc_lhs_scan_tid = 12;
  __global_context::__loc_probe_rhs_tid = 13;
  __global_context::__loc_rhs_peer_barrier_tid = 14;
  __global_context::__loc_rhs_scan_tid = 15;
  __global_context::__ready_tid = 16;
  __global_context::__shutdown_tid = 17;
  __global_context::__li_having_global_barrier_tid = 18;
  __global_context::__li_having_merge_tid = 19;
  __global_context::__li_having_peer_barrier_tid = 20;
  __global_context::__li_having_scan_tid = 21;
  __k3_context::__trigger_names[__global_context::__li_having_scan_tid] = "li_having_scan";
  __k3_context::__trigger_names[__global_context::__li_having_peer_barrier_tid] = "li_having_peer_barrier";
  __k3_context::__trigger_names[__global_context::__li_having_merge_tid] = "li_having_merge";
  __k3_context::__trigger_names[__global_context::__li_having_global_barrier_tid] = "li_having_global_barrier";
  __k3_context::__trigger_names[__global_context::__shutdown_tid] = "shutdown_";
  __k3_context::__trigger_names[__global_context::__ready_tid] = "ready";
  __k3_context::__trigger_names[__global_context::__loc_rhs_scan_tid] = "loc_rhs_scan";
  __k3_context::__trigger_names[__global_context::__loc_rhs_peer_barrier_tid] = "loc_rhs_peer_barrier";
  __k3_context::__trigger_names[__global_context::__loc_probe_rhs_tid] = "loc_probe_rhs";
  __k3_context::__trigger_names[__global_context::__loc_lhs_scan_tid] = "loc_lhs_scan";
  __k3_context::__trigger_names[__global_context::__loc_lhs_peer_barrier_tid] = "loc_lhs_peer_barrier";
  __k3_context::__trigger_names[__global_context::__loc_global_barrier_tid] = "loc_global_barrier";
  __k3_context::__trigger_names[__global_context::__loc_build_lhs_tid] = "loc_build_lhs";
  __k3_context::__trigger_names[__global_context::__load_all_tid] = "load_all";
  __k3_context::__trigger_names[__global_context::__hello_tid] = "hello";
  __k3_context::__trigger_names[__global_context::__finished_tid] = "finished";
  __k3_context::__trigger_names[__global_context::__start_tid] = "start";
  __k3_context::__trigger_names[__global_context::__log_aggregate_peer_barrier_tid] = "log_aggregate_peer_barrier";
  __k3_context::__trigger_names[__global_context::__loc_aggregate_tid] = "loc_aggregate";
  __k3_context::__trigger_names[__global_context::__lineitem_orders_customer_tid] = "lineitem_orders_customer";
  __k3_context::__trigger_names[__global_context::__lineitem_orders_tid] = "lineitem_orders";
  __k3_context::__trigger_names[__global_context::__lineitem_having_tid] = "lineitem_having";
  __k3_context::__clonable_dispatchers[__global_context::__li_having_scan_tid] = make_shared<ValDispatcher<unit_t>>();
  __k3_context::__clonable_dispatchers[__global_context::__li_having_peer_barrier_tid] = make_shared<ValDispatcher<unit_t>>();
  __k3_context::__clonable_dispatchers[__global_context::__li_having_merge_tid] = make_shared<ValDispatcher<_Collection<R_key_value<int,
  double>>>>();
  __k3_context::__clonable_dispatchers[__global_context::__li_having_global_barrier_tid] = make_shared<ValDispatcher<unit_t>>();
  __k3_context::__clonable_dispatchers[__global_context::__shutdown_tid] = make_shared<ValDispatcher<unit_t>>();
  __k3_context::__clonable_dispatchers[__global_context::__ready_tid] = make_shared<ValDispatcher<unit_t>>();
  __k3_context::__clonable_dispatchers[__global_context::__loc_rhs_scan_tid] = make_shared<ValDispatcher<unit_t>>();
  __k3_context::__clonable_dispatchers[__global_context::__loc_rhs_peer_barrier_tid] = make_shared<ValDispatcher<unit_t>>();
  __k3_context::__clonable_dispatchers[__global_context::__loc_probe_rhs_tid] = make_shared<ValDispatcher<_Collection<R_key_value<int,
  K3::base_string>>>>();
  __k3_context::__clonable_dispatchers[__global_context::__loc_lhs_scan_tid] = make_shared<ValDispatcher<unit_t>>();
  __k3_context::__clonable_dispatchers[__global_context::__loc_lhs_peer_barrier_tid] = make_shared<ValDispatcher<unit_t>>();
  __k3_context::__clonable_dispatchers[__global_context::__loc_global_barrier_tid] = make_shared<ValDispatcher<unit_t>>();
  __k3_context::__clonable_dispatchers[__global_context::__loc_build_lhs_tid] = make_shared<ValDispatcher<_Collection<R_key_value<int,
  _Map<R_key_value<R_od_ok_tp<K3::base_string, int, double>, double>>>>>>();
  __k3_context::__clonable_dispatchers[__global_context::__load_all_tid] = make_shared<ValDispatcher<unit_t>>();
  __k3_context::__clonable_dispatchers[__global_context::__hello_tid] = make_shared<ValDispatcher<unit_t>>();
  __k3_context::__clonable_dispatchers[__global_context::__finished_tid] = make_shared<ValDispatcher<unit_t>>();
  __k3_context::__clonable_dispatchers[__global_context::__start_tid] = make_shared<ValDispatcher<unit_t>>();
  __k3_context::__clonable_dispatchers[__global_context::__log_aggregate_peer_barrier_tid] = make_shared<ValDispatcher<unit_t>>();
  __k3_context::__clonable_dispatchers[__global_context::__loc_aggregate_tid] = make_shared<ValDispatcher<_Collection<R_key_value<R_ck_nm_od_ok_tp<int,
  K3::base_string, K3::base_string, int, double>, double>>>>();
  __k3_context::__clonable_dispatchers[__global_context::__lineitem_orders_customer_tid] = make_shared<ValDispatcher<unit_t>>();
  __k3_context::__clonable_dispatchers[__global_context::__lineitem_orders_tid] = make_shared<ValDispatcher<unit_t>>();
  __k3_context::__clonable_dispatchers[__global_context::__lineitem_having_tid] = make_shared<ValDispatcher<unit_t>>();
  Options opt;
  if (opt.parse(argc, argv)) {
    return 0;
  }
  runProgram<__global_context>(opt.peer_strings, opt.simulation, opt.log_level);
}
