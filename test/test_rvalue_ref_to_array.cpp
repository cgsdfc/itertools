//
// Created by cgsdfc on 19-6-7.
//
#include <catch2/catch.hpp>
#include "itertools/detail.h"
using itertools::iterable_wrapper;

TEST_CASE("") {
#if 0
  // This is should not compile and give a friendly message.
  iterable_wrapper<int (&&)[2]>::type a;
#endif
}
