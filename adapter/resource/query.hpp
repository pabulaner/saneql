int64_t row10 = 0;
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
if (w_id1 > 5){ //282; p2c::Selection::produce(const p2c::IUSet&, p2c::ConsumerFn)::<lambda()>
if (row10 >= 0){ //71; p2c::produceAndPrint(std::unique_ptr<Operator>, const std::vector<IU*>&, unsigned int, uint64_t, int64_t)::<lambda()>
cerr << w_id1 << " ";cerr << w_name2 << " ";cerr << w_street_13 << " ";cerr << w_street_24 << " ";cerr << w_city5 << " ";cerr << w_state6 << " ";cerr << w_zip7 << " ";cerr << w_tax8 << " ";cerr << w_ytd9 << " ";cerr << endl;
}
row10++;}
}
);