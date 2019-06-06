//
// Created by cgsdfc on 19-6-6.
//

#include <catch2/catch.hpp>
#include "itertools.h"

using itertools::enumerate;
using itertools::zip;

TEST_CASE("all wrapped iterable is lvalue", "[zip]") {
  std::vector<double> v1{1, 2, 3};
  std::vector<int> v2{1, 2, 3};

  auto z = zip(v1, v2);
  for (auto[x, y]:z) {
    printf("%lf, %d\n", x, y);
  }
}