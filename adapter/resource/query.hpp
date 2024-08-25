db->nation_tpch.forEach([&](auto& key, auto& value) {
	Integer v_1 = key.n_nationkey;
	Varchar<25> v_2 = value.n_name;
	Integer v_3 = value.n_regionkey;
	Varchar<152> v_4 = value.n_comment;
	Varchar<31> v_5 = Varchar<6>("name: ") || v_2;
	std::cout << v_5 << ", " << v_1 << ", " << v_2 << ", " << v_3 << ", " << v_4 << std::endl;
});

