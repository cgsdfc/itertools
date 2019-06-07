//
// Created by cgsdfc on 19-6-6.
//
#include <catch2/catch.hpp>
#include <type_traits>
#include <iostream>
#include <cstring>
#include "itertools.h"
#include "itertools/detail.h"

using itertools::iterable_wrapper;

template <class T>
struct WrapperBase {
  using type = typename iterable_wrapper<T>::type;
  type wrapped;
};

template <class T>
WrapperBase(T &&) -> WrapperBase<T &&>;

TEST_CASE("", "[WrapperBase][rvalue]") {
  int arr[] = {1, 2};
  std::vector vec{1, 2, 3};

  SECTION("vector") {
    WrapperBase wb{decltype(vec)(vec)};
    REQUIRE(wb.wrapped == vec);
  }
}

TEST_CASE("", "[WrapperBase][lvalue]") {
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