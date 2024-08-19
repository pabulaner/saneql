#include <vector>
#include <unordered_map>
#include <tuple>

#include "Database.hpp"

extern "C" void exec(void* _db) {
    adapter::Database* db = (adapter::Database*) _db;
    #include "resource/query.hpp"
}