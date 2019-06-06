//
// Created by cgsdfc on 19-6-6.
//
#include <catch2/catch.hpp>
#include <type_traits>
#include <iostream>
#include <cstring>

template <class T>
struct Wrapper {
  T t;
};

template <class T>
Wrapper(T &) -> Wrapper<T &>;

template <class T>
Wrapper(T &&) -> Wrapper<T &&>;

struct Wrapper2 {
  std::vector<int> &&t;
};

namespace test {
template <class T>
struct WrapperBase1 {
  T wrapped;
};

template <class T>
WrapperBase1(T &) -> WrapperBase1<std::remove_reference_t<T> &>;

template <class T>
WrapperBase1(T &&) -> WrapperBase1<std::remove_reference_t<T> &&>;

}

TEST_CASE("rvalue ref as member should expand object's life time") {
  Wrapper2 w{std::vector{1, 2, 3}};
  REQUIRE(w.t == std::vector{1, 2, 3});
  w.t[0] = 2;
  REQUIRE(w.t[0] == 2);
}

TEST_CASE("lvalue and rvalue iterable argument should be handled differently", "[util]") {
//  std::forward()
  SECTION("wrap a lvalue ref") {
    int a = 1;
    Wrapper w{a};
    REQUIRE(w.t == a);
    w.t = 2;
    REQUIRE(a == 2);
  }

  SECTION("wrap a rvalue ref") {
    Wrapper w{1};
    REQUIRE(w.t == 1);
    w.t = 2;
    REQUIRE(w.t == 2);
  }

}

TEST_CASE("IterableWrapper should work in both cases", "[util]") {
  int arr[] = {1, 2};
  std::vector vec{1, 2, 3};

  SECTION("wrap a lvalue ref of vector") {
    test::WrapperBase1 iw{vec};
    REQUIRE(&iw.wrapped == &vec);
  }

  SECTION("wrap a lvalue ref of array") {
    test::WrapperBase1 iw{arr};
    REQUIRE(&iw.wrapped == &arr);
  }

  SECTION("wrap a rvalue of vector") {
    test::WrapperBase1 iw{std::vector{1, 2, 3}};
    REQUIRE(iw.wrapped[0] == 1);
    REQUIRE(iw.wrapped[1] == 2);
    REQUIRE(iw.wrapped[2] == 3);
  }

  SECTION("wrap a rvalue ref of array") {
    test::WrapperBase1 iw{(int[]) {1, 2, 3}};
    REQUIRE(iw.wrapped[0] == 1);
    REQUIRE(iw.wrapped[1] == 2);
    REQUIRE(iw.wrapped[2] == 3);
  }
//  std::reference_wrapper
}

template <class T>
struct WrapperBase;

template <class T>
struct WrapperBase<T &> {
  T &wrapped;
};

template <class T>
struct WrapperBase<T &&> {
  T wrapped;
};

template <class T, std::size_t N>
struct WrapperBase<T (&&)[N]> {
  T (&&wrapped)[N];
};

template <class T>
WrapperBase(T &&) -> WrapperBase<typename std::remove_reference<T>::type &&>;

template <class T>
WrapperBase(T &) -> WrapperBase<typename std::remove_reference<T>::type &>;

TEST_CASE("rvalue", "[WrapperBase]") {
  int arr[] = {1, 2};
  std::vector vec{1, 2, 3};

  SECTION("vector") {
    WrapperBase wb{decltype(vec)(vec)};
    REQUIRE(wb.wrapped == vec);
  }
  SECTION("array") {
    WrapperBase wb{(int[]) {1, 2}};
    REQUIRE(std::memcmp(&wb.wrapped[0], &arr[0], sizeof(arr)) == 0);
    printf("%lu\n", sizeof(wb.wrapped));
  }
}

TEST_CASE("lvalue", "[WrapperBase]") {
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