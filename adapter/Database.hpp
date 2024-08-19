#pragma once

#include <memory>

#include "vmcache/vmcache.hpp"
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

std::unique_ptr<Database> Database::instance = nullptr;

Database* Database::getInstance() {
    if (instance.get() == nullptr) {
        u32 threadCount = envOr("THREADS", 1);
        u32 warehouseCount = envOr("DATASIZE", 1);

        Database* ptr = new Database(threadCount, warehouseCount);
        instance = std::unique_ptr<Database>(ptr);
    }

    return instance.get();
}

Database::Database(u32 threadCount, u32 warehouseCount) 
    : tpcc(warehouse, district, customer, customerwdl, history, neworder, order, order_wdc, orderline, item, stock, true, warehouseCount, true) 
{
    if (get_bm()->useExmap) {
        struct sigaction action;
        action.sa_flags = SA_SIGINFO;
        action.sa_sigaction = handleSEGFAULT;
        if (sigaction(SIGSEGV, &action, NULL) == -1) {
            perror("sigusr: sigaction");
            exit(1);
        }
    }

    tpcc.loadItem();
    tpcc.loadWarehouse();

    parallel_for(1, warehouseCount+1, threadCount, [&](uint64_t worker, uint64_t begin, uint64_t end) {
        for (Integer w_id=begin; w_id<end; w_id++) {
            tpcc.loadStock(w_id);
            tpcc.loadDistrinct(w_id);
            for (Integer d_id = 1; d_id <= 10; d_id++) {
                tpcc.loadCustomer(w_id, d_id);
                tpcc.loadOrders(w_id, d_id);
            }
        }
    });
}

} // namespace adapter

template<typename... Args>
struct hash<tuple<Args...>> {
    inline size_t operator()(const tuple<Args...> &args) const {
        return fold_tuple(args, 0ul, [](const size_t acc, const auto &val) -> uint64_t {
          hash<typename decay<decltype(val)>::type> hasher;
            return hasher(val) ^ acc;
        });
    }

   private:
    template<typename T, typename F, unsigned I = 0, typename... Tuple>
    constexpr inline static T fold_tuple(const tuple<Tuple...> &tuple, T acc_or_init, const F &fn) {
        if constexpr (I == sizeof...(Args)) {
            return acc_or_init;
        } else {
            return fold_tuple<T, F, I + 1, Tuple...>(tuple, fn(acc_or_init, get<I>(tuple)), fn);
        }
    }
};