//
// Created by cgsdfc on 19-6-11.
//

#include <catch2/catch.hpp>
#include "itertools/cycle.h"

using itertools::cycle;

TEST_CASE("cycle of an empty iterable should be empty", "[cycle]") {
  std::vector<int> v;
  auto c = cycle(v);
  REQUIRE(c.begin() == c.end());
}

TEST_CASE("cycle of one item", "[cycle]") {
  std::vector v = {1};
  auto limit = 10;
  auto cnt = 0;
  for (auto val: cycle(v)) {
    REQUIRE(val == 1);
    if (++cnt > limit) {
      break;
    }
  }
}

TEST_CASE("cycle of list with size > 1", "[cycle]") {
  std::string str = "ABCD";
  auto limit = 10;
  auto cnt = 0;
  for (auto val: cycle(str)) {
    printf("%c\n", val);
    if (++cnt > limit) {
      break;
    }
  }
}