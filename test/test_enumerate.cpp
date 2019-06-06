//
// Created by cgsdfc on 19-6-6.
//
#include <catch2/catch.hpp>
#include <iostream>
#include "itertools/enumerate.h"
#include "itertools/range.h"
using itertools::enumerate;

TEST_CASE("", "[enumerate][lvalue]") {
  std::vector vec = {1, 2, 3};
  SECTION("iterate") {
    for (auto item : enumerate(vec)) {
      std::cout << "index: " << item.first << " value: " << item.second << '\n';
    }
  }

  SECTION("iterate with structural assignment") {
    for (auto[index, value] : enumerate(vec)) {
      std::cout << index << " " << value << '\n';
    }
  }

  SECTION("start from other value") {
    for (auto[index, value] : enumerate(vec, 1)) {
      std::cout << index << " " << value << '\n';
    }
  }

  SECTION("iterate while changing value") {
    for (auto item : enumerate(vec)) {
      item.second = 1;
    }
    REQUIRE(std::all_of(vec.begin(), vec.end(), [](auto value) -> bool { return value == 1; }));
  }

  SECTION("iterate over const container") {
    const std::vector<int> const_vec = {1, 2, 3};
    for (auto item : enumerate(const_vec)) {
      REQUIRE(item.first + 1 == item.second);
    }
  }

  SECTION("C array can be used") {
    int arr[] = {1, 2, 3, 4};
    for (auto[id, val]:enumerate(arr)) {
      REQUIRE(id == val - 1);
    }
  }

  SECTION("initializer_list can be used") {
    std::initializer_list<int> init = {1, 2, 3, 4};
    for (auto[id, val]:enumerate(init)) {
      REQUIRE(id == val - 1);
    }
  }
}

TEST_CASE("", "[enumerate][rvalue]") {
  SECTION("array") {
    auto e = enumerate((int[]) {1, 2});
    for (auto item: e) {
      printf("%d %d\n", item.first, item.second);
    }
  }
  SECTION("vector") {
    auto e = enumerate(std::vector{1, 2});
    for (auto item: e) {
      printf("%d %d\n", item.first, item.second);
    }
  }

}

TEST_CASE("", "[enumerate][range]") {
  using itertools::range;
  auto e = enumerate(range(10));
  for (auto item: e) {
    printf("%d %d\n", item.first, item.second);
  }
}
