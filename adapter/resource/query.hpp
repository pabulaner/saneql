std::vector<std::tuple<Integer, Varchar<25>, Integer, Varchar<25>>> v_1;
std::unordered_map<std::tuple<Varchar<25>>, std::tuple<Integer>> v_2;
std::unordered_multimap<std::tuple<Integer, Integer>, std::tuple<Integer, Integer, Integer, Integer, Numeric, Numeric, Numeric, Numeric, Varchar<1>, Varchar<1>, Timestamp, Timestamp, Timestamp, Varchar<25>, Varchar<10>, Varchar<44>, Integer, Integer, Varchar<25>, Integer, Varchar<152>, Integer, Integer, Varchar<1>, Numeric, Timestamp, Varchar<15>, Varchar<15>, Integer, Varchar<79>, Integer, Integer, Numeric, Numeric, Numeric, Numeric, Varchar<1>, Varchar<1>, Timestamp, Timestamp, Timestamp, Varchar<25>, Varchar<10>, Varchar<44>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<101>>> v_3;
std::unordered_multimap<std::tuple<Integer, Integer>, std::tuple<Integer, Integer, Varchar<25>, Integer, Varchar<152>, Integer, Integer, Varchar<1>, Numeric, Timestamp, Varchar<15>, Varchar<15>, Integer, Varchar<79>, Integer, Integer, Numeric, Numeric, Numeric, Numeric, Varchar<1>, Varchar<1>, Timestamp, Timestamp, Timestamp, Varchar<25>, Varchar<10>, Varchar<44>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<101>>> v_4;
std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Integer, Varchar<1>, Numeric, Timestamp, Varchar<15>, Varchar<15>, Integer, Varchar<79>, Integer, Integer, Integer, Integer, Numeric, Numeric, Numeric, Numeric, Varchar<1>, Varchar<1>, Timestamp, Timestamp, Timestamp, Varchar<25>, Varchar<10>, Varchar<44>, Integer, Varchar<25>, Varchar<40>, Varchar<15>, Numeric, Varchar<101>>> v_5;
std::unordered_multimap<std::tuple<Integer>, std::tuple<Integer, Integer, Integer, Numeric, Numeric, Numeric, Numeric, Varchar<1>, Varchar<1>, Timestamp, Timestamp, Timestamp, Varchar<25>, Varchar<10>, Varchar<44>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<101>>> v_6;
std::unordered_multimap<std::tuple<Integer>, std::tuple<Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<101>>> v_7;
db->supplier.forEach([&](auto& key, auto& value) {
	Integer v_8 = key.s_suppkey;
	Varchar<25> v_9 = value.s_name;
	Varchar<40> v_10 = value.s_address;
	Integer v_11 = value.s_nationkey;
	Varchar<15> v_12 = value.s_phone;
	Numeric v_13 = value.s_acctbal;
	Varchar<101> v_14 = value.s_comment;
	v_7.insert({{v_8}, {v_9, v_10, v_11, v_12, v_13, v_14}});
});
db->lineitem.forEach([&](auto& key, auto& value) {
	Integer v_15 = key.l_orderkey;
	Integer v_16 = value.l_partkey;
	Integer v_17 = value.l_suppkey;
	Integer v_18 = value.l_linenumber;
	Numeric v_19 = value.l_quantity;
	Numeric v_20 = value.l_extendedprice;
	Numeric v_21 = value.l_discount;
	Numeric v_22 = value.l_tax;
	Varchar<1> v_23 = value.l_returnflag;
	Varchar<1> v_24 = value.l_linestatus;
	Timestamp v_25 = value.l_shipdate;
	Timestamp v_26 = value.l_commitdate;
	Timestamp v_27 = value.l_receiptdate;
	Varchar<25> v_28 = value.l_shipinstruct;
	Varchar<10> v_29 = value.l_shipmode;
	Varchar<44> v_30 = value.l_comment;
	if (v_27 > v_26) {
		for (auto range = v_7.equal_range({v_17}); range.first!=range.second; range.first++) {
			Integer v_8 = std::get<0>(range.first->first);
			Varchar<25> v_9 = std::get<0>(range.first->second);
			Varchar<40> v_10 = std::get<1>(range.first->second);
			Integer v_11 = std::get<2>(range.first->second);
			Varchar<15> v_12 = std::get<3>(range.first->second);
			Numeric v_13 = std::get<4>(range.first->second);
			Varchar<101> v_14 = std::get<5>(range.first->second);
			v_6.insert({{v_15}, {v_16, v_17, v_18, v_19, v_20, v_21, v_22, v_23, v_24, v_25, v_26, v_27, v_28, v_29, v_30, v_8, v_9, v_10, v_11, v_12, v_13, v_14}});
		}
	}
});
db->orders.forEach([&](auto& key, auto& value) {
	Integer v_31 = key.o_orderkey;
	Integer v_32 = value.o_custkey;
	Varchar<1> v_33 = value.o_orderstatus;
	Numeric v_34 = value.o_totalprice;
	Timestamp v_35 = value.o_orderdate;
	Varchar<15> v_36 = value.o_orderpriority;
	Varchar<15> v_37 = value.o_clerk;
	Integer v_38 = value.o_shippriority;
	Varchar<79> v_39 = value.o_comment;
	if (v_33 == "F") {
		for (auto range = v_6.equal_range({v_31}); range.first!=range.second; range.first++) {
			Integer v_15 = std::get<0>(range.first->first);
			Integer v_16 = std::get<0>(range.first->second);
			Integer v_17 = std::get<1>(range.first->second);
			Integer v_18 = std::get<2>(range.first->second);
			Numeric v_19 = std::get<3>(range.first->second);
			Numeric v_20 = std::get<4>(range.first->second);
			Numeric v_21 = std::get<5>(range.first->second);
			Numeric v_22 = std::get<6>(range.first->second);
			Varchar<1> v_23 = std::get<7>(range.first->second);
			Varchar<1> v_24 = std::get<8>(range.first->second);
			Timestamp v_25 = std::get<9>(range.first->second);
			Timestamp v_26 = std::get<10>(range.first->second);
			Timestamp v_27 = std::get<11>(range.first->second);
			Varchar<25> v_28 = std::get<12>(range.first->second);
			Varchar<10> v_29 = std::get<13>(range.first->second);
			Varchar<44> v_30 = std::get<14>(range.first->second);
			Integer v_8 = std::get<15>(range.first->second);
			Varchar<25> v_9 = std::get<16>(range.first->second);
			Varchar<40> v_10 = std::get<17>(range.first->second);
			Integer v_11 = std::get<18>(range.first->second);
			Varchar<15> v_12 = std::get<19>(range.first->second);
			Numeric v_13 = std::get<20>(range.first->second);
			Varchar<101> v_14 = std::get<21>(range.first->second);
			v_5.insert({{v_11}, {v_31, v_32, v_33, v_34, v_35, v_36, v_37, v_38, v_39, v_15, v_16, v_17, v_18, v_19, v_20, v_21, v_22, v_23, v_24, v_25, v_26, v_27, v_28, v_29, v_30, v_8, v_9, v_10, v_12, v_13, v_14}});
		}
	}
});
db->nation.forEach([&](auto& key, auto& value) {
	Integer v_40 = key.n_nationkey;
	Varchar<25> v_41 = value.n_name;
	Integer v_42 = value.n_regionkey;
	Varchar<152> v_43 = value.n_comment;
	if ((v_41 == "SAUDI ARABIA") && (v_41 == "BACKDAD")) {
		for (auto range = v_5.equal_range({v_40}); range.first!=range.second; range.first++) {
			Integer v_11 = std::get<0>(range.first->first);
			Integer v_31 = std::get<0>(range.first->second);
			Integer v_32 = std::get<1>(range.first->second);
			Varchar<1> v_33 = std::get<2>(range.first->second);
			Numeric v_34 = std::get<3>(range.first->second);
			Timestamp v_35 = std::get<4>(range.first->second);
			Varchar<15> v_36 = std::get<5>(range.first->second);
			Varchar<15> v_37 = std::get<6>(range.first->second);
			Integer v_38 = std::get<7>(range.first->second);
			Varchar<79> v_39 = std::get<8>(range.first->second);
			Integer v_15 = std::get<9>(range.first->second);
			Integer v_16 = std::get<10>(range.first->second);
			Integer v_17 = std::get<11>(range.first->second);
			Integer v_18 = std::get<12>(range.first->second);
			Numeric v_19 = std::get<13>(range.first->second);
			Numeric v_20 = std::get<14>(range.first->second);
			Numeric v_21 = std::get<15>(range.first->second);
			Numeric v_22 = std::get<16>(range.first->second);
			Varchar<1> v_23 = std::get<17>(range.first->second);
			Varchar<1> v_24 = std::get<18>(range.first->second);
			Timestamp v_25 = std::get<19>(range.first->second);
			Timestamp v_26 = std::get<20>(range.first->second);
			Timestamp v_27 = std::get<21>(range.first->second);
			Varchar<25> v_28 = std::get<22>(range.first->second);
			Varchar<10> v_29 = std::get<23>(range.first->second);
			Varchar<44> v_30 = std::get<24>(range.first->second);
			Integer v_8 = std::get<25>(range.first->second);
			Varchar<25> v_9 = std::get<26>(range.first->second);
			Varchar<40> v_10 = std::get<27>(range.first->second);
			Varchar<15> v_12 = std::get<28>(range.first->second);
			Numeric v_13 = std::get<29>(range.first->second);
			Varchar<101> v_14 = std::get<30>(range.first->second);
			Integer v_44 = v_11 * 2;
			v_4.insert({{v_17, v_15}, {v_44, v_40, v_41, v_42, v_43, v_31, v_32, v_33, v_34, v_35, v_36, v_37, v_38, v_39, v_16, v_18, v_19, v_20, v_21, v_22, v_23, v_24, v_25, v_26, v_27, v_28, v_29, v_30, v_8, v_9, v_10, v_11, v_12, v_13, v_14}});
		}
	}
});
db->lineitem.forEach([&](auto& key, auto& value) {
	Integer v_45 = key.l_orderkey;
	Integer v_46 = value.l_partkey;
	Integer v_47 = value.l_suppkey;
	Integer v_48 = value.l_linenumber;
	Numeric v_49 = value.l_quantity;
	Numeric v_50 = value.l_extendedprice;
	Numeric v_51 = value.l_discount;
	Numeric v_52 = value.l_tax;
	Varchar<1> v_53 = value.l_returnflag;
	Varchar<1> v_54 = value.l_linestatus;
	Timestamp v_55 = value.l_shipdate;
	Timestamp v_56 = value.l_commitdate;
	Timestamp v_57 = value.l_receiptdate;
	Varchar<25> v_58 = value.l_shipinstruct;
	Varchar<10> v_59 = value.l_shipmode;
	Varchar<44> v_60 = value.l_comment;
	for (auto range = v_4.equal_range({v_47, v_45}); range.first!=range.second; range.first++) {
		Integer v_17 = std::get<0>(range.first->first);
		Integer v_15 = std::get<1>(range.first->first);
		Integer v_44 = std::get<0>(range.first->second);
		Integer v_40 = std::get<1>(range.first->second);
		Varchar<25> v_41 = std::get<2>(range.first->second);
		Integer v_42 = std::get<3>(range.first->second);
		Varchar<152> v_43 = std::get<4>(range.first->second);
		Integer v_31 = std::get<5>(range.first->second);
		Integer v_32 = std::get<6>(range.first->second);
		Varchar<1> v_33 = std::get<7>(range.first->second);
		Numeric v_34 = std::get<8>(range.first->second);
		Timestamp v_35 = std::get<9>(range.first->second);
		Varchar<15> v_36 = std::get<10>(range.first->second);
		Varchar<15> v_37 = std::get<11>(range.first->second);
		Integer v_38 = std::get<12>(range.first->second);
		Varchar<79> v_39 = std::get<13>(range.first->second);
		Integer v_16 = std::get<14>(range.first->second);
		Integer v_18 = std::get<15>(range.first->second);
		Numeric v_19 = std::get<16>(range.first->second);
		Numeric v_20 = std::get<17>(range.first->second);
		Numeric v_21 = std::get<18>(range.first->second);
		Numeric v_22 = std::get<19>(range.first->second);
		Varchar<1> v_23 = std::get<20>(range.first->second);
		Varchar<1> v_24 = std::get<21>(range.first->second);
		Timestamp v_25 = std::get<22>(range.first->second);
		Timestamp v_26 = std::get<23>(range.first->second);
		Timestamp v_27 = std::get<24>(range.first->second);
		Varchar<25> v_28 = std::get<25>(range.first->second);
		Varchar<10> v_29 = std::get<26>(range.first->second);
		Varchar<44> v_30 = std::get<27>(range.first->second);
		Integer v_8 = std::get<28>(range.first->second);
		Varchar<25> v_9 = std::get<29>(range.first->second);
		Varchar<40> v_10 = std::get<30>(range.first->second);
		Integer v_11 = std::get<31>(range.first->second);
		Varchar<15> v_12 = std::get<32>(range.first->second);
		Numeric v_13 = std::get<33>(range.first->second);
		Varchar<101> v_14 = std::get<34>(range.first->second);
		v_3.insert({{v_17, v_15}, {v_45, v_46, v_47, v_48, v_49, v_50, v_51, v_52, v_53, v_54, v_55, v_56, v_57, v_58, v_59, v_60, v_44, v_40, v_41, v_42, v_43, v_31, v_32, v_33, v_34, v_35, v_36, v_37, v_38, v_39, v_16, v_18, v_19, v_20, v_21, v_22, v_23, v_24, v_25, v_26, v_27, v_28, v_29, v_30, v_8, v_9, v_10, v_11, v_12, v_13, v_14}});
	}
});
db->lineitem.forEach([&](auto& key, auto& value) {
	Integer v_61 = key.l_orderkey;
	Integer v_62 = value.l_partkey;
	Integer v_63 = value.l_suppkey;
	Integer v_64 = value.l_linenumber;
	Numeric v_65 = value.l_quantity;
	Numeric v_66 = value.l_extendedprice;
	Numeric v_67 = value.l_discount;
	Numeric v_68 = value.l_tax;
	Varchar<1> v_69 = value.l_returnflag;
	Varchar<1> v_70 = value.l_linestatus;
	Timestamp v_71 = value.l_shipdate;
	Timestamp v_72 = value.l_commitdate;
	Timestamp v_73 = value.l_receiptdate;
	Varchar<25> v_74 = value.l_shipinstruct;
	Varchar<10> v_75 = value.l_shipmode;
	Varchar<44> v_76 = value.l_comment;
	for (auto range = v_3.equal_range({v_63, v_61}); range.first!=range.second; range.first++) {
		Integer v_17 = std::get<0>(range.first->first);
		Integer v_15 = std::get<1>(range.first->first);
		Integer v_45 = std::get<0>(range.first->second);
		Integer v_46 = std::get<1>(range.first->second);
		Integer v_47 = std::get<2>(range.first->second);
		Integer v_48 = std::get<3>(range.first->second);
		Numeric v_49 = std::get<4>(range.first->second);
		Numeric v_50 = std::get<5>(range.first->second);
		Numeric v_51 = std::get<6>(range.first->second);
		Numeric v_52 = std::get<7>(range.first->second);
		Varchar<1> v_53 = std::get<8>(range.first->second);
		Varchar<1> v_54 = std::get<9>(range.first->second);
		Timestamp v_55 = std::get<10>(range.first->second);
		Timestamp v_56 = std::get<11>(range.first->second);
		Timestamp v_57 = std::get<12>(range.first->second);
		Varchar<25> v_58 = std::get<13>(range.first->second);
		Varchar<10> v_59 = std::get<14>(range.first->second);
		Varchar<44> v_60 = std::get<15>(range.first->second);
		Integer v_44 = std::get<16>(range.first->second);
		Integer v_40 = std::get<17>(range.first->second);
		Varchar<25> v_41 = std::get<18>(range.first->second);
		Integer v_42 = std::get<19>(range.first->second);
		Varchar<152> v_43 = std::get<20>(range.first->second);
		Integer v_31 = std::get<21>(range.first->second);
		Integer v_32 = std::get<22>(range.first->second);
		Varchar<1> v_33 = std::get<23>(range.first->second);
		Numeric v_34 = std::get<24>(range.first->second);
		Timestamp v_35 = std::get<25>(range.first->second);
		Varchar<15> v_36 = std::get<26>(range.first->second);
		Varchar<15> v_37 = std::get<27>(range.first->second);
		Integer v_38 = std::get<28>(range.first->second);
		Varchar<79> v_39 = std::get<29>(range.first->second);
		Integer v_16 = std::get<30>(range.first->second);
		Integer v_18 = std::get<31>(range.first->second);
		Numeric v_19 = std::get<32>(range.first->second);
		Numeric v_20 = std::get<33>(range.first->second);
		Numeric v_21 = std::get<34>(range.first->second);
		Numeric v_22 = std::get<35>(range.first->second);
		Varchar<1> v_23 = std::get<36>(range.first->second);
		Varchar<1> v_24 = std::get<37>(range.first->second);
		Timestamp v_25 = std::get<38>(range.first->second);
		Timestamp v_26 = std::get<39>(range.first->second);
		Timestamp v_27 = std::get<40>(range.first->second);
		Varchar<25> v_28 = std::get<41>(range.first->second);
		Varchar<10> v_29 = std::get<42>(range.first->second);
		Varchar<44> v_30 = std::get<43>(range.first->second);
		Integer v_8 = std::get<44>(range.first->second);
		Varchar<25> v_9 = std::get<45>(range.first->second);
		Varchar<40> v_10 = std::get<46>(range.first->second);
		Integer v_11 = std::get<47>(range.first->second);
		Varchar<15> v_12 = std::get<48>(range.first->second);
		Numeric v_13 = std::get<49>(range.first->second);
		Varchar<101> v_14 = std::get<50>(range.first->second);
		auto it = v_2.find({v_9});
		if (it == v_2.end()) {
			v_2.insert({{v_9}, {1}});
		} else {
			std::get<0>(it->second) += 1;
		}
	}
});
for (auto& it : v_2) {
	Varchar<25> v_77 = std::get<0>(it.first);
	Integer v_78 = std::get<0>(it.second);
	v_1.push_back({v_78, v_77, v_78, v_77});
}
std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) { return t1 < t2; });
for (auto& t : v_1) {
	Integer v_78 = std::get<2>(t);
	Varchar<25> v_77 = std::get<3>(t);
	std::cout << v_78 << ", " << v_77 << std::endl;
}

