//
// Created by cgsdfc on 19-6-7.
//

#include <catch2/catch.hpp>
#include <cmath>
#include "itertools/map.h"
using itertools::map;

TEST_CASE("map a single iterable", "[map]") {
  auto m = map(sqrt, (int[]) {1, 2, 3});
  for (auto v:m) {
    printf("%lf\n", v);
  }
}