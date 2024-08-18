db->partsupp.forEach([&](auto& key, auto& value) {
	Integer v_1 = key.ps_partkey;
	Integer v_2 = key.ps_suppkey;
	Integer v_3 = value.ps_availqty;
	Numeric v_4 = value.ps_supplycost;
	Varchar<199> v_5 = value.ps_comment;
	db->part.lookup1({v_1}, [&](auto& value) {
		Integer v_6 = v_1;
		Varchar<55> v_7 = value.p_name;
		Varchar<25> v_8 = value.p_mfgr;
		Varchar<10> v_9 = value.p_brand;
		Varchar<25> v_10 = value.p_type;
		Integer v_11 = value.p_size;
		Varchar<10> v_12 = value.p_container;
		Numeric v_13 = value.p_retailprice;
		Varchar<23> v_14 = value.p_comment;
		std::cout << v_1 << ", " << v_2 << ", " << v_3 << ", " << v_4 << ", " << v_5 << ", " << v_6 << ", " << v_7 << ", " << v_8 << ", " << v_9 << ", " << v_10 << ", " << v_11 << ", " << v_12 << ", " << v_13 << ", " << v_14 << std::endl;
	});
});

