#include <gtest/gtest.h>
#include <memory_resource>
#include <string>
#include <memory>
#include <tuple>
#include <type_traits>

#include "test_utils.h"
#include "my_exception.h"

template <typename _Tuple>
class OperationsTests : public TestingHelper::StringTestingBase<_Tuple> {};

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
  std::tuple<char, std::char_traits<char>,
    std::pmr::polymorphic_allocator<char>>
>;

TYPED_TEST_SUITE(OperationsTests, MyParamTypes);

TYPED_TEST(OperationsTests, ReserveInLocal) {
  //Arrange
  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  __str.reserve(__str.capacity() - 1);

  //Assert
  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __str.length());
}

TYPED_TEST(OperationsTests, ReserveLocalToDynamic) {
  //Arrange
  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  __str.reserve(__str.capacity() + 1);

  //Assert
  EXPECT_NE(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_LE(__str.capacity(), __prevCap * 2);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __str.length());
}

TYPED_TEST(OperationsTests, ReserveDynamicToDynamic) {
  //Arrange
  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  __str.reserve(__str.capacity() + 1);

  //Assert
  EXPECT_NE(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_LE(__str.capacity(), __prevCap * 2);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __ilist.size());
}

#if __cplusplus <= 201703L
TYPED_TEST(OperationsTests, ReserveAsShrinkToFit) {
  //Arrange
  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  __str.reserve();

  //Assert
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_LE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __ilist.size());
}
#endif

TYPED_TEST(OperationsTests, ShrinkToFitLocal) {
  //Arrange
  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold - 1);

  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  // Going to use allocated storage
  __str.reserve(TestFixture::_localBufferCapThreshold + 1);
  // Moving back to local storage
  __str.shrink_to_fit();

  //Assert
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __str.length());
}

TYPED_TEST(OperationsTests, ShrinkToFitDynamic) {
  //Arrange
  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  __str.shrink_to_fit();

  //Assert
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_LE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __ilist.size());
}

TYPED_TEST(OperationsTests, ClearLocal) {
  //Arrange
  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevData = __str.data();
  auto __prevCap = __str.capacity();

  //Act
  __str.clear();

  //Assert
  EXPECT_TRUE(__str.empty());
  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.capacity(), __prevCap);
}

TYPED_TEST(OperationsTests, ClearDynamic) {
  //Arrange
  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevData = __str.data();
  auto __prevCap = __str.capacity();

  //Act
  __str.clear();

  //Assert
  EXPECT_TRUE(__str.empty());
  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.capacity(), __prevCap);
}

TYPED_TEST(OperationsTests, InsertCharPosLocalBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const value_type __ch = *(__ilist.begin());
  const size_type __pos = 0;

  typename TestFixture::MyTestingString __str(__ilist.begin(), __initLen);

  std::basic_string<value_type> __cmp(__ilist.begin(), __initLen);
  __cmp.insert(__pos, 1, __ch);

  //Act
  __str.insert(__pos, __ch);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharPosLocalMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist.begin(), __initLen);

  const value_type __ch = *(__ilist.begin());
  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);

  std::basic_string<value_type> __cmp(__ilist.begin(), __initLen);
  __cmp.insert(__pos, 1, __ch);

  //Act
  __str.insert(__pos, __ch);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharPosLocalEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist.begin(), __initLen);

  const value_type __ch = *(__ilist.begin());
  const size_type __pos = __str.length();

  std::basic_string<value_type> __cmp(__ilist.begin(), __initLen);
  __cmp.insert(__pos, 1, __ch);

  //Act
  __str.insert(__pos, __ch);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharPosLocalToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const value_type __ch = *(__ilist.begin());
  const size_type __pos = 0;

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.insert(__pos, 1, __ch);

  //Act
  __str.insert(__pos, __ch);

  //Assert
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharPosLocalToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const value_type __ch = *(__ilist.begin());
  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.insert(__pos, 1, __ch);

  //Act
  __str.insert(__pos, __ch);

  //Assert
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharPosLocalToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const value_type __ch = *(__ilist.begin());
  size_type __pos = __str.length();

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.insert(__pos, 1, __ch);

  //Act
  __str.insert(__pos, __ch);

  //Assert
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharPosDynamicToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());
  const size_type __pos = 0;

  std::basic_string<value_type> __cmp(__ilist);
  __cmp.insert(__pos, 1, __ch);

  //Act
  __str.insert(__pos, __ch);

  //Assert
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharPosDynamicToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());
  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);

  std::basic_string<value_type> __cmp(__ilist.begin());
  __cmp.insert(__pos, 1, __ch);

  //Act
  __str.insert(__pos, __ch);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharPosDynamicToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());
  size_type __pos = __str.length();

  std::basic_string<value_type> __cmp(__ilist);
  __cmp.insert(__pos, 1, __ch);

  //Act
  __str.insert(__pos, __ch);

  //Assert
  EXPECT_EQ(__str.length(), __cmp.length());
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharPosOut) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const value_type __ch = *(__ilist.begin());
  size_type __pos = __str.length() + 1;

  //Act

  //Assert
  EXPECT_THROW({
    __str.insert(__pos, __ch);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __ilist.size());
}

TYPED_TEST(OperationsTests, InsertCharPosCountLocalBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const value_type __ch = *(__ilist.begin());
  const size_type __pos = 0;
  const size_type __count = TestFixture::_localBufferLenThreshold - __initLen;

  typename TestFixture::MyTestingString __str(__ilist.begin(), __initLen);

  std::basic_string<value_type> __cmp(__ilist.begin(), __initLen);
  __cmp.insert(__pos, __count, __ch);

  //Act
  __str.insert(__pos, __count, __ch);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharPosCountLocalMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist.begin(), __initLen);

  const value_type __ch = *(__ilist.begin());
  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  const size_type __count = TestFixture::_localBufferLenThreshold - __initLen;

  std::basic_string<value_type> __cmp(__ilist.begin(), __initLen);
  __cmp.insert(__pos, __count, __ch);

  //Act
  __str.insert(__pos, __count, __ch);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharPosCountLocalEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist.begin(), __initLen);

  const value_type __ch = *(__ilist.begin());
  const size_type __pos = __str.length();
  const size_type __count = TestFixture::_localBufferLenThreshold - __initLen;

  std::basic_string<value_type> __cmp(__ilist.begin(), __initLen);
  __cmp.insert(__pos, __count, __ch);

  //Act
  __str.insert(__pos, __count, __ch);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharPosCountLocalToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const value_type __ch = *(__ilist.begin());
  const size_type __pos = 0;
  size_type __count = 1;
  ADJUST_OUT(TestFixture::_localBufferLenThreshold - __str.length() + 1,
    __count);

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.insert(__pos, __count, __ch);

  //Act
  __str.insert(__pos, __count, __ch);

  //Assert
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharPosCountLocalToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const value_type __ch = *(__ilist.begin());
  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 1;
  ADJUST_OUT(TestFixture::_localBufferLenThreshold - __str.length() + 1,
    __count);

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.insert(__pos, __count, __ch);

  //Act
  __str.insert(__pos, __count, __ch);

  //Assert
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharPosCountLocalToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const value_type __ch = *(__ilist.begin());
  size_type __pos = __str.length();
  size_type __count = 1;
  ADJUST_OUT(TestFixture::_localBufferLenThreshold - __str.length() + 1,
    __count);

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.insert(__pos, __count, __ch);

  //Act
  __str.insert(__pos, __count, __ch);

  //Assert
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharPosCountDynamicToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());
  const size_type __pos = 0;
  size_type __count = 1;
  ADJUST_OUT(1, __count);


  std::basic_string<value_type> __cmp(__ilist);
  __cmp.insert(__pos, __count, __ch);

  //Act
  __str.insert(__pos, __count, __ch);

  //Assert
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharPosCountDynamicToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());
  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 1;
  ADJUST_OUT(1, __count);

  std::basic_string<value_type> __cmp(__ilist.begin());
  __cmp.insert(__pos, __count, __ch);

  //Act
  __str.insert(__pos, __count, __ch);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharPosCountDynamicToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());
  size_type __pos = __str.length();
  size_type __count = 1;
  ADJUST_OUT(1, __count);

  std::basic_string<value_type> __cmp(__ilist);
  __cmp.insert(__pos, __count, __ch);

  //Act
  __str.insert(__pos, __count, __ch);

  //Assert
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharPosOutCount) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const value_type __ch = *(__ilist.begin());
  size_type __pos = __str.length() + 1;
  size_type __count = 1;
  ADJUST_OUT(1, __count);

  //Act

  //Assert
  EXPECT_THROW({
    __str.insert(__pos, __count, __ch);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __ilist.size());
}

TYPED_TEST(OperationsTests, InsertCStrPosLocalBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);
  const size_type __pos = 0;

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos, __other.data());

  //Act
  __str.insert(__pos, __other.data());

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCStrPosLocalMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);
  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos, __other.data());

  //Act
  __str.insert(__pos, __other.data());

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCStrPosLocalEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);
  const size_type __pos = __str.length();

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos, __other.data());

  //Act
  __str.insert(__pos, __other.data());

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCStrPosLocalToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos = 0;

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos, __other.data());

  //Act
  __str.insert(__pos, __other.data());

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCStrPosLocalToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const typename TestFixture::MyTestingString __other(__ilist2);
  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos, __other.data());

  //Act
  __str.insert(__pos, __other.data());

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCStrPosLocalToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos = __str.length();

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos, __other.data());

  //Act
  __str.insert(__pos, __other.data());

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCStrPosDynamicToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos = 0;

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.insert(__pos, __other.data());

  //Act
  __str.insert(__pos, __other.data());

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCStrPosDynamicToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);
  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.insert(__pos, __other.data());

  //Act
  __str.insert(__pos, __other.data());

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCStrPosDynamicToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos = __str.length();

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.insert(__pos, __other.data());

  //Act
  __str.insert(__pos, __other.data());

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCStrPosOut) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  size_type __pos = __str.length() + 1;

  //Act

  //Assert
  EXPECT_THROW({
    __str.insert(__pos, __other.data());
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(OperationsTests, InsertCStrPosCountLocalBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos = 0;
  const size_type __count = TestFixture::_localBufferLenThreshold - __initLen;

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos, __other.data(), __count);

  //Act
  __str.insert(__pos, __other.data(), __count);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCStrPosCountLocalMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const typename TestFixture::MyTestingString __other(__ilist2);
  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  const size_type __count = TestFixture::_localBufferLenThreshold - __initLen;

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos, __other.data(), __count);

  //Act
  __str.insert(__pos, __other.data(), __count);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCStrPosCountLocalEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos = __str.length();
  const size_type __count = TestFixture::_localBufferLenThreshold - __initLen;

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos, __other.data(), __count);

  //Act
  __str.insert(__pos, __other.data(), __count);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCStrPosCountLocalToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos = 0;
  size_type __count = __other.length();
  ADJUST_OUT(TestFixture::_localBufferLenThreshold - __str.length() + 1,
    __count);
  ADJUST_IN(__other.length(), __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos, __other.data(), __count);

  //Act
  __str.insert(__pos, __other.data(), __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCStrPosCountLocalToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const typename TestFixture::MyTestingString __other(__ilist2);
  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = __other.length();
  ADJUST_OUT(TestFixture::_localBufferLenThreshold - __str.length() + 1,
    __count);
  ADJUST_IN(__other.length(), __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos, __other.data(), __count);

  //Act
  __str.insert(__pos, __other.data(), __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCStrPosCountLocalToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos = __str.length();
  size_type __count = __other.length();
  ADJUST_OUT(TestFixture::_localBufferLenThreshold - __str.length() + 1,
    __count);
  ADJUST_IN(__other.length(), __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos, __other.data(), __count);

  //Act
  __str.insert(__pos, __other.data(), __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCStrPosCountDynamicToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos = 0;
  size_type __count = __other.length();
  ADJUST_OUT(1 , __count);
  ADJUST_IN(__other.length(), __count);

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.insert(__pos, __other.data(), __count);

  //Act
  __str.insert(__pos, __other.data(), __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCStrPosCountDynamicToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);
  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = __other.length();
  ADJUST_OUT(1 , __count);
  ADJUST_IN(__other.length(), __count);

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.insert(__pos, __other.data(), __count);

  //Act
  __str.insert(__pos, __other.data(), __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCStrPosCountDynamicToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos = __str.length();
  size_type __count = __other.length();
  ADJUST_OUT(1 , __count);
  ADJUST_IN(__other.length(), __count);

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.insert(__pos, __other.data(), __count);

  //Act
  __str.insert(__pos, __other.data(), __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCStrPosCountOut) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  size_type __pos = __str.length() + 1;
  size_type __count = __other.length();
  ADJUST_OUT(1 , __count);
  ADJUST_IN(__other.length(), __count);

  //Act

  //Assert
  EXPECT_THROW({
    __str.insert(__pos, __other.data(), __count);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosLocalBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const std::basic_string<value_type> __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);
  const size_type __pos = 0;

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos, __other);

  //Act
  __str.insert(__pos, __other);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosLocalMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const std::basic_string<value_type> __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);
  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos, __other);

  //Act
  __str.insert(__pos, __other);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosLocalEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const std::basic_string<value_type> __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);
  const size_type __pos = __str.length();

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos, __other);

  //Act
  __str.insert(__pos, __other);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosLocalToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  const std::basic_string<value_type> __other(__ilist2);
  const size_type __pos = 0;

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.insert(__pos, __other);

  //Act
  __str.insert(__pos, __other);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosLocalToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  const std::basic_string<value_type> __other(__ilist2);
  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.insert(__pos, __other);

  //Act
  __str.insert(__pos, __other);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosLocalToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  const std::basic_string<value_type> __other(__ilist2);
  const size_type __pos = __str.length();

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.insert(__pos, __other);

  //Act
  __str.insert(__pos, __other);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosDynamicToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);
  const size_type __pos = 0;

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.insert(__pos, __other);

  //Act
  __str.insert(__pos, __other);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosDynamicToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);
  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.insert(__pos, __other);

  //Act
  __str.insert(__pos, __other);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosDynamicToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);
  const size_type __pos = __str.length();

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.insert(__pos, __other);

  //Act
  __str.insert(__pos, __other);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosOut) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  size_type __pos = __str.length() + 1;

  //Act

  //Assert
  EXPECT_THROW({
    __str.insert(__pos, __other);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(OperationsTests, InsertMyStringPosLocalBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);
  const size_type __pos = 0;

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos, __other.data());

  //Act
  __str.insert(__pos, __other);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertMyStringPosLocalMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);
  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos, __other.data());

  //Act
  __str.insert(__pos, __other);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertMyStringPosLocalEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);
  const size_type __pos = __str.length();

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos, __other.data());

  //Act
  __str.insert(__pos, __other);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertMyStringPosLocalToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos = 0;

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.insert(__pos, __other.data());

  //Act
  __str.insert(__pos, __other);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertMyStringPosLocalToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  const typename TestFixture::MyTestingString __other(__ilist2);
  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.insert(__pos, __other.data());

  //Act
  __str.insert(__pos, __other);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertMyStringPosLocalToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos = __str.length();

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.insert(__pos, __other.data());

  //Act
  __str.insert(__pos, __other);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertMyStringPosDynamicToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos = 0;

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.insert(__pos, __other.data());

  //Act
  __str.insert(__pos, __other);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertMyStringPosDynamicToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);
  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.insert(__pos, __other.data());

  //Act
  __str.insert(__pos, __other);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertMyStringPosDynamicToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos = __str.length();

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.insert(__pos, __other.data());

  //Act
  __str.insert(__pos, __other);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertMyStringPosOut) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  size_type __pos = __str.length() + 1;

  //Act

  //Assert
  EXPECT_THROW({
    __str.insert(__pos, __other);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosStrPosCountLocalBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const std::basic_string<value_type> __other(__ilist2);
  const size_type __pos1 = 0;
  size_type __pos2 = 1;
  size_type __count = TestFixture::_localBufferLenThreshold - __initLen;
  ADJUST_OUT(1, __count);
  ADJUST_IN(TestFixture::_localBufferLenThreshold - __initLen, __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos1, __other, __pos2, __count);

  //Act
  __str.insert(__pos1, __other, __pos2, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosStrPosCountLocalMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const std::basic_string<value_type> __other(__ilist2);
  size_type __pos1 = __str.length() / 2;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(TestFixture::_localBufferLenThreshold - __initLen, __pos1);
  const size_type __pos2 = 1;
  size_type __count = TestFixture::_localBufferLenThreshold - __initLen;
  ADJUST_OUT(1, __count);
  ADJUST_IN(TestFixture::_localBufferLenThreshold - __initLen, __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos1, __other, __pos2, __count);

  //Act
  __str.insert(__pos1, __other, __pos2, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosStrPosCountLocalEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const std::basic_string<value_type> __other(__ilist2);
  const size_type __pos1 = __str.length();
  const size_type __pos2 = 1;
  size_type __count = TestFixture::_localBufferLenThreshold - __initLen;
  ADJUST_OUT(1, __count);
  ADJUST_IN(TestFixture::_localBufferLenThreshold - __initLen, __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.insert(__pos1, __other, __pos2, __count);

  //Act
  __str.insert(__pos1, __other, __pos2, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosStrPosCountLocalToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  const std::basic_string<value_type> __other(__ilist2);
  const size_type __pos1 = 0;
  const size_type __pos2 = 1;
  size_type __count = __other.length();
  ADJUST_OUT(1, __count);
  ADJUST_IN(__other.length(), __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.insert(__pos1, __other, __pos2, __count);

  //Act
  __str.insert(__pos1, __other, __pos2, __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosStrPosCountLocalToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  const std::basic_string<value_type> __other(__ilist2);
  size_type __pos1 = __str.length() / 2;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  const size_type __pos2 = 1;
  size_type __count = __other.length();
  ADJUST_OUT(1, __count);
  ADJUST_IN(__other.length(), __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.insert(__pos1, __other, __pos2, __count);

  //Act
  __str.insert(__pos1, __other, __pos2, __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosStrPosCountLocalToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  const std::basic_string<value_type> __other(__ilist2);
  const size_type __pos1 = __str.length();
  const size_type __pos2 = 1;
  size_type __count = __other.length();
  ADJUST_OUT(1, __count);
  ADJUST_IN(__other.length(), __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.insert(__pos1, __other, __pos2, __count);

  //Act
  __str.insert(__pos1, __other, __pos2, __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosStrPosCountDynamicToDynamicBegin)
{
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);
  const size_type __pos1 = 0;
  const size_type __pos2 = 1;
  size_type __count = __other.length();
  ADJUST_OUT(1, __count);
  ADJUST_IN(__other.length(), __count);

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.insert(__pos1, __other, __pos2, __count);

  //Act
  __str.insert(__pos1, __other, __pos2, __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosStrPosCountDynamicToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);
  size_type __pos1 = __str.length() / 2;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  const size_type __pos2 = 1;
  size_type __count = __other.length();
  ADJUST_OUT(1, __count);
  ADJUST_IN(__other.length(), __count);

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.insert(__pos1, __other, __pos2, __count);

  //Act
  __str.insert(__pos1, __other, __pos2, __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosStrPosCountDynamicToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);
  const size_type __pos1 = __str.length();
  const size_type __pos2 = 1;
  size_type __count = __other.length();
  ADJUST_OUT(1, __count);
  ADJUST_IN(__other.length(), __count);

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.insert(__pos1, __other, __pos2, __count);

  //Act
  __str.insert(__pos1, __other, __pos2, __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosOutStrPosCount) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  size_type __pos1 = __str.length() + 1;
  ADJUST_OUT(__str.length() + 1, __pos1);
  const size_type __pos2 = 1;

  //Act

  //Assert
  EXPECT_THROW({
    __str.insert(__pos1, __other, __pos2);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(OperationsTests, InsertSTLStringPosStrPosOutCount) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const size_type __pos1 = 1;
  size_type __pos2 = __other.length() + 1;
  ADJUST_OUT(__other.length() + 1, __pos2);

  //Act

  //Assert
  EXPECT_THROW({
    __str.insert(__pos1, __other, __pos2);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(OperationsTests, InsertMyStringPosStrPosCountLocalBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos1 = 0;
  size_type __pos2 = 1;
  size_type __count = TestFixture::_localBufferLenThreshold - __initLen;
  ADJUST_OUT(1, __count);
  ADJUST_IN(TestFixture::_localBufferLenThreshold - __initLen, __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  const std::basic_string<value_type> __otherCmp(__ilist2);
  __cmp.insert(__pos1, __otherCmp, __pos2, __count);

  //Act
  __str.insert(__pos1, __other, __pos2, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertMyStringPosStrPosCountLocalMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const typename TestFixture::MyTestingString __other(__ilist2);
  size_type __pos1 = __str.length() / 2;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(TestFixture::_localBufferLenThreshold - __initLen, __pos1);
  const size_type __pos2 = 1;
  size_type __count = TestFixture::_localBufferLenThreshold - __initLen;
  ADJUST_OUT(1, __count);
  ADJUST_IN(TestFixture::_localBufferLenThreshold - __initLen, __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  const std::basic_string<value_type> __otherCmp(__ilist2);
  __cmp.insert(__pos1, __otherCmp, __pos2, __count);

  //Act
  __str.insert(__pos1, __other, __pos2, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertMyStringPosStrPosCountLocalEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos1 = __str.length();
  const size_type __pos2 = 1;
  size_type __count = TestFixture::_localBufferLenThreshold - __initLen;
  ADJUST_OUT(1, __count);
  ADJUST_IN(TestFixture::_localBufferLenThreshold - __initLen, __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  const std::basic_string<value_type> __otherCmp(__ilist2);
  __cmp.insert(__pos1, __otherCmp, __pos2, __count);

  //Act
  __str.insert(__pos1, __other, __pos2, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertMyStringPosStrPosCountLocalToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos1 = 0;
  const size_type __pos2 = 1;
  size_type __count = __other.length();
  ADJUST_OUT(1, __count);
  ADJUST_IN(__other.length(), __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  const std::basic_string<value_type> __otherCmp(__ilist2);
  __cmp.insert(__pos1, __otherCmp, __pos2, __count);

  //Act
  __str.insert(__pos1, __other, __pos2, __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertMyStringPosStrPosCountLocalToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  const typename TestFixture::MyTestingString __other(__ilist2);
  size_type __pos1 = __str.length() / 2;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  const size_type __pos2 = 1;
  size_type __count = __other.length();
  ADJUST_OUT(1, __count);
  ADJUST_IN(__other.length(), __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  const std::basic_string<value_type> __otherCmp(__ilist2);
  __cmp.insert(__pos1, __otherCmp, __pos2, __count);

  //Act
  __str.insert(__pos1, __other, __pos2, __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertMyStringPosStrPosCountLocalToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos1 = __str.length();
  const size_type __pos2 = 1;
  size_type __count = __other.length();
  ADJUST_OUT(1, __count);
  ADJUST_IN(__other.length(), __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  const std::basic_string<value_type> __otherCmp(__ilist2);
  __cmp.insert(__pos1, __otherCmp, __pos2, __count);

  //Act
  __str.insert(__pos1, __other, __pos2, __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertMyStringPosStrPosCountDynamicToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos1 = 0;
  const size_type __pos2 = 1;
  size_type __count = __other.length();
  ADJUST_OUT(1, __count);
  ADJUST_IN(__other.length(), __count);

  std::basic_string<value_type> __cmp(__ilist1);
  const std::basic_string<value_type> __otherCmp(__ilist2);
  __cmp.insert(__pos1, __otherCmp, __pos2, __count);

  //Act
  __str.insert(__pos1, __other, __pos2, __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertMyStringPosStrPosCountDynamicToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);
  size_type __pos1 = __str.length() / 2;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  const size_type __pos2 = 1;
  size_type __count = __other.length();
  ADJUST_OUT(1, __count);
  ADJUST_IN(__other.length(), __count);

  std::basic_string<value_type> __cmp(__ilist1);
  const std::basic_string<value_type> __otherCmp(__ilist2);
  __cmp.insert(__pos1, __otherCmp, __pos2, __count);

  //Act
  __str.insert(__pos1, __other, __pos2, __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertMyStringPosStrPosCountDynamicToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);
  const size_type __pos1 = __str.length();
  const size_type __pos2 = 1;
  size_type __count = __other.length();
  ADJUST_OUT(1, __count);
  ADJUST_IN(__other.length(), __count);

  std::basic_string<value_type> __cmp(__ilist1);
  const std::basic_string<value_type> __otherCmp(__ilist2);
  __cmp.insert(__pos1, __otherCmp, __pos2, __count);

  //Act
  __str.insert(__pos1, __other, __pos2, __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertMyStringPosOutStrPosCount) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  size_type __pos1 = __str.length() + 1;
  ADJUST_OUT(__str.length() + 1, __pos1);
  const size_type __pos2 = 1;

  //Act

  //Assert
  EXPECT_THROW({
    __str.insert(__pos1, __other, __pos2);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(OperationsTests, InsertMyStringPosStrPosOutCount) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const size_type __pos1 = 1;
  size_type __pos2 = __other.length() + 1;
  ADJUST_OUT(__other.length() + 1, __pos2);

  //Act

  //Assert
  EXPECT_THROW({
    __str.insert(__pos1, __other, __pos2);
  }, MyTypes::MyException);

  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(OperationsTests, InsertCharIterLocalBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist.begin(), __initLen);

  const value_type __ch = *(__ilist.begin());

  std::basic_string<value_type> __cmp(__ilist.begin(), __initLen);
  auto __retIterCmp = __cmp.insert(__cmp.begin(), __ch);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin(), __ch);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharIterLocalMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist.begin(), __initLen);

  const value_type __ch = *(__ilist.begin());
  size_type __shift = __str.length() / 2;
  ADJUST_OUT(1, __shift);
  ADJUST_IN(__str.length() - 1, __shift);

  std::basic_string<value_type> __cmp(__ilist.begin(), __initLen);
  auto __retIterCmp = __cmp.insert(__cmp.begin() + __shift, __ch);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin() + __shift, __ch);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharIterLocalEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist.begin(), __initLen);

  const value_type __ch = *(__ilist.begin());

  std::basic_string<value_type> __cmp(__ilist.begin(), __initLen);
  auto __retIterCmp = __cmp.insert(__cmp.end(), __ch);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.end(), __ch);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharIterLocalToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const value_type __ch = *(__ilist.begin());

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.insert(__cmp.begin(), __ch);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin(), __ch);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharIterLocalToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const value_type __ch = *(__ilist.begin());
  size_type __shift = __str.length() / 2;
  ADJUST_OUT(1, __shift);
  ADJUST_IN(__str.length() - 1, __shift);

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.insert(__cmp.begin() + __shift, __ch);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin() + __shift, __ch);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharIterLocalToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const value_type __ch = *(__ilist.begin());

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.insert(__cmp.end(), __ch);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.end(), __ch);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharIterDynamicToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());

  std::basic_string<value_type> __cmp(__ilist);
  auto __retIterCmp = __cmp.insert(__cmp.begin(), __ch);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin(), __ch);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharIterDynamicToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());
  size_type __shift = __str.length() / 2;
  ADJUST_OUT(1, __shift);
  ADJUST_IN(__str.length() - 1, __shift);

  std::basic_string<value_type> __cmp(__ilist);
  auto __retIterCmp = __cmp.insert(__cmp.begin() + __shift, __ch);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin() + __shift, __ch);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharIterDynamicToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());

  std::basic_string<value_type> __cmp(__ilist);
  auto __retIterCmp = __cmp.insert(__cmp.end(), __ch);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.end(), __ch);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharIterCountLocalBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const value_type __ch = *(__ilist.begin());
  const size_type __count = TestFixture::_localBufferLenThreshold - __initLen;

  typename TestFixture::MyTestingString __str(__ilist.begin(), __initLen);

  std::basic_string<value_type> __cmp(__ilist.begin(), __initLen);
  auto __retIterCmp = __cmp.insert(__cmp.begin(), __count, __ch);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin(), __count, __ch);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharIterCountLocalMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist.begin(), __initLen);

  const value_type __ch = *(__ilist.begin());
  size_type __shift = __str.length() / 2;
  ADJUST_OUT(1, __shift);
  ADJUST_IN(__str.length() - 1, __shift);
  const size_type __count = TestFixture::_localBufferLenThreshold - __initLen;

  std::basic_string<value_type> __cmp(__ilist.begin(), __initLen);
  auto __retIterCmp = __cmp.insert(__cmp.begin() + __shift, __count, __ch);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin() + __shift, __count, __ch);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharIterCountLocalEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist.begin(), __initLen);

  const value_type __ch = *(__ilist.begin());
  const size_type __count = TestFixture::_localBufferLenThreshold - __initLen;

  std::basic_string<value_type> __cmp(__ilist.begin(), __initLen);
  auto __retIterCmp = __cmp.insert(__cmp.end(), __count, __ch);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.end(), __count, __ch);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharIterCountLocalToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const value_type __ch = *(__ilist.begin());
  size_type __count = 1;
  ADJUST_OUT(TestFixture::_localBufferLenThreshold - __str.length() + 1,
    __count);

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.insert(__cmp.begin(), __count, __ch);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin(), __count, __ch);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharIterCountLocalToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const value_type __ch = *(__ilist.begin());
  size_type __shift = __str.length() / 2;
  ADJUST_OUT(1, __shift);
  ADJUST_IN(__str.length() - 1, __shift);
  size_type __count = 1;
  ADJUST_OUT(TestFixture::_localBufferLenThreshold - __str.length() + 1,
    __count);

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.insert(__cmp.begin() + __shift, __count, __ch);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin() + __shift, __count, __ch);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharIterCountLocalToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const value_type __ch = *(__ilist.begin());
  size_type __count = 1;
  ADJUST_OUT(TestFixture::_localBufferLenThreshold - __str.length() + 1,
    __count);

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.insert(__cmp.end(), __count, __ch);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.end(), __count, __ch);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharIterCountDynamicToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());
  size_type __count = 1;
  ADJUST_OUT(1, __count);


  std::basic_string<value_type> __cmp(__ilist);
  auto __retIterCmp = __cmp.insert(__cmp.begin(), __count, __ch);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin(), __count, __ch);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharIterCountDynamicToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());
  size_type __shift = __str.length() / 2;
  ADJUST_OUT(1, __shift);
  ADJUST_IN(__str.length() - 1, __shift);
  size_type __count = 1;
  ADJUST_OUT(1, __count);

  std::basic_string<value_type> __cmp(__ilist.begin());
  auto __retIterCmp = __cmp.insert(__cmp.begin() + __shift, __count, __ch);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin() + __shift, __count, __ch);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertCharIterCountDynamicToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());
  size_type __count = 1;
  ADJUST_OUT(1, __count);

  std::basic_string<value_type> __cmp(__ilist);
  auto __retIterCmp = __cmp.insert(__cmp.end(), __count, __ch);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.end(), __count, __ch);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertItersRangeIterLocalBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const std::basic_string<value_type> __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  auto __retIterCmp = __cmp.insert(__cmp.begin(), __other.begin(),
    __other.end());
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin(), __other.begin(),
    __other.end());
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertItersRangeIterLocalMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const std::basic_string<value_type> __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);

  size_type __shift = __str.length() / 2;
  ADJUST_OUT(1, __shift);
  ADJUST_IN(__str.length() - 1, __shift);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  auto __retIterCmp = __cmp.insert(__cmp.begin() + __shift, __other.begin(),
    __other.end());
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin() + __shift, __other.begin(),
    __other.end());
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertItersRangeIterLocalEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  const std::basic_string<value_type> __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  auto __retIterCmp = __cmp.insert(__cmp.end(), __other.begin(), __other.end());
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.end(), __other.begin(), __other.end());
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertItersRangeIterLocalToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);


  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.insert(__cmp.begin(), __ilist2.begin(),
    __ilist2.end());
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin(), __ilist2.begin(),
    __ilist2.end());
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertItersRangeIterLocalToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  size_type __shift = __str.length() / 2;
  ADJUST_OUT(1, __shift);
  ADJUST_IN(__str.length() - 1, __shift);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.insert(__cmp.begin() + __shift, __ilist2.begin(),
    __ilist2.end());
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin() + __shift, __ilist2.begin(),
    __ilist2.end());
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertItersRangeIterLocalToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.insert(__cmp.end(), __ilist2.begin(),
    __ilist2.end());
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.end(), __ilist2.begin(),
    __ilist2.end());
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertItersRangeIterDynamicToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  std::basic_string<value_type> __cmp(__ilist1);
  auto __retIterCmp = __cmp.insert(__cmp.end(), __ilist2.begin(),
    __ilist2.end());
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.end(), __ilist2.begin(),
    __ilist2.end());
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertItersRangeIterDynamicToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  size_type __shift = __str.length() / 2;
  ADJUST_OUT(1, __shift);
  ADJUST_IN(__str.length() - 1, __shift);

  std::basic_string<value_type> __cmp(__ilist1);
  auto __retIterCmp = __cmp.insert(__cmp.begin() + __shift, __ilist2.begin(),
    __ilist2.end());
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin() + __shift, __ilist2.begin(),
    __ilist2.end());
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertItersRangeIterDynamicToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  std::basic_string<value_type> __cmp(__ilist1);
  auto __retIterCmp = __cmp.insert(__cmp.end(), __ilist2.begin(),
    __ilist2.end());
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.end(), __ilist2.begin(),
    __ilist2.end());
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertItersRangeIterFirstEqLast) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  std::basic_string<value_type> __cmp(__ilist1);
  auto __retIterCmp = __cmp.insert(__cmp.end(), __ilist2.begin(),
    __ilist2.begin());
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.end(), __ilist2.begin(),
    __ilist2.begin());
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertListIterLocalBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const std::initializer_list<value_type> __ilist2 = {'G', 'o'};

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  auto __retIterCmp = __cmp.insert(__cmp.begin(), __ilist2);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin(), __ilist2);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertListIterLocalMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const std::initializer_list<value_type> __ilist2 = {'G', 'o'};

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  size_type __shift = __str.length() / 2;
  ADJUST_OUT(1, __shift);
  ADJUST_IN(__str.length() - 1, __shift);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  auto __retIterCmp = __cmp.insert(__cmp.begin() + __shift, __ilist2);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin() + __shift, __ilist2);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertListIterLocalEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const std::initializer_list<value_type> __ilist2 = {'G', 'o'};

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  auto __retIterCmp = __cmp.insert(__cmp.end(), __ilist2);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.end(), __ilist2);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertListIterLocalToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.insert(__cmp.begin(), __ilist2);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin(), __ilist2);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertListIterLocalToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  size_type __shift = __str.length() / 2;
  ADJUST_OUT(1, __shift);
  ADJUST_IN(__str.length() - 1, __shift);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.insert(__cmp.begin() + __shift, __ilist2);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin() + __shift, __ilist2);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertListIterLocalToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.insert(__cmp.end(), __ilist2);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.end(), __ilist2);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertListIterDynamicToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  std::basic_string<value_type> __cmp(__ilist1);
  auto __retIterCmp = __cmp.insert(__cmp.end(), __ilist2);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.end(), __ilist2);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertListIterDynamicToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  size_type __shift = __str.length() / 2;
  ADJUST_OUT(1, __shift);
  ADJUST_IN(__str.length() - 1, __shift);

  std::basic_string<value_type> __cmp(__ilist1);
  auto __retIterCmp = __cmp.insert(__cmp.begin() + __shift, __ilist2);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.begin() + __shift, __ilist2);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertListIterDynamicToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  std::basic_string<value_type> __cmp(__ilist1);
  auto __retIterCmp = __cmp.insert(__cmp.end(), __ilist2);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.end(), __ilist2);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, InsertListIterFirstEqLast) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  std::basic_string<value_type> __cmp(__ilist1);
  auto __retIterCmp = __cmp.insert(__cmp.end(), __ilist2);
  auto __diffCmp = std::distance(__cmp.begin(), __retIterCmp);

  //Act
  auto __retIterStr = __str.insert(__str.end(), __ilist2);
  auto __diffStr = std::distance(__str.begin(), __retIterStr);

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, ErasePosCountNone) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  const size_type __pos = 0;
  const size_type __count = 0;

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.erase(__pos, __count);

  //Act
  __str.erase(__pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, ErasePosCountLocalBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const size_type __pos = 0;
  size_type __count = 1;
  ADJUST_OUT(1, __count);

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.erase(__pos, __count);

  //Act
  __str.erase(__pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, ErasePosCountLocalMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  size_type __pos = __str.length() / 2;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 2, __pos);
  size_type __count = 1;
  ADJUST_OUT(1, __count);

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.erase(__pos, __count);

  //Act
  __str.erase(__pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, ErasePosCountLocalEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const size_type __pos = __str.length() - 1;
  size_type __count = 1;
  ADJUST_OUT(1, __count);

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.erase(__pos, __count);

  //Act
  __str.erase(__pos, __count);

  //Assert
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, ErasePosCountDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin());
  
  auto __prevCap = __str.capacity();

  const size_type __pos = 0;
  size_type __count = __str.length() / 2; 
  ADJUST_OUT(1, __count);

  std::basic_string<value_type> __cmp(__ilist);
  __cmp.erase(__pos, __count);

  //Act
  __str.erase(__pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, ErasePosCountDynamicMid) {
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

  std::basic_string<value_type> __cmp(__ilist);
  __cmp.erase(__pos, __count);

  //Act
  __str.erase(__pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, ErasePosCountDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevCap = __str.capacity();

  const size_type __pos = __str.length() - 1;
  size_type __count = __str.length() / 2;
  ADJUST_OUT(1, __count);

  std::basic_string<value_type> __cmp(__ilist);
  __cmp.erase(__pos, __count);

  //Act
  __str.erase(__pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, ErasePosCount) {
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

TYPED_TEST(OperationsTests, EraseIterLocalBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.erase(__cmp.begin());
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin());
  auto __diffStr = std::distance(__retIterStr, __str.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, EraseIterLocalMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  size_type __shift = __str.length() / 2;
  ADJUST_OUT(1, __shift);
  ADJUST_IN(__str.length() - 2, __shift);

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.erase(__cmp.begin() + __shift);
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin() + __shift);
  auto __diffStr = std::distance(__retIterCmp, __cmp.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, EraseIterLocalEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const size_type __shift = __str.length() - 1;

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.erase(__cmp.begin() + __shift);
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin() + __shift);
  auto __diffStr = std::distance(__retIterCmp, __cmp.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, EraseIterDynamicToLocalBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold + 1);
  
  auto __prevCap = __str.capacity();

  std::basic_string<value_type> __cmp(__ilist.begin(),
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

TYPED_TEST(OperationsTests, EraseIterDynamicToLocalMid) {
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

  std::basic_string<value_type> __cmp(__ilist.begin(),
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

TYPED_TEST(OperationsTests, EraseIterDynamicToLocalEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold + 1);

  auto __prevCap = __str.capacity();

  const size_type __shift = __str.length() - 1;

  std::basic_string<value_type> __cmp(__ilist.begin(),
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

TYPED_TEST(OperationsTests, EraseIterDynamicToDynamicBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);
  
  auto __prevCap = __str.capacity();

  std::basic_string<value_type> __cmp(__ilist);
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

TYPED_TEST(OperationsTests, EraseIterDynamicToDynamicMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevCap = __str.capacity();

  size_type __shift = __str.length() / 2;
  ADJUST_OUT(1, __shift);
  ADJUST_IN(__str.length() - 2, __shift);

  std::basic_string<value_type> __cmp(__ilist);
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

TYPED_TEST(OperationsTests, EraseIterDynamicToDynamicEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevCap = __str.capacity();

  const size_type __shift = __str.length() - 1;

  std::basic_string<value_type> __cmp(__ilist);
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

TYPED_TEST(OperationsTests, EraseIterRangeNone) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  const size_type __count = 0;

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __retIterCmp = __cmp.erase(__cmp.begin(), __cmp.begin() + __count);
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin(), __str.begin() + __count);
  auto __diffStr = std::distance(__retIterStr, __str.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, EraseIterRangeLocalBegin) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const size_type __shift = 0;
  size_type __count = 1;
  ADJUST_OUT(1, __count);
  ADJUST_IN(__str.length() - __shift, __count);

  std::basic_string<value_type> __cmp(__ilist.begin(),
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
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, EraseIterRangeLocalMid) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  size_type __shift = __str.length() / 2;
  ADJUST_OUT(1, __shift);
  ADJUST_IN(__str.length() - 2, __shift);
  size_type __count = 1;
  ADJUST_OUT(1, __count);
  ADJUST_IN(__str.length() - __shift, __count);

  std::basic_string<value_type> __cmp(__ilist.begin(),
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
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, EraseIterRangeLocalEnd) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const size_type __shift = __str.length() - 1;
  size_type __count = 1;
  ADJUST_OUT(1, __count);
  ADJUST_IN(__str.length() - __shift, __count);

  std::basic_string<value_type> __cmp(__ilist.begin(),
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
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(OperationsTests, EraseIterRangeDynamicBegin) {
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

  std::basic_string<value_type> __cmp(__ilist);
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

TYPED_TEST(OperationsTests, EraseIterRangeDynamicMid) {
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

  std::basic_string<value_type> __cmp(__ilist);
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

TYPED_TEST(OperationsTests, EraseIterRangeDynamicEnd) {
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

  std::basic_string<value_type> __cmp(__ilist);
  auto __retIterCmp = __cmp.erase(__cmp.begin() + __shift, __cmp.begin() +
    __shift + __count);
  auto __diffCmp = std::distance(__retIterCmp, __cmp.begin());

  //Act
  auto __retIterStr = __str.erase(__str.begin() + __shift, __str.begin() +
    __shift + __count);
  auto __diffStr = std::distance(__retIterStr, __str.begin());

  //Assert
  EXPECT_EQ(__diffStr, __diffCmp);  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}
