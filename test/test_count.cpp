//
// Created by cgsdfc on 19-6-11.
//

#include <catch2/catch.hpp>
#include "itertools/count.h"

using itertools::count;

template <class T = int>
struct Test {};

Test()->Test<int>;

TEST_CASE("count() can compile", "[count][compile]") {
//  auto c0 = count{};
//  auto c1 = count(1);
//  auto c2 = count(2, 3);
}

TEST_CASE("empty argument list") {
//  auto t = Test();
  Test t;
  Test t2{};
//  Test();
  Test{};
  printf("ss");
}