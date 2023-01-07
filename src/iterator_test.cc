#include <gtest/gtest.h>

#include <iostream>
#include "test_utils.h"

template <typename _Tuple>
class IteratorTests : public TestingHelper::IteratorTestingBase<_Tuple> {};

using MyParamTypes = testing::Types<
// For types defined in standards after C++17
#if __cplusplus > 201703L
  std::tuple<char8_t, char8_t*>
#endif
  std::tuple<char, char*>,
  std::tuple<char16_t, char16_t*>,
  std::tuple<char32_t, char32_t*>,
  std::tuple<wchar_t, wchar_t*>
>;

TYPED_TEST_SUITE(IteratorTests, MyParamTypes);
