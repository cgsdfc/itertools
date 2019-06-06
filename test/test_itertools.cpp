//
// Created by cgsdfc on 19-6-3.
//
#include <catch2/catch.hpp>
#include "itertools.h"
#include <vector>
#include <iostream>
#include <numeric>

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