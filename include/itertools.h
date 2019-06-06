//
// Created by cgsdfc on 19-6-3.
//

#ifndef ITERTOOLS_ITERTOOLS_H
#define ITERTOOLS_ITERTOOLS_H

#include <iterator>
#include <catch2/catch.hpp>
#include <type_traits>
#include <iostream>
#include <cstring>

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

#define ITERTOOLS_IMPL_MUTABLE_BEGIN_END(type_name) \
  iterator begin() const {\
    return const_cast<type_name *>(this)->begin();\
  }\
  iterator end() const {\
    return const_cast<type_name *>(this)->end();\
  }

using enumerate_index_type = int;

template <class Iterable>
class enumerate {
public:
  using traits = iterable_traits<Iterable>;
  using wrapped_iterable = typename traits::wrapped_iterable;
  using raw_iterator = typename traits::raw_iterator;
  using value_type = std::pair<enumerate_index_type, typename traits::value_type>;

  class iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    using Iterator = raw_iterator;
    Iterator iter_;
    enumerate_index_type start_;
  public:
    iterator(Iterator iterator, enumerate_index_type start) : iter_(iterator), start_(start) {}
    bool operator==(const iterator &that) const {
      return iter_ == that.iter_;
    }
    bool operator!=(const iterator &that) const {
      return !operator==(that);
    }
    iterator &operator++() {
      ++iter_;
      ++start_;
      return *this;
    }
    value_type operator*() const {
      return {start_, *iter_};
    }
  };

  explicit enumerate(Iterable &&iterable, enumerate_index_type start = 0)
      : iterable_(std::forward<Iterable>(iterable)), start_(start) {}

  iterator begin() {
    return iterator(std::begin(iterable_), start_);
  }
  iterator end() {
    return iterator(std::end(iterable_), 0);
  }
  ITERTOOLS_IMPL_MUTABLE_BEGIN_END(enumerate)
private:
  wrapped_iterable iterable_;
  enumerate_index_type start_;
};

template <class Iterable> enumerate(Iterable &, enumerate_index_type= 0) -> enumerate<Iterable &>;
template <class Iterable> enumerate(Iterable &&, enumerate_index_type= 0) -> enumerate<Iterable &&>;

template <class ... Iterables>
class zip {
public:
  using value_type = std::tuple<typename iterable_traits<Iterables>::value_type...>;
  using wrapped_iterables = std::tuple<typename iterable_traits<Iterables>::wrapped_iterable ...>;
  using raw_iterators = std::tuple<typename iterable_traits<Iterables>::raw_iterator ...>;
  using index_sequence = std::index_sequence_for<Iterables...>;

  class iterator {
    raw_iterators iterators_;
  public:
    explicit iterator(raw_iterators iterators) : iterators_(std::move(iterators)) {}
    bool operator==(const iterator &that) const {
      // any of these iterators equal.
      return compare(that, index_sequence());
    }
    bool operator!=(const iterator &that) const {
      return !operator==(that);
    }
    value_type operator*() const {
      return star_all(index_sequence());
    }
    iterator &operator++() {
      inc_all(index_sequence());
      return *this;
    }
  private:
    template <std::size_t ... Is>
    bool compare(const iterator &that, std::index_sequence<Is...>) const {
      return (... || (std::get<Is>(iterators_) == std::get<Is>(that.iterators_)));
    }
    template <std::size_t ... Is>
    value_type star_all(std::index_sequence<Is ...>) const {
      return {(*std::get<Is>(iterators_))...};
    }
    template <std::size_t ... Is>
    void inc_all(std::index_sequence<Is ...>) {
      (++std::get<Is>(iterators_), ...);
    }
  };

  explicit zip(Iterables &&...iterables) : iterables_(std::forward<Iterables>(iterables)...) {}

  iterator begin() {
    return iterator(begin_impl(index_sequence()));
  }
  iterator end() {
    return iterator(end_impl(index_sequence()));
  }
  ITERTOOLS_IMPL_MUTABLE_BEGIN_END(zip)
private:
  wrapped_iterables iterables_;
  template <std::size_t ... Is>
  iterator begin_impl(std::index_sequence<Is...>) {
    return iterator(std::tuple(std::begin(std::get<Is>(iterables_))...));
  }
  template <std::size_t ... Is>
  iterator end_impl(std::index_sequence<Is...>) {
    return iterator(std::tuple(std::end(std::get<Is>(iterables_))...));
  }
};

template <class ... Iterables>
zip(Iterables &&...) -> zip<Iterables && ...>;

template <class Integer>
class range_iterator : public std::iterator<std::forward_iterator_tag, Integer> {
  static_assert(std::is_integral_v<Integer>, "range_iterator must handle integer");
  std::size_t cur_ = 0;
  Integer start_;
  Integer step_;
public:
  using value_type = Integer;
  range_iterator(std::size_t cur, Integer start, Integer step)
      : cur_(cur), start_(start), step_(step) {}
  Integer operator*() const {
    return start_ + cur_ * step_;
  }
  bool operator==(const range_iterator &that) const {
    return cur_ == that.cur_;
  }
  bool operator!=(const range_iterator &that) const {
    return !(that == *this);
  }
  range_iterator &operator++() {
    ++cur_;
  }
};

template <class Integer>
class range {
  using iterator = range_iterator<Integer>;
  Integer start_ = 0;
  Integer stop_;
  Integer step_ = 1;
  std::size_t length_;

  std::size_t compute_length() const {
    Integer low, high;
    std::size_t pos_step;
    if (step_ > 0) {
      low = start_;
      high = stop_;
      pos_step = step_;
    } else {
      low = stop_;
      high = start_;
      pos_step = -step_;
    }
    if (low > high)
      return 0;
    return ((high - low - 1) / pos_step) + 1;
  }

public:
  explicit range(Integer stop) : range(0, stop, 1) {}
  range(Integer start, Integer stop) : range(start, stop, 1) {}
  range(Integer start, Integer stop, Integer step)
      : start_(start), stop_(stop), step_(step) {
    length_ = compute_length();
  }

  iterator begin() const {
    return {0, start_, step_};
  }

  iterator end() const {
    return {length_, start_, step_};
  }
};

#if 0
template <class Callable, class ... Iterators>
using map_value_type = std::invoke_result_t<Callable, typename std::iterator_traits<Iterators>::value_type ...>;

template <class Callable, class ... Iterators>
class map_iterator : public std::iterator<std::forward_iterator_tag, map_value_type<Callable, Iterators...>> {
  Callable func_;
  zip_iterator<Iterators...> args_;
public:
  using value_type = map_value_type<Callable, Iterators...>;
  explicit map_iterator(Callable func, Iterators ... iterators) : func_(func), args_(iterators...) {}
  bool operator==(const map_iterator &rhs) const {
    return args_ == rhs.args_;
  }
  bool operator!=(const map_iterator &rhs) const {
    return !(rhs == *this);
  }
  map_iterator &operator++() {
    ++args_;
    return *this;
  }
  value_type operator*() const {
    auto &&arg_tuple = *args_;
    return std::apply(func_, arg_tuple);
  }
};

template <class Callable, class ... Iterables>
class map : public IterableAdapter<map_iterator<Callable, iter_from_iterable < Iterables>...>>
{
public:
using Base = IterableAdapter<map_iterator<Callable, iter_from_iterable < Iterables>...>>;
using iterator = typename Base::iterator;
explicit map(Callable func, Iterables &... iterables) : Base(
    iterator(func, std::begin(iterables)...),
    iterator(func, std::end(iterables)...)
) {}
};

template <class Integer>
class count_iterator {
  Integer start_ = 0;
  Integer step_ = 1;
public:
  count_iterator(Integer start, Integer step) : start_(start), step_(step) {}

};
#endif
}

#endif //ITERTOOLS_ITERTOOLS_H
