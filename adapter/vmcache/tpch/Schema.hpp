#pragma once
#include "../Types.hpp"
// -------------------------------------------------------------------------------------

struct part_tpch_t {
   static constexpr int id = 0;
   struct Key {
      static constexpr int id = 0;
      Integer p_partkey;
   };

   Varchar<55> p_name;
   Varchar<25> p_mfgr;
   Varchar<10> p_brand;
   Varchar<25> p_type;
   Integer p_size;
   Varchar<10> p_container;
   Numeric p_retailprice;
   Varchar<23> p_comment;

   template <class T>
   static unsigned foldKey(uint8_t* out, const T& record)
   {
      unsigned pos = 0;
      pos += fold(out + pos, record.p_partkey);
      return pos;
   }
   template <class T>
   static unsigned unfoldKey(const uint8_t* in, T& record)
   {
      unsigned pos = 0;
      pos += unfold(in + pos, record.p_partkey);
      return pos;
   }
   static constexpr unsigned maxFoldLength() { return 0 + sizeof(Key::p_partkey); };
};

struct region_tpch_t {
   static constexpr int id = 1;
   struct Key {
      static constexpr int id = 1;
      Integer r_region;
   };

   Varchar<25> r_name;
   Varchar<152> r_comment;

   template <class T>
   static unsigned foldKey(uint8_t* out, const T& record)
   {
      unsigned pos = 0;
      pos += fold(out + pos, record.r_region);
      return pos;
   }
   template <class T>
   static unsigned unfoldKey(const uint8_t* in, T& record)
   {
      unsigned pos = 0;
      pos += unfold(in + pos, record.r_region);
      return pos;
   }
   static constexpr unsigned maxFoldLength() { return 0 + sizeof(Key::r_region); };
};

struct nation_tpch_t {
   static constexpr int id = 2;
   struct Key {
      static constexpr int id = 2;
      Integer n_nationkey;
   };

   Varchar<25> n_name;
   Integer n_regionkey;
   Varchar<152> n_comment;

   template <class T>
   static unsigned foldKey(uint8_t* out, const T& record)
   {
      unsigned pos = 0;
      pos += fold(out + pos, record.n_nationkey);
      return pos;
   }
   template <class T>
   static unsigned unfoldKey(const uint8_t* in, T& record)
   {
      unsigned pos = 0;
      pos += unfold(in + pos, record.n_nationkey);
      return pos;
   }
   static constexpr unsigned maxFoldLength() { return 0 + sizeof(Key::n_nationkey); };
};

struct supplier_tpch_t {
   static constexpr int id = 3;
   struct Key {
      static constexpr int id = 3;
      Integer s_suppkey;
   };

   Varchar<25> s_name;
   Varchar<40> s_address;
   Integer s_nationkey;
   Varchar<15> s_phone;
   Numeric s_acctbal;
   Varchar<101> s_comment;

   template <class T>
   static unsigned foldKey(uint8_t* out, const T& record)
   {
      unsigned pos = 0;
      pos += fold(out + pos, record.s_suppkey);
      return pos;
   }
   template <class T>
   static unsigned unfoldKey(const uint8_t* in, T& record)
   {
      unsigned pos = 0;
      pos += unfold(in + pos, record.s_suppkey);
      return pos;
   }
   static constexpr unsigned maxFoldLength() { return 0 + sizeof(Key::s_suppkey); };
};

struct partsupp_tpch_t {
   static constexpr int id = 4;
   struct Key {
      static constexpr int id = 4;
      Integer ps_partkey;
   };

   Integer ps_suppkey;
   Integer ps_availqty;
   Numeric ps_supplycost;
   Varchar<199> ps_comment;

   template <class T>
   static unsigned foldKey(uint8_t* out, const T& record)
   {
      unsigned pos = 0;
      pos += fold(out + pos, record.ps_partkey);
      return pos;
   }
   template <class T>
   static unsigned unfoldKey(const uint8_t* in, T& record)
   {
      unsigned pos = 0;
      pos += unfold(in + pos, record.ps_partkey);
      return pos;
   }
   static constexpr unsigned maxFoldLength() { return 0 + sizeof(Key::ps_partkey); };
};

struct customer_tpch_t {
   static constexpr int id = 5;
   struct Key {
      static constexpr int id = 5;
      Integer c_custkey;
   };

   Varchar<25> c_name;
   Varchar<40> c_address;
   Integer c_nationkey;
   Varchar<15> c_phone;
   Numeric c_acctbal;
   Varchar<10> c_mktsegment;
   Varchar<117> c_comment;

   template <class T>
   static unsigned foldKey(uint8_t* out, const T& record)
   {
      unsigned pos = 0;
      pos += fold(out + pos, record.c_custkey);
      return pos;
   }
   template <class T>
   static unsigned unfoldKey(const uint8_t* in, T& record)
   {
      unsigned pos = 0;
      pos += unfold(in + pos, record.c_custkey);
      return pos;
   }
   static constexpr unsigned maxFoldLength() { return 0 + sizeof(Key::c_custkey); };
};

struct orders_tpch_t {
   static constexpr int id = 6;
   struct Key {
      static constexpr int id = 6;
      Integer o_orderkey;
   };

   Integer o_custkey;
   Varchar<1> o_orderstatus;
   Numeric o_totalprice;
   Timestamp o_orderdate;
   Varchar<15> o_orderpriority;
   Varchar<15> o_clerk;
   Integer o_shippriority;
   Varchar<79> o_comment;

   template <class T>
   static unsigned foldKey(uint8_t* out, const T& record)
   {
      unsigned pos = 0;
      pos += fold(out + pos, record.o_orderkey);
      return pos;
   }
   template <class T>
   static unsigned unfoldKey(const uint8_t* in, T& record)
   {
      unsigned pos = 0;
      pos += unfold(in + pos, record.o_orderkey);
      return pos;
   }
   static constexpr unsigned maxFoldLength() { return 0 + sizeof(Key::o_orderkey); };
};

struct lineitem_tpch_t {
   static constexpr int id = 7;
   struct Key {
      static constexpr int id = 7;
      Integer l_orderkey;
   };

   Integer l_partkey;
   Integer l_suppkey;
   Integer l_linenumber;
   Numeric l_quantity;
   Numeric l_extendedprice;
   Numeric l_discount;
   Numeric l_tax;
   Varchar<1> l_returnflag;
   Varchar<1> l_linestatus;
   Timestamp l_shipdate;
   Timestamp l_commitdate;
   Timestamp l_receiptdate;
   Varchar<25> l_shipinstruct;
   Varchar<10> l_shipmode;
   Varchar<44> l_comment;

   template <class T>
   static unsigned foldKey(uint8_t* out, const T& record)
   {
      unsigned pos = 0;
      pos += fold(out + pos, record.l_orderkey);
      return pos;
   }
   template <class T>
   static unsigned unfoldKey(const uint8_t* in, T& record)
   {
      unsigned pos = 0;
      pos += unfold(in + pos, record.l_orderkey);
      return pos;
   }
   static constexpr unsigned maxFoldLength() { return 0 + sizeof(Key::l_orderkey); };
};