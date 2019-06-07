//
// Created by cgsdfc on 19-6-3.
//

#ifndef ITERTOOLS_ITERTOOLS_H
#define ITERTOOLS_ITERTOOLS_H

#include "itertools/enumerate.h"
#include "itertools/zip.h"
#include "itertools/range.h"

namespace itertools {

#if 0


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
