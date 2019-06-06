//
// Created by cgsdfc on 19-6-6.
//

#include <catch2/catch.hpp>
#include "zip.h"

using itertools::zip;

TEST_CASE("all wrapped iterable is lvalue", "[zip]") {
  std::vector<double> v1{1, 2, 3};
  std::vector<int> v2{1, 2, 3};

  auto z = zip(v1, v2);
  for (auto[x, y]:z) {
    printf("%lf, %d\n", x, y);
  }
}

TEST_CASE("all wrapped iterable is rvalue", "[zip]") {
  auto z = zip(std::string{"Hello"}, std::vector{1, 2, 3, 4, 5});
  for (auto[x, y]:z) {
    printf("%c, %d\n", x, y);
  }
}

TEST_CASE("mixed lvalue and rvalue", "[zip]") {
  std::string s{"Hello"};
  auto zp = zip(s, std::string(s));
  for (auto[ch, num]: zip(s, (int[]) {1, 2, 3, 4, 5})) {
    printf("%c, %d\n", ch, num);
  }
}