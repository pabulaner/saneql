int64_t row28 = 0;
std::cout << "[QUERY_BEGIN]" << std::endl;
std::cout << "w_id,";std::cout << "w_name,";std::cout << "w_street_1,";std::cout << "w_street_2,";std::cout << "w_city,";std::cout << "w_state,";std::cout << "w_zip,";std::cout << "w_tax,";std::cout << "w_ytd,";std::cout << "s_w_id,";std::cout << "s_i_id,";std::cout << "s_quantity,";std::cout << "s_dist_01,";std::cout << "s_dist_02,";std::cout << "s_dist_03,";std::cout << "s_dist_04,";std::cout << "s_dist_05,";std::cout << "s_dist_06,";std::cout << "s_dist_07,";std::cout << "s_dist_08,";std::cout << "s_dist_09,";std::cout << "s_dist_10,";std::cout << "s_ytd,";std::cout << "s_order_cnt,";std::cout << "s_remote_cnt,";std::cout << "s_data,";std::cout << std::endl;
unordered_multimap<tuple<int>, tuple<Varchar<10>,Varchar<20>,Varchar<20>,Varchar<20>,Varchar<2>,Varchar<9>,double,double>> joinHT27;
db->warehouse.forEach([&](auto& key, auto& value){ //227; virtual void p2c::Scan::produce(const p2c::IUSet&, p2c::ConsumerFn)
int w_id1 = key.w_id;
Varchar<10> w_name2 = value.w_name;
Varchar<20> w_street_13 = value.w_street_1;
Varchar<20> w_street_24 = value.w_street_2;
Varchar<20> w_city5 = value.w_city;
Varchar<2> w_state6 = value.w_state;
Varchar<9> w_zip7 = value.w_zip;
double w_tax8 = value.w_tax;
double w_ytd9 = value.w_ytd;
if (w_name2 == "e03gy9m"){ //277; p2c::Selection::produce(const p2c::IUSet&, p2c::ConsumerFn)::<lambda()>
joinHT27.insert({{w_id1}, {w_name2,w_street_13,w_street_24,w_city5,w_state6,w_zip7,w_tax8,w_ytd9}});
}
}
);db->stock.forEach([&](auto& key, auto& value){ //227; virtual void p2c::Scan::produce(const p2c::IUSet&, p2c::ConsumerFn)
int s_w_id10 = key.s_w_id;
int s_i_id11 = key.s_i_id;
double s_quantity12 = value.s_quantity;
Varchar<24> s_dist_0113 = value.s_dist_01;
Varchar<24> s_dist_0214 = value.s_dist_02;
Varchar<24> s_dist_0315 = value.s_dist_03;
Varchar<24> s_dist_0416 = value.s_dist_04;
Varchar<24> s_dist_0517 = value.s_dist_05;
Varchar<24> s_dist_0618 = value.s_dist_06;
Varchar<24> s_dist_0719 = value.s_dist_07;
Varchar<24> s_dist_0820 = value.s_dist_08;
Varchar<24> s_dist_0921 = value.s_dist_09;
Varchar<24> s_dist_1022 = value.s_dist_10;
double s_ytd23 = value.s_ytd;
double s_order_cnt24 = value.s_order_cnt;
double s_remote_cnt25 = value.s_remote_cnt;
Varchar<50> s_data26 = value.s_data;
for (auto range = joinHT27.equal_range({s_w_id10}); range.first!=range.second; range.first++){ //513; p2c::HashJoin::produce(const p2c::IUSet&, p2c::ConsumerFn)::<lambda()>
Varchar<10> w_name2 = get<0>(range.first->second);
Varchar<20> w_street_13 = get<1>(range.first->second);
Varchar<20> w_street_24 = get<2>(range.first->second);
Varchar<20> w_city5 = get<3>(range.first->second);
Varchar<2> w_state6 = get<4>(range.first->second);
Varchar<9> w_zip7 = get<5>(range.first->second);
double w_tax8 = get<6>(range.first->second);
double w_ytd9 = get<7>(range.first->second);
int w_id1 = get<0>(range.first->first);
if (row28 >= 0){ //76; p2c::produceAndPrint(std::unique_ptr<Operator>, const std::vector<IU*>&, unsigned int, uint64_t, int64_t)::<lambda()>
std::cout << w_id1 << ",";std::cout << w_name2 << ",";std::cout << w_street_13 << ",";std::cout << w_street_24 << ",";std::cout << w_city5 << ",";std::cout << w_state6 << ",";std::cout << w_zip7 << ",";std::cout << w_tax8 << ",";std::cout << w_ytd9 << ",";std::cout << s_w_id10 << ",";std::cout << s_i_id11 << ",";std::cout << s_quantity12 << ",";std::cout << s_dist_0113 << ",";std::cout << s_dist_0214 << ",";std::cout << s_dist_0315 << ",";std::cout << s_dist_0416 << ",";std::cout << s_dist_0517 << ",";std::cout << s_dist_0618 << ",";std::cout << s_dist_0719 << ",";std::cout << s_dist_0820 << ",";std::cout << s_dist_0921 << ",";std::cout << s_dist_1022 << ",";std::cout << s_ytd23 << ",";std::cout << s_order_cnt24 << ",";std::cout << s_remote_cnt25 << ",";std::cout << s_data26 << ",";std::cout << std::endl;
}
row28++;}
}
);std::cout << "[QUERY_END]" << std::endl;
