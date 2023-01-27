#include <gtest/gtest.h>
#include <memory_resource>
#include <string>
#include <memory>
#include <tuple>
#include <type_traits>

#include "test_utils.h"
#include "my_exception.h"

template <typename _Tuple>
class EraseTests : public TestingHelper::StringTestingBase<_Tuple> {};
using TestingHelper::MyParamTypes;

TYPED_TEST_SUITE(EraseTests, MyParamTypes);

TYPED_TEST(EraseTests, PosCountNone) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  const size_type __pos = 0;
  const size_type __count = 0;

  typename TestFixture::STLString __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.erase(__pos, __count);

  //Act
  __str.erase(__pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, PosCountLocalBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  const size_type __pos = 0;
  size_type __count = 1;
  ADJUST_OUT(1, __count);

  typename TestFixture::STLString __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.erase(__pos, __count);

  //Act
  __str.erase(__pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, PosCountLocalMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 2, __pos);
  size_type __count = 1;
  ADJUST_OUT(1, __count);

  typename TestFixture::STLString __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.erase(__pos, __count);

  //Act
  __str.erase(__pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, PosCountLocalEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  const size_type __pos = __str.length() - 1;
  size_type __count = 1;
  ADJUST_OUT(1, __count);

  typename TestFixture::STLString __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.erase(__pos, __count);

  //Act
  __str.erase(__pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, PosCountDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin());

  auto __prevCap = __str.capacity();

  const size_type __pos = 0;
  size_type __count = __str.length() / 2;
  ADJUST_OUT(1, __count);

  typename TestFixture::STLString __cmp(__ilist);
  __cmp.erase(__pos, __count);

  //Act
  __str.erase(__pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, PosCountDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevCap = __str.capacity();

  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 2, __pos);
  size_type __count = __str.length() / 2;
  ADJUST_OUT(1, __count);

  typename TestFixture::STLString __cmp(__ilist);
  __cmp.erase(__pos, __count);

  //Act
  __str.erase(__pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, PosCountDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevCap = __str.capacity();

  const size_type __pos = __str.length() - 1;
  size_type __count = __str.length() / 2;
  ADJUST_OUT(1, __count);

  typename TestFixture::STLString __cmp(__ilist);
  __cmp.erase(__pos, __count);

  //Act
  __str.erase(__pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, PosCount) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const size_type __pos = __str.length() + 1;
  size_type __count = __str.length() / 2;
  ADJUST_OUT(1, __count);

  //Act

  //Assert
  EXPECT_THROW({
    __str.erase(__pos, __count);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __ilist.size());
}

TYPED_TEST(EraseTests, IterLocalBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  typename TestFixture::STLString __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.erase(__cmp.begin());
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin());
  auto __diffStr = std::distance(__retIterStr, __str.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, IterLocalMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  size_type __shift = __str.length() / 2;
  ADJUST_OUT(1, __shift);
  ADJUST_IN(__str.length() - 2, __shift);

  typename TestFixture::STLString __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.erase(__cmp.begin() + __shift);
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin() + __shift);
  auto __diffStr = std::distance(__retIterCmp, __cmp.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, IterLocalEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  const size_type __shift = __str.length() - 1;

  typename TestFixture::STLString __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.erase(__cmp.begin() + __shift);
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin() + __shift);
  auto __diffStr = std::distance(__retIterCmp, __cmp.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, IterDynamicToLocalBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold + 1);

  auto __prevCap = __str.capacity();

  typename TestFixture::STLString __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold + 1);
  auto __retIterCmp = __cmp.erase(__cmp.begin());
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin());
  auto __diffStr = std::distance(__retIterCmp, __cmp.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, IterDynamicToLocalMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold + 1);

  auto __prevCap = __str.capacity();

  size_type __shift = __str.length() / 2;
  ADJUST_OUT(1, __shift);
  ADJUST_IN(__str.length() - 2, __shift);

  typename TestFixture::STLString __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold + 1);
  auto __retIterCmp = __cmp.erase(__cmp.begin() + __shift);
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin() + __shift);
  auto __diffStr = std::distance(__retIterStr, __str.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, IterDynamicToLocalEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold + 1);

  auto __prevCap = __str.capacity();

  const size_type __shift = __str.length() - 1;

  typename TestFixture::STLString __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold + 1);
  auto __retIterCmp = __cmp.erase(__cmp.begin() + __shift);
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin() + __shift);
  auto __diffStr = std::distance(__retIterStr, __str.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, IterDynamicToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevCap = __str.capacity();

  typename TestFixture::STLString __cmp(__ilist);
  auto __retIterCmp = __cmp.erase(__cmp.begin());
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin());
  auto __diffStr = std::distance(__retIterStr, __str.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, IterDynamicToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevCap = __str.capacity();

  size_type __shift = __str.length() / 2;
  ADJUST_OUT(1, __shift);
  ADJUST_IN(__str.length() - 2, __shift);

  typename TestFixture::STLString __cmp(__ilist);
  auto __retIterCmp = __cmp.erase(__cmp.begin() + __shift);
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin() + __shift);
  auto __diffStr = std::distance(__retIterStr, __str.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, IterDynamicToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevCap = __str.capacity();

  const size_type __shift = __str.length() - 1;

  typename TestFixture::STLString __cmp(__ilist);
  auto __retIterCmp = __cmp.erase(__cmp.begin() + __shift);
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin() + __shift);
  auto __diffStr = std::distance(__retIterStr, __str.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, IterRangeNone) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  const size_type __count = 0;

  typename TestFixture::STLString __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.erase(__cmp.begin(), __cmp.begin() + __count);
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin(), __str.begin() + __count);
  auto __diffStr = std::distance(__retIterStr, __str.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, IterRangeLocalBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  const size_type __shift = 0;
  size_type __count = 1;
  ADJUST_OUT(1, __count);
  ADJUST_IN(__str.length() - __shift, __count);

  typename TestFixture::STLString __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.erase(__cmp.begin() + __shift, __cmp.begin() +
    __shift + __count);
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin() + __shift, __str.begin() +
    __shift + __count);
  auto __diffStr = std::distance(__retIterStr, __str.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, IterRangeLocalMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  size_type __shift = __str.length() / 2;
  ADJUST_OUT(1, __shift);
  ADJUST_IN(__str.length() - 2, __shift);
  size_type __count = 1;
  ADJUST_OUT(1, __count);
  ADJUST_IN(__str.length() - __shift, __count);

  typename TestFixture::STLString __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.erase(__cmp.begin() + __shift, __cmp.begin() +
    __shift + __count);
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin() + __shift, __str.begin() +
    __shift + __count);
  auto __diffStr = std::distance(__retIterStr, __str.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, IterRangeLocalEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  const size_type __shift = __str.length() - 1;
  size_type __count = 1;
  ADJUST_OUT(1, __count);
  ADJUST_IN(__str.length() - __shift, __count);

  typename TestFixture::STLString __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.erase(__cmp.begin() + __shift, __cmp.begin() +
    __shift + __count);
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin() + __shift, __str.begin() +
    __shift + __count);
  auto __diffStr = std::distance(__retIterStr, __str.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, IterRangeDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin());

  auto __prevCap = __str.capacity();

  const size_type __shift = 0;
  size_type __count = __str.length() / 2;
  ADJUST_OUT(1, __count);
  ADJUST_IN(__str.length() - __shift, __count);

  typename TestFixture::STLString __cmp(__ilist);
  auto __retIterCmp = __cmp.erase(__cmp.begin() + __shift, __cmp.begin() +
    __shift + __count);
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin() + __shift, __str.begin() +
    __shift + __count);
  auto __diffStr = std::distance(__retIterStr, __str.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, IterRangeDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevCap = __str.capacity();

  size_type __shift = __str.length() / 2;
  ADJUST_OUT(1, __shift);
  ADJUST_IN(__str.length() - 2, __shift);
  size_type __count = __str.length() / 2;
  ADJUST_OUT(1, __count);
  ADJUST_IN(__str.length() - __shift, __count);

  typename TestFixture::STLString __cmp(__ilist);
  auto __retIterCmp = __cmp.erase(__cmp.begin() + __shift, __cmp.begin() +
    __shift + __count);
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin() + __shift, __str.begin() +
    __shift + __count);
  auto __diffStr = std::distance(__retIterStr, __str.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(EraseTests, IterRangeDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevCap = __str.capacity();

  const size_type __shift = __str.length() - 1;
  size_type __count = __str.length() / 2;
  ADJUST_OUT(1, __count);
  ADJUST_IN(__str.length() - __shift, __count);

  typename TestFixture::STLString __cmp(__ilist);
  auto __retIterCmp = __cmp.erase(__cmp.begin() + __shift, __cmp.begin() +
    __shift + __count);
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin() + __shift, __str.begin() +
    __shift + __count);
  auto __diffStr = std::distance(__retIterStr, __str.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}
