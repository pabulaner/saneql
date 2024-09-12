#include "Database.hpp"

#include <map>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <algorithm>

#include "StringUtil.hpp"
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
    // queries sorted by optimization and by name
    std::map<std::string, std::map<std::string, std::function<void(Database*)>>> queries;

    #include "resource/query.hpp"

    bool run = true;
    while (run) {
        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string_view> params = sutil::split(input, ' ');
        
        if (params.size() == 0) {
            continue;
        }

        if (params[0] == "exit") {
            run = false;
        } else if (params[0] == "help") {
            std::cout << "Commands: help = print help" << std::endl;
            std::cout << "          exit = exit the program" << std::endl;
            std::cout << "          run [--file opt/name] --repeat number = runs the provided files (queries) a number of times" << std::endl;
        } else if (params[0] == "run") {
            bool file = false;
            bool repeat = false;

            std::vector<std::string_view> fileValues;
            size_t repeatValue = 1;

            for (size_t i = 1; i < params.size(); i++) {
                if (params[i] == "--file") {
                    files = true;
                } else if (params[i] == "--repeat") {
                    repeat = true;
                } else if (file) {
                    files = false;
                    fileValues.push_back(params[i]);
                } else if (repeat) {
                    repeat = false;
                    repeatValue = std::atoi(params[i]);

                    if (repeatValue == 0) {
                        std::cout << "Invalid repeat value" << std::endl;
                        continue;
                    }
                } else {
                    std::cout << "Invalid syntax" << std::endl;
                    continue;
                }
            }

            if (files || repeat) {
                std::cout << "Invalid syntax" << std::endl;
                continue;
            }

            for (auto& file : fileValues) {
                std::vector<std::string_view> optAndName = sutil::split(file, '/');

                if (optAndName.size() != 2) {
                    std::cout << "Invalid file name " << file << std::endl;
                    continue;
                }

                std::string_view opt = optAndName[0];
                std::string_view name = optAndName[1];

                bool allOpts = opt == "*";
                bool allNames = name == "*";

                if (!allOpts && !queries.contains(opt)) {
                    std::cout << "Invalid optimization name " << opt << std::endl;
                    continue;
                }

                for (auto& queriesByOpt : queries) {
                    if (allOpts || queriesByOpt.first == opt) {
                        if (!allNames && !queriesByOpt.second.contains(name)) {
                            std::cout << "Invalid query name " << name << std::endl;
                            continue; 
                        }
                    }
                }

                for (auto& queriesByOpt : queries) {
                    if (allOpts || queriesByOpt.first == opt) {
                        for (auto& queriesByName : queriesByOpt.second) {
                            if (allNames || queriesByName.first == name) {
                                for (size_t i = 0; i < repeatValue; i++) {
                                    queriesByName.second(db);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}