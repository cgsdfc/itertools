//
// Created by cgsdfc on 19-6-7.
//

#include <catch2/catch.hpp>
#include <cmath>
#include <functional>
#include <iostream>
#include "itertools/range.h"
#include "itertools/map.h"
using itertools::map;

TEST_CASE("map a single iterable", "[map]") {
  SECTION("rvalue") {
    auto m = map(sqrt, (int[]) {1, 2, 3});
    for (auto v:m) {
      printf("%lf\n", v);
    }
  }
  SECTION("lvalue") {
    std::vector vec{1, 2, 3};
    auto cnt = 1;
    for (auto v: map([](auto val) { return 2 * val; }, vec)) {
      REQUIRE(2 * cnt == v);
      ++cnt;
    }
  }
  SECTION("upper case a string") {
    std::string s{"hello"};
    auto m = map(::toupper, s);
    std::string out;
    std::copy(m.begin(), m.end(), std::back_inserter(out));
    REQUIRE(out == "HELLO");
  }
}

TEST_CASE("map a list of iterables", "[map]") {
  SECTION("plus") {
    std::vector vec{1, 2, 3};
    auto cnt = 1;
    for (auto val: map(std::plus<>(), vec, vec)) {
      REQUIRE(val == 2 * cnt);
      ++cnt;
    }
  }
  SECTION("different element types") {
    auto func = [](char ch, std::size_t cnt) {
      return std::string(cnt, ch);
    };
    char chars[] = {'a', 'b', 'c'};
    std::size_t cnt[] = {1, 2, 3};
    for (auto &&str : map(func, chars, cnt)) {
      std::cout << str << '\n';
    }
  }
}

TEST_CASE("map a range", "[map][range]") {
  using itertools::range;
  for (auto val : map([](auto x) { return std::pow(x, 2); }, range(10))) {
    std::cout << val << '\n';
  }
}