//
// Created by cgsdfc on 19-6-6.
//

#ifndef ITERTOOLS_DETAIL_H
#define ITERTOOLS_DETAIL_H
#include <iterator>
#include <type_traits>

namespace itertools {
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
  using type = T (&&)[N];
};
template <class T>
struct iterator_from_iterable {
  using iterable = typename std::add_lvalue_reference<T>::type;
  using type =  decltype(std::begin(std::declval<iterable>()));
};
template <class T>
struct iterable_traits {
  using raw_iterable = T;
  using raw_iterator = typename iterator_from_iterable<raw_iterable>::type;
  using wrapped_iterable = typename iterable_wrapper<T>::type;
  using value_type = decltype(*std::declval<raw_iterator>());
};

}
#endif //ITERTOOLS_DETAIL_H
