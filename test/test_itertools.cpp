//
// Created by cgsdfc on 19-6-3.
//
#include <catch2/catch.hpp>
#include "itertools.h"
#include <vector>
#include <iostream>

using namespace itertools;

TEST_CASE("normal iterating", "[enumerate]") {
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
}

TEST_CASE("zip one or more iterable", "[zip]") {
  int arr[] = {1, 2, 3, 4};
  std::vector vec = {'a', 'b', 'c', 'd'};
  for (auto[integer, character]: zip(arr, vec)) {

  }
}