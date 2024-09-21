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
   createTable("part_tpch", {
      {"p_partkey", Type::getInteger(), true}, 
      {"p_name", Type::getVarchar(55), false}, 
      {"p_mfgr", Type::getVarchar(25), false}, 
      {"p_brand", Type::getVarchar(10), false}, 
      {"p_type", Type::getVarchar(25), false}, 
      {"p_size", Type::getInteger(), false}, 
      {"p_container", Type::getVarchar(10), false}, 
      {"p_retailprice", Type::getDecimal(0, 0), false}, 
      {"p_comment", Type::getVarchar(23), false}});
   createTable("region_tpch", {
      {"r_regionkey", Type::getInteger(), true}, 
      {"r_name", Type::getVarchar(25), false}, 
      {"r_comment", Type::getVarchar(152), false}});
   createTable("nation_tpch", {
      {"n_nationkey", Type::getInteger(), true}, 
      {"n_name", Type::getVarchar(25), false}, 
      {"n_regionkey", Type::getInteger(), false}, 
      {"n_comment", Type::getVarchar(152), false}});
   createTable("supplier_tpch", {
      {"s_suppkey", Type::getInteger(), true}, 
      {"s_name", Type::getVarchar(25), false}, 
      {"s_address", Type::getVarchar(40), false}, 
      {"s_nationkey", Type::getInteger(), false}, 
      {"s_phone", Type::getVarchar(15), false}, 
      {"s_acctbal", Type::getDecimal(0, 0), false}, 
      {"s_comment", Type::getVarchar(101), false}});
   createTable("partsupp_tpch", {
      {"ps_partkey", Type::getInteger(), true}, 
      {"ps_suppkey", Type::getInteger(), true}, 
      {"ps_availqty", Type::getInteger(), false}, 
      {"ps_supplycost", Type::getDecimal(0, 0), false}, 
      {"ps_comment", Type::getVarchar(199), false}});
   createTable("customer_tpch", {
      {"c_custkey", Type::getInteger(), true}, 
      {"c_name", Type::getVarchar(25), false}, 
      {"c_address", Type::getVarchar(40), false}, 
      {"c_nationkey", Type::getInteger(), false}, 
      {"c_phone", Type::getVarchar(15), false}, 
      {"c_acctbal", Type::getDecimal(0, 0), false}, 
      {"c_mktsegment", Type::getVarchar(10), false}, 
      {"c_comment", Type::getVarchar(117), false}});
   createTable("orders_tpch", {
      {"o_orderkey", Type::getInteger(), true}, 
      {"o_custkey", Type::getInteger(), true}, 
      {"o_orderstatus", Type::getVarchar(1), false}, 
      {"o_totalprice", Type::getDecimal(0, 0), false}, 
      {"o_orderdate", Type::getDate(), false}, 
      {"o_orderpriority", Type::getVarchar(15), false}, 
      {"o_clerk", Type::getVarchar(15), false}, 
      {"o_shippriority", Type::getInteger(), false}, 
      {"o_comment", Type::getVarchar(79), false}});
   createTable("lineitem_tpch", {
      {"l_orderkey", Type::getInteger(), true}, 
      {"l_partkey", Type::getInteger(), true}, 
      {"l_suppkey", Type::getInteger(), true}, 
      {"l_linenumber", Type::getInteger(), false}, 
      {"l_quantity", Type::getDecimal(0, 0), false}, 
      {"l_extendedprice", Type::getDecimal(0, 0), false}, 
      {"l_discount", Type::getDecimal(0, 0), false}, 
      {"l_tax", Type::getDecimal(0, 0), false}, 
      {"l_returnflag", Type::getVarchar(1), false}, 
      {"l_linestatus", Type::getVarchar(1), false}, 
      {"l_shipdate", Type::getDate(), false}, 
      {"l_commitdate", Type::getDate(), false}, 
      {"l_receiptdate", Type::getDate(), false}, 
      {"l_shipinstruct", Type::getVarchar(25), false}, 
      {"l_shipmode", Type::getVarchar(10), false}, 
      {"l_comment", Type::getVarchar(44), false}});
}
//---------------------------------------------------------------------------
void Schema::createTPCC()
// Create the TPC-C schema for vmcache
{
   createTable("warehouse", {
      {"w_id", Type::getInteger(), true}, 
      {"w_name", Type::getVarchar(10), false}, 
      {"w_street_1", Type::getVarchar(20), false}, 
      {"w_street_2", Type::getVarchar(20), false}, 
      {"w_city", Type::getVarchar(20), false}, 
      {"w_state", Type::getVarchar(2), false}, 
      {"w_zip", Type::getVarchar(9), false}, 
      {"w_tax", Type::getDecimal(0, 0), false}, 
      {"w_ytd", Type::getDecimal(0, 0), false}});
   createTable("district", {
      {"d_w_id", Type::getInteger(), true}, 
      {"d_id", Type::getInteger(), true}, 
      {"d_name", Type::getVarchar(10), false}, 
      {"d_street_1", Type::getVarchar(20), false}, 
      {"d_street_2", Type::getVarchar(20), false}, 
      {"d_city", Type::getVarchar(20), false}, 
      {"d_state", Type::getVarchar(2), false}, 
      {"d_zip", Type::getVarchar(9), false}, 
      {"d_tax", Type::getDecimal(0, 0), false}, 
      {"d_ytd", Type::getDecimal(0, 0), false}, 
      {"d_next_o_id", Type::getInteger(), false}});
   createTable("customer", {
      {"c_w_id", Type::getInteger(), true}, 
      {"c_d_id", Type::getInteger(), true}, 
      {"c_id", Type::getInteger(), true},
      {"c_first", Type::getVarchar(16), false},
      {"c_middle", Type::getVarchar(2), false},
      {"c_last", Type::getVarchar(16), false},
      {"c_street_1", Type::getVarchar(20), false},
      {"c_street_2", Type::getVarchar(20), false},
      {"c_city", Type::getVarchar(20), false},
      {"c_state", Type::getVarchar(2), false},
      {"c_zip", Type::getVarchar(9), false},
      {"c_phone", Type::getVarchar(16), false},
      {"c_since", Type::getDate(), false},
      {"c_credit", Type::getVarchar(2), false},
      {"c_credit_lim", Type::getDecimal(0, 0), false},
      {"c_discount", Type::getDecimal(0, 0), false},
      {"c_balance", Type::getDecimal(0, 0), false},
      {"c_ytd_payment", Type::getDecimal(0, 0), false},
      {"c_payment_cnt", Type::getDecimal(0, 0), false},
      {"c_delivery_cnt", Type::getDecimal(0, 0), false},
      {"c_data", Type::getVarchar(500), false}});
   createTable("customer_wdl", {
      {"c_w_id", Type::getInteger(), true},
      {"c_d_id", Type::getInteger(), true},
      {"c_last", Type::getVarchar(16), true},
      {"c_first", Type::getVarchar(16), true},
      {"c_id", Type::getInteger(), false}});
   createTable("history", {
      {"thread_id", Type::getInteger(), true},
      {"h_pk", Type::getInteger(), true},
      {"h_c_id", Type::getInteger(), false},
      {"h_c_d_id", Type::getInteger(), false},
      {"h_c_w_id", Type::getInteger(), false},
      {"h_d_id", Type::getInteger(), false},
      {"h_w_id", Type::getInteger(), false},
      {"h_date", Type::getDate(), false},
      {"h_amount", Type::getDecimal(0, 0), false},
      {"h_data", Type::getVarchar(24), false}});
   createTable("order", {
      {"o_w_id", Type::getInteger(), true},
      {"o_d_id", Type::getInteger(), true},
      {"o_id", Type::getInteger(), true},
      {"o_c_id", Type::getInteger(), false},
      {"o_entry_d", Type::getDate(), false},
      {"o_carrier_id", Type::getInteger(), false},
      {"o_ol_cnt", Type::getDecimal(0, 0), false},
      {"o_all_local", Type::getDecimal(0, 0), false}});
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
      {"ol_i_id", Type::getInteger(), false},
      {"ol_supply_w_id", Type::getInteger(), false},
      {"ol_delivery_d", Type::getDate(), false},
      {"ol_quantity", Type::getDecimal(0, 0), false},
      {"ol_amount", Type::getDecimal(0, 0), false},
      {"ol_dist_info", Type::getVarchar(24), false}});
   createTable("item", {
      {"i_id", Type::getInteger(), true},
      {"i_im_id", Type::getInteger(), false},
      {"i_name", Type::getVarchar(24), false},
      {"i_price", Type::getDecimal(0, 0), false},
      {"i_data", Type::getVarchar(50), false}});
   createTable("stock", {
      {"s_w_id", Type::getInteger(), true},
      {"s_i_id", Type::getInteger(), true},
      {"s_quantity", Type::getDecimal(0, 0), false},
      {"s_dist_01", Type::getVarchar(24), false},
      {"s_dist_02", Type::getVarchar(24), false},
      {"s_dist_03", Type::getVarchar(24), false},
      {"s_dist_04", Type::getVarchar(24), false},
      {"s_dist_05", Type::getVarchar(24), false},
      {"s_dist_06", Type::getVarchar(24), false},
      {"s_dist_07", Type::getVarchar(24), false},
      {"s_dist_08", Type::getVarchar(24), false},
      {"s_dist_09", Type::getVarchar(24), false},
      {"s_dist_10", Type::getVarchar(24), false},
      {"s_ytd", Type::getDecimal(0, 0), false},
      {"s_order_cnt", Type::getDecimal(0, 0), false},
      {"s_remote_cnt", Type::getDecimal(0, 0), false},
      {"s_data", Type::getVarchar(50), false}});
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
