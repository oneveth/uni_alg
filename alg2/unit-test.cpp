//
//  unit-test.cpp
//  alg2
//
//  Created by Ivan Batrakov on 17/02/2026.
//  Copyright © 2026 on_eveth. All rights reserved.
//

#include <stdio.h>
#include "catch_amalgamated.hpp"
#include "main.cpp"

std::queue<int> empty_q;
std::queue<int> example = queue_extended_with_zeroes_generator(empty_q, 10);

TEST_CASE( "test", "[test]" ) {
    CHECK( example.size() == 10 ); // убеждаемся в том, что размер очереди соответствует, переданному параметру (цикл работает корректно)
    
    while( !example.empty() ){
        CHECK( example.back() == 0 );
        example.pop(); // перебирая очередь, проверяем, все ли элементы являются нулём (не знаю, что ещё придумать)
    }
    
}
