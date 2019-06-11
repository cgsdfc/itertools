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
template <class Number, std::size_t Args>
class count;

template <class T>
class count_iterator {
  T cnt_ = 0;
public:
  count_iterator() = default;
  explicit count_iterator(T cnt) : cnt_(cnt_) {}
  T operator*() const {
    return cnt_;
  }
  bool operator==(const count_iterator &) const {
    return false; // To be infinite.
  }
  count_iterator &operator++() {
    cnt_ += 1; // Number may be float, which does not support ++.
    return *this;
  }
  ITERTOOLS_IMPL_NEQ_POST_INC(count_iterator)
};

template <class Number>
class count<Number, 0> {
public:
  using value_type = Number;
  using iterator = count_iterator<value_type>;

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
  using iterator = count_iterator<value_type>;
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

template <class Number>
class count<Number, 2> {
public:
  using value_type = Number;
  count(value_type start, value_type step) : start_(start), step_(step) {}
private:
  class integral_iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    value_type start_;
    value_type step_;
  public:
    integral_iterator() = default;
    integral_iterator(value_type start, value_type step) : start_(start), step_(step) {}
    value_type operator*() const {
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
  class floating_point_iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    value_type start_;
    value_type step_;
    std::size_t cnt_ = 0;
  public:
    floating_point_iterator() = default;
    floating_point_iterator(value_type start, value_type step) : start_(start), step_(step) {}
    value_type operator*() const {
      return start_ + cnt_ * step_;
    }
    floating_point_iterator &operator++() {
      ++cnt_;
      return *this;
    }
    bool operator==(const integral_iterator &) const {
      return false;
    }
    ITERTOOLS_IMPL_NEQ_POST_INC(floating_point_iterator)
  };
public:
  using iterator = typename std::conditional<std::is_integral<value_type>::value,
                                             integral_iterator,
                                             floating_point_iterator>::type;
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

namespace detail {
template <class ... Numbers>
struct count_number {
  using is_all_arithmetic = std::conjunction<std::is_arithmetic<Numbers>...>;
  static_assert(is_all_arithmetic::value, "all arguments to count() must be of arithmetic type");
  using type = typename std::common_type<Numbers...>::type;
};
}

template <class ... Numbers>
count(Numbers...) ->count<typename detail::count_number<Numbers...>::type, sizeof...(Numbers)>;
}

#endif //ITERTOOLS_COUNT_H
