#include "Database.hpp"

#include <unordered_map>
#include <vector>
#include <tuple>
#include <algorithm>

#include "vmcache/tpch/data/csv.hpp"
#include "vmcache/tpch/data/table-reader.hpp"
#include "vmcache/tpch/data/tpch.hpp"

using namespace adapter;

namespace adapter {

std::unique_ptr<Database> Database::instance = nullptr;

Database* Database::getInstance() {
    if (instance.get() == nullptr) {
        u32 threadCount = envOr("THREADS", 1);
        u32 warehouseCount = envOr("DATASIZE", 3);
        std::string tpchPath = envOr("TPCHPATH", "/opt/tpch");

        // use new due to private constructor
        Database* ptr = new Database(threadCount, warehouseCount, tpchPath);
        instance = std::unique_ptr<Database>(ptr);
    }

    return instance.get();
}

Database::Database(u32 threadCount, u32 warehouseCount, const std::string& tpchPath) 
    : tpcc(warehouse, district, customer, customerwdl, history, neworder, order, order_wdc, orderline, item, stock, true, warehouseCount, true) 
{
    if (bm.useExmap) {
        struct sigaction action;
        action.sa_flags = SA_SIGINFO;
        action.sa_sigaction = handleSEGFAULT;
        if (sigaction(SIGSEGV, &action, NULL) == -1) {
            perror("sigusr: sigaction");
            exit(1);
        }
    }

    std::cout << "Loading TPCC..." << std::endl;
    
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

    std::cout << "Finished loading TPCC!" << std::endl;
    std::cout << "Loading TPCH..." << std::endl;

    auto fullPath = [&](const std::string& table) {
        return tpchPath + "/" + table + ".tbl";
    };

    {
        tpch::part::import part(fullPath("part"));
        auto partRows = part.read();

        for (size_t i = 0; i < partRows; i++) {
            part_tpch.insert({
                get<0>(part.outputs).items[i],
            }, {
                get<1>(part.outputs).items[i],
                get<2>(part.outputs).items[i],
                get<3>(part.outputs).items[i],
                get<4>(part.outputs).items[i],
                get<5>(part.outputs).items[i],
                get<6>(part.outputs).items[i],
                get<7>(part.outputs).items[i],
                get<8>(part.outputs).items[i],
            });
        }
    }
    {
        tpch::region::import region(fullPath("region"));
        auto regionRows = region.read();
        for (size_t i = 0; i < regionRows; i++) {
            region_tpch.insert({
                get<0>(region.outputs).items[i],
            }, {
                get<1>(region.outputs).items[i],
                get<2>(region.outputs).items[i],
            });
        }
    }
    {
        tpch::nation::import nation(fullPath("nation"));
        auto nationRows = nation.read();
        for (size_t i = 0; i < nationRows; i++) {
            nation_tpch.insert({
                get<0>(nation.outputs).items[i],
            }, {
                get<1>(nation.outputs).items[i],
                get<2>(nation.outputs).items[i],
                get<3>(nation.outputs).items[i],
            });
        }
    }
    {
        tpch::supplier::import supplier(fullPath("supplier"));
        auto supplierRows = supplier.read();
        for (size_t i = 0; i < supplierRows; i++) {
            supplier_tpch.insert({
                get<0>(supplier.outputs).items[i],
            }, {
                get<1>(supplier.outputs).items[i],
                get<2>(supplier.outputs).items[i],
                get<3>(supplier.outputs).items[i],
                get<4>(supplier.outputs).items[i],
                get<5>(supplier.outputs).items[i],
                get<6>(supplier.outputs).items[i],
            });
        }
    }
        {
        tpch::partsupp::import partsupp(fullPath("partsupp"));
        auto partsuppRows = partsupp.read();
        for (size_t i = 0; i < partsuppRows; i++) {
            partsupp_tpch.insert({
                get<0>(partsupp.outputs).items[i],
            }, {
                get<1>(partsupp.outputs).items[i],
                get<2>(partsupp.outputs).items[i],
                get<3>(partsupp.outputs).items[i],
                get<4>(partsupp.outputs).items[i],
            });
        }
    }
    {
        tpch::customer::import customer(fullPath("customer"));
        auto customerRows = customer.read();
        for (size_t i = 0; i < customerRows; i++) {
            customer_tpch.insert({
                get<0>(customer.outputs).items[i],
            }, {
                get<1>(customer.outputs).items[i],
                get<2>(customer.outputs).items[i],
                get<3>(customer.outputs).items[i],
                get<4>(customer.outputs).items[i],
                get<5>(customer.outputs).items[i],
                get<6>(customer.outputs).items[i],
                get<7>(customer.outputs).items[i],
            });
        }
    }
    {
        tpch::orders::import orders(fullPath("orders"));
        auto ordersRows = orders.read();
        for (size_t i = 0; i < ordersRows; i++) {
            orders_tpch.insert({
                (Integer) get<0>(orders.outputs).items[i],
            }, {
                get<1>(orders.outputs).items[i],
                get<2>(orders.outputs).items[i],
                get<3>(orders.outputs).items[i],
                get<4>(orders.outputs).items[i].value,
                get<5>(orders.outputs).items[i],
                get<6>(orders.outputs).items[i],
                get<7>(orders.outputs).items[i],
                get<8>(orders.outputs).items[i],
            });
        }
    }
    {
        tpch::lineitem::import lineitem(fullPath("lineitem"));
        auto lineitemRows = lineitem.read();
        for (size_t i = 0; i < lineitemRows; i++) {
            lineitem_tpch.insert({
                (Integer) get<0>(lineitem.outputs).items[i],
            }, {
                get<1>(lineitem.outputs).items[i],
                get<2>(lineitem.outputs).items[i],
                get<3>(lineitem.outputs).items[i],
                get<4>(lineitem.outputs).items[i],
                get<5>(lineitem.outputs).items[i],
                get<6>(lineitem.outputs).items[i],
                get<7>(lineitem.outputs).items[i],
                get<8>(lineitem.outputs).items[i],
                get<9>(lineitem.outputs).items[i],
                get<10>(lineitem.outputs).items[i].value,
                get<11>(lineitem.outputs).items[i].value,
                get<12>(lineitem.outputs).items[i].value,
                get<13>(lineitem.outputs).items[i],
                get<14>(lineitem.outputs).items[i],
                get<15>(lineitem.outputs).items[i],
            });
        }
    }

    std::cout << "Finished loading TPCH!" << std::endl;
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

int main(int argc, char** argv) {
    Database* db = Database::getInstance();
    #include "resource/query.hpp"
}