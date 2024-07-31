int64_t row10 = 0;
std::cout << "[QUERY_BEGIN]" << std::endl;
std::cout << "w_id,";std::cout << "w_name,";std::cout << "w_street_1,";std::cout << "w_street_2,";std::cout << "w_city,";std::cout << "w_state,";std::cout << "w_zip,";std::cout << "w_tax,";std::cout << "w_ytd,";std::cout << std::endl;
db->warehouse.forEach([&](auto& key, auto& value){ //232; virtual void p2c::Scan::produce(const p2c::IUSet&, p2c::ConsumerFn)
int w_id1 = key.w_id;
Varchar<10> w_name2 = value.w_name;
Varchar<20> w_street_13 = value.w_street_1;
Varchar<20> w_street_24 = value.w_street_2;
Varchar<20> w_city5 = value.w_city;
Varchar<2> w_state6 = value.w_state;
Varchar<9> w_zip7 = value.w_zip;
double w_tax8 = value.w_tax;
double w_ytd9 = value.w_ytd;
if (row10 >= 0){ //76; p2c::produceAndPrint(std::unique_ptr<Operator>, const std::vector<IU*>&, unsigned int, uint64_t, int64_t)::<lambda()>
std::cout << w_id1 << ",";std::cout << w_name2 << ",";std::cout << w_street_13 << ",";std::cout << w_street_24 << ",";std::cout << w_city5 << ",";std::cout << w_state6 << ",";std::cout << w_zip7 << ",";std::cout << w_tax8 << ",";std::cout << w_ytd9 << ",";std::cout << std::endl;
}
row10++;}
);std::cout << "[QUERY_END]" << std::endl;
