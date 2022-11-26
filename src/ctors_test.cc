#include <gtest/gtest.h>
#include <string>
#include <memory>
#include <tuple>
#include "my_string.h"

template <template <typename _CharT,
                    typename _Traits,
                    typename _Alloc> Tuple<_CharT, _Traits, _Alloc
                   >
>
class ConstructorsTest : public testing::Test {
 public:
  using MyTypedString = MyTypes::MyBasicString<_CharT>;
};

#if __cplusplus > 201703L
using MyParamTypes = tesing::Types<char, char16_t, char32_t, wchar_t , char8_t>;
#else
using MyParamTypes = testing::Types<char, char16_t, char32_t, wchar_t>;
#endif

TYPED_TEST_SUITE(ConstructorsTest, MyParamTypes);

TYPED_TEST(ConstructorsTest, EmptyStirng) {
  //Arrange
  typename TestFixture::MyTypedString str; 
  //Act

  //Assert
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(str.size(), 0);
  EXPECT_GT(str.capacity(), 0);
}
