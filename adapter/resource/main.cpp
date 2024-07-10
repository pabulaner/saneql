#include "../Database.hpp"
#include "../Operator.hpp"

using namespace adapter;

int main(int argc, char** argv) {
    adapter::Database* db = adapter::Database::getInstance();
    #include "../../query/query.cpp"
}