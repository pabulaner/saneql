std::map<std::string, std::map<std::string, std::function<void(Database*, size_t)>>> queries = {
	{"none", {
	{"./examples/cpp/q3.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "c_custkey" << ", " << "c_name" << ", " << "c_acctbal" << ", " << "c_phone" << ", " << "n_name" << ", " << "c_address" << ", " << "c_comment" << ", " << "revenue" << std::endl;
		}
		std::vector<std::tuple<Numeric, Integer, Varchar<25>, Numeric, Varchar<15>, Varchar<25>, Varchar<40>, Varchar<117>, Numeric>> v_1;
		std::unordered_map<std::tuple<Integer, Varchar<25>, Numeric, Varchar<15>, Varchar<25>, Varchar<40>, Varchar<117>>, std::tuple<Numeric>> v_2;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Varchar<15>, Numeric, Varchar<117>, Numeric, Numeric>> v_3;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<117>>> v_4;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer>> v_5;
		db->orders_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_6 = key.o_orderkey;
			const Integer& v_7 = key.o_custkey;
			const Timestamp& v_8 = value.o_orderdate;
			if ((v_8 >= (2449262)) && (v_8 < (2449354))) {
				v_5.insert({{v_7}, {v_6}});
			}
		});
		db->customer_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_9 = key.c_custkey;
			const Varchar<25>& v_10 = value.c_name;
			const Varchar<40>& v_11 = value.c_address;
			const Integer& v_12 = value.c_nationkey;
			const Varchar<15>& v_13 = value.c_phone;
			const Numeric& v_14 = value.c_acctbal;
			const Varchar<117>& v_15 = value.c_comment;
			for (auto range = v_5.equal_range({v_9}); range.first!=range.second; range.first++) {
				const Integer& v_6 = std::get<0>(range.first->second);
				v_4.insert({{v_6}, {v_9, v_10, v_11, v_12, v_13, v_14, v_15}});
			}
		});
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_16 = key.l_orderkey;
			const Numeric& v_17 = value.l_extendedprice;
			const Numeric& v_18 = value.l_discount;
			const Varchar<1>& v_19 = value.l_returnflag;
			if (v_19 == Varchar<1>("R")) {
				for (auto range = v_4.equal_range({v_16}); range.first!=range.second; range.first++) {
					const Integer& v_9 = std::get<0>(range.first->second);
					const Varchar<25>& v_10 = std::get<1>(range.first->second);
					const Varchar<40>& v_11 = std::get<2>(range.first->second);
					const Integer& v_12 = std::get<3>(range.first->second);
					const Varchar<15>& v_13 = std::get<4>(range.first->second);
					const Numeric& v_14 = std::get<5>(range.first->second);
					const Varchar<117>& v_15 = std::get<6>(range.first->second);
					v_3.insert({{v_12}, {v_9, v_10, v_11, v_13, v_14, v_15, v_17, v_18}});
				}
			}
		});
		db->nation_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_20 = key.n_nationkey;
			const Varchar<25>& v_21 = value.n_name;
			for (auto range = v_3.equal_range({v_20}); range.first!=range.second; range.first++) {
				const Integer& v_9 = std::get<0>(range.first->second);
				const Varchar<25>& v_10 = std::get<1>(range.first->second);
				const Varchar<40>& v_11 = std::get<2>(range.first->second);
				const Varchar<15>& v_13 = std::get<3>(range.first->second);
				const Numeric& v_14 = std::get<4>(range.first->second);
				const Varchar<117>& v_15 = std::get<5>(range.first->second);
				const Numeric& v_17 = std::get<6>(range.first->second);
				const Numeric& v_18 = std::get<7>(range.first->second);
				auto it = v_2.find({v_9, v_10, v_14, v_13, v_21, v_11, v_15});
				if (it == v_2.end()) {
					v_2.insert({{v_9, v_10, v_14, v_13, v_21, v_11, v_15}, {v_17 * (1 - v_18)}});
				} else {
					std::get<0>(it->second) += v_17 * (1 - v_18);
				}
			}
		});
		for (auto& it : v_2) {
			const Integer& v_22 = std::get<0>(it.first);
			const Varchar<25>& v_23 = std::get<1>(it.first);
			const Numeric& v_24 = std::get<2>(it.first);
			const Varchar<15>& v_25 = std::get<3>(it.first);
			const Varchar<25>& v_26 = std::get<4>(it.first);
			const Varchar<40>& v_27 = std::get<5>(it.first);
			const Varchar<117>& v_28 = std::get<6>(it.first);
			const Numeric& v_29 = std::get<0>(it.second);
			v_1.push_back({v_29, v_22, v_23, v_24, v_25, v_26, v_27, v_28, v_29});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Integer& v_22 = std::get<1>(t);
			const Varchar<25>& v_23 = std::get<2>(t);
			const Numeric& v_24 = std::get<3>(t);
			const Varchar<15>& v_25 = std::get<4>(t);
			const Varchar<25>& v_26 = std::get<5>(t);
			const Varchar<40>& v_27 = std::get<6>(t);
			const Varchar<117>& v_28 = std::get<7>(t);
			const Numeric& v_29 = std::get<8>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_22 << ", " << v_23 << ", " << v_24 << ", " << v_25 << ", " << v_26 << ", " << v_27 << ", " << v_28 << ", " << v_29 << std::endl;
			}
		}
	}},
}},
	{"selects", {
	{"./examples/cpp/q3.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "c_custkey" << ", " << "c_name" << ", " << "c_acctbal" << ", " << "c_phone" << ", " << "n_name" << ", " << "c_address" << ", " << "c_comment" << ", " << "revenue" << std::endl;
		}
		std::vector<std::tuple<Numeric, Integer, Varchar<25>, Numeric, Varchar<15>, Varchar<25>, Varchar<40>, Varchar<117>, Numeric>> v_1;
		std::unordered_map<std::tuple<Integer, Varchar<25>, Numeric, Varchar<15>, Varchar<25>, Varchar<40>, Varchar<117>>, std::tuple<Numeric>> v_2;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Varchar<15>, Numeric, Varchar<117>, Numeric, Numeric>> v_3;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<117>>> v_4;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer>> v_5;
		db->orders_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_6 = key.o_orderkey;
			const Integer& v_7 = key.o_custkey;
			const Timestamp& v_8 = value.o_orderdate;
			if ((v_8 >= (2449262)) && (v_8 < (2449354))) {
				v_5.insert({{v_7}, {v_6}});
			}
		});
		db->customer_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_9 = key.c_custkey;
			const Varchar<25>& v_10 = value.c_name;
			const Varchar<40>& v_11 = value.c_address;
			const Integer& v_12 = value.c_nationkey;
			const Varchar<15>& v_13 = value.c_phone;
			const Numeric& v_14 = value.c_acctbal;
			const Varchar<117>& v_15 = value.c_comment;
			for (auto range = v_5.equal_range({v_9}); range.first!=range.second; range.first++) {
				const Integer& v_6 = std::get<0>(range.first->second);
				v_4.insert({{v_6}, {v_9, v_10, v_11, v_12, v_13, v_14, v_15}});
			}
		});
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_16 = key.l_orderkey;
			const Numeric& v_17 = value.l_extendedprice;
			const Numeric& v_18 = value.l_discount;
			const Varchar<1>& v_19 = value.l_returnflag;
			if (v_19 == Varchar<1>("R")) {
				for (auto range = v_4.equal_range({v_16}); range.first!=range.second; range.first++) {
					const Integer& v_9 = std::get<0>(range.first->second);
					const Varchar<25>& v_10 = std::get<1>(range.first->second);
					const Varchar<40>& v_11 = std::get<2>(range.first->second);
					const Integer& v_12 = std::get<3>(range.first->second);
					const Varchar<15>& v_13 = std::get<4>(range.first->second);
					const Numeric& v_14 = std::get<5>(range.first->second);
					const Varchar<117>& v_15 = std::get<6>(range.first->second);
					v_3.insert({{v_12}, {v_9, v_10, v_11, v_13, v_14, v_15, v_17, v_18}});
				}
			}
		});
		db->nation_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_20 = key.n_nationkey;
			const Varchar<25>& v_21 = value.n_name;
			for (auto range = v_3.equal_range({v_20}); range.first!=range.second; range.first++) {
				const Integer& v_9 = std::get<0>(range.first->second);
				const Varchar<25>& v_10 = std::get<1>(range.first->second);
				const Varchar<40>& v_11 = std::get<2>(range.first->second);
				const Varchar<15>& v_13 = std::get<3>(range.first->second);
				const Numeric& v_14 = std::get<4>(range.first->second);
				const Varchar<117>& v_15 = std::get<5>(range.first->second);
				const Numeric& v_17 = std::get<6>(range.first->second);
				const Numeric& v_18 = std::get<7>(range.first->second);
				auto it = v_2.find({v_9, v_10, v_14, v_13, v_21, v_11, v_15});
				if (it == v_2.end()) {
					v_2.insert({{v_9, v_10, v_14, v_13, v_21, v_11, v_15}, {v_17 * (1 - v_18)}});
				} else {
					std::get<0>(it->second) += v_17 * (1 - v_18);
				}
			}
		});
		for (auto& it : v_2) {
			const Integer& v_22 = std::get<0>(it.first);
			const Varchar<25>& v_23 = std::get<1>(it.first);
			const Numeric& v_24 = std::get<2>(it.first);
			const Varchar<15>& v_25 = std::get<3>(it.first);
			const Varchar<25>& v_26 = std::get<4>(it.first);
			const Varchar<40>& v_27 = std::get<5>(it.first);
			const Varchar<117>& v_28 = std::get<6>(it.first);
			const Numeric& v_29 = std::get<0>(it.second);
			v_1.push_back({v_29, v_22, v_23, v_24, v_25, v_26, v_27, v_28, v_29});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Integer& v_22 = std::get<1>(t);
			const Varchar<25>& v_23 = std::get<2>(t);
			const Numeric& v_24 = std::get<3>(t);
			const Varchar<15>& v_25 = std::get<4>(t);
			const Varchar<25>& v_26 = std::get<5>(t);
			const Varchar<40>& v_27 = std::get<6>(t);
			const Varchar<117>& v_28 = std::get<7>(t);
			const Numeric& v_29 = std::get<8>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_22 << ", " << v_23 << ", " << v_24 << ", " << v_25 << ", " << v_26 << ", " << v_27 << ", " << v_28 << ", " << v_29 << std::endl;
			}
		}
	}},
}},
	{"scans", {
	{"./examples/cpp/q3.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "c_custkey" << ", " << "c_name" << ", " << "c_acctbal" << ", " << "c_phone" << ", " << "n_name" << ", " << "c_address" << ", " << "c_comment" << ", " << "revenue" << std::endl;
		}
		std::vector<std::tuple<Numeric, Integer, Varchar<25>, Numeric, Varchar<15>, Varchar<25>, Varchar<40>, Varchar<117>, Numeric>> v_1;
		std::unordered_map<std::tuple<Integer, Varchar<25>, Numeric, Varchar<15>, Varchar<25>, Varchar<40>, Varchar<117>>, std::tuple<Numeric>> v_2;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Varchar<15>, Numeric, Varchar<117>, Numeric, Numeric>> v_3;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<117>>> v_4;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer>> v_5;
		db->orders_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_6 = key.o_orderkey;
			const Integer& v_7 = key.o_custkey;
			const Timestamp& v_8 = value.o_orderdate;
			if ((v_8 >= (2449262)) && (v_8 < (2449354))) {
				v_5.insert({{v_7}, {v_6}});
			}
		});
		db->customer_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_9 = key.c_custkey;
			const Varchar<25>& v_10 = value.c_name;
			const Varchar<40>& v_11 = value.c_address;
			const Integer& v_12 = value.c_nationkey;
			const Varchar<15>& v_13 = value.c_phone;
			const Numeric& v_14 = value.c_acctbal;
			const Varchar<117>& v_15 = value.c_comment;
			for (auto range = v_5.equal_range({v_9}); range.first!=range.second; range.first++) {
				const Integer& v_6 = std::get<0>(range.first->second);
				v_4.insert({{v_6}, {v_9, v_10, v_11, v_12, v_13, v_14, v_15}});
			}
		});
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_16 = key.l_orderkey;
			const Numeric& v_17 = value.l_extendedprice;
			const Numeric& v_18 = value.l_discount;
			const Varchar<1>& v_19 = value.l_returnflag;
			if (v_19 == Varchar<1>("R")) {
				for (auto range = v_4.equal_range({v_16}); range.first!=range.second; range.first++) {
					const Integer& v_9 = std::get<0>(range.first->second);
					const Varchar<25>& v_10 = std::get<1>(range.first->second);
					const Varchar<40>& v_11 = std::get<2>(range.first->second);
					const Integer& v_12 = std::get<3>(range.first->second);
					const Varchar<15>& v_13 = std::get<4>(range.first->second);
					const Numeric& v_14 = std::get<5>(range.first->second);
					const Varchar<117>& v_15 = std::get<6>(range.first->second);
					v_3.insert({{v_12}, {v_9, v_10, v_11, v_13, v_14, v_15, v_17, v_18}});
				}
			}
		});
		db->nation_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_20 = key.n_nationkey;
			const Varchar<25>& v_21 = value.n_name;
			for (auto range = v_3.equal_range({v_20}); range.first!=range.second; range.first++) {
				const Integer& v_9 = std::get<0>(range.first->second);
				const Varchar<25>& v_10 = std::get<1>(range.first->second);
				const Varchar<40>& v_11 = std::get<2>(range.first->second);
				const Varchar<15>& v_13 = std::get<3>(range.first->second);
				const Numeric& v_14 = std::get<4>(range.first->second);
				const Varchar<117>& v_15 = std::get<5>(range.first->second);
				const Numeric& v_17 = std::get<6>(range.first->second);
				const Numeric& v_18 = std::get<7>(range.first->second);
				auto it = v_2.find({v_9, v_10, v_14, v_13, v_21, v_11, v_15});
				if (it == v_2.end()) {
					v_2.insert({{v_9, v_10, v_14, v_13, v_21, v_11, v_15}, {v_17 * (1 - v_18)}});
				} else {
					std::get<0>(it->second) += v_17 * (1 - v_18);
				}
			}
		});
		for (auto& it : v_2) {
			const Integer& v_22 = std::get<0>(it.first);
			const Varchar<25>& v_23 = std::get<1>(it.first);
			const Numeric& v_24 = std::get<2>(it.first);
			const Varchar<15>& v_25 = std::get<3>(it.first);
			const Varchar<25>& v_26 = std::get<4>(it.first);
			const Varchar<40>& v_27 = std::get<5>(it.first);
			const Varchar<117>& v_28 = std::get<6>(it.first);
			const Numeric& v_29 = std::get<0>(it.second);
			v_1.push_back({v_29, v_22, v_23, v_24, v_25, v_26, v_27, v_28, v_29});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Integer& v_22 = std::get<1>(t);
			const Varchar<25>& v_23 = std::get<2>(t);
			const Numeric& v_24 = std::get<3>(t);
			const Varchar<15>& v_25 = std::get<4>(t);
			const Varchar<25>& v_26 = std::get<5>(t);
			const Varchar<40>& v_27 = std::get<6>(t);
			const Varchar<117>& v_28 = std::get<7>(t);
			const Numeric& v_29 = std::get<8>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_22 << ", " << v_23 << ", " << v_24 << ", " << v_25 << ", " << v_26 << ", " << v_27 << ", " << v_28 << ", " << v_29 << std::endl;
			}
		}
	}},
}},
	{"joins", {
	{"./examples/cpp/q3.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "c_custkey" << ", " << "c_name" << ", " << "c_acctbal" << ", " << "c_phone" << ", " << "n_name" << ", " << "c_address" << ", " << "c_comment" << ", " << "revenue" << std::endl;
		}
		std::vector<std::tuple<Numeric, Integer, Varchar<25>, Numeric, Varchar<15>, Varchar<25>, Varchar<40>, Varchar<117>, Numeric>> v_1;
		std::unordered_map<std::tuple<Integer, Varchar<25>, Numeric, Varchar<15>, Varchar<25>, Varchar<40>, Varchar<117>>, std::tuple<Numeric>> v_2;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<117>>> v_3;
		db->orders_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_4 = key.o_orderkey;
			const Integer& v_5 = key.o_custkey;
			const Timestamp& v_6 = value.o_orderdate;
			if ((v_6 >= (2449262)) && (v_6 < (2449354))) {
				db->customer_tpch.lookup1({v_5}, [&](auto& value) {
					Integer v_7 = v_5;
					Varchar<25> v_8 = value.c_name;
					Varchar<40> v_9 = value.c_address;
					Integer v_10 = value.c_nationkey;
					Varchar<15> v_11 = value.c_phone;
					Numeric v_12 = value.c_acctbal;
					Varchar<117> v_13 = value.c_comment;
					v_3.insert({{v_4}, {v_7, v_8, v_9, v_10, v_11, v_12, v_13}});
				});
			}
		});
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_14 = key.l_orderkey;
			const Numeric& v_15 = value.l_extendedprice;
			const Numeric& v_16 = value.l_discount;
			const Varchar<1>& v_17 = value.l_returnflag;
			if (v_17 == Varchar<1>("R")) {
				for (auto range = v_3.equal_range({v_14}); range.first!=range.second; range.first++) {
					const Integer& v_7 = std::get<0>(range.first->second);
					const Varchar<25>& v_8 = std::get<1>(range.first->second);
					const Varchar<40>& v_9 = std::get<2>(range.first->second);
					const Integer& v_10 = std::get<3>(range.first->second);
					const Varchar<15>& v_11 = std::get<4>(range.first->second);
					const Numeric& v_12 = std::get<5>(range.first->second);
					const Varchar<117>& v_13 = std::get<6>(range.first->second);
					db->nation_tpch.lookup1({v_10}, [&](auto& value) {
						Varchar<25> v_18 = value.n_name;
						auto it = v_2.find({v_7, v_8, v_12, v_11, v_18, v_9, v_13});
						if (it == v_2.end()) {
							v_2.insert({{v_7, v_8, v_12, v_11, v_18, v_9, v_13}, {v_15 * (1 - v_16)}});
						} else {
							std::get<0>(it->second) += v_15 * (1 - v_16);
						}
					});
				}
			}
		});
		for (auto& it : v_2) {
			const Integer& v_19 = std::get<0>(it.first);
			const Varchar<25>& v_20 = std::get<1>(it.first);
			const Numeric& v_21 = std::get<2>(it.first);
			const Varchar<15>& v_22 = std::get<3>(it.first);
			const Varchar<25>& v_23 = std::get<4>(it.first);
			const Varchar<40>& v_24 = std::get<5>(it.first);
			const Varchar<117>& v_25 = std::get<6>(it.first);
			const Numeric& v_26 = std::get<0>(it.second);
			v_1.push_back({v_26, v_19, v_20, v_21, v_22, v_23, v_24, v_25, v_26});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Integer& v_19 = std::get<1>(t);
			const Varchar<25>& v_20 = std::get<2>(t);
			const Numeric& v_21 = std::get<3>(t);
			const Varchar<15>& v_22 = std::get<4>(t);
			const Varchar<25>& v_23 = std::get<5>(t);
			const Varchar<40>& v_24 = std::get<6>(t);
			const Varchar<117>& v_25 = std::get<7>(t);
			const Numeric& v_26 = std::get<8>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_19 << ", " << v_20 << ", " << v_21 << ", " << v_22 << ", " << v_23 << ", " << v_24 << ", " << v_25 << ", " << v_26 << std::endl;
			}
		}
	}},
}},
	{"all", {
	{"./examples/cpp/q3.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "c_custkey" << ", " << "c_name" << ", " << "c_acctbal" << ", " << "c_phone" << ", " << "n_name" << ", " << "c_address" << ", " << "c_comment" << ", " << "revenue" << std::endl;
		}
		std::vector<std::tuple<Numeric, Integer, Varchar<25>, Numeric, Varchar<15>, Varchar<25>, Varchar<40>, Varchar<117>, Numeric>> v_1;
		std::unordered_map<std::tuple<Integer, Varchar<25>, Numeric, Varchar<15>, Varchar<25>, Varchar<40>, Varchar<117>>, std::tuple<Numeric>> v_2;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<117>>> v_3;
		db->orders_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_4 = key.o_orderkey;
			const Integer& v_5 = key.o_custkey;
			const Timestamp& v_6 = value.o_orderdate;
			if ((v_6 >= (2449262)) && (v_6 < (2449354))) {
				db->customer_tpch.lookup1({v_5}, [&](auto& value) {
					Integer v_7 = v_5;
					Varchar<25> v_8 = value.c_name;
					Varchar<40> v_9 = value.c_address;
					Integer v_10 = value.c_nationkey;
					Varchar<15> v_11 = value.c_phone;
					Numeric v_12 = value.c_acctbal;
					Varchar<117> v_13 = value.c_comment;
					v_3.insert({{v_4}, {v_7, v_8, v_9, v_10, v_11, v_12, v_13}});
				});
			}
		});
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_14 = key.l_orderkey;
			const Numeric& v_15 = value.l_extendedprice;
			const Numeric& v_16 = value.l_discount;
			const Varchar<1>& v_17 = value.l_returnflag;
			if (v_17 == Varchar<1>("R")) {
				for (auto range = v_3.equal_range({v_14}); range.first!=range.second; range.first++) {
					const Integer& v_7 = std::get<0>(range.first->second);
					const Varchar<25>& v_8 = std::get<1>(range.first->second);
					const Varchar<40>& v_9 = std::get<2>(range.first->second);
					const Integer& v_10 = std::get<3>(range.first->second);
					const Varchar<15>& v_11 = std::get<4>(range.first->second);
					const Numeric& v_12 = std::get<5>(range.first->second);
					const Varchar<117>& v_13 = std::get<6>(range.first->second);
					db->nation_tpch.lookup1({v_10}, [&](auto& value) {
						Varchar<25> v_18 = value.n_name;
						auto it = v_2.find({v_7, v_8, v_12, v_11, v_18, v_9, v_13});
						if (it == v_2.end()) {
							v_2.insert({{v_7, v_8, v_12, v_11, v_18, v_9, v_13}, {v_15 * (1 - v_16)}});
						} else {
							std::get<0>(it->second) += v_15 * (1 - v_16);
						}
					});
				}
			}
		});
		for (auto& it : v_2) {
			const Integer& v_19 = std::get<0>(it.first);
			const Varchar<25>& v_20 = std::get<1>(it.first);
			const Numeric& v_21 = std::get<2>(it.first);
			const Varchar<15>& v_22 = std::get<3>(it.first);
			const Varchar<25>& v_23 = std::get<4>(it.first);
			const Varchar<40>& v_24 = std::get<5>(it.first);
			const Varchar<117>& v_25 = std::get<6>(it.first);
			const Numeric& v_26 = std::get<0>(it.second);
			v_1.push_back({v_26, v_19, v_20, v_21, v_22, v_23, v_24, v_25, v_26});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Integer& v_19 = std::get<1>(t);
			const Varchar<25>& v_20 = std::get<2>(t);
			const Numeric& v_21 = std::get<3>(t);
			const Varchar<15>& v_22 = std::get<4>(t);
			const Varchar<25>& v_23 = std::get<5>(t);
			const Varchar<40>& v_24 = std::get<6>(t);
			const Varchar<117>& v_25 = std::get<7>(t);
			const Numeric& v_26 = std::get<8>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_19 << ", " << v_20 << ", " << v_21 << ", " << v_22 << ", " << v_23 << ", " << v_24 << ", " << v_25 << ", " << v_26 << std::endl;
			}
		}
	}},
}},
};
