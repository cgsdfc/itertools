//
// Created by cgsdfc on 19-6-6.
//

#ifndef ITERTOOLS_ZIP_H
#define ITERTOOLS_ZIP_H
#include "itertools/detail.h"
#include "macros.h"
#include <utility>

namespace itertools {

template <class ... Iterables>
class zip {
public:
  using value_type = std::tuple<typename iterable_traits<Iterables>::deref_value_type...>;
  using wrapped_iterables = std::tuple<typename iterable_traits<Iterables>::wrapped_iterable ...>;
  using raw_iterators = std::tuple<typename iterable_traits<Iterables>::raw_iterator ...>;
  using index_sequence = std::index_sequence_for<Iterables...>;

  class iterator : public std::iterator<std::forward_iterator_tag, value_type> {
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
  ITERTOOLS_IMPL_CONST_BEGIN_END(zip)
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

}
#endif //ITERTOOLS_ZIP_H
