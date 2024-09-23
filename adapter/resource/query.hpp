std::map<std::string, std::map<std::string, std::function<void(Database*, size_t)>>> queries = {
	{"none", {
	{"./query/benchmark/q2.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "1" << std::endl;
		}
		std::unordered_map<std::tuple<>, std::tuple<Numeric, Numeric>> v_1;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric, Timestamp>> v_2;
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_3 = key.l_partkey;
			const Numeric& v_4 = value.l_extendedprice;
			const Numeric& v_5 = value.l_discount;
			const Timestamp& v_6 = value.l_shipdate;
			v_2.insert({{v_3}, {v_4, v_5, v_6}});
		});
		db->part_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_7 = key.p_partkey;
			for (auto range = v_2.equal_range({v_7}); range.first!=range.second; range.first++) {
				const Numeric& v_4 = std::get<0>(range.first->second);
				const Numeric& v_5 = std::get<1>(range.first->second);
				const Timestamp& v_6 = std::get<2>(range.first->second);
				if ((v_6 >= (2449962)) && (v_6 < (2449992))) {
					auto it = v_1.find({});
					if (it == v_1.end()) {
						v_1.insert({{}, {v_4 * (1 - v_5), v_4 * (1 - v_5)}});
					} else {
						std::get<0>(it->second) += v_4 * (1 - v_5);
						std::get<1>(it->second) += v_4 * (1 - v_5);
					}
				}
			}
		});
		for (auto& it : v_1) {
			const Numeric& v_8 = std::get<0>(it.second);
			const Numeric& v_9 = std::get<1>(it.second);
			Numeric v_10 = (100.00 * v_8) / v_9;
			if (limit > 0) {
				limit -= 1;
				std::cout << v_10 << std::endl;
			}
		}
	}},
}},
	{"selects", {
	{"./query/benchmark/q2.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "1" << std::endl;
		}
		std::unordered_map<std::tuple<>, std::tuple<Numeric, Numeric>> v_1;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric>> v_2;
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_3 = key.l_partkey;
			const Numeric& v_4 = value.l_extendedprice;
			const Numeric& v_5 = value.l_discount;
			const Timestamp& v_6 = value.l_shipdate;
			if ((v_6 >= (2449962)) && (v_6 < (2449992))) {
				v_2.insert({{v_3}, {v_4, v_5}});
			}
		});
		db->part_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_7 = key.p_partkey;
			for (auto range = v_2.equal_range({v_7}); range.first!=range.second; range.first++) {
				const Numeric& v_4 = std::get<0>(range.first->second);
				const Numeric& v_5 = std::get<1>(range.first->second);
				auto it = v_1.find({});
				if (it == v_1.end()) {
					v_1.insert({{}, {v_4 * (1 - v_5), v_4 * (1 - v_5)}});
				} else {
					std::get<0>(it->second) += v_4 * (1 - v_5);
					std::get<1>(it->second) += v_4 * (1 - v_5);
				}
			}
		});
		for (auto& it : v_1) {
			const Numeric& v_8 = std::get<0>(it.second);
			const Numeric& v_9 = std::get<1>(it.second);
			Numeric v_10 = (100.00 * v_8) / v_9;
			if (limit > 0) {
				limit -= 1;
				std::cout << v_10 << std::endl;
			}
		}
	}},
}},
	{"scans", {
	{"./query/benchmark/q2.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "1" << std::endl;
		}
		std::unordered_map<std::tuple<>, std::tuple<Numeric, Numeric>> v_1;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric, Timestamp>> v_2;
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_3 = key.l_partkey;
			const Numeric& v_4 = value.l_extendedprice;
			const Numeric& v_5 = value.l_discount;
			const Timestamp& v_6 = value.l_shipdate;
			v_2.insert({{v_3}, {v_4, v_5, v_6}});
		});
		db->part_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_7 = key.p_partkey;
			for (auto range = v_2.equal_range({v_7}); range.first!=range.second; range.first++) {
				const Numeric& v_4 = std::get<0>(range.first->second);
				const Numeric& v_5 = std::get<1>(range.first->second);
				const Timestamp& v_6 = std::get<2>(range.first->second);
				if ((v_6 >= (2449962)) && (v_6 < (2449992))) {
					auto it = v_1.find({});
					if (it == v_1.end()) {
						v_1.insert({{}, {v_4 * (1 - v_5), v_4 * (1 - v_5)}});
					} else {
						std::get<0>(it->second) += v_4 * (1 - v_5);
						std::get<1>(it->second) += v_4 * (1 - v_5);
					}
				}
			}
		});
		for (auto& it : v_1) {
			const Numeric& v_8 = std::get<0>(it.second);
			const Numeric& v_9 = std::get<1>(it.second);
			Numeric v_10 = (100.00 * v_8) / v_9;
			if (limit > 0) {
				limit -= 1;
				std::cout << v_10 << std::endl;
			}
		}
	}},
}},
	{"joins", {
	{"./query/benchmark/q2.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "1" << std::endl;
		}
		std::unordered_map<std::tuple<>, std::tuple<Numeric, Numeric>> v_1;
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_2 = key.l_partkey;
			const Numeric& v_3 = value.l_extendedprice;
			const Numeric& v_4 = value.l_discount;
			const Timestamp& v_5 = value.l_shipdate;
			db->part_tpch.lookup1({v_2}, [&](auto& value) {
				if ((v_5 >= (2449962)) && (v_5 < (2449992))) {
					auto it = v_1.find({});
					if (it == v_1.end()) {
						v_1.insert({{}, {v_3 * (1 - v_4), v_3 * (1 - v_4)}});
					} else {
						std::get<0>(it->second) += v_3 * (1 - v_4);
						std::get<1>(it->second) += v_3 * (1 - v_4);
					}
				}
			});
		});
		for (auto& it : v_1) {
			const Numeric& v_6 = std::get<0>(it.second);
			const Numeric& v_7 = std::get<1>(it.second);
			Numeric v_8 = (100.00 * v_6) / v_7;
			if (limit > 0) {
				limit -= 1;
				std::cout << v_8 << std::endl;
			}
		}
	}},
}},
	{"all", {
	{"./query/benchmark/q2.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "1" << std::endl;
		}
		std::unordered_map<std::tuple<>, std::tuple<Numeric, Numeric>> v_1;
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_2 = key.l_partkey;
			const Numeric& v_3 = value.l_extendedprice;
			const Numeric& v_4 = value.l_discount;
			const Timestamp& v_5 = value.l_shipdate;
			if ((v_5 >= (2449962)) && (v_5 < (2449992))) {
				db->part_tpch.lookup1({v_2}, [&](auto& value) {
					auto it = v_1.find({});
					if (it == v_1.end()) {
						v_1.insert({{}, {v_3 * (1 - v_4), v_3 * (1 - v_4)}});
					} else {
						std::get<0>(it->second) += v_3 * (1 - v_4);
						std::get<1>(it->second) += v_3 * (1 - v_4);
					}
				});
			}
		});
		for (auto& it : v_1) {
			const Numeric& v_6 = std::get<0>(it.second);
			const Numeric& v_7 = std::get<1>(it.second);
			Numeric v_8 = (100.00 * v_6) / v_7;
			if (limit > 0) {
				limit -= 1;
				std::cout << v_8 << std::endl;
			}
		}
	}},
}},
};
