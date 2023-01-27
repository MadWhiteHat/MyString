#include <gtest/gtest.h>
#include <memory_resource>
#include <string>
#include <memory>
#include <tuple>
#include <type_traits>

#include "test_utils.h"
#include "my_exception.h"

template <typename _Tuple>
class ReplaceTests : public TestingHelper::StringTestingBase<_Tuple> {};
using TestingHelper::MyParamTypes;

TYPED_TEST_SUITE(ReplaceTests, MyParamTypes);

TYPED_TEST(ReplaceTests, STLStringPosCountLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 2;
  ADJUST_OUT(1, __count);
  ADJUST_IN(std::max(__str.length() - __pos - 1, size_type(1)), __count);
  const typename TestFixture::STLString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);

  typename TestFixture::STLString __cmp(__ilist1.begin(), __initLen);
  __cmp.replace(__pos, __count, __other);

  //Act
  __str.replace(__pos, __count, __other);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, STLStringPosCountLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 2;
  ADJUST_OUT(1, __count);
  ADJUST_IN(std::max(__str.length() - __pos - 1, size_type(1)), __count);
  const typename TestFixture::STLString __other(__ilist2);

  typename TestFixture::STLString __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.replace(__pos, __count, __other);

  //Act
  __str.replace(__pos, __count, __other);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, STLStringPosCountDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 2;
  ADJUST_OUT(1, __count);
  ADJUST_IN(std::max(__str.length() - __pos - 1, size_type(1)), __count);
  const typename TestFixture::STLString __other(__ilist2);

  typename TestFixture::STLString __cmp(__ilist1);
  __cmp.replace(__pos, __count, __other);

  //Act
  __str.replace(__pos, __count, __other);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, STLStringPosOutCount) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const size_type __pos = __str.length() + 1;
  size_type __count = 2;
  ADJUST_OUT(1, __count);
  ADJUST_IN(std::max(__str.length() - __pos - 1, size_type(1)), __count);
  const typename TestFixture::STLString __other(__ilist2);

  //Act

  //Assert
  EXPECT_THROW({
    __str.replace(__pos, __count, __other);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(ReplaceTests, MyStringPosCountLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 2;
  ADJUST_OUT(1, __count);
  ADJUST_IN(std::max(__str.length() - __pos - 1, size_type(1)), __count);
  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);

  typename TestFixture::STLString __cmp(__ilist1.begin(), __initLen);
  __cmp.replace(__pos, __count, __other.data());

  //Act
  __str.replace(__pos, __count, __other);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, MyStringPosCountLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 2;
  ADJUST_OUT(1, __count);
  ADJUST_IN(std::max(__str.length() - __pos - 1, size_type(1)), __count);
  const typename TestFixture::MyTestingString __other(__ilist2);

  typename TestFixture::STLString __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.replace(__pos, __count, __other.data());

  //Act
  __str.replace(__pos, __count, __other);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, MyStringPosCountDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 2;
  ADJUST_OUT(1, __count);
  ADJUST_IN(std::max(__str.length() - __pos - 1, size_type(1)), __count);
  const typename TestFixture::MyTestingString __other(__ilist2);

  typename TestFixture::STLString __cmp(__ilist1);
  __cmp.replace(__pos, __count, __other.data());

  //Act
  __str.replace(__pos, __count, __other);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, MyStringPosOutCount) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const size_type __pos = __str.length() + 1;
  size_type __count = 2;
  ADJUST_OUT(1, __count);
  ADJUST_IN(std::max(__str.length() - __pos - 1, size_type(1)), __count);
  const typename TestFixture::MyTestingString __other(__ilist2);

  //Act

  //Assert
  EXPECT_THROW({
    __str.replace(__pos, __count, __other);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(ReplaceTests, STLStringItersRangeLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 2;
  ADJUST_OUT(1, __count);
  ADJUST_IN(std::max(__str.length() - __pos - 1, size_type(1)), __count);
  const typename TestFixture::STLString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);

  typename TestFixture::STLString __cmp(__ilist1.begin(), __initLen);
  __cmp.replace(__cmp.begin() + __pos, __cmp.begin() + __pos + __count,
    __other);

  //Act
  __str.replace(__str.begin() + __pos, __str.begin() + __pos + __count,
    __other);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, STLStringItersRangeLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 2;
  ADJUST_OUT(1, __count);
  ADJUST_IN(std::max(__str.length() - __pos - 1, size_type(1)), __count);
  const typename TestFixture::STLString __other(__ilist2);

  typename TestFixture::STLString __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.replace(__cmp.begin() + __pos, __cmp.begin() + __pos + __count,
    __other);

  //Act
  __str.replace(__str.begin() + __pos, __str.begin() + __pos + __count,
    __other);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, STLStringItersRangeDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 2;
  ADJUST_OUT(1, __count);
  ADJUST_IN(std::max(__str.length() - __pos - 1, size_type(1)), __count);
  const typename TestFixture::STLString __other(__ilist2);

  typename TestFixture::MyTestingString __cmp(__ilist1);
  __cmp.replace(__cmp.begin() + __pos, __cmp.begin() + __pos + __count,
    __other);

  //Act
  __str.replace(__str.begin() + __pos, __str.begin() + __pos + __count,
    __other);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, STLStringItersRangeOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const size_type __pos = __str.length() + 1;
  size_type __count = 2;
  ADJUST_OUT(1, __count);
  ADJUST_IN(std::max(__str.length() - __pos - 1, size_type(1)), __count);
  const typename TestFixture::STLString __other(__ilist2);

  //Act

  //Assert
  EXPECT_THROW({
    __str.replace(__str.begin() + __pos, __str.begin() + __pos + __count,
      __other);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(ReplaceTests, MyStringItersRangeLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 2;
  ADJUST_OUT(1, __count);
  ADJUST_IN(std::max(__str.length() - __pos - 1, size_type(1)), __count);
  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);

  typename TestFixture::STLString __cmp(__ilist1.begin(), __initLen);
  __cmp.replace(__pos, __count, __other.data());

  //Act
  __str.replace(__str.begin() + __pos, __str.begin() + __pos + __count,
    __other);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, MyStringItersRangeLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 2;
  ADJUST_OUT(1, __count);
  ADJUST_IN(std::max(__str.length() - __pos - 1, size_type(1)), __count);
  const typename TestFixture::MyTestingString __other(__ilist2);

  typename TestFixture::STLString __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.replace(__pos, __count, __other.data());

  //Act
  __str.replace(__str.begin() + __pos, __str.begin() + __pos + __count,
    __other);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, MyStringItersRangeDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 2;
  ADJUST_OUT(1, __count);
  ADJUST_IN(std::max(__str.length() - __pos - 1, size_type(1)), __count);
  const typename TestFixture::MyTestingString __other(__ilist2);

  typename TestFixture::MyTestingString __cmp(__ilist1);
  __cmp.replace(__pos, __count, __other);

  //Act
  __str.replace(__str.begin() + __pos, __str.begin() + __pos + __count,
    __other);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, MyStringItersRangeOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const size_type __pos = __str.length() + 1;
  size_type __count = 2;
  ADJUST_OUT(1, __count);
  ADJUST_IN(std::max(__str.length() - __pos - 1, size_type(1)), __count);
  const typename TestFixture::MyTestingString __other(__ilist2);

  //Act

  //Assert
  EXPECT_THROW({
    __str.replace(__str.begin() + __pos, __str.begin() + __pos + __count,
      __other);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(ReplaceTests, STLStringPosCountStrPosStrCountLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);
  const size_type __pos2 = 1;
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);


  typename TestFixture::STLString __cmp(__ilist1.begin(), __initLen);
  __cmp.replace(__pos1, __count1, __other, __pos2, __count2);

  //Act
  __str.replace(__pos1, __count1, __other, __pos2, __count2);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, STLStringPosCountStrPosStrCountLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2);
  const size_type __pos2 = 1;
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);

  typename TestFixture::STLString __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.replace(__pos1, __count1, __other, __pos2, __count2);

  //Act
  __str.replace(__pos1, __count1, __other, __pos2, __count2);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, STLStringPosCountStrPosStrCountDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2);
  const size_type __pos2 = 1;
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);

  typename TestFixture::STLString __cmp(__ilist1);
  __cmp.replace(__pos1, __count1, __other, __pos2, __count2);

  //Act
  __str.replace(__pos1, __count1, __other, __pos2, __count2);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, STLStringPosOutCountStrPosStrCount) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const size_type __pos1 = __str.length() + 1;
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2);
  const size_type __pos2 = 1;
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);

  //Act

  //Assert
  EXPECT_THROW({
    __str.replace(__pos1, __count1, __other, __pos2, __count2);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(ReplaceTests, STLStringPosCountStrPosOutStrCount) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const size_type __pos1 = 1;
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2);
  const size_type __pos2 = __other.length() + 1;
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);

  //Act

  //Assert
  EXPECT_THROW({
    __str.replace(__pos1, __count1, __other, __pos2, __count2);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(ReplaceTests, MyStringPosCountStrPosStrCountLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);
  const typename TestFixture::STLString __otherCmp(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);
  const size_type __pos2 = 1;
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);

  typename TestFixture::STLString __cmp(__ilist1.begin(), __initLen);
  __cmp.replace(__pos1, __count1, __otherCmp, __pos2, __count2);

  //Act
  __str.replace(__pos1, __count1, __other, __pos2, __count2);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, MyStringPosCountStrPosStrCountLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::MyTestingString __other(__ilist2);
  const typename TestFixture::STLString __otherCmp(__ilist2);
  const size_type __pos2 = 1;
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);

  typename TestFixture::STLString __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.replace(__pos1, __count1, __otherCmp, __pos2, __count2);

  //Act
  __str.replace(__pos1, __count1, __other, __pos2, __count2);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, MyStringPosCountStrPosStrCountDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::MyTestingString __other(__ilist2);
  const typename TestFixture::STLString __otherCmp(__ilist2);
  const size_type __pos2 = 1;
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);

  typename TestFixture::STLString __cmp(__ilist1);
  __cmp.replace(__pos1, __count1, __otherCmp, __pos2, __count2);

  //Act
  __str.replace(__pos1, __count1, __other, __pos2, __count2);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, MyStringPosOutCountStrPosStrCount) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const size_type __pos1 = __str.length() + 1;
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos2 = 1;
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);

  //Act

  //Assert
  EXPECT_THROW({
    __str.replace(__pos1, __count1, __other, __pos2, __count2);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(ReplaceTests, MyStringPosCountStrPosOutStrCount) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const size_type __pos1 = 1;
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos2 = __other.length() + 1;
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);

  //Act

  //Assert
  EXPECT_THROW({
    __str.replace(__pos1, __count1, __other, __pos2, __count2);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(ReplaceTests, ItersRangeStrItersRangeLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);
  const size_type __pos2 = 1;
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);


  typename TestFixture::STLString __cmp(__ilist1.begin(), __initLen);
  __cmp.replace(__cmp.begin() + __pos1, __cmp.begin() + __pos1 + __count1,
    __other.begin() + __pos2, __other.begin() + __pos2 + __count2);

  //Act
  __str.replace(__str.begin() + __pos1, __str.begin() + __pos1 + __count1,
    __other.begin() + __pos2, __other.begin() + __pos2 + __count2);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, ItersRangeStrItersRangeLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2);
  const size_type __pos2 = 1;
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);

  typename TestFixture::STLString __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.replace(__cmp.begin() + __pos1, __cmp.begin() + __pos1 + __count1,
    __other.begin() + __pos2, __other.begin() + __pos2 + __count2);

  //Act
  __str.replace(__str.begin() + __pos1, __str.begin() + __pos1 + __count1,
    __other.begin() + __pos2, __other.begin() + __pos2 + __count2);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, ItersRangeStrItersRangeDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2);
  const size_type __pos2 = 1;
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);

  typename TestFixture::STLString __cmp(__ilist1);
  __cmp.replace(__cmp.begin() + __pos1, __cmp.begin() + __pos1 + __count1,
    __other.begin() + __pos2, __other.begin() + __pos2 + __count2);

  //Act
  __str.replace(__str.begin() + __pos1, __str.begin() + __pos1 + __count1,
    __other.begin() + __pos2, __other.begin() + __pos2 + __count2);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, CStrPosCountStrCountLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);


  typename TestFixture::STLString __cmp(__ilist1.begin(), __initLen);
  __cmp.replace(__pos1, __count1, __other.data(), __count2);

  //Act
  __str.replace(__pos1, __count1, __other.data(), __count2);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, CStrPosCountStrCountLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2);
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);

  typename TestFixture::STLString __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.replace(__pos1, __count1, __other.data(), __count2);

  //Act
  __str.replace(__pos1, __count1, __other.data(), __count2);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, CStrPosCountStrCountDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2);
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);

  typename TestFixture::STLString __cmp(__ilist1);
  __cmp.replace(__pos1, __count1, __other.data(), __count2);

  //Act
  __str.replace(__pos1, __count1, __other.data(), __count2);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, CStrPosOutCountStrCount) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const size_type __pos1 = __str.length() + 1;
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2);
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);

  //Act

  //Assert
  EXPECT_THROW({
    __str.replace(__pos1, __count1, __other.data(), __count2);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(ReplaceTests, CStrItersRangeCountLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);


  typename TestFixture::STLString __cmp(__ilist1.begin(), __initLen);
  __cmp.replace(__cmp.begin() + __pos1, __cmp.begin() + __pos1 + __count1,
    __other.data(), __count2);

  //Act
  __str.replace(__str.begin() + __pos1, __str.begin() + __pos1 + __count1,
    __other.data(), __count2);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, CStrItersRangeCountLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2);
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);

  typename TestFixture::STLString __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.replace(__cmp.begin() + __pos1, __cmp.begin() + __pos1 + __count1,
    __other.data(), __count2);

  //Act
  __str.replace(__str.begin() + __pos1, __str.begin() + __pos1 + __count1,
    __other.data(), __count2);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, CStrItersRangeCountDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2);
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);

  typename TestFixture::STLString __cmp(__ilist1);
  __cmp.replace(__cmp.begin() + __pos1, __cmp.begin() + __pos1 + __count1,
    __other.data(), __count2);

  //Act
  __str.replace(__str.begin() + __pos1, __str.begin() + __pos1 + __count1,
    __other.data(), __count2);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, CStrItersRangeOutCount) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const size_type __pos1 = __str.length() + 1;
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2);
  size_type __count2 = __other.length();
  ADJUST_OUT(1, __count2);

  //Act

  //Assert
  EXPECT_THROW({
    __str.replace(__str.begin() + __pos1, __str.begin() + __pos1 + __count1,
      __other.data(), __count2);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(ReplaceTests, CStrPosCountLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);


  typename TestFixture::STLString __cmp(__ilist1.begin(), __initLen);
  __cmp.replace(__pos1, __count1, __other.data());

  //Act
  __str.replace(__pos1, __count1, __other.data());

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, CStrPosCountLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2);

  typename TestFixture::STLString __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.replace(__pos1, __count1, __other.data());

  //Act
  __str.replace(__pos1, __count1, __other.data());

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, CStrPosCountDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2);

  typename TestFixture::STLString __cmp(__ilist1);
  __cmp.replace(__pos1, __count1, __other.data());

  //Act
  __str.replace(__pos1, __count1, __other.data());

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, CStrPosOutCount) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const size_type __pos1 = __str.length() + 1;
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2);

  //Act

  //Assert
  EXPECT_THROW({
    __str.replace(__pos1, __count1, __other.data());
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(ReplaceTests, CStrItersRangeLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);


  typename TestFixture::STLString __cmp(__ilist1.begin(), __initLen);
  __cmp.replace(__cmp.begin() + __pos1, __cmp.begin() + __pos1 + __count1,
    __other.data());

  //Act
  __str.replace(__str.begin() + __pos1, __str.begin() + __pos1 + __count1,
    __other.data());

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, CStrItersRangeLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2);

  typename TestFixture::STLString __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.replace(__cmp.begin() + __pos1, __cmp.begin() + __pos1 + __count1,
    __other.data());

  //Act
  __str.replace(__str.begin() + __pos1, __str.begin() + __pos1 + __count1,
    __other.data());

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, CStrItersRangeDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2);

  typename TestFixture::STLString __cmp(__ilist1);
  __cmp.replace(__cmp.begin() + __pos1, __cmp.begin() + __pos1 + __count1,
    __other.data());

  //Act
  __str.replace(__str.begin() + __pos1, __str.begin() + __pos1 + __count1,
    __other.data());

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, CStrItersRangeOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const size_type __pos1 = __str.length() + 1;
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const typename TestFixture::STLString __other(__ilist2);

  //Act

  //Assert
  EXPECT_THROW({
    __str.replace(__str.begin() + __pos1, __str.begin() + __pos1 + __count1,
      __other.data());
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(ReplaceTests, CharPosCountCharsCountLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist.begin(), __initLen);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const value_type __ch = *(__ilist.begin());
  size_type __count2 = 1;
  ADJUST_OUT(1, __count2);
  ADJUST_IN(TestFixture::_localBufferLenThreshold - __initLen, __count2);

  typename TestFixture::STLString __cmp(__ilist.begin(), __initLen);
  __cmp.replace(__pos1, __count1, __count2, __ch);

  //Act
  __str.replace(__pos1, __count1, __count2, __ch);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, CharPosCountCharsCountLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const value_type __ch = *(__ilist.begin());
  size_type __count2 = __count1 + 1;
  ADJUST_OUT(__count1 + 1, __count2);


  typename TestFixture::STLString __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.replace(__pos1, __count1, __count2, __ch);

  //Act
  __str.replace(__pos1, __count1, __count2, __ch);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, CharPosCountCharsCountDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const value_type __ch = *(__ilist.begin());
  size_type __count2 = 1;
  ADJUST_OUT(1, __count2);

  typename TestFixture::STLString __cmp(__ilist);
  __cmp.replace(__pos1, __count1, __count2, __ch);

  //Act
  __str.replace(__pos1, __count1, __count2, __ch);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, CharPosOutCountCharsCount) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const size_type __pos1 = __str.length() + 1;
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const value_type __ch = *(__ilist.begin());
  size_type __count2 = 1;
  ADJUST_OUT(1, __count2);

  //Act

  //Assert
  EXPECT_THROW({
    __str.replace(__pos1, __count1, __count2, __ch);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __ilist.size());
}

TYPED_TEST(ReplaceTests, CharItersRangeCharsCountLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist.begin(), __initLen);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const value_type __ch = *(__ilist.begin());
  size_type __count2 = 1;
  ADJUST_OUT(1, __count2);
  ADJUST_IN(TestFixture::_localBufferLenThreshold - __initLen, __count2);

  typename TestFixture::STLString __cmp(__ilist.begin(), __initLen);
  __cmp.replace(__cmp.begin() + __pos1, __cmp.begin() + __pos1 + __count1,
    __count2, __ch);

  //Act
  __str.replace(__str.begin() + __pos1, __str.begin() + __pos1 + __count1,
    __count2, __ch);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, CharItersRangeCharsCountLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const value_type __ch = *(__ilist.begin());
  size_type __count2 = __count1 + 1;
  ADJUST_OUT(__count1 + 1, __count2);


  typename TestFixture::STLString __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.replace(__cmp.begin() + __pos1, __cmp.begin() + __pos1 + __count1,
    __count2, __ch);

  //Act
  __str.replace(__str.begin() + __pos1, __str.begin() + __pos1 + __count1,
    __count2, __ch);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, CharItersRangeCharsCountDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const value_type __ch = *(__ilist.begin());
  size_type __count2 = 1;
  ADJUST_OUT(1, __count2);

  typename TestFixture::STLString __cmp(__ilist);
  __cmp.replace(__cmp.begin() + __pos1, __cmp.begin() + __pos1 + __count1,
    __count2, __ch);

  //Act
  __str.replace(__str.begin() + __pos1, __str.begin() + __pos1 + __count1,
    __count2, __ch);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, CharItersRangeOutCharsCount) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const size_type __pos1 = __str.length() + 1;
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);
  const value_type __ch = *(__ilist.begin());
  size_type __count2 = 1;
  ADJUST_OUT(1, __count2);

  //Act

  //Assert
  EXPECT_THROW({
    __str.replace(__str.begin() + __pos1, __str.begin() + __pos1 + __count1,
      __count2, __ch);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __ilist.size());
}

TYPED_TEST(ReplaceTests, ListItersRangeLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const std::initializer_list<value_type> __ilist2 = {'G', 'o'};

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);

  typename TestFixture::STLString __cmp(__ilist1.begin(), __initLen);
  __cmp.replace(__cmp.begin() + __pos1, __cmp.begin() + __pos1 + __count1,
    __ilist2);

  //Act
  __str.replace(__str.begin() + __pos1, __str.begin() + __pos1 + __count1,
    __ilist2);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, ListItersRangeLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);

  typename TestFixture::STLString __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.replace(__cmp.begin() + __pos1, __cmp.begin() + __pos1 + __count1,
    __ilist2);

  //Act
  __str.replace(__str.begin() + __pos1, __str.begin() + __pos1 + __count1,
    __ilist2);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ReplaceTests, ListItersRangeDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  size_type __count1 = 2;
  ADJUST_OUT(1, __count1);
  ADJUST_IN(std::max(__str.length() - __pos1 - 1, size_type(1)), __count1);

  typename TestFixture::STLString __cmp(__ilist1);
  __cmp.replace(__cmp.begin() + __pos1, __cmp.begin() + __pos1 + __count1,
    __ilist2);

  //Act
  __str.replace(__str.begin() + __pos1, __str.begin() + __pos1 + __count1,
    __ilist2);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}
