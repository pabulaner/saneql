using namespace adapter;
int v_1;
Varchar<10> v_2;
Varchar<20> v_3;
Varchar<20> v_4;
Varchar<20> v_5;
Varchar<2> v_6;
Varchar<9> v_7;
double v_8;
double v_9;
OutputOp c_1([&]() {
	std::cout << v_1 << ", " << v_2.toString() << ", " << v_3.toString() << ", " << v_4.toString() << ", " << v_5.toString() << ", " << v_6.toString() << ", " << v_7.toString() << ", " << v_8 << ", " << v_9 << std::endl;
});
ScanOp c_2(&c_1, db->warehouse, [&](const warehouse_t::Key& key, const warehouse_t& value) {
	v_1 = key.w_id;
	v_2 = value.w_name;
	v_3 = value.w_street_1;
	v_4 = value.w_street_2;
	v_5 = value.w_city;
	v_6 = value.w_state;
	v_7 = value.w_zip;
	v_8 = value.w_tax;
	v_9 = value.w_ytd;
});
c_2.process();

