std::vector<std::tuple<Varchar<25>, Integer, Varchar<25>, Varchar<40>, Integer, Varchar<15>, Numeric, Varchar<10>, Varchar<117>>> v_1;
db->customer_tpch.forEach([&](auto& key, auto& value) {
	Integer v_2 = key.c_custkey;
	Varchar<25> v_3 = value.c_name;
	Varchar<40> v_4 = value.c_address;
	Integer v_5 = value.c_nationkey;
	Varchar<15> v_6 = value.c_phone;
	Numeric v_7 = value.c_acctbal;
	Varchar<10> v_8 = value.c_mktsegment;
	Varchar<117> v_9 = value.c_comment;
	v_1.push_back({v_3, v_2, v_3, v_4, v_5, v_6, v_7, v_8, v_9});
});
std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) { return t1 < t2; });
for (auto& t : v_1) {
	Integer v_2 = std::get<1>(t);
	Varchar<25> v_3 = std::get<2>(t);
	Varchar<40> v_4 = std::get<3>(t);
	Integer v_5 = std::get<4>(t);
	Varchar<15> v_6 = std::get<5>(t);
	Numeric v_7 = std::get<6>(t);
	Varchar<10> v_8 = std::get<7>(t);
	Varchar<117> v_9 = std::get<8>(t);
	std::cout << v_2 << ", " << v_3 << ", " << v_4 << ", " << v_5 << ", " << v_6 << ", " << v_7 << ", " << v_8 << ", " << v_9 << std::endl;
}

