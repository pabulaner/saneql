std::map<std::string, std::map<std::string, std::function<void(Database*, size_t)>>> queries = {
	{"none", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		std::cout << ([&]() {
			Integer v_1 = 0;
			std::unordered_multimap<std::tuple<Integer, Integer>, std::tuple<Integer, Integer, Integer, Integer, Timestamp, Numeric, Numeric, Varchar<24>>> v_2;
			db->orderline.forEach([&](auto& key, auto& value) {
				const Integer& v_3 = key.ol_w_id;
				const Integer& v_4 = key.ol_d_id;
				const Integer& v_5 = key.ol_o_id;
				const Integer& v_6 = key.ol_number;
				const Integer& v_7 = value.ol_i_id;
				const Integer& v_8 = value.ol_supply_w_id;
				const Timestamp& v_9 = value.ol_delivery_d;
				const Numeric& v_10 = value.ol_quantity;
				const Numeric& v_11 = value.ol_amount;
				const Varchar<24>& v_12 = value.ol_dist_info;
				if ((((v_3 == 0) && (v_4 == 5)) && (v_5 == 0)) && (v_5 > (0 - 20))) {
					v_2.insert({{v_7, v_3}, {v_4, v_5, v_6, v_8, v_9, v_10, v_11, v_12}});
				}
			});
			db->stock.forEach([&](auto& key, auto& value) {
				const Integer& v_13 = key.s_w_id;
				const Integer& v_14 = key.s_i_id;
				const Numeric& v_15 = value.s_quantity;
				const Varchar<24>& v_16 = value.s_dist_01;
				const Varchar<24>& v_17 = value.s_dist_02;
				const Varchar<24>& v_18 = value.s_dist_03;
				const Varchar<24>& v_19 = value.s_dist_04;
				const Varchar<24>& v_20 = value.s_dist_05;
				const Varchar<24>& v_21 = value.s_dist_06;
				const Varchar<24>& v_22 = value.s_dist_07;
				const Varchar<24>& v_23 = value.s_dist_08;
				const Varchar<24>& v_24 = value.s_dist_09;
				const Varchar<24>& v_25 = value.s_dist_10;
				const Numeric& v_26 = value.s_ytd;
				const Numeric& v_27 = value.s_order_cnt;
				const Numeric& v_28 = value.s_remote_cnt;
				const Varchar<50>& v_29 = value.s_data;
				if (v_15 < 10) {
					for (auto range = v_2.equal_range({v_14, v_13}); range.first!=range.second; range.first++) {
						const Integer& v_7 = std::get<0>(range.first->first);
						const Integer& v_3 = std::get<1>(range.first->first);
						const Integer& v_4 = std::get<0>(range.first->second);
						const Integer& v_5 = std::get<1>(range.first->second);
						const Integer& v_6 = std::get<2>(range.first->second);
						const Integer& v_8 = std::get<3>(range.first->second);
						const Timestamp& v_9 = std::get<4>(range.first->second);
						const Numeric& v_10 = std::get<5>(range.first->second);
						const Numeric& v_11 = std::get<6>(range.first->second);
						const Varchar<24>& v_12 = std::get<7>(range.first->second);
						v_1 += 1;
					}
				}
			});
			return v_1;
		}()) + ([&]() {
			Integer v_30 = 0;
			std::unordered_multimap<std::tuple<Integer, Integer>, std::tuple<Integer, Integer, Integer, Integer, Timestamp, Numeric, Numeric, Varchar<24>>> v_31;
			db->orderline.forEach([&](auto& key, auto& value) {
				const Integer& v_32 = key.ol_w_id;
				const Integer& v_33 = key.ol_d_id;
				const Integer& v_34 = key.ol_o_id;
				const Integer& v_35 = key.ol_number;
				const Integer& v_36 = value.ol_i_id;
				const Integer& v_37 = value.ol_supply_w_id;
				const Timestamp& v_38 = value.ol_delivery_d;
				const Numeric& v_39 = value.ol_quantity;
				const Numeric& v_40 = value.ol_amount;
				const Varchar<24>& v_41 = value.ol_dist_info;
				if ((((v_32 == 1) && (v_33 == 6)) && (v_34 == 1)) && (v_34 > (1 - 20))) {
					v_31.insert({{v_36, v_32}, {v_33, v_34, v_35, v_37, v_38, v_39, v_40, v_41}});
				}
			});
			db->stock.forEach([&](auto& key, auto& value) {
				const Integer& v_42 = key.s_w_id;
				const Integer& v_43 = key.s_i_id;
				const Numeric& v_44 = value.s_quantity;
				const Varchar<24>& v_45 = value.s_dist_01;
				const Varchar<24>& v_46 = value.s_dist_02;
				const Varchar<24>& v_47 = value.s_dist_03;
				const Varchar<24>& v_48 = value.s_dist_04;
				const Varchar<24>& v_49 = value.s_dist_05;
				const Varchar<24>& v_50 = value.s_dist_06;
				const Varchar<24>& v_51 = value.s_dist_07;
				const Varchar<24>& v_52 = value.s_dist_08;
				const Varchar<24>& v_53 = value.s_dist_09;
				const Varchar<24>& v_54 = value.s_dist_10;
				const Numeric& v_55 = value.s_ytd;
				const Numeric& v_56 = value.s_order_cnt;
				const Numeric& v_57 = value.s_remote_cnt;
				const Varchar<50>& v_58 = value.s_data;
				if (v_44 < 11) {
					for (auto range = v_31.equal_range({v_43, v_42}); range.first!=range.second; range.first++) {
						const Integer& v_36 = std::get<0>(range.first->first);
						const Integer& v_32 = std::get<1>(range.first->first);
						const Integer& v_33 = std::get<0>(range.first->second);
						const Integer& v_34 = std::get<1>(range.first->second);
						const Integer& v_35 = std::get<2>(range.first->second);
						const Integer& v_37 = std::get<3>(range.first->second);
						const Timestamp& v_38 = std::get<4>(range.first->second);
						const Numeric& v_39 = std::get<5>(range.first->second);
						const Numeric& v_40 = std::get<6>(range.first->second);
						const Varchar<24>& v_41 = std::get<7>(range.first->second);
						v_30 += 1;
					}
				}
			});
			return v_30;
		}()) << std::endl;
	}},
}},
	{"selects", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		std::cout << ([&]() {
			Integer v_1 = 0;
			std::unordered_multimap<std::tuple<Integer, Integer>, std::tuple<Integer, Integer, Integer, Integer, Timestamp, Numeric, Numeric, Varchar<24>>> v_2;
			db->orderline.forEach([&](auto& key, auto& value) {
				const Integer& v_3 = key.ol_w_id;
				const Integer& v_4 = key.ol_d_id;
				const Integer& v_5 = key.ol_o_id;
				const Integer& v_6 = key.ol_number;
				const Integer& v_7 = value.ol_i_id;
				const Integer& v_8 = value.ol_supply_w_id;
				const Timestamp& v_9 = value.ol_delivery_d;
				const Numeric& v_10 = value.ol_quantity;
				const Numeric& v_11 = value.ol_amount;
				const Varchar<24>& v_12 = value.ol_dist_info;
				if ((((v_3 == 0) && (v_4 == 5)) && (v_5 == 0)) && (v_5 > (0 - 20))) {
					v_2.insert({{v_7, v_3}, {v_4, v_5, v_6, v_8, v_9, v_10, v_11, v_12}});
				}
			});
			db->stock.forEach([&](auto& key, auto& value) {
				const Integer& v_13 = key.s_w_id;
				const Integer& v_14 = key.s_i_id;
				const Numeric& v_15 = value.s_quantity;
				const Varchar<24>& v_16 = value.s_dist_01;
				const Varchar<24>& v_17 = value.s_dist_02;
				const Varchar<24>& v_18 = value.s_dist_03;
				const Varchar<24>& v_19 = value.s_dist_04;
				const Varchar<24>& v_20 = value.s_dist_05;
				const Varchar<24>& v_21 = value.s_dist_06;
				const Varchar<24>& v_22 = value.s_dist_07;
				const Varchar<24>& v_23 = value.s_dist_08;
				const Varchar<24>& v_24 = value.s_dist_09;
				const Varchar<24>& v_25 = value.s_dist_10;
				const Numeric& v_26 = value.s_ytd;
				const Numeric& v_27 = value.s_order_cnt;
				const Numeric& v_28 = value.s_remote_cnt;
				const Varchar<50>& v_29 = value.s_data;
				if (v_15 < 10) {
					for (auto range = v_2.equal_range({v_14, v_13}); range.first!=range.second; range.first++) {
						const Integer& v_7 = std::get<0>(range.first->first);
						const Integer& v_3 = std::get<1>(range.first->first);
						const Integer& v_4 = std::get<0>(range.first->second);
						const Integer& v_5 = std::get<1>(range.first->second);
						const Integer& v_6 = std::get<2>(range.first->second);
						const Integer& v_8 = std::get<3>(range.first->second);
						const Timestamp& v_9 = std::get<4>(range.first->second);
						const Numeric& v_10 = std::get<5>(range.first->second);
						const Numeric& v_11 = std::get<6>(range.first->second);
						const Varchar<24>& v_12 = std::get<7>(range.first->second);
						v_1 += 1;
					}
				}
			});
			return v_1;
		}()) + ([&]() {
			Integer v_30 = 0;
			std::unordered_multimap<std::tuple<Integer, Integer>, std::tuple<Integer, Integer, Integer, Integer, Timestamp, Numeric, Numeric, Varchar<24>>> v_31;
			db->orderline.forEach([&](auto& key, auto& value) {
				const Integer& v_32 = key.ol_w_id;
				const Integer& v_33 = key.ol_d_id;
				const Integer& v_34 = key.ol_o_id;
				const Integer& v_35 = key.ol_number;
				const Integer& v_36 = value.ol_i_id;
				const Integer& v_37 = value.ol_supply_w_id;
				const Timestamp& v_38 = value.ol_delivery_d;
				const Numeric& v_39 = value.ol_quantity;
				const Numeric& v_40 = value.ol_amount;
				const Varchar<24>& v_41 = value.ol_dist_info;
				if ((((v_32 == 1) && (v_33 == 6)) && (v_34 == 1)) && (v_34 > (1 - 20))) {
					v_31.insert({{v_36, v_32}, {v_33, v_34, v_35, v_37, v_38, v_39, v_40, v_41}});
				}
			});
			db->stock.forEach([&](auto& key, auto& value) {
				const Integer& v_42 = key.s_w_id;
				const Integer& v_43 = key.s_i_id;
				const Numeric& v_44 = value.s_quantity;
				const Varchar<24>& v_45 = value.s_dist_01;
				const Varchar<24>& v_46 = value.s_dist_02;
				const Varchar<24>& v_47 = value.s_dist_03;
				const Varchar<24>& v_48 = value.s_dist_04;
				const Varchar<24>& v_49 = value.s_dist_05;
				const Varchar<24>& v_50 = value.s_dist_06;
				const Varchar<24>& v_51 = value.s_dist_07;
				const Varchar<24>& v_52 = value.s_dist_08;
				const Varchar<24>& v_53 = value.s_dist_09;
				const Varchar<24>& v_54 = value.s_dist_10;
				const Numeric& v_55 = value.s_ytd;
				const Numeric& v_56 = value.s_order_cnt;
				const Numeric& v_57 = value.s_remote_cnt;
				const Varchar<50>& v_58 = value.s_data;
				if (v_44 < 11) {
					for (auto range = v_31.equal_range({v_43, v_42}); range.first!=range.second; range.first++) {
						const Integer& v_36 = std::get<0>(range.first->first);
						const Integer& v_32 = std::get<1>(range.first->first);
						const Integer& v_33 = std::get<0>(range.first->second);
						const Integer& v_34 = std::get<1>(range.first->second);
						const Integer& v_35 = std::get<2>(range.first->second);
						const Integer& v_37 = std::get<3>(range.first->second);
						const Timestamp& v_38 = std::get<4>(range.first->second);
						const Numeric& v_39 = std::get<5>(range.first->second);
						const Numeric& v_40 = std::get<6>(range.first->second);
						const Varchar<24>& v_41 = std::get<7>(range.first->second);
						v_30 += 1;
					}
				}
			});
			return v_30;
		}()) << std::endl;
	}},
}},
	{"scans", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		std::cout << ([&]() {
			Integer v_1 = 0;
			std::unordered_multimap<std::tuple<Integer, Integer>, std::tuple<Integer, Integer, Integer, Integer, Timestamp, Numeric, Numeric, Varchar<24>>> v_2;
			db->orderline.forEach([&](auto& key, auto& value) {
				const Integer& v_3 = key.ol_w_id;
				const Integer& v_4 = key.ol_d_id;
				const Integer& v_5 = key.ol_o_id;
				const Integer& v_6 = key.ol_number;
				const Integer& v_7 = value.ol_i_id;
				const Integer& v_8 = value.ol_supply_w_id;
				const Timestamp& v_9 = value.ol_delivery_d;
				const Numeric& v_10 = value.ol_quantity;
				const Numeric& v_11 = value.ol_amount;
				const Varchar<24>& v_12 = value.ol_dist_info;
				if ((((v_3 == 0) && (v_4 == 5)) && (v_5 == 0)) && (v_5 > (0 - 20))) {
					v_2.insert({{v_7, v_3}, {v_4, v_5, v_6, v_8, v_9, v_10, v_11, v_12}});
				}
			});
			db->stock.forEach([&](auto& key, auto& value) {
				const Integer& v_13 = key.s_w_id;
				const Integer& v_14 = key.s_i_id;
				const Numeric& v_15 = value.s_quantity;
				const Varchar<24>& v_16 = value.s_dist_01;
				const Varchar<24>& v_17 = value.s_dist_02;
				const Varchar<24>& v_18 = value.s_dist_03;
				const Varchar<24>& v_19 = value.s_dist_04;
				const Varchar<24>& v_20 = value.s_dist_05;
				const Varchar<24>& v_21 = value.s_dist_06;
				const Varchar<24>& v_22 = value.s_dist_07;
				const Varchar<24>& v_23 = value.s_dist_08;
				const Varchar<24>& v_24 = value.s_dist_09;
				const Varchar<24>& v_25 = value.s_dist_10;
				const Numeric& v_26 = value.s_ytd;
				const Numeric& v_27 = value.s_order_cnt;
				const Numeric& v_28 = value.s_remote_cnt;
				const Varchar<50>& v_29 = value.s_data;
				if (v_15 < 10) {
					for (auto range = v_2.equal_range({v_14, v_13}); range.first!=range.second; range.first++) {
						const Integer& v_7 = std::get<0>(range.first->first);
						const Integer& v_3 = std::get<1>(range.first->first);
						const Integer& v_4 = std::get<0>(range.first->second);
						const Integer& v_5 = std::get<1>(range.first->second);
						const Integer& v_6 = std::get<2>(range.first->second);
						const Integer& v_8 = std::get<3>(range.first->second);
						const Timestamp& v_9 = std::get<4>(range.first->second);
						const Numeric& v_10 = std::get<5>(range.first->second);
						const Numeric& v_11 = std::get<6>(range.first->second);
						const Varchar<24>& v_12 = std::get<7>(range.first->second);
						v_1 += 1;
					}
				}
			});
			return v_1;
		}()) + ([&]() {
			Integer v_30 = 0;
			std::unordered_multimap<std::tuple<Integer, Integer>, std::tuple<Integer, Integer, Integer, Integer, Timestamp, Numeric, Numeric, Varchar<24>>> v_31;
			db->orderline.forEach([&](auto& key, auto& value) {
				const Integer& v_32 = key.ol_w_id;
				const Integer& v_33 = key.ol_d_id;
				const Integer& v_34 = key.ol_o_id;
				const Integer& v_35 = key.ol_number;
				const Integer& v_36 = value.ol_i_id;
				const Integer& v_37 = value.ol_supply_w_id;
				const Timestamp& v_38 = value.ol_delivery_d;
				const Numeric& v_39 = value.ol_quantity;
				const Numeric& v_40 = value.ol_amount;
				const Varchar<24>& v_41 = value.ol_dist_info;
				if ((((v_32 == 1) && (v_33 == 6)) && (v_34 == 1)) && (v_34 > (1 - 20))) {
					v_31.insert({{v_36, v_32}, {v_33, v_34, v_35, v_37, v_38, v_39, v_40, v_41}});
				}
			});
			db->stock.forEach([&](auto& key, auto& value) {
				const Integer& v_42 = key.s_w_id;
				const Integer& v_43 = key.s_i_id;
				const Numeric& v_44 = value.s_quantity;
				const Varchar<24>& v_45 = value.s_dist_01;
				const Varchar<24>& v_46 = value.s_dist_02;
				const Varchar<24>& v_47 = value.s_dist_03;
				const Varchar<24>& v_48 = value.s_dist_04;
				const Varchar<24>& v_49 = value.s_dist_05;
				const Varchar<24>& v_50 = value.s_dist_06;
				const Varchar<24>& v_51 = value.s_dist_07;
				const Varchar<24>& v_52 = value.s_dist_08;
				const Varchar<24>& v_53 = value.s_dist_09;
				const Varchar<24>& v_54 = value.s_dist_10;
				const Numeric& v_55 = value.s_ytd;
				const Numeric& v_56 = value.s_order_cnt;
				const Numeric& v_57 = value.s_remote_cnt;
				const Varchar<50>& v_58 = value.s_data;
				if (v_44 < 11) {
					for (auto range = v_31.equal_range({v_43, v_42}); range.first!=range.second; range.first++) {
						const Integer& v_36 = std::get<0>(range.first->first);
						const Integer& v_32 = std::get<1>(range.first->first);
						const Integer& v_33 = std::get<0>(range.first->second);
						const Integer& v_34 = std::get<1>(range.first->second);
						const Integer& v_35 = std::get<2>(range.first->second);
						const Integer& v_37 = std::get<3>(range.first->second);
						const Timestamp& v_38 = std::get<4>(range.first->second);
						const Numeric& v_39 = std::get<5>(range.first->second);
						const Numeric& v_40 = std::get<6>(range.first->second);
						const Varchar<24>& v_41 = std::get<7>(range.first->second);
						v_30 += 1;
					}
				}
			});
			return v_30;
		}()) << std::endl;
	}},
}},
	{"joins", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		std::cout << ([&]() {
			Integer v_1 = 0;
			std::unordered_multimap<std::tuple<Integer, Integer>, std::tuple<Integer, Integer, Integer, Integer, Timestamp, Numeric, Numeric, Varchar<24>>> v_2;
			db->orderline.forEach([&](auto& key, auto& value) {
				const Integer& v_3 = key.ol_w_id;
				const Integer& v_4 = key.ol_d_id;
				const Integer& v_5 = key.ol_o_id;
				const Integer& v_6 = key.ol_number;
				const Integer& v_7 = value.ol_i_id;
				const Integer& v_8 = value.ol_supply_w_id;
				const Timestamp& v_9 = value.ol_delivery_d;
				const Numeric& v_10 = value.ol_quantity;
				const Numeric& v_11 = value.ol_amount;
				const Varchar<24>& v_12 = value.ol_dist_info;
				if ((((v_3 == 0) && (v_4 == 5)) && (v_5 == 0)) && (v_5 > (0 - 20))) {
					v_2.insert({{v_7, v_3}, {v_4, v_5, v_6, v_8, v_9, v_10, v_11, v_12}});
				}
			});
			db->stock.forEach([&](auto& key, auto& value) {
				const Integer& v_13 = key.s_w_id;
				const Integer& v_14 = key.s_i_id;
				const Numeric& v_15 = value.s_quantity;
				const Varchar<24>& v_16 = value.s_dist_01;
				const Varchar<24>& v_17 = value.s_dist_02;
				const Varchar<24>& v_18 = value.s_dist_03;
				const Varchar<24>& v_19 = value.s_dist_04;
				const Varchar<24>& v_20 = value.s_dist_05;
				const Varchar<24>& v_21 = value.s_dist_06;
				const Varchar<24>& v_22 = value.s_dist_07;
				const Varchar<24>& v_23 = value.s_dist_08;
				const Varchar<24>& v_24 = value.s_dist_09;
				const Varchar<24>& v_25 = value.s_dist_10;
				const Numeric& v_26 = value.s_ytd;
				const Numeric& v_27 = value.s_order_cnt;
				const Numeric& v_28 = value.s_remote_cnt;
				const Varchar<50>& v_29 = value.s_data;
				if (v_15 < 10) {
					for (auto range = v_2.equal_range({v_14, v_13}); range.first!=range.second; range.first++) {
						const Integer& v_7 = std::get<0>(range.first->first);
						const Integer& v_3 = std::get<1>(range.first->first);
						const Integer& v_4 = std::get<0>(range.first->second);
						const Integer& v_5 = std::get<1>(range.first->second);
						const Integer& v_6 = std::get<2>(range.first->second);
						const Integer& v_8 = std::get<3>(range.first->second);
						const Timestamp& v_9 = std::get<4>(range.first->second);
						const Numeric& v_10 = std::get<5>(range.first->second);
						const Numeric& v_11 = std::get<6>(range.first->second);
						const Varchar<24>& v_12 = std::get<7>(range.first->second);
						v_1 += 1;
					}
				}
			});
			return v_1;
		}()) + ([&]() {
			Integer v_30 = 0;
			std::unordered_multimap<std::tuple<Integer, Integer>, std::tuple<Integer, Integer, Integer, Integer, Timestamp, Numeric, Numeric, Varchar<24>>> v_31;
			db->orderline.forEach([&](auto& key, auto& value) {
				const Integer& v_32 = key.ol_w_id;
				const Integer& v_33 = key.ol_d_id;
				const Integer& v_34 = key.ol_o_id;
				const Integer& v_35 = key.ol_number;
				const Integer& v_36 = value.ol_i_id;
				const Integer& v_37 = value.ol_supply_w_id;
				const Timestamp& v_38 = value.ol_delivery_d;
				const Numeric& v_39 = value.ol_quantity;
				const Numeric& v_40 = value.ol_amount;
				const Varchar<24>& v_41 = value.ol_dist_info;
				if ((((v_32 == 1) && (v_33 == 6)) && (v_34 == 1)) && (v_34 > (1 - 20))) {
					v_31.insert({{v_36, v_32}, {v_33, v_34, v_35, v_37, v_38, v_39, v_40, v_41}});
				}
			});
			db->stock.forEach([&](auto& key, auto& value) {
				const Integer& v_42 = key.s_w_id;
				const Integer& v_43 = key.s_i_id;
				const Numeric& v_44 = value.s_quantity;
				const Varchar<24>& v_45 = value.s_dist_01;
				const Varchar<24>& v_46 = value.s_dist_02;
				const Varchar<24>& v_47 = value.s_dist_03;
				const Varchar<24>& v_48 = value.s_dist_04;
				const Varchar<24>& v_49 = value.s_dist_05;
				const Varchar<24>& v_50 = value.s_dist_06;
				const Varchar<24>& v_51 = value.s_dist_07;
				const Varchar<24>& v_52 = value.s_dist_08;
				const Varchar<24>& v_53 = value.s_dist_09;
				const Varchar<24>& v_54 = value.s_dist_10;
				const Numeric& v_55 = value.s_ytd;
				const Numeric& v_56 = value.s_order_cnt;
				const Numeric& v_57 = value.s_remote_cnt;
				const Varchar<50>& v_58 = value.s_data;
				if (v_44 < 11) {
					for (auto range = v_31.equal_range({v_43, v_42}); range.first!=range.second; range.first++) {
						const Integer& v_36 = std::get<0>(range.first->first);
						const Integer& v_32 = std::get<1>(range.first->first);
						const Integer& v_33 = std::get<0>(range.first->second);
						const Integer& v_34 = std::get<1>(range.first->second);
						const Integer& v_35 = std::get<2>(range.first->second);
						const Integer& v_37 = std::get<3>(range.first->second);
						const Timestamp& v_38 = std::get<4>(range.first->second);
						const Numeric& v_39 = std::get<5>(range.first->second);
						const Numeric& v_40 = std::get<6>(range.first->second);
						const Varchar<24>& v_41 = std::get<7>(range.first->second);
						v_30 += 1;
					}
				}
			});
			return v_30;
		}()) << std::endl;
	}},
}},
	{"all", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		std::cout << ([&]() {
			Integer v_1 = 0;
			std::unordered_multimap<std::tuple<Integer, Integer>, std::tuple<Integer, Integer, Integer, Integer, Timestamp, Numeric, Numeric, Varchar<24>>> v_2;
			db->orderline.forEach([&](auto& key, auto& value) {
				const Integer& v_3 = key.ol_w_id;
				const Integer& v_4 = key.ol_d_id;
				const Integer& v_5 = key.ol_o_id;
				const Integer& v_6 = key.ol_number;
				const Integer& v_7 = value.ol_i_id;
				const Integer& v_8 = value.ol_supply_w_id;
				const Timestamp& v_9 = value.ol_delivery_d;
				const Numeric& v_10 = value.ol_quantity;
				const Numeric& v_11 = value.ol_amount;
				const Varchar<24>& v_12 = value.ol_dist_info;
				if ((((v_3 == 0) && (v_4 == 5)) && (v_5 == 0)) && (v_5 > (0 - 20))) {
					v_2.insert({{v_7, v_3}, {v_4, v_5, v_6, v_8, v_9, v_10, v_11, v_12}});
				}
			});
			db->stock.forEach([&](auto& key, auto& value) {
				const Integer& v_13 = key.s_w_id;
				const Integer& v_14 = key.s_i_id;
				const Numeric& v_15 = value.s_quantity;
				const Varchar<24>& v_16 = value.s_dist_01;
				const Varchar<24>& v_17 = value.s_dist_02;
				const Varchar<24>& v_18 = value.s_dist_03;
				const Varchar<24>& v_19 = value.s_dist_04;
				const Varchar<24>& v_20 = value.s_dist_05;
				const Varchar<24>& v_21 = value.s_dist_06;
				const Varchar<24>& v_22 = value.s_dist_07;
				const Varchar<24>& v_23 = value.s_dist_08;
				const Varchar<24>& v_24 = value.s_dist_09;
				const Varchar<24>& v_25 = value.s_dist_10;
				const Numeric& v_26 = value.s_ytd;
				const Numeric& v_27 = value.s_order_cnt;
				const Numeric& v_28 = value.s_remote_cnt;
				const Varchar<50>& v_29 = value.s_data;
				if (v_15 < 10) {
					for (auto range = v_2.equal_range({v_14, v_13}); range.first!=range.second; range.first++) {
						const Integer& v_7 = std::get<0>(range.first->first);
						const Integer& v_3 = std::get<1>(range.first->first);
						const Integer& v_4 = std::get<0>(range.first->second);
						const Integer& v_5 = std::get<1>(range.first->second);
						const Integer& v_6 = std::get<2>(range.first->second);
						const Integer& v_8 = std::get<3>(range.first->second);
						const Timestamp& v_9 = std::get<4>(range.first->second);
						const Numeric& v_10 = std::get<5>(range.first->second);
						const Numeric& v_11 = std::get<6>(range.first->second);
						const Varchar<24>& v_12 = std::get<7>(range.first->second);
						v_1 += 1;
					}
				}
			});
			return v_1;
		}()) + ([&]() {
			Integer v_30 = 0;
			std::unordered_multimap<std::tuple<Integer, Integer>, std::tuple<Integer, Integer, Integer, Integer, Timestamp, Numeric, Numeric, Varchar<24>>> v_31;
			db->orderline.forEach([&](auto& key, auto& value) {
				const Integer& v_32 = key.ol_w_id;
				const Integer& v_33 = key.ol_d_id;
				const Integer& v_34 = key.ol_o_id;
				const Integer& v_35 = key.ol_number;
				const Integer& v_36 = value.ol_i_id;
				const Integer& v_37 = value.ol_supply_w_id;
				const Timestamp& v_38 = value.ol_delivery_d;
				const Numeric& v_39 = value.ol_quantity;
				const Numeric& v_40 = value.ol_amount;
				const Varchar<24>& v_41 = value.ol_dist_info;
				if ((((v_32 == 1) && (v_33 == 6)) && (v_34 == 1)) && (v_34 > (1 - 20))) {
					v_31.insert({{v_36, v_32}, {v_33, v_34, v_35, v_37, v_38, v_39, v_40, v_41}});
				}
			});
			db->stock.forEach([&](auto& key, auto& value) {
				const Integer& v_42 = key.s_w_id;
				const Integer& v_43 = key.s_i_id;
				const Numeric& v_44 = value.s_quantity;
				const Varchar<24>& v_45 = value.s_dist_01;
				const Varchar<24>& v_46 = value.s_dist_02;
				const Varchar<24>& v_47 = value.s_dist_03;
				const Varchar<24>& v_48 = value.s_dist_04;
				const Varchar<24>& v_49 = value.s_dist_05;
				const Varchar<24>& v_50 = value.s_dist_06;
				const Varchar<24>& v_51 = value.s_dist_07;
				const Varchar<24>& v_52 = value.s_dist_08;
				const Varchar<24>& v_53 = value.s_dist_09;
				const Varchar<24>& v_54 = value.s_dist_10;
				const Numeric& v_55 = value.s_ytd;
				const Numeric& v_56 = value.s_order_cnt;
				const Numeric& v_57 = value.s_remote_cnt;
				const Varchar<50>& v_58 = value.s_data;
				if (v_44 < 11) {
					for (auto range = v_31.equal_range({v_43, v_42}); range.first!=range.second; range.first++) {
						const Integer& v_36 = std::get<0>(range.first->first);
						const Integer& v_32 = std::get<1>(range.first->first);
						const Integer& v_33 = std::get<0>(range.first->second);
						const Integer& v_34 = std::get<1>(range.first->second);
						const Integer& v_35 = std::get<2>(range.first->second);
						const Integer& v_37 = std::get<3>(range.first->second);
						const Timestamp& v_38 = std::get<4>(range.first->second);
						const Numeric& v_39 = std::get<5>(range.first->second);
						const Numeric& v_40 = std::get<6>(range.first->second);
						const Varchar<24>& v_41 = std::get<7>(range.first->second);
						v_30 += 1;
					}
				}
			});
			return v_30;
		}()) << std::endl;
	}},
}},
};
