std::map<std::string, std::map<std::string, std::function<void(Database*, size_t)>>> queries = {
	{"none", {
	{"examples/cpp/q1.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "o_orderpriority" << ", " << "order_count" << std::endl;
		}
		std::vector<std::tuple<Varchar<15>, Varchar<15>, Integer>> v_1;
		std::unordered_map<std::tuple<Varchar<15>>, std::tuple<Integer>> v_2;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Timestamp, Varchar<15>>> v_3;
		db->orders_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_4 = key.o_orderkey;
			const Timestamp& v_5 = value.o_orderdate;
			const Varchar<15>& v_6 = value.o_orderpriority;
			v_3.insert({{v_4}, {v_5, v_6}});
		});
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_7 = key.l_orderkey;
			const Timestamp& v_8 = value.l_commitdate;
			const Timestamp& v_9 = value.l_receiptdate;
			for (auto range = v_3.equal_range({v_7}); range.first!=range.second; range.first++) {
				const Timestamp& v_5 = std::get<0>(range.first->second);
				const Varchar<15>& v_6 = std::get<1>(range.first->second);
				if (((v_5 >= (2449170)) && (v_5 < (2449262))) && (v_8 < v_9)) {
					auto it = v_2.find({v_6});
					if (it == v_2.end()) {
						v_2.insert({{v_6}, {1}});
					} else {
						std::get<0>(it->second) += 1;
					}
				}
			}
		});
		for (auto& it : v_2) {
			const Varchar<15>& v_10 = std::get<0>(it.first);
			const Integer& v_11 = std::get<0>(it.second);
			v_1.push_back({v_10, v_10, v_11});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Varchar<15>& v_10 = std::get<1>(t);
			const Integer& v_11 = std::get<2>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_10 << ", " << v_11 << std::endl;
			}
		}
	}},
	{"examples/cpp/q2.sane", [](Database* db, size_t limit) {
		std::cout << [&]() {
			Numeric v_12 = 0;
			Numeric v_13 = 0;
			std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric, Timestamp>> v_14;
			db->lineitem_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_15 = key.l_partkey;
				const Numeric& v_16 = value.l_extendedprice;
				const Numeric& v_17 = value.l_discount;
				const Timestamp& v_18 = value.l_shipdate;
				v_14.insert({{v_15}, {v_16, v_17, v_18}});
			});
			db->part_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_19 = key.p_partkey;
				for (auto range = v_14.equal_range({v_19}); range.first!=range.second; range.first++) {
					const Numeric& v_16 = std::get<0>(range.first->second);
					const Numeric& v_17 = std::get<1>(range.first->second);
					const Timestamp& v_18 = std::get<2>(range.first->second);
					if ((v_18 >= (2449962)) && (v_18 < (2449992))) {
						v_12 += v_16 * (1 - v_17);
						v_13 += v_16 * (1 - v_17);
					}
				}
			});
			return (100.00 * v_12) / v_13;
		}() << std::endl;
	}},
	{"examples/cpp/q3.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "ps_partkey" << ", " << "value" << std::endl;
		}
		std::vector<std::tuple<Numeric, Integer, Numeric>> v_1;
		std::unordered_map<std::tuple<Integer>, std::tuple<Numeric>> v_20;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Integer, Numeric>> v_21;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Integer, Numeric>> v_22;
		db->partsupp_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_23 = key.ps_partkey;
			const Integer& v_24 = key.ps_suppkey;
			const Integer& v_25 = value.ps_availqty;
			const Numeric& v_26 = value.ps_supplycost;
			v_22.insert({{v_24}, {v_23, v_25, v_26}});
		});
		db->supplier_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_4 = key.s_suppkey;
			const Integer& v_27 = value.s_nationkey;
			for (auto range = v_22.equal_range({v_4}); range.first!=range.second; range.first++) {
				const Integer& v_23 = std::get<0>(range.first->second);
				const Integer& v_25 = std::get<1>(range.first->second);
				const Numeric& v_26 = std::get<2>(range.first->second);
				v_21.insert({{v_27}, {v_23, v_25, v_26}});
			}
		});
		db->nation_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_28 = key.n_nationkey;
			const Varchar<25>& v_29 = value.n_name;
			for (auto range = v_21.equal_range({v_28}); range.first!=range.second; range.first++) {
				const Integer& v_23 = std::get<0>(range.first->second);
				const Integer& v_25 = std::get<1>(range.first->second);
				const Numeric& v_26 = std::get<2>(range.first->second);
				if (v_29 == Varchar<7>("GERMANY")) {
					auto it = v_20.find({v_23});
					if (it == v_20.end()) {
						v_20.insert({{v_23}, {v_26 * v_25}});
					} else {
						std::get<0>(it->second) += v_26 * v_25;
					}
				}
			}
		});
		for (auto& it : v_20) {
			const Integer& v_30 = std::get<0>(it.first);
			const Numeric& v_31 = std::get<0>(it.second);
			if (v_31 > (([&]() {
				Numeric v_32 = 0;
				std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Numeric>> v_33;
				std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Numeric>> v_34;
				db->partsupp_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_35 = key.ps_suppkey;
					const Integer& v_36 = value.ps_availqty;
					const Numeric& v_37 = value.ps_supplycost;
					v_34.insert({{v_35}, {v_36, v_37}});
				});
				db->supplier_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_38 = key.s_suppkey;
					const Integer& v_39 = value.s_nationkey;
					for (auto range = v_34.equal_range({v_38}); range.first!=range.second; range.first++) {
						const Integer& v_36 = std::get<0>(range.first->second);
						const Numeric& v_37 = std::get<1>(range.first->second);
						v_33.insert({{v_39}, {v_36, v_37}});
					}
				});
				db->nation_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_40 = key.n_nationkey;
					const Varchar<25>& v_41 = value.n_name;
					for (auto range = v_33.equal_range({v_40}); range.first!=range.second; range.first++) {
						const Integer& v_36 = std::get<0>(range.first->second);
						const Numeric& v_37 = std::get<1>(range.first->second);
						if (v_41 == Varchar<7>("GERMANY")) {
							v_32 += v_37 * v_36;
						}
					}
				});
				return v_32;
			}()) * 0.0001)) {
				v_1.push_back({v_31, v_30, v_31});
			}
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Integer& v_30 = std::get<1>(t);
			const Numeric& v_31 = std::get<2>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_30 << ", " << v_31 << std::endl;
			}
		}
	}},
}},
	{"selects", {
	{"examples/cpp/q1.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "o_orderpriority" << ", " << "order_count" << std::endl;
		}
		std::vector<std::tuple<Varchar<15>, Varchar<15>, Integer>> v_1;
		std::unordered_map<std::tuple<Varchar<15>>, std::tuple<Integer>> v_2;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Varchar<15>>> v_3;
		db->orders_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_4 = key.o_orderkey;
			const Timestamp& v_5 = value.o_orderdate;
			const Varchar<15>& v_6 = value.o_orderpriority;
			if ((v_5 >= (2449170)) && (v_5 < (2449262))) {
				v_3.insert({{v_4}, {v_6}});
			}
		});
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_7 = key.l_orderkey;
			const Timestamp& v_8 = value.l_commitdate;
			const Timestamp& v_9 = value.l_receiptdate;
			if (v_8 < v_9) {
				for (auto range = v_3.equal_range({v_7}); range.first!=range.second; range.first++) {
					const Varchar<15>& v_6 = std::get<0>(range.first->second);
					auto it = v_2.find({v_6});
					if (it == v_2.end()) {
						v_2.insert({{v_6}, {1}});
					} else {
						std::get<0>(it->second) += 1;
					}
				}
			}
		});
		for (auto& it : v_2) {
			const Varchar<15>& v_10 = std::get<0>(it.first);
			const Integer& v_11 = std::get<0>(it.second);
			v_1.push_back({v_10, v_10, v_11});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Varchar<15>& v_10 = std::get<1>(t);
			const Integer& v_11 = std::get<2>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_10 << ", " << v_11 << std::endl;
			}
		}
	}},
	{"examples/cpp/q2.sane", [](Database* db, size_t limit) {
		std::cout << [&]() {
			Numeric v_12 = 0;
			Numeric v_13 = 0;
			std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric, Timestamp>> v_14;
			db->lineitem_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_15 = key.l_partkey;
				const Numeric& v_16 = value.l_extendedprice;
				const Numeric& v_17 = value.l_discount;
				const Timestamp& v_6 = value.l_shipdate;
				v_14.insert({{v_15}, {v_16, v_17, v_6}});
			});
			db->part_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_18 = key.p_partkey;
				for (auto range = v_14.equal_range({v_18}); range.first!=range.second; range.first++) {
					const Numeric& v_16 = std::get<0>(range.first->second);
					const Numeric& v_17 = std::get<1>(range.first->second);
					const Timestamp& v_6 = std::get<2>(range.first->second);
					if ((v_6 >= (2449962)) && (v_6 < (2449992))) {
						v_12 += v_16 * (1 - v_17);
						v_13 += v_16 * (1 - v_17);
					}
				}
			});
			return (100.00 * v_12) / v_13;
		}() << std::endl;
	}},
	{"examples/cpp/q3.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "ps_partkey" << ", " << "value" << std::endl;
		}
		std::vector<std::tuple<Numeric, Integer, Numeric>> v_1;
		std::unordered_map<std::tuple<Integer>, std::tuple<Numeric>> v_19;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Integer, Numeric>> v_20;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Integer, Numeric>> v_21;
		db->partsupp_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_22 = key.ps_partkey;
			const Integer& v_23 = key.ps_suppkey;
			const Integer& v_24 = value.ps_availqty;
			const Numeric& v_25 = value.ps_supplycost;
			v_21.insert({{v_23}, {v_22, v_24, v_25}});
		});
		db->supplier_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_6 = key.s_suppkey;
			const Integer& v_26 = value.s_nationkey;
			for (auto range = v_21.equal_range({v_6}); range.first!=range.second; range.first++) {
				const Integer& v_22 = std::get<0>(range.first->second);
				const Integer& v_24 = std::get<1>(range.first->second);
				const Numeric& v_25 = std::get<2>(range.first->second);
				v_20.insert({{v_26}, {v_22, v_24, v_25}});
			}
		});
		db->nation_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_18 = key.n_nationkey;
			const Varchar<25>& v_27 = value.n_name;
			if (v_27 == Varchar<7>("GERMANY")) {
				for (auto range = v_20.equal_range({v_18}); range.first!=range.second; range.first++) {
					const Integer& v_22 = std::get<0>(range.first->second);
					const Integer& v_24 = std::get<1>(range.first->second);
					const Numeric& v_25 = std::get<2>(range.first->second);
					auto it = v_19.find({v_22});
					if (it == v_19.end()) {
						v_19.insert({{v_22}, {v_25 * v_24}});
					} else {
						std::get<0>(it->second) += v_25 * v_24;
					}
				}
			}
		});
		for (auto& it : v_19) {
			const Integer& v_28 = std::get<0>(it.first);
			const Numeric& v_29 = std::get<0>(it.second);
			if (v_29 > (([&]() {
				Numeric v_30 = 0;
				std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Numeric>> v_31;
				std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Numeric>> v_32;
				db->partsupp_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_33 = key.ps_suppkey;
					const Integer& v_34 = value.ps_availqty;
					const Numeric& v_35 = value.ps_supplycost;
					v_32.insert({{v_33}, {v_34, v_35}});
				});
				db->supplier_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_36 = key.s_suppkey;
					const Integer& v_37 = value.s_nationkey;
					for (auto range = v_32.equal_range({v_36}); range.first!=range.second; range.first++) {
						const Integer& v_34 = std::get<0>(range.first->second);
						const Numeric& v_35 = std::get<1>(range.first->second);
						v_31.insert({{v_37}, {v_34, v_35}});
					}
				});
				db->nation_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_38 = key.n_nationkey;
					const Varchar<25>& v_39 = value.n_name;
					for (auto range = v_31.equal_range({v_38}); range.first!=range.second; range.first++) {
						const Integer& v_34 = std::get<0>(range.first->second);
						const Numeric& v_35 = std::get<1>(range.first->second);
						if (v_39 == Varchar<7>("GERMANY")) {
							v_30 += v_35 * v_34;
						}
					}
				});
				return v_30;
			}()) * 0.0001)) {
				v_1.push_back({v_29, v_28, v_29});
			}
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Integer& v_28 = std::get<1>(t);
			const Numeric& v_29 = std::get<2>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_28 << ", " << v_29 << std::endl;
			}
		}
	}},
}},
	{"scans", {
	{"examples/cpp/q1.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "o_orderpriority" << ", " << "order_count" << std::endl;
		}
		std::vector<std::tuple<Varchar<15>, Varchar<15>, Integer>> v_1;
		std::unordered_map<std::tuple<Varchar<15>>, std::tuple<Integer>> v_2;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Timestamp, Varchar<15>>> v_3;
		db->orders_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_4 = key.o_orderkey;
			const Timestamp& v_5 = value.o_orderdate;
			const Varchar<15>& v_6 = value.o_orderpriority;
			v_3.insert({{v_4}, {v_5, v_6}});
		});
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_7 = key.l_orderkey;
			const Timestamp& v_8 = value.l_commitdate;
			const Timestamp& v_9 = value.l_receiptdate;
			for (auto range = v_3.equal_range({v_7}); range.first!=range.second; range.first++) {
				const Timestamp& v_5 = std::get<0>(range.first->second);
				const Varchar<15>& v_6 = std::get<1>(range.first->second);
				if (((v_5 >= (2449170)) && (v_5 < (2449262))) && (v_8 < v_9)) {
					auto it = v_2.find({v_6});
					if (it == v_2.end()) {
						v_2.insert({{v_6}, {1}});
					} else {
						std::get<0>(it->second) += 1;
					}
				}
			}
		});
		for (auto& it : v_2) {
			const Varchar<15>& v_10 = std::get<0>(it.first);
			const Integer& v_11 = std::get<0>(it.second);
			v_1.push_back({v_10, v_10, v_11});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Varchar<15>& v_10 = std::get<1>(t);
			const Integer& v_11 = std::get<2>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_10 << ", " << v_11 << std::endl;
			}
		}
	}},
	{"examples/cpp/q2.sane", [](Database* db, size_t limit) {
		std::cout << [&]() {
			Numeric v_12 = 0;
			Numeric v_13 = 0;
			std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric, Timestamp>> v_14;
			db->lineitem_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_15 = key.l_partkey;
				const Numeric& v_16 = value.l_extendedprice;
				const Numeric& v_17 = value.l_discount;
				const Timestamp& v_18 = value.l_shipdate;
				v_14.insert({{v_15}, {v_16, v_17, v_18}});
			});
			db->part_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_19 = key.p_partkey;
				for (auto range = v_14.equal_range({v_19}); range.first!=range.second; range.first++) {
					const Numeric& v_16 = std::get<0>(range.first->second);
					const Numeric& v_17 = std::get<1>(range.first->second);
					const Timestamp& v_18 = std::get<2>(range.first->second);
					if ((v_18 >= (2449962)) && (v_18 < (2449992))) {
						v_12 += v_16 * (1 - v_17);
						v_13 += v_16 * (1 - v_17);
					}
				}
			});
			return (100.00 * v_12) / v_13;
		}() << std::endl;
	}},
	{"examples/cpp/q3.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "ps_partkey" << ", " << "value" << std::endl;
		}
		std::vector<std::tuple<Numeric, Integer, Numeric>> v_1;
		std::unordered_map<std::tuple<Integer>, std::tuple<Numeric>> v_20;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Integer, Numeric>> v_21;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Integer, Numeric>> v_22;
		db->partsupp_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_23 = key.ps_partkey;
			const Integer& v_24 = key.ps_suppkey;
			const Integer& v_25 = value.ps_availqty;
			const Numeric& v_26 = value.ps_supplycost;
			v_22.insert({{v_24}, {v_23, v_25, v_26}});
		});
		db->supplier_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_18 = key.s_suppkey;
			const Integer& v_27 = value.s_nationkey;
			for (auto range = v_22.equal_range({v_18}); range.first!=range.second; range.first++) {
				const Integer& v_23 = std::get<0>(range.first->second);
				const Integer& v_25 = std::get<1>(range.first->second);
				const Numeric& v_26 = std::get<2>(range.first->second);
				v_21.insert({{v_27}, {v_23, v_25, v_26}});
			}
		});
		db->nation_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_28 = key.n_nationkey;
			const Varchar<25>& v_29 = value.n_name;
			for (auto range = v_21.equal_range({v_28}); range.first!=range.second; range.first++) {
				const Integer& v_23 = std::get<0>(range.first->second);
				const Integer& v_25 = std::get<1>(range.first->second);
				const Numeric& v_26 = std::get<2>(range.first->second);
				if (v_29 == Varchar<7>("GERMANY")) {
					auto it = v_20.find({v_23});
					if (it == v_20.end()) {
						v_20.insert({{v_23}, {v_26 * v_25}});
					} else {
						std::get<0>(it->second) += v_26 * v_25;
					}
				}
			}
		});
		for (auto& it : v_20) {
			const Integer& v_30 = std::get<0>(it.first);
			const Numeric& v_31 = std::get<0>(it.second);
			if (v_31 > (([&]() {
				Numeric v_32 = 0;
				std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Numeric>> v_33;
				std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Numeric>> v_34;
				db->partsupp_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_35 = key.ps_suppkey;
					const Integer& v_36 = value.ps_availqty;
					const Numeric& v_37 = value.ps_supplycost;
					v_34.insert({{v_35}, {v_36, v_37}});
				});
				db->supplier_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_38 = key.s_suppkey;
					const Integer& v_39 = value.s_nationkey;
					for (auto range = v_34.equal_range({v_38}); range.first!=range.second; range.first++) {
						const Integer& v_36 = std::get<0>(range.first->second);
						const Numeric& v_37 = std::get<1>(range.first->second);
						v_33.insert({{v_39}, {v_36, v_37}});
					}
				});
				db->nation_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_40 = key.n_nationkey;
					const Varchar<25>& v_41 = value.n_name;
					for (auto range = v_33.equal_range({v_40}); range.first!=range.second; range.first++) {
						const Integer& v_36 = std::get<0>(range.first->second);
						const Numeric& v_37 = std::get<1>(range.first->second);
						if (v_41 == Varchar<7>("GERMANY")) {
							v_32 += v_37 * v_36;
						}
					}
				});
				return v_32;
			}()) * 0.0001)) {
				v_1.push_back({v_31, v_30, v_31});
			}
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Integer& v_30 = std::get<1>(t);
			const Numeric& v_31 = std::get<2>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_30 << ", " << v_31 << std::endl;
			}
		}
	}},
}},
	{"joins", {
	{"examples/cpp/q1.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "o_orderpriority" << ", " << "order_count" << std::endl;
		}
		std::vector<std::tuple<Varchar<15>, Varchar<15>, Integer>> v_1;
		std::unordered_map<std::tuple<Varchar<15>>, std::tuple<Integer>> v_2;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Timestamp, Varchar<15>>> v_3;
		db->orders_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_4 = key.o_orderkey;
			const Timestamp& v_5 = value.o_orderdate;
			const Varchar<15>& v_6 = value.o_orderpriority;
			v_3.insert({{v_4}, {v_5, v_6}});
		});
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_7 = key.l_orderkey;
			const Timestamp& v_8 = value.l_commitdate;
			const Timestamp& v_9 = value.l_receiptdate;
			for (auto range = v_3.equal_range({v_7}); range.first!=range.second; range.first++) {
				const Timestamp& v_5 = std::get<0>(range.first->second);
				const Varchar<15>& v_6 = std::get<1>(range.first->second);
				if (((v_5 >= (2449170)) && (v_5 < (2449262))) && (v_8 < v_9)) {
					auto it = v_2.find({v_6});
					if (it == v_2.end()) {
						v_2.insert({{v_6}, {1}});
					} else {
						std::get<0>(it->second) += 1;
					}
				}
			}
		});
		for (auto& it : v_2) {
			const Varchar<15>& v_10 = std::get<0>(it.first);
			const Integer& v_11 = std::get<0>(it.second);
			v_1.push_back({v_10, v_10, v_11});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Varchar<15>& v_10 = std::get<1>(t);
			const Integer& v_11 = std::get<2>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_10 << ", " << v_11 << std::endl;
			}
		}
	}},
	{"examples/cpp/q2.sane", [](Database* db, size_t limit) {
		std::cout << [&]() {
			Numeric v_12 = 0;
			Numeric v_13 = 0;
			std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric, Timestamp>> v_14;
			db->lineitem_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_15 = key.l_partkey;
				const Numeric& v_16 = value.l_extendedprice;
				const Numeric& v_17 = value.l_discount;
				const Timestamp& v_18 = value.l_shipdate;
				v_14.insert({{v_15}, {v_16, v_17, v_18}});
			});
			db->part_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_19 = key.p_partkey;
				for (auto range = v_14.equal_range({v_19}); range.first!=range.second; range.first++) {
					const Numeric& v_16 = std::get<0>(range.first->second);
					const Numeric& v_17 = std::get<1>(range.first->second);
					const Timestamp& v_18 = std::get<2>(range.first->second);
					if ((v_18 >= (2449962)) && (v_18 < (2449992))) {
						v_12 += v_16 * (1 - v_17);
						v_13 += v_16 * (1 - v_17);
					}
				}
			});
			return (100.00 * v_12) / v_13;
		}() << std::endl;
	}},
	{"examples/cpp/q3.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "ps_partkey" << ", " << "value" << std::endl;
		}
		std::vector<std::tuple<Numeric, Integer, Numeric>> v_1;
		std::unordered_map<std::tuple<Integer>, std::tuple<Numeric>> v_20;
		db->partsupp_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_21 = key.ps_partkey;
			const Integer& v_22 = key.ps_suppkey;
			const Integer& v_23 = value.ps_availqty;
			const Numeric& v_24 = value.ps_supplycost;
			db->supplier_tpch.lookup1({v_22}, [&](auto& value) {
				Integer v_25 = value.s_nationkey;
				db->nation_tpch.lookup1({v_25}, [&](auto& value) {
					Varchar<25> v_8 = value.n_name;
					if (v_8 == Varchar<7>("GERMANY")) {
						auto it = v_20.find({v_21});
						if (it == v_20.end()) {
							v_20.insert({{v_21}, {v_24 * v_23}});
						} else {
							std::get<0>(it->second) += v_24 * v_23;
						}
					}
				});
			});
		});
		for (auto& it : v_20) {
			const Integer& v_26 = std::get<0>(it.first);
			const Numeric& v_27 = std::get<0>(it.second);
			if (v_27 > (([&]() {
				Numeric v_28 = 0;
				std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Numeric>> v_29;
				std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Numeric>> v_30;
				db->partsupp_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_31 = key.ps_suppkey;
					const Integer& v_32 = value.ps_availqty;
					const Numeric& v_33 = value.ps_supplycost;
					v_30.insert({{v_31}, {v_32, v_33}});
				});
				db->supplier_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_34 = key.s_suppkey;
					const Integer& v_35 = value.s_nationkey;
					for (auto range = v_30.equal_range({v_34}); range.first!=range.second; range.first++) {
						const Integer& v_32 = std::get<0>(range.first->second);
						const Numeric& v_33 = std::get<1>(range.first->second);
						v_29.insert({{v_35}, {v_32, v_33}});
					}
				});
				db->nation_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_36 = key.n_nationkey;
					const Varchar<25>& v_37 = value.n_name;
					for (auto range = v_29.equal_range({v_36}); range.first!=range.second; range.first++) {
						const Integer& v_32 = std::get<0>(range.first->second);
						const Numeric& v_33 = std::get<1>(range.first->second);
						if (v_37 == Varchar<7>("GERMANY")) {
							v_28 += v_33 * v_32;
						}
					}
				});
				return v_28;
			}()) * 0.0001)) {
				v_1.push_back({v_27, v_26, v_27});
			}
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Integer& v_26 = std::get<1>(t);
			const Numeric& v_27 = std::get<2>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_26 << ", " << v_27 << std::endl;
			}
		}
	}},
}},
	{"all", {
	{"examples/cpp/q1.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "o_orderpriority" << ", " << "order_count" << std::endl;
		}
		std::vector<std::tuple<Varchar<15>, Varchar<15>, Integer>> v_1;
		std::unordered_map<std::tuple<Varchar<15>>, std::tuple<Integer>> v_2;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Varchar<15>>> v_3;
		db->orders_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_4 = key.o_orderkey;
			const Timestamp& v_5 = value.o_orderdate;
			const Varchar<15>& v_6 = value.o_orderpriority;
			if ((v_5 >= (2449170)) && (v_5 < (2449262))) {
				v_3.insert({{v_4}, {v_6}});
			}
		});
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_7 = key.l_orderkey;
			const Timestamp& v_8 = value.l_commitdate;
			const Timestamp& v_9 = value.l_receiptdate;
			if (v_8 < v_9) {
				for (auto range = v_3.equal_range({v_7}); range.first!=range.second; range.first++) {
					const Varchar<15>& v_6 = std::get<0>(range.first->second);
					auto it = v_2.find({v_6});
					if (it == v_2.end()) {
						v_2.insert({{v_6}, {1}});
					} else {
						std::get<0>(it->second) += 1;
					}
				}
			}
		});
		for (auto& it : v_2) {
			const Varchar<15>& v_10 = std::get<0>(it.first);
			const Integer& v_11 = std::get<0>(it.second);
			v_1.push_back({v_10, v_10, v_11});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Varchar<15>& v_10 = std::get<1>(t);
			const Integer& v_11 = std::get<2>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_10 << ", " << v_11 << std::endl;
			}
		}
	}},
	{"examples/cpp/q2.sane", [](Database* db, size_t limit) {
		std::cout << [&]() {
			Numeric v_12 = 0;
			Numeric v_13 = 0;
			std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric, Timestamp>> v_14;
			db->lineitem_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_15 = key.l_partkey;
				const Numeric& v_16 = value.l_extendedprice;
				const Numeric& v_17 = value.l_discount;
				const Timestamp& v_18 = value.l_shipdate;
				v_14.insert({{v_15}, {v_16, v_17, v_18}});
			});
			db->part_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_19 = key.p_partkey;
				for (auto range = v_14.equal_range({v_19}); range.first!=range.second; range.first++) {
					const Numeric& v_16 = std::get<0>(range.first->second);
					const Numeric& v_17 = std::get<1>(range.first->second);
					const Timestamp& v_18 = std::get<2>(range.first->second);
					if ((v_18 >= (2449962)) && (v_18 < (2449992))) {
						v_12 += v_16 * (1 - v_17);
						v_13 += v_16 * (1 - v_17);
					}
				}
			});
			return (100.00 * v_12) / v_13;
		}() << std::endl;
	}},
	{"examples/cpp/q3.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "ps_partkey" << ", " << "value" << std::endl;
		}
		std::vector<std::tuple<Numeric, Integer, Numeric>> v_1;
		std::unordered_map<std::tuple<Integer>, std::tuple<Numeric>> v_20;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Integer, Numeric>> v_21;
		db->partsupp_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_10 = key.ps_partkey;
			const Integer& v_22 = key.ps_suppkey;
			const Integer& v_23 = value.ps_availqty;
			const Numeric& v_24 = value.ps_supplycost;
			db->supplier_tpch.lookup1({v_22}, [&](auto& value) {
				Integer v_25 = value.s_nationkey;
				v_21.insert({{v_25}, {v_10, v_23, v_24}});
			});
		});
		db->nation_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_26 = key.n_nationkey;
			const Varchar<25>& v_18 = value.n_name;
			if (v_18 == Varchar<7>("GERMANY")) {
				for (auto range = v_21.equal_range({v_26}); range.first!=range.second; range.first++) {
					const Integer& v_10 = std::get<0>(range.first->second);
					const Integer& v_23 = std::get<1>(range.first->second);
					const Numeric& v_24 = std::get<2>(range.first->second);
					auto it = v_20.find({v_10});
					if (it == v_20.end()) {
						v_20.insert({{v_10}, {v_24 * v_23}});
					} else {
						std::get<0>(it->second) += v_24 * v_23;
					}
				}
			}
		});
		for (auto& it : v_20) {
			const Integer& v_27 = std::get<0>(it.first);
			const Numeric& v_28 = std::get<0>(it.second);
			if (v_28 > (([&]() {
				Numeric v_29 = 0;
				std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Numeric>> v_30;
				std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Numeric>> v_31;
				db->partsupp_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_32 = key.ps_suppkey;
					const Integer& v_33 = value.ps_availqty;
					const Numeric& v_34 = value.ps_supplycost;
					v_31.insert({{v_32}, {v_33, v_34}});
				});
				db->supplier_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_35 = key.s_suppkey;
					const Integer& v_36 = value.s_nationkey;
					for (auto range = v_31.equal_range({v_35}); range.first!=range.second; range.first++) {
						const Integer& v_33 = std::get<0>(range.first->second);
						const Numeric& v_34 = std::get<1>(range.first->second);
						v_30.insert({{v_36}, {v_33, v_34}});
					}
				});
				db->nation_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_37 = key.n_nationkey;
					const Varchar<25>& v_38 = value.n_name;
					for (auto range = v_30.equal_range({v_37}); range.first!=range.second; range.first++) {
						const Integer& v_33 = std::get<0>(range.first->second);
						const Numeric& v_34 = std::get<1>(range.first->second);
						if (v_38 == Varchar<7>("GERMANY")) {
							v_29 += v_34 * v_33;
						}
					}
				});
				return v_29;
			}()) * 0.0001)) {
				v_1.push_back({v_28, v_27, v_28});
			}
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Integer& v_27 = std::get<1>(t);
			const Numeric& v_28 = std::get<2>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_27 << ", " << v_28 << std::endl;
			}
		}
	}},
}},
};
