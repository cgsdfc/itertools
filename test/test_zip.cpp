//
// Created by cgsdfc on 19-6-6.
//

#include <catch2/catch.hpp>
#include <numeric>
#include <iostream>
#include "itertools/zip.h"

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

TEST_CASE("zip one or more iterable", "[zip]") {
  SECTION("two seqs with identical lens") {
    int arr[] = {1, 2, 3, 4};
    std::vector vec = {'a', 'b', 'c', 'd'};
    for (auto[integer, character]: zip(arr, vec)) {
      std::cout << "int: " << integer << " char: " << character << '\n';
    }
  }

  SECTION("zip one seq should be identical with that seq") {
    std::vector vec = {1, 2, 3};
    size_t cnt = 0;
    for (auto[val]: zip(vec)) {
      REQUIRE(vec.at(cnt) == val);
      cnt++;
    }
    REQUIRE(cnt == vec.size());
  }

  SECTION("zip should stop when the shortest seq stops") {
    std::vector<int> shortest_seq(2);
    std::iota(shortest_seq.begin(), shortest_seq.end(), 0);
    const char *str_seq[] = {"One", "Two", "Three"};
    double db_seq[] = {1., 2., 3., 4.};
    size_t cnt = 0;
    for (auto _ : zip(shortest_seq, str_seq, db_seq)) {
      ++cnt;
    }
    REQUIRE(cnt == shortest_seq.size());

  }
}
