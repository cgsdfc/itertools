//
// Created by cgsdfc on 19-6-9.
//

#include <catch2/catch.hpp>
#include "itertools.h"

using namespace itertools;

TEST_CASE("map and zip") {
  SECTION("ugly way") {
    for (auto val : map(
        [](auto args) { return std::apply(std::plus{}, args); },
        zip(range(10), range(10)))) {
      printf("%d\n", val);
    }
  }
  SECTION("pretty way") {
    for (auto val : map(
        [](auto a, auto b) { return a + b; },
        range(10), range(10))) {
      printf("%d\n", val);
    }
  }
}

template <class Tuple, std::size_t ... Is>
auto reverse_tuple_impl(Tuple &&tuple, std::index_sequence<Is...>) {
  return std::tuple{std::get<sizeof...(Is) + 1 - Is>(tuple)...};
}

template <class Callable>
class unpack_wrapper {
  Callable func_;
public:
  explicit unpack_wrapper(Callable func) : func_(std::move(func)) {}
  template <class Tuple>
  auto operator()(Tuple &&args) {
    return std::apply(func_, std::forward<Tuple>(args));
  }
};

template <class Callable>
auto unpack(Callable func) {
  return [func](auto &&args) {
    return std::apply(func, args);
  };
}

TEST_CASE("build a word dict") {
  auto words = std::array{
      "Foo", "Bar", "Mechanism", "Policy", "Implementation",
  };
  using string_type = decltype(words)::value_type;
  auto indexes_words = enumerate(words);

  auto words_indexes = map(
      unpack([](auto a, auto b) { return std::pair{b, a}; }),
      indexes_words
  );

  auto i2w = std::unordered_map<int, string_type>(
      indexes_words.begin(),
      indexes_words.end()
  );
  auto w2i = std::unordered_map<string_type, int>(
      words_indexes.begin(),
      words_indexes.end()
  );

  for (auto[index, word] : i2w) {
    REQUIRE(w2i[word] == index);
    printf("%d: %s\n", index, word);
  }

  for (auto[word, index] : w2i) {
    REQUIRE(i2w[index] == word);
    printf("%s: %d\n", word, index);
  }
}
