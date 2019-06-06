//
// Created by cgsdfc on 19-6-3.
//
#include <catch2/catch.hpp>
#include "itertools.h"
#include <vector>
#include <iostream>
#include <numeric>

using namespace itertools;

#if 0
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

TEST_CASE("map(func, iterables...)", "[map]") {
  SECTION("basic with C array") {
    int arr[] = {1, 2, 3};
    for (auto i : map([](auto x) { return x * 2; }, arr)) {
      std::cout << i << ' ';
    }
    std::cout << '\n';
  }

  SECTION("with range") {
    std::tuple t = {1};
    auto r = range(100000l);
//    for (auto x : map([](auto x) { return x * x; }, r)) {
//
//    }
  }
}
#endif
