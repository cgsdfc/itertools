//
// Created by cgsdfc on 19-6-3.
//

#ifndef ITERTOOLS_ITERTOOLS_H
#define ITERTOOLS_ITERTOOLS_H
#include <iterator>

namespace itertools {

// Adapt an Iterator class to an Iterable class.
template <class Iterator>
class IterableAdapter {
  Iterator begin_;
  Iterator end_;
public:
  using iterator = Iterator;
  IterableAdapter(Iterator begin, Iterator end) : begin_(begin), end_(end) {}
  Iterator begin() const { return begin_; }
  Iterator end() const { return end_; }
};

template <class Iterable>
using iterator_maybe_const = std::conditional_t<std::is_const_v<Iterable>,
                                                decltype(std::cbegin(std::declval<Iterable>())),
                                                decltype(std::begin(std::declval<Iterable>()))>;

template <template <class...> class FunctionIterator, class ... Iterable>
using IterableWrapper = IterableAdapter<
    FunctionIterator<iterator_maybe_const<Iterable>...>
>;

using enum_index_type = int;

template <class Iterator>
using enum_value_type = std::pair<int, typename std::iterator_traits<Iterator>::reference>;

template <class Iterator>
class enum_iterator : public std::iterator<std::forward_iterator_tag, enum_value_type<Iterator>> {
  Iterator iter_;
  enum_index_type start_;
public:
  using value_type = enum_value_type<Iterator>;
  explicit enum_iterator(Iterator iterator, enum_index_type start = 0) : iter_(iterator), start_(start) {}
  bool operator==(const enum_iterator &that) const {
    return iter_ == that.iter_;
  }
  bool operator!=(const enum_iterator &that) const {
    return !operator==(that);
  }
  enum_iterator &operator++() {
    ++iter_;
    ++start_;
    return *this;
  }
  value_type operator*() const {
    return {start_, *iter_};
  }
};

template <class Iterable>
class enumerate : public IterableWrapper<enum_iterator, Iterable> {
public:
  using Base =  IterableWrapper<enum_iterator, Iterable>;
  using iterator = typename Base::iterator;

  explicit enumerate(Iterable &iterable, enum_index_type start = 0) : Base(
      iterator(std::begin(iterable), start),
      iterator(std::end(iterable))
  ) {}
};

// A tuple of references.
template <class ... Iterators>
using zip_value_type = std::tuple<typename std::iterator_traits<Iterators>::reference ...>;

template <class ... Iterators>
class zip_iterator : public std::iterator<std::forward_iterator_tag, zip_value_type<Iterators...>> {
  using index_sequence = std::index_sequence_for<Iterators...>;
  std::tuple<Iterators...> iterators_;
  template <std::size_t ... Is>
  bool compare(const zip_iterator &that, std::index_sequence<Is...>) const {
    return (... || (std::get<Is>(iterators_) == std::get<Is>(that.iterators_)));
  }
  template <std::size_t ... Is>
  auto star_all(std::index_sequence<Is ...>) const {
    return std::make_tuple((*std::get<Is>(iterators_))...);
  }
  template <std::size_t ... Is>
  void inc_all(std::index_sequence<Is ...>) {
    (++std::get<Is>(iterators_), ...);
  }

public:
  using value_type = zip_value_type<Iterators...>;
  explicit zip_iterator(Iterators ... iterator) : iterators_(iterator...) {}

  bool operator==(const zip_iterator &that) const {
    // any of these iterators equal.
    return compare(that, index_sequence());
  }
  bool operator!=(const zip_iterator &that) const {
    return !operator==(that);
  }
  value_type operator*() const {
    return star_all(index_sequence());
  }
  zip_iterator &operator++() {
    inc_all(index_sequence());
    return *this;
  }
};

template <class ... Iterables>
class zip : public IterableWrapper<zip_iterator, Iterables...> {
  using Base = IterableWrapper<zip_iterator, Iterables...>;
  using iterator = typename Base::iterator;
public:
  explicit zip(Iterables &... iterables) : Base(
      iterator(std::begin(iterables)...),
      iterator(std::end(iterables)...)
  ) {}
};

}

#endif //ITERTOOLS_ITERTOOLS_H
