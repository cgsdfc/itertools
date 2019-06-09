//
// Created by cgsdfc on 19-6-6.
//

#ifndef ITERTOOLS_DETAIL_H
#define ITERTOOLS_DETAIL_H
#include <iterator>
#include <type_traits>
#include <initializer_list>
#include <array>

namespace itertools {
// We aways pass iterable by reference so the T (value) version should never be needed.
template <class T>
struct iterable_wrapper;
template <class T>
struct iterable_wrapper<T &> {
  using type = T &;
};
template <class T>
struct iterable_wrapper<T &&> {
  using type = T;
};
template <class T, std::size_t N>
struct iterable_wrapper<T (&&)[N]> {
  using type = typename T::rvalue_reference_to_array_is_not_supported;
};
template <class T>
struct iterator_from_iterable {
  // Value category is normalized to lvalue ref. Const is kept as it.
  using iterable = typename std::remove_reference<T>::type &;
  using type =  decltype(std::begin(std::declval<iterable>()));
};
template <class T>
struct iterable_traits {
  /// Raw iterable type with const and value category.
  using raw_iterable = T;
  /// Raw iterator type produced by calling std::begin on the raw_iterable.
  using raw_iterator = typename iterator_from_iterable<raw_iterable>::type;
  /// The type that can be kept as a member, wrapping the raw_iterable.
  using wrapped_iterable = typename iterable_wrapper<T>::type;
  /// The type returned by operator* on the raw_iterator.
  using deref_value_type = decltype(*std::declval<raw_iterator>());

};

}
#endif //ITERTOOLS_DETAIL_H
