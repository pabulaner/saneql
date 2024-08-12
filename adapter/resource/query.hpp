std::vector<std::tuple<int, int, double, int>> v_1;
std::unordered_map<std::tuple<int>, std::tuple<int, std::pair<double, int>>> v_2;
db->item.forEach([&](auto& key, auto& value) {
	int v_3 = key.i_id;
	int v_4 = value.i_im_id;
	Varchar<24> v_5 = value.i_name;
	double v_6 = value.i_price;
	Varchar<50> v_7 = value.i_data;
	auto it = v_2.find({v_4});
	if (it == v_2.end()) {
		v_2.insert({{v_4}, {1, {v_6, 1}}});
	} else {
		std::get<0>(it->second) += 1;
		std::get<1>(it->second) = {std::get<1>(it->second).first + v_6, std::get<1>(it->second).second + 1};
	}
});
for (auto& it : v_2) {
	int v_8 = std::get<0>(it.first);
	int v_9 = std::get<0>(it.second);
	double v_10 = std::get<1>(it.second).first / (double)std::get<1>(it.second).second;
	v_1.push_back({v_8, v_9, v_10, v_8});
}
sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) { return t1 < t2; });
for (auto& t : v_1) {
	int v_9 = std::get<1>(t);
	double v_10 = std::get<2>(t);
	int v_8 = std::get<3>(t);
	if (v_9 > 10) {
		std::cout << v_9 << ", " << v_10 << ", " << v_8 << std::endl;
	}
}

