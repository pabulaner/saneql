#include "Database.hpp"

#include <unordered_map>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace adapter;

namespace adapter {

std::unique_ptr<Database> Database::instance = nullptr;

Database* Database::getInstance() {
    if (instance.get() == nullptr) {
        u32 threadCount = envOr("THREADS", 1);
        u32 warehouseCount = envOr("DATASIZE", 3);

        Database* ptr = new Database(threadCount, warehouseCount);
        instance = std::unique_ptr<Database>(ptr);
    }

    return instance.get();
}

Database::Database(u32 threadCount, u32 warehouseCount) 
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

    // load tpcc
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

    // load tpch
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