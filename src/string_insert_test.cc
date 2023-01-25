#include <gtest/gtest.h>
#include <memory_resource>
#include <string>
#include <memory>
#include <tuple>
#include <type_traits>

#include "test_utils.h"
#include "my_exception.h"

template <typename _Tuple>
class InsertTests : public TestingHelper::StringTestingBase<_Tuple> {};

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

TYPED_TEST_SUITE(InsertTests, MyParamTypes);

TYPED_TEST(InsertTests, ReserveInLocal) {
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

TYPED_TEST(InsertTests, ReserveLocalToDynamic) {
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

TYPED_TEST(InsertTests, ReserveDynamicToDynamic) {
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
TYPED_TEST(InsertTests, ReserveAsShrinkToFit) {
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

TYPED_TEST(InsertTests, ShrinkToFitLocal) {
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

TYPED_TEST(InsertTests, ShrinkToFitDynamic) {
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

TYPED_TEST(InsertTests, ClearLocal) {
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

TYPED_TEST(InsertTests, ClearDynamic) {
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

TYPED_TEST(InsertTests, CharPosLocalBegin) {
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

TYPED_TEST(InsertTests, CharPosLocalMid) {
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

TYPED_TEST(InsertTests, CharPosLocalEnd) {
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

TYPED_TEST(InsertTests, CharPosLocalToDynamicBegin) {
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

TYPED_TEST(InsertTests, CharPosLocalToDynamicMid) {
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

TYPED_TEST(InsertTests, CharPosLocalToDynamicEnd) {
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

TYPED_TEST(InsertTests, CharPosDynamicToDynamicBegin) {
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

TYPED_TEST(InsertTests, CharPosDynamicToDynamicMid) {
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

TYPED_TEST(InsertTests, CharPosDynamicToDynamicEnd) {
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

TYPED_TEST(InsertTests, CharPosOut) {
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

TYPED_TEST(InsertTests, CharPosCountLocalBegin) {
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

TYPED_TEST(InsertTests, CharPosCountLocalMid) {
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

TYPED_TEST(InsertTests, CharPosCountLocalEnd) {
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

TYPED_TEST(InsertTests, CharPosCountLocalToDynamicBegin) {
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

TYPED_TEST(InsertTests, CharPosCountLocalToDynamicMid) {
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

TYPED_TEST(InsertTests, CharPosCountLocalToDynamicEnd) {
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

TYPED_TEST(InsertTests, CharPosCountDynamicToDynamicBegin) {
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

TYPED_TEST(InsertTests, CharPosCountDynamicToDynamicMid) {
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

TYPED_TEST(InsertTests, CharPosCountDynamicToDynamicEnd) {
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

TYPED_TEST(InsertTests, CharPosOutCount) {
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

TYPED_TEST(InsertTests, CStrPosLocalBegin) {
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

TYPED_TEST(InsertTests, CStrPosLocalMid) {
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

TYPED_TEST(InsertTests, CStrPosLocalEnd) {
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

TYPED_TEST(InsertTests, CStrPosLocalToDynamicBegin) {
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

TYPED_TEST(InsertTests, CStrPosLocalToDynamicMid) {
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

TYPED_TEST(InsertTests, CStrPosLocalToDynamicEnd) {
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

TYPED_TEST(InsertTests, CStrPosDynamicToDynamicBegin) {
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

TYPED_TEST(InsertTests, CStrPosDynamicToDynamicMid) {
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

TYPED_TEST(InsertTests, CStrPosDynamicToDynamicEnd) {
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

TYPED_TEST(InsertTests, CStrPosOut) {
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

TYPED_TEST(InsertTests, CStrPosCountLocalBegin) {
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

TYPED_TEST(InsertTests, CStrPosCountLocalMid) {
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

TYPED_TEST(InsertTests, CStrPosCountLocalEnd) {
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

TYPED_TEST(InsertTests, CStrPosCountLocalToDynamicBegin) {
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

TYPED_TEST(InsertTests, CStrPosCountLocalToDynamicMid) {
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

TYPED_TEST(InsertTests, CStrPosCountLocalToDynamicEnd) {
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

TYPED_TEST(InsertTests, CStrPosCountDynamicToDynamicBegin) {
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

TYPED_TEST(InsertTests, CStrPosCountDynamicToDynamicMid) {
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

TYPED_TEST(InsertTests, CStrPosCountDynamicToDynamicEnd) {
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

TYPED_TEST(InsertTests, CStrPosCountOut) {
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

TYPED_TEST(InsertTests, STLStringPosLocalBegin) {
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

TYPED_TEST(InsertTests, STLStringPosLocalMid) {
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

TYPED_TEST(InsertTests, STLStringPosLocalEnd) {
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

TYPED_TEST(InsertTests, STLStringPosLocalToDynamicBegin) {
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

TYPED_TEST(InsertTests, STLStringPosLocalToDynamicMid) {
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

TYPED_TEST(InsertTests, STLStringPosLocalToDynamicEnd) {
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

TYPED_TEST(InsertTests, STLStringPosDynamicToDynamicBegin) {
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

TYPED_TEST(InsertTests, STLStringPosDynamicToDynamicMid) {
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

TYPED_TEST(InsertTests, STLStringPosDynamicToDynamicEnd) {
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

TYPED_TEST(InsertTests, STLStringPosOut) {
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

TYPED_TEST(InsertTests, MyStringPosLocalBegin) {
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

TYPED_TEST(InsertTests, MyStringPosLocalMid) {
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

TYPED_TEST(InsertTests, MyStringPosLocalEnd) {
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

TYPED_TEST(InsertTests, MyStringPosLocalToDynamicBegin) {
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

TYPED_TEST(InsertTests, MyStringPosLocalToDynamicMid) {
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

TYPED_TEST(InsertTests, MyStringPosLocalToDynamicEnd) {
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

TYPED_TEST(InsertTests, MyStringPosDynamicToDynamicBegin) {
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

TYPED_TEST(InsertTests, MyStringPosDynamicToDynamicMid) {
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

TYPED_TEST(InsertTests, MyStringPosDynamicToDynamicEnd) {
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

TYPED_TEST(InsertTests, MyStringPosOut) {
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

TYPED_TEST(InsertTests, STLStringPosStrPosCountLocalBegin) {
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

TYPED_TEST(InsertTests, STLStringPosStrPosCountLocalMid) {
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

TYPED_TEST(InsertTests, STLStringPosStrPosCountLocalEnd) {
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

TYPED_TEST(InsertTests, STLStringPosStrPosCountLocalToDynamicBegin) {
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

TYPED_TEST(InsertTests, STLStringPosStrPosCountLocalToDynamicMid) {
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

TYPED_TEST(InsertTests, STLStringPosStrPosCountLocalToDynamicEnd) {
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

TYPED_TEST(InsertTests, STLStringPosStrPosCountDynamicToDynamicBegin) {
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

TYPED_TEST(InsertTests, STLStringPosStrPosCountDynamicToDynamicMid) {
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

TYPED_TEST(InsertTests, STLStringPosStrPosCountDynamicToDynamicEnd) {
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

TYPED_TEST(InsertTests, STLStringPosOutStrPosCount) {
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

TYPED_TEST(InsertTests, STLStringPosStrPosOutCount) {
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

TYPED_TEST(InsertTests, MyStringPosStrPosCountLocalBegin) {
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

TYPED_TEST(InsertTests, MyStringPosStrPosCountLocalMid) {
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

TYPED_TEST(InsertTests, MyStringPosStrPosCountLocalEnd) {
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

TYPED_TEST(InsertTests, MyStringPosStrPosCountLocalToDynamicBegin) {
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

TYPED_TEST(InsertTests, MyStringPosStrPosCountLocalToDynamicMid) {
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

TYPED_TEST(InsertTests, MyStringPosStrPosCountLocalToDynamicEnd) {
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

TYPED_TEST(InsertTests, MyStringPosStrPosCountDynamicToDynamicBegin) {
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

TYPED_TEST(InsertTests, MyStringPosStrPosCountDynamicToDynamicMid) {
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

TYPED_TEST(InsertTests, MyStringPosStrPosCountDynamicToDynamicEnd) {
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

TYPED_TEST(InsertTests, MyStringPosOutStrPosCount) {
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

TYPED_TEST(InsertTests, MyStringPosStrPosOutCount) {
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

TYPED_TEST(InsertTests, CharIterLocalBegin) {
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

TYPED_TEST(InsertTests, CharIterLocalMid) {
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

TYPED_TEST(InsertTests, CharIterLocalEnd) {
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

TYPED_TEST(InsertTests, CharIterLocalToDynamicBegin) {
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

TYPED_TEST(InsertTests, CharIterLocalToDynamicMid) {
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

TYPED_TEST(InsertTests, CharIterLocalToDynamicEnd) {
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

TYPED_TEST(InsertTests, CharIterDynamicToDynamicBegin) {
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

TYPED_TEST(InsertTests, CharIterDynamicToDynamicMid) {
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

TYPED_TEST(InsertTests, CharIterDynamicToDynamicEnd) {
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

TYPED_TEST(InsertTests, CharIterCountLocalBegin) {
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

TYPED_TEST(InsertTests, CharIterCountLocalMid) {
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

TYPED_TEST(InsertTests, CharIterCountLocalEnd) {
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

TYPED_TEST(InsertTests, CharIterCountLocalToDynamicBegin) {
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

TYPED_TEST(InsertTests, CharIterCountLocalToDynamicMid) {
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

TYPED_TEST(InsertTests, CharIterCountLocalToDynamicEnd) {
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

TYPED_TEST(InsertTests, CharIterCountDynamicToDynamicBegin) {
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

TYPED_TEST(InsertTests, CharIterCountDynamicToDynamicMid) {
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

TYPED_TEST(InsertTests, CharIterCountDynamicToDynamicEnd) {
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

TYPED_TEST(InsertTests, ItersRangeIterLocalBegin) {
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

TYPED_TEST(InsertTests, ItersRangeIterLocalMid) {
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

TYPED_TEST(InsertTests, ItersRangeIterLocalEnd) {
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

TYPED_TEST(InsertTests, ItersRangeIterLocalToDynamicBegin) {
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

TYPED_TEST(InsertTests, ItersRangeIterLocalToDynamicMid) {
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

TYPED_TEST(InsertTests, ItersRangeIterLocalToDynamicEnd) {
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

TYPED_TEST(InsertTests, ItersRangeIterDynamicToDynamicBegin) {
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

TYPED_TEST(InsertTests, ItersRangeIterDynamicToDynamicMid) {
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

TYPED_TEST(InsertTests, ItersRangeIterDynamicToDynamicEnd) {
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

TYPED_TEST(InsertTests, ItersRangeIterFirstEqLast) {
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

TYPED_TEST(InsertTests, ListIterLocalBegin) {
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

TYPED_TEST(InsertTests, ListIterLocalMid) {
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

TYPED_TEST(InsertTests, ListIterLocalEnd) {
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

TYPED_TEST(InsertTests, ListIterLocalToDynamicBegin) {
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

TYPED_TEST(InsertTests, ListIterLocalToDynamicMid) {
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

TYPED_TEST(InsertTests, ListIterLocalToDynamicEnd) {
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

TYPED_TEST(InsertTests, ListIterDynamicToDynamicBegin) {
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

TYPED_TEST(InsertTests, ListIterDynamicToDynamicMid) {
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

TYPED_TEST(InsertTests, ListIterDynamicToDynamicEnd) {
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

TYPED_TEST(InsertTests, ListIterFirstEqLast) {
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
