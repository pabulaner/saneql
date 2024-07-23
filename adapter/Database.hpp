#pragma once

#include <memory>

#include "vmcache/vmcache.hpp"

namespace adapter {

class Database {
    private:
    /// The database instance
    static std::unique_ptr<Database> instance;

    public:
    /// Get the database instance
    static Database* getInstance();

    /// The vmcache adapters
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
    
    private:
    /// The tpcc workload
    TPCCWorkload<vmcacheAdapter> tpcc;

    /// The constructor
    Database(u32 threadCount, u32 warehouseCount);

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;
};

} // namespace adapter