#include "infra/Schema.hpp"
//---------------------------------------------------------------------------
// (c) 2023 Thomas Neumann
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
namespace saneql {
//---------------------------------------------------------------------------
string Type::getName() const
// Get the name (for error reporting)
{
   switch (tag) {
      case Unknown: return "unknown";
      case Bool: return "boolean";
      case Integer: return "integer";
      case Decimal: return "decimal";
      case Char: return "char";
      case Varchar: return "varchar";
      case Text: return "text";
      case Date: return "date";
      case Interval: return "interval";
   }
   __builtin_unreachable();
}
//---------------------------------------------------------------------------
void Schema::createTable(std::string name, std::initializer_list<Column> columns)
// Create a table
{
   auto& t = tables[name];
   t.columns.assign(columns.begin(), columns.end());
}
//---------------------------------------------------------------------------
void Schema::createTPCH()
// Create the TPC-H schema for experiments
{
   createTable("part", {
      {"p_partkey", Type::getInteger()}, 
      {"p_name", Type::getVarchar(55)}, 
      {"p_mfgr", Type::getChar(25)}, 
      {"p_brand", Type::getChar(10)}, 
      {"p_type", Type::getVarchar(25)}, 
      {"p_size", Type::getInteger()}, 
      {"p_container", Type::getChar(10)}, 
      {"p_retailprice", Type::getDecimal(12, 2)}, 
      {"p_comment", Type::getVarchar(23)}});
   createTable("region", {
      {"r_regionkey", Type::getInteger()}, 
      {"r_name", Type::getChar(25)}, 
      {"r_comment", Type::getVarchar(152)}});
   createTable("nation", {
      {"n_nationkey", Type::getInteger()}, 
      {"n_name", Type::getChar(25)}, 
      {"n_regionkey", Type::getInteger()}, 
      {"n_comment", Type::getVarchar(152)}});
   createTable("supplier", {
      {"s_suppkey", Type::getInteger()}, 
      {"s_name", Type::getChar(25)}, 
      {"s_address", Type::getVarchar(40)}, 
      {"s_nationkey", Type::getInteger()}, 
      {"s_phone", Type::getChar(15)}, 
      {"s_acctbal", Type::getDecimal(12, 2)}, 
      {"s_comment", Type::getVarchar(101)}});
   createTable("partsupp", {
      {"ps_partkey", Type::getInteger()}, 
      {"ps_suppkey", Type::getInteger()}, 
      {"ps_availqty", Type::getInteger()}, 
      {"ps_supplycost", Type::getDecimal(12, 2)}, 
      {"ps_comment", Type::getVarchar(199)}});
   createTable("customer", {
      {"c_custkey", Type::getInteger()}, 
      {"c_name", Type::getVarchar(25)}, 
      {"c_address", Type::getVarchar(40)}, 
      {"c_nationkey", Type::getInteger()}, 
      {"c_phone", Type::getChar(15)}, 
      {"c_acctbal", Type::getDecimal(12, 2)}, 
      {"c_mktsegment", Type::getChar(10)}, 
      {"c_comment", Type::getVarchar(117)}});
   createTable("orders", {
      {"o_orderkey", Type::getInteger()}, 
      {"o_custkey", Type::getInteger()}, 
      {"o_orderstatus", Type::getChar(1)}, 
      {"o_totalprice", Type::getDecimal(12, 2)}, 
      {"o_orderdate", Type::getDate()}, 
      {"o_orderpriority", Type::getChar(15)}, 
      {"o_clerk", Type::getChar(15)}, 
      {"o_shippriority", Type::getInteger()}, 
      {"o_comment", Type::getVarchar(79)}});
   createTable("lineitem", {
      {"l_orderkey", Type::getInteger()}, 
      {"l_partkey", Type::getInteger()}, 
      {"l_suppkey", Type::getInteger()}, 
      {"l_linenumber", Type::getInteger()}, 
      {"l_quantity", Type::getDecimal(12, 2)}, 
      {"l_extendedprice", Type::getDecimal(12, 2)}, 
      {"l_discount", Type::getDecimal(12, 2)}, 
      {"l_tax", Type::getDecimal(12, 2)}, 
      {"l_returnflag", Type::getChar(1)}, 
      {"l_linestatus", Type::getChar(1)}, 
      {"l_shipdate", Type::getDate()}, 
      {"l_commitdate", Type::getDate()}, 
      {"l_receiptdate", Type::getDate()}, 
      {"l_shipinstruct", Type::getChar(25)}, 
      {"l_shipmode", Type::getChar(10)}, 
      {"l_comment", Type::getVarchar(44)}});
}
//---------------------------------------------------------------------------
void Schema::createTPCC()
// Create the TPC-C schema for vmcache
{
   createTable("warehouse", {
      {"w_id", Type::getInteger(), true}, 
      {"w_name", Type::getVarchar(10)}, 
      {"w_street_1", Type::getVarchar(20)}, 
      {"w_street_2", Type::getVarchar(20)}, 
      {"w_city", Type::getVarchar(20)}, 
      {"w_state", Type::getVarchar(2)}, 
      {"w_zip", Type::getVarchar(9)}, 
      {"w_tax", Type::getDecimal(0, 0)}, 
      {"w_ytd", Type::getDecimal(0, 0)}});
   createTable("district", {
      {"d_w_id", Type::getInteger(), true}, 
      {"d_id", Type::getInteger(), true}, 
      {"d_name", Type::getVarchar(10)}, 
      {"d_street_1", Type::getVarchar(20)}, 
      {"d_street_2", Type::getVarchar(20)}, 
      {"d_city", Type::getVarchar(20)}, 
      {"d_state", Type::getVarchar(2)}, 
      {"d_zip", Type::getVarchar(9)}, 
      {"d_tax", Type::getDecimal(0, 0)}, 
      {"d_ytd", Type::getDecimal(0, 0)}, 
      {"d_next_o_id", Type::getInteger()}});
   createTable("customer", {
      {"c_w_id", Type::getInteger(), true}, 
      {"c_d_id", Type::getInteger(), true}, 
      {"c_id", Type::getInteger(), true},
      {"c_first", Type::getVarchar(16)},
      {"c_middle", Type::getVarchar(2)},
      {"c_last", Type::getVarchar(16)},
      {"c_street_1", Type::getVarchar(20)},
      {"c_street_2", Type::getVarchar(20)},
      {"c_city", Type::getVarchar(20)},
      {"c_state", Type::getVarchar(2)},
      {"c_zip", Type::getVarchar(9)},
      {"c_phone", Type::getVarchar(16)},
      {"c_since", Type::getDate()},
      {"c_credit", Type::getVarchar(2)},
      {"c_credit_lim", Type::getDecimal(0, 0)},
      {"c_discount", Type::getDecimal(0, 0)},
      {"c_balance", Type::getDecimal(0, 0)},
      {"c_ytd_payment", Type::getDecimal(0, 0)},
      {"c_payment_cnt", Type::getDecimal(0, 0)},
      {"c_delivery_cnt", Type::getDecimal(0, 0)},
      {"c_data", Type::getVarchar(500)}});
   createTable("customer_wdl", {
      {"c_w_id", Type::getInteger(), true},
      {"c_d_id", Type::getInteger(), true},
      {"c_last", Type::getVarchar(16), true},
      {"c_first", Type::getVarchar(16), true},
      {"c_id", Type::getInteger()}});
   createTable("history", {
      {"thread_id", Type::getInteger(), true},
      {"h_pk", Type::getInteger(), true},
      {"h_c_id", Type::getInteger()},
      {"h_c_d_id", Type::getInteger()},
      {"h_c_w_id", Type::getInteger()},
      {"h_d_id", Type::getInteger()},
      {"h_w_id", Type::getInteger()},
      {"h_date", Type::getDate()},
      {"h_amount", Type::getDecimal(0, 0)},
      {"h_data", Type::getVarchar(24)}});
   createTable("order", {
      {"o_w_id", Type::getInteger(), true},
      {"o_d_id", Type::getInteger(), true},
      {"o_id", Type::getInteger(), true},
      {"o_c_id", Type::getInteger()},
      {"o_entry_d", Type::getDate()},
      {"o_carrier_id", Type::getInteger()},
      {"o_ol_cnt", Type::getDecimal(0, 0)},
      {"o_all_local", Type::getDecimal(0, 0)}});
   createTable("order_wdc", {
      {"o_w_id", Type::getInteger(), true},
      {"o_d_id", Type::getInteger(), true},
      {"o_c_id", Type::getInteger(), true},
      {"o_id", Type::getInteger(), true}});
   createTable("orderline", {
      {"ol_w_id", Type::getInteger(), true},
      {"ol_d_id", Type::getInteger(), true},
      {"ol_o_id", Type::getInteger(), true},
      {"ol_number", Type::getInteger(), true},
      {"ol_i_id", Type::getInteger()},
      {"ol_supply_w_id", Type::getInteger()},
      {"ol_delivery_d", Type::getDate()},
      {"ol_quantity", Type::getDecimal(0, 0)},
      {"ol_amount", Type::getDecimal(0, 0)},
      {"ol_dist_info", Type::getVarchar(24)}});
   createTable("item", {
      {"i_id", Type::getInteger(), true},
      {"i_im_id", Type::getInteger()},
      {"i_name", Type::getVarchar(24)},
      {"i_price", Type::getDecimal(0, 0)},
      {"i_data", Type::getVarchar(50)}});
   createTable("stock", {
      {"s_w_id", Type::getInteger(), true},
      {"s_i_id", Type::getInteger(), true},
      {"s_quantity", Type::getDecimal(0, 0)},
      {"s_dist_01", Type::getVarchar(24)},
      {"s_dist_02", Type::getVarchar(24)},
      {"s_dist_03", Type::getVarchar(24)},
      {"s_dist_04", Type::getVarchar(24)},
      {"s_dist_05", Type::getVarchar(24)},
      {"s_dist_06", Type::getVarchar(24)},
      {"s_dist_07", Type::getVarchar(24)},
      {"s_dist_08", Type::getVarchar(24)},
      {"s_dist_09", Type::getVarchar(24)},
      {"s_dist_10", Type::getVarchar(24)},
      {"s_ytd", Type::getDecimal(0, 0)},
      {"s_order_cnt", Type::getDecimal(0, 0)},
      {"s_remote_cnt", Type::getDecimal(0, 0)},
      {"s_data", Type::getVarchar(50)}});
}
//---------------------------------------------------------------------------
void Schema::populateSchema()
// Create initial schema objects
{
   // For now we hard-code TPC-H for experiments
   createTPCH();
   // For now we hard-code TPC-C for vmcache
   createTPCC();
}
//---------------------------------------------------------------------------
const Schema::Table* Schema::lookupTable(const std::string& name) const
// Check if a table exists in the schema
{
   auto iter = tables.find(name);
   if (iter != tables.end())
      return &(iter->second);
   return nullptr;
}
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
