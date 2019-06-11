//
// Created by cgsdfc on 19-6-10.
//

#include <catch2/catch.hpp>
#include "itertools/repeat.h"
#include "itertools/map.h"
#include "itertools/range.h"

using itertools::repeat;

TEST_CASE("repeat infinite", "[repeat]") {
  auto r = repeat(0);
  auto iter = r.begin();
  REQUIRE(iter != r.end());
  REQUIRE(*iter == 0);
  REQUIRE(*++iter == 0);
  REQUIRE(*iter++ == 0);
  REQUIRE_FALSE(iter == r.end());
}

TEST_CASE("repeat a string") {
  auto string = std::string{"Hello"};
  const auto limit = 10;
  auto cnt = 0;
  for (auto &&str : repeat(string)) {
    REQUIRE(str == string);
    if (++cnt >= limit) {
      break;
    }
  }
}

TEST_CASE("repeat finite times") {
  auto r = repeat("A", 4);
  auto cnt = 0;
  for (auto str : r) {
    REQUIRE(std::string(str) == "A");
    cnt++;
  }
  REQUIRE(cnt == 4);
}

TEST_CASE("example from pydoc", "[repeat][map][range]") {
  using itertools::map;
  using itertools::range;
#ifdef _MSC_VER
  auto m = map([](int x, int y) { return pow(x, y); }, range(10), repeat(2));
#else
  auto m = map(::pow, range(10), repeat(2));
#endif
  double val = 0;
  for (auto xval : m) {
    REQUIRE(xval == pow(val, 2));
    ++val;
  }
}
