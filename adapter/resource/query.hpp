std::map<std::string, std::map<std::string, std::function<void(Database*)>>> queries = {
	{"none", {
	{"./query/query.sane", [](Database* db) {
		std::vector<std::tuple<Varchar<10>, Integer, Varchar<10>, Varchar<20>, Varchar<20>, Varchar<20>, Varchar<2>, Varchar<9>, Numeric, Numeric>> v_1;
		db->warehouse.forEach([&](auto& key, auto& value) {
			Integer v_2 = key.w_id;
			Varchar<10> v_3 = value.w_name;
			Varchar<20> v_4 = value.w_street_1;
			Varchar<20> v_5 = value.w_street_2;
			Varchar<20> v_6 = value.w_city;
			Varchar<2> v_7 = value.w_state;
			Varchar<9> v_8 = value.w_zip;
			Numeric v_9 = value.w_tax;
			Numeric v_10 = value.w_ytd;
			v_1.push_back({v_3, v_2, v_3, v_4, v_5, v_6, v_7, v_8, v_9, v_10});
		});
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) { return t1 < t2; });
		for (auto& t : v_1) {
			Integer v_2 = std::get<1>(t);
			Varchar<10> v_3 = std::get<2>(t);
			Varchar<20> v_4 = std::get<3>(t);
			Varchar<20> v_5 = std::get<4>(t);
			Varchar<20> v_6 = std::get<5>(t);
			Varchar<2> v_7 = std::get<6>(t);
			Varchar<9> v_8 = std::get<7>(t);
			Numeric v_9 = std::get<8>(t);
			Numeric v_10 = std::get<9>(t);
			if ((v_2 == 1) && (v_3 == Varchar<5>("hello"))) {
				std::cout << v_2 << ", " << v_3 << ", " << v_4 << ", " << v_5 << ", " << v_6 << ", " << v_7 << ", " << v_8 << ", " << v_9 << ", " << v_10 << std::endl;
			}
		}
	}},
}},
	{"selects", {
	{"./query/query.sane", [](Database* db) {
		std::vector<std::tuple<Varchar<10>, Integer, Varchar<10>, Varchar<20>, Varchar<20>, Varchar<20>, Varchar<2>, Varchar<9>, Numeric, Numeric>> v_1;
		db->warehouse.forEach([&](auto& key, auto& value) {
			Integer v_2 = key.w_id;
			Varchar<10> v_3 = value.w_name;
			Varchar<20> v_4 = value.w_street_1;
			Varchar<20> v_5 = value.w_street_2;
			Varchar<20> v_6 = value.w_city;
			Varchar<2> v_7 = value.w_state;
			Varchar<9> v_8 = value.w_zip;
			Numeric v_9 = value.w_tax;
			Numeric v_10 = value.w_ytd;
			if ((v_2 == 1) && (v_3 == Varchar<5>("hello"))) {
				v_1.push_back({v_3, v_2, v_3, v_4, v_5, v_6, v_7, v_8, v_9, v_10});
			}
		});
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) { return t1 < t2; });
		for (auto& t : v_1) {
			Integer v_2 = std::get<1>(t);
			Varchar<10> v_3 = std::get<2>(t);
			Varchar<20> v_4 = std::get<3>(t);
			Varchar<20> v_5 = std::get<4>(t);
			Varchar<20> v_6 = std::get<5>(t);
			Varchar<2> v_7 = std::get<6>(t);
			Varchar<9> v_8 = std::get<7>(t);
			Numeric v_9 = std::get<8>(t);
			Numeric v_10 = std::get<9>(t);
			std::cout << v_2 << ", " << v_3 << ", " << v_4 << ", " << v_5 << ", " << v_6 << ", " << v_7 << ", " << v_8 << ", " << v_9 << ", " << v_10 << std::endl;
		}
	}},
}},
	{"scans", {
	{"./query/query.sane", [](Database* db) {
		std::vector<std::tuple<Varchar<10>, Integer, Varchar<10>, Varchar<20>, Varchar<20>, Varchar<20>, Varchar<2>, Varchar<9>, Numeric, Numeric>> v_1;
		db->warehouse.forEach([&](auto& key, auto& value) {
			Integer v_2 = key.w_id;
			Varchar<10> v_3 = value.w_name;
			Varchar<20> v_4 = value.w_street_1;
			Varchar<20> v_5 = value.w_street_2;
			Varchar<20> v_6 = value.w_city;
			Varchar<2> v_7 = value.w_state;
			Varchar<9> v_8 = value.w_zip;
			Numeric v_9 = value.w_tax;
			Numeric v_10 = value.w_ytd;
			v_1.push_back({v_3, v_2, v_3, v_4, v_5, v_6, v_7, v_8, v_9, v_10});
		});
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) { return t1 < t2; });
		for (auto& t : v_1) {
			Integer v_2 = std::get<1>(t);
			Varchar<10> v_3 = std::get<2>(t);
			Varchar<20> v_4 = std::get<3>(t);
			Varchar<20> v_5 = std::get<4>(t);
			Varchar<20> v_6 = std::get<5>(t);
			Varchar<2> v_7 = std::get<6>(t);
			Varchar<9> v_8 = std::get<7>(t);
			Numeric v_9 = std::get<8>(t);
			Numeric v_10 = std::get<9>(t);
			if ((v_2 == 1) && (v_3 == Varchar<5>("hello"))) {
				std::cout << v_2 << ", " << v_3 << ", " << v_4 << ", " << v_5 << ", " << v_6 << ", " << v_7 << ", " << v_8 << ", " << v_9 << ", " << v_10 << std::endl;
			}
		}
	}},
}},
	{"joins", {
	{"./query/query.sane", [](Database* db) {
		std::vector<std::tuple<Varchar<10>, Integer, Varchar<10>, Varchar<20>, Varchar<20>, Varchar<20>, Varchar<2>, Varchar<9>, Numeric, Numeric>> v_1;
		db->warehouse.forEach([&](auto& key, auto& value) {
			Integer v_2 = key.w_id;
			Varchar<10> v_3 = value.w_name;
			Varchar<20> v_4 = value.w_street_1;
			Varchar<20> v_5 = value.w_street_2;
			Varchar<20> v_6 = value.w_city;
			Varchar<2> v_7 = value.w_state;
			Varchar<9> v_8 = value.w_zip;
			Numeric v_9 = value.w_tax;
			Numeric v_10 = value.w_ytd;
			v_1.push_back({v_3, v_2, v_3, v_4, v_5, v_6, v_7, v_8, v_9, v_10});
		});
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) { return t1 < t2; });
		for (auto& t : v_1) {
			Integer v_2 = std::get<1>(t);
			Varchar<10> v_3 = std::get<2>(t);
			Varchar<20> v_4 = std::get<3>(t);
			Varchar<20> v_5 = std::get<4>(t);
			Varchar<20> v_6 = std::get<5>(t);
			Varchar<2> v_7 = std::get<6>(t);
			Varchar<9> v_8 = std::get<7>(t);
			Numeric v_9 = std::get<8>(t);
			Numeric v_10 = std::get<9>(t);
			if ((v_2 == 1) && (v_3 == Varchar<5>("hello"))) {
				std::cout << v_2 << ", " << v_3 << ", " << v_4 << ", " << v_5 << ", " << v_6 << ", " << v_7 << ", " << v_8 << ", " << v_9 << ", " << v_10 << std::endl;
			}
		}
	}},
}},
	{"all", {
	{"./query/query.sane", [](Database* db) {
		std::vector<std::tuple<Varchar<10>, Integer, Varchar<10>, Varchar<20>, Varchar<20>, Varchar<20>, Varchar<2>, Varchar<9>, Numeric, Numeric>> v_1;
		db->warehouse.lookup1({1}, [&](auto& value) {
			Integer v_2 = 1;
			Varchar<10> v_3 = value.w_name;
			Varchar<20> v_4 = value.w_street_1;
			Varchar<20> v_5 = value.w_street_2;
			Varchar<20> v_6 = value.w_city;
			Varchar<2> v_7 = value.w_state;
			Varchar<9> v_8 = value.w_zip;
			Numeric v_9 = value.w_tax;
			Numeric v_10 = value.w_ytd;
			if (v_3 == Varchar<5>("hello")) {
				v_1.push_back({v_3, v_2, v_3, v_4, v_5, v_6, v_7, v_8, v_9, v_10});
			}
		});
		std::sort(v_1.begin(), v_1.end(), [](const auto& t1, const auto& t2) { return t1 < t2; });
		for (auto& t : v_1) {
			Integer v_2 = std::get<1>(t);
			Varchar<10> v_3 = std::get<2>(t);
			Varchar<20> v_4 = std::get<3>(t);
			Varchar<20> v_5 = std::get<4>(t);
			Varchar<20> v_6 = std::get<5>(t);
			Varchar<2> v_7 = std::get<6>(t);
			Varchar<9> v_8 = std::get<7>(t);
			Numeric v_9 = std::get<8>(t);
			Numeric v_10 = std::get<9>(t);
			std::cout << v_2 << ", " << v_3 << ", " << v_4 << ", " << v_5 << ", " << v_6 << ", " << v_7 << ", " << v_8 << ", " << v_9 << ", " << v_10 << std::endl;
		}
	}},
}},
};
