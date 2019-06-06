//
// Created by cgsdfc on 19-6-6.
//

#include <catch2/catch.hpp>
#include <iostream>
#include "range.h"
#include "zip.h"
using itertools::range;

TEST_CASE("range is a user-friendly integral loop", "[range]") {
  SECTION("normal 0-based loop") {
    for (auto i : range(10)) {
      std::cout << i << " ";
    }
    std::cout << '\n';
  }

  SECTION("specify start") {
    for (auto i : range(1, 10)) {
      std::cout << i << " ";
    }
    std::cout << '\n';
  }

  SECTION("specify step") {
    for (auto i : range(0, 10, 2)) {
      std::cout << i << " ";
    }
    std::cout << '\n';
    for (auto i : range(1, 10, 2)) {
      std::cout << i << " ";
    }
    std::cout << '\n';
  }

  SECTION("negative step") {
    for (auto i : range(10, 0, -1)) {
      std::cout << i << " ";
    }
    std::cout << '\n';
  }

  SECTION("empty range") {
    std::vector<int> vec;
    for (auto i : range(999, 1)) {
      vec.push_back(i);
    }
    REQUIRE(vec.empty());
  }
}

TEST_CASE("zip 2 ranges", "[zip][range]") {
  using itertools::zip;
  auto zip_r = zip(range(10), range(5));
  std::vector<decltype(zip_r)::value_type> vec;
  std::copy(zip_r.begin(), zip_r.end(), std::back_inserter(vec));
  for (auto [i, j]: vec) {
    printf("%d, %d\n", i, j);
  }
  std::cout << '\n';
}