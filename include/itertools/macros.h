//
// Created by cgsdfc on 19-6-6.
//

#ifndef ITERTOOLS_MACROS_H
#define ITERTOOLS_MACROS_H

#define ITERTOOLS_IMPL_CONST_BEGIN_END(type_name) \
  iterator begin() const {\
    return const_cast<type_name *>(this)->begin();\
  }\
  iterator end() const {\
    return const_cast<type_name *>(this)->end();\
  }

#define ITERTOOLS_IMPL_NEQ(type_name) \
  bool operator!=(const type_name &that) const { \
    return !operator==(that); \
  } \


#endif //ITERTOOLS_MACROS_H
