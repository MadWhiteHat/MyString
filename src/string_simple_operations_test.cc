#include <gtest/gtest.h>
#include <memory_resource>
#include <string>
#include <memory>
#include <tuple>
#include <type_traits>

#include "test_utils.h"
#include "my_exception.h"

template <typename _Tuple>
class SimpleOperationsTests : public TestingHelper::StringTestingBase<_Tuple> {};

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

TYPED_TEST_SUITE(SimpleOperationsTests, MyParamTypes);

TYPED_TEST(SimpleOperationsTests, ReserveInLocal) {
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

TYPED_TEST(SimpleOperationsTests, ReserveLocalToDynamic) {
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

TYPED_TEST(SimpleOperationsTests, ReserveDynamicToDynamic) {
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
TYPED_TEST(SimpleOperationsTests, ReserveAsShrinkToFit) {
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

TYPED_TEST(SimpleOperationsTests, ShrinkToFitLocal) {
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

TYPED_TEST(SimpleOperationsTests, ShrinkToFitDynamic) {
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

TYPED_TEST(SimpleOperationsTests, ClearLocal) {
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

TYPED_TEST(SimpleOperationsTests, ClearDynamic) {
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

TYPED_TEST(SimpleOperationsTests, PushBackToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold - 1);

  auto __prevCap = __str.capacity();

  const value_type __ch = *(__ilist.begin());

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold - 1);
  __cmp.push_back(__ch);

  //Act
  __str.push_back(__ch);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(SimpleOperationsTests, PushBackLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  const value_type __ch = *(__ilist.begin());

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.push_back(__ch);

  //Act
  __str.push_back(__ch);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(SimpleOperationsTests, PushBackDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevCap = __str.capacity();

  const value_type __ch = *(__ilist.begin());

  std::basic_string<value_type> __cmp(__ilist);
  __cmp.push_back(__ch);

  //Act
  __str.push_back(__ch);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(SimpleOperationsTests, PopBackToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.pop_back();

  //Act
  __str.pop_back();

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(SimpleOperationsTests, PopBackDynamicToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold + 1);

  auto __prevCap = __str.capacity();

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold + 1);
  __cmp.pop_back();

  //Act
  __str.pop_back();

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(SimpleOperationsTests, PopBackDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevCap = __str.capacity();

  std::basic_string<value_type> __cmp(__ilist);
  __cmp.pop_back();

  //Act
  __str.pop_back();

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(SimpleOperationsTests, StartsWithCharTrue) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());

  //Act
  auto __res = __str.starts_with(__ch);

  //Assert
  EXPECT_TRUE(__res);
}

TYPED_TEST(SimpleOperationsTests, StartsWithCharFalse) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin()) + 1;

  //Act
  auto __res = __str.starts_with(__ch);

  //Assert
  EXPECT_FALSE(__res);
}

TYPED_TEST(SimpleOperationsTests, StartsWithCStrTrue) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);
  const typename TestFixture::MyTestingString __other(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  //Act
  auto __res = __str.starts_with(__other.data());

  //Assert
  EXPECT_TRUE(__res);
}

TYPED_TEST(SimpleOperationsTests, StartsWithCStrFalse) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);
  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold);

  //Act
  auto __res = __str.starts_with(__other.data());

  //Assert
  EXPECT_FALSE(__res);
}

TYPED_TEST(SimpleOperationsTests, EndsWithCharTrue) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.end() - 1);

  //Act
  auto __res = __str.ends_with(__ch);

  //Assert
  EXPECT_TRUE(__res);
}

TYPED_TEST(SimpleOperationsTests, EndsWithCharFalse) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.end()) + 1;

  //Act
  auto __res = __str.ends_with(__ch);

  //Assert
  EXPECT_FALSE(__res);
}

TYPED_TEST(SimpleOperationsTests, EndsWithCStrTrue) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);
  const typename TestFixture::MyTestingString __other(__str, 1);

  //Act
  auto __res = __str.ends_with(__other.data());

  //Assert
  EXPECT_TRUE(__res);
}

TYPED_TEST(SimpleOperationsTests, EndsWithCStrFalse) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);
  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold);

  //Act
  auto __res = __str.ends_with(__other.data());

  //Assert
  EXPECT_FALSE(__res);
}

TYPED_TEST(SimpleOperationsTests, ContainsCharTrue) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());

  //Act
  auto __res = __str.contains(__ch);

  //Assert
  EXPECT_TRUE(__res);
}

TYPED_TEST(SimpleOperationsTests, ContainsCharFalse) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = ~*(__ilist.begin());

  //Act
  auto __res = __str.contains(__ch);

  //Assert
  EXPECT_FALSE(__res);
}

TYPED_TEST(SimpleOperationsTests, ContainsCStrTrue) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);
  const typename TestFixture::MyTestingString __other(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  //Act
  auto __res = __str.contains(__other.data());

  //Assert
  EXPECT_TRUE(__res);
}

TYPED_TEST(SimpleOperationsTests, ContainsCStrFalse) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);
  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold);

  //Act
  auto __res = __str.contains(__other.data());

  //Assert
  EXPECT_FALSE(__res);
}

TYPED_TEST(SimpleOperationsTests, SubstrLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);
  size_type __pos = 1;
  size_type __count = TestFixture::_localBufferLenThreshold;
  ADJUST_POS_COUNT_LOCAL(__str.length(), __pos, __count);

  std::basic_string<value_type> __cmp(__ilist);
  auto __resCmp = __cmp.substr(__pos, __count);

  //Act
  auto __resStr = __str.substr(__pos, __count);

  //Assert
  EXPECT_EQ(__resStr.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__resStr.data(), __resStr.length(), __resCmp.data(),
    __resCmp.length());
}

TYPED_TEST(SimpleOperationsTests, SubstrDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);
  size_type __pos = 1;
  size_type __count = TestFixture::_localBufferLenThreshold + 1;
  ADJUST_POS_COUNT_DYNAMIC(__str.length(), __pos, __count);

  std::basic_string<value_type> __cmp(__ilist);
  auto __resCmp = __cmp.substr(__pos, __count);

  //Act
  auto __resStr = __str.substr(__pos, __count);

  //Assert
  EXPECT_GT(__resStr.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__resStr.data(), __resStr.length(), __resCmp.data(),
    __resCmp.length());
}

TYPED_TEST(SimpleOperationsTests, SubstrOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);
  size_type __pos = __str.length() + 1;

  //Act

  //Assert
  EXPECT_THROW({
    auto __resStr = __str.substr(__pos);
  }, MyTypes::MyException);
}

TYPED_TEST(SimpleOperationsTests, CopyPos) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);
  size_type __pos = 1;
  size_type __count = TestFixture::_localBufferLenThreshold + 1;
  ADJUST_POS_COUNT_DYNAMIC(__str.length(), __pos, __count);

  value_type* __cStr = new value_type[__str.length()];
  ASSERT_NE(__cStr, nullptr);
  std::memset(__cStr, 0x00, __str.length());

  std::basic_string<value_type> __cmp(__ilist);
  std::basic_string<value_type> __other(__cmp, __pos, __count);

  //Act
  __str.copy(__cStr, __count, __pos);

  //Assert
  EXPECT_STREQ_CUSTOM(__str.data() + __pos, __count, __cStr,
    std::char_traits<value_type>::length(__cStr));
  delete[] __cStr;
}

TYPED_TEST(SimpleOperationsTests, CopyPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);
  const size_type __pos = __str.length() + 1;

  value_type* __cStr = new value_type[__str.length()];
  ASSERT_NE(__cStr, nullptr);
  std::memset(__cStr, 0x00, __str.length());

  //Act

  //Assert
  EXPECT_THROW({
    __str.copy(__cStr, TestFixture::MyTestingString::npos, __pos);
  }, MyTypes::MyException);
  delete[] __cStr;
}

TYPED_TEST(SimpleOperationsTests, ResizeCountLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist.begin(), __initLen);

  auto __prevCap = __str.capacity();

  size_type __count = __str.length() + 1;
  ADJUST_OUT(__str.length() + 1, __count);
  ADJUST_IN(TestFixture::_localBufferLenThreshold, __count);

  std::basic_string<value_type> __cmp(__ilist.begin(), __initLen);
  __cmp.resize(__count);

  //Act
  __str.resize(__count);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(SimpleOperationsTests, ResizeCountLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  size_type __count = __str.length() + 1;
  ADJUST_OUT(__str.length() + 1, __count);

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.resize(__count);

  //Act
  __str.resize(__count);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(SimpleOperationsTests, ResizeCountDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevCap = __str.capacity();

  size_type __count = __str.length() + 1;
  ADJUST_OUT(__str.length() + 1, __count);

  std::basic_string<value_type> __cmp(__ilist);
  __cmp.resize(__count);

  //Act
  __str.resize(__count);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(SimpleOperationsTests, ResizeCountCharLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist.begin(), __initLen);

  auto __prevCap = __str.capacity();

  size_type __count = __str.length() + 1;
  ADJUST_OUT(__str.length() + 1, __count);
  ADJUST_IN(TestFixture::_localBufferLenThreshold, __count);
  const value_type __ch = *(__ilist.begin());

  std::basic_string<value_type> __cmp(__ilist.begin(), __initLen);
  __cmp.resize(__count, __ch);

  //Act
  __str.resize(__count, __ch);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(SimpleOperationsTests, ResizeCountCharLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  size_type __count = __str.length() + 1;
  ADJUST_OUT(__str.length() + 1, __count);
  const value_type __ch = *(__ilist.begin());

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.resize(__count, __ch);

  //Act
  __str.resize(__count, __ch);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(SimpleOperationsTests, ResizeCountCharDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevCap = __str.capacity();

  size_type __count = __str.length() + 1;
  ADJUST_OUT(__str.length() + 1, __count);
  const value_type __ch = *(__ilist.begin());

  std::basic_string<value_type> __cmp(__ilist);
  __cmp.resize(__count, __ch);

  //Act
  __str.resize(__count, __ch);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(SimpleOperationsTests, ResizeCountCharDecrease) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevCap = __str.capacity();

  size_type __count = __str.length() - 2;
  ADJUST_OUT(1, __count);
  ADJUST_IN(__str.length() - 2, __count);
  const value_type __ch = *(__ilist.begin());

  std::basic_string<value_type> __cmp(__ilist);
  __cmp.resize(__count, __ch);

  //Act
  __str.resize(__count, __ch);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(SimpleOperationsTests, SwapLocalToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevLenStr = __str.length();
  auto __prevCapStr = __str.capacity();

  typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevLenCmp = __other.length();
  auto __prevCapCmp = __other.capacity();

  //Act
  __str.swap(__other);

  //Assert
  EXPECT_EQ(__str.length(), __prevLenCmp);
  EXPECT_EQ(__str.capacity(), __prevCapCmp);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist2.begin(),
    __str.length());

  EXPECT_EQ(__other.length(), __prevLenStr);
  EXPECT_EQ(__other.capacity(), __prevCapStr);
  EXPECT_STREQ_CUSTOM(__other.data(), __other.length(), __ilist1.begin(),
    __other.length());
}

TYPED_TEST(SimpleOperationsTests, SwapDynamicToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevLenStr = __str.length();
  auto __prevCapStr = __str.capacity();

  typename TestFixture::MyTestingString __other(__ilist2);

  auto __prevLenCmp = __other.length();
  auto __prevCapCmp = __other.capacity();

  //Act
  __str.swap(__other);

  //Assert
  EXPECT_EQ(__str.length(), __prevLenCmp);
  EXPECT_EQ(__str.capacity(), __prevCapCmp);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist2.begin(),
    __str.length());

  EXPECT_EQ(__other.length(), __prevLenStr);
  EXPECT_EQ(__other.capacity(), __prevCapStr);
  EXPECT_STREQ_CUSTOM(__other.data(), __other.length(), __ilist1.begin(),
    __other.length());
}

TYPED_TEST(SimpleOperationsTests, SwapLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevLenStr = __str.length();
  auto __prevCapStr = __str.capacity();

  typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevLenCmp = __other.length();
  auto __prevCapCmp = __other.capacity();

  //Act
  __str.swap(__other);

  //Assert
  EXPECT_EQ(__str.length(), __prevLenCmp);
  EXPECT_EQ(__str.capacity(), __prevCapCmp);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist2.begin(),
    __str.length());

  EXPECT_EQ(__other.length(), __prevLenStr);
  EXPECT_EQ(__other.capacity(), __prevCapStr);
  EXPECT_STREQ_CUSTOM(__other.data(), __other.length(), __ilist1.begin(),
    __other.length());
}

TYPED_TEST(SimpleOperationsTests, SwapDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevLenStr = __str.length();
  auto __prevCapStr = __str.capacity();

  typename TestFixture::MyTestingString __other(__ilist2);

  auto __prevLenCmp = __other.length();
  auto __prevCapCmp = __other.capacity();

  //Act
  __str.swap(__other);

  //Assert
  EXPECT_EQ(__str.length(), __prevLenCmp);
  EXPECT_EQ(__str.capacity(), __prevCapCmp);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist2.begin(),
    __str.length());

  EXPECT_EQ(__other.length(), __prevLenStr);
  EXPECT_EQ(__other.capacity(), __prevCapStr);
  EXPECT_STREQ_CUSTOM(__other.data(), __other.length(), __ilist1.begin(),
    __other.length());
}
