//
// Created by cgsdfc on 19-6-10.
//

#ifndef ITERTOOLS_COUNT_H
#define ITERTOOLS_COUNT_H
#include <cstddef>
#include <type_traits>
#include <iterator>
#include "macros.h"

namespace itertools {
namespace detail::count {
/// Implementation of count() and count(start).
template <class T>
class single_step_iterator {
  T cnt_ = 0;
public:
  single_step_iterator() = default;
  explicit single_step_iterator(T cnt) : cnt_(cnt_) {}
  T operator*() const {
    return cnt_;
  }
  bool operator==(const single_step_iterator &) const {
    return false; // To be infinite.
  }
  single_step_iterator &operator++() {
    cnt_ += 1; // Number may be float, which does not support ++.
    return *this;
  }
  ITERTOOLS_IMPL_NEQ_POST_INC(single_step_iterator)
};
}

template <class Number = std::size_t, std::size_t Args = 0>
class count {
public:
  using value_type = std::size_t;
  using iterator = detail::count::single_step_iterator<value_type>;

  count() = default;
  iterator begin() {
    return {};
  }
  iterator end() {
    return {};
  }
  ITERTOOLS_IMPL_CONST_BEGIN_END(count)
};

template <class Number>
class count<Number, 1> {
public:
  using value_type = Number;
  using iterator = detail::count::single_step_iterator<value_type>;
  explicit count(value_type start) : start_(start) {}
  iterator begin() {
    return iterator(start_);
  }
  iterator end() {
    return {};
  }
  ITERTOOLS_IMPL_CONST_BEGIN_END(count)
private:
  value_type start_;
};

namespace detail::count {
template <class Integral>
class integral_iterator : public std::iterator<std::forward_iterator_tag, Integral> {
  Integral start_;
  Integral step_;
public:
  // Only begin() is valid.
  integral_iterator() = default;
  integral_iterator(Integral start, Integral step) : start_(start), step_(step) {}
  Integral operator*() const {
    return start_;
  }
  integral_iterator &operator++() {
    start_ += step_;
    return *this;
  }
  bool operator==(const integral_iterator &) const {
    return false;
  }
  ITERTOOLS_IMPL_NEQ_POST_INC(integral_iterator)
};

template <class FloatingPoint>
class floating_point_iterator : public std::iterator<std::forward_iterator_tag, FloatingPoint> {
  FloatingPoint start_;
  FloatingPoint step_;
  std::size_t cnt_ = 0;
public:
  floating_point_iterator() = default;
  floating_point_iterator(FloatingPoint start, FloatingPoint step) : start_(start), step_(step) {}
  FloatingPoint operator*() const {
    return start_ + cnt_ * step_;
  }
  floating_point_iterator &operator++() {
    ++cnt_;
    return *this;
  }
  bool operator==(const floating_point_iterator &) const {
    return false;
  }
  ITERTOOLS_IMPL_NEQ_POST_INC(floating_point_iterator)
};
}

/// count(start, step) -> start, start+step, start+2*step, ...
template <class Number>
class count<Number, 2> {
public:
  using value_type = Number;
  count(value_type start, value_type step) : start_(start), step_(step) {}
  using iterator = typename std::conditional<std::is_integral<value_type>::value,
                                             detail::count::integral_iterator<value_type>,
                                             detail::count::floating_point_iterator<value_type>>::type;
  iterator begin() {
    return iterator(start_, step_);
  }
  iterator end() {
    return {};
  }
  ITERTOOLS_IMPL_CONST_BEGIN_END(count)
private:
  value_type start_;
  value_type step_;
};

namespace detail::count {
template <class ... Numbers>
struct number {
  // type checking.
  using is_all_arithmetic = std::conjunction<std::is_arithmetic<Numbers>...>;
  static_assert(is_all_arithmetic::value, "all arguments to count() must be of arithmetic type");
  using type = typename std::common_type<Numbers...>::type;
};

//template <>
//struct number<> {
//  using type = std::size_t;
//};
}

template <class N, class ... Numbers>
count(N, Numbers...) ->count<typename detail::count::number<N, Numbers...>::type, 1 + sizeof...(Numbers)>;

count()->count<>;
}

#endif //ITERTOOLS_COUNT_H
