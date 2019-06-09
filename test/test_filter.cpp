//
// Created by cgsdfc on 19-6-9.
//

#include <catch2/catch.hpp>
#include "itertools/filter.h"

using itertools::filter;
using itertools::filter_false;

TEST_CASE("filter") {
  std::vector v(5, 0);
  std::iota(v.begin(), v.end(), 0);
  auto f = filter([](int val) { return val % 2 == 0; }, v);
  auto iter = f.begin();
  REQUIRE(*iter++ == 0);
  REQUIRE(*iter++ == 2);
  REQUIRE(*iter++ == 4);
  REQUIRE(iter == f.end());
}
