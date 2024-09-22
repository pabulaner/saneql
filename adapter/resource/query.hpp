std::map<std::string, std::map<std::string, std::function<void(Database*, size_t)>>> queries = {
	{"none", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "l_returnflag" << ", " << "l_linestatus" << ", " << "sum_qty" << ", " << "sum_base_price" << ", " << "sum_disc_price" << ", " << "sum_charge" << ", " << "avg_qty" << ", " << "avg_price" << ", " << "avg_disc" << ", " << "count_order" << std::endl;
		}
		std::vector<std::tuple<Varchar<1>, Varchar<1>, Varchar<1>, Varchar<1>, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Integer>> v_1;
		std::unordered_map<std::tuple<Varchar<1>, Varchar<1>>, std::tuple<Numeric, Numeric, Numeric, Numeric, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, Integer>> v_2;
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Numeric& v_3 = value.l_quantity;
			const Numeric& v_4 = value.l_extendedprice;
			const Numeric& v_5 = value.l_discount;
			const Numeric& v_6 = value.l_tax;
			const Varchar<1>& v_7 = value.l_returnflag;
			const Varchar<1>& v_8 = value.l_linestatus;
			const Timestamp& v_9 = value.l_shipdate;
			if (v_9 <= (2451058)) {
				auto it = v_2.find({v_7, v_8});
				if (it == v_2.end()) {
					v_2.insert({{v_7, v_8}, {v_3, v_4, v_4 * (1 - v_5), (v_4 * (1 - v_5)) * (1 + v_6), {v_3, 1}, {v_4, 1}, {v_5, 1}, 1}});
				} else {
					std::get<0>(it->second) += v_3;
					std::get<1>(it->second) += v_4;
					std::get<2>(it->second) += v_4 * (1 - v_5);
					std::get<3>(it->second) += (v_4 * (1 - v_5)) * (1 + v_6);
					std::get<4>(it->second) = {std::get<4>(it->second).first + v_3, std::get<4>(it->second).second + 1};
					std::get<5>(it->second) = {std::get<5>(it->second).first + v_4, std::get<5>(it->second).second + 1};
					std::get<6>(it->second) = {std::get<6>(it->second).first + v_5, std::get<6>(it->second).second + 1};
					std::get<7>(it->second) += 1;
				}
			}
		});
		for (auto& it : v_2) {
			const Varchar<1>& v_10 = std::get<0>(it.first);
			const Varchar<1>& v_11 = std::get<1>(it.first);
			const Numeric& v_12 = std::get<0>(it.second);
			const Numeric& v_13 = std::get<1>(it.second);
			const Numeric& v_14 = std::get<2>(it.second);
			const Numeric& v_15 = std::get<3>(it.second);
			const Numeric v_16 = std::get<4>(it.second).first / (double)std::get<4>(it.second).second;
			const Numeric v_17 = std::get<5>(it.second).first / (double)std::get<5>(it.second).second;
			const Numeric v_18 = std::get<6>(it.second).first / (double)std::get<6>(it.second).second;
			const Integer& v_19 = std::get<7>(it.second);
			v_1.push_back({v_10, v_11, v_10, v_11, v_12, v_13, v_14, v_15, v_16, v_17, v_18, v_19});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			if (get<1>(t1) < get<1>(t2)) return true;
			if (get<1>(t2) < get<1>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Varchar<1>& v_10 = std::get<2>(t);
			const Varchar<1>& v_11 = std::get<3>(t);
			const Numeric& v_12 = std::get<4>(t);
			const Numeric& v_13 = std::get<5>(t);
			const Numeric& v_14 = std::get<6>(t);
			const Numeric& v_15 = std::get<7>(t);
			const Numeric& v_16 = std::get<8>(t);
			const Numeric& v_17 = std::get<9>(t);
			const Numeric& v_18 = std::get<10>(t);
			const Integer& v_19 = std::get<11>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_12 << ", " << v_13 << ", " << v_14 << ", " << v_15 << ", " << v_16 << ", " << v_17 << ", " << v_18 << ", " << v_19 << ", " << v_10 << ", " << v_11 << std::endl;
			}
		}
	}},
}},
	{"selects", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "l_returnflag" << ", " << "l_linestatus" << ", " << "sum_qty" << ", " << "sum_base_price" << ", " << "sum_disc_price" << ", " << "sum_charge" << ", " << "avg_qty" << ", " << "avg_price" << ", " << "avg_disc" << ", " << "count_order" << std::endl;
		}
		std::vector<std::tuple<Varchar<1>, Varchar<1>, Varchar<1>, Varchar<1>, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Integer>> v_1;
		std::unordered_map<std::tuple<Varchar<1>, Varchar<1>>, std::tuple<Numeric, Numeric, Numeric, Numeric, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, Integer>> v_2;
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Numeric& v_3 = value.l_quantity;
			const Numeric& v_4 = value.l_extendedprice;
			const Numeric& v_5 = value.l_discount;
			const Numeric& v_6 = value.l_tax;
			const Varchar<1>& v_7 = value.l_returnflag;
			const Varchar<1>& v_8 = value.l_linestatus;
			const Timestamp& v_9 = value.l_shipdate;
			if (v_9 <= (2451058)) {
				auto it = v_2.find({v_7, v_8});
				if (it == v_2.end()) {
					v_2.insert({{v_7, v_8}, {v_3, v_4, v_4 * (1 - v_5), (v_4 * (1 - v_5)) * (1 + v_6), {v_3, 1}, {v_4, 1}, {v_5, 1}, 1}});
				} else {
					std::get<0>(it->second) += v_3;
					std::get<1>(it->second) += v_4;
					std::get<2>(it->second) += v_4 * (1 - v_5);
					std::get<3>(it->second) += (v_4 * (1 - v_5)) * (1 + v_6);
					std::get<4>(it->second) = {std::get<4>(it->second).first + v_3, std::get<4>(it->second).second + 1};
					std::get<5>(it->second) = {std::get<5>(it->second).first + v_4, std::get<5>(it->second).second + 1};
					std::get<6>(it->second) = {std::get<6>(it->second).first + v_5, std::get<6>(it->second).second + 1};
					std::get<7>(it->second) += 1;
				}
			}
		});
		for (auto& it : v_2) {
			const Varchar<1>& v_10 = std::get<0>(it.first);
			const Varchar<1>& v_11 = std::get<1>(it.first);
			const Numeric& v_12 = std::get<0>(it.second);
			const Numeric& v_13 = std::get<1>(it.second);
			const Numeric& v_14 = std::get<2>(it.second);
			const Numeric& v_15 = std::get<3>(it.second);
			const Numeric v_16 = std::get<4>(it.second).first / (double)std::get<4>(it.second).second;
			const Numeric v_17 = std::get<5>(it.second).first / (double)std::get<5>(it.second).second;
			const Numeric v_18 = std::get<6>(it.second).first / (double)std::get<6>(it.second).second;
			const Integer& v_19 = std::get<7>(it.second);
			v_1.push_back({v_10, v_11, v_10, v_11, v_12, v_13, v_14, v_15, v_16, v_17, v_18, v_19});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			if (get<1>(t1) < get<1>(t2)) return true;
			if (get<1>(t2) < get<1>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Varchar<1>& v_10 = std::get<2>(t);
			const Varchar<1>& v_11 = std::get<3>(t);
			const Numeric& v_12 = std::get<4>(t);
			const Numeric& v_13 = std::get<5>(t);
			const Numeric& v_14 = std::get<6>(t);
			const Numeric& v_15 = std::get<7>(t);
			const Numeric& v_16 = std::get<8>(t);
			const Numeric& v_17 = std::get<9>(t);
			const Numeric& v_18 = std::get<10>(t);
			const Integer& v_19 = std::get<11>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_12 << ", " << v_13 << ", " << v_14 << ", " << v_15 << ", " << v_16 << ", " << v_17 << ", " << v_18 << ", " << v_19 << ", " << v_10 << ", " << v_11 << std::endl;
			}
		}
	}},
}},
	{"scans", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "l_returnflag" << ", " << "l_linestatus" << ", " << "sum_qty" << ", " << "sum_base_price" << ", " << "sum_disc_price" << ", " << "sum_charge" << ", " << "avg_qty" << ", " << "avg_price" << ", " << "avg_disc" << ", " << "count_order" << std::endl;
		}
		std::vector<std::tuple<Varchar<1>, Varchar<1>, Varchar<1>, Varchar<1>, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Integer>> v_1;
		std::unordered_map<std::tuple<Varchar<1>, Varchar<1>>, std::tuple<Numeric, Numeric, Numeric, Numeric, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, Integer>> v_2;
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Numeric& v_3 = value.l_quantity;
			const Numeric& v_4 = value.l_extendedprice;
			const Numeric& v_5 = value.l_discount;
			const Numeric& v_6 = value.l_tax;
			const Varchar<1>& v_7 = value.l_returnflag;
			const Varchar<1>& v_8 = value.l_linestatus;
			const Timestamp& v_9 = value.l_shipdate;
			if (v_9 <= (2451058)) {
				auto it = v_2.find({v_7, v_8});
				if (it == v_2.end()) {
					v_2.insert({{v_7, v_8}, {v_3, v_4, v_4 * (1 - v_5), (v_4 * (1 - v_5)) * (1 + v_6), {v_3, 1}, {v_4, 1}, {v_5, 1}, 1}});
				} else {
					std::get<0>(it->second) += v_3;
					std::get<1>(it->second) += v_4;
					std::get<2>(it->second) += v_4 * (1 - v_5);
					std::get<3>(it->second) += (v_4 * (1 - v_5)) * (1 + v_6);
					std::get<4>(it->second) = {std::get<4>(it->second).first + v_3, std::get<4>(it->second).second + 1};
					std::get<5>(it->second) = {std::get<5>(it->second).first + v_4, std::get<5>(it->second).second + 1};
					std::get<6>(it->second) = {std::get<6>(it->second).first + v_5, std::get<6>(it->second).second + 1};
					std::get<7>(it->second) += 1;
				}
			}
		});
		for (auto& it : v_2) {
			const Varchar<1>& v_10 = std::get<0>(it.first);
			const Varchar<1>& v_11 = std::get<1>(it.first);
			const Numeric& v_12 = std::get<0>(it.second);
			const Numeric& v_13 = std::get<1>(it.second);
			const Numeric& v_14 = std::get<2>(it.second);
			const Numeric& v_15 = std::get<3>(it.second);
			const Numeric v_16 = std::get<4>(it.second).first / (double)std::get<4>(it.second).second;
			const Numeric v_17 = std::get<5>(it.second).first / (double)std::get<5>(it.second).second;
			const Numeric v_18 = std::get<6>(it.second).first / (double)std::get<6>(it.second).second;
			const Integer& v_19 = std::get<7>(it.second);
			v_1.push_back({v_10, v_11, v_10, v_11, v_12, v_13, v_14, v_15, v_16, v_17, v_18, v_19});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			if (get<1>(t1) < get<1>(t2)) return true;
			if (get<1>(t2) < get<1>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Varchar<1>& v_10 = std::get<2>(t);
			const Varchar<1>& v_11 = std::get<3>(t);
			const Numeric& v_12 = std::get<4>(t);
			const Numeric& v_13 = std::get<5>(t);
			const Numeric& v_14 = std::get<6>(t);
			const Numeric& v_15 = std::get<7>(t);
			const Numeric& v_16 = std::get<8>(t);
			const Numeric& v_17 = std::get<9>(t);
			const Numeric& v_18 = std::get<10>(t);
			const Integer& v_19 = std::get<11>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_12 << ", " << v_13 << ", " << v_14 << ", " << v_15 << ", " << v_16 << ", " << v_17 << ", " << v_18 << ", " << v_19 << ", " << v_10 << ", " << v_11 << std::endl;
			}
		}
	}},
}},
	{"joins", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "l_returnflag" << ", " << "l_linestatus" << ", " << "sum_qty" << ", " << "sum_base_price" << ", " << "sum_disc_price" << ", " << "sum_charge" << ", " << "avg_qty" << ", " << "avg_price" << ", " << "avg_disc" << ", " << "count_order" << std::endl;
		}
		std::vector<std::tuple<Varchar<1>, Varchar<1>, Varchar<1>, Varchar<1>, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Integer>> v_1;
		std::unordered_map<std::tuple<Varchar<1>, Varchar<1>>, std::tuple<Numeric, Numeric, Numeric, Numeric, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, Integer>> v_2;
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Numeric& v_3 = value.l_quantity;
			const Numeric& v_4 = value.l_extendedprice;
			const Numeric& v_5 = value.l_discount;
			const Numeric& v_6 = value.l_tax;
			const Varchar<1>& v_7 = value.l_returnflag;
			const Varchar<1>& v_8 = value.l_linestatus;
			const Timestamp& v_9 = value.l_shipdate;
			if (v_9 <= (2451058)) {
				auto it = v_2.find({v_7, v_8});
				if (it == v_2.end()) {
					v_2.insert({{v_7, v_8}, {v_3, v_4, v_4 * (1 - v_5), (v_4 * (1 - v_5)) * (1 + v_6), {v_3, 1}, {v_4, 1}, {v_5, 1}, 1}});
				} else {
					std::get<0>(it->second) += v_3;
					std::get<1>(it->second) += v_4;
					std::get<2>(it->second) += v_4 * (1 - v_5);
					std::get<3>(it->second) += (v_4 * (1 - v_5)) * (1 + v_6);
					std::get<4>(it->second) = {std::get<4>(it->second).first + v_3, std::get<4>(it->second).second + 1};
					std::get<5>(it->second) = {std::get<5>(it->second).first + v_4, std::get<5>(it->second).second + 1};
					std::get<6>(it->second) = {std::get<6>(it->second).first + v_5, std::get<6>(it->second).second + 1};
					std::get<7>(it->second) += 1;
				}
			}
		});
		for (auto& it : v_2) {
			const Varchar<1>& v_10 = std::get<0>(it.first);
			const Varchar<1>& v_11 = std::get<1>(it.first);
			const Numeric& v_12 = std::get<0>(it.second);
			const Numeric& v_13 = std::get<1>(it.second);
			const Numeric& v_14 = std::get<2>(it.second);
			const Numeric& v_15 = std::get<3>(it.second);
			const Numeric v_16 = std::get<4>(it.second).first / (double)std::get<4>(it.second).second;
			const Numeric v_17 = std::get<5>(it.second).first / (double)std::get<5>(it.second).second;
			const Numeric v_18 = std::get<6>(it.second).first / (double)std::get<6>(it.second).second;
			const Integer& v_19 = std::get<7>(it.second);
			v_1.push_back({v_10, v_11, v_10, v_11, v_12, v_13, v_14, v_15, v_16, v_17, v_18, v_19});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			if (get<1>(t1) < get<1>(t2)) return true;
			if (get<1>(t2) < get<1>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Varchar<1>& v_10 = std::get<2>(t);
			const Varchar<1>& v_11 = std::get<3>(t);
			const Numeric& v_12 = std::get<4>(t);
			const Numeric& v_13 = std::get<5>(t);
			const Numeric& v_14 = std::get<6>(t);
			const Numeric& v_15 = std::get<7>(t);
			const Numeric& v_16 = std::get<8>(t);
			const Numeric& v_17 = std::get<9>(t);
			const Numeric& v_18 = std::get<10>(t);
			const Integer& v_19 = std::get<11>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_12 << ", " << v_13 << ", " << v_14 << ", " << v_15 << ", " << v_16 << ", " << v_17 << ", " << v_18 << ", " << v_19 << ", " << v_10 << ", " << v_11 << std::endl;
			}
		}
	}},
}},
	{"all", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "l_returnflag" << ", " << "l_linestatus" << ", " << "sum_qty" << ", " << "sum_base_price" << ", " << "sum_disc_price" << ", " << "sum_charge" << ", " << "avg_qty" << ", " << "avg_price" << ", " << "avg_disc" << ", " << "count_order" << std::endl;
		}
		std::vector<std::tuple<Varchar<1>, Varchar<1>, Varchar<1>, Varchar<1>, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Integer>> v_1;
		std::unordered_map<std::tuple<Varchar<1>, Varchar<1>>, std::tuple<Numeric, Numeric, Numeric, Numeric, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, Integer>> v_2;
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Numeric& v_3 = value.l_quantity;
			const Numeric& v_4 = value.l_extendedprice;
			const Numeric& v_5 = value.l_discount;
			const Numeric& v_6 = value.l_tax;
			const Varchar<1>& v_7 = value.l_returnflag;
			const Varchar<1>& v_8 = value.l_linestatus;
			const Timestamp& v_9 = value.l_shipdate;
			if (v_9 <= (2451058)) {
				auto it = v_2.find({v_7, v_8});
				if (it == v_2.end()) {
					v_2.insert({{v_7, v_8}, {v_3, v_4, v_4 * (1 - v_5), (v_4 * (1 - v_5)) * (1 + v_6), {v_3, 1}, {v_4, 1}, {v_5, 1}, 1}});
				} else {
					std::get<0>(it->second) += v_3;
					std::get<1>(it->second) += v_4;
					std::get<2>(it->second) += v_4 * (1 - v_5);
					std::get<3>(it->second) += (v_4 * (1 - v_5)) * (1 + v_6);
					std::get<4>(it->second) = {std::get<4>(it->second).first + v_3, std::get<4>(it->second).second + 1};
					std::get<5>(it->second) = {std::get<5>(it->second).first + v_4, std::get<5>(it->second).second + 1};
					std::get<6>(it->second) = {std::get<6>(it->second).first + v_5, std::get<6>(it->second).second + 1};
					std::get<7>(it->second) += 1;
				}
			}
		});
		for (auto& it : v_2) {
			const Varchar<1>& v_10 = std::get<0>(it.first);
			const Varchar<1>& v_11 = std::get<1>(it.first);
			const Numeric& v_12 = std::get<0>(it.second);
			const Numeric& v_13 = std::get<1>(it.second);
			const Numeric& v_14 = std::get<2>(it.second);
			const Numeric& v_15 = std::get<3>(it.second);
			const Numeric v_16 = std::get<4>(it.second).first / (double)std::get<4>(it.second).second;
			const Numeric v_17 = std::get<5>(it.second).first / (double)std::get<5>(it.second).second;
			const Numeric v_18 = std::get<6>(it.second).first / (double)std::get<6>(it.second).second;
			const Integer& v_19 = std::get<7>(it.second);
			v_1.push_back({v_10, v_11, v_10, v_11, v_12, v_13, v_14, v_15, v_16, v_17, v_18, v_19});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			if (get<1>(t1) < get<1>(t2)) return true;
			if (get<1>(t2) < get<1>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Varchar<1>& v_10 = std::get<2>(t);
			const Varchar<1>& v_11 = std::get<3>(t);
			const Numeric& v_12 = std::get<4>(t);
			const Numeric& v_13 = std::get<5>(t);
			const Numeric& v_14 = std::get<6>(t);
			const Numeric& v_15 = std::get<7>(t);
			const Numeric& v_16 = std::get<8>(t);
			const Numeric& v_17 = std::get<9>(t);
			const Numeric& v_18 = std::get<10>(t);
			const Integer& v_19 = std::get<11>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_12 << ", " << v_13 << ", " << v_14 << ", " << v_15 << ", " << v_16 << ", " << v_17 << ", " << v_18 << ", " << v_19 << ", " << v_10 << ", " << v_11 << std::endl;
			}
		}
	}},
}},
};
