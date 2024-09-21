std::map<std::string, std::map<std::string, std::function<void(Database*, size_t)>>> queries = {
	{"none", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		std::vector<std::tuple<Numeric, Numeric, Varchar<25>>> v_1;
		std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Numeric>> v_2;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<152>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<101>, Integer, Integer, Integer, Integer, Numeric, Numeric, Numeric, Numeric, Varchar<1>, Varchar<1>, Timestamp, Timestamp, Timestamp, Varchar<25>, Varchar<10>, Varchar<44>, Integer, Integer, Varchar<1>, Numeric, Timestamp, Varchar<15>, Varchar<15>, Integer, Varchar<79>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<10>, Varchar<117>>> v_3;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Varchar<15>, Numeric, Varchar<101>, Integer, Integer, Integer, Integer, Numeric, Numeric, Numeric, Numeric, Varchar<1>, Varchar<1>, Timestamp, Timestamp, Timestamp, Varchar<25>, Varchar<10>, Varchar<44>, Integer, Integer, Varchar<1>, Numeric, Timestamp, Varchar<15>, Varchar<15>, Integer, Varchar<79>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<10>, Varchar<117>>> v_4;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Integer, Integer, Numeric, Numeric, Numeric, Numeric, Varchar<1>, Varchar<1>, Timestamp, Timestamp, Timestamp, Varchar<25>, Varchar<10>, Varchar<44>, Integer, Integer, Varchar<1>, Numeric, Timestamp, Varchar<15>, Varchar<15>, Integer, Varchar<79>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<10>, Varchar<117>>> v_5;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<1>, Numeric, Timestamp, Varchar<15>, Varchar<15>, Integer, Varchar<79>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<10>, Varchar<117>>> v_6;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<10>, Varchar<117>>> v_7;
		db->customer_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_8 = key.c_custkey;
			const Varchar<25>& v_9 = value.c_name;
			const Varchar<40>& v_10 = value.c_address;
			const Integer& v_11 = value.c_nationkey;
			const Varchar<15>& v_12 = value.c_phone;
			const Numeric& v_13 = value.c_acctbal;
			const Varchar<10>& v_14 = value.c_mktsegment;
			const Varchar<117>& v_15 = value.c_comment;
			v_7.insert({{v_8}, {v_9, v_10, v_11, v_12, v_13, v_14, v_15}});
		});
		db->orders_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_16 = key.o_orderkey;
			const Integer& v_17 = value.o_custkey;
			const Varchar<1>& v_18 = value.o_orderstatus;
			const Numeric& v_19 = value.o_totalprice;
			const Timestamp& v_20 = value.o_orderdate;
			const Varchar<15>& v_21 = value.o_orderpriority;
			const Varchar<15>& v_22 = value.o_clerk;
			const Integer& v_23 = value.o_shippriority;
			const Varchar<79>& v_24 = value.o_comment;
			if ((v_20 >= (2449354)) && (v_20 < (2449719))) {
				for (auto range = v_7.equal_range({v_17}); range.first!=range.second; range.first++) {
					const Integer& v_8 = std::get<0>(range.first->first);
					const Varchar<25>& v_9 = std::get<0>(range.first->second);
					const Varchar<40>& v_10 = std::get<1>(range.first->second);
					const Integer& v_11 = std::get<2>(range.first->second);
					const Varchar<15>& v_12 = std::get<3>(range.first->second);
					const Numeric& v_13 = std::get<4>(range.first->second);
					const Varchar<10>& v_14 = std::get<5>(range.first->second);
					const Varchar<117>& v_15 = std::get<6>(range.first->second);
					v_6.insert({{v_16}, {v_17, v_18, v_19, v_20, v_21, v_22, v_23, v_24, v_8, v_9, v_10, v_11, v_12, v_13, v_14, v_15}});
				}
			}
		});
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_25 = key.l_orderkey;
			const Integer& v_26 = value.l_partkey;
			const Integer& v_27 = value.l_suppkey;
			const Integer& v_28 = value.l_linenumber;
			const Numeric& v_29 = value.l_quantity;
			const Numeric& v_30 = value.l_extendedprice;
			const Numeric& v_31 = value.l_discount;
			const Numeric& v_32 = value.l_tax;
			const Varchar<1>& v_33 = value.l_returnflag;
			const Varchar<1>& v_34 = value.l_linestatus;
			const Timestamp& v_35 = value.l_shipdate;
			const Timestamp& v_36 = value.l_commitdate;
			const Timestamp& v_37 = value.l_receiptdate;
			const Varchar<25>& v_38 = value.l_shipinstruct;
			const Varchar<10>& v_39 = value.l_shipmode;
			const Varchar<44>& v_40 = value.l_comment;
			for (auto range = v_6.equal_range({v_25}); range.first!=range.second; range.first++) {
				const Integer& v_16 = std::get<0>(range.first->first);
				const Integer& v_17 = std::get<0>(range.first->second);
				const Varchar<1>& v_18 = std::get<1>(range.first->second);
				const Numeric& v_19 = std::get<2>(range.first->second);
				const Timestamp& v_20 = std::get<3>(range.first->second);
				const Varchar<15>& v_21 = std::get<4>(range.first->second);
				const Varchar<15>& v_22 = std::get<5>(range.first->second);
				const Integer& v_23 = std::get<6>(range.first->second);
				const Varchar<79>& v_24 = std::get<7>(range.first->second);
				const Integer& v_8 = std::get<8>(range.first->second);
				const Varchar<25>& v_9 = std::get<9>(range.first->second);
				const Varchar<40>& v_10 = std::get<10>(range.first->second);
				const Integer& v_11 = std::get<11>(range.first->second);
				const Varchar<15>& v_12 = std::get<12>(range.first->second);
				const Numeric& v_13 = std::get<13>(range.first->second);
				const Varchar<10>& v_14 = std::get<14>(range.first->second);
				const Varchar<117>& v_15 = std::get<15>(range.first->second);
				v_5.insert({{v_27}, {v_25, v_26, v_28, v_29, v_30, v_31, v_32, v_33, v_34, v_35, v_36, v_37, v_38, v_39, v_40, v_16, v_17, v_18, v_19, v_20, v_21, v_22, v_23, v_24, v_8, v_9, v_10, v_11, v_12, v_13, v_14, v_15}});
			}
		});
		db->supplier_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_41 = key.s_suppkey;
			const Varchar<25>& v_42 = value.s_name;
			const Varchar<40>& v_43 = value.s_address;
			const Integer& v_44 = value.s_nationkey;
			const Varchar<15>& v_45 = value.s_phone;
			const Numeric& v_46 = value.s_acctbal;
			const Varchar<101>& v_47 = value.s_comment;
			for (auto range = v_5.equal_range({v_41}); range.first!=range.second; range.first++) {
				const Integer& v_27 = std::get<0>(range.first->first);
				const Integer& v_25 = std::get<0>(range.first->second);
				const Integer& v_26 = std::get<1>(range.first->second);
				const Integer& v_28 = std::get<2>(range.first->second);
				const Numeric& v_29 = std::get<3>(range.first->second);
				const Numeric& v_30 = std::get<4>(range.first->second);
				const Numeric& v_31 = std::get<5>(range.first->second);
				const Numeric& v_32 = std::get<6>(range.first->second);
				const Varchar<1>& v_33 = std::get<7>(range.first->second);
				const Varchar<1>& v_34 = std::get<8>(range.first->second);
				const Timestamp& v_35 = std::get<9>(range.first->second);
				const Timestamp& v_36 = std::get<10>(range.first->second);
				const Timestamp& v_37 = std::get<11>(range.first->second);
				const Varchar<25>& v_38 = std::get<12>(range.first->second);
				const Varchar<10>& v_39 = std::get<13>(range.first->second);
				const Varchar<44>& v_40 = std::get<14>(range.first->second);
				const Integer& v_16 = std::get<15>(range.first->second);
				const Integer& v_17 = std::get<16>(range.first->second);
				const Varchar<1>& v_18 = std::get<17>(range.first->second);
				const Numeric& v_19 = std::get<18>(range.first->second);
				const Timestamp& v_20 = std::get<19>(range.first->second);
				const Varchar<15>& v_21 = std::get<20>(range.first->second);
				const Varchar<15>& v_22 = std::get<21>(range.first->second);
				const Integer& v_23 = std::get<22>(range.first->second);
				const Varchar<79>& v_24 = std::get<23>(range.first->second);
				const Integer& v_8 = std::get<24>(range.first->second);
				const Varchar<25>& v_9 = std::get<25>(range.first->second);
				const Varchar<40>& v_10 = std::get<26>(range.first->second);
				const Integer& v_11 = std::get<27>(range.first->second);
				const Varchar<15>& v_12 = std::get<28>(range.first->second);
				const Numeric& v_13 = std::get<29>(range.first->second);
				const Varchar<10>& v_14 = std::get<30>(range.first->second);
				const Varchar<117>& v_15 = std::get<31>(range.first->second);
				v_4.insert({{v_44}, {v_41, v_42, v_43, v_45, v_46, v_47, v_25, v_26, v_27, v_28, v_29, v_30, v_31, v_32, v_33, v_34, v_35, v_36, v_37, v_38, v_39, v_40, v_16, v_17, v_18, v_19, v_20, v_21, v_22, v_23, v_24, v_8, v_9, v_10, v_11, v_12, v_13, v_14, v_15}});
			}
		});
		db->nation_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_48 = key.n_nationkey;
			const Varchar<25>& v_49 = value.n_name;
			const Integer& v_50 = value.n_regionkey;
			const Varchar<152>& v_51 = value.n_comment;
			for (auto range = v_4.equal_range({v_48}); range.first!=range.second; range.first++) {
				const Integer& v_44 = std::get<0>(range.first->first);
				const Integer& v_41 = std::get<0>(range.first->second);
				const Varchar<25>& v_42 = std::get<1>(range.first->second);
				const Varchar<40>& v_43 = std::get<2>(range.first->second);
				const Varchar<15>& v_45 = std::get<3>(range.first->second);
				const Numeric& v_46 = std::get<4>(range.first->second);
				const Varchar<101>& v_47 = std::get<5>(range.first->second);
				const Integer& v_25 = std::get<6>(range.first->second);
				const Integer& v_26 = std::get<7>(range.first->second);
				const Integer& v_27 = std::get<8>(range.first->second);
				const Integer& v_28 = std::get<9>(range.first->second);
				const Numeric& v_29 = std::get<10>(range.first->second);
				const Numeric& v_30 = std::get<11>(range.first->second);
				const Numeric& v_31 = std::get<12>(range.first->second);
				const Numeric& v_32 = std::get<13>(range.first->second);
				const Varchar<1>& v_33 = std::get<14>(range.first->second);
				const Varchar<1>& v_34 = std::get<15>(range.first->second);
				const Timestamp& v_35 = std::get<16>(range.first->second);
				const Timestamp& v_36 = std::get<17>(range.first->second);
				const Timestamp& v_37 = std::get<18>(range.first->second);
				const Varchar<25>& v_38 = std::get<19>(range.first->second);
				const Varchar<10>& v_39 = std::get<20>(range.first->second);
				const Varchar<44>& v_40 = std::get<21>(range.first->second);
				const Integer& v_16 = std::get<22>(range.first->second);
				const Integer& v_17 = std::get<23>(range.first->second);
				const Varchar<1>& v_18 = std::get<24>(range.first->second);
				const Numeric& v_19 = std::get<25>(range.first->second);
				const Timestamp& v_20 = std::get<26>(range.first->second);
				const Varchar<15>& v_21 = std::get<27>(range.first->second);
				const Varchar<15>& v_22 = std::get<28>(range.first->second);
				const Integer& v_23 = std::get<29>(range.first->second);
				const Varchar<79>& v_24 = std::get<30>(range.first->second);
				const Integer& v_8 = std::get<31>(range.first->second);
				const Varchar<25>& v_9 = std::get<32>(range.first->second);
				const Varchar<40>& v_10 = std::get<33>(range.first->second);
				const Integer& v_11 = std::get<34>(range.first->second);
				const Varchar<15>& v_12 = std::get<35>(range.first->second);
				const Numeric& v_13 = std::get<36>(range.first->second);
				const Varchar<10>& v_14 = std::get<37>(range.first->second);
				const Varchar<117>& v_15 = std::get<38>(range.first->second);
				v_3.insert({{v_50}, {v_48, v_49, v_51, v_41, v_42, v_43, v_44, v_45, v_46, v_47, v_25, v_26, v_27, v_28, v_29, v_30, v_31, v_32, v_33, v_34, v_35, v_36, v_37, v_38, v_39, v_40, v_16, v_17, v_18, v_19, v_20, v_21, v_22, v_23, v_24, v_8, v_9, v_10, v_11, v_12, v_13, v_14, v_15}});
			}
		});
		db->region_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_52 = key.r_regionkey;
			const Varchar<25>& v_53 = value.r_name;
			const Varchar<152>& v_54 = value.r_comment;
			if (v_53 == Varchar<4>("ASIA")) {
				for (auto range = v_3.equal_range({v_52}); range.first!=range.second; range.first++) {
					const Integer& v_50 = std::get<0>(range.first->first);
					const Integer& v_48 = std::get<0>(range.first->second);
					const Varchar<25>& v_49 = std::get<1>(range.first->second);
					const Varchar<152>& v_51 = std::get<2>(range.first->second);
					const Integer& v_41 = std::get<3>(range.first->second);
					const Varchar<25>& v_42 = std::get<4>(range.first->second);
					const Varchar<40>& v_43 = std::get<5>(range.first->second);
					const Integer& v_44 = std::get<6>(range.first->second);
					const Varchar<15>& v_45 = std::get<7>(range.first->second);
					const Numeric& v_46 = std::get<8>(range.first->second);
					const Varchar<101>& v_47 = std::get<9>(range.first->second);
					const Integer& v_25 = std::get<10>(range.first->second);
					const Integer& v_26 = std::get<11>(range.first->second);
					const Integer& v_27 = std::get<12>(range.first->second);
					const Integer& v_28 = std::get<13>(range.first->second);
					const Numeric& v_29 = std::get<14>(range.first->second);
					const Numeric& v_30 = std::get<15>(range.first->second);
					const Numeric& v_31 = std::get<16>(range.first->second);
					const Numeric& v_32 = std::get<17>(range.first->second);
					const Varchar<1>& v_33 = std::get<18>(range.first->second);
					const Varchar<1>& v_34 = std::get<19>(range.first->second);
					const Timestamp& v_35 = std::get<20>(range.first->second);
					const Timestamp& v_36 = std::get<21>(range.first->second);
					const Timestamp& v_37 = std::get<22>(range.first->second);
					const Varchar<25>& v_38 = std::get<23>(range.first->second);
					const Varchar<10>& v_39 = std::get<24>(range.first->second);
					const Varchar<44>& v_40 = std::get<25>(range.first->second);
					const Integer& v_16 = std::get<26>(range.first->second);
					const Integer& v_17 = std::get<27>(range.first->second);
					const Varchar<1>& v_18 = std::get<28>(range.first->second);
					const Numeric& v_19 = std::get<29>(range.first->second);
					const Timestamp& v_20 = std::get<30>(range.first->second);
					const Varchar<15>& v_21 = std::get<31>(range.first->second);
					const Varchar<15>& v_22 = std::get<32>(range.first->second);
					const Integer& v_23 = std::get<33>(range.first->second);
					const Varchar<79>& v_24 = std::get<34>(range.first->second);
					const Integer& v_8 = std::get<35>(range.first->second);
					const Varchar<25>& v_9 = std::get<36>(range.first->second);
					const Varchar<40>& v_10 = std::get<37>(range.first->second);
					const Integer& v_11 = std::get<38>(range.first->second);
					const Varchar<15>& v_12 = std::get<39>(range.first->second);
					const Numeric& v_13 = std::get<40>(range.first->second);
					const Varchar<10>& v_14 = std::get<41>(range.first->second);
					const Varchar<117>& v_15 = std::get<42>(range.first->second);
					auto it = v_2.find({v_49});
					if (it == v_2.end()) {
						v_2.insert({{v_49}, {v_30 * (1 - v_31)}});
					} else {
						std::get<0>(it->second) += v_30 * (1 - v_31);
					}
				}
			}
		});
		for (auto& it : v_2) {
			const Varchar<25>& v_55 = std::get<0>(it.first);
			const Numeric& v_56 = std::get<0>(it.second);
			v_1.push_back({v_56, v_56, v_55});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Numeric& v_56 = std::get<1>(t);
			const Varchar<25>& v_55 = std::get<2>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_56 << ", " << v_55 << std::endl;
			}
		}
	}},
}},
	{"selects", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		std::vector<std::tuple<Numeric, Numeric, Varchar<25>>> v_1;
		std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Numeric>> v_2;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<152>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<101>, Integer, Integer, Integer, Integer, Numeric, Numeric, Numeric, Numeric, Varchar<1>, Varchar<1>, Timestamp, Timestamp, Timestamp, Varchar<25>, Varchar<10>, Varchar<44>, Integer, Integer, Varchar<1>, Numeric, Timestamp, Varchar<15>, Varchar<15>, Integer, Varchar<79>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<10>, Varchar<117>>> v_3;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Varchar<15>, Numeric, Varchar<101>, Integer, Integer, Integer, Integer, Numeric, Numeric, Numeric, Numeric, Varchar<1>, Varchar<1>, Timestamp, Timestamp, Timestamp, Varchar<25>, Varchar<10>, Varchar<44>, Integer, Integer, Varchar<1>, Numeric, Timestamp, Varchar<15>, Varchar<15>, Integer, Varchar<79>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<10>, Varchar<117>>> v_4;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Integer, Integer, Numeric, Numeric, Numeric, Numeric, Varchar<1>, Varchar<1>, Timestamp, Timestamp, Timestamp, Varchar<25>, Varchar<10>, Varchar<44>, Integer, Integer, Varchar<1>, Numeric, Timestamp, Varchar<15>, Varchar<15>, Integer, Varchar<79>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<10>, Varchar<117>>> v_5;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<1>, Numeric, Timestamp, Varchar<15>, Varchar<15>, Integer, Varchar<79>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<10>, Varchar<117>>> v_6;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<10>, Varchar<117>>> v_7;
		db->customer_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_8 = key.c_custkey;
			const Varchar<25>& v_9 = value.c_name;
			const Varchar<40>& v_10 = value.c_address;
			const Integer& v_11 = value.c_nationkey;
			const Varchar<15>& v_12 = value.c_phone;
			const Numeric& v_13 = value.c_acctbal;
			const Varchar<10>& v_14 = value.c_mktsegment;
			const Varchar<117>& v_15 = value.c_comment;
			v_7.insert({{v_8}, {v_9, v_10, v_11, v_12, v_13, v_14, v_15}});
		});
		db->orders_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_16 = key.o_orderkey;
			const Integer& v_17 = value.o_custkey;
			const Varchar<1>& v_18 = value.o_orderstatus;
			const Numeric& v_19 = value.o_totalprice;
			const Timestamp& v_20 = value.o_orderdate;
			const Varchar<15>& v_21 = value.o_orderpriority;
			const Varchar<15>& v_22 = value.o_clerk;
			const Integer& v_23 = value.o_shippriority;
			const Varchar<79>& v_24 = value.o_comment;
			if ((v_20 >= (2449354)) && (v_20 < (2449719))) {
				for (auto range = v_7.equal_range({v_17}); range.first!=range.second; range.first++) {
					const Integer& v_8 = std::get<0>(range.first->first);
					const Varchar<25>& v_9 = std::get<0>(range.first->second);
					const Varchar<40>& v_10 = std::get<1>(range.first->second);
					const Integer& v_11 = std::get<2>(range.first->second);
					const Varchar<15>& v_12 = std::get<3>(range.first->second);
					const Numeric& v_13 = std::get<4>(range.first->second);
					const Varchar<10>& v_14 = std::get<5>(range.first->second);
					const Varchar<117>& v_15 = std::get<6>(range.first->second);
					v_6.insert({{v_16}, {v_17, v_18, v_19, v_20, v_21, v_22, v_23, v_24, v_8, v_9, v_10, v_11, v_12, v_13, v_14, v_15}});
				}
			}
		});
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_25 = key.l_orderkey;
			const Integer& v_26 = value.l_partkey;
			const Integer& v_27 = value.l_suppkey;
			const Integer& v_28 = value.l_linenumber;
			const Numeric& v_29 = value.l_quantity;
			const Numeric& v_30 = value.l_extendedprice;
			const Numeric& v_31 = value.l_discount;
			const Numeric& v_32 = value.l_tax;
			const Varchar<1>& v_33 = value.l_returnflag;
			const Varchar<1>& v_34 = value.l_linestatus;
			const Timestamp& v_35 = value.l_shipdate;
			const Timestamp& v_36 = value.l_commitdate;
			const Timestamp& v_37 = value.l_receiptdate;
			const Varchar<25>& v_38 = value.l_shipinstruct;
			const Varchar<10>& v_39 = value.l_shipmode;
			const Varchar<44>& v_40 = value.l_comment;
			for (auto range = v_6.equal_range({v_25}); range.first!=range.second; range.first++) {
				const Integer& v_16 = std::get<0>(range.first->first);
				const Integer& v_17 = std::get<0>(range.first->second);
				const Varchar<1>& v_18 = std::get<1>(range.first->second);
				const Numeric& v_19 = std::get<2>(range.first->second);
				const Timestamp& v_20 = std::get<3>(range.first->second);
				const Varchar<15>& v_21 = std::get<4>(range.first->second);
				const Varchar<15>& v_22 = std::get<5>(range.first->second);
				const Integer& v_23 = std::get<6>(range.first->second);
				const Varchar<79>& v_24 = std::get<7>(range.first->second);
				const Integer& v_8 = std::get<8>(range.first->second);
				const Varchar<25>& v_9 = std::get<9>(range.first->second);
				const Varchar<40>& v_10 = std::get<10>(range.first->second);
				const Integer& v_11 = std::get<11>(range.first->second);
				const Varchar<15>& v_12 = std::get<12>(range.first->second);
				const Numeric& v_13 = std::get<13>(range.first->second);
				const Varchar<10>& v_14 = std::get<14>(range.first->second);
				const Varchar<117>& v_15 = std::get<15>(range.first->second);
				v_5.insert({{v_27}, {v_25, v_26, v_28, v_29, v_30, v_31, v_32, v_33, v_34, v_35, v_36, v_37, v_38, v_39, v_40, v_16, v_17, v_18, v_19, v_20, v_21, v_22, v_23, v_24, v_8, v_9, v_10, v_11, v_12, v_13, v_14, v_15}});
			}
		});
		db->supplier_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_41 = key.s_suppkey;
			const Varchar<25>& v_42 = value.s_name;
			const Varchar<40>& v_43 = value.s_address;
			const Integer& v_44 = value.s_nationkey;
			const Varchar<15>& v_45 = value.s_phone;
			const Numeric& v_46 = value.s_acctbal;
			const Varchar<101>& v_47 = value.s_comment;
			for (auto range = v_5.equal_range({v_41}); range.first!=range.second; range.first++) {
				const Integer& v_27 = std::get<0>(range.first->first);
				const Integer& v_25 = std::get<0>(range.first->second);
				const Integer& v_26 = std::get<1>(range.first->second);
				const Integer& v_28 = std::get<2>(range.first->second);
				const Numeric& v_29 = std::get<3>(range.first->second);
				const Numeric& v_30 = std::get<4>(range.first->second);
				const Numeric& v_31 = std::get<5>(range.first->second);
				const Numeric& v_32 = std::get<6>(range.first->second);
				const Varchar<1>& v_33 = std::get<7>(range.first->second);
				const Varchar<1>& v_34 = std::get<8>(range.first->second);
				const Timestamp& v_35 = std::get<9>(range.first->second);
				const Timestamp& v_36 = std::get<10>(range.first->second);
				const Timestamp& v_37 = std::get<11>(range.first->second);
				const Varchar<25>& v_38 = std::get<12>(range.first->second);
				const Varchar<10>& v_39 = std::get<13>(range.first->second);
				const Varchar<44>& v_40 = std::get<14>(range.first->second);
				const Integer& v_16 = std::get<15>(range.first->second);
				const Integer& v_17 = std::get<16>(range.first->second);
				const Varchar<1>& v_18 = std::get<17>(range.first->second);
				const Numeric& v_19 = std::get<18>(range.first->second);
				const Timestamp& v_20 = std::get<19>(range.first->second);
				const Varchar<15>& v_21 = std::get<20>(range.first->second);
				const Varchar<15>& v_22 = std::get<21>(range.first->second);
				const Integer& v_23 = std::get<22>(range.first->second);
				const Varchar<79>& v_24 = std::get<23>(range.first->second);
				const Integer& v_8 = std::get<24>(range.first->second);
				const Varchar<25>& v_9 = std::get<25>(range.first->second);
				const Varchar<40>& v_10 = std::get<26>(range.first->second);
				const Integer& v_11 = std::get<27>(range.first->second);
				const Varchar<15>& v_12 = std::get<28>(range.first->second);
				const Numeric& v_13 = std::get<29>(range.first->second);
				const Varchar<10>& v_14 = std::get<30>(range.first->second);
				const Varchar<117>& v_15 = std::get<31>(range.first->second);
				v_4.insert({{v_44}, {v_41, v_42, v_43, v_45, v_46, v_47, v_25, v_26, v_27, v_28, v_29, v_30, v_31, v_32, v_33, v_34, v_35, v_36, v_37, v_38, v_39, v_40, v_16, v_17, v_18, v_19, v_20, v_21, v_22, v_23, v_24, v_8, v_9, v_10, v_11, v_12, v_13, v_14, v_15}});
			}
		});
		db->nation_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_48 = key.n_nationkey;
			const Varchar<25>& v_49 = value.n_name;
			const Integer& v_50 = value.n_regionkey;
			const Varchar<152>& v_51 = value.n_comment;
			for (auto range = v_4.equal_range({v_48}); range.first!=range.second; range.first++) {
				const Integer& v_44 = std::get<0>(range.first->first);
				const Integer& v_41 = std::get<0>(range.first->second);
				const Varchar<25>& v_42 = std::get<1>(range.first->second);
				const Varchar<40>& v_43 = std::get<2>(range.first->second);
				const Varchar<15>& v_45 = std::get<3>(range.first->second);
				const Numeric& v_46 = std::get<4>(range.first->second);
				const Varchar<101>& v_47 = std::get<5>(range.first->second);
				const Integer& v_25 = std::get<6>(range.first->second);
				const Integer& v_26 = std::get<7>(range.first->second);
				const Integer& v_27 = std::get<8>(range.first->second);
				const Integer& v_28 = std::get<9>(range.first->second);
				const Numeric& v_29 = std::get<10>(range.first->second);
				const Numeric& v_30 = std::get<11>(range.first->second);
				const Numeric& v_31 = std::get<12>(range.first->second);
				const Numeric& v_32 = std::get<13>(range.first->second);
				const Varchar<1>& v_33 = std::get<14>(range.first->second);
				const Varchar<1>& v_34 = std::get<15>(range.first->second);
				const Timestamp& v_35 = std::get<16>(range.first->second);
				const Timestamp& v_36 = std::get<17>(range.first->second);
				const Timestamp& v_37 = std::get<18>(range.first->second);
				const Varchar<25>& v_38 = std::get<19>(range.first->second);
				const Varchar<10>& v_39 = std::get<20>(range.first->second);
				const Varchar<44>& v_40 = std::get<21>(range.first->second);
				const Integer& v_16 = std::get<22>(range.first->second);
				const Integer& v_17 = std::get<23>(range.first->second);
				const Varchar<1>& v_18 = std::get<24>(range.first->second);
				const Numeric& v_19 = std::get<25>(range.first->second);
				const Timestamp& v_20 = std::get<26>(range.first->second);
				const Varchar<15>& v_21 = std::get<27>(range.first->second);
				const Varchar<15>& v_22 = std::get<28>(range.first->second);
				const Integer& v_23 = std::get<29>(range.first->second);
				const Varchar<79>& v_24 = std::get<30>(range.first->second);
				const Integer& v_8 = std::get<31>(range.first->second);
				const Varchar<25>& v_9 = std::get<32>(range.first->second);
				const Varchar<40>& v_10 = std::get<33>(range.first->second);
				const Integer& v_11 = std::get<34>(range.first->second);
				const Varchar<15>& v_12 = std::get<35>(range.first->second);
				const Numeric& v_13 = std::get<36>(range.first->second);
				const Varchar<10>& v_14 = std::get<37>(range.first->second);
				const Varchar<117>& v_15 = std::get<38>(range.first->second);
				v_3.insert({{v_50}, {v_48, v_49, v_51, v_41, v_42, v_43, v_44, v_45, v_46, v_47, v_25, v_26, v_27, v_28, v_29, v_30, v_31, v_32, v_33, v_34, v_35, v_36, v_37, v_38, v_39, v_40, v_16, v_17, v_18, v_19, v_20, v_21, v_22, v_23, v_24, v_8, v_9, v_10, v_11, v_12, v_13, v_14, v_15}});
			}
		});
		db->region_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_52 = key.r_regionkey;
			const Varchar<25>& v_53 = value.r_name;
			const Varchar<152>& v_54 = value.r_comment;
			if (v_53 == Varchar<4>("ASIA")) {
				for (auto range = v_3.equal_range({v_52}); range.first!=range.second; range.first++) {
					const Integer& v_50 = std::get<0>(range.first->first);
					const Integer& v_48 = std::get<0>(range.first->second);
					const Varchar<25>& v_49 = std::get<1>(range.first->second);
					const Varchar<152>& v_51 = std::get<2>(range.first->second);
					const Integer& v_41 = std::get<3>(range.first->second);
					const Varchar<25>& v_42 = std::get<4>(range.first->second);
					const Varchar<40>& v_43 = std::get<5>(range.first->second);
					const Integer& v_44 = std::get<6>(range.first->second);
					const Varchar<15>& v_45 = std::get<7>(range.first->second);
					const Numeric& v_46 = std::get<8>(range.first->second);
					const Varchar<101>& v_47 = std::get<9>(range.first->second);
					const Integer& v_25 = std::get<10>(range.first->second);
					const Integer& v_26 = std::get<11>(range.first->second);
					const Integer& v_27 = std::get<12>(range.first->second);
					const Integer& v_28 = std::get<13>(range.first->second);
					const Numeric& v_29 = std::get<14>(range.first->second);
					const Numeric& v_30 = std::get<15>(range.first->second);
					const Numeric& v_31 = std::get<16>(range.first->second);
					const Numeric& v_32 = std::get<17>(range.first->second);
					const Varchar<1>& v_33 = std::get<18>(range.first->second);
					const Varchar<1>& v_34 = std::get<19>(range.first->second);
					const Timestamp& v_35 = std::get<20>(range.first->second);
					const Timestamp& v_36 = std::get<21>(range.first->second);
					const Timestamp& v_37 = std::get<22>(range.first->second);
					const Varchar<25>& v_38 = std::get<23>(range.first->second);
					const Varchar<10>& v_39 = std::get<24>(range.first->second);
					const Varchar<44>& v_40 = std::get<25>(range.first->second);
					const Integer& v_16 = std::get<26>(range.first->second);
					const Integer& v_17 = std::get<27>(range.first->second);
					const Varchar<1>& v_18 = std::get<28>(range.first->second);
					const Numeric& v_19 = std::get<29>(range.first->second);
					const Timestamp& v_20 = std::get<30>(range.first->second);
					const Varchar<15>& v_21 = std::get<31>(range.first->second);
					const Varchar<15>& v_22 = std::get<32>(range.first->second);
					const Integer& v_23 = std::get<33>(range.first->second);
					const Varchar<79>& v_24 = std::get<34>(range.first->second);
					const Integer& v_8 = std::get<35>(range.first->second);
					const Varchar<25>& v_9 = std::get<36>(range.first->second);
					const Varchar<40>& v_10 = std::get<37>(range.first->second);
					const Integer& v_11 = std::get<38>(range.first->second);
					const Varchar<15>& v_12 = std::get<39>(range.first->second);
					const Numeric& v_13 = std::get<40>(range.first->second);
					const Varchar<10>& v_14 = std::get<41>(range.first->second);
					const Varchar<117>& v_15 = std::get<42>(range.first->second);
					auto it = v_2.find({v_49});
					if (it == v_2.end()) {
						v_2.insert({{v_49}, {v_30 * (1 - v_31)}});
					} else {
						std::get<0>(it->second) += v_30 * (1 - v_31);
					}
				}
			}
		});
		for (auto& it : v_2) {
			const Varchar<25>& v_55 = std::get<0>(it.first);
			const Numeric& v_56 = std::get<0>(it.second);
			v_1.push_back({v_56, v_56, v_55});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Numeric& v_56 = std::get<1>(t);
			const Varchar<25>& v_55 = std::get<2>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_56 << ", " << v_55 << std::endl;
			}
		}
	}},
}},
	{"scans", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		std::vector<std::tuple<Numeric, Numeric, Varchar<25>>> v_1;
		std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Numeric>> v_2;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<152>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<101>, Integer, Integer, Integer, Integer, Numeric, Numeric, Numeric, Numeric, Varchar<1>, Varchar<1>, Timestamp, Timestamp, Timestamp, Varchar<25>, Varchar<10>, Varchar<44>, Integer, Integer, Varchar<1>, Numeric, Timestamp, Varchar<15>, Varchar<15>, Integer, Varchar<79>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<10>, Varchar<117>>> v_3;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<40>, Varchar<15>, Numeric, Varchar<101>, Integer, Integer, Integer, Integer, Numeric, Numeric, Numeric, Numeric, Varchar<1>, Varchar<1>, Timestamp, Timestamp, Timestamp, Varchar<25>, Varchar<10>, Varchar<44>, Integer, Integer, Varchar<1>, Numeric, Timestamp, Varchar<15>, Varchar<15>, Integer, Varchar<79>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<10>, Varchar<117>>> v_4;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Integer, Integer, Numeric, Numeric, Numeric, Numeric, Varchar<1>, Varchar<1>, Timestamp, Timestamp, Timestamp, Varchar<25>, Varchar<10>, Varchar<44>, Integer, Integer, Varchar<1>, Numeric, Timestamp, Varchar<15>, Varchar<15>, Integer, Varchar<79>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<10>, Varchar<117>>> v_5;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<1>, Numeric, Timestamp, Varchar<15>, Varchar<15>, Integer, Varchar<79>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<10>, Varchar<117>>> v_6;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<10>, Varchar<117>>> v_7;
		db->customer_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_8 = key.c_custkey;
			const Varchar<25>& v_9 = value.c_name;
			const Varchar<40>& v_10 = value.c_address;
			const Integer& v_11 = value.c_nationkey;
			const Varchar<15>& v_12 = value.c_phone;
			const Numeric& v_13 = value.c_acctbal;
			const Varchar<10>& v_14 = value.c_mktsegment;
			const Varchar<117>& v_15 = value.c_comment;
			v_7.insert({{v_8}, {v_9, v_10, v_11, v_12, v_13, v_14, v_15}});
		});
		db->orders_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_16 = key.o_orderkey;
			const Integer& v_17 = value.o_custkey;
			const Varchar<1>& v_18 = value.o_orderstatus;
			const Numeric& v_19 = value.o_totalprice;
			const Timestamp& v_20 = value.o_orderdate;
			const Varchar<15>& v_21 = value.o_orderpriority;
			const Varchar<15>& v_22 = value.o_clerk;
			const Integer& v_23 = value.o_shippriority;
			const Varchar<79>& v_24 = value.o_comment;
			if ((v_20 >= (2449354)) && (v_20 < (2449719))) {
				for (auto range = v_7.equal_range({v_17}); range.first!=range.second; range.first++) {
					const Integer& v_8 = std::get<0>(range.first->first);
					const Varchar<25>& v_9 = std::get<0>(range.first->second);
					const Varchar<40>& v_10 = std::get<1>(range.first->second);
					const Integer& v_11 = std::get<2>(range.first->second);
					const Varchar<15>& v_12 = std::get<3>(range.first->second);
					const Numeric& v_13 = std::get<4>(range.first->second);
					const Varchar<10>& v_14 = std::get<5>(range.first->second);
					const Varchar<117>& v_15 = std::get<6>(range.first->second);
					v_6.insert({{v_16}, {v_17, v_18, v_19, v_20, v_21, v_22, v_23, v_24, v_8, v_9, v_10, v_11, v_12, v_13, v_14, v_15}});
				}
			}
		});
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_25 = key.l_orderkey;
			const Integer& v_26 = value.l_partkey;
			const Integer& v_27 = value.l_suppkey;
			const Integer& v_28 = value.l_linenumber;
			const Numeric& v_29 = value.l_quantity;
			const Numeric& v_30 = value.l_extendedprice;
			const Numeric& v_31 = value.l_discount;
			const Numeric& v_32 = value.l_tax;
			const Varchar<1>& v_33 = value.l_returnflag;
			const Varchar<1>& v_34 = value.l_linestatus;
			const Timestamp& v_35 = value.l_shipdate;
			const Timestamp& v_36 = value.l_commitdate;
			const Timestamp& v_37 = value.l_receiptdate;
			const Varchar<25>& v_38 = value.l_shipinstruct;
			const Varchar<10>& v_39 = value.l_shipmode;
			const Varchar<44>& v_40 = value.l_comment;
			for (auto range = v_6.equal_range({v_25}); range.first!=range.second; range.first++) {
				const Integer& v_16 = std::get<0>(range.first->first);
				const Integer& v_17 = std::get<0>(range.first->second);
				const Varchar<1>& v_18 = std::get<1>(range.first->second);
				const Numeric& v_19 = std::get<2>(range.first->second);
				const Timestamp& v_20 = std::get<3>(range.first->second);
				const Varchar<15>& v_21 = std::get<4>(range.first->second);
				const Varchar<15>& v_22 = std::get<5>(range.first->second);
				const Integer& v_23 = std::get<6>(range.first->second);
				const Varchar<79>& v_24 = std::get<7>(range.first->second);
				const Integer& v_8 = std::get<8>(range.first->second);
				const Varchar<25>& v_9 = std::get<9>(range.first->second);
				const Varchar<40>& v_10 = std::get<10>(range.first->second);
				const Integer& v_11 = std::get<11>(range.first->second);
				const Varchar<15>& v_12 = std::get<12>(range.first->second);
				const Numeric& v_13 = std::get<13>(range.first->second);
				const Varchar<10>& v_14 = std::get<14>(range.first->second);
				const Varchar<117>& v_15 = std::get<15>(range.first->second);
				v_5.insert({{v_27}, {v_25, v_26, v_28, v_29, v_30, v_31, v_32, v_33, v_34, v_35, v_36, v_37, v_38, v_39, v_40, v_16, v_17, v_18, v_19, v_20, v_21, v_22, v_23, v_24, v_8, v_9, v_10, v_11, v_12, v_13, v_14, v_15}});
			}
		});
		db->supplier_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_41 = key.s_suppkey;
			const Varchar<25>& v_42 = value.s_name;
			const Varchar<40>& v_43 = value.s_address;
			const Integer& v_44 = value.s_nationkey;
			const Varchar<15>& v_45 = value.s_phone;
			const Numeric& v_46 = value.s_acctbal;
			const Varchar<101>& v_47 = value.s_comment;
			for (auto range = v_5.equal_range({v_41}); range.first!=range.second; range.first++) {
				const Integer& v_27 = std::get<0>(range.first->first);
				const Integer& v_25 = std::get<0>(range.first->second);
				const Integer& v_26 = std::get<1>(range.first->second);
				const Integer& v_28 = std::get<2>(range.first->second);
				const Numeric& v_29 = std::get<3>(range.first->second);
				const Numeric& v_30 = std::get<4>(range.first->second);
				const Numeric& v_31 = std::get<5>(range.first->second);
				const Numeric& v_32 = std::get<6>(range.first->second);
				const Varchar<1>& v_33 = std::get<7>(range.first->second);
				const Varchar<1>& v_34 = std::get<8>(range.first->second);
				const Timestamp& v_35 = std::get<9>(range.first->second);
				const Timestamp& v_36 = std::get<10>(range.first->second);
				const Timestamp& v_37 = std::get<11>(range.first->second);
				const Varchar<25>& v_38 = std::get<12>(range.first->second);
				const Varchar<10>& v_39 = std::get<13>(range.first->second);
				const Varchar<44>& v_40 = std::get<14>(range.first->second);
				const Integer& v_16 = std::get<15>(range.first->second);
				const Integer& v_17 = std::get<16>(range.first->second);
				const Varchar<1>& v_18 = std::get<17>(range.first->second);
				const Numeric& v_19 = std::get<18>(range.first->second);
				const Timestamp& v_20 = std::get<19>(range.first->second);
				const Varchar<15>& v_21 = std::get<20>(range.first->second);
				const Varchar<15>& v_22 = std::get<21>(range.first->second);
				const Integer& v_23 = std::get<22>(range.first->second);
				const Varchar<79>& v_24 = std::get<23>(range.first->second);
				const Integer& v_8 = std::get<24>(range.first->second);
				const Varchar<25>& v_9 = std::get<25>(range.first->second);
				const Varchar<40>& v_10 = std::get<26>(range.first->second);
				const Integer& v_11 = std::get<27>(range.first->second);
				const Varchar<15>& v_12 = std::get<28>(range.first->second);
				const Numeric& v_13 = std::get<29>(range.first->second);
				const Varchar<10>& v_14 = std::get<30>(range.first->second);
				const Varchar<117>& v_15 = std::get<31>(range.first->second);
				v_4.insert({{v_44}, {v_41, v_42, v_43, v_45, v_46, v_47, v_25, v_26, v_27, v_28, v_29, v_30, v_31, v_32, v_33, v_34, v_35, v_36, v_37, v_38, v_39, v_40, v_16, v_17, v_18, v_19, v_20, v_21, v_22, v_23, v_24, v_8, v_9, v_10, v_11, v_12, v_13, v_14, v_15}});
			}
		});
		db->nation_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_48 = key.n_nationkey;
			const Varchar<25>& v_49 = value.n_name;
			const Integer& v_50 = value.n_regionkey;
			const Varchar<152>& v_51 = value.n_comment;
			for (auto range = v_4.equal_range({v_48}); range.first!=range.second; range.first++) {
				const Integer& v_44 = std::get<0>(range.first->first);
				const Integer& v_41 = std::get<0>(range.first->second);
				const Varchar<25>& v_42 = std::get<1>(range.first->second);
				const Varchar<40>& v_43 = std::get<2>(range.first->second);
				const Varchar<15>& v_45 = std::get<3>(range.first->second);
				const Numeric& v_46 = std::get<4>(range.first->second);
				const Varchar<101>& v_47 = std::get<5>(range.first->second);
				const Integer& v_25 = std::get<6>(range.first->second);
				const Integer& v_26 = std::get<7>(range.first->second);
				const Integer& v_27 = std::get<8>(range.first->second);
				const Integer& v_28 = std::get<9>(range.first->second);
				const Numeric& v_29 = std::get<10>(range.first->second);
				const Numeric& v_30 = std::get<11>(range.first->second);
				const Numeric& v_31 = std::get<12>(range.first->second);
				const Numeric& v_32 = std::get<13>(range.first->second);
				const Varchar<1>& v_33 = std::get<14>(range.first->second);
				const Varchar<1>& v_34 = std::get<15>(range.first->second);
				const Timestamp& v_35 = std::get<16>(range.first->second);
				const Timestamp& v_36 = std::get<17>(range.first->second);
				const Timestamp& v_37 = std::get<18>(range.first->second);
				const Varchar<25>& v_38 = std::get<19>(range.first->second);
				const Varchar<10>& v_39 = std::get<20>(range.first->second);
				const Varchar<44>& v_40 = std::get<21>(range.first->second);
				const Integer& v_16 = std::get<22>(range.first->second);
				const Integer& v_17 = std::get<23>(range.first->second);
				const Varchar<1>& v_18 = std::get<24>(range.first->second);
				const Numeric& v_19 = std::get<25>(range.first->second);
				const Timestamp& v_20 = std::get<26>(range.first->second);
				const Varchar<15>& v_21 = std::get<27>(range.first->second);
				const Varchar<15>& v_22 = std::get<28>(range.first->second);
				const Integer& v_23 = std::get<29>(range.first->second);
				const Varchar<79>& v_24 = std::get<30>(range.first->second);
				const Integer& v_8 = std::get<31>(range.first->second);
				const Varchar<25>& v_9 = std::get<32>(range.first->second);
				const Varchar<40>& v_10 = std::get<33>(range.first->second);
				const Integer& v_11 = std::get<34>(range.first->second);
				const Varchar<15>& v_12 = std::get<35>(range.first->second);
				const Numeric& v_13 = std::get<36>(range.first->second);
				const Varchar<10>& v_14 = std::get<37>(range.first->second);
				const Varchar<117>& v_15 = std::get<38>(range.first->second);
				v_3.insert({{v_50}, {v_48, v_49, v_51, v_41, v_42, v_43, v_44, v_45, v_46, v_47, v_25, v_26, v_27, v_28, v_29, v_30, v_31, v_32, v_33, v_34, v_35, v_36, v_37, v_38, v_39, v_40, v_16, v_17, v_18, v_19, v_20, v_21, v_22, v_23, v_24, v_8, v_9, v_10, v_11, v_12, v_13, v_14, v_15}});
			}
		});
		db->region_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_52 = key.r_regionkey;
			const Varchar<25>& v_53 = value.r_name;
			const Varchar<152>& v_54 = value.r_comment;
			if (v_53 == Varchar<4>("ASIA")) {
				for (auto range = v_3.equal_range({v_52}); range.first!=range.second; range.first++) {
					const Integer& v_50 = std::get<0>(range.first->first);
					const Integer& v_48 = std::get<0>(range.first->second);
					const Varchar<25>& v_49 = std::get<1>(range.first->second);
					const Varchar<152>& v_51 = std::get<2>(range.first->second);
					const Integer& v_41 = std::get<3>(range.first->second);
					const Varchar<25>& v_42 = std::get<4>(range.first->second);
					const Varchar<40>& v_43 = std::get<5>(range.first->second);
					const Integer& v_44 = std::get<6>(range.first->second);
					const Varchar<15>& v_45 = std::get<7>(range.first->second);
					const Numeric& v_46 = std::get<8>(range.first->second);
					const Varchar<101>& v_47 = std::get<9>(range.first->second);
					const Integer& v_25 = std::get<10>(range.first->second);
					const Integer& v_26 = std::get<11>(range.first->second);
					const Integer& v_27 = std::get<12>(range.first->second);
					const Integer& v_28 = std::get<13>(range.first->second);
					const Numeric& v_29 = std::get<14>(range.first->second);
					const Numeric& v_30 = std::get<15>(range.first->second);
					const Numeric& v_31 = std::get<16>(range.first->second);
					const Numeric& v_32 = std::get<17>(range.first->second);
					const Varchar<1>& v_33 = std::get<18>(range.first->second);
					const Varchar<1>& v_34 = std::get<19>(range.first->second);
					const Timestamp& v_35 = std::get<20>(range.first->second);
					const Timestamp& v_36 = std::get<21>(range.first->second);
					const Timestamp& v_37 = std::get<22>(range.first->second);
					const Varchar<25>& v_38 = std::get<23>(range.first->second);
					const Varchar<10>& v_39 = std::get<24>(range.first->second);
					const Varchar<44>& v_40 = std::get<25>(range.first->second);
					const Integer& v_16 = std::get<26>(range.first->second);
					const Integer& v_17 = std::get<27>(range.first->second);
					const Varchar<1>& v_18 = std::get<28>(range.first->second);
					const Numeric& v_19 = std::get<29>(range.first->second);
					const Timestamp& v_20 = std::get<30>(range.first->second);
					const Varchar<15>& v_21 = std::get<31>(range.first->second);
					const Varchar<15>& v_22 = std::get<32>(range.first->second);
					const Integer& v_23 = std::get<33>(range.first->second);
					const Varchar<79>& v_24 = std::get<34>(range.first->second);
					const Integer& v_8 = std::get<35>(range.first->second);
					const Varchar<25>& v_9 = std::get<36>(range.first->second);
					const Varchar<40>& v_10 = std::get<37>(range.first->second);
					const Integer& v_11 = std::get<38>(range.first->second);
					const Varchar<15>& v_12 = std::get<39>(range.first->second);
					const Numeric& v_13 = std::get<40>(range.first->second);
					const Varchar<10>& v_14 = std::get<41>(range.first->second);
					const Varchar<117>& v_15 = std::get<42>(range.first->second);
					auto it = v_2.find({v_49});
					if (it == v_2.end()) {
						v_2.insert({{v_49}, {v_30 * (1 - v_31)}});
					} else {
						std::get<0>(it->second) += v_30 * (1 - v_31);
					}
				}
			}
		});
		for (auto& it : v_2) {
			const Varchar<25>& v_55 = std::get<0>(it.first);
			const Numeric& v_56 = std::get<0>(it.second);
			v_1.push_back({v_56, v_56, v_55});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Numeric& v_56 = std::get<1>(t);
			const Varchar<25>& v_55 = std::get<2>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_56 << ", " << v_55 << std::endl;
			}
		}
	}},
}},
	{"joins", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		std::vector<std::tuple<Numeric, Numeric, Varchar<25>>> v_1;
		std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Numeric>> v_2;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<152>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<101>, Integer, Integer, Integer, Integer, Numeric, Numeric, Numeric, Numeric, Varchar<1>, Varchar<1>, Timestamp, Timestamp, Timestamp, Varchar<25>, Varchar<10>, Varchar<44>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<10>, Varchar<117>, Integer, Integer, Varchar<1>, Numeric, Timestamp, Varchar<15>, Varchar<15>, Integer, Varchar<79>>> v_3;
		db->orders_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_4 = key.o_orderkey;
			const Integer& v_5 = value.o_custkey;
			const Varchar<1>& v_6 = value.o_orderstatus;
			const Numeric& v_7 = value.o_totalprice;
			const Timestamp& v_8 = value.o_orderdate;
			const Varchar<15>& v_9 = value.o_orderpriority;
			const Varchar<15>& v_10 = value.o_clerk;
			const Integer& v_11 = value.o_shippriority;
			const Varchar<79>& v_12 = value.o_comment;
			if ((v_8 >= (2449354)) && (v_8 < (2449719))) {
				db->customer_tpch.lookup1({v_5}, [&](auto& value) {
					Integer v_13 = v_5;
					Varchar<25> v_14 = value.c_name;
					Varchar<40> v_15 = value.c_address;
					Integer v_16 = value.c_nationkey;
					Varchar<15> v_17 = value.c_phone;
					Numeric v_18 = value.c_acctbal;
					Varchar<10> v_19 = value.c_mktsegment;
					Varchar<117> v_20 = value.c_comment;
					db->lineitem_tpch.lookup1({v_4}, [&](auto& value) {
						Integer v_21 = v_4;
						Integer v_22 = value.l_partkey;
						Integer v_23 = value.l_suppkey;
						Integer v_24 = value.l_linenumber;
						Numeric v_25 = value.l_quantity;
						Numeric v_26 = value.l_extendedprice;
						Numeric v_27 = value.l_discount;
						Numeric v_28 = value.l_tax;
						Varchar<1> v_29 = value.l_returnflag;
						Varchar<1> v_30 = value.l_linestatus;
						Timestamp v_31 = value.l_shipdate;
						Timestamp v_32 = value.l_commitdate;
						Timestamp v_33 = value.l_receiptdate;
						Varchar<25> v_34 = value.l_shipinstruct;
						Varchar<10> v_35 = value.l_shipmode;
						Varchar<44> v_36 = value.l_comment;
						db->supplier_tpch.lookup1({v_23}, [&](auto& value) {
							Integer v_37 = v_23;
							Varchar<25> v_38 = value.s_name;
							Varchar<40> v_39 = value.s_address;
							Integer v_40 = value.s_nationkey;
							Varchar<15> v_41 = value.s_phone;
							Numeric v_42 = value.s_acctbal;
							Varchar<101> v_43 = value.s_comment;
							db->nation_tpch.lookup1({v_40}, [&](auto& value) {
								Integer v_44 = v_40;
								Varchar<25> v_45 = value.n_name;
								Integer v_46 = value.n_regionkey;
								Varchar<152> v_47 = value.n_comment;
								v_3.insert({{v_46}, {v_44, v_45, v_47, v_37, v_38, v_39, v_40, v_41, v_42, v_43, v_21, v_22, v_23, v_24, v_25, v_26, v_27, v_28, v_29, v_30, v_31, v_32, v_33, v_34, v_35, v_36, v_13, v_14, v_15, v_16, v_17, v_18, v_19, v_20, v_4, v_5, v_6, v_7, v_8, v_9, v_10, v_11, v_12}});
							});
						});
					});
				});
			}
		});
		db->region_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_48 = key.r_regionkey;
			const Varchar<25>& v_49 = value.r_name;
			const Varchar<152>& v_50 = value.r_comment;
			if (v_49 == Varchar<4>("ASIA")) {
				for (auto range = v_3.equal_range({v_48}); range.first!=range.second; range.first++) {
					const Integer& v_46 = std::get<0>(range.first->first);
					const Integer& v_44 = std::get<0>(range.first->second);
					const Varchar<25>& v_45 = std::get<1>(range.first->second);
					const Varchar<152>& v_47 = std::get<2>(range.first->second);
					const Integer& v_37 = std::get<3>(range.first->second);
					const Varchar<25>& v_38 = std::get<4>(range.first->second);
					const Varchar<40>& v_39 = std::get<5>(range.first->second);
					const Integer& v_40 = std::get<6>(range.first->second);
					const Varchar<15>& v_41 = std::get<7>(range.first->second);
					const Numeric& v_42 = std::get<8>(range.first->second);
					const Varchar<101>& v_43 = std::get<9>(range.first->second);
					const Integer& v_21 = std::get<10>(range.first->second);
					const Integer& v_22 = std::get<11>(range.first->second);
					const Integer& v_23 = std::get<12>(range.first->second);
					const Integer& v_24 = std::get<13>(range.first->second);
					const Numeric& v_25 = std::get<14>(range.first->second);
					const Numeric& v_26 = std::get<15>(range.first->second);
					const Numeric& v_27 = std::get<16>(range.first->second);
					const Numeric& v_28 = std::get<17>(range.first->second);
					const Varchar<1>& v_29 = std::get<18>(range.first->second);
					const Varchar<1>& v_30 = std::get<19>(range.first->second);
					const Timestamp& v_31 = std::get<20>(range.first->second);
					const Timestamp& v_32 = std::get<21>(range.first->second);
					const Timestamp& v_33 = std::get<22>(range.first->second);
					const Varchar<25>& v_34 = std::get<23>(range.first->second);
					const Varchar<10>& v_35 = std::get<24>(range.first->second);
					const Varchar<44>& v_36 = std::get<25>(range.first->second);
					const Integer& v_13 = std::get<26>(range.first->second);
					const Varchar<25>& v_14 = std::get<27>(range.first->second);
					const Varchar<40>& v_15 = std::get<28>(range.first->second);
					const Integer& v_16 = std::get<29>(range.first->second);
					const Varchar<15>& v_17 = std::get<30>(range.first->second);
					const Numeric& v_18 = std::get<31>(range.first->second);
					const Varchar<10>& v_19 = std::get<32>(range.first->second);
					const Varchar<117>& v_20 = std::get<33>(range.first->second);
					const Integer& v_4 = std::get<34>(range.first->second);
					const Integer& v_5 = std::get<35>(range.first->second);
					const Varchar<1>& v_6 = std::get<36>(range.first->second);
					const Numeric& v_7 = std::get<37>(range.first->second);
					const Timestamp& v_8 = std::get<38>(range.first->second);
					const Varchar<15>& v_9 = std::get<39>(range.first->second);
					const Varchar<15>& v_10 = std::get<40>(range.first->second);
					const Integer& v_11 = std::get<41>(range.first->second);
					const Varchar<79>& v_12 = std::get<42>(range.first->second);
					auto it = v_2.find({v_45});
					if (it == v_2.end()) {
						v_2.insert({{v_45}, {v_26 * (1 - v_27)}});
					} else {
						std::get<0>(it->second) += v_26 * (1 - v_27);
					}
				}
			}
		});
		for (auto& it : v_2) {
			const Varchar<25>& v_51 = std::get<0>(it.first);
			const Numeric& v_52 = std::get<0>(it.second);
			v_1.push_back({v_52, v_52, v_51});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Numeric& v_52 = std::get<1>(t);
			const Varchar<25>& v_51 = std::get<2>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_52 << ", " << v_51 << std::endl;
			}
		}
	}},
}},
	{"all", {
	{"./query/query.sane", [](Database* db, size_t limit) {
		std::vector<std::tuple<Numeric, Numeric, Varchar<25>>> v_1;
		std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Numeric>> v_2;
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Varchar<25>, Varchar<152>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<101>, Integer, Integer, Integer, Integer, Numeric, Numeric, Numeric, Numeric, Varchar<1>, Varchar<1>, Timestamp, Timestamp, Timestamp, Varchar<25>, Varchar<10>, Varchar<44>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<10>, Varchar<117>, Integer, Integer, Varchar<1>, Numeric, Timestamp, Varchar<15>, Varchar<15>, Integer, Varchar<79>>> v_3;
		db->orders_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_4 = key.o_orderkey;
			const Integer& v_5 = value.o_custkey;
			const Varchar<1>& v_6 = value.o_orderstatus;
			const Numeric& v_7 = value.o_totalprice;
			const Timestamp& v_8 = value.o_orderdate;
			const Varchar<15>& v_9 = value.o_orderpriority;
			const Varchar<15>& v_10 = value.o_clerk;
			const Integer& v_11 = value.o_shippriority;
			const Varchar<79>& v_12 = value.o_comment;
			if ((v_8 >= (2449354)) && (v_8 < (2449719))) {
				db->customer_tpch.lookup1({v_5}, [&](auto& value) {
					Integer v_13 = v_5;
					Varchar<25> v_14 = value.c_name;
					Varchar<40> v_15 = value.c_address;
					Integer v_16 = value.c_nationkey;
					Varchar<15> v_17 = value.c_phone;
					Numeric v_18 = value.c_acctbal;
					Varchar<10> v_19 = value.c_mktsegment;
					Varchar<117> v_20 = value.c_comment;
					db->lineitem_tpch.lookup1({v_4}, [&](auto& value) {
						Integer v_21 = v_4;
						Integer v_22 = value.l_partkey;
						Integer v_23 = value.l_suppkey;
						Integer v_24 = value.l_linenumber;
						Numeric v_25 = value.l_quantity;
						Numeric v_26 = value.l_extendedprice;
						Numeric v_27 = value.l_discount;
						Numeric v_28 = value.l_tax;
						Varchar<1> v_29 = value.l_returnflag;
						Varchar<1> v_30 = value.l_linestatus;
						Timestamp v_31 = value.l_shipdate;
						Timestamp v_32 = value.l_commitdate;
						Timestamp v_33 = value.l_receiptdate;
						Varchar<25> v_34 = value.l_shipinstruct;
						Varchar<10> v_35 = value.l_shipmode;
						Varchar<44> v_36 = value.l_comment;
						db->supplier_tpch.lookup1({v_23}, [&](auto& value) {
							Integer v_37 = v_23;
							Varchar<25> v_38 = value.s_name;
							Varchar<40> v_39 = value.s_address;
							Integer v_40 = value.s_nationkey;
							Varchar<15> v_41 = value.s_phone;
							Numeric v_42 = value.s_acctbal;
							Varchar<101> v_43 = value.s_comment;
							db->nation_tpch.lookup1({v_40}, [&](auto& value) {
								Integer v_44 = v_40;
								Varchar<25> v_45 = value.n_name;
								Integer v_46 = value.n_regionkey;
								Varchar<152> v_47 = value.n_comment;
								v_3.insert({{v_46}, {v_44, v_45, v_47, v_37, v_38, v_39, v_40, v_41, v_42, v_43, v_21, v_22, v_23, v_24, v_25, v_26, v_27, v_28, v_29, v_30, v_31, v_32, v_33, v_34, v_35, v_36, v_13, v_14, v_15, v_16, v_17, v_18, v_19, v_20, v_4, v_5, v_6, v_7, v_8, v_9, v_10, v_11, v_12}});
							});
						});
					});
				});
			}
		});
		db->region_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_48 = key.r_regionkey;
			const Varchar<25>& v_49 = value.r_name;
			const Varchar<152>& v_50 = value.r_comment;
			if (v_49 == Varchar<4>("ASIA")) {
				for (auto range = v_3.equal_range({v_48}); range.first!=range.second; range.first++) {
					const Integer& v_46 = std::get<0>(range.first->first);
					const Integer& v_44 = std::get<0>(range.first->second);
					const Varchar<25>& v_45 = std::get<1>(range.first->second);
					const Varchar<152>& v_47 = std::get<2>(range.first->second);
					const Integer& v_37 = std::get<3>(range.first->second);
					const Varchar<25>& v_38 = std::get<4>(range.first->second);
					const Varchar<40>& v_39 = std::get<5>(range.first->second);
					const Integer& v_40 = std::get<6>(range.first->second);
					const Varchar<15>& v_41 = std::get<7>(range.first->second);
					const Numeric& v_42 = std::get<8>(range.first->second);
					const Varchar<101>& v_43 = std::get<9>(range.first->second);
					const Integer& v_21 = std::get<10>(range.first->second);
					const Integer& v_22 = std::get<11>(range.first->second);
					const Integer& v_23 = std::get<12>(range.first->second);
					const Integer& v_24 = std::get<13>(range.first->second);
					const Numeric& v_25 = std::get<14>(range.first->second);
					const Numeric& v_26 = std::get<15>(range.first->second);
					const Numeric& v_27 = std::get<16>(range.first->second);
					const Numeric& v_28 = std::get<17>(range.first->second);
					const Varchar<1>& v_29 = std::get<18>(range.first->second);
					const Varchar<1>& v_30 = std::get<19>(range.first->second);
					const Timestamp& v_31 = std::get<20>(range.first->second);
					const Timestamp& v_32 = std::get<21>(range.first->second);
					const Timestamp& v_33 = std::get<22>(range.first->second);
					const Varchar<25>& v_34 = std::get<23>(range.first->second);
					const Varchar<10>& v_35 = std::get<24>(range.first->second);
					const Varchar<44>& v_36 = std::get<25>(range.first->second);
					const Integer& v_13 = std::get<26>(range.first->second);
					const Varchar<25>& v_14 = std::get<27>(range.first->second);
					const Varchar<40>& v_15 = std::get<28>(range.first->second);
					const Integer& v_16 = std::get<29>(range.first->second);
					const Varchar<15>& v_17 = std::get<30>(range.first->second);
					const Numeric& v_18 = std::get<31>(range.first->second);
					const Varchar<10>& v_19 = std::get<32>(range.first->second);
					const Varchar<117>& v_20 = std::get<33>(range.first->second);
					const Integer& v_4 = std::get<34>(range.first->second);
					const Integer& v_5 = std::get<35>(range.first->second);
					const Varchar<1>& v_6 = std::get<36>(range.first->second);
					const Numeric& v_7 = std::get<37>(range.first->second);
					const Timestamp& v_8 = std::get<38>(range.first->second);
					const Varchar<15>& v_9 = std::get<39>(range.first->second);
					const Varchar<15>& v_10 = std::get<40>(range.first->second);
					const Integer& v_11 = std::get<41>(range.first->second);
					const Varchar<79>& v_12 = std::get<42>(range.first->second);
					auto it = v_2.find({v_45});
					if (it == v_2.end()) {
						v_2.insert({{v_45}, {v_26 * (1 - v_27)}});
					} else {
						std::get<0>(it->second) += v_26 * (1 - v_27);
					}
				}
			}
		});
		for (auto& it : v_2) {
			const Varchar<25>& v_51 = std::get<0>(it.first);
			const Numeric& v_52 = std::get<0>(it.second);
			v_1.push_back({v_52, v_52, v_51});
		}
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) {
			if (get<0>(t1) < get<0>(t2)) return true;
			if (get<0>(t2) < get<0>(t1)) return false;
			return false;
		});
		for (auto& t : v_1) {
			const Numeric& v_52 = std::get<1>(t);
			const Varchar<25>& v_51 = std::get<2>(t);
			if (limit > 0) {
				limit -= 1;
				std::cout << v_52 << ", " << v_51 << std::endl;
			}
		}
	}},
}},
};
