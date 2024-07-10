#include "Database.hpp"

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