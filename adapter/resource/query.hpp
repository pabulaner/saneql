struct c_2 {
	int v_1;
	Varchar<10> v_2;
	Varchar<20> v_3;
	Varchar<20> v_4;
	Varchar<20> v_5;
	Varchar<2> v_6;
	Varchar<9> v_7;
	double v_8;
	double v_9;
};
int v_1;
Varchar<10> v_2;
Varchar<20> v_3;
Varchar<20> v_4;
Varchar<20> v_5;
Varchar<2> v_6;
Varchar<9> v_7;
double v_8;
double v_9;
int v_10;
int v_11;
int v_12;
Varchar<10> v_13;
Varchar<20> v_14;
Varchar<20> v_15;
Varchar<20> v_16;
Varchar<2> v_17;
Varchar<9> v_18;
double v_19;
double v_20;
int v_21;
OutputOp c_1([&]() {
	std::cout << v_1 << ", " << v_2.toString() << ", " << v_3.toString() << ", " << v_4.toString() << ", " << v_5.toString() << ", " << v_6.toString() << ", " << v_7.toString() << ", " << v_8 << ", " << v_9 << ", " << v_10 << ", " << v_11 << ", " << v_12 << ", " << v_13.toString() << ", " << v_14.toString() << ", " << v_15.toString() << ", " << v_16.toString() << ", " << v_17.toString() << ", " << v_18.toString() << ", " << v_19 << ", " << v_20 << ", " << v_21 << std::endl;
});
JoinOp c_3(&c_1, c_2{}, [&]() {
	return c_2{v_1, v_2, v_3, v_4, v_5, v_6, v_7, v_8, v_9};
}, [&](const c_2& row) {
	v_1 = row.v_1;
	v_2 = row.v_2;
	v_3 = row.v_3;
	v_4 = row.v_4;
	v_5 = row.v_5;
	v_6 = row.v_6;
	v_7 = row.v_7;
	v_8 = row.v_8;
	v_9 = row.v_9;
}, [&]() {
	return v_11 == v_1;
});
MapOp c_4(&c_3, [&]() {
	v_10 = v_1 * 2;
});
SelectOp c_5(&c_4, [&]() {
	return v_1 == 1;
});
ScanOp c_6(&c_5, &(db->warehouse), [&](const warehouse_t::Key& key, const warehouse_t& value) {
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
ScanOp c_7(&c_3, &(db->district), [&](const district_t::Key& key, const district_t& value) {
	v_11 = key.d_w_id;
	v_12 = key.d_id;
	v_13 = value.d_name;
	v_14 = value.d_street_1;
	v_15 = value.d_street_2;
	v_16 = value.d_city;
	v_17 = value.d_state;
	v_18 = value.d_zip;
	v_19 = value.d_tax;
	v_20 = value.d_ytd;
	v_21 = value.d_next_o_id;
});
c_6.process();
c_7.process();

