db
    .lineitem
    .stream([&]() {
        return Tuple<warehouse_t>({"v_1", warehouse_t::*name_t}, {"v_2", warehouse_t::*value_t});
    })
    .groupBy([&](const auto& row) {
        return {get<"v_6">(row)};
    }, [&](auto& result, const auto& row) {
        get<"v_4">(result) += get<"v_3">(row);
    })
    .select([&](const auto& row) { 
        return get<"v_1">(row) > 10; 
    })
    .join(db
        .order
        .stream()
        .filter([&](const auto& row) {
            return get<"v_2">(row) < 5;
        }), [](auto& lrow, auto& rrow) {
        return get<"v_3">(lrow) == get<"v_4">(rrow);
    })
    .forEach([&](const auto& row) {
        cout << row << endl;
    });