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
  SECTION("rvalue vector") {
    // vector has no such issue.
    auto m = map([](int x) { return std::sqrt(x); }, std::vector{1, 2, 3});
    REQUIRE(m.end() == m.end());
    REQUIRE(m.begin() == m.begin());
    REQUIRE(m.begin() != m.end());

    for (auto v:m) {
      printf("%lf\n", v);
    }
  }

  SECTION("lvalue vector") {
    std::vector vec{1, 2, 3};
    auto cnt = 1;
    for (auto v: map([](auto val) { return 2 * val; }, vec)) {
      REQUIRE(2 * cnt == v);
      ++cnt;
    }
  }

  SECTION("lvalue array") {
    int arr[] = {1, 2, 3};
    std::size_t i = 0;
    for (auto val : map([](auto x) { return x * 2; }, arr)) {
      REQUIRE(val == arr[i] * 2);
      i++;
      std::cout << val << ' ';
    }
    std::cout << '\n';
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
    std::size_t i = 0;
    for (auto &&str : map(func, chars, cnt)) {
      REQUIRE(str.size() == cnt[i]);
      REQUIRE(str[0] == chars[i]);
      i++;
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