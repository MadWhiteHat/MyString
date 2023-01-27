#include <gtest/gtest.h>
#include <memory_resource>
#include <string>
#include <memory>
#include <tuple>
#include <type_traits>

#include "test_utils.h"
#include "my_exception.h"

template <typename _Tuple>
class ConcatTests : public TestingHelper::StringTestingBase<_Tuple> {};
using TestingHelper::MyParamTypes;

TYPED_TEST_SUITE(ConcatTests, MyParamTypes);

TYPED_TEST(ConcatTests, MyStringMyStringLocalAndLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const typename TestFixture::MyTestingString __str2(__ilist2.begin(),
    __initLen);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2.begin(), __initLen);
  auto __cmp3 = __cmp1 + __cmp2;

  //Act
  auto __str3 = __str1 + __str2;

  //Assert
  EXPECT_EQ(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MyStringMyStringLocalAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = __cmp1 + __cmp2;

  //Act
  auto __str3 = __str1 + __str2;

  //Assert
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MyStringMyStringDynamicAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = __cmp1 + __cmp2;

  //Act
  auto __str3 = __str1 + __str2;

  //Assert
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MyStringSTLStringLocalAndLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const typename TestFixture::STLString __str2(__ilist2.begin(), __initLen);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2.begin(), __initLen);
  auto __cmp3 = __cmp1 + __cmp2;

  //Act
  auto __str3 = __str1 + __str2;

  //Assert
  EXPECT_EQ(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MyStringSTLStringLocalAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const typename TestFixture::STLString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = __cmp1 + __cmp2;

  //Act
  auto __str3 = __str1 + __str2;

  //Assert
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MyStringSTLStringDynamicAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::STLString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = __cmp1 + __cmp2;

  //Act
  auto __str3 = __str1 + __str2;

  //Assert
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, STLStringMyStringLocalAndLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::STLString __str1(__ilist1.begin(), __initLen);
  const typename TestFixture::MyTestingString __str2(__ilist2.begin(),
    __initLen);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2.begin(), __initLen);
  auto __cmp3 = __cmp1 + __cmp2;

  //Act
  auto __str3 = __str1 + __str2;

  //Assert
  EXPECT_EQ(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, STLStringMyStringLocalAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::STLString __str1(__ilist1.begin(), __initLen);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = __cmp1 + __cmp2;

  //Act
  auto __str3 = __str1 + __str2;

  //Assert
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, STLStringMyStringDynamicAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::STLString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = __cmp1 + __cmp2;

  //Act
  auto __str3 = __str1 + __str2;

  //Assert
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MyStringCStrLocalAndLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const typename TestFixture::STLString __str2(__ilist2.begin(),
    __initLen);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2.begin(), __initLen);
  auto __cmp3 = __cmp1 + __cmp2.data();

  //Act
  auto __str3 = __str1 + __str2.data();

  //Assert
  EXPECT_EQ(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MyStringCStrLocalAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const typename TestFixture::STLString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = __cmp1 + __cmp2.data();

  //Act
  auto __str3 = __str1 + __str2.data();

  //Assert
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MyStringCStrDynamicAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::STLString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = __cmp1 + __cmp2.data();

  //Act
  auto __str3 = __str1 + __str2.data();

  //Assert
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MyStringCharLocalAndLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold - 1;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const value_type __ch = *(__ilist2.begin());

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  auto __cmp2 = __cmp1 + __ch;

  //Act
  auto __str2 = __str1 + __ch;

  //Assert
  EXPECT_EQ(__str2.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str2.data(), __str2.length(), __cmp2.data(),
    __cmp2.length());
}

TYPED_TEST(ConcatTests, MyStringCharLocalAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const value_type __ch = *(__ilist2.begin());

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  auto __cmp2 = __cmp1 + __ch;

  //Act
  auto __str2 = __str1 + __ch;

  //Assert
  EXPECT_GT(__str2.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str2.data(), __str2.length(), __cmp2.data(),
    __cmp2.length());
}

TYPED_TEST(ConcatTests, MyStringCharDynamicAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const value_type __ch = *(__ilist2.begin());

  const typename TestFixture::STLString __cmp1(__ilist1);
  auto __cmp2 = __cmp1 + __ch;

  //Act
  auto __str2 = __str1 + __ch;

  //Assert
  EXPECT_GT(__str2.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str2.data(), __str2.length(), __cmp2.data(),
    __cmp2.length());
}

TYPED_TEST(ConcatTests, CStrMyStringLocalAndLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::STLString __str1(__ilist1.begin(), __initLen);
  const typename TestFixture::MyTestingString __str2(__ilist2.begin(),
    __initLen);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2.begin(), __initLen);
  auto __cmp3 = __cmp1.data() + __cmp2;

  //Act
  auto __str3 = __str1.data() + __str2;

  //Assert
  EXPECT_EQ(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, CStrMyStringLocalAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::STLString __str1(__ilist1.begin(), __initLen);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = __cmp1.data() + __cmp2;

  //Act
  auto __str3 = __str1.data() + __str2;

  //Assert
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, CStrMyStringDynamicAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::STLString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = __cmp1.data() + __cmp2;

  //Act
  auto __str3 = __str1.data() + __str2;

  //Assert
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, CharMyStringLocalAndLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold - 1;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const value_type __ch = *(__ilist2.begin());

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  auto __cmp2 = __ch + __cmp1;

  //Act
  auto __str2 = __ch + __str1;

  //Assert
  EXPECT_EQ(__str2.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str2.data(), __str2.length(), __cmp2.data(),
    __cmp2.length());
}

TYPED_TEST(ConcatTests, CharMyStringLocalAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const value_type __ch = *(__ilist2.begin());

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  auto __cmp2 = __ch + __cmp1;

  //Act
  auto __str2 = __ch + __str1;

  //Assert
  EXPECT_GT(__str2.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str2.data(), __str2.length(), __cmp2.data(),
    __cmp2.length());
}

TYPED_TEST(ConcatTests, CharMyStringDynamicAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const value_type __ch = *(__ilist2.begin());

  const typename TestFixture::STLString __cmp1(__ilist1);
  auto __cmp2 = __ch + __cmp1;

  //Act
  auto __str2 = __ch + __str1;

  //Assert
  EXPECT_GT(__str2.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str2.data(), __str2.length(), __cmp2.data(),
    __cmp2.length());
}

TYPED_TEST(ConcatTests, MoveMyStringMoveMyStringLocalAndLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const typename TestFixture::MyTestingString __str2(__ilist2.begin(),
    __initLen);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2.begin(), __initLen);
  auto __cmp3 = std::move(__cmp1) + std::move(__cmp2);

  //Act
  auto __str3 = std::move(__str1) + std::move(__str2);

  //Assert
  EXPECT_EQ(__str1.empty(), __cmp1.empty());
  EXPECT_EQ(__str2.empty(), __cmp2.empty());
  EXPECT_EQ(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MoveMyStringMoveMyStringLocalAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = std::move(__cmp1) + std::move(__cmp2);

  //Act
  auto __str3 = std::move(__str1) + std::move(__str2);

  //Assert
  EXPECT_EQ(__str1.empty(), __cmp1.empty());
  EXPECT_EQ(__str2.empty(), __cmp2.empty());
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MoveMyStringMoveMyStringDynamicAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = std::move(__cmp1) + std::move(__cmp2);

  //Act
  auto __str3 = std::move(__str1) + std::move(__str2);

  //Assert
  EXPECT_EQ(__str1.empty(), __cmp1.empty());
  EXPECT_EQ(__str2.empty(), __cmp2.empty());
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MoveMyStringMyStringLocalAndLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const typename TestFixture::MyTestingString __str2(__ilist2.begin(),
    __initLen);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2.begin(), __initLen);
  auto __cmp3 = std::move(__cmp1) + __cmp2;

  //Act
  auto __str3 = std::move(__str1) + __str2;

  //Assert
  EXPECT_EQ(__str1.empty(), __cmp1.empty());
  EXPECT_EQ(__str2.empty(), __cmp2.empty());
  EXPECT_EQ(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MoveMyStringMyStringLocalAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = std::move(__cmp1) + __cmp2;

  //Act
  auto __str3 = std::move(__str1) + __str2;

  //Assert
  EXPECT_EQ(__str1.empty(), __cmp1.empty());
  EXPECT_EQ(__str2.empty(), __cmp2.empty());
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MoveMyStringMyStringDynamicAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = std::move(__cmp1) + __cmp2;

  //Act
  auto __str3 = std::move(__str1) + __str2;

  //Assert
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MoveMyStringSTLStringLocalAndLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const typename TestFixture::STLString __str2(__ilist2.begin(), __initLen);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2.begin(), __initLen);
  auto __cmp3 = std::move(__cmp1) + __cmp2;

  //Act
  auto __str3 = std::move(__str1) + __str2;

  //Assert
  EXPECT_EQ(__str1.empty(), __cmp1.empty());
  EXPECT_EQ(__str2.empty(), __cmp2.empty());
  EXPECT_EQ(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MoveMyStringSTLStringLocalAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const typename TestFixture::STLString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = std::move(__cmp1) + __cmp2;

  //Act
  auto __str3 = std::move(__str1) + __str2;

  //Assert
  EXPECT_EQ(__str1.empty(), __cmp1.empty());
  EXPECT_EQ(__str2.empty(), __cmp2.empty());
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MoveMyStringSTLStringDynamicAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::STLString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = std::move(__cmp1) + __cmp2;

  //Act
  auto __str3 = std::move(__str1) + __str2;

  //Assert
  EXPECT_EQ(__str1.empty(), __cmp1.empty());
  EXPECT_EQ(__str2.empty(), __cmp2.empty());
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MoveMyStringCStrLocalAndLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const typename TestFixture::STLString __str2(__ilist2.begin(),
    __initLen);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2.begin(), __initLen);
  auto __cmp3 = std::move(__cmp1) + __cmp2.data();

  //Act
  auto __str3 = std::move(__str1) + __str2.data();

  //Assert
  EXPECT_EQ(__str1.empty(), __cmp1.empty());
  EXPECT_EQ(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MoveMyStringCStrLocalAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const typename TestFixture::STLString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = std::move(__cmp1) + __cmp2.data();

  //Act
  auto __str3 = std::move(__str1) + __str2.data();

  //Assert
  EXPECT_EQ(__str1.empty(), __cmp1.empty());
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MoveMyStringCStrDynamicAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::STLString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = std::move(__cmp1) + __cmp2.data();

  //Act
  auto __str3 = std::move(__str1) + __str2.data();

  //Assert
  EXPECT_EQ(__str1.empty(), __cmp1.empty());
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MoveMyStringCharLocalAndLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold - 1;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const value_type __ch = *(__ilist2.begin());

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  auto __cmp2 = std::move(__cmp1) + __ch;

  //Act
  auto __str2 = std::move(__str1) + __ch;

  //Assert
  EXPECT_EQ(__str1.empty(), __cmp1.empty());
  EXPECT_EQ(__str2.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str2.data(), __str2.length(), __cmp2.data(),
    __cmp2.length());
}

TYPED_TEST(ConcatTests, MoveMyStringCharLocalAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const value_type __ch = *(__ilist2.begin());

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  auto __cmp2 = std::move(__cmp1) + __ch;

  //Act
  auto __str2 = std::move(__str1) + __ch;

  //Assert
  EXPECT_EQ(__str1.empty(), __cmp1.empty());
  EXPECT_GT(__str2.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str2.data(), __str2.length(), __cmp2.data(),
    __cmp2.length());
}

TYPED_TEST(ConcatTests, MoveMyStringCharDynamicAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const value_type __ch = *(__ilist2.begin());

  const typename TestFixture::STLString __cmp1(__ilist1);
  auto __cmp2 = std::move(__cmp1) + __ch;

  //Act
  auto __str2 = std::move(__str1) + __ch;

  //Assert
  EXPECT_EQ(__str1.empty(), __cmp1.empty());
  EXPECT_GT(__str2.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str2.data(), __str2.length(), __cmp2.data(),
    __cmp2.length());
}

TYPED_TEST(ConcatTests, MyStringMoveMyStringLocalAndLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const typename TestFixture::MyTestingString __str2(__ilist2.begin(),
    __initLen);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2.begin(), __initLen);
  auto __cmp3 = __cmp1 + std::move(__cmp2);

  //Act
  auto __str3 = __str1 + std::move(__str2);

  //Assert
  EXPECT_EQ(__str1.empty(), __cmp1.empty());
  EXPECT_EQ(__str2.empty(), __cmp2.empty());
  EXPECT_EQ(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MyStringMoveMyStringLocalAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = __cmp1 + std::move(__cmp2);

  //Act
  auto __str3 = __str1 + std::move(__str2);

  //Assert
  EXPECT_EQ(__str1.empty(), __cmp1.empty());
  EXPECT_EQ(__str2.empty(), __cmp2.empty());
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, MyStringMoveMyStringDynamicAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = __cmp1 + std::move(__cmp2);

  //Act
  auto __str3 = __str1 + std::move(__str2);

  //Assert
  EXPECT_EQ(__str1.empty(), __cmp1.empty());
  EXPECT_EQ(__str2.empty(), __cmp2.empty());
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, STLStringMoveMyStringLocalAndLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::STLString __str1(__ilist1.begin(), __initLen);
  const typename TestFixture::MyTestingString __str2(__ilist2.begin(),
    __initLen);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2.begin(), __initLen);
  auto __cmp3 = __cmp1 + std::move(__cmp2);

  //Act
  auto __str3 = __str1 + std::move(__str2);

  //Assert
  EXPECT_EQ(__str2.empty(), __cmp2.empty());
  EXPECT_EQ(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, STLStringMoveMyStringLocalAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::STLString __str1(__ilist1.begin(), __initLen);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = __cmp1 + std::move(__cmp2);

  //Act
  auto __str3 = __str1 + std::move(__str2);

  //Assert
  EXPECT_EQ(__str2.empty(), __cmp2.empty());
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, STLStringMoveMyStringDynamicAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::STLString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = __cmp1 + std::move(__cmp2);

  //Act
  auto __str3 = __str1 + std::move(__str2);

  //Assert
  EXPECT_EQ(__str2.empty(), __cmp2.empty());
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, CstrMoveMyStringLocalAndLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::STLString __str1(__ilist1.begin(), __initLen);
  const typename TestFixture::MyTestingString __str2(__ilist2.begin(),
    __initLen);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2.begin(), __initLen);
  auto __cmp3 = __cmp1.data() + std::move(__cmp2);

  //Act
  auto __str3 = __str1.data() + std::move(__str2);

  //Assert
  EXPECT_EQ(__str2.empty(), __cmp2.empty());
  EXPECT_EQ(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, CStrMoveMyStringLocalAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const typename TestFixture::STLString __str1(__ilist1.begin(), __initLen);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = __cmp1.data() + std::move(__cmp2);

  //Act
  auto __str3 = __str1.data() + std::move(__str2);

  //Assert
  EXPECT_EQ(__str2.empty(), __cmp2.empty());
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, CStrMoveMyStringDynamicAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::STLString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __cmp3 = __cmp1.data() + std::move(__cmp2);

  //Act
  auto __str3 = __str1.data() + std::move(__str2);

  //Assert
  EXPECT_EQ(__str2.empty(), __cmp2.empty());
  EXPECT_GT(__str3.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str3.data(), __str3.length(), __cmp3.data(),
    __cmp3.length());
}

TYPED_TEST(ConcatTests, CharMoveMyStringLocalAndLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold - 1;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const value_type __ch = *(__ilist2.begin());

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  auto __cmp2 = __ch + std::move(__cmp1);

  //Act
  auto __str2 = __ch + std::move(__str1);

  //Assert
  EXPECT_EQ(__str1.empty(), __cmp1.empty());
  EXPECT_EQ(__str2.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str2.data(), __str2.length(), __cmp2.data(),
    __cmp2.length());
}

TYPED_TEST(ConcatTests, CharMoveMyStringLocalAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold;
  const typename TestFixture::MyTestingString __str1(__ilist1.begin(),
    __initLen);
  const value_type __ch = *(__ilist2.begin());

  const typename TestFixture::STLString __cmp1(__ilist1.begin(), __initLen);
  auto __cmp2 = __ch + std::move(__cmp1);

  //Act
  auto __str2 = __ch + std::move(__str1);

  //Assert
  EXPECT_EQ(__str1.empty(), __cmp1.empty());
  EXPECT_GT(__str2.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str2.data(), __str2.length(), __cmp2.data(),
    __cmp2.length());
}

TYPED_TEST(ConcatTests, CharMoveMyStringDynamicAndDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const value_type __ch = *(__ilist2.begin());

  const typename TestFixture::STLString __cmp1(__ilist1);
  auto __cmp2 = __ch + __cmp1;

  //Act
  auto __str2 = __ch + __str1;

  //Assert
  EXPECT_EQ(__str1.empty(), __cmp1.empty());
  EXPECT_GT(__str2.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str2.data(), __str2.length(), __cmp2.data(),
    __cmp2.length());
}
