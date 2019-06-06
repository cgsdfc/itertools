//
// Created by cgsdfc on 19-6-3.
//
#include <catch2/catch.hpp>
#include "itertools.h"
#include <vector>
#include <iostream>
#include <numeric>

using namespace itertools;

struct ILStore {
};

TEST_CASE("can we store an initializer_list?", "[util]") {
  std::initializer_list<int> t{1, 2, 3};
}

#if 0


TEST_CASE("map(func, iterables...)", "[map]") {
  SECTION("basic with C array") {
    int arr[] = {1, 2, 3};
    for (auto i : map([](auto x) { return x * 2; }, arr)) {
      std::cout << i << ' ';
    }
    std::cout << '\n';
  }

  SECTION("with range") {
    std::tuple t = {1};
    auto r = range(100000l);
//    for (auto x : map([](auto x) { return x * x; }, r)) {
//
//    }
  }
}
#endif
