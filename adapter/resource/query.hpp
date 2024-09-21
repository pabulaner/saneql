std::map<std::string, std::map<std::string, std::function<void(Database*, size_t)>>> queries = {
	{"none", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		std::vector<std::tuple<Varchar<1>, Varchar<1>, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Integer, Varchar<1>, Varchar<1>>> v_1;
		std::unordered_map<std::tuple<Varchar<1>, Varchar<1>>, std::tuple<Numeric, Numeric, Numeric, Numeric, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, Integer>> v_2;
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			Integer v_3 = key.l_orderkey;
			Integer v_4 = value.l_partkey;
			Integer v_5 = value.l_suppkey;
			Integer v_6 = value.l_linenumber;
			Numeric v_7 = value.l_quantity;
			Numeric v_8 = value.l_extendedprice;
			Numeric v_9 = value.l_discount;
			Numeric v_10 = value.l_tax;
			Varchar<1> v_11 = value.l_returnflag;
			Varchar<1> v_12 = value.l_linestatus;
			Timestamp v_13 = value.l_shipdate;
			Timestamp v_14 = value.l_commitdate;
			Timestamp v_15 = value.l_receiptdate;
			Varchar<25> v_16 = value.l_shipinstruct;
			Varchar<10> v_17 = value.l_shipmode;
			Varchar<44> v_18 = value.l_comment;
			if (v_13 <= (2451058)) {
				auto it = v_2.find({v_11, v_12});
				if (it == v_2.end()) {
					v_2.insert({{v_11, v_12}, {v_7, v_8, v_8 * (1 - v_9), (v_8 * (1 - v_9)) * (1 + v_10), {v_7, 1}, {v_8, 1}, {v_9, 1}, 1}});
				} else {
					std::get<0>(it->second) += v_7;
					std::get<1>(it->second) += v_8;
					std::get<2>(it->second) += v_8 * (1 - v_9);
					std::get<3>(it->second) += (v_8 * (1 - v_9)) * (1 + v_10);
					std::get<4>(it->second) = {std::get<4>(it->second).first + v_7, std::get<4>(it->second).second + 1};
					std::get<5>(it->second) = {std::get<5>(it->second).first + v_8, std::get<5>(it->second).second + 1};
					std::get<6>(it->second) = {std::get<6>(it->second).first + v_9, std::get<6>(it->second).second + 1};
					std::get<7>(it->second) += 1;
				}
			}
		});
		for (auto& it : v_2) {
			Varchar<1> v_19 = std::get<0>(it.first);
			Varchar<1> v_20 = std::get<1>(it.first);
			Numeric v_21 = std::get<0>(it.second);
			Numeric v_22 = std::get<1>(it.second);
			Numeric v_23 = std::get<2>(it.second);
			Numeric v_24 = std::get<3>(it.second);
			Numeric v_25 = std::get<4>(it.second).first / (double)std::get<4>(it.second).second;
			Numeric v_26 = std::get<5>(it.second).first / (double)std::get<5>(it.second).second;
			Numeric v_27 = std::get<6>(it.second).first / (double)std::get<6>(it.second).second;
			Integer v_28 = std::get<7>(it.second);
			v_1.push_back({v_19, v_20, v_21, v_22, v_23, v_24, v_25, v_26, v_27, v_28, v_19, v_20});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			if (get<1>(t1) < get<1>(t2)) return true;
			if (get<1>(t2) < get<1>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			Numeric v_21 = std::get<2>(t);
			Numeric v_22 = std::get<3>(t);
			Numeric v_23 = std::get<4>(t);
			Numeric v_24 = std::get<5>(t);
			Numeric v_25 = std::get<6>(t);
			Numeric v_26 = std::get<7>(t);
			Numeric v_27 = std::get<8>(t);
			Integer v_28 = std::get<9>(t);
			Varchar<1> v_19 = std::get<10>(t);
			Varchar<1> v_20 = std::get<11>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_21 << ", " << v_22 << ", " << v_23 << ", " << v_24 << ", " << v_25 << ", " << v_26 << ", " << v_27 << ", " << v_28 << ", " << v_19 << ", " << v_20 << std::endl;
			}
		}
	}},
}},
	{"selects", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		std::vector<std::tuple<Varchar<1>, Varchar<1>, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Integer, Varchar<1>, Varchar<1>>> v_1;
		std::unordered_map<std::tuple<Varchar<1>, Varchar<1>>, std::tuple<Numeric, Numeric, Numeric, Numeric, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, Integer>> v_2;
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			Integer v_3 = key.l_orderkey;
			Integer v_4 = value.l_partkey;
			Integer v_5 = value.l_suppkey;
			Integer v_6 = value.l_linenumber;
			Numeric v_7 = value.l_quantity;
			Numeric v_8 = value.l_extendedprice;
			Numeric v_9 = value.l_discount;
			Numeric v_10 = value.l_tax;
			Varchar<1> v_11 = value.l_returnflag;
			Varchar<1> v_12 = value.l_linestatus;
			Timestamp v_13 = value.l_shipdate;
			Timestamp v_14 = value.l_commitdate;
			Timestamp v_15 = value.l_receiptdate;
			Varchar<25> v_16 = value.l_shipinstruct;
			Varchar<10> v_17 = value.l_shipmode;
			Varchar<44> v_18 = value.l_comment;
			if (v_13 <= (2451058)) {
				auto it = v_2.find({v_11, v_12});
				if (it == v_2.end()) {
					v_2.insert({{v_11, v_12}, {v_7, v_8, v_8 * (1 - v_9), (v_8 * (1 - v_9)) * (1 + v_10), {v_7, 1}, {v_8, 1}, {v_9, 1}, 1}});
				} else {
					std::get<0>(it->second) += v_7;
					std::get<1>(it->second) += v_8;
					std::get<2>(it->second) += v_8 * (1 - v_9);
					std::get<3>(it->second) += (v_8 * (1 - v_9)) * (1 + v_10);
					std::get<4>(it->second) = {std::get<4>(it->second).first + v_7, std::get<4>(it->second).second + 1};
					std::get<5>(it->second) = {std::get<5>(it->second).first + v_8, std::get<5>(it->second).second + 1};
					std::get<6>(it->second) = {std::get<6>(it->second).first + v_9, std::get<6>(it->second).second + 1};
					std::get<7>(it->second) += 1;
				}
			}
		});
		for (auto& it : v_2) {
			Varchar<1> v_19 = std::get<0>(it.first);
			Varchar<1> v_20 = std::get<1>(it.first);
			Numeric v_21 = std::get<0>(it.second);
			Numeric v_22 = std::get<1>(it.second);
			Numeric v_23 = std::get<2>(it.second);
			Numeric v_24 = std::get<3>(it.second);
			Numeric v_25 = std::get<4>(it.second).first / (double)std::get<4>(it.second).second;
			Numeric v_26 = std::get<5>(it.second).first / (double)std::get<5>(it.second).second;
			Numeric v_27 = std::get<6>(it.second).first / (double)std::get<6>(it.second).second;
			Integer v_28 = std::get<7>(it.second);
			v_1.push_back({v_19, v_20, v_21, v_22, v_23, v_24, v_25, v_26, v_27, v_28, v_19, v_20});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			if (get<1>(t1) < get<1>(t2)) return true;
			if (get<1>(t2) < get<1>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			Numeric v_21 = std::get<2>(t);
			Numeric v_22 = std::get<3>(t);
			Numeric v_23 = std::get<4>(t);
			Numeric v_24 = std::get<5>(t);
			Numeric v_25 = std::get<6>(t);
			Numeric v_26 = std::get<7>(t);
			Numeric v_27 = std::get<8>(t);
			Integer v_28 = std::get<9>(t);
			Varchar<1> v_19 = std::get<10>(t);
			Varchar<1> v_20 = std::get<11>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_21 << ", " << v_22 << ", " << v_23 << ", " << v_24 << ", " << v_25 << ", " << v_26 << ", " << v_27 << ", " << v_28 << ", " << v_19 << ", " << v_20 << std::endl;
			}
		}
	}},
}},
	{"scans", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		std::vector<std::tuple<Varchar<1>, Varchar<1>, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Integer, Varchar<1>, Varchar<1>>> v_1;
		std::unordered_map<std::tuple<Varchar<1>, Varchar<1>>, std::tuple<Numeric, Numeric, Numeric, Numeric, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, Integer>> v_2;
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			Integer v_3 = key.l_orderkey;
			Integer v_4 = value.l_partkey;
			Integer v_5 = value.l_suppkey;
			Integer v_6 = value.l_linenumber;
			Numeric v_7 = value.l_quantity;
			Numeric v_8 = value.l_extendedprice;
			Numeric v_9 = value.l_discount;
			Numeric v_10 = value.l_tax;
			Varchar<1> v_11 = value.l_returnflag;
			Varchar<1> v_12 = value.l_linestatus;
			Timestamp v_13 = value.l_shipdate;
			Timestamp v_14 = value.l_commitdate;
			Timestamp v_15 = value.l_receiptdate;
			Varchar<25> v_16 = value.l_shipinstruct;
			Varchar<10> v_17 = value.l_shipmode;
			Varchar<44> v_18 = value.l_comment;
			if (v_13 <= (2451058)) {
				auto it = v_2.find({v_11, v_12});
				if (it == v_2.end()) {
					v_2.insert({{v_11, v_12}, {v_7, v_8, v_8 * (1 - v_9), (v_8 * (1 - v_9)) * (1 + v_10), {v_7, 1}, {v_8, 1}, {v_9, 1}, 1}});
				} else {
					std::get<0>(it->second) += v_7;
					std::get<1>(it->second) += v_8;
					std::get<2>(it->second) += v_8 * (1 - v_9);
					std::get<3>(it->second) += (v_8 * (1 - v_9)) * (1 + v_10);
					std::get<4>(it->second) = {std::get<4>(it->second).first + v_7, std::get<4>(it->second).second + 1};
					std::get<5>(it->second) = {std::get<5>(it->second).first + v_8, std::get<5>(it->second).second + 1};
					std::get<6>(it->second) = {std::get<6>(it->second).first + v_9, std::get<6>(it->second).second + 1};
					std::get<7>(it->second) += 1;
				}
			}
		});
		for (auto& it : v_2) {
			Varchar<1> v_19 = std::get<0>(it.first);
			Varchar<1> v_20 = std::get<1>(it.first);
			Numeric v_21 = std::get<0>(it.second);
			Numeric v_22 = std::get<1>(it.second);
			Numeric v_23 = std::get<2>(it.second);
			Numeric v_24 = std::get<3>(it.second);
			Numeric v_25 = std::get<4>(it.second).first / (double)std::get<4>(it.second).second;
			Numeric v_26 = std::get<5>(it.second).first / (double)std::get<5>(it.second).second;
			Numeric v_27 = std::get<6>(it.second).first / (double)std::get<6>(it.second).second;
			Integer v_28 = std::get<7>(it.second);
			v_1.push_back({v_19, v_20, v_21, v_22, v_23, v_24, v_25, v_26, v_27, v_28, v_19, v_20});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			if (get<1>(t1) < get<1>(t2)) return true;
			if (get<1>(t2) < get<1>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			Numeric v_21 = std::get<2>(t);
			Numeric v_22 = std::get<3>(t);
			Numeric v_23 = std::get<4>(t);
			Numeric v_24 = std::get<5>(t);
			Numeric v_25 = std::get<6>(t);
			Numeric v_26 = std::get<7>(t);
			Numeric v_27 = std::get<8>(t);
			Integer v_28 = std::get<9>(t);
			Varchar<1> v_19 = std::get<10>(t);
			Varchar<1> v_20 = std::get<11>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_21 << ", " << v_22 << ", " << v_23 << ", " << v_24 << ", " << v_25 << ", " << v_26 << ", " << v_27 << ", " << v_28 << ", " << v_19 << ", " << v_20 << std::endl;
			}
		}
	}},
}},
	{"joins", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		std::vector<std::tuple<Varchar<1>, Varchar<1>, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Integer, Varchar<1>, Varchar<1>>> v_1;
		std::unordered_map<std::tuple<Varchar<1>, Varchar<1>>, std::tuple<Numeric, Numeric, Numeric, Numeric, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, Integer>> v_2;
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			Integer v_3 = key.l_orderkey;
			Integer v_4 = value.l_partkey;
			Integer v_5 = value.l_suppkey;
			Integer v_6 = value.l_linenumber;
			Numeric v_7 = value.l_quantity;
			Numeric v_8 = value.l_extendedprice;
			Numeric v_9 = value.l_discount;
			Numeric v_10 = value.l_tax;
			Varchar<1> v_11 = value.l_returnflag;
			Varchar<1> v_12 = value.l_linestatus;
			Timestamp v_13 = value.l_shipdate;
			Timestamp v_14 = value.l_commitdate;
			Timestamp v_15 = value.l_receiptdate;
			Varchar<25> v_16 = value.l_shipinstruct;
			Varchar<10> v_17 = value.l_shipmode;
			Varchar<44> v_18 = value.l_comment;
			if (v_13 <= (2451058)) {
				auto it = v_2.find({v_11, v_12});
				if (it == v_2.end()) {
					v_2.insert({{v_11, v_12}, {v_7, v_8, v_8 * (1 - v_9), (v_8 * (1 - v_9)) * (1 + v_10), {v_7, 1}, {v_8, 1}, {v_9, 1}, 1}});
				} else {
					std::get<0>(it->second) += v_7;
					std::get<1>(it->second) += v_8;
					std::get<2>(it->second) += v_8 * (1 - v_9);
					std::get<3>(it->second) += (v_8 * (1 - v_9)) * (1 + v_10);
					std::get<4>(it->second) = {std::get<4>(it->second).first + v_7, std::get<4>(it->second).second + 1};
					std::get<5>(it->second) = {std::get<5>(it->second).first + v_8, std::get<5>(it->second).second + 1};
					std::get<6>(it->second) = {std::get<6>(it->second).first + v_9, std::get<6>(it->second).second + 1};
					std::get<7>(it->second) += 1;
				}
			}
		});
		for (auto& it : v_2) {
			Varchar<1> v_19 = std::get<0>(it.first);
			Varchar<1> v_20 = std::get<1>(it.first);
			Numeric v_21 = std::get<0>(it.second);
			Numeric v_22 = std::get<1>(it.second);
			Numeric v_23 = std::get<2>(it.second);
			Numeric v_24 = std::get<3>(it.second);
			Numeric v_25 = std::get<4>(it.second).first / (double)std::get<4>(it.second).second;
			Numeric v_26 = std::get<5>(it.second).first / (double)std::get<5>(it.second).second;
			Numeric v_27 = std::get<6>(it.second).first / (double)std::get<6>(it.second).second;
			Integer v_28 = std::get<7>(it.second);
			v_1.push_back({v_19, v_20, v_21, v_22, v_23, v_24, v_25, v_26, v_27, v_28, v_19, v_20});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			if (get<1>(t1) < get<1>(t2)) return true;
			if (get<1>(t2) < get<1>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			Numeric v_21 = std::get<2>(t);
			Numeric v_22 = std::get<3>(t);
			Numeric v_23 = std::get<4>(t);
			Numeric v_24 = std::get<5>(t);
			Numeric v_25 = std::get<6>(t);
			Numeric v_26 = std::get<7>(t);
			Numeric v_27 = std::get<8>(t);
			Integer v_28 = std::get<9>(t);
			Varchar<1> v_19 = std::get<10>(t);
			Varchar<1> v_20 = std::get<11>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_21 << ", " << v_22 << ", " << v_23 << ", " << v_24 << ", " << v_25 << ", " << v_26 << ", " << v_27 << ", " << v_28 << ", " << v_19 << ", " << v_20 << std::endl;
			}
		}
	}},
}},
	{"all", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		std::vector<std::tuple<Varchar<1>, Varchar<1>, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Integer, Varchar<1>, Varchar<1>>> v_1;
		std::unordered_map<std::tuple<Varchar<1>, Varchar<1>>, std::tuple<Numeric, Numeric, Numeric, Numeric, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, Integer>> v_2;
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			Integer v_3 = key.l_orderkey;
			Integer v_4 = value.l_partkey;
			Integer v_5 = value.l_suppkey;
			Integer v_6 = value.l_linenumber;
			Numeric v_7 = value.l_quantity;
			Numeric v_8 = value.l_extendedprice;
			Numeric v_9 = value.l_discount;
			Numeric v_10 = value.l_tax;
			Varchar<1> v_11 = value.l_returnflag;
			Varchar<1> v_12 = value.l_linestatus;
			Timestamp v_13 = value.l_shipdate;
			Timestamp v_14 = value.l_commitdate;
			Timestamp v_15 = value.l_receiptdate;
			Varchar<25> v_16 = value.l_shipinstruct;
			Varchar<10> v_17 = value.l_shipmode;
			Varchar<44> v_18 = value.l_comment;
			if (v_13 <= (2451058)) {
				auto it = v_2.find({v_11, v_12});
				if (it == v_2.end()) {
					v_2.insert({{v_11, v_12}, {v_7, v_8, v_8 * (1 - v_9), (v_8 * (1 - v_9)) * (1 + v_10), {v_7, 1}, {v_8, 1}, {v_9, 1}, 1}});
				} else {
					std::get<0>(it->second) += v_7;
					std::get<1>(it->second) += v_8;
					std::get<2>(it->second) += v_8 * (1 - v_9);
					std::get<3>(it->second) += (v_8 * (1 - v_9)) * (1 + v_10);
					std::get<4>(it->second) = {std::get<4>(it->second).first + v_7, std::get<4>(it->second).second + 1};
					std::get<5>(it->second) = {std::get<5>(it->second).first + v_8, std::get<5>(it->second).second + 1};
					std::get<6>(it->second) = {std::get<6>(it->second).first + v_9, std::get<6>(it->second).second + 1};
					std::get<7>(it->second) += 1;
				}
			}
		});
		for (auto& it : v_2) {
			Varchar<1> v_19 = std::get<0>(it.first);
			Varchar<1> v_20 = std::get<1>(it.first);
			Numeric v_21 = std::get<0>(it.second);
			Numeric v_22 = std::get<1>(it.second);
			Numeric v_23 = std::get<2>(it.second);
			Numeric v_24 = std::get<3>(it.second);
			Numeric v_25 = std::get<4>(it.second).first / (double)std::get<4>(it.second).second;
			Numeric v_26 = std::get<5>(it.second).first / (double)std::get<5>(it.second).second;
			Numeric v_27 = std::get<6>(it.second).first / (double)std::get<6>(it.second).second;
			Integer v_28 = std::get<7>(it.second);
			v_1.push_back({v_19, v_20, v_21, v_22, v_23, v_24, v_25, v_26, v_27, v_28, v_19, v_20});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			if (get<1>(t1) < get<1>(t2)) return true;
			if (get<1>(t2) < get<1>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			Numeric v_21 = std::get<2>(t);
			Numeric v_22 = std::get<3>(t);
			Numeric v_23 = std::get<4>(t);
			Numeric v_24 = std::get<5>(t);
			Numeric v_25 = std::get<6>(t);
			Numeric v_26 = std::get<7>(t);
			Numeric v_27 = std::get<8>(t);
			Integer v_28 = std::get<9>(t);
			Varchar<1> v_19 = std::get<10>(t);
			Varchar<1> v_20 = std::get<11>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_21 << ", " << v_22 << ", " << v_23 << ", " << v_24 << ", " << v_25 << ", " << v_26 << ", " << v_27 << ", " << v_28 << ", " << v_19 << ", " << v_20 << std::endl;
			}
		}
	}},
}},
};
