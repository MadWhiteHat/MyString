#ifndef _TESTS_UTILS_H
#define _TESTS_UTILS_H

#include <iostream>
#include <algorithm>
#include <string>
#include <gtest/gtest.h>

#include "my_string.h"

namespace TestingHelper {

template <typename _Tuple>
class TestingBase : public testing::Test {
 private:
  static_assert(std::tuple_size_v<_Tuple> < size_t(4) &&
    std::tuple_size_v<_Tuple> > size_t(0),
    "For testing input tuple must have CharType, [TraitsType], [AllocType]");
  using _CharT = std::tuple_element_t<0, _Tuple>;

  template <size_t _N, bool = false>
  struct _TupleHelper {
    using type = void;
  };

  template <size_t _N>
  struct _TupleHelper<_N, true> {
    using type = std::tuple_element_t<_N, _Tuple>;
  };

  template <size_t _N, bool _B>
  using _TupleHelperT = typename _TupleHelper<_N, _B>::type;

  using _Traits = _TupleHelperT<1,
    std::greater_equal<size_t>()(std::tuple_size_v<_Tuple>, 2)>; 
  
  using _Alloc = _TupleHelperT<2,
    std::greater_equal<size_t>()(std::tuple_size_v<_Tuple>, 3)>;

 public:
// Instantiation different string type depending on provided tuple 
  using MyTestingString = std::conditional_t<
    std::is_same_v<_Traits, void>,
    MyTypes::MyBasicString<_CharT>,
    std::conditional_t<std::is_same_v<_Alloc, void>,
      MyTypes::MyBasicString<_CharT, _Traits>,
      MyTypes::MyBasicString<_CharT, _Traits, _Alloc>
    >
  >;
  const typename MyTestingString::size_type _localBufferCapThreshold = 
    LOCAL_CAPACITY / sizeof(typename MyTestingString::value_type);
  const typename MyTestingString::size_type _localBufferLenThreshold =
    _localBufferCapThreshold - 1;

  inline void LengthTest(const _CharT* __cStr) {
    ASSERT_GT(std::char_traits<_CharT>::length(__cStr),
     _localBufferLenThreshold);
  }
};

int _CompareHelper(size_t __count1, size_t __count2);

template <typename _CharT>
int CustomStrCmp(const _CharT* __cStr1, const size_t __len1,
  const _CharT* __cStr2, const size_t __len2) {
  const size_t __minLength = std::min(__len1, __len2);

  int __res = std::char_traits<_CharT>::compare(__cStr1, __cStr2, __minLength);

  if (__res == 0) {
    __res = _CompareHelper(__len1, __len2);
  }
  return __res;
}
} // namespace TesingHelper

#endif // _TESTS_UTILS_H
