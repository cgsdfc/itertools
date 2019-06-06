//
// Created by cgsdfc on 19-6-6.
//
#include <catch2/catch.hpp>
#include <type_traits>
#include <iostream>
#include <cstring>
#include "itertools.h"

using itertools::WrapperBase;

struct RValueRefWrapper {
  std::vector<int> &&t;
};

TEST_CASE("rvalue ref as member should expand object's life time") {
  RValueRefWrapper w{std::vector{1, 2, 3}};
  REQUIRE(w.t == std::vector{1, 2, 3});
  w.t[0] = 2;
  REQUIRE(w.t[0] == 2);
}

TEST_CASE("rvalue", "[WrapperBase]") {
  int arr[] = {1, 2};
  std::vector vec{1, 2, 3};

  SECTION("vector") {
    WrapperBase wb{decltype(vec)(vec)};
    REQUIRE(wb.wrapped == vec);
  }
  SECTION("array") {
    WrapperBase wb{(int[]) {1, 2}};
    REQUIRE(std::memcmp(&wb.wrapped[0], &arr[0], sizeof(arr)) == 0);
    printf("%lu\n", sizeof(wb.wrapped));
  }
}

TEST_CASE("lvalue", "[WrapperBase]") {
  int arr[] = {1, 2};
  std::vector vec{1, 2, 3};

  SECTION("vector") {
    WrapperBase wb{vec};
    REQUIRE(wb.wrapped == vec);
    wb.wrapped[0] = 999;
    REQUIRE(wb.wrapped[0] == vec[0]);
  }
  SECTION("array") {
    WrapperBase wb{arr};
    REQUIRE(std::memcmp(&wb.wrapped[0], &arr[0], sizeof(arr)) == 0);
    wb.wrapped[0] = 999;
    REQUIRE(wb.wrapped[0] == arr[0]);
  }
}