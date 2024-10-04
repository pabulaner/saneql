std::map<std::string, std::map<std::string, std::function<void(Database*, size_t)>>> queries = {
	{"none", {
	{"./query/benchmark/handwritten.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "s_w_id" << ", " << "s_i_id" << ", " << "s_quantity" << ", " << "s_dist_01" << ", " << "s_dist_02" << ", " << "s_dist_03" << ", " << "s_dist_04" << ", " << "s_dist_05" << ", " << "s_dist_06" << ", " << "s_dist_07" << ", " << "s_dist_08" << ", " << "s_dist_09" << ", " << "s_dist_10" << ", " << "s_ytd" << ", " << "s_order_cnt" << ", " << "s_remote_cnt" << ", " << "s_data" << ", " << "ol_w_id" << ", " << "ol_d_id" << ", " << "ol_o_id" << ", " << "ol_number" << ", " << "ol_i_id" << ", " << "ol_supply_w_id" << ", " << "ol_delivery_d" << ", " << "ol_quantity" << ", " << "ol_amount" << ", " << "ol_dist_info" << std::endl;
		}
		{
			std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Numeric, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Numeric, Numeric, Numeric, Varchar<50>>> v_1(1024 * 1024);
			db->stock.forEach([&](auto& key, auto& value) {
				const Integer& v_2 = key.s_w_id;
				const Integer& v_3 = key.s_i_id;
				const Numeric& v_4 = value.s_quantity;
				const Varchar<24>& v_5 = value.s_dist_01;
				const Varchar<24>& v_6 = value.s_dist_02;
				const Varchar<24>& v_7 = value.s_dist_03;
				const Varchar<24>& v_8 = value.s_dist_04;
				const Varchar<24>& v_9 = value.s_dist_05;
				const Varchar<24>& v_10 = value.s_dist_06;
				const Varchar<24>& v_11 = value.s_dist_07;
				const Varchar<24>& v_12 = value.s_dist_08;
				const Varchar<24>& v_13 = value.s_dist_09;
				const Varchar<24>& v_14 = value.s_dist_10;
				const Numeric& v_15 = value.s_ytd;
				const Numeric& v_16 = value.s_order_cnt;
				const Numeric& v_17 = value.s_remote_cnt;
				const Varchar<50>& v_18 = value.s_data;
				if ((v_2 == 2) && (v_4 < 20)) {
					v_1.insert({{v_3}, {v_2, v_4, v_5, v_6, v_7, v_8, v_9, v_10, v_11, v_12, v_13, v_14, v_15, v_16, v_17, v_18}});
				}
			});
			db->orderline.forEach([&](auto& key, auto& value) {
				const Integer& v_19 = key.ol_w_id;
				const Integer& v_20 = key.ol_d_id;
				const Integer& v_21 = key.ol_o_id;
				const Integer& v_22 = key.ol_number;
				const Integer& v_23 = value.ol_i_id;
				const Integer& v_24 = value.ol_supply_w_id;
				const Timestamp& v_25 = value.ol_delivery_d;
				const Numeric& v_26 = value.ol_quantity;
				const Numeric& v_27 = value.ol_amount;
				const Varchar<24>& v_28 = value.ol_dist_info;
				if ((((v_19 == 1) && (v_20 == 2)) && (v_21 < 3)) && (v_21 >= (3 - 20))) {
					for (auto range = v_1.equal_range({v_23}); range.first!=range.second; range.first++) {
						const Integer& v_3 = std::get<0>(range.first->first);
						const Integer& v_2 = std::get<0>(range.first->second);
						const Numeric& v_4 = std::get<1>(range.first->second);
						const Varchar<24>& v_5 = std::get<2>(range.first->second);
						const Varchar<24>& v_6 = std::get<3>(range.first->second);
						const Varchar<24>& v_7 = std::get<4>(range.first->second);
						const Varchar<24>& v_8 = std::get<5>(range.first->second);
						const Varchar<24>& v_9 = std::get<6>(range.first->second);
						const Varchar<24>& v_10 = std::get<7>(range.first->second);
						const Varchar<24>& v_11 = std::get<8>(range.first->second);
						const Varchar<24>& v_12 = std::get<9>(range.first->second);
						const Varchar<24>& v_13 = std::get<10>(range.first->second);
						const Varchar<24>& v_14 = std::get<11>(range.first->second);
						const Numeric& v_15 = std::get<12>(range.first->second);
						const Numeric& v_16 = std::get<13>(range.first->second);
						const Numeric& v_17 = std::get<14>(range.first->second);
						const Varchar<50>& v_18 = std::get<15>(range.first->second);
						if (limit > 0) {
							limit -= 1;
							std::cout << v_2 << ", " << v_3 << ", " << v_4 << ", " << v_5 << ", " << v_6 << ", " << v_7 << ", " << v_8 << ", " << v_9 << ", " << v_10 << ", " << v_11 << ", " << v_12 << ", " << v_13 << ", " << v_14 << ", " << v_15 << ", " << v_16 << ", " << v_17 << ", " << v_18 << ", " << v_19 << ", " << v_20 << ", " << v_21 << ", " << v_22 << ", " << v_23 << ", " << v_24 << ", " << v_25 << ", " << v_26 << ", " << v_27 << ", " << v_28 << std::endl;
						}
					}
				}
			});
		}
	}},
	{"./query/benchmark/index_scan_query.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "s_suppkey" << ", " << "s_name" << ", " << "s_address" << ", " << "s_nationkey" << ", " << "s_phone" << ", " << "s_acctbal" << ", " << "s_comment" << ", " << "c_custkey" << ", " << "c_name" << ", " << "c_address" << ", " << "c_nationkey" << ", " << "c_phone" << ", " << "c_acctbal" << ", " << "c_mktsegment" << ", " << "c_comment" << std::endl;
		}
		{
			std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Varchar<15>, Numeric, Varchar<101>>> v_1(1024 * 1024);
			db->supplier_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_29 = key.s_suppkey;
				const Varchar<25>& v_30 = value.s_name;
				const Varchar<40>& v_31 = value.s_address;
				const Integer& v_32 = value.s_nationkey;
				const Varchar<15>& v_33 = value.s_phone;
				const Numeric& v_34 = value.s_acctbal;
				const Varchar<101>& v_35 = value.s_comment;
				v_1.insert({{v_32}, {v_29, v_30, v_31, v_33, v_34, v_35}});
			});
			db->customer_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_15 = key.c_custkey;
				const Varchar<25>& v_3 = value.c_name;
				const Varchar<40>& v_4 = value.c_address;
				const Integer& v_5 = value.c_nationkey;
				const Varchar<15>& v_6 = value.c_phone;
				const Numeric& v_11 = value.c_acctbal;
				const Varchar<10>& v_12 = value.c_mktsegment;
				const Varchar<117>& v_2 = value.c_comment;
				if (v_15 == 1) {
					for (auto range = v_1.equal_range({v_5}); range.first!=range.second; range.first++) {
						const Integer& v_32 = std::get<0>(range.first->first);
						const Integer& v_29 = std::get<0>(range.first->second);
						const Varchar<25>& v_30 = std::get<1>(range.first->second);
						const Varchar<40>& v_31 = std::get<2>(range.first->second);
						const Varchar<15>& v_33 = std::get<3>(range.first->second);
						const Numeric& v_34 = std::get<4>(range.first->second);
						const Varchar<101>& v_35 = std::get<5>(range.first->second);
						if (limit > 0) {
							limit -= 1;
							std::cout << v_29 << ", " << v_30 << ", " << v_31 << ", " << v_32 << ", " << v_33 << ", " << v_34 << ", " << v_35 << ", " << v_15 << ", " << v_3 << ", " << v_4 << ", " << v_5 << ", " << v_6 << ", " << v_11 << ", " << v_12 << ", " << v_2 << std::endl;
						}
					}
				}
			});
		}
	}},
	{"./query/benchmark/tpch_1.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "l_returnflag" << ", " << "l_linestatus" << ", " << "sum_qty" << ", " << "sum_base_price" << ", " << "sum_disc_price" << ", " << "sum_charge" << ", " << "avg_qty" << ", " << "avg_price" << ", " << "avg_disc" << ", " << "count_order" << std::endl;
		}
		{
			std::vector<std::tuple<Varchar<1>, Varchar<1>, Varchar<1>, Varchar<1>, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Integer>> v_36;
			v_36.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Varchar<1>, Varchar<1>>, std::tuple<Numeric, Numeric, Numeric, Numeric, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, Integer>> v_37(1024 * 1024);
				db->lineitem_tpch.forEach([&](auto& key, auto& value) {
					const Numeric& v_23 = value.l_quantity;
					const Numeric& v_14 = value.l_extendedprice;
					const Numeric& v_24 = value.l_discount;
					const Numeric& v_22 = value.l_tax;
					const Varchar<1>& v_38 = value.l_returnflag;
					const Varchar<1>& v_15 = value.l_linestatus;
					const Timestamp& v_4 = value.l_shipdate;
					if (v_4 <= (2451058)) {
						auto it = v_37.find({v_38, v_15});
						if (it == v_37.end()) {
							v_37.insert({{v_38, v_15}, {v_23, v_14, v_14 * (1 - v_24), (v_14 * (1 - v_24)) * (1 + v_22), {v_23, 1}, {v_14, 1}, {v_24, 1}, 1}});
						} else {
							std::get<0>(it->second) += v_23;
							std::get<1>(it->second) += v_14;
							std::get<2>(it->second) += v_14 * (1 - v_24);
							std::get<3>(it->second) += (v_14 * (1 - v_24)) * (1 + v_22);
							std::get<4>(it->second) = {std::get<4>(it->second).first + v_23, std::get<4>(it->second).second + 1};
							std::get<5>(it->second) = {std::get<5>(it->second).first + v_14, std::get<5>(it->second).second + 1};
							std::get<6>(it->second) = {std::get<6>(it->second).first + v_24, std::get<6>(it->second).second + 1};
							std::get<7>(it->second) += 1;
						}
					}
				});
				for (auto& it : v_37) {
					const Varchar<1>& v_39 = std::get<0>(it.first);
					const Varchar<1>& v_40 = std::get<1>(it.first);
					const Numeric& v_41 = std::get<0>(it.second);
					const Numeric& v_42 = std::get<1>(it.second);
					const Numeric& v_43 = std::get<2>(it.second);
					const Numeric& v_44 = std::get<3>(it.second);
					const Numeric v_45 = std::get<4>(it.second).first / (double)std::get<4>(it.second).second;
					const Numeric v_46 = std::get<5>(it.second).first / (double)std::get<5>(it.second).second;
					const Numeric v_47 = std::get<6>(it.second).first / (double)std::get<6>(it.second).second;
					const Integer& v_48 = std::get<7>(it.second);
					v_36.push_back({v_39, v_40, v_39, v_40, v_41, v_42, v_43, v_44, v_45, v_46, v_47, v_48});
				}
			}
			std::sort(v_36.begin(), v_36.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				if (get<1>(t1) < get<1>(t2)) return true;
				if (get<1>(t2) < get<1>(t1)) return false;
				return false;
			});
			for (auto& t : v_36) {
				const Varchar<1>& v_39 = std::get<2>(t);
				const Varchar<1>& v_40 = std::get<3>(t);
				const Numeric& v_41 = std::get<4>(t);
				const Numeric& v_42 = std::get<5>(t);
				const Numeric& v_43 = std::get<6>(t);
				const Numeric& v_44 = std::get<7>(t);
				const Numeric& v_45 = std::get<8>(t);
				const Numeric& v_46 = std::get<9>(t);
				const Numeric& v_47 = std::get<10>(t);
				const Integer& v_48 = std::get<11>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_39 << ", " << v_40 << ", " << v_41 << ", " << v_42 << ", " << v_43 << ", " << v_44 << ", " << v_45 << ", " << v_46 << ", " << v_47 << ", " << v_48 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_10.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "c_custkey" << ", " << "c_name" << ", " << "c_acctbal" << ", " << "c_phone" << ", " << "n_name" << ", " << "c_address" << ", " << "c_comment" << ", " << "revenue" << std::endl;
		}
		{
			std::vector<std::tuple<Numeric, Integer, Varchar<25>, Numeric, Varchar<15>, Varchar<25>, Varchar<40>, Varchar<117>, Numeric>> v_36;
			v_36.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Integer, Varchar<25>, Numeric, Varchar<15>, Varchar<25>, Varchar<40>, Varchar<117>>, std::tuple<Numeric>> v_37(1024 * 1024);
				{
					std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Varchar<15>, Numeric, Varchar<117>, Numeric, Numeric>> v_49(1024 * 1024);
					{
						std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<117>>> v_50(1024 * 1024);
						{
							std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer>> v_51(1024 * 1024);
							db->orders_tpch.forEach([&](auto& key, auto& value) {
								const Integer& v_52 = key.o_orderkey;
								const Integer& v_53 = key.o_custkey;
								const Timestamp& v_54 = value.o_orderdate;
								if ((v_54 >= (2449262)) && (v_54 < (2449354))) {
									v_51.insert({{v_53}, {v_52}});
								}
							});
							db->customer_tpch.forEach([&](auto& key, auto& value) {
								const Integer& v_45 = key.c_custkey;
								const Varchar<25>& v_38 = value.c_name;
								const Varchar<40>& v_55 = value.c_address;
								const Integer& v_48 = value.c_nationkey;
								const Varchar<15>& v_21 = value.c_phone;
								const Numeric& v_27 = value.c_acctbal;
								const Varchar<117>& v_23 = value.c_comment;
								for (auto range = v_51.equal_range({v_45}); range.first!=range.second; range.first++) {
									const Integer& v_52 = std::get<0>(range.first->second);
									v_50.insert({{v_52}, {v_45, v_38, v_55, v_48, v_21, v_27, v_23}});
								}
							});
						}
						db->lineitem_tpch.forEach([&](auto& key, auto& value) {
							const Integer& v_28 = key.l_orderkey;
							const Numeric& v_56 = value.l_extendedprice;
							const Numeric& v_57 = value.l_discount;
							const Varchar<1>& v_58 = value.l_returnflag;
							if (v_58 == Varchar<1>("R")) {
								for (auto range = v_50.equal_range({v_28}); range.first!=range.second; range.first++) {
									const Integer& v_45 = std::get<0>(range.first->second);
									const Varchar<25>& v_38 = std::get<1>(range.first->second);
									const Varchar<40>& v_55 = std::get<2>(range.first->second);
									const Integer& v_48 = std::get<3>(range.first->second);
									const Varchar<15>& v_21 = std::get<4>(range.first->second);
									const Numeric& v_27 = std::get<5>(range.first->second);
									const Varchar<117>& v_23 = std::get<6>(range.first->second);
									v_49.insert({{v_48}, {v_45, v_38, v_55, v_21, v_27, v_23, v_56, v_57}});
								}
							}
						});
					}
					db->nation_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_59 = key.n_nationkey;
						const Varchar<25>& v_60 = value.n_name;
						for (auto range = v_49.equal_range({v_59}); range.first!=range.second; range.first++) {
							const Integer& v_45 = std::get<0>(range.first->second);
							const Varchar<25>& v_38 = std::get<1>(range.first->second);
							const Varchar<40>& v_55 = std::get<2>(range.first->second);
							const Varchar<15>& v_21 = std::get<3>(range.first->second);
							const Numeric& v_27 = std::get<4>(range.first->second);
							const Varchar<117>& v_23 = std::get<5>(range.first->second);
							const Numeric& v_56 = std::get<6>(range.first->second);
							const Numeric& v_57 = std::get<7>(range.first->second);
							auto it = v_37.find({v_45, v_38, v_27, v_21, v_60, v_55, v_23});
							if (it == v_37.end()) {
								v_37.insert({{v_45, v_38, v_27, v_21, v_60, v_55, v_23}, {v_56 * (1 - v_57)}});
							} else {
								std::get<0>(it->second) += v_56 * (1 - v_57);
							}
						}
					});
				}
				for (auto& it : v_37) {
					const Integer& v_61 = std::get<0>(it.first);
					const Varchar<25>& v_62 = std::get<1>(it.first);
					const Numeric& v_63 = std::get<2>(it.first);
					const Varchar<15>& v_64 = std::get<3>(it.first);
					const Varchar<25>& v_65 = std::get<4>(it.first);
					const Varchar<40>& v_66 = std::get<5>(it.first);
					const Varchar<117>& v_67 = std::get<6>(it.first);
					const Numeric& v_68 = std::get<0>(it.second);
					v_36.push_back({v_68, v_61, v_62, v_63, v_64, v_65, v_66, v_67, v_68});
				}
			}
			std::sort(v_36.begin(), v_36.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				return false;
			});
			for (auto& t : v_36) {
				const Integer& v_61 = std::get<1>(t);
				const Varchar<25>& v_62 = std::get<2>(t);
				const Numeric& v_63 = std::get<3>(t);
				const Varchar<15>& v_64 = std::get<4>(t);
				const Varchar<25>& v_65 = std::get<5>(t);
				const Varchar<40>& v_66 = std::get<6>(t);
				const Varchar<117>& v_67 = std::get<7>(t);
				const Numeric& v_68 = std::get<8>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_61 << ", " << v_62 << ", " << v_63 << ", " << v_64 << ", " << v_65 << ", " << v_66 << ", " << v_67 << ", " << v_68 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_14_changed.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "p_type" << ", " << "2" << std::endl;
		}
		{
			std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Numeric, Numeric>> v_69(1024 * 1024);
			{
				std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric, Timestamp>> v_70(1024 * 1024);
				db->lineitem_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_71 = key.l_partkey;
					const Numeric& v_72 = value.l_extendedprice;
					const Numeric& v_73 = value.l_discount;
					const Timestamp& v_52 = value.l_shipdate;
					v_70.insert({{v_71}, {v_72, v_73, v_52}});
				});
				db->part_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_14 = key.p_partkey;
					const Varchar<25>& v_27 = value.p_type;
					for (auto range = v_70.equal_range({v_14}); range.first!=range.second; range.first++) {
						const Numeric& v_72 = std::get<0>(range.first->second);
						const Numeric& v_73 = std::get<1>(range.first->second);
						const Timestamp& v_52 = std::get<2>(range.first->second);
						if ((v_52 >= (2449962)) && (v_52 < (2449992))) {
							auto it = v_69.find({v_27});
							if (it == v_69.end()) {
								v_69.insert({{v_27}, {v_72 * (1 - v_73), v_72 * (1 - v_73)}});
							} else {
								std::get<0>(it->second) += v_72 * (1 - v_73);
								std::get<1>(it->second) += v_72 * (1 - v_73);
							}
						}
					}
				});
			}
			for (auto& it : v_69) {
				const Varchar<25>& v_74 = std::get<0>(it.first);
				const Numeric& v_75 = std::get<0>(it.second);
				const Numeric& v_76 = std::get<1>(it.second);
				Numeric v_77 = (100.00 * v_75) / v_76;
				if (limit > 0) {
					limit -= 1;
					std::cout << v_74 << ", " << v_77 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_3.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << [&]() {
				Integer v_78 = 0;
				{
					std::vector<std::tuple<Numeric, Timestamp>> v_79;
					v_79.reserve(1024 * 1024);
					{
						std::unordered_map<std::tuple<Integer, Timestamp, Integer>, std::tuple<Numeric>> v_80(1024 * 1024);
						{
							std::unordered_multimap<std::tuple<Integer>, std::tuple<Timestamp, Integer>> v_81(1024 * 1024);
							{
								std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_82(1024 * 1024);
								db->customer_tpch.forEach([&](auto& key, auto& value) {
									const Integer& v_83 = key.c_custkey;
									const Varchar<10>& v_84 = value.c_mktsegment;
									if (v_84 == Varchar<8>("BUILDING")) {
										v_82.insert({{v_83}, {}});
									}
								});
								db->orders_tpch.forEach([&](auto& key, auto& value) {
									const Integer& v_4 = key.o_orderkey;
									const Integer& v_23 = key.o_custkey;
									const Timestamp& v_11 = value.o_orderdate;
									const Integer& v_85 = value.o_shippriority;
									if (v_11 < (2449792)) {
										for (auto range = v_82.equal_range({v_23}); range.first!=range.second; range.first++) {
											v_81.insert({{v_4}, {v_11, v_85}});
										}
									}
								});
							}
							db->lineitem_tpch.forEach([&](auto& key, auto& value) {
								const Integer& v_86 = key.l_orderkey;
								const Numeric& v_34 = value.l_extendedprice;
								const Numeric& v_87 = value.l_discount;
								const Timestamp& v_88 = value.l_shipdate;
								if (v_88 > (2449792)) {
									for (auto range = v_81.equal_range({v_86}); range.first!=range.second; range.first++) {
										const Timestamp& v_11 = std::get<0>(range.first->second);
										const Integer& v_85 = std::get<1>(range.first->second);
										auto it = v_80.find({v_86, v_11, v_85});
										if (it == v_80.end()) {
											v_80.insert({{v_86, v_11, v_85}, {v_34 * (1 - v_87)}});
										} else {
											std::get<0>(it->second) += v_34 * (1 - v_87);
										}
									}
								}
							});
						}
						for (auto& it : v_80) {
							const Timestamp& v_89 = std::get<1>(it.first);
							const Numeric& v_90 = std::get<0>(it.second);
							v_79.push_back({v_90, v_89});
						}
					}
					std::sort(v_79.begin(), v_79.end(), [](const auto& t1, const auto& t2) {
						if (get<0>(t1) < get<0>(t2)) return true;
						if (get<0>(t2) < get<0>(t1)) return false;
						if (get<1>(t1) < get<1>(t2)) return true;
						if (get<1>(t2) < get<1>(t1)) return false;
						return false;
					});
					for (auto& t : v_79) {
						v_78 += 1;
					}
				}
				return v_78;
			}() << std::endl;
		}
	}},
	{"./query/benchmark/tpch_4_changed.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "o_orderpriority" << ", " << "order_count" << std::endl;
		}
		{
			std::vector<std::tuple<Varchar<15>, Varchar<15>, Integer>> v_36;
			v_36.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Varchar<15>>, std::tuple<Integer>> v_37(1024 * 1024);
				{
					std::unordered_multimap<std::tuple<Integer>, std::tuple<Varchar<15>>> v_49(1024 * 1024);
					db->orders_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_91 = key.o_orderkey;
						const Timestamp& v_76 = value.o_orderdate;
						const Varchar<15>& v_92 = value.o_orderpriority;
						if ((v_76 >= (2449170)) && (v_76 < (2449262))) {
							v_49.insert({{v_91}, {v_92}});
						}
					});
					db->lineitem_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_86 = key.l_orderkey;
						const Timestamp& v_93 = value.l_commitdate;
						const Timestamp& v_94 = value.l_receiptdate;
						if (v_93 < v_94) {
							for (auto range = v_49.equal_range({v_86}); range.first!=range.second; range.first++) {
								const Varchar<15>& v_92 = std::get<0>(range.first->second);
								auto it = v_37.find({v_92});
								if (it == v_37.end()) {
									v_37.insert({{v_92}, {1}});
								} else {
									std::get<0>(it->second) += 1;
								}
							}
						}
					});
				}
				for (auto& it : v_37) {
					const Varchar<15>& v_95 = std::get<0>(it.first);
					const Integer& v_96 = std::get<0>(it.second);
					v_36.push_back({v_95, v_95, v_96});
				}
			}
			std::sort(v_36.begin(), v_36.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				return false;
			});
			for (auto& t : v_36) {
				const Varchar<15>& v_95 = std::get<1>(t);
				const Integer& v_96 = std::get<2>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_95 << ", " << v_96 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_5.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "n_name" << ", " << "revenue" << std::endl;
		}
		{
			std::vector<std::tuple<Numeric, Varchar<25>, Numeric>> v_36;
			v_36.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Numeric>> v_37(1024 * 1024);
				{
					std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric, Varchar<25>>> v_49(1024 * 1024);
					{
						std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric>> v_50(1024 * 1024);
						{
							std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric>> v_51(1024 * 1024);
							{
								std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_97(1024 * 1024);
								{
									std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_98(1024 * 1024);
									db->customer_tpch.forEach([&](auto& key, auto& value) {
										const Integer& v_99 = key.c_custkey;
										v_98.insert({{v_99}, {}});
									});
									db->orders_tpch.forEach([&](auto& key, auto& value) {
										const Integer& v_11 = key.o_orderkey;
										const Integer& v_15 = key.o_custkey;
										const Timestamp& v_27 = value.o_orderdate;
										if ((v_27 >= (2449354)) && (v_27 < (2449719))) {
											for (auto range = v_98.equal_range({v_15}); range.first!=range.second; range.first++) {
												v_97.insert({{v_11}, {}});
											}
										}
									});
								}
								db->lineitem_tpch.forEach([&](auto& key, auto& value) {
									const Integer& v_58 = key.l_orderkey;
									const Integer& v_100 = key.l_suppkey;
									const Numeric& v_101 = value.l_extendedprice;
									const Numeric& v_102 = value.l_discount;
									for (auto range = v_97.equal_range({v_58}); range.first!=range.second; range.first++) {
										v_51.insert({{v_100}, {v_101, v_102}});
									}
								});
							}
							db->supplier_tpch.forEach([&](auto& key, auto& value) {
								const Integer& v_103 = key.s_suppkey;
								const Integer& v_104 = value.s_nationkey;
								for (auto range = v_51.equal_range({v_103}); range.first!=range.second; range.first++) {
									const Numeric& v_101 = std::get<0>(range.first->second);
									const Numeric& v_102 = std::get<1>(range.first->second);
									v_50.insert({{v_104}, {v_101, v_102}});
								}
							});
						}
						db->nation_tpch.forEach([&](auto& key, auto& value) {
							const Integer& v_105 = key.n_nationkey;
							const Varchar<25>& v_106 = value.n_name;
							const Integer& v_107 = value.n_regionkey;
							for (auto range = v_50.equal_range({v_105}); range.first!=range.second; range.first++) {
								const Numeric& v_101 = std::get<0>(range.first->second);
								const Numeric& v_102 = std::get<1>(range.first->second);
								v_49.insert({{v_107}, {v_101, v_102, v_106}});
							}
						});
					}
					db->region_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_108 = key.r_regionkey;
						const Varchar<25>& v_109 = value.r_name;
						if (v_109 == Varchar<4>("ASIA")) {
							for (auto range = v_49.equal_range({v_108}); range.first!=range.second; range.first++) {
								const Numeric& v_101 = std::get<0>(range.first->second);
								const Numeric& v_102 = std::get<1>(range.first->second);
								const Varchar<25>& v_106 = std::get<2>(range.first->second);
								auto it = v_37.find({v_106});
								if (it == v_37.end()) {
									v_37.insert({{v_106}, {v_101 * (1 - v_102)}});
								} else {
									std::get<0>(it->second) += v_101 * (1 - v_102);
								}
							}
						}
					});
				}
				for (auto& it : v_37) {
					const Varchar<25>& v_110 = std::get<0>(it.first);
					const Numeric& v_111 = std::get<0>(it.second);
					v_36.push_back({v_111, v_110, v_111});
				}
			}
			std::sort(v_36.begin(), v_36.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				return false;
			});
			for (auto& t : v_36) {
				const Varchar<25>& v_110 = std::get<1>(t);
				const Numeric& v_111 = std::get<2>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_110 << ", " << v_111 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_5_opt.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "n_name" << ", " << "revenue" << std::endl;
		}
		{
			std::vector<std::tuple<Numeric, Varchar<25>, Numeric>> v_36;
			v_36.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Numeric>> v_37(1024 * 1024);
				{
					std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_49(1024 * 1024);
					db->region_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_112 = key.r_regionkey;
						const Varchar<25>& v_113 = value.r_name;
						if (v_113 == Varchar<4>("ASIA")) {
							v_49.insert({{v_112}, {}});
						}
					});
					{
						std::unordered_multimap<std::tuple<Integer>, std::tuple<Varchar<25>, Integer>> v_50(1024 * 1024);
						db->nation_tpch.forEach([&](auto& key, auto& value) {
							const Integer& v_114 = key.n_nationkey;
							const Varchar<25>& v_115 = value.n_name;
							const Integer& v_5 = value.n_regionkey;
							v_50.insert({{v_114}, {v_115, v_5}});
						});
						{
							std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer>> v_51(1024 * 1024);
							db->supplier_tpch.forEach([&](auto& key, auto& value) {
								const Integer& v_27 = key.s_suppkey;
								const Integer& v_24 = value.s_nationkey;
								v_51.insert({{v_27}, {v_24}});
							});
							{
								std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_97(1024 * 1024);
								{
									std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_98(1024 * 1024);
									db->customer_tpch.forEach([&](auto& key, auto& value) {
										const Integer& v_116 = key.c_custkey;
										v_98.insert({{v_116}, {}});
									});
									db->orders_tpch.forEach([&](auto& key, auto& value) {
										const Integer& v_117 = key.o_orderkey;
										const Integer& v_118 = key.o_custkey;
										const Timestamp& v_119 = value.o_orderdate;
										if ((v_119 >= (2449354)) && (v_119 < (2449719))) {
											for (auto range = v_98.equal_range({v_118}); range.first!=range.second; range.first++) {
												v_97.insert({{v_117}, {}});
											}
										}
									});
								}
								db->lineitem_tpch.forEach([&](auto& key, auto& value) {
									const Integer& v_120 = key.l_orderkey;
									const Integer& v_121 = key.l_suppkey;
									const Numeric& v_122 = value.l_extendedprice;
									const Numeric& v_123 = value.l_discount;
									for (auto range = v_97.equal_range({v_120}); range.first!=range.second; range.first++) {
										for (auto range = v_51.equal_range({v_121}); range.first!=range.second; range.first++) {
											const Integer& v_24 = std::get<0>(range.first->second);
											for (auto range = v_50.equal_range({v_24}); range.first!=range.second; range.first++) {
												const Varchar<25>& v_115 = std::get<0>(range.first->second);
												const Integer& v_5 = std::get<1>(range.first->second);
												for (auto range = v_49.equal_range({v_5}); range.first!=range.second; range.first++) {
													auto it = v_37.find({v_115});
													if (it == v_37.end()) {
														v_37.insert({{v_115}, {v_122 * (1 - v_123)}});
													} else {
														std::get<0>(it->second) += v_122 * (1 - v_123);
													}
												}
											}
										}
									}
								});
							}
						}
					}
				}
				for (auto& it : v_37) {
					const Varchar<25>& v_124 = std::get<0>(it.first);
					const Numeric& v_125 = std::get<0>(it.second);
					v_36.push_back({v_125, v_124, v_125});
				}
			}
			std::sort(v_36.begin(), v_36.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				return false;
			});
			for (auto& t : v_36) {
				const Varchar<25>& v_124 = std::get<1>(t);
				const Numeric& v_125 = std::get<2>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_124 << ", " << v_125 << std::endl;
				}
			}
		}
	}},
}},
	{"selects", {
	{"./query/benchmark/handwritten.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "s_w_id" << ", " << "s_i_id" << ", " << "s_quantity" << ", " << "s_dist_01" << ", " << "s_dist_02" << ", " << "s_dist_03" << ", " << "s_dist_04" << ", " << "s_dist_05" << ", " << "s_dist_06" << ", " << "s_dist_07" << ", " << "s_dist_08" << ", " << "s_dist_09" << ", " << "s_dist_10" << ", " << "s_ytd" << ", " << "s_order_cnt" << ", " << "s_remote_cnt" << ", " << "s_data" << ", " << "ol_w_id" << ", " << "ol_d_id" << ", " << "ol_o_id" << ", " << "ol_number" << ", " << "ol_i_id" << ", " << "ol_supply_w_id" << ", " << "ol_delivery_d" << ", " << "ol_quantity" << ", " << "ol_amount" << ", " << "ol_dist_info" << std::endl;
		}
		{
			std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Numeric, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Numeric, Numeric, Numeric, Varchar<50>>> v_1(1024 * 1024);
			db->stock.forEach([&](auto& key, auto& value) {
				const Integer& v_2 = key.s_w_id;
				const Integer& v_3 = key.s_i_id;
				const Numeric& v_4 = value.s_quantity;
				const Varchar<24>& v_5 = value.s_dist_01;
				const Varchar<24>& v_6 = value.s_dist_02;
				const Varchar<24>& v_7 = value.s_dist_03;
				const Varchar<24>& v_8 = value.s_dist_04;
				const Varchar<24>& v_9 = value.s_dist_05;
				const Varchar<24>& v_10 = value.s_dist_06;
				const Varchar<24>& v_11 = value.s_dist_07;
				const Varchar<24>& v_12 = value.s_dist_08;
				const Varchar<24>& v_13 = value.s_dist_09;
				const Varchar<24>& v_14 = value.s_dist_10;
				const Numeric& v_15 = value.s_ytd;
				const Numeric& v_16 = value.s_order_cnt;
				const Numeric& v_17 = value.s_remote_cnt;
				const Varchar<50>& v_18 = value.s_data;
				if ((v_2 == 2) && (v_4 < 20)) {
					v_1.insert({{v_3}, {v_2, v_4, v_5, v_6, v_7, v_8, v_9, v_10, v_11, v_12, v_13, v_14, v_15, v_16, v_17, v_18}});
				}
			});
			db->orderline.forEach([&](auto& key, auto& value) {
				const Integer& v_19 = key.ol_w_id;
				const Integer& v_20 = key.ol_d_id;
				const Integer& v_21 = key.ol_o_id;
				const Integer& v_22 = key.ol_number;
				const Integer& v_23 = value.ol_i_id;
				const Integer& v_24 = value.ol_supply_w_id;
				const Timestamp& v_25 = value.ol_delivery_d;
				const Numeric& v_26 = value.ol_quantity;
				const Numeric& v_27 = value.ol_amount;
				const Varchar<24>& v_28 = value.ol_dist_info;
				if ((((v_19 == 1) && (v_20 == 2)) && (v_21 < 3)) && (v_21 >= (3 - 20))) {
					for (auto range = v_1.equal_range({v_23}); range.first!=range.second; range.first++) {
						const Integer& v_3 = std::get<0>(range.first->first);
						const Integer& v_2 = std::get<0>(range.first->second);
						const Numeric& v_4 = std::get<1>(range.first->second);
						const Varchar<24>& v_5 = std::get<2>(range.first->second);
						const Varchar<24>& v_6 = std::get<3>(range.first->second);
						const Varchar<24>& v_7 = std::get<4>(range.first->second);
						const Varchar<24>& v_8 = std::get<5>(range.first->second);
						const Varchar<24>& v_9 = std::get<6>(range.first->second);
						const Varchar<24>& v_10 = std::get<7>(range.first->second);
						const Varchar<24>& v_11 = std::get<8>(range.first->second);
						const Varchar<24>& v_12 = std::get<9>(range.first->second);
						const Varchar<24>& v_13 = std::get<10>(range.first->second);
						const Varchar<24>& v_14 = std::get<11>(range.first->second);
						const Numeric& v_15 = std::get<12>(range.first->second);
						const Numeric& v_16 = std::get<13>(range.first->second);
						const Numeric& v_17 = std::get<14>(range.first->second);
						const Varchar<50>& v_18 = std::get<15>(range.first->second);
						if (limit > 0) {
							limit -= 1;
							std::cout << v_2 << ", " << v_3 << ", " << v_4 << ", " << v_5 << ", " << v_6 << ", " << v_7 << ", " << v_8 << ", " << v_9 << ", " << v_10 << ", " << v_11 << ", " << v_12 << ", " << v_13 << ", " << v_14 << ", " << v_15 << ", " << v_16 << ", " << v_17 << ", " << v_18 << ", " << v_19 << ", " << v_20 << ", " << v_21 << ", " << v_22 << ", " << v_23 << ", " << v_24 << ", " << v_25 << ", " << v_26 << ", " << v_27 << ", " << v_28 << std::endl;
						}
					}
				}
			});
		}
	}},
	{"./query/benchmark/index_scan_query.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "s_suppkey" << ", " << "s_name" << ", " << "s_address" << ", " << "s_nationkey" << ", " << "s_phone" << ", " << "s_acctbal" << ", " << "s_comment" << ", " << "c_custkey" << ", " << "c_name" << ", " << "c_address" << ", " << "c_nationkey" << ", " << "c_phone" << ", " << "c_acctbal" << ", " << "c_mktsegment" << ", " << "c_comment" << std::endl;
		}
		{
			std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Varchar<15>, Numeric, Varchar<101>>> v_1(1024 * 1024);
			db->supplier_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_29 = key.s_suppkey;
				const Varchar<25>& v_30 = value.s_name;
				const Varchar<40>& v_31 = value.s_address;
				const Integer& v_32 = value.s_nationkey;
				const Varchar<15>& v_33 = value.s_phone;
				const Numeric& v_34 = value.s_acctbal;
				const Varchar<101>& v_35 = value.s_comment;
				v_1.insert({{v_32}, {v_29, v_30, v_31, v_33, v_34, v_35}});
			});
			db->customer_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_9 = key.c_custkey;
				const Varchar<25>& v_23 = value.c_name;
				const Varchar<40>& v_24 = value.c_address;
				const Integer& v_25 = value.c_nationkey;
				const Varchar<15>& v_26 = value.c_phone;
				const Numeric& v_27 = value.c_acctbal;
				const Varchar<10>& v_28 = value.c_mktsegment;
				const Varchar<117>& v_19 = value.c_comment;
				if (v_9 == 1) {
					for (auto range = v_1.equal_range({v_25}); range.first!=range.second; range.first++) {
						const Integer& v_32 = std::get<0>(range.first->first);
						const Integer& v_29 = std::get<0>(range.first->second);
						const Varchar<25>& v_30 = std::get<1>(range.first->second);
						const Varchar<40>& v_31 = std::get<2>(range.first->second);
						const Varchar<15>& v_33 = std::get<3>(range.first->second);
						const Numeric& v_34 = std::get<4>(range.first->second);
						const Varchar<101>& v_35 = std::get<5>(range.first->second);
						if (limit > 0) {
							limit -= 1;
							std::cout << v_29 << ", " << v_30 << ", " << v_31 << ", " << v_32 << ", " << v_33 << ", " << v_34 << ", " << v_35 << ", " << v_9 << ", " << v_23 << ", " << v_24 << ", " << v_25 << ", " << v_26 << ", " << v_27 << ", " << v_28 << ", " << v_19 << std::endl;
						}
					}
				}
			});
		}
	}},
	{"./query/benchmark/tpch_1.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "l_returnflag" << ", " << "l_linestatus" << ", " << "sum_qty" << ", " << "sum_base_price" << ", " << "sum_disc_price" << ", " << "sum_charge" << ", " << "avg_qty" << ", " << "avg_price" << ", " << "avg_disc" << ", " << "count_order" << std::endl;
		}
		{
			std::vector<std::tuple<Varchar<1>, Varchar<1>, Varchar<1>, Varchar<1>, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Integer>> v_36;
			v_36.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Varchar<1>, Varchar<1>>, std::tuple<Numeric, Numeric, Numeric, Numeric, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, Integer>> v_37(1024 * 1024);
				db->lineitem_tpch.forEach([&](auto& key, auto& value) {
					const Numeric& v_38 = value.l_quantity;
					const Numeric& v_39 = value.l_extendedprice;
					const Numeric& v_40 = value.l_discount;
					const Numeric& v_31 = value.l_tax;
					const Varchar<1>& v_23 = value.l_returnflag;
					const Varchar<1>& v_24 = value.l_linestatus;
					const Timestamp& v_25 = value.l_shipdate;
					if (v_25 <= (2451058)) {
						auto it = v_37.find({v_23, v_24});
						if (it == v_37.end()) {
							v_37.insert({{v_23, v_24}, {v_38, v_39, v_39 * (1 - v_40), (v_39 * (1 - v_40)) * (1 + v_31), {v_38, 1}, {v_39, 1}, {v_40, 1}, 1}});
						} else {
							std::get<0>(it->second) += v_38;
							std::get<1>(it->second) += v_39;
							std::get<2>(it->second) += v_39 * (1 - v_40);
							std::get<3>(it->second) += (v_39 * (1 - v_40)) * (1 + v_31);
							std::get<4>(it->second) = {std::get<4>(it->second).first + v_38, std::get<4>(it->second).second + 1};
							std::get<5>(it->second) = {std::get<5>(it->second).first + v_39, std::get<5>(it->second).second + 1};
							std::get<6>(it->second) = {std::get<6>(it->second).first + v_40, std::get<6>(it->second).second + 1};
							std::get<7>(it->second) += 1;
						}
					}
				});
				for (auto& it : v_37) {
					const Varchar<1>& v_13 = std::get<0>(it.first);
					const Varchar<1>& v_41 = std::get<1>(it.first);
					const Numeric& v_42 = std::get<0>(it.second);
					const Numeric& v_43 = std::get<1>(it.second);
					const Numeric& v_44 = std::get<2>(it.second);
					const Numeric& v_45 = std::get<3>(it.second);
					const Numeric v_46 = std::get<4>(it.second).first / (double)std::get<4>(it.second).second;
					const Numeric v_47 = std::get<5>(it.second).first / (double)std::get<5>(it.second).second;
					const Numeric v_48 = std::get<6>(it.second).first / (double)std::get<6>(it.second).second;
					const Integer& v_49 = std::get<7>(it.second);
					v_36.push_back({v_13, v_41, v_13, v_41, v_42, v_43, v_44, v_45, v_46, v_47, v_48, v_49});
				}
			}
			std::sort(v_36.begin(), v_36.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				if (get<1>(t1) < get<1>(t2)) return true;
				if (get<1>(t2) < get<1>(t1)) return false;
				return false;
			});
			for (auto& t : v_36) {
				const Varchar<1>& v_13 = std::get<2>(t);
				const Varchar<1>& v_41 = std::get<3>(t);
				const Numeric& v_42 = std::get<4>(t);
				const Numeric& v_43 = std::get<5>(t);
				const Numeric& v_44 = std::get<6>(t);
				const Numeric& v_45 = std::get<7>(t);
				const Numeric& v_46 = std::get<8>(t);
				const Numeric& v_47 = std::get<9>(t);
				const Numeric& v_48 = std::get<10>(t);
				const Integer& v_49 = std::get<11>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_13 << ", " << v_41 << ", " << v_42 << ", " << v_43 << ", " << v_44 << ", " << v_45 << ", " << v_46 << ", " << v_47 << ", " << v_48 << ", " << v_49 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_10.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "c_custkey" << ", " << "c_name" << ", " << "c_acctbal" << ", " << "c_phone" << ", " << "n_name" << ", " << "c_address" << ", " << "c_comment" << ", " << "revenue" << std::endl;
		}
		{
			std::vector<std::tuple<Numeric, Integer, Varchar<25>, Numeric, Varchar<15>, Varchar<25>, Varchar<40>, Varchar<117>, Numeric>> v_36;
			v_36.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Integer, Varchar<25>, Numeric, Varchar<15>, Varchar<25>, Varchar<40>, Varchar<117>>, std::tuple<Numeric>> v_37(1024 * 1024);
				{
					std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Varchar<15>, Numeric, Varchar<117>, Numeric, Numeric>> v_50(1024 * 1024);
					{
						std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<117>>> v_51(1024 * 1024);
						{
							std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer>> v_52(1024 * 1024);
							db->orders_tpch.forEach([&](auto& key, auto& value) {
								const Integer& v_53 = key.o_orderkey;
								const Integer& v_54 = key.o_custkey;
								const Timestamp& v_55 = value.o_orderdate;
								if ((v_55 >= (2449262)) && (v_55 < (2449354))) {
									v_52.insert({{v_54}, {v_53}});
								}
							});
							db->customer_tpch.forEach([&](auto& key, auto& value) {
								const Integer& v_56 = key.c_custkey;
								const Varchar<25>& v_23 = value.c_name;
								const Varchar<40>& v_45 = value.c_address;
								const Integer& v_49 = value.c_nationkey;
								const Varchar<15>& v_57 = value.c_phone;
								const Numeric& v_40 = value.c_acctbal;
								const Varchar<117>& v_14 = value.c_comment;
								for (auto range = v_52.equal_range({v_56}); range.first!=range.second; range.first++) {
									const Integer& v_53 = std::get<0>(range.first->second);
									v_51.insert({{v_53}, {v_56, v_23, v_45, v_49, v_57, v_40, v_14}});
								}
							});
						}
						db->lineitem_tpch.forEach([&](auto& key, auto& value) {
							const Integer& v_58 = key.l_orderkey;
							const Numeric& v_59 = value.l_extendedprice;
							const Numeric& v_60 = value.l_discount;
							const Varchar<1>& v_61 = value.l_returnflag;
							if (v_61 == Varchar<1>("R")) {
								for (auto range = v_51.equal_range({v_58}); range.first!=range.second; range.first++) {
									const Integer& v_56 = std::get<0>(range.first->second);
									const Varchar<25>& v_23 = std::get<1>(range.first->second);
									const Varchar<40>& v_45 = std::get<2>(range.first->second);
									const Integer& v_49 = std::get<3>(range.first->second);
									const Varchar<15>& v_57 = std::get<4>(range.first->second);
									const Numeric& v_40 = std::get<5>(range.first->second);
									const Varchar<117>& v_14 = std::get<6>(range.first->second);
									v_50.insert({{v_49}, {v_56, v_23, v_45, v_57, v_40, v_14, v_59, v_60}});
								}
							}
						});
					}
					db->nation_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_62 = key.n_nationkey;
						const Varchar<25>& v_63 = value.n_name;
						for (auto range = v_50.equal_range({v_62}); range.first!=range.second; range.first++) {
							const Integer& v_56 = std::get<0>(range.first->second);
							const Varchar<25>& v_23 = std::get<1>(range.first->second);
							const Varchar<40>& v_45 = std::get<2>(range.first->second);
							const Varchar<15>& v_57 = std::get<3>(range.first->second);
							const Numeric& v_40 = std::get<4>(range.first->second);
							const Varchar<117>& v_14 = std::get<5>(range.first->second);
							const Numeric& v_59 = std::get<6>(range.first->second);
							const Numeric& v_60 = std::get<7>(range.first->second);
							auto it = v_37.find({v_56, v_23, v_40, v_57, v_63, v_45, v_14});
							if (it == v_37.end()) {
								v_37.insert({{v_56, v_23, v_40, v_57, v_63, v_45, v_14}, {v_59 * (1 - v_60)}});
							} else {
								std::get<0>(it->second) += v_59 * (1 - v_60);
							}
						}
					});
				}
				for (auto& it : v_37) {
					const Integer& v_64 = std::get<0>(it.first);
					const Varchar<25>& v_65 = std::get<1>(it.first);
					const Numeric& v_66 = std::get<2>(it.first);
					const Varchar<15>& v_67 = std::get<3>(it.first);
					const Varchar<25>& v_68 = std::get<4>(it.first);
					const Varchar<40>& v_69 = std::get<5>(it.first);
					const Varchar<117>& v_70 = std::get<6>(it.first);
					const Numeric& v_71 = std::get<0>(it.second);
					v_36.push_back({v_71, v_64, v_65, v_66, v_67, v_68, v_69, v_70, v_71});
				}
			}
			std::sort(v_36.begin(), v_36.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				return false;
			});
			for (auto& t : v_36) {
				const Integer& v_64 = std::get<1>(t);
				const Varchar<25>& v_65 = std::get<2>(t);
				const Numeric& v_66 = std::get<3>(t);
				const Varchar<15>& v_67 = std::get<4>(t);
				const Varchar<25>& v_68 = std::get<5>(t);
				const Varchar<40>& v_69 = std::get<6>(t);
				const Varchar<117>& v_70 = std::get<7>(t);
				const Numeric& v_71 = std::get<8>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_64 << ", " << v_65 << ", " << v_66 << ", " << v_67 << ", " << v_68 << ", " << v_69 << ", " << v_70 << ", " << v_71 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_14_changed.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "p_type" << ", " << "2" << std::endl;
		}
		{
			std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Numeric, Numeric>> v_72(1024 * 1024);
			{
				std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric>> v_73(1024 * 1024);
				db->lineitem_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_74 = key.l_partkey;
					const Numeric& v_5 = value.l_extendedprice;
					const Numeric& v_35 = value.l_discount;
					const Timestamp& v_54 = value.l_shipdate;
					if ((v_54 >= (2449962)) && (v_54 < (2449992))) {
						v_73.insert({{v_74}, {v_5, v_35}});
					}
				});
				db->part_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_75 = key.p_partkey;
					const Varchar<25>& v_57 = value.p_type;
					for (auto range = v_73.equal_range({v_75}); range.first!=range.second; range.first++) {
						const Numeric& v_5 = std::get<0>(range.first->second);
						const Numeric& v_35 = std::get<1>(range.first->second);
						auto it = v_72.find({v_57});
						if (it == v_72.end()) {
							v_72.insert({{v_57}, {v_5 * (1 - v_35), v_5 * (1 - v_35)}});
						} else {
							std::get<0>(it->second) += v_5 * (1 - v_35);
							std::get<1>(it->second) += v_5 * (1 - v_35);
						}
					}
				});
			}
			for (auto& it : v_72) {
				const Varchar<25>& v_13 = std::get<0>(it.first);
				const Numeric& v_76 = std::get<0>(it.second);
				const Numeric& v_77 = std::get<1>(it.second);
				Numeric v_78 = (100.00 * v_76) / v_77;
				if (limit > 0) {
					limit -= 1;
					std::cout << v_13 << ", " << v_78 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_3.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << [&]() {
				Integer v_6 = 0;
				{
					std::vector<std::tuple<Numeric, Timestamp>> v_79;
					v_79.reserve(1024 * 1024);
					{
						std::unordered_map<std::tuple<Integer, Timestamp, Integer>, std::tuple<Numeric>> v_80(1024 * 1024);
						{
							std::unordered_multimap<std::tuple<Integer>, std::tuple<Timestamp, Integer>> v_81(1024 * 1024);
							{
								std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_82(1024 * 1024);
								db->customer_tpch.forEach([&](auto& key, auto& value) {
									const Integer& v_83 = key.c_custkey;
									const Varchar<10>& v_84 = value.c_mktsegment;
									if (v_84 == Varchar<8>("BUILDING")) {
										v_82.insert({{v_83}, {}});
									}
								});
								db->orders_tpch.forEach([&](auto& key, auto& value) {
									const Integer& v_24 = key.o_orderkey;
									const Integer& v_40 = key.o_custkey;
									const Timestamp& v_9 = value.o_orderdate;
									const Integer& v_5 = value.o_shippriority;
									if (v_9 < (2449792)) {
										for (auto range = v_82.equal_range({v_40}); range.first!=range.second; range.first++) {
											v_81.insert({{v_24}, {v_9, v_5}});
										}
									}
								});
							}
							db->lineitem_tpch.forEach([&](auto& key, auto& value) {
								const Integer& v_85 = key.l_orderkey;
								const Numeric& v_86 = value.l_extendedprice;
								const Numeric& v_87 = value.l_discount;
								const Timestamp& v_14 = value.l_shipdate;
								if (v_14 > (2449792)) {
									for (auto range = v_81.equal_range({v_85}); range.first!=range.second; range.first++) {
										const Timestamp& v_9 = std::get<0>(range.first->second);
										const Integer& v_5 = std::get<1>(range.first->second);
										auto it = v_80.find({v_85, v_9, v_5});
										if (it == v_80.end()) {
											v_80.insert({{v_85, v_9, v_5}, {v_86 * (1 - v_87)}});
										} else {
											std::get<0>(it->second) += v_86 * (1 - v_87);
										}
									}
								}
							});
						}
						for (auto& it : v_80) {
							const Timestamp& v_88 = std::get<1>(it.first);
							const Numeric& v_89 = std::get<0>(it.second);
							v_79.push_back({v_89, v_88});
						}
					}
					std::sort(v_79.begin(), v_79.end(), [](const auto& t1, const auto& t2) {
						if (get<0>(t1) < get<0>(t2)) return true;
						if (get<0>(t2) < get<0>(t1)) return false;
						if (get<1>(t1) < get<1>(t2)) return true;
						if (get<1>(t2) < get<1>(t1)) return false;
						return false;
					});
					for (auto& t : v_79) {
						v_6 += 1;
					}
				}
				return v_6;
			}() << std::endl;
		}
	}},
	{"./query/benchmark/tpch_4_changed.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "o_orderpriority" << ", " << "order_count" << std::endl;
		}
		{
			std::vector<std::tuple<Varchar<15>, Varchar<15>, Integer>> v_36;
			v_36.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Varchar<15>>, std::tuple<Integer>> v_37(1024 * 1024);
				{
					std::unordered_multimap<std::tuple<Integer>, std::tuple<Varchar<15>>> v_50(1024 * 1024);
					db->orders_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_90 = key.o_orderkey;
						const Timestamp& v_91 = value.o_orderdate;
						const Varchar<15>& v_92 = value.o_orderpriority;
						if ((v_91 >= (2449170)) && (v_91 < (2449262))) {
							v_50.insert({{v_90}, {v_92}});
						}
					});
					db->lineitem_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_93 = key.l_orderkey;
						const Timestamp& v_5 = value.l_commitdate;
						const Timestamp& v_45 = value.l_receiptdate;
						if (v_5 < v_45) {
							for (auto range = v_50.equal_range({v_93}); range.first!=range.second; range.first++) {
								const Varchar<15>& v_92 = std::get<0>(range.first->second);
								auto it = v_37.find({v_92});
								if (it == v_37.end()) {
									v_37.insert({{v_92}, {1}});
								} else {
									std::get<0>(it->second) += 1;
								}
							}
						}
					});
				}
				for (auto& it : v_37) {
					const Varchar<15>& v_94 = std::get<0>(it.first);
					const Integer& v_95 = std::get<0>(it.second);
					v_36.push_back({v_94, v_94, v_95});
				}
			}
			std::sort(v_36.begin(), v_36.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				return false;
			});
			for (auto& t : v_36) {
				const Varchar<15>& v_94 = std::get<1>(t);
				const Integer& v_95 = std::get<2>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_94 << ", " << v_95 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_5.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "n_name" << ", " << "revenue" << std::endl;
		}
		{
			std::vector<std::tuple<Numeric, Varchar<25>, Numeric>> v_36;
			v_36.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Numeric>> v_37(1024 * 1024);
				{
					std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric, Varchar<25>>> v_50(1024 * 1024);
					{
						std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric>> v_51(1024 * 1024);
						{
							std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric>> v_52(1024 * 1024);
							{
								std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_96(1024 * 1024);
								{
									std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_97(1024 * 1024);
									db->customer_tpch.forEach([&](auto& key, auto& value) {
										const Integer& v_98 = key.c_custkey;
										v_97.insert({{v_98}, {}});
									});
									db->orders_tpch.forEach([&](auto& key, auto& value) {
										const Integer& v_40 = key.o_orderkey;
										const Integer& v_19 = key.o_custkey;
										const Timestamp& v_55 = value.o_orderdate;
										if ((v_55 >= (2449354)) && (v_55 < (2449719))) {
											for (auto range = v_97.equal_range({v_19}); range.first!=range.second; range.first++) {
												v_96.insert({{v_40}, {}});
											}
										}
									});
								}
								db->lineitem_tpch.forEach([&](auto& key, auto& value) {
									const Integer& v_99 = key.l_orderkey;
									const Integer& v_100 = key.l_suppkey;
									const Numeric& v_101 = value.l_extendedprice;
									const Numeric& v_102 = value.l_discount;
									for (auto range = v_96.equal_range({v_99}); range.first!=range.second; range.first++) {
										v_52.insert({{v_100}, {v_101, v_102}});
									}
								});
							}
							db->supplier_tpch.forEach([&](auto& key, auto& value) {
								const Integer& v_103 = key.s_suppkey;
								const Integer& v_104 = value.s_nationkey;
								for (auto range = v_52.equal_range({v_103}); range.first!=range.second; range.first++) {
									const Numeric& v_101 = std::get<0>(range.first->second);
									const Numeric& v_102 = std::get<1>(range.first->second);
									v_51.insert({{v_104}, {v_101, v_102}});
								}
							});
						}
						db->nation_tpch.forEach([&](auto& key, auto& value) {
							const Integer& v_105 = key.n_nationkey;
							const Varchar<25>& v_106 = value.n_name;
							const Integer& v_107 = value.n_regionkey;
							for (auto range = v_51.equal_range({v_105}); range.first!=range.second; range.first++) {
								const Numeric& v_101 = std::get<0>(range.first->second);
								const Numeric& v_102 = std::get<1>(range.first->second);
								v_50.insert({{v_107}, {v_101, v_102, v_106}});
							}
						});
					}
					db->region_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_108 = key.r_regionkey;
						const Varchar<25>& v_109 = value.r_name;
						if (v_109 == Varchar<4>("ASIA")) {
							for (auto range = v_50.equal_range({v_108}); range.first!=range.second; range.first++) {
								const Numeric& v_101 = std::get<0>(range.first->second);
								const Numeric& v_102 = std::get<1>(range.first->second);
								const Varchar<25>& v_106 = std::get<2>(range.first->second);
								auto it = v_37.find({v_106});
								if (it == v_37.end()) {
									v_37.insert({{v_106}, {v_101 * (1 - v_102)}});
								} else {
									std::get<0>(it->second) += v_101 * (1 - v_102);
								}
							}
						}
					});
				}
				for (auto& it : v_37) {
					const Varchar<25>& v_110 = std::get<0>(it.first);
					const Numeric& v_111 = std::get<0>(it.second);
					v_36.push_back({v_111, v_110, v_111});
				}
			}
			std::sort(v_36.begin(), v_36.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				return false;
			});
			for (auto& t : v_36) {
				const Varchar<25>& v_110 = std::get<1>(t);
				const Numeric& v_111 = std::get<2>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_110 << ", " << v_111 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_5_opt.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "n_name" << ", " << "revenue" << std::endl;
		}
		{
			std::vector<std::tuple<Numeric, Varchar<25>, Numeric>> v_36;
			v_36.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Numeric>> v_37(1024 * 1024);
				{
					std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_50(1024 * 1024);
					db->region_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_112 = key.r_regionkey;
						const Varchar<25>& v_92 = value.r_name;
						if (v_92 == Varchar<4>("ASIA")) {
							v_50.insert({{v_112}, {}});
						}
					});
					{
						std::unordered_multimap<std::tuple<Integer>, std::tuple<Varchar<25>, Integer>> v_51(1024 * 1024);
						db->nation_tpch.forEach([&](auto& key, auto& value) {
							const Integer& v_113 = key.n_nationkey;
							const Varchar<25>& v_28 = value.n_name;
							const Integer& v_24 = value.n_regionkey;
							v_51.insert({{v_113}, {v_28, v_24}});
						});
						{
							std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer>> v_52(1024 * 1024);
							db->supplier_tpch.forEach([&](auto& key, auto& value) {
								const Integer& v_9 = key.s_suppkey;
								const Integer& v_20 = value.s_nationkey;
								v_52.insert({{v_9}, {v_20}});
							});
							{
								std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_96(1024 * 1024);
								{
									std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_97(1024 * 1024);
									db->customer_tpch.forEach([&](auto& key, auto& value) {
										const Integer& v_86 = key.c_custkey;
										v_97.insert({{v_86}, {}});
									});
									db->orders_tpch.forEach([&](auto& key, auto& value) {
										const Integer& v_59 = key.o_orderkey;
										const Integer& v_114 = key.o_custkey;
										const Timestamp& v_115 = value.o_orderdate;
										if ((v_115 >= (2449354)) && (v_115 < (2449719))) {
											for (auto range = v_97.equal_range({v_114}); range.first!=range.second; range.first++) {
												v_96.insert({{v_59}, {}});
											}
										}
									});
								}
								db->lineitem_tpch.forEach([&](auto& key, auto& value) {
									const Integer& v_116 = key.l_orderkey;
									const Integer& v_117 = key.l_suppkey;
									const Numeric& v_118 = value.l_extendedprice;
									const Numeric& v_119 = value.l_discount;
									for (auto range = v_96.equal_range({v_116}); range.first!=range.second; range.first++) {
										for (auto range = v_52.equal_range({v_117}); range.first!=range.second; range.first++) {
											const Integer& v_20 = std::get<0>(range.first->second);
											for (auto range = v_51.equal_range({v_20}); range.first!=range.second; range.first++) {
												const Varchar<25>& v_28 = std::get<0>(range.first->second);
												const Integer& v_24 = std::get<1>(range.first->second);
												for (auto range = v_50.equal_range({v_24}); range.first!=range.second; range.first++) {
													auto it = v_37.find({v_28});
													if (it == v_37.end()) {
														v_37.insert({{v_28}, {v_118 * (1 - v_119)}});
													} else {
														std::get<0>(it->second) += v_118 * (1 - v_119);
													}
												}
											}
										}
									}
								});
							}
						}
					}
				}
				for (auto& it : v_37) {
					const Varchar<25>& v_120 = std::get<0>(it.first);
					const Numeric& v_121 = std::get<0>(it.second);
					v_36.push_back({v_121, v_120, v_121});
				}
			}
			std::sort(v_36.begin(), v_36.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				return false;
			});
			for (auto& t : v_36) {
				const Varchar<25>& v_120 = std::get<1>(t);
				const Numeric& v_121 = std::get<2>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_120 << ", " << v_121 << std::endl;
				}
			}
		}
	}},
}},
	{"scans", {
	{"./query/benchmark/handwritten.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "s_w_id" << ", " << "s_i_id" << ", " << "s_quantity" << ", " << "s_dist_01" << ", " << "s_dist_02" << ", " << "s_dist_03" << ", " << "s_dist_04" << ", " << "s_dist_05" << ", " << "s_dist_06" << ", " << "s_dist_07" << ", " << "s_dist_08" << ", " << "s_dist_09" << ", " << "s_dist_10" << ", " << "s_ytd" << ", " << "s_order_cnt" << ", " << "s_remote_cnt" << ", " << "s_data" << ", " << "ol_w_id" << ", " << "ol_d_id" << ", " << "ol_o_id" << ", " << "ol_number" << ", " << "ol_i_id" << ", " << "ol_supply_w_id" << ", " << "ol_delivery_d" << ", " << "ol_quantity" << ", " << "ol_amount" << ", " << "ol_dist_info" << std::endl;
		}
		{
			std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Numeric, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Numeric, Numeric, Numeric, Varchar<50>>> v_1(1024 * 1024);
			db->stock.forEach([&](auto& key, auto& value) {
				const Integer& v_2 = key.s_w_id;
				const Integer& v_3 = key.s_i_id;
				const Numeric& v_4 = value.s_quantity;
				const Varchar<24>& v_5 = value.s_dist_01;
				const Varchar<24>& v_6 = value.s_dist_02;
				const Varchar<24>& v_7 = value.s_dist_03;
				const Varchar<24>& v_8 = value.s_dist_04;
				const Varchar<24>& v_9 = value.s_dist_05;
				const Varchar<24>& v_10 = value.s_dist_06;
				const Varchar<24>& v_11 = value.s_dist_07;
				const Varchar<24>& v_12 = value.s_dist_08;
				const Varchar<24>& v_13 = value.s_dist_09;
				const Varchar<24>& v_14 = value.s_dist_10;
				const Numeric& v_15 = value.s_ytd;
				const Numeric& v_16 = value.s_order_cnt;
				const Numeric& v_17 = value.s_remote_cnt;
				const Varchar<50>& v_18 = value.s_data;
				if ((v_4 < 20) && (v_2 == 2)) {
					v_1.insert({{v_3}, {v_2, v_4, v_5, v_6, v_7, v_8, v_9, v_10, v_11, v_12, v_13, v_14, v_15, v_16, v_17, v_18}});
				}
			});
			db->orderline.forEach([&](auto& key, auto& value) {
				const Integer& v_19 = key.ol_w_id;
				const Integer& v_20 = key.ol_d_id;
				const Integer& v_21 = key.ol_o_id;
				const Integer& v_22 = key.ol_number;
				const Integer& v_23 = value.ol_i_id;
				const Integer& v_24 = value.ol_supply_w_id;
				const Timestamp& v_25 = value.ol_delivery_d;
				const Numeric& v_26 = value.ol_quantity;
				const Numeric& v_27 = value.ol_amount;
				const Varchar<24>& v_28 = value.ol_dist_info;
				if ((((v_21 < 3) && (v_21 >= (3 - 20))) && (v_19 == 1)) && (v_20 == 2)) {
					for (auto range = v_1.equal_range({v_23}); range.first!=range.second; range.first++) {
						const Integer& v_3 = std::get<0>(range.first->first);
						const Integer& v_2 = std::get<0>(range.first->second);
						const Numeric& v_4 = std::get<1>(range.first->second);
						const Varchar<24>& v_5 = std::get<2>(range.first->second);
						const Varchar<24>& v_6 = std::get<3>(range.first->second);
						const Varchar<24>& v_7 = std::get<4>(range.first->second);
						const Varchar<24>& v_8 = std::get<5>(range.first->second);
						const Varchar<24>& v_9 = std::get<6>(range.first->second);
						const Varchar<24>& v_10 = std::get<7>(range.first->second);
						const Varchar<24>& v_11 = std::get<8>(range.first->second);
						const Varchar<24>& v_12 = std::get<9>(range.first->second);
						const Varchar<24>& v_13 = std::get<10>(range.first->second);
						const Varchar<24>& v_14 = std::get<11>(range.first->second);
						const Numeric& v_15 = std::get<12>(range.first->second);
						const Numeric& v_16 = std::get<13>(range.first->second);
						const Numeric& v_17 = std::get<14>(range.first->second);
						const Varchar<50>& v_18 = std::get<15>(range.first->second);
						if (limit > 0) {
							limit -= 1;
							std::cout << v_2 << ", " << v_3 << ", " << v_4 << ", " << v_5 << ", " << v_6 << ", " << v_7 << ", " << v_8 << ", " << v_9 << ", " << v_10 << ", " << v_11 << ", " << v_12 << ", " << v_13 << ", " << v_14 << ", " << v_15 << ", " << v_16 << ", " << v_17 << ", " << v_18 << ", " << v_19 << ", " << v_20 << ", " << v_21 << ", " << v_22 << ", " << v_23 << ", " << v_24 << ", " << v_25 << ", " << v_26 << ", " << v_27 << ", " << v_28 << std::endl;
						}
					}
				}
			});
		}
	}},
	{"./query/benchmark/index_scan_query.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "s_suppkey" << ", " << "s_name" << ", " << "s_address" << ", " << "s_nationkey" << ", " << "s_phone" << ", " << "s_acctbal" << ", " << "s_comment" << ", " << "c_custkey" << ", " << "c_name" << ", " << "c_address" << ", " << "c_nationkey" << ", " << "c_phone" << ", " << "c_acctbal" << ", " << "c_mktsegment" << ", " << "c_comment" << std::endl;
		}
		{
			std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Varchar<15>, Numeric, Varchar<101>>> v_1(1024 * 1024);
			db->supplier_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_29 = key.s_suppkey;
				const Varchar<25>& v_30 = value.s_name;
				const Varchar<40>& v_31 = value.s_address;
				const Integer& v_32 = value.s_nationkey;
				const Varchar<15>& v_33 = value.s_phone;
				const Numeric& v_34 = value.s_acctbal;
				const Varchar<101>& v_35 = value.s_comment;
				v_1.insert({{v_32}, {v_29, v_30, v_31, v_33, v_34, v_35}});
			});
			db->customer_tpch.lookup1({1}, [&](auto& value) {
				Integer v_18 = 1;
				Varchar<25> v_22 = value.c_name;
				Varchar<40> v_23 = value.c_address;
				Integer v_27 = value.c_nationkey;
				Varchar<15> v_28 = value.c_phone;
				Numeric v_36 = value.c_acctbal;
				Varchar<10> v_9 = value.c_mktsegment;
				Varchar<117> v_21 = value.c_comment;
				for (auto range = v_1.equal_range({v_27}); range.first!=range.second; range.first++) {
					const Integer& v_32 = std::get<0>(range.first->first);
					const Integer& v_29 = std::get<0>(range.first->second);
					const Varchar<25>& v_30 = std::get<1>(range.first->second);
					const Varchar<40>& v_31 = std::get<2>(range.first->second);
					const Varchar<15>& v_33 = std::get<3>(range.first->second);
					const Numeric& v_34 = std::get<4>(range.first->second);
					const Varchar<101>& v_35 = std::get<5>(range.first->second);
					if (limit > 0) {
						limit -= 1;
						std::cout << v_29 << ", " << v_30 << ", " << v_31 << ", " << v_32 << ", " << v_33 << ", " << v_34 << ", " << v_35 << ", " << v_18 << ", " << v_22 << ", " << v_23 << ", " << v_27 << ", " << v_28 << ", " << v_36 << ", " << v_9 << ", " << v_21 << std::endl;
					}
				}
			});
		}
	}},
	{"./query/benchmark/tpch_1.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "l_returnflag" << ", " << "l_linestatus" << ", " << "sum_qty" << ", " << "sum_base_price" << ", " << "sum_disc_price" << ", " << "sum_charge" << ", " << "avg_qty" << ", " << "avg_price" << ", " << "avg_disc" << ", " << "count_order" << std::endl;
		}
		{
			std::vector<std::tuple<Varchar<1>, Varchar<1>, Varchar<1>, Varchar<1>, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Integer>> v_37;
			v_37.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Varchar<1>, Varchar<1>>, std::tuple<Numeric, Numeric, Numeric, Numeric, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, Integer>> v_38(1024 * 1024);
				db->lineitem_tpch.forEach([&](auto& key, auto& value) {
					const Numeric& v_39 = value.l_quantity;
					const Numeric& v_40 = value.l_extendedprice;
					const Numeric& v_13 = value.l_discount;
					const Numeric& v_32 = value.l_tax;
					const Varchar<1>& v_18 = value.l_returnflag;
					const Varchar<1>& v_22 = value.l_linestatus;
					const Timestamp& v_23 = value.l_shipdate;
					if (v_23 <= (2451058)) {
						auto it = v_38.find({v_18, v_22});
						if (it == v_38.end()) {
							v_38.insert({{v_18, v_22}, {v_39, v_40, v_40 * (1 - v_13), (v_40 * (1 - v_13)) * (1 + v_32), {v_39, 1}, {v_40, 1}, {v_13, 1}, 1}});
						} else {
							std::get<0>(it->second) += v_39;
							std::get<1>(it->second) += v_40;
							std::get<2>(it->second) += v_40 * (1 - v_13);
							std::get<3>(it->second) += (v_40 * (1 - v_13)) * (1 + v_32);
							std::get<4>(it->second) = {std::get<4>(it->second).first + v_39, std::get<4>(it->second).second + 1};
							std::get<5>(it->second) = {std::get<5>(it->second).first + v_40, std::get<5>(it->second).second + 1};
							std::get<6>(it->second) = {std::get<6>(it->second).first + v_13, std::get<6>(it->second).second + 1};
							std::get<7>(it->second) += 1;
						}
					}
				});
				for (auto& it : v_38) {
					const Varchar<1>& v_41 = std::get<0>(it.first);
					const Varchar<1>& v_42 = std::get<1>(it.first);
					const Numeric& v_43 = std::get<0>(it.second);
					const Numeric& v_44 = std::get<1>(it.second);
					const Numeric& v_45 = std::get<2>(it.second);
					const Numeric& v_46 = std::get<3>(it.second);
					const Numeric v_47 = std::get<4>(it.second).first / (double)std::get<4>(it.second).second;
					const Numeric v_48 = std::get<5>(it.second).first / (double)std::get<5>(it.second).second;
					const Numeric v_49 = std::get<6>(it.second).first / (double)std::get<6>(it.second).second;
					const Integer& v_50 = std::get<7>(it.second);
					v_37.push_back({v_41, v_42, v_41, v_42, v_43, v_44, v_45, v_46, v_47, v_48, v_49, v_50});
				}
			}
			std::sort(v_37.begin(), v_37.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				if (get<1>(t1) < get<1>(t2)) return true;
				if (get<1>(t2) < get<1>(t1)) return false;
				return false;
			});
			for (auto& t : v_37) {
				const Varchar<1>& v_41 = std::get<2>(t);
				const Varchar<1>& v_42 = std::get<3>(t);
				const Numeric& v_43 = std::get<4>(t);
				const Numeric& v_44 = std::get<5>(t);
				const Numeric& v_45 = std::get<6>(t);
				const Numeric& v_46 = std::get<7>(t);
				const Numeric& v_47 = std::get<8>(t);
				const Numeric& v_48 = std::get<9>(t);
				const Numeric& v_49 = std::get<10>(t);
				const Integer& v_50 = std::get<11>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_41 << ", " << v_42 << ", " << v_43 << ", " << v_44 << ", " << v_45 << ", " << v_46 << ", " << v_47 << ", " << v_48 << ", " << v_49 << ", " << v_50 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_10.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "c_custkey" << ", " << "c_name" << ", " << "c_acctbal" << ", " << "c_phone" << ", " << "n_name" << ", " << "c_address" << ", " << "c_comment" << ", " << "revenue" << std::endl;
		}
		{
			std::vector<std::tuple<Numeric, Integer, Varchar<25>, Numeric, Varchar<15>, Varchar<25>, Varchar<40>, Varchar<117>, Numeric>> v_37;
			v_37.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Integer, Varchar<25>, Numeric, Varchar<15>, Varchar<25>, Varchar<40>, Varchar<117>>, std::tuple<Numeric>> v_38(1024 * 1024);
				{
					std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Varchar<15>, Numeric, Varchar<117>, Numeric, Numeric>> v_51(1024 * 1024);
					{
						std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<117>>> v_52(1024 * 1024);
						{
							std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer>> v_53(1024 * 1024);
							db->orders_tpch.forEach([&](auto& key, auto& value) {
								const Integer& v_54 = key.o_orderkey;
								const Integer& v_55 = key.o_custkey;
								const Timestamp& v_56 = value.o_orderdate;
								if ((v_56 >= (2449262)) && (v_56 < (2449354))) {
									v_53.insert({{v_55}, {v_54}});
								}
							});
							db->customer_tpch.forEach([&](auto& key, auto& value) {
								const Integer& v_57 = key.c_custkey;
								const Varchar<25>& v_13 = value.c_name;
								const Varchar<40>& v_47 = value.c_address;
								const Integer& v_58 = value.c_nationkey;
								const Varchar<15>& v_50 = value.c_phone;
								const Numeric& v_33 = value.c_acctbal;
								const Varchar<117>& v_59 = value.c_comment;
								for (auto range = v_53.equal_range({v_57}); range.first!=range.second; range.first++) {
									const Integer& v_54 = std::get<0>(range.first->second);
									v_52.insert({{v_54}, {v_57, v_13, v_47, v_58, v_50, v_33, v_59}});
								}
							});
						}
						db->lineitem_tpch.forEach([&](auto& key, auto& value) {
							const Integer& v_60 = key.l_orderkey;
							const Numeric& v_61 = value.l_extendedprice;
							const Numeric& v_62 = value.l_discount;
							const Varchar<1>& v_14 = value.l_returnflag;
							if (v_14 == Varchar<1>("R")) {
								for (auto range = v_52.equal_range({v_60}); range.first!=range.second; range.first++) {
									const Integer& v_57 = std::get<0>(range.first->second);
									const Varchar<25>& v_13 = std::get<1>(range.first->second);
									const Varchar<40>& v_47 = std::get<2>(range.first->second);
									const Integer& v_58 = std::get<3>(range.first->second);
									const Varchar<15>& v_50 = std::get<4>(range.first->second);
									const Numeric& v_33 = std::get<5>(range.first->second);
									const Varchar<117>& v_59 = std::get<6>(range.first->second);
									v_51.insert({{v_58}, {v_57, v_13, v_47, v_50, v_33, v_59, v_61, v_62}});
								}
							}
						});
					}
					db->nation_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_63 = key.n_nationkey;
						const Varchar<25>& v_64 = value.n_name;
						for (auto range = v_51.equal_range({v_63}); range.first!=range.second; range.first++) {
							const Integer& v_57 = std::get<0>(range.first->second);
							const Varchar<25>& v_13 = std::get<1>(range.first->second);
							const Varchar<40>& v_47 = std::get<2>(range.first->second);
							const Varchar<15>& v_50 = std::get<3>(range.first->second);
							const Numeric& v_33 = std::get<4>(range.first->second);
							const Varchar<117>& v_59 = std::get<5>(range.first->second);
							const Numeric& v_61 = std::get<6>(range.first->second);
							const Numeric& v_62 = std::get<7>(range.first->second);
							auto it = v_38.find({v_57, v_13, v_33, v_50, v_64, v_47, v_59});
							if (it == v_38.end()) {
								v_38.insert({{v_57, v_13, v_33, v_50, v_64, v_47, v_59}, {v_61 * (1 - v_62)}});
							} else {
								std::get<0>(it->second) += v_61 * (1 - v_62);
							}
						}
					});
				}
				for (auto& it : v_38) {
					const Integer& v_65 = std::get<0>(it.first);
					const Varchar<25>& v_66 = std::get<1>(it.first);
					const Numeric& v_67 = std::get<2>(it.first);
					const Varchar<15>& v_68 = std::get<3>(it.first);
					const Varchar<25>& v_69 = std::get<4>(it.first);
					const Varchar<40>& v_70 = std::get<5>(it.first);
					const Varchar<117>& v_71 = std::get<6>(it.first);
					const Numeric& v_72 = std::get<0>(it.second);
					v_37.push_back({v_72, v_65, v_66, v_67, v_68, v_69, v_70, v_71, v_72});
				}
			}
			std::sort(v_37.begin(), v_37.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				return false;
			});
			for (auto& t : v_37) {
				const Integer& v_65 = std::get<1>(t);
				const Varchar<25>& v_66 = std::get<2>(t);
				const Numeric& v_67 = std::get<3>(t);
				const Varchar<15>& v_68 = std::get<4>(t);
				const Varchar<25>& v_69 = std::get<5>(t);
				const Varchar<40>& v_70 = std::get<6>(t);
				const Varchar<117>& v_71 = std::get<7>(t);
				const Numeric& v_72 = std::get<8>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_65 << ", " << v_66 << ", " << v_67 << ", " << v_68 << ", " << v_69 << ", " << v_70 << ", " << v_71 << ", " << v_72 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_14_changed.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "p_type" << ", " << "2" << std::endl;
		}
		{
			std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Numeric, Numeric>> v_73(1024 * 1024);
			{
				std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric, Timestamp>> v_74(1024 * 1024);
				db->lineitem_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_46 = key.l_partkey;
					const Numeric& v_75 = value.l_extendedprice;
					const Numeric& v_76 = value.l_discount;
					const Timestamp& v_27 = value.l_shipdate;
					v_74.insert({{v_46}, {v_75, v_76, v_27}});
				});
				db->part_tpch.forEach([&](auto& key, auto& value) {
					const Integer& v_55 = key.p_partkey;
					const Varchar<25>& v_57 = value.p_type;
					for (auto range = v_74.equal_range({v_55}); range.first!=range.second; range.first++) {
						const Numeric& v_75 = std::get<0>(range.first->second);
						const Numeric& v_76 = std::get<1>(range.first->second);
						const Timestamp& v_27 = std::get<2>(range.first->second);
						if ((v_27 >= (2449962)) && (v_27 < (2449992))) {
							auto it = v_73.find({v_57});
							if (it == v_73.end()) {
								v_73.insert({{v_57}, {v_75 * (1 - v_76), v_75 * (1 - v_76)}});
							} else {
								std::get<0>(it->second) += v_75 * (1 - v_76);
								std::get<1>(it->second) += v_75 * (1 - v_76);
							}
						}
					}
				});
			}
			for (auto& it : v_73) {
				const Varchar<25>& v_77 = std::get<0>(it.first);
				const Numeric& v_78 = std::get<0>(it.second);
				const Numeric& v_79 = std::get<1>(it.second);
				Numeric v_80 = (100.00 * v_78) / v_79;
				if (limit > 0) {
					limit -= 1;
					std::cout << v_77 << ", " << v_80 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_3.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << [&]() {
				Integer v_81 = 0;
				{
					std::vector<std::tuple<Numeric, Timestamp>> v_82;
					v_82.reserve(1024 * 1024);
					{
						std::unordered_map<std::tuple<Integer, Timestamp, Integer>, std::tuple<Numeric>> v_83(1024 * 1024);
						{
							std::unordered_multimap<std::tuple<Integer>, std::tuple<Timestamp, Integer>> v_84(1024 * 1024);
							{
								std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_85(1024 * 1024);
								db->customer_tpch.forEach([&](auto& key, auto& value) {
									const Integer& v_86 = key.c_custkey;
									const Varchar<10>& v_87 = value.c_mktsegment;
									if (v_87 == Varchar<8>("BUILDING")) {
										v_85.insert({{v_86}, {}});
									}
								});
								db->orders_tpch.forEach([&](auto& key, auto& value) {
									const Integer& v_28 = key.o_orderkey;
									const Integer& v_58 = key.o_custkey;
									const Timestamp& v_18 = value.o_orderdate;
									const Integer& v_33 = value.o_shippriority;
									if (v_18 < (2449792)) {
										for (auto range = v_85.equal_range({v_58}); range.first!=range.second; range.first++) {
											v_84.insert({{v_28}, {v_18, v_33}});
										}
									}
								});
							}
							db->lineitem_tpch.forEach([&](auto& key, auto& value) {
								const Integer& v_56 = key.l_orderkey;
								const Numeric& v_14 = value.l_extendedprice;
								const Numeric& v_16 = value.l_discount;
								const Timestamp& v_88 = value.l_shipdate;
								if (v_88 > (2449792)) {
									for (auto range = v_84.equal_range({v_56}); range.first!=range.second; range.first++) {
										const Timestamp& v_18 = std::get<0>(range.first->second);
										const Integer& v_33 = std::get<1>(range.first->second);
										auto it = v_83.find({v_56, v_18, v_33});
										if (it == v_83.end()) {
											v_83.insert({{v_56, v_18, v_33}, {v_14 * (1 - v_16)}});
										} else {
											std::get<0>(it->second) += v_14 * (1 - v_16);
										}
									}
								}
							});
						}
						for (auto& it : v_83) {
							const Timestamp& v_89 = std::get<1>(it.first);
							const Numeric& v_90 = std::get<0>(it.second);
							v_82.push_back({v_90, v_89});
						}
					}
					std::sort(v_82.begin(), v_82.end(), [](const auto& t1, const auto& t2) {
						if (get<0>(t1) < get<0>(t2)) return true;
						if (get<0>(t2) < get<0>(t1)) return false;
						if (get<1>(t1) < get<1>(t2)) return true;
						if (get<1>(t2) < get<1>(t1)) return false;
						return false;
					});
					for (auto& t : v_82) {
						v_81 += 1;
					}
				}
				return v_81;
			}() << std::endl;
		}
	}},
	{"./query/benchmark/tpch_4_changed.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "o_orderpriority" << ", " << "order_count" << std::endl;
		}
		{
			std::vector<std::tuple<Varchar<15>, Varchar<15>, Integer>> v_37;
			v_37.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Varchar<15>>, std::tuple<Integer>> v_38(1024 * 1024);
				{
					std::unordered_multimap<std::tuple<Integer>, std::tuple<Varchar<15>>> v_51(1024 * 1024);
					db->orders_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_91 = key.o_orderkey;
						const Timestamp& v_36 = value.o_orderdate;
						const Varchar<15>& v_92 = value.o_orderpriority;
						if ((v_36 >= (2449170)) && (v_36 < (2449262))) {
							v_51.insert({{v_91}, {v_92}});
						}
					});
					db->lineitem_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_13 = key.l_orderkey;
						const Timestamp& v_93 = value.l_commitdate;
						const Timestamp& v_94 = value.l_receiptdate;
						if (v_93 < v_94) {
							for (auto range = v_51.equal_range({v_13}); range.first!=range.second; range.first++) {
								const Varchar<15>& v_92 = std::get<0>(range.first->second);
								auto it = v_38.find({v_92});
								if (it == v_38.end()) {
									v_38.insert({{v_92}, {1}});
								} else {
									std::get<0>(it->second) += 1;
								}
							}
						}
					});
				}
				for (auto& it : v_38) {
					const Varchar<15>& v_72 = std::get<0>(it.first);
					const Integer& v_95 = std::get<0>(it.second);
					v_37.push_back({v_72, v_72, v_95});
				}
			}
			std::sort(v_37.begin(), v_37.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				return false;
			});
			for (auto& t : v_37) {
				const Varchar<15>& v_72 = std::get<1>(t);
				const Integer& v_95 = std::get<2>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_72 << ", " << v_95 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_5.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "n_name" << ", " << "revenue" << std::endl;
		}
		{
			std::vector<std::tuple<Numeric, Varchar<25>, Numeric>> v_37;
			v_37.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Numeric>> v_38(1024 * 1024);
				{
					std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric, Varchar<25>>> v_51(1024 * 1024);
					{
						std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric>> v_52(1024 * 1024);
						{
							std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric>> v_53(1024 * 1024);
							{
								std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_96(1024 * 1024);
								{
									std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_97(1024 * 1024);
									db->customer_tpch.forEach([&](auto& key, auto& value) {
										const Integer& v_98 = key.c_custkey;
										v_97.insert({{v_98}, {}});
									});
									db->orders_tpch.forEach([&](auto& key, auto& value) {
										const Integer& v_99 = key.o_orderkey;
										const Integer& v_58 = key.o_custkey;
										const Timestamp& v_24 = value.o_orderdate;
										if ((v_24 >= (2449354)) && (v_24 < (2449719))) {
											for (auto range = v_97.equal_range({v_58}); range.first!=range.second; range.first++) {
												v_96.insert({{v_99}, {}});
											}
										}
									});
								}
								db->lineitem_tpch.forEach([&](auto& key, auto& value) {
									const Integer& v_100 = key.l_orderkey;
									const Integer& v_101 = key.l_suppkey;
									const Numeric& v_102 = value.l_extendedprice;
									const Numeric& v_103 = value.l_discount;
									for (auto range = v_96.equal_range({v_100}); range.first!=range.second; range.first++) {
										v_53.insert({{v_101}, {v_102, v_103}});
									}
								});
							}
							db->supplier_tpch.forEach([&](auto& key, auto& value) {
								const Integer& v_104 = key.s_suppkey;
								const Integer& v_105 = value.s_nationkey;
								for (auto range = v_53.equal_range({v_104}); range.first!=range.second; range.first++) {
									const Numeric& v_102 = std::get<0>(range.first->second);
									const Numeric& v_103 = std::get<1>(range.first->second);
									v_52.insert({{v_105}, {v_102, v_103}});
								}
							});
						}
						db->nation_tpch.forEach([&](auto& key, auto& value) {
							const Integer& v_106 = key.n_nationkey;
							const Varchar<25>& v_107 = value.n_name;
							const Integer& v_108 = value.n_regionkey;
							for (auto range = v_52.equal_range({v_106}); range.first!=range.second; range.first++) {
								const Numeric& v_102 = std::get<0>(range.first->second);
								const Numeric& v_103 = std::get<1>(range.first->second);
								v_51.insert({{v_108}, {v_102, v_103, v_107}});
							}
						});
					}
					db->region_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_109 = key.r_regionkey;
						const Varchar<25>& v_110 = value.r_name;
						if (v_110 == Varchar<4>("ASIA")) {
							for (auto range = v_51.equal_range({v_109}); range.first!=range.second; range.first++) {
								const Numeric& v_102 = std::get<0>(range.first->second);
								const Numeric& v_103 = std::get<1>(range.first->second);
								const Varchar<25>& v_107 = std::get<2>(range.first->second);
								auto it = v_38.find({v_107});
								if (it == v_38.end()) {
									v_38.insert({{v_107}, {v_102 * (1 - v_103)}});
								} else {
									std::get<0>(it->second) += v_102 * (1 - v_103);
								}
							}
						}
					});
				}
				for (auto& it : v_38) {
					const Varchar<25>& v_111 = std::get<0>(it.first);
					const Numeric& v_112 = std::get<0>(it.second);
					v_37.push_back({v_112, v_111, v_112});
				}
			}
			std::sort(v_37.begin(), v_37.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				return false;
			});
			for (auto& t : v_37) {
				const Varchar<25>& v_111 = std::get<1>(t);
				const Numeric& v_112 = std::get<2>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_111 << ", " << v_112 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_5_opt.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "n_name" << ", " << "revenue" << std::endl;
		}
		{
			std::vector<std::tuple<Numeric, Varchar<25>, Numeric>> v_37;
			v_37.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Numeric>> v_38(1024 * 1024);
				{
					std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_51(1024 * 1024);
					db->region_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_113 = key.r_regionkey;
						const Varchar<25>& v_114 = value.r_name;
						if (v_114 == Varchar<4>("ASIA")) {
							v_51.insert({{v_113}, {}});
						}
					});
					{
						std::unordered_multimap<std::tuple<Integer>, std::tuple<Varchar<25>, Integer>> v_52(1024 * 1024);
						db->nation_tpch.forEach([&](auto& key, auto& value) {
							const Integer& v_115 = key.n_nationkey;
							const Varchar<25>& v_116 = value.n_name;
							const Integer& v_21 = value.n_regionkey;
							v_52.insert({{v_115}, {v_116, v_21}});
						});
						{
							std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer>> v_53(1024 * 1024);
							db->supplier_tpch.forEach([&](auto& key, auto& value) {
								const Integer& v_24 = key.s_suppkey;
								const Integer& v_27 = value.s_nationkey;
								v_53.insert({{v_24}, {v_27}});
							});
							{
								std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_96(1024 * 1024);
								{
									std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_97(1024 * 1024);
									db->customer_tpch.forEach([&](auto& key, auto& value) {
										const Integer& v_117 = key.c_custkey;
										v_97.insert({{v_117}, {}});
									});
									db->orders_tpch.forEach([&](auto& key, auto& value) {
										const Integer& v_118 = key.o_orderkey;
										const Integer& v_119 = key.o_custkey;
										const Timestamp& v_87 = value.o_orderdate;
										if ((v_87 >= (2449354)) && (v_87 < (2449719))) {
											for (auto range = v_97.equal_range({v_119}); range.first!=range.second; range.first++) {
												v_96.insert({{v_118}, {}});
											}
										}
									});
								}
								db->lineitem_tpch.forEach([&](auto& key, auto& value) {
									const Integer& v_120 = key.l_orderkey;
									const Integer& v_121 = key.l_suppkey;
									const Numeric& v_122 = value.l_extendedprice;
									const Numeric& v_123 = value.l_discount;
									for (auto range = v_96.equal_range({v_120}); range.first!=range.second; range.first++) {
										for (auto range = v_53.equal_range({v_121}); range.first!=range.second; range.first++) {
											const Integer& v_27 = std::get<0>(range.first->second);
											for (auto range = v_52.equal_range({v_27}); range.first!=range.second; range.first++) {
												const Varchar<25>& v_116 = std::get<0>(range.first->second);
												const Integer& v_21 = std::get<1>(range.first->second);
												for (auto range = v_51.equal_range({v_21}); range.first!=range.second; range.first++) {
													auto it = v_38.find({v_116});
													if (it == v_38.end()) {
														v_38.insert({{v_116}, {v_122 * (1 - v_123)}});
													} else {
														std::get<0>(it->second) += v_122 * (1 - v_123);
													}
												}
											}
										}
									}
								});
							}
						}
					}
				}
				for (auto& it : v_38) {
					const Varchar<25>& v_124 = std::get<0>(it.first);
					const Numeric& v_125 = std::get<0>(it.second);
					v_37.push_back({v_125, v_124, v_125});
				}
			}
			std::sort(v_37.begin(), v_37.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				return false;
			});
			for (auto& t : v_37) {
				const Varchar<25>& v_124 = std::get<1>(t);
				const Numeric& v_125 = std::get<2>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_124 << ", " << v_125 << std::endl;
				}
			}
		}
	}},
}},
	{"joins", {
	{"./query/benchmark/handwritten.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "s_w_id" << ", " << "s_i_id" << ", " << "s_quantity" << ", " << "s_dist_01" << ", " << "s_dist_02" << ", " << "s_dist_03" << ", " << "s_dist_04" << ", " << "s_dist_05" << ", " << "s_dist_06" << ", " << "s_dist_07" << ", " << "s_dist_08" << ", " << "s_dist_09" << ", " << "s_dist_10" << ", " << "s_ytd" << ", " << "s_order_cnt" << ", " << "s_remote_cnt" << ", " << "s_data" << ", " << "ol_w_id" << ", " << "ol_d_id" << ", " << "ol_o_id" << ", " << "ol_number" << ", " << "ol_i_id" << ", " << "ol_supply_w_id" << ", " << "ol_delivery_d" << ", " << "ol_quantity" << ", " << "ol_amount" << ", " << "ol_dist_info" << std::endl;
		}
		{
			std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Numeric, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Numeric, Numeric, Numeric, Varchar<50>>> v_1(1024 * 1024);
			db->stock.forEach([&](auto& key, auto& value) {
				const Integer& v_2 = key.s_w_id;
				const Integer& v_3 = key.s_i_id;
				const Numeric& v_4 = value.s_quantity;
				const Varchar<24>& v_5 = value.s_dist_01;
				const Varchar<24>& v_6 = value.s_dist_02;
				const Varchar<24>& v_7 = value.s_dist_03;
				const Varchar<24>& v_8 = value.s_dist_04;
				const Varchar<24>& v_9 = value.s_dist_05;
				const Varchar<24>& v_10 = value.s_dist_06;
				const Varchar<24>& v_11 = value.s_dist_07;
				const Varchar<24>& v_12 = value.s_dist_08;
				const Varchar<24>& v_13 = value.s_dist_09;
				const Varchar<24>& v_14 = value.s_dist_10;
				const Numeric& v_15 = value.s_ytd;
				const Numeric& v_16 = value.s_order_cnt;
				const Numeric& v_17 = value.s_remote_cnt;
				const Varchar<50>& v_18 = value.s_data;
				if ((v_2 == 2) && (v_4 < 20)) {
					v_1.insert({{v_3}, {v_2, v_4, v_5, v_6, v_7, v_8, v_9, v_10, v_11, v_12, v_13, v_14, v_15, v_16, v_17, v_18}});
				}
			});
			db->orderline.forEach([&](auto& key, auto& value) {
				const Integer& v_19 = key.ol_w_id;
				const Integer& v_20 = key.ol_d_id;
				const Integer& v_21 = key.ol_o_id;
				const Integer& v_22 = key.ol_number;
				const Integer& v_23 = value.ol_i_id;
				const Integer& v_24 = value.ol_supply_w_id;
				const Timestamp& v_25 = value.ol_delivery_d;
				const Numeric& v_26 = value.ol_quantity;
				const Numeric& v_27 = value.ol_amount;
				const Varchar<24>& v_28 = value.ol_dist_info;
				if ((((v_19 == 1) && (v_20 == 2)) && (v_21 < 3)) && (v_21 >= (3 - 20))) {
					for (auto range = v_1.equal_range({v_23}); range.first!=range.second; range.first++) {
						const Integer& v_3 = std::get<0>(range.first->first);
						const Integer& v_2 = std::get<0>(range.first->second);
						const Numeric& v_4 = std::get<1>(range.first->second);
						const Varchar<24>& v_5 = std::get<2>(range.first->second);
						const Varchar<24>& v_6 = std::get<3>(range.first->second);
						const Varchar<24>& v_7 = std::get<4>(range.first->second);
						const Varchar<24>& v_8 = std::get<5>(range.first->second);
						const Varchar<24>& v_9 = std::get<6>(range.first->second);
						const Varchar<24>& v_10 = std::get<7>(range.first->second);
						const Varchar<24>& v_11 = std::get<8>(range.first->second);
						const Varchar<24>& v_12 = std::get<9>(range.first->second);
						const Varchar<24>& v_13 = std::get<10>(range.first->second);
						const Varchar<24>& v_14 = std::get<11>(range.first->second);
						const Numeric& v_15 = std::get<12>(range.first->second);
						const Numeric& v_16 = std::get<13>(range.first->second);
						const Numeric& v_17 = std::get<14>(range.first->second);
						const Varchar<50>& v_18 = std::get<15>(range.first->second);
						if (limit > 0) {
							limit -= 1;
							std::cout << v_2 << ", " << v_3 << ", " << v_4 << ", " << v_5 << ", " << v_6 << ", " << v_7 << ", " << v_8 << ", " << v_9 << ", " << v_10 << ", " << v_11 << ", " << v_12 << ", " << v_13 << ", " << v_14 << ", " << v_15 << ", " << v_16 << ", " << v_17 << ", " << v_18 << ", " << v_19 << ", " << v_20 << ", " << v_21 << ", " << v_22 << ", " << v_23 << ", " << v_24 << ", " << v_25 << ", " << v_26 << ", " << v_27 << ", " << v_28 << std::endl;
						}
					}
				}
			});
		}
	}},
	{"./query/benchmark/index_scan_query.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "s_suppkey" << ", " << "s_name" << ", " << "s_address" << ", " << "s_nationkey" << ", " << "s_phone" << ", " << "s_acctbal" << ", " << "s_comment" << ", " << "c_custkey" << ", " << "c_name" << ", " << "c_address" << ", " << "c_nationkey" << ", " << "c_phone" << ", " << "c_acctbal" << ", " << "c_mktsegment" << ", " << "c_comment" << std::endl;
		}
		{
			std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Varchar<15>, Numeric, Varchar<101>>> v_1(1024 * 1024);
			db->supplier_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_29 = key.s_suppkey;
				const Varchar<25>& v_30 = value.s_name;
				const Varchar<40>& v_31 = value.s_address;
				const Integer& v_32 = value.s_nationkey;
				const Varchar<15>& v_33 = value.s_phone;
				const Numeric& v_34 = value.s_acctbal;
				const Varchar<101>& v_35 = value.s_comment;
				v_1.insert({{v_32}, {v_29, v_30, v_31, v_33, v_34, v_35}});
			});
			db->customer_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_26 = key.c_custkey;
				const Varchar<25>& v_10 = value.c_name;
				const Varchar<40>& v_27 = value.c_address;
				const Integer& v_36 = value.c_nationkey;
				const Varchar<15>& v_9 = value.c_phone;
				const Numeric& v_37 = value.c_acctbal;
				const Varchar<10>& v_16 = value.c_mktsegment;
				const Varchar<117>& v_15 = value.c_comment;
				if (v_26 == 1) {
					for (auto range = v_1.equal_range({v_36}); range.first!=range.second; range.first++) {
						const Integer& v_32 = std::get<0>(range.first->first);
						const Integer& v_29 = std::get<0>(range.first->second);
						const Varchar<25>& v_30 = std::get<1>(range.first->second);
						const Varchar<40>& v_31 = std::get<2>(range.first->second);
						const Varchar<15>& v_33 = std::get<3>(range.first->second);
						const Numeric& v_34 = std::get<4>(range.first->second);
						const Varchar<101>& v_35 = std::get<5>(range.first->second);
						if (limit > 0) {
							limit -= 1;
							std::cout << v_29 << ", " << v_30 << ", " << v_31 << ", " << v_32 << ", " << v_33 << ", " << v_34 << ", " << v_35 << ", " << v_26 << ", " << v_10 << ", " << v_27 << ", " << v_36 << ", " << v_9 << ", " << v_37 << ", " << v_16 << ", " << v_15 << std::endl;
						}
					}
				}
			});
		}
	}},
	{"./query/benchmark/tpch_1.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "l_returnflag" << ", " << "l_linestatus" << ", " << "sum_qty" << ", " << "sum_base_price" << ", " << "sum_disc_price" << ", " << "sum_charge" << ", " << "avg_qty" << ", " << "avg_price" << ", " << "avg_disc" << ", " << "count_order" << std::endl;
		}
		{
			std::vector<std::tuple<Varchar<1>, Varchar<1>, Varchar<1>, Varchar<1>, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Integer>> v_38;
			v_38.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Varchar<1>, Varchar<1>>, std::tuple<Numeric, Numeric, Numeric, Numeric, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, Integer>> v_39(1024 * 1024);
				db->lineitem_tpch.forEach([&](auto& key, auto& value) {
					const Numeric& v_40 = value.l_quantity;
					const Numeric& v_41 = value.l_extendedprice;
					const Numeric& v_42 = value.l_discount;
					const Numeric& v_9 = value.l_tax;
					const Varchar<1>& v_43 = value.l_returnflag;
					const Varchar<1>& v_26 = value.l_linestatus;
					const Timestamp& v_10 = value.l_shipdate;
					if (v_10 <= (2451058)) {
						auto it = v_39.find({v_43, v_26});
						if (it == v_39.end()) {
							v_39.insert({{v_43, v_26}, {v_40, v_41, v_41 * (1 - v_42), (v_41 * (1 - v_42)) * (1 + v_9), {v_40, 1}, {v_41, 1}, {v_42, 1}, 1}});
						} else {
							std::get<0>(it->second) += v_40;
							std::get<1>(it->second) += v_41;
							std::get<2>(it->second) += v_41 * (1 - v_42);
							std::get<3>(it->second) += (v_41 * (1 - v_42)) * (1 + v_9);
							std::get<4>(it->second) = {std::get<4>(it->second).first + v_40, std::get<4>(it->second).second + 1};
							std::get<5>(it->second) = {std::get<5>(it->second).first + v_41, std::get<5>(it->second).second + 1};
							std::get<6>(it->second) = {std::get<6>(it->second).first + v_42, std::get<6>(it->second).second + 1};
							std::get<7>(it->second) += 1;
						}
					}
				});
				for (auto& it : v_39) {
					const Varchar<1>& v_44 = std::get<0>(it.first);
					const Varchar<1>& v_45 = std::get<1>(it.first);
					const Numeric& v_46 = std::get<0>(it.second);
					const Numeric& v_47 = std::get<1>(it.second);
					const Numeric& v_48 = std::get<2>(it.second);
					const Numeric& v_49 = std::get<3>(it.second);
					const Numeric v_50 = std::get<4>(it.second).first / (double)std::get<4>(it.second).second;
					const Numeric v_51 = std::get<5>(it.second).first / (double)std::get<5>(it.second).second;
					const Numeric v_52 = std::get<6>(it.second).first / (double)std::get<6>(it.second).second;
					const Integer& v_53 = std::get<7>(it.second);
					v_38.push_back({v_44, v_45, v_44, v_45, v_46, v_47, v_48, v_49, v_50, v_51, v_52, v_53});
				}
			}
			std::sort(v_38.begin(), v_38.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				if (get<1>(t1) < get<1>(t2)) return true;
				if (get<1>(t2) < get<1>(t1)) return false;
				return false;
			});
			for (auto& t : v_38) {
				const Varchar<1>& v_44 = std::get<2>(t);
				const Varchar<1>& v_45 = std::get<3>(t);
				const Numeric& v_46 = std::get<4>(t);
				const Numeric& v_47 = std::get<5>(t);
				const Numeric& v_48 = std::get<6>(t);
				const Numeric& v_49 = std::get<7>(t);
				const Numeric& v_50 = std::get<8>(t);
				const Numeric& v_51 = std::get<9>(t);
				const Numeric& v_52 = std::get<10>(t);
				const Integer& v_53 = std::get<11>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_44 << ", " << v_45 << ", " << v_46 << ", " << v_47 << ", " << v_48 << ", " << v_49 << ", " << v_50 << ", " << v_51 << ", " << v_52 << ", " << v_53 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_10.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "c_custkey" << ", " << "c_name" << ", " << "c_acctbal" << ", " << "c_phone" << ", " << "n_name" << ", " << "c_address" << ", " << "c_comment" << ", " << "revenue" << std::endl;
		}
		{
			std::vector<std::tuple<Numeric, Integer, Varchar<25>, Numeric, Varchar<15>, Varchar<25>, Varchar<40>, Varchar<117>, Numeric>> v_38;
			v_38.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Integer, Varchar<25>, Numeric, Varchar<15>, Varchar<25>, Varchar<40>, Varchar<117>>, std::tuple<Numeric>> v_39(1024 * 1024);
				{
					std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<117>>> v_54(1024 * 1024);
					db->orders_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_55 = key.o_orderkey;
						const Integer& v_56 = key.o_custkey;
						const Timestamp& v_57 = value.o_orderdate;
						if ((v_57 >= (2449262)) && (v_57 < (2449354))) {
							db->customer_tpch.lookup1({v_56}, [&](auto& value) {
								Integer v_53 = v_56;
								Varchar<25> v_25 = value.c_name;
								Varchar<40> v_58 = value.c_address;
								Integer v_59 = value.c_nationkey;
								Varchar<15> v_60 = value.c_phone;
								Numeric v_15 = value.c_acctbal;
								Varchar<117> v_61 = value.c_comment;
								v_54.insert({{v_55}, {v_53, v_25, v_58, v_59, v_60, v_15, v_61}});
							});
						}
					});
					db->lineitem_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_62 = key.l_orderkey;
						const Numeric& v_63 = value.l_extendedprice;
						const Numeric& v_64 = value.l_discount;
						const Varchar<1>& v_65 = value.l_returnflag;
						if (v_65 == Varchar<1>("R")) {
							for (auto range = v_54.equal_range({v_62}); range.first!=range.second; range.first++) {
								const Integer& v_53 = std::get<0>(range.first->second);
								const Varchar<25>& v_25 = std::get<1>(range.first->second);
								const Varchar<40>& v_58 = std::get<2>(range.first->second);
								const Integer& v_59 = std::get<3>(range.first->second);
								const Varchar<15>& v_60 = std::get<4>(range.first->second);
								const Numeric& v_15 = std::get<5>(range.first->second);
								const Varchar<117>& v_61 = std::get<6>(range.first->second);
								db->nation_tpch.lookup1({v_59}, [&](auto& value) {
									Varchar<25> v_66 = value.n_name;
									auto it = v_39.find({v_53, v_25, v_15, v_60, v_66, v_58, v_61});
									if (it == v_39.end()) {
										v_39.insert({{v_53, v_25, v_15, v_60, v_66, v_58, v_61}, {v_63 * (1 - v_64)}});
									} else {
										std::get<0>(it->second) += v_63 * (1 - v_64);
									}
								});
							}
						}
					});
				}
				for (auto& it : v_39) {
					const Integer& v_67 = std::get<0>(it.first);
					const Varchar<25>& v_68 = std::get<1>(it.first);
					const Numeric& v_69 = std::get<2>(it.first);
					const Varchar<15>& v_70 = std::get<3>(it.first);
					const Varchar<25>& v_71 = std::get<4>(it.first);
					const Varchar<40>& v_72 = std::get<5>(it.first);
					const Varchar<117>& v_73 = std::get<6>(it.first);
					const Numeric& v_74 = std::get<0>(it.second);
					v_38.push_back({v_74, v_67, v_68, v_69, v_70, v_71, v_72, v_73, v_74});
				}
			}
			std::sort(v_38.begin(), v_38.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				return false;
			});
			for (auto& t : v_38) {
				const Integer& v_67 = std::get<1>(t);
				const Varchar<25>& v_68 = std::get<2>(t);
				const Numeric& v_69 = std::get<3>(t);
				const Varchar<15>& v_70 = std::get<4>(t);
				const Varchar<25>& v_71 = std::get<5>(t);
				const Varchar<40>& v_72 = std::get<6>(t);
				const Varchar<117>& v_73 = std::get<7>(t);
				const Numeric& v_74 = std::get<8>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_67 << ", " << v_68 << ", " << v_69 << ", " << v_70 << ", " << v_71 << ", " << v_72 << ", " << v_73 << ", " << v_74 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_14_changed.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "p_type" << ", " << "2" << std::endl;
		}
		{
			std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Numeric, Numeric>> v_75(1024 * 1024);
			db->lineitem_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_76 = key.l_partkey;
				const Numeric& v_77 = value.l_extendedprice;
				const Numeric& v_78 = value.l_discount;
				const Timestamp& v_26 = value.l_shipdate;
				db->part_tpch.lookup1({v_76}, [&](auto& value) {
					Varchar<25> v_79 = value.p_type;
					if ((v_26 >= (2449962)) && (v_26 < (2449992))) {
						auto it = v_75.find({v_79});
						if (it == v_75.end()) {
							v_75.insert({{v_79}, {v_77 * (1 - v_78), v_77 * (1 - v_78)}});
						} else {
							std::get<0>(it->second) += v_77 * (1 - v_78);
							std::get<1>(it->second) += v_77 * (1 - v_78);
						}
					}
				});
			});
			for (auto& it : v_75) {
				const Varchar<25>& v_80 = std::get<0>(it.first);
				const Numeric& v_81 = std::get<0>(it.second);
				const Numeric& v_82 = std::get<1>(it.second);
				Numeric v_83 = (100.00 * v_81) / v_82;
				if (limit > 0) {
					limit -= 1;
					std::cout << v_80 << ", " << v_83 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_3.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << [&]() {
				Integer v_84 = 0;
				{
					std::vector<std::tuple<Numeric, Timestamp>> v_85;
					v_85.reserve(1024 * 1024);
					{
						std::unordered_map<std::tuple<Integer, Timestamp, Integer>, std::tuple<Numeric>> v_86(1024 * 1024);
						{
							std::unordered_multimap<std::tuple<Integer>, std::tuple<Timestamp, Integer>> v_87(1024 * 1024);
							{
								std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_88(1024 * 1024);
								db->customer_tpch.forEach([&](auto& key, auto& value) {
									const Integer& v_89 = key.c_custkey;
									const Varchar<10>& v_90 = value.c_mktsegment;
									if (v_90 == Varchar<8>("BUILDING")) {
										v_88.insert({{v_89}, {}});
									}
								});
								db->orders_tpch.forEach([&](auto& key, auto& value) {
									const Integer& v_10 = key.o_orderkey;
									const Integer& v_91 = key.o_custkey;
									const Timestamp& v_36 = value.o_orderdate;
									const Integer& v_47 = value.o_shippriority;
									if (v_36 < (2449792)) {
										for (auto range = v_88.equal_range({v_91}); range.first!=range.second; range.first++) {
											v_87.insert({{v_10}, {v_36, v_47}});
										}
									}
								});
							}
							db->lineitem_tpch.forEach([&](auto& key, auto& value) {
								const Integer& v_15 = key.l_orderkey;
								const Numeric& v_92 = value.l_extendedprice;
								const Numeric& v_93 = value.l_discount;
								const Timestamp& v_94 = value.l_shipdate;
								if (v_94 > (2449792)) {
									for (auto range = v_87.equal_range({v_15}); range.first!=range.second; range.first++) {
										const Timestamp& v_36 = std::get<0>(range.first->second);
										const Integer& v_47 = std::get<1>(range.first->second);
										auto it = v_86.find({v_15, v_36, v_47});
										if (it == v_86.end()) {
											v_86.insert({{v_15, v_36, v_47}, {v_92 * (1 - v_93)}});
										} else {
											std::get<0>(it->second) += v_92 * (1 - v_93);
										}
									}
								}
							});
						}
						for (auto& it : v_86) {
							const Timestamp& v_95 = std::get<1>(it.first);
							const Numeric& v_20 = std::get<0>(it.second);
							v_85.push_back({v_20, v_95});
						}
					}
					std::sort(v_85.begin(), v_85.end(), [](const auto& t1, const auto& t2) {
						if (get<0>(t1) < get<0>(t2)) return true;
						if (get<0>(t2) < get<0>(t1)) return false;
						if (get<1>(t1) < get<1>(t2)) return true;
						if (get<1>(t2) < get<1>(t1)) return false;
						return false;
					});
					for (auto& t : v_85) {
						v_84 += 1;
					}
				}
				return v_84;
			}() << std::endl;
		}
	}},
	{"./query/benchmark/tpch_4_changed.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "o_orderpriority" << ", " << "order_count" << std::endl;
		}
		{
			std::vector<std::tuple<Varchar<15>, Varchar<15>, Integer>> v_38;
			v_38.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Varchar<15>>, std::tuple<Integer>> v_39(1024 * 1024);
				{
					std::unordered_multimap<std::tuple<Integer>, std::tuple<Varchar<15>>> v_96(1024 * 1024);
					db->orders_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_97 = key.o_orderkey;
						const Timestamp& v_98 = value.o_orderdate;
						const Varchar<15>& v_99 = value.o_orderpriority;
						if ((v_98 >= (2449170)) && (v_98 < (2449262))) {
							v_96.insert({{v_97}, {v_99}});
						}
					});
					db->lineitem_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_100 = key.l_orderkey;
						const Timestamp& v_101 = value.l_commitdate;
						const Timestamp& v_102 = value.l_receiptdate;
						if (v_101 < v_102) {
							for (auto range = v_96.equal_range({v_100}); range.first!=range.second; range.first++) {
								const Varchar<15>& v_99 = std::get<0>(range.first->second);
								auto it = v_39.find({v_99});
								if (it == v_39.end()) {
									v_39.insert({{v_99}, {1}});
								} else {
									std::get<0>(it->second) += 1;
								}
							}
						}
					});
				}
				for (auto& it : v_39) {
					const Varchar<15>& v_103 = std::get<0>(it.first);
					const Integer& v_104 = std::get<0>(it.second);
					v_38.push_back({v_103, v_103, v_104});
				}
			}
			std::sort(v_38.begin(), v_38.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				return false;
			});
			for (auto& t : v_38) {
				const Varchar<15>& v_103 = std::get<1>(t);
				const Integer& v_104 = std::get<2>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_103 << ", " << v_104 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_5.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "n_name" << ", " << "revenue" << std::endl;
		}
		{
			std::vector<std::tuple<Numeric, Varchar<25>, Numeric>> v_38;
			v_38.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Numeric>> v_39(1024 * 1024);
				{
					std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric, Varchar<25>>> v_96(1024 * 1024);
					{
						std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_105(1024 * 1024);
						db->orders_tpch.forEach([&](auto& key, auto& value) {
							const Integer& v_79 = key.o_orderkey;
							const Integer& v_26 = key.o_custkey;
							const Timestamp& v_9 = value.o_orderdate;
							if ((v_9 >= (2449354)) && (v_9 < (2449719))) {
								db->customer_tpch.lookup1({v_26}, [&](auto& value) {
									v_105.insert({{v_79}, {}});
								});
							}
						});
						db->lineitem_tpch.forEach([&](auto& key, auto& value) {
							const Integer& v_106 = key.l_orderkey;
							const Integer& v_107 = key.l_suppkey;
							const Numeric& v_11 = value.l_extendedprice;
							const Numeric& v_13 = value.l_discount;
							for (auto range = v_105.equal_range({v_106}); range.first!=range.second; range.first++) {
								db->supplier_tpch.lookup1({v_107}, [&](auto& value) {
									Integer v_108 = value.s_nationkey;
									db->nation_tpch.lookup1({v_108}, [&](auto& value) {
										Varchar<25> v_109 = value.n_name;
										Integer v_110 = value.n_regionkey;
										v_96.insert({{v_110}, {v_11, v_13, v_109}});
									});
								});
							}
						});
					}
					db->region_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_111 = key.r_regionkey;
						const Varchar<25>& v_112 = value.r_name;
						if (v_112 == Varchar<4>("ASIA")) {
							for (auto range = v_96.equal_range({v_111}); range.first!=range.second; range.first++) {
								const Numeric& v_11 = std::get<0>(range.first->second);
								const Numeric& v_13 = std::get<1>(range.first->second);
								const Varchar<25>& v_109 = std::get<2>(range.first->second);
								auto it = v_39.find({v_109});
								if (it == v_39.end()) {
									v_39.insert({{v_109}, {v_11 * (1 - v_13)}});
								} else {
									std::get<0>(it->second) += v_11 * (1 - v_13);
								}
							}
						}
					});
				}
				for (auto& it : v_39) {
					const Varchar<25>& v_113 = std::get<0>(it.first);
					const Numeric& v_114 = std::get<0>(it.second);
					v_38.push_back({v_114, v_113, v_114});
				}
			}
			std::sort(v_38.begin(), v_38.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				return false;
			});
			for (auto& t : v_38) {
				const Varchar<25>& v_113 = std::get<1>(t);
				const Numeric& v_114 = std::get<2>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_113 << ", " << v_114 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_5_opt.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "n_name" << ", " << "revenue" << std::endl;
		}
		{
			std::vector<std::tuple<Numeric, Varchar<25>, Numeric>> v_38;
			v_38.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Numeric>> v_39(1024 * 1024);
				{
					std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_96(1024 * 1024);
					db->region_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_115 = key.r_regionkey;
						const Varchar<25>& v_116 = value.r_name;
						if (v_116 == Varchar<4>("ASIA")) {
							v_96.insert({{v_115}, {}});
						}
					});
					{
						std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_105(1024 * 1024);
						db->orders_tpch.forEach([&](auto& key, auto& value) {
							const Integer& v_117 = key.o_orderkey;
							const Integer& v_118 = key.o_custkey;
							const Timestamp& v_119 = value.o_orderdate;
							if ((v_119 >= (2449354)) && (v_119 < (2449719))) {
								db->customer_tpch.lookup1({v_118}, [&](auto& value) {
									v_105.insert({{v_117}, {}});
								});
							}
						});
						db->lineitem_tpch.forEach([&](auto& key, auto& value) {
							const Integer& v_120 = key.l_orderkey;
							const Integer& v_121 = key.l_suppkey;
							const Numeric& v_122 = value.l_extendedprice;
							const Numeric& v_123 = value.l_discount;
							for (auto range = v_105.equal_range({v_120}); range.first!=range.second; range.first++) {
								db->supplier_tpch.lookup1({v_121}, [&](auto& value) {
									Integer v_9 = value.s_nationkey;
									db->nation_tpch.lookup1({v_9}, [&](auto& value) {
										Varchar<25> v_124 = value.n_name;
										Integer v_57 = value.n_regionkey;
										for (auto range = v_96.equal_range({v_57}); range.first!=range.second; range.first++) {
											auto it = v_39.find({v_124});
											if (it == v_39.end()) {
												v_39.insert({{v_124}, {v_122 * (1 - v_123)}});
											} else {
												std::get<0>(it->second) += v_122 * (1 - v_123);
											}
										}
									});
								});
							}
						});
					}
				}
				for (auto& it : v_39) {
					const Varchar<25>& v_125 = std::get<0>(it.first);
					const Numeric& v_126 = std::get<0>(it.second);
					v_38.push_back({v_126, v_125, v_126});
				}
			}
			std::sort(v_38.begin(), v_38.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				return false;
			});
			for (auto& t : v_38) {
				const Varchar<25>& v_125 = std::get<1>(t);
				const Numeric& v_126 = std::get<2>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_125 << ", " << v_126 << std::endl;
				}
			}
		}
	}},
}},
	{"all", {
	{"./query/benchmark/handwritten.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "s_w_id" << ", " << "s_i_id" << ", " << "s_quantity" << ", " << "s_dist_01" << ", " << "s_dist_02" << ", " << "s_dist_03" << ", " << "s_dist_04" << ", " << "s_dist_05" << ", " << "s_dist_06" << ", " << "s_dist_07" << ", " << "s_dist_08" << ", " << "s_dist_09" << ", " << "s_dist_10" << ", " << "s_ytd" << ", " << "s_order_cnt" << ", " << "s_remote_cnt" << ", " << "s_data" << ", " << "ol_w_id" << ", " << "ol_d_id" << ", " << "ol_o_id" << ", " << "ol_number" << ", " << "ol_i_id" << ", " << "ol_supply_w_id" << ", " << "ol_delivery_d" << ", " << "ol_quantity" << ", " << "ol_amount" << ", " << "ol_dist_info" << std::endl;
		}
		{
			std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Numeric, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Varchar<24>, Numeric, Numeric, Numeric, Varchar<50>>> v_1(1024 * 1024);
			db->stock.forEach([&](auto& key, auto& value) {
				const Integer& v_2 = key.s_w_id;
				const Integer& v_3 = key.s_i_id;
				const Numeric& v_4 = value.s_quantity;
				const Varchar<24>& v_5 = value.s_dist_01;
				const Varchar<24>& v_6 = value.s_dist_02;
				const Varchar<24>& v_7 = value.s_dist_03;
				const Varchar<24>& v_8 = value.s_dist_04;
				const Varchar<24>& v_9 = value.s_dist_05;
				const Varchar<24>& v_10 = value.s_dist_06;
				const Varchar<24>& v_11 = value.s_dist_07;
				const Varchar<24>& v_12 = value.s_dist_08;
				const Varchar<24>& v_13 = value.s_dist_09;
				const Varchar<24>& v_14 = value.s_dist_10;
				const Numeric& v_15 = value.s_ytd;
				const Numeric& v_16 = value.s_order_cnt;
				const Numeric& v_17 = value.s_remote_cnt;
				const Varchar<50>& v_18 = value.s_data;
				if ((v_4 < 20) && (v_2 == 2)) {
					v_1.insert({{v_3}, {v_2, v_4, v_5, v_6, v_7, v_8, v_9, v_10, v_11, v_12, v_13, v_14, v_15, v_16, v_17, v_18}});
				}
			});
			db->orderline.forEach([&](auto& key, auto& value) {
				const Integer& v_19 = key.ol_w_id;
				const Integer& v_20 = key.ol_d_id;
				const Integer& v_21 = key.ol_o_id;
				const Integer& v_22 = key.ol_number;
				const Integer& v_23 = value.ol_i_id;
				const Integer& v_24 = value.ol_supply_w_id;
				const Timestamp& v_25 = value.ol_delivery_d;
				const Numeric& v_26 = value.ol_quantity;
				const Numeric& v_27 = value.ol_amount;
				const Varchar<24>& v_28 = value.ol_dist_info;
				if ((((v_21 < 3) && (v_21 >= (3 - 20))) && (v_19 == 1)) && (v_20 == 2)) {
					for (auto range = v_1.equal_range({v_23}); range.first!=range.second; range.first++) {
						const Integer& v_3 = std::get<0>(range.first->first);
						const Integer& v_2 = std::get<0>(range.first->second);
						const Numeric& v_4 = std::get<1>(range.first->second);
						const Varchar<24>& v_5 = std::get<2>(range.first->second);
						const Varchar<24>& v_6 = std::get<3>(range.first->second);
						const Varchar<24>& v_7 = std::get<4>(range.first->second);
						const Varchar<24>& v_8 = std::get<5>(range.first->second);
						const Varchar<24>& v_9 = std::get<6>(range.first->second);
						const Varchar<24>& v_10 = std::get<7>(range.first->second);
						const Varchar<24>& v_11 = std::get<8>(range.first->second);
						const Varchar<24>& v_12 = std::get<9>(range.first->second);
						const Varchar<24>& v_13 = std::get<10>(range.first->second);
						const Varchar<24>& v_14 = std::get<11>(range.first->second);
						const Numeric& v_15 = std::get<12>(range.first->second);
						const Numeric& v_16 = std::get<13>(range.first->second);
						const Numeric& v_17 = std::get<14>(range.first->second);
						const Varchar<50>& v_18 = std::get<15>(range.first->second);
						if (limit > 0) {
							limit -= 1;
							std::cout << v_2 << ", " << v_3 << ", " << v_4 << ", " << v_5 << ", " << v_6 << ", " << v_7 << ", " << v_8 << ", " << v_9 << ", " << v_10 << ", " << v_11 << ", " << v_12 << ", " << v_13 << ", " << v_14 << ", " << v_15 << ", " << v_16 << ", " << v_17 << ", " << v_18 << ", " << v_19 << ", " << v_20 << ", " << v_21 << ", " << v_22 << ", " << v_23 << ", " << v_24 << ", " << v_25 << ", " << v_26 << ", " << v_27 << ", " << v_28 << std::endl;
						}
					}
				}
			});
		}
	}},
	{"./query/benchmark/index_scan_query.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "s_suppkey" << ", " << "s_name" << ", " << "s_address" << ", " << "s_nationkey" << ", " << "s_phone" << ", " << "s_acctbal" << ", " << "s_comment" << ", " << "c_custkey" << ", " << "c_name" << ", " << "c_address" << ", " << "c_nationkey" << ", " << "c_phone" << ", " << "c_acctbal" << ", " << "c_mktsegment" << ", " << "c_comment" << std::endl;
		}
		{
			std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Varchar<15>, Numeric, Varchar<101>>> v_1(1024 * 1024);
			db->supplier_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_29 = key.s_suppkey;
				const Varchar<25>& v_30 = value.s_name;
				const Varchar<40>& v_31 = value.s_address;
				const Integer& v_32 = value.s_nationkey;
				const Varchar<15>& v_33 = value.s_phone;
				const Numeric& v_34 = value.s_acctbal;
				const Varchar<101>& v_35 = value.s_comment;
				v_1.insert({{v_32}, {v_29, v_30, v_31, v_33, v_34, v_35}});
			});
			db->customer_tpch.lookup1({1}, [&](auto& value) {
				Integer v_14 = 1;
				Varchar<25> v_25 = value.c_name;
				Varchar<40> v_27 = value.c_address;
				Integer v_28 = value.c_nationkey;
				Varchar<15> v_9 = value.c_phone;
				Numeric v_10 = value.c_acctbal;
				Varchar<10> v_13 = value.c_mktsegment;
				Varchar<117> v_24 = value.c_comment;
				for (auto range = v_1.equal_range({v_28}); range.first!=range.second; range.first++) {
					const Integer& v_32 = std::get<0>(range.first->first);
					const Integer& v_29 = std::get<0>(range.first->second);
					const Varchar<25>& v_30 = std::get<1>(range.first->second);
					const Varchar<40>& v_31 = std::get<2>(range.first->second);
					const Varchar<15>& v_33 = std::get<3>(range.first->second);
					const Numeric& v_34 = std::get<4>(range.first->second);
					const Varchar<101>& v_35 = std::get<5>(range.first->second);
					if (limit > 0) {
						limit -= 1;
						std::cout << v_29 << ", " << v_30 << ", " << v_31 << ", " << v_32 << ", " << v_33 << ", " << v_34 << ", " << v_35 << ", " << v_14 << ", " << v_25 << ", " << v_27 << ", " << v_28 << ", " << v_9 << ", " << v_10 << ", " << v_13 << ", " << v_24 << std::endl;
					}
				}
			});
		}
	}},
	{"./query/benchmark/tpch_1.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "l_returnflag" << ", " << "l_linestatus" << ", " << "sum_qty" << ", " << "sum_base_price" << ", " << "sum_disc_price" << ", " << "sum_charge" << ", " << "avg_qty" << ", " << "avg_price" << ", " << "avg_disc" << ", " << "count_order" << std::endl;
		}
		{
			std::vector<std::tuple<Varchar<1>, Varchar<1>, Varchar<1>, Varchar<1>, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Numeric, Integer>> v_36;
			v_36.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Varchar<1>, Varchar<1>>, std::tuple<Numeric, Numeric, Numeric, Numeric, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, std::pair<Numeric, Integer>, Integer>> v_37(1024 * 1024);
				db->lineitem_tpch.forEach([&](auto& key, auto& value) {
					const Numeric& v_38 = value.l_quantity;
					const Numeric& v_39 = value.l_extendedprice;
					const Numeric& v_40 = value.l_discount;
					const Numeric& v_34 = value.l_tax;
					const Varchar<1>& v_28 = value.l_returnflag;
					const Varchar<1>& v_9 = value.l_linestatus;
					const Timestamp& v_10 = value.l_shipdate;
					if (v_10 <= (2451058)) {
						auto it = v_37.find({v_28, v_9});
						if (it == v_37.end()) {
							v_37.insert({{v_28, v_9}, {v_38, v_39, v_39 * (1 - v_40), (v_39 * (1 - v_40)) * (1 + v_34), {v_38, 1}, {v_39, 1}, {v_40, 1}, 1}});
						} else {
							std::get<0>(it->second) += v_38;
							std::get<1>(it->second) += v_39;
							std::get<2>(it->second) += v_39 * (1 - v_40);
							std::get<3>(it->second) += (v_39 * (1 - v_40)) * (1 + v_34);
							std::get<4>(it->second) = {std::get<4>(it->second).first + v_38, std::get<4>(it->second).second + 1};
							std::get<5>(it->second) = {std::get<5>(it->second).first + v_39, std::get<5>(it->second).second + 1};
							std::get<6>(it->second) = {std::get<6>(it->second).first + v_40, std::get<6>(it->second).second + 1};
							std::get<7>(it->second) += 1;
						}
					}
				});
				for (auto& it : v_37) {
					const Varchar<1>& v_25 = std::get<0>(it.first);
					const Varchar<1>& v_41 = std::get<1>(it.first);
					const Numeric& v_42 = std::get<0>(it.second);
					const Numeric& v_43 = std::get<1>(it.second);
					const Numeric& v_44 = std::get<2>(it.second);
					const Numeric& v_45 = std::get<3>(it.second);
					const Numeric v_46 = std::get<4>(it.second).first / (double)std::get<4>(it.second).second;
					const Numeric v_47 = std::get<5>(it.second).first / (double)std::get<5>(it.second).second;
					const Numeric v_48 = std::get<6>(it.second).first / (double)std::get<6>(it.second).second;
					const Integer& v_49 = std::get<7>(it.second);
					v_36.push_back({v_25, v_41, v_25, v_41, v_42, v_43, v_44, v_45, v_46, v_47, v_48, v_49});
				}
			}
			std::sort(v_36.begin(), v_36.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				if (get<1>(t1) < get<1>(t2)) return true;
				if (get<1>(t2) < get<1>(t1)) return false;
				return false;
			});
			for (auto& t : v_36) {
				const Varchar<1>& v_25 = std::get<2>(t);
				const Varchar<1>& v_41 = std::get<3>(t);
				const Numeric& v_42 = std::get<4>(t);
				const Numeric& v_43 = std::get<5>(t);
				const Numeric& v_44 = std::get<6>(t);
				const Numeric& v_45 = std::get<7>(t);
				const Numeric& v_46 = std::get<8>(t);
				const Numeric& v_47 = std::get<9>(t);
				const Numeric& v_48 = std::get<10>(t);
				const Integer& v_49 = std::get<11>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_25 << ", " << v_41 << ", " << v_42 << ", " << v_43 << ", " << v_44 << ", " << v_45 << ", " << v_46 << ", " << v_47 << ", " << v_48 << ", " << v_49 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_10.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "c_custkey" << ", " << "c_name" << ", " << "c_acctbal" << ", " << "c_phone" << ", " << "n_name" << ", " << "c_address" << ", " << "c_comment" << ", " << "revenue" << std::endl;
		}
		{
			std::vector<std::tuple<Numeric, Integer, Varchar<25>, Numeric, Varchar<15>, Varchar<25>, Varchar<40>, Varchar<117>, Numeric>> v_36;
			v_36.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Integer, Varchar<25>, Numeric, Varchar<15>, Varchar<25>, Varchar<40>, Varchar<117>>, std::tuple<Numeric>> v_37(1024 * 1024);
				{
					std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<117>>> v_50(1024 * 1024);
					db->orders_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_51 = key.o_orderkey;
						const Integer& v_52 = key.o_custkey;
						const Timestamp& v_53 = value.o_orderdate;
						if ((v_53 >= (2449262)) && (v_53 < (2449354))) {
							db->customer_tpch.lookup1({v_52}, [&](auto& value) {
								Integer v_14 = v_52;
								Varchar<25> v_54 = value.c_name;
								Varchar<40> v_55 = value.c_address;
								Integer v_56 = value.c_nationkey;
								Varchar<15> v_20 = value.c_phone;
								Numeric v_26 = value.c_acctbal;
								Varchar<117> v_38 = value.c_comment;
								v_50.insert({{v_51}, {v_14, v_54, v_55, v_56, v_20, v_26, v_38}});
							});
						}
					});
					db->lineitem_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_45 = key.l_orderkey;
						const Numeric& v_57 = value.l_extendedprice;
						const Numeric& v_58 = value.l_discount;
						const Varchar<1>& v_59 = value.l_returnflag;
						if (v_59 == Varchar<1>("R")) {
							for (auto range = v_50.equal_range({v_45}); range.first!=range.second; range.first++) {
								const Integer& v_14 = std::get<0>(range.first->second);
								const Varchar<25>& v_54 = std::get<1>(range.first->second);
								const Varchar<40>& v_55 = std::get<2>(range.first->second);
								const Integer& v_56 = std::get<3>(range.first->second);
								const Varchar<15>& v_20 = std::get<4>(range.first->second);
								const Numeric& v_26 = std::get<5>(range.first->second);
								const Varchar<117>& v_38 = std::get<6>(range.first->second);
								db->nation_tpch.lookup1({v_56}, [&](auto& value) {
									Varchar<25> v_60 = value.n_name;
									auto it = v_37.find({v_14, v_54, v_26, v_20, v_60, v_55, v_38});
									if (it == v_37.end()) {
										v_37.insert({{v_14, v_54, v_26, v_20, v_60, v_55, v_38}, {v_57 * (1 - v_58)}});
									} else {
										std::get<0>(it->second) += v_57 * (1 - v_58);
									}
								});
							}
						}
					});
				}
				for (auto& it : v_37) {
					const Integer& v_19 = std::get<0>(it.first);
					const Varchar<25>& v_61 = std::get<1>(it.first);
					const Numeric& v_21 = std::get<2>(it.first);
					const Varchar<15>& v_47 = std::get<3>(it.first);
					const Varchar<25>& v_62 = std::get<4>(it.first);
					const Varchar<40>& v_63 = std::get<5>(it.first);
					const Varchar<117>& v_64 = std::get<6>(it.first);
					const Numeric& v_65 = std::get<0>(it.second);
					v_36.push_back({v_65, v_19, v_61, v_21, v_47, v_62, v_63, v_64, v_65});
				}
			}
			std::sort(v_36.begin(), v_36.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				return false;
			});
			for (auto& t : v_36) {
				const Integer& v_19 = std::get<1>(t);
				const Varchar<25>& v_61 = std::get<2>(t);
				const Numeric& v_21 = std::get<3>(t);
				const Varchar<15>& v_47 = std::get<4>(t);
				const Varchar<25>& v_62 = std::get<5>(t);
				const Varchar<40>& v_63 = std::get<6>(t);
				const Varchar<117>& v_64 = std::get<7>(t);
				const Numeric& v_65 = std::get<8>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_19 << ", " << v_61 << ", " << v_21 << ", " << v_47 << ", " << v_62 << ", " << v_63 << ", " << v_64 << ", " << v_65 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_14_changed.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "p_type" << ", " << "2" << std::endl;
		}
		{
			std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Numeric, Numeric>> v_66(1024 * 1024);
			db->lineitem_tpch.forEach([&](auto& key, auto& value) {
				const Integer& v_67 = key.l_partkey;
				const Numeric& v_68 = value.l_extendedprice;
				const Numeric& v_69 = value.l_discount;
				const Timestamp& v_10 = value.l_shipdate;
				if ((v_10 >= (2449962)) && (v_10 < (2449992))) {
					db->part_tpch.lookup1({v_67}, [&](auto& value) {
						Varchar<25> v_20 = value.p_type;
						auto it = v_66.find({v_20});
						if (it == v_66.end()) {
							v_66.insert({{v_20}, {v_68 * (1 - v_69), v_68 * (1 - v_69)}});
						} else {
							std::get<0>(it->second) += v_68 * (1 - v_69);
							std::get<1>(it->second) += v_68 * (1 - v_69);
						}
					});
				}
			});
			for (auto& it : v_66) {
				const Varchar<25>& v_2 = std::get<0>(it.first);
				const Numeric& v_70 = std::get<0>(it.second);
				const Numeric& v_71 = std::get<1>(it.second);
				Numeric v_72 = (100.00 * v_70) / v_71;
				if (limit > 0) {
					limit -= 1;
					std::cout << v_2 << ", " << v_72 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_3.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << [&]() {
				Integer v_45 = 0;
				{
					std::vector<std::tuple<Numeric, Timestamp>> v_73;
					v_73.reserve(1024 * 1024);
					{
						std::unordered_map<std::tuple<Integer, Timestamp, Integer>, std::tuple<Numeric>> v_74(1024 * 1024);
						{
							std::unordered_multimap<std::tuple<Integer>, std::tuple<Timestamp, Integer>> v_75(1024 * 1024);
							{
								std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_76(1024 * 1024);
								db->customer_tpch.forEach([&](auto& key, auto& value) {
									const Integer& v_77 = key.c_custkey;
									const Varchar<10>& v_78 = value.c_mktsegment;
									if (v_78 == Varchar<8>("BUILDING")) {
										v_76.insert({{v_77}, {}});
									}
								});
								db->orders_tpch.forEach([&](auto& key, auto& value) {
									const Integer& v_79 = key.o_orderkey;
									const Integer& v_13 = key.o_custkey;
									const Timestamp& v_80 = value.o_orderdate;
									const Integer& v_56 = value.o_shippriority;
									if (v_80 < (2449792)) {
										for (auto range = v_76.equal_range({v_13}); range.first!=range.second; range.first++) {
											v_75.insert({{v_79}, {v_80, v_56}});
										}
									}
								});
							}
							db->lineitem_tpch.forEach([&](auto& key, auto& value) {
								const Integer& v_35 = key.l_orderkey;
								const Numeric& v_81 = value.l_extendedprice;
								const Numeric& v_82 = value.l_discount;
								const Timestamp& v_83 = value.l_shipdate;
								if (v_83 > (2449792)) {
									for (auto range = v_75.equal_range({v_35}); range.first!=range.second; range.first++) {
										const Timestamp& v_80 = std::get<0>(range.first->second);
										const Integer& v_56 = std::get<1>(range.first->second);
										auto it = v_74.find({v_35, v_80, v_56});
										if (it == v_74.end()) {
											v_74.insert({{v_35, v_80, v_56}, {v_81 * (1 - v_82)}});
										} else {
											std::get<0>(it->second) += v_81 * (1 - v_82);
										}
									}
								}
							});
						}
						for (auto& it : v_74) {
							const Timestamp& v_84 = std::get<1>(it.first);
							const Numeric& v_85 = std::get<0>(it.second);
							v_73.push_back({v_85, v_84});
						}
					}
					std::sort(v_73.begin(), v_73.end(), [](const auto& t1, const auto& t2) {
						if (get<0>(t1) < get<0>(t2)) return true;
						if (get<0>(t2) < get<0>(t1)) return false;
						if (get<1>(t1) < get<1>(t2)) return true;
						if (get<1>(t2) < get<1>(t1)) return false;
						return false;
					});
					for (auto& t : v_73) {
						v_45 += 1;
					}
				}
				return v_45;
			}() << std::endl;
		}
	}},
	{"./query/benchmark/tpch_4_changed.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "o_orderpriority" << ", " << "order_count" << std::endl;
		}
		{
			std::vector<std::tuple<Varchar<15>, Varchar<15>, Integer>> v_36;
			v_36.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Varchar<15>>, std::tuple<Integer>> v_37(1024 * 1024);
				{
					std::unordered_multimap<std::tuple<Integer>, std::tuple<Varchar<15>>> v_86(1024 * 1024);
					db->orders_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_87 = key.o_orderkey;
						const Timestamp& v_88 = value.o_orderdate;
						const Varchar<15>& v_89 = value.o_orderpriority;
						if ((v_88 >= (2449170)) && (v_88 < (2449262))) {
							v_86.insert({{v_87}, {v_89}});
						}
					});
					db->lineitem_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_14 = key.l_orderkey;
						const Timestamp& v_35 = value.l_commitdate;
						const Timestamp& v_90 = value.l_receiptdate;
						if (v_35 < v_90) {
							for (auto range = v_86.equal_range({v_14}); range.first!=range.second; range.first++) {
								const Varchar<15>& v_89 = std::get<0>(range.first->second);
								auto it = v_37.find({v_89});
								if (it == v_37.end()) {
									v_37.insert({{v_89}, {1}});
								} else {
									std::get<0>(it->second) += 1;
								}
							}
						}
					});
				}
				for (auto& it : v_37) {
					const Varchar<15>& v_91 = std::get<0>(it.first);
					const Integer& v_92 = std::get<0>(it.second);
					v_36.push_back({v_91, v_91, v_92});
				}
			}
			std::sort(v_36.begin(), v_36.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				return false;
			});
			for (auto& t : v_36) {
				const Varchar<15>& v_91 = std::get<1>(t);
				const Integer& v_92 = std::get<2>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_91 << ", " << v_92 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_5.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "n_name" << ", " << "revenue" << std::endl;
		}
		{
			std::vector<std::tuple<Numeric, Varchar<25>, Numeric>> v_36;
			v_36.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Numeric>> v_37(1024 * 1024);
				{
					std::unordered_multimap<std::tuple<Integer>, std::tuple<Numeric, Numeric, Varchar<25>>> v_86(1024 * 1024);
					{
						std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_93(1024 * 1024);
						db->orders_tpch.forEach([&](auto& key, auto& value) {
							const Integer& v_2 = key.o_orderkey;
							const Integer& v_24 = key.o_custkey;
							const Timestamp& v_56 = value.o_orderdate;
							if ((v_56 >= (2449354)) && (v_56 < (2449719))) {
								db->customer_tpch.lookup1({v_24}, [&](auto& value) {
									v_93.insert({{v_2}, {}});
								});
							}
						});
						db->lineitem_tpch.forEach([&](auto& key, auto& value) {
							const Integer& v_90 = key.l_orderkey;
							const Integer& v_94 = key.l_suppkey;
							const Numeric& v_95 = value.l_extendedprice;
							const Numeric& v_12 = value.l_discount;
							for (auto range = v_93.equal_range({v_90}); range.first!=range.second; range.first++) {
								db->supplier_tpch.lookup1({v_94}, [&](auto& value) {
									Integer v_96 = value.s_nationkey;
									db->nation_tpch.lookup1({v_96}, [&](auto& value) {
										Varchar<25> v_97 = value.n_name;
										Integer v_98 = value.n_regionkey;
										v_86.insert({{v_98}, {v_95, v_12, v_97}});
									});
								});
							}
						});
					}
					db->region_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_99 = key.r_regionkey;
						const Varchar<25>& v_100 = value.r_name;
						if (v_100 == Varchar<4>("ASIA")) {
							for (auto range = v_86.equal_range({v_99}); range.first!=range.second; range.first++) {
								const Numeric& v_95 = std::get<0>(range.first->second);
								const Numeric& v_12 = std::get<1>(range.first->second);
								const Varchar<25>& v_97 = std::get<2>(range.first->second);
								auto it = v_37.find({v_97});
								if (it == v_37.end()) {
									v_37.insert({{v_97}, {v_95 * (1 - v_12)}});
								} else {
									std::get<0>(it->second) += v_95 * (1 - v_12);
								}
							}
						}
					});
				}
				for (auto& it : v_37) {
					const Varchar<25>& v_101 = std::get<0>(it.first);
					const Numeric& v_102 = std::get<0>(it.second);
					v_36.push_back({v_102, v_101, v_102});
				}
			}
			std::sort(v_36.begin(), v_36.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				return false;
			});
			for (auto& t : v_36) {
				const Varchar<25>& v_101 = std::get<1>(t);
				const Numeric& v_102 = std::get<2>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_101 << ", " << v_102 << std::endl;
				}
			}
		}
	}},
	{"./query/benchmark/tpch_5_opt.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "n_name" << ", " << "revenue" << std::endl;
		}
		{
			std::vector<std::tuple<Numeric, Varchar<25>, Numeric>> v_36;
			v_36.reserve(1024 * 1024);
			{
				std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Numeric>> v_37(1024 * 1024);
				{
					std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_86(1024 * 1024);
					db->region_tpch.forEach([&](auto& key, auto& value) {
						const Integer& v_103 = key.r_regionkey;
						const Varchar<25>& v_104 = value.r_name;
						if (v_104 == Varchar<4>("ASIA")) {
							v_86.insert({{v_103}, {}});
						}
					});
					{
						std::unordered_multimap<std::tuple<Integer>, std::tuple<>> v_93(1024 * 1024);
						db->orders_tpch.forEach([&](auto& key, auto& value) {
							const Integer& v_105 = key.o_orderkey;
							const Integer& v_106 = key.o_custkey;
							const Timestamp& v_107 = value.o_orderdate;
							if ((v_107 >= (2449354)) && (v_107 < (2449719))) {
								db->customer_tpch.lookup1({v_106}, [&](auto& value) {
									v_93.insert({{v_105}, {}});
								});
							}
						});
						db->lineitem_tpch.forEach([&](auto& key, auto& value) {
							const Integer& v_108 = key.l_orderkey;
							const Integer& v_109 = key.l_suppkey;
							const Numeric& v_110 = value.l_extendedprice;
							const Numeric& v_111 = value.l_discount;
							for (auto range = v_93.equal_range({v_108}); range.first!=range.second; range.first++) {
								db->supplier_tpch.lookup1({v_109}, [&](auto& value) {
									Integer v_55 = value.s_nationkey;
									db->nation_tpch.lookup1({v_55}, [&](auto& value) {
										Varchar<25> v_112 = value.n_name;
										Integer v_14 = value.n_regionkey;
										for (auto range = v_86.equal_range({v_14}); range.first!=range.second; range.first++) {
											auto it = v_37.find({v_112});
											if (it == v_37.end()) {
												v_37.insert({{v_112}, {v_110 * (1 - v_111)}});
											} else {
												std::get<0>(it->second) += v_110 * (1 - v_111);
											}
										}
									});
								});
							}
						});
					}
				}
				for (auto& it : v_37) {
					const Varchar<25>& v_113 = std::get<0>(it.first);
					const Numeric& v_114 = std::get<0>(it.second);
					v_36.push_back({v_114, v_113, v_114});
				}
			}
			std::sort(v_36.begin(), v_36.end(), [](const auto& t1, const auto& t2) {
				if (get<0>(t1) < get<0>(t2)) return true;
				if (get<0>(t2) < get<0>(t1)) return false;
				return false;
			});
			for (auto& t : v_36) {
				const Varchar<25>& v_113 = std::get<1>(t);
				const Numeric& v_114 = std::get<2>(t);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_113 << ", " << v_114 << std::endl;
				}
			}
		}
	}},
}},
};
