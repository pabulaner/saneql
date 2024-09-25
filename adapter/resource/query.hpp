std::map<std::string, std::map<std::string, std::function<void(Database*, size_t)>>> queries = {
	{"none", {
	{"./query/query2.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "s_suppkey" << ", " << "s_name" << ", " << "s_address" << ", " << "s_nationkey" << ", " << "s_phone" << ", " << "s_acctbal" << ", " << "s_comment" << ", " << "l_orderkey" << ", " << "l_partkey" << ", " << "l_suppkey" << ", " << "l_linenumber" << ", " << "l_quantity" << ", " << "l_extendedprice" << ", " << "l_discount" << ", " << "l_tax" << ", " << "l_returnflag" << ", " << "l_linestatus" << ", " << "l_shipdate" << ", " << "l_commitdate" << ", " << "l_receiptdate" << ", " << "l_shipinstruct" << ", " << "l_shipmode" << ", " << "l_comment" << std::endl;
		}
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<101>>> v_1;
		db->supplier_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_2 = key.s_suppkey;
			const Varchar<25>& v_3 = value.s_name;
			const Varchar<40>& v_4 = value.s_address;
			const Integer& v_5 = value.s_nationkey;
			const Varchar<15>& v_6 = value.s_phone;
			const Numeric& v_7 = value.s_acctbal;
			const Varchar<101>& v_8 = value.s_comment;
			v_1.insert({{v_2}, {v_3, v_4, v_5, v_6, v_7, v_8}});
		});
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_9 = key.l_orderkey;
			const Integer& v_10 = key.l_partkey;
			const Integer& v_11 = key.l_suppkey;
			const Integer& v_12 = value.l_linenumber;
			const Numeric& v_13 = value.l_quantity;
			const Numeric& v_14 = value.l_extendedprice;
			const Numeric& v_15 = value.l_discount;
			const Numeric& v_16 = value.l_tax;
			const Varchar<1>& v_17 = value.l_returnflag;
			const Varchar<1>& v_18 = value.l_linestatus;
			const Timestamp& v_19 = value.l_shipdate;
			const Timestamp& v_20 = value.l_commitdate;
			const Timestamp& v_21 = value.l_receiptdate;
			const Varchar<25>& v_22 = value.l_shipinstruct;
			const Varchar<10>& v_23 = value.l_shipmode;
			const Varchar<44>& v_24 = value.l_comment;
			for (auto range = v_1.equal_range({v_11}); range.first!=range.second; range.first++) {
				const Integer& v_2 = std::get<0>(range.first->first);
				const Varchar<25>& v_3 = std::get<0>(range.first->second);
				const Varchar<40>& v_4 = std::get<1>(range.first->second);
				const Integer& v_5 = std::get<2>(range.first->second);
				const Varchar<15>& v_6 = std::get<3>(range.first->second);
				const Numeric& v_7 = std::get<4>(range.first->second);
				const Varchar<101>& v_8 = std::get<5>(range.first->second);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_2 << ", " << v_3 << ", " << v_4 << ", " << v_5 << ", " << v_6 << ", " << v_7 << ", " << v_8 << ", " << v_9 << ", " << v_10 << ", " << v_11 << ", " << v_12 << ", " << v_13 << ", " << v_14 << ", " << v_15 << ", " << v_16 << ", " << v_17 << ", " << v_18 << ", " << v_19 << ", " << v_20 << ", " << v_21 << ", " << v_22 << ", " << v_23 << ", " << v_24 << std::endl;
				}
			}
		});
	}},
}},
	{"selects", {
	{"./query/query2.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "s_suppkey" << ", " << "s_name" << ", " << "s_address" << ", " << "s_nationkey" << ", " << "s_phone" << ", " << "s_acctbal" << ", " << "s_comment" << ", " << "l_orderkey" << ", " << "l_partkey" << ", " << "l_suppkey" << ", " << "l_linenumber" << ", " << "l_quantity" << ", " << "l_extendedprice" << ", " << "l_discount" << ", " << "l_tax" << ", " << "l_returnflag" << ", " << "l_linestatus" << ", " << "l_shipdate" << ", " << "l_commitdate" << ", " << "l_receiptdate" << ", " << "l_shipinstruct" << ", " << "l_shipmode" << ", " << "l_comment" << std::endl;
		}
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<101>>> v_1;
		db->supplier_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_2 = key.s_suppkey;
			const Varchar<25>& v_3 = value.s_name;
			const Varchar<40>& v_4 = value.s_address;
			const Integer& v_5 = value.s_nationkey;
			const Varchar<15>& v_6 = value.s_phone;
			const Numeric& v_7 = value.s_acctbal;
			const Varchar<101>& v_8 = value.s_comment;
			v_1.insert({{v_2}, {v_3, v_4, v_5, v_6, v_7, v_8}});
		});
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_9 = key.l_orderkey;
			const Integer& v_10 = key.l_partkey;
			const Integer& v_11 = key.l_suppkey;
			const Integer& v_12 = value.l_linenumber;
			const Numeric& v_13 = value.l_quantity;
			const Numeric& v_14 = value.l_extendedprice;
			const Numeric& v_15 = value.l_discount;
			const Numeric& v_16 = value.l_tax;
			const Varchar<1>& v_17 = value.l_returnflag;
			const Varchar<1>& v_18 = value.l_linestatus;
			const Timestamp& v_19 = value.l_shipdate;
			const Timestamp& v_20 = value.l_commitdate;
			const Timestamp& v_21 = value.l_receiptdate;
			const Varchar<25>& v_22 = value.l_shipinstruct;
			const Varchar<10>& v_23 = value.l_shipmode;
			const Varchar<44>& v_24 = value.l_comment;
			for (auto range = v_1.equal_range({v_11}); range.first!=range.second; range.first++) {
				const Integer& v_2 = std::get<0>(range.first->first);
				const Varchar<25>& v_3 = std::get<0>(range.first->second);
				const Varchar<40>& v_4 = std::get<1>(range.first->second);
				const Integer& v_5 = std::get<2>(range.first->second);
				const Varchar<15>& v_6 = std::get<3>(range.first->second);
				const Numeric& v_7 = std::get<4>(range.first->second);
				const Varchar<101>& v_8 = std::get<5>(range.first->second);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_2 << ", " << v_3 << ", " << v_4 << ", " << v_5 << ", " << v_6 << ", " << v_7 << ", " << v_8 << ", " << v_9 << ", " << v_10 << ", " << v_11 << ", " << v_12 << ", " << v_13 << ", " << v_14 << ", " << v_15 << ", " << v_16 << ", " << v_17 << ", " << v_18 << ", " << v_19 << ", " << v_20 << ", " << v_21 << ", " << v_22 << ", " << v_23 << ", " << v_24 << std::endl;
				}
			}
		});
	}},
}},
	{"scans", {
	{"./query/query2.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "s_suppkey" << ", " << "s_name" << ", " << "s_address" << ", " << "s_nationkey" << ", " << "s_phone" << ", " << "s_acctbal" << ", " << "s_comment" << ", " << "l_orderkey" << ", " << "l_partkey" << ", " << "l_suppkey" << ", " << "l_linenumber" << ", " << "l_quantity" << ", " << "l_extendedprice" << ", " << "l_discount" << ", " << "l_tax" << ", " << "l_returnflag" << ", " << "l_linestatus" << ", " << "l_shipdate" << ", " << "l_commitdate" << ", " << "l_receiptdate" << ", " << "l_shipinstruct" << ", " << "l_shipmode" << ", " << "l_comment" << std::endl;
		}
		std::unordered_multimap<std::tuple<Integer>, std::tuple<Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<101>>> v_1;
		db->supplier_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_2 = key.s_suppkey;
			const Varchar<25>& v_3 = value.s_name;
			const Varchar<40>& v_4 = value.s_address;
			const Integer& v_5 = value.s_nationkey;
			const Varchar<15>& v_6 = value.s_phone;
			const Numeric& v_7 = value.s_acctbal;
			const Varchar<101>& v_8 = value.s_comment;
			v_1.insert({{v_2}, {v_3, v_4, v_5, v_6, v_7, v_8}});
		});
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_9 = key.l_orderkey;
			const Integer& v_10 = key.l_partkey;
			const Integer& v_11 = key.l_suppkey;
			const Integer& v_12 = value.l_linenumber;
			const Numeric& v_13 = value.l_quantity;
			const Numeric& v_14 = value.l_extendedprice;
			const Numeric& v_15 = value.l_discount;
			const Numeric& v_16 = value.l_tax;
			const Varchar<1>& v_17 = value.l_returnflag;
			const Varchar<1>& v_18 = value.l_linestatus;
			const Timestamp& v_19 = value.l_shipdate;
			const Timestamp& v_20 = value.l_commitdate;
			const Timestamp& v_21 = value.l_receiptdate;
			const Varchar<25>& v_22 = value.l_shipinstruct;
			const Varchar<10>& v_23 = value.l_shipmode;
			const Varchar<44>& v_24 = value.l_comment;
			for (auto range = v_1.equal_range({v_11}); range.first!=range.second; range.first++) {
				const Integer& v_2 = std::get<0>(range.first->first);
				const Varchar<25>& v_3 = std::get<0>(range.first->second);
				const Varchar<40>& v_4 = std::get<1>(range.first->second);
				const Integer& v_5 = std::get<2>(range.first->second);
				const Varchar<15>& v_6 = std::get<3>(range.first->second);
				const Numeric& v_7 = std::get<4>(range.first->second);
				const Varchar<101>& v_8 = std::get<5>(range.first->second);
				if (limit > 0) {
					limit -= 1;
					std::cout << v_2 << ", " << v_3 << ", " << v_4 << ", " << v_5 << ", " << v_6 << ", " << v_7 << ", " << v_8 << ", " << v_9 << ", " << v_10 << ", " << v_11 << ", " << v_12 << ", " << v_13 << ", " << v_14 << ", " << v_15 << ", " << v_16 << ", " << v_17 << ", " << v_18 << ", " << v_19 << ", " << v_20 << ", " << v_21 << ", " << v_22 << ", " << v_23 << ", " << v_24 << std::endl;
				}
			}
		});
	}},
}},
	{"joins", {
	{"./query/query2.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "s_suppkey" << ", " << "s_name" << ", " << "s_address" << ", " << "s_nationkey" << ", " << "s_phone" << ", " << "s_acctbal" << ", " << "s_comment" << ", " << "l_orderkey" << ", " << "l_partkey" << ", " << "l_suppkey" << ", " << "l_linenumber" << ", " << "l_quantity" << ", " << "l_extendedprice" << ", " << "l_discount" << ", " << "l_tax" << ", " << "l_returnflag" << ", " << "l_linestatus" << ", " << "l_shipdate" << ", " << "l_commitdate" << ", " << "l_receiptdate" << ", " << "l_shipinstruct" << ", " << "l_shipmode" << ", " << "l_comment" << std::endl;
		}
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_1 = key.l_orderkey;
			const Integer& v_2 = key.l_partkey;
			const Integer& v_3 = key.l_suppkey;
			const Integer& v_4 = value.l_linenumber;
			const Numeric& v_5 = value.l_quantity;
			const Numeric& v_6 = value.l_extendedprice;
			const Numeric& v_7 = value.l_discount;
			const Numeric& v_8 = value.l_tax;
			const Varchar<1>& v_9 = value.l_returnflag;
			const Varchar<1>& v_10 = value.l_linestatus;
			const Timestamp& v_11 = value.l_shipdate;
			const Timestamp& v_12 = value.l_commitdate;
			const Timestamp& v_13 = value.l_receiptdate;
			const Varchar<25>& v_14 = value.l_shipinstruct;
			const Varchar<10>& v_15 = value.l_shipmode;
			const Varchar<44>& v_16 = value.l_comment;
			db->supplier_tpch.lookup1({v_3}, [&](auto& value) {
				Integer v_17 = v_3;
				Varchar<25> v_18 = value.s_name;
				Varchar<40> v_19 = value.s_address;
				Integer v_20 = value.s_nationkey;
				Varchar<15> v_21 = value.s_phone;
				Numeric v_22 = value.s_acctbal;
				Varchar<101> v_23 = value.s_comment;
				if (limit > 0) {
					limit -= 1;
					std::cout << v_17 << ", " << v_18 << ", " << v_19 << ", " << v_20 << ", " << v_21 << ", " << v_22 << ", " << v_23 << ", " << v_1 << ", " << v_2 << ", " << v_3 << ", " << v_4 << ", " << v_5 << ", " << v_6 << ", " << v_7 << ", " << v_8 << ", " << v_9 << ", " << v_10 << ", " << v_11 << ", " << v_12 << ", " << v_13 << ", " << v_14 << ", " << v_15 << ", " << v_16 << std::endl;
				}
			});
		});
	}},
}},
	{"all", {
	{"./query/query2.sane", [](Database* db, size_t limit) {
		if (limit > 0) {
			std::cout << "s_suppkey" << ", " << "s_name" << ", " << "s_address" << ", " << "s_nationkey" << ", " << "s_phone" << ", " << "s_acctbal" << ", " << "s_comment" << ", " << "l_orderkey" << ", " << "l_partkey" << ", " << "l_suppkey" << ", " << "l_linenumber" << ", " << "l_quantity" << ", " << "l_extendedprice" << ", " << "l_discount" << ", " << "l_tax" << ", " << "l_returnflag" << ", " << "l_linestatus" << ", " << "l_shipdate" << ", " << "l_commitdate" << ", " << "l_receiptdate" << ", " << "l_shipinstruct" << ", " << "l_shipmode" << ", " << "l_comment" << std::endl;
		}
		db->lineitem_tpch.forEach([&](auto& key, auto& value) {
			const Integer& v_1 = key.l_orderkey;
			const Integer& v_2 = key.l_partkey;
			const Integer& v_3 = key.l_suppkey;
			const Integer& v_4 = value.l_linenumber;
			const Numeric& v_5 = value.l_quantity;
			const Numeric& v_6 = value.l_extendedprice;
			const Numeric& v_7 = value.l_discount;
			const Numeric& v_8 = value.l_tax;
			const Varchar<1>& v_9 = value.l_returnflag;
			const Varchar<1>& v_10 = value.l_linestatus;
			const Timestamp& v_11 = value.l_shipdate;
			const Timestamp& v_12 = value.l_commitdate;
			const Timestamp& v_13 = value.l_receiptdate;
			const Varchar<25>& v_14 = value.l_shipinstruct;
			const Varchar<10>& v_15 = value.l_shipmode;
			const Varchar<44>& v_16 = value.l_comment;
			db->supplier_tpch.lookup1({v_3}, [&](auto& value) {
				Integer v_17 = v_3;
				Varchar<25> v_18 = value.s_name;
				Varchar<40> v_19 = value.s_address;
				Integer v_20 = value.s_nationkey;
				Varchar<15> v_21 = value.s_phone;
				Numeric v_22 = value.s_acctbal;
				Varchar<101> v_23 = value.s_comment;
				if (limit > 0) {
					limit -= 1;
					std::cout << v_17 << ", " << v_18 << ", " << v_19 << ", " << v_20 << ", " << v_21 << ", " << v_22 << ", " << v_23 << ", " << v_1 << ", " << v_2 << ", " << v_3 << ", " << v_4 << ", " << v_5 << ", " << v_6 << ", " << v_7 << ", " << v_8 << ", " << v_9 << ", " << v_10 << ", " << v_11 << ", " << v_12 << ", " << v_13 << ", " << v_14 << ", " << v_15 << ", " << v_16 << std::endl;
				}
			});
		});
	}},
}},
};
