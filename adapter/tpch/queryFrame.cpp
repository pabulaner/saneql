#include <functional>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>
#include "TPCH.hpp"

using namespace std;
using namespace tpch;

struct Database : TPCH {
  std::string basepath;

  Database(const std::string &path) : basepath(path) {}

  template <typename T>
  void ensureLoaded(vec<T> &into, uint64_t &cnt, const std::string &relname,
                    const std::string &colname) {
    // table is already loaded; don't have to reload
    if (into.is_backed()) {
      assert(cnt);
      return;
    }
    // load table and store in into
    std::string colpath = basepath + '/' + relname + '/' + colname + ".bin";
    vec<T> file = vec<T>(colpath.c_str());
    assert(cnt == 0 || cnt == file.size());
    cnt = file.size();
    into = std::move(file);
  };
};

int main(int argc, char** argv) {
   Database db(argc >= 2 ? argv[1] : "/opt/tpch/sf1");
#include "gen.cpp"
   return 0;
}
