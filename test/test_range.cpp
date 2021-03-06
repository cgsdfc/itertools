//
// Created by cgsdfc on 19-6-6.
//

#include <catch2/catch.hpp>
#include <iostream>
#include "itertools/range.h"
#include "itertools/zip.h"
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
  for (auto[i, j]: vec) {
    printf("%d, %d\n", i, j);
  }
  std::cout << '\n';
}

TEST_CASE("common types of integrals", "[util]") {
  using type = typename std::common_type<std::size_t, int>::type;
  type x = 0;
  std::cout << x << '\n';
}

TEST_CASE("range with different integer type", "[range]") {
  SECTION("start stop") {
    std::vector<int> v(2, 6);
    auto r = range(0, v.size());
    auto iter = std::begin(r);
    REQUIRE(*iter++ == 0);
    REQUIRE(*iter++ == 1);
    REQUIRE(iter == r.end());
  }

  SECTION("start stop step") {
    std::vector<int> v(2, 6);
    auto r = range(0, v.size(), 2);
    auto iter = r.begin();
    REQUIRE(*iter++ == 0);
    REQUIRE(iter == r.end());
  }

  SECTION("negative step") {
    std::vector<int> v(2, 6);
    auto r = range(v.size() - 1, -1, -1);
    auto iter = r.begin();
    REQUIRE(*iter++ == 1);
    REQUIRE(*iter++ == 0);
    REQUIRE(iter == r.end());
  }

}

TEST_CASE("combination of operator++ and operator*", "[range]") {
  auto r = range(5);
  auto iter = r.begin();
  REQUIRE(*iter == 0);
  ++iter;
  REQUIRE(*iter == 1);
  iter++;
  REQUIRE(*iter == 2);
  REQUIRE(*iter++ == 2);
  REQUIRE(*iter == 3);
  REQUIRE(*++iter == 4);
}

TEST_CASE("range with different numbers of arguments", "[range]") {
  auto r1 = range(10);
  auto r2 = range(0, 10);
  auto r3 = range(0, 10, 1);
  SECTION("range objects have smaller size") {
    REQUIRE(sizeof(r1) < sizeof(r2));
    REQUIRE(sizeof(r2) < sizeof(r3));
  }

  auto i1 = r1.begin();
  auto i2 = r2.begin();
  auto i3 = r3.begin();
  SECTION("range iterators have smaller size") {
    REQUIRE(sizeof(i1) <= sizeof(i2));
    REQUIRE(sizeof(i2) < sizeof(i3));
  }
}