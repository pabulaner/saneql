db->part_tpch.forEach([&](auto& key, auto& value) {
	Integer v_1 = key.p_partkey;
	Varchar<55> v_2 = value.p_name;
	Varchar<25> v_3 = value.p_mfgr;
	Varchar<10> v_4 = value.p_brand;
	Varchar<25> v_5 = value.p_type;
	Integer v_6 = value.p_size;
	Varchar<10> v_7 = value.p_container;
	Numeric v_8 = value.p_retailprice;
	Varchar<23> v_9 = value.p_comment;
	db->partsupp_tpch.lookup1({v_1}, [&](auto& value) {
		Integer v_10 = v_1;
		Integer v_11 = value.ps_suppkey;
		Integer v_12 = value.ps_availqty;
		Numeric v_13 = value.ps_supplycost;
		Varchar<199> v_14 = value.ps_comment;
		std::cout << v_1 << ", " << v_2 << ", " << v_3 << ", " << v_4 << ", " << v_5 << ", " << v_6 << ", " << v_7 << ", " << v_8 << ", " << v_9 << ", " << v_10 << ", " << v_11 << ", " << v_12 << ", " << v_13 << ", " << v_14 << std::endl;
	});
});

