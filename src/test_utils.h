#ifndef _TESTS_UTILS_H
#define _TESTS_UTILS_H

#include <iostream>
#include <algorithm>
#include <string>
#include <gtest/gtest.h>

#include "my_string.h"

#define EXPECT_STREQ_CUSTOM(__cStr1, __cStr1Len, __cStr2, __cStr2Len) \
  EXPECT_TRUE( \
    TestingHelper::_CustomStrEq(__cStr1, __cStr1Len, __cStr2, __cStr2Len) \
  )

#define ADJUST_POS_LOCAL(__length, __pos) \
  TestFixture::_Adjust(__length, __pos, TestingHelper::Adjustment::LOCAL)

#define ADJUST_POS_DYNAMIC(__length, __pos) \
  TestFixture::_Adjust(__length, __pos, TestingHelper::Adjustment::DYNAMIC)

#define ADJUST_POS_COUNT_LOCAL(__length, __pos, __count) \
  TestFixture::_Adjust(__length, __pos, TestingHelper::Adjustment::LOCAL)

#define ADJUST_POS_COUNT_DYNAMIC(__length, __pos, __count) \
  TestFixture::_Adjust(__length, __pos, TestingHelper::Adjustment::DYNAMIC)

#define ADJUST_OUT(__reqested, __var) \
  __var = (__var > __reqested) ? __var : __reqested

#define ADJUST_IN(__reqested, __var) \
  __var = (__var < __reqested) ? __var : __reqested

namespace TestingHelper {

enum Adjustment { LOCAL, DYNAMIC };

template <typename _Tuple>
class StringTestingBase : public ::testing::Test {
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

 protected:
// Instantiation different string type depending on provided tuple 
  using MyTestingString = std::conditional_t<
    std::is_same_v<_Traits, void>,
    MyTypes::MyBasicString<_CharT>,
    std::conditional_t<std::is_same_v<_Alloc, void>,
      MyTypes::MyBasicString<_CharT, _Traits>,
      MyTypes::MyBasicString<_CharT, _Traits, _Alloc>
    >
  >;
  
  using value_type = typename MyTestingString::value_type;
  using allocator_type = typename MyTestingString::allocator_type;
  using size_type = typename MyTestingString::size_type;

  const size_type _localBufferCapThreshold =  LOCAL_CAPACITY /
    sizeof(typename MyTestingString::value_type);
  const size_type _localBufferLenThreshold =  _localBufferCapThreshold - 1;

  const std::initializer_list<value_type> _str1 = 
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
  const std::initializer_list<value_type> _str2 =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i','n', 'g', ' ', 's', 'u', 'n'};

  void SetUp() override {
    ASSERT_GT(_str1.size(), _localBufferCapThreshold);
    ASSERT_GT(_str2.size(), _localBufferCapThreshold);
  }

  void _Adjust(const size_type __length, size_type& __pos,
    TestingHelper::Adjustment __adjust) {
    size_type __count = __length + 1;
    _Adjust(__length, __pos, __count, __adjust);
}

  void _Adjust(const size_type __length, size_type& __pos, size_type& __count,
    TestingHelper::Adjustment __adjust) {
    if (__pos < 0) { __pos = 0; }
    switch (__adjust) {
      case TestingHelper::LOCAL: {
        if (__count <= 0 || __count > _localBufferLenThreshold) {
          __count = _localBufferLenThreshold;
        }
        if (__pos + __count < __length) {
          __pos = __length - __count;
        }
        break;
      }
      case TestingHelper::DYNAMIC: {
        if (__count <= _localBufferLenThreshold || __count > __length) {
          __count = _localBufferLenThreshold + 1;
        }
        if (__pos + __count > __length) {
          __pos = __length - __count;
        }
        break;
      }
    }
  }
};

int _CompareHelper(size_t __count1, size_t __count2);

template <typename _CharT>
int _CustomStrCmp(const _CharT* __cStr1, const size_t __len1,
  const _CharT* __cStr2, const size_t __len2) {
  const size_t __minLength = std::min(__len1, __len2);

  int __res = std::char_traits<_CharT>::compare(__cStr1, __cStr2, __minLength);

  if (__res == 0) {
    __res = _CompareHelper(__len1, __len2);
  }
  return __res;
}

template <typename _CharT>
::testing::AssertionResult _CustomStrEq(const _CharT* __cStr1,
    const size_t __len1, const _CharT* __cStr2, const size_t __len2) {
  return (_CustomStrCmp(__cStr1, __len1, __cStr2, __len2) == 0) ?
    ::testing::AssertionSuccess() : ::testing::AssertionFailure();
}

} // namespace TestingHelper

#endif // _TESTS_UTILS_H
