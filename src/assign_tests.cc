#include <gtest/gtest.h>

#include "test_utils.h"

template <typename _Tuple>
class AssignTests : public TestingHelper::TestingBase<_Tuple> {};

using MyParamTypes = testing::Types<
// For types defined in standards after C++17
#if __cplusplus > 201703L
  std::tuple<char8_t>
#endif
 std::tuple<char>,
 std::tuple<char16_t>,
 std::tuple<char32_t>,
 std::tuple<wchar_t>,
 std::tuple<char, std::char_traits<char>>,
 std::tuple<char, std::char_traits<char>, std::pmr::polymorphic_allocator<char>>
>;


TYPED_TEST_SUITE(AssignTests, MyParamTypes);

TYPED_TEST(AssignTests, AssignOperatorMyStringLocal) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};  
  typename TestFixture::MyTestingString __other(__cStr,
       TestFixture::_localBufferThreshold - 1);
  typename TestFixture::MyTestingString __str;

  //Act
  __str = __other;

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}
