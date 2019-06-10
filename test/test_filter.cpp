//
// Created by cgsdfc on 19-6-9.
//

#include <catch2/catch.hpp>
#include <numeric>
#include <string>
#include "itertools/filter.h"

using namespace std::literals;
using itertools::filter;
using itertools::filterfalse;

TEST_CASE("single_step_iterator stepping", "[filter]") {
  std::vector v(5, 0);
  std::iota(v.begin(), v.end(), 0);
  auto f = filter([](int val) { return val % 2 == 0; }, v);
  auto iter = f.begin();

  // dereference any time yield the same result.
  REQUIRE(*iter == 0);
  REQUIRE(*iter == 0);
  REQUIRE(*iter == 0);

  // compare to end() always yield the same result.
  REQUIRE(iter != f.end());
  REQUIRE(iter != f.end());
  REQUIRE(iter != f.end());

  ++iter;
  REQUIRE(*iter == 2);
  REQUIRE(*++iter == 4);
  REQUIRE(*iter == 4);
  REQUIRE(++iter == f.end());
}

TEST_CASE("loop over", "[filter]") {
  std::size_t i = 1;
  for (auto val : filter([](auto val) -> bool { val > 0; },
                         std::vector{-3, -2, -1, 0, 1, 2, 3})) {
    REQUIRE(val == i);
    REQUIRE(val > 0);
    ++i;
  }
}

TEST_CASE("filterfalse", "[filterfalse]") {
  auto ff = filterfalse([](auto &&str) -> bool { return !str.empty(); },
                         std::array{""s, ""s, "a"s, "b"s, ""s});
  for (auto &&str : ff) {
    REQUIRE(str.empty());
  }
}