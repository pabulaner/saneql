std::map<std::string, std::map<std::string, std::function<void(Database*, size_t)>>> queries = {
	{"none", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		std::cout << [&]() {
			Numeric v_1 = std::numeric_limits<Numeric>::max();
			db->partsupp_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_2 = key.ps_partkey;
				const Numeric& v_3 = value.ps_supplycost;
				if (v_2 == 5) {
					v_1 = std::min(v_1, v_3);
				}
			});
			return v_1;
		}() << std::endl;
	}},
}},
	{"selects", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		std::cout << [&]() {
			Numeric v_1 = std::numeric_limits<Numeric>::max();
			db->partsupp_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_2 = key.ps_partkey;
				const Numeric& v_3 = value.ps_supplycost;
				if (v_2 == 5) {
					v_1 = std::min(v_1, v_3);
				}
			});
			return v_1;
		}() << std::endl;
	}},
}},
	{"scans", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		std::cout << [&]() {
			Numeric v_1 = std::numeric_limits<Numeric>::max();
			db->partsupp_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_2 = key.ps_partkey;
				const Numeric& v_3 = value.ps_supplycost;
				if (v_2 == 5) {
					v_1 = std::min(v_1, v_3);
				}
			});
			return v_1;
		}() << std::endl;
	}},
}},
	{"joins", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		std::cout << [&]() {
			Numeric v_1 = std::numeric_limits<Numeric>::max();
			db->partsupp_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_2 = key.ps_partkey;
				const Numeric& v_3 = value.ps_supplycost;
				if (v_2 == 5) {
					v_1 = std::min(v_1, v_3);
				}
			});
			return v_1;
		}() << std::endl;
	}},
}},
	{"all", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		std::cout << [&]() {
			Numeric v_1 = std::numeric_limits<Numeric>::max();
			db->partsupp_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_2 = key.ps_partkey;
				const Numeric& v_3 = value.ps_supplycost;
				if (v_2 == 5) {
					v_1 = std::min(v_1, v_3);
				}
			});
			return v_1;
		}() << std::endl;
	}},
}},
};
