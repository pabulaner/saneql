#pragma once

#include <memory>

#include "vmcache/vmcache.hpp"
#include "vmcache/tpcc/Schema.hpp"
#include "vmcache/tpch/Schema.hpp"

namespace adapter {

class Database {
    private:
    /// The database instance
    static std::unique_ptr<Database> instance;

    public:
    /// Get the database instance
    static Database* getInstance();

    /// TPCC
    vmcacheAdapter<warehouse_t> warehouse;
    vmcacheAdapter<district_t> district;
    vmcacheAdapter<customer_t> customer;
    vmcacheAdapter<customer_wdl_t> customerwdl;
    vmcacheAdapter<history_t> history;
    vmcacheAdapter<neworder_t> neworder;
    vmcacheAdapter<order_t> order;
    vmcacheAdapter<order_wdc_t> order_wdc;
    vmcacheAdapter<orderline_t> orderline;
    vmcacheAdapter<item_t> item;
    vmcacheAdapter<stock_t> stock;

    // TPCH
    vmcacheAdapter<part_tpch_t> part_tpch;    
    vmcacheAdapter<region_tpch_t> region_tpch;
    vmcacheAdapter<nation_tpch_t> nation_tpch;
    vmcacheAdapter<supplier_tpch_t> supplier_tpch;
    vmcacheAdapter<partsupp_tpch_t> partsupp_tpch;
    vmcacheAdapter<customer_tpch_t> customer_tpch;
    vmcacheAdapter<lineitem_tpch_t> lineitem_tpch;
    
    private:
    /// The tpcc workload
    TPCCWorkload<vmcacheAdapter> tpcc;

    /// The constructor
    Database(u32 threadCount, u32 warehouseCount);

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;
};

} // namespace adapter