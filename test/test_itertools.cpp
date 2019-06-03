//
// Created by cgsdfc on 19-6-3.
//
#include <catch2/catch.hpp>
#include "itertools.h"
#include <vector>
#include <iostream>

using namespace itertools;

TEST_CASE() {
  std::vector vec = {1, 2, 3};
  for (auto item : enumerate(vec)) {
    std::cout << "index: " << item.first << " value: " << item.second << '\n';
  }

  for (auto[index, value] : enumerate(vec)) {
    std::cout << index << " " << value << '\n';
  }
}