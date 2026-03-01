//
//  test.cpp
//  hw_2
//
//  Created by Ivan Batrakov on 01/03/2026.
//  Copyright © 2026 on_eveth. All rights reserved.
//

#include <stdio.h>
#include "catch_amalgamated.hpp"
#include "../main.cpp"

const double expected_res = 406.6;

TEST_CASE("n=2", "[simpson_rule]"){
    double result = simpson_rule(func, 2, 7, 2);
    CHECK( result == Catch::Approx(expected_res).epsilon(0.1) );
};

TEST_CASE("n=8", "[simpson_rule]"){
    double result = simpson_rule(func, 2, 7, 8);
    CHECK( result == Catch::Approx(expected_res).epsilon(0.1) );
};

TEST_CASE("n=10", "[simpson_rule]"){
    double result = simpson_rule(func, 2, 7, 10);
    CHECK( result == Catch::Approx(expected_res).epsilon(0.1) );
};
