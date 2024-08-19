db->warehouse.forEach([&](auto& key, auto& value) {
	Integer v_1 = key.w_id;
	Varchar<10> v_2 = value.w_name;
	Varchar<20> v_3 = value.w_street_1;
	Varchar<20> v_4 = value.w_street_2;
	Varchar<20> v_5 = value.w_city;
	Varchar<2> v_6 = value.w_state;
	Varchar<9> v_7 = value.w_zip;
	Numeric v_8 = value.w_tax;
	Numeric v_9 = value.w_ytd;
	std::cout << v_1 << ", " << v_2 << ", " << v_3 << ", " << v_4 << ", " << v_5 << ", " << v_6 << ", " << v_7 << ", " << v_8 << ", " << v_9 << std::endl;
});

