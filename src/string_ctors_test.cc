#include <gtest/gtest.h>
#include <iostream>
#include <initializer_list>
#include <memory_resource>
#include <string>
#include <memory>
#include <tuple>
#include <type_traits>

#include "test_utils.h"
#include "my_exception.h"

template <typename _Tuple>
class ConstructorsTests : public TestingHelper::StringTestingBase<_Tuple> {};
using TestingHelper::MyParamTypes;

TYPED_TEST_SUITE(ConstructorsTests, MyParamTypes);

TYPED_TEST(ConstructorsTests, Default) {
  //Arrange

  //Act
  const typename TestFixture::MyTestingString __str;

  //Assert
  EXPECT_TRUE(__str.empty());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(ConstructorsTests, Allocator) {
  //Arrange
  using allocator_type = typename TestFixture::allocator_type;

  allocator_type __alloc;

  //Act
  const typename TestFixture::MyTestingString __str(__alloc);

  //Assert
  EXPECT_TRUE(__str.empty());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(ConstructorsTests, SingleChar) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const value_type __ch = *(TestFixture::_str1.begin());

  const typename TestFixture::STLString __cmp(1, __ch);

  //Act
  const typename TestFixture::MyTestingString __str(__ch);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, CharsInLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const value_type __ch = *(TestFixture::_str1.begin());
  const size_type __count = 0x8e % TestFixture::_localBufferCapThreshold;

  const typename TestFixture::STLString __cmp(__count, __ch);

  //Act
  const typename TestFixture::MyTestingString __str(__count, __ch);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, CharsDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const value_type __ch = *(TestFixture::_str1.begin());
  size_type __count = 0x8e % TestFixture::_localBufferCapThreshold +
    TestFixture::_localBufferCapThreshold;
  ADJUST_OUT(TestFixture::_localBufferLenThreshold + 1, __count);

  const typename TestFixture::STLString __cmp(__count, __ch);

  //Act
  const typename TestFixture::MyTestingString __str(__count, __ch);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, STLStringLocalPosInside) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __other(__ilist);

  size_type __pos = 6;
  ADJUST_POS_LOCAL(__other.length(), __pos);

  const typename TestFixture::STLString __cmp(__other, __pos);

  //Act
  const typename TestFixture::MyTestingString __str(__other, __pos);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, STLStringDynamicPosInside) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __other(__ilist);

  size_type __pos = 6;
  ADJUST_POS_DYNAMIC(__other.length(), __pos);

  const typename TestFixture::STLString __cmp(__other, __pos);

  //Act
  const typename TestFixture::MyTestingString __str(__other, __pos);

  //Assert
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, STLStringPosOutside) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __other(__ilist);

  //Act
  size_type __pos = 1000;
  ADJUST_OUT(__other.length() + 1, __pos);

  //Assert
  EXPECT_THROW( {
    const typename TestFixture::MyTestingString __str(__other, __pos);
  }, MyTypes::MyException );
}

TYPED_TEST(ConstructorsTests, STLStringLocalPosInsideCountValid) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __other(__ilist);

  size_type __pos = 6;
  size_type __count = TestFixture::_localBufferLenThreshold;
  ADJUST_POS_COUNT_LOCAL(__other.length(), __pos, __count);

  const typename TestFixture::STLString __cmp(__other, __pos, __count);

  //Act
  const typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, STLStringLocalPosInsideCountOver) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __other(__ilist);

  size_type __pos = 6;
  size_type __count = 1000;
  ADJUST_POS_LOCAL(__other.length(), __pos);
  ADJUST_OUT(__other.length() + 1, __count);

  const typename TestFixture::STLString __cmp(__other, __pos, __count);

  //Act
  const typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, STLStringDynamicPosInsideCountValid) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

   const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __other(__ilist);

  size_type __pos = 6;
  size_type __count = TestFixture::_localBufferCapThreshold;
  ADJUST_POS_COUNT_DYNAMIC(__other.length(), __pos, __count);

  const typename TestFixture::STLString __cmp(__other, __pos, __count);

  //Act
  const typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_GT(__str.capacity(), __count);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, STLStringDynamicPosInsideCountOver) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __other(__ilist);

  size_type __pos = 6;
  size_type __count = 1000;
  ADJUST_POS_DYNAMIC(__other.length(), __pos);
  ADJUST_OUT(__other.length() + 1, __count);

  const typename TestFixture::STLString __cmp(__other, __pos, __count);

  //Act
  const typename TestFixture::MyTestingString __str(__other, __pos, __count);

  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, STLStringPosOutsideCounted) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __other(__ilist);

  size_type __pos = 1000;
  const size_type __count = 6;
  ADJUST_OUT(__other.length() + 1, __pos);
  //Act

  //Assert
  EXPECT_THROW( {
    const typename TestFixture::MyTestingString __str(__other, __pos, __count);
  }, MyTypes::MyException );
}

TYPED_TEST(ConstructorsTests, MyStringLocalPosInside) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __other(__ilist);

  size_type __pos = 6;
  ADJUST_POS_LOCAL(__other.length(), __pos);

  const typename TestFixture::STLString __cmp(__other.data() + __pos);

  //Act
  const typename TestFixture::MyTestingString __str(__other, __pos);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, MyStringDynamicPosInside) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __other(__ilist);

  size_type __pos = 6;
  ADJUST_POS_DYNAMIC(__other.length(), __pos);

  const typename TestFixture::STLString __cmp(__other.data() + __pos);

  //Act
  const typename TestFixture::MyTestingString __str(__other, __pos);

  //Assert
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, MyStringPosOutside) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __other(__ilist);

  size_type __pos = 1000;
  ADJUST_OUT(__other.length() + 1, __pos);

  //Act

  //Assert
  EXPECT_THROW( {
    const typename TestFixture::MyTestingString __str(__other, __pos);
  }, MyTypes::MyException );
}

TYPED_TEST(ConstructorsTests, MyStringLocalPosInsideCountValid) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __other(__ilist);

  size_type __pos = 6;
  size_type __count = TestFixture::_localBufferLenThreshold;
  ADJUST_POS_COUNT_LOCAL(__other.length(), __pos, __count);

  const typename TestFixture::STLString __cmp(__other.data() +  __pos, __count);

  //Act
  const typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, MyStringLocalPosInsideCountOver) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __other(__ilist);

  size_type __pos = 6;
  size_type __count = 1000;
  ADJUST_POS_LOCAL(__other.length(), __pos);
  ADJUST_OUT(__other.length() + 1, __count);

  const typename TestFixture::STLString __helper(__ilist);
  const typename TestFixture::STLString __cmp(__helper, __pos, __count);

  //Act
  const typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, MyStringDynamicPosInsideCountValid) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __other(__ilist);

  size_type __pos = 6;
  size_type __count = TestFixture::_localBufferCapThreshold + 1;
  ADJUST_POS_COUNT_DYNAMIC(__other.length(), __pos, __count);

  const typename TestFixture::STLString __cmp(__other.data() + __pos, __count);

  //Act
  const typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, MyStringDynamicPosInsideCountOver) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __other(__ilist);

  size_type __pos = 6;
  size_type __count = 1000;
  ADJUST_POS_DYNAMIC(__other.length(), __pos);
  ADJUST_OUT(__other.length(), __count);

  const typename TestFixture::STLString __helper(__ilist);
  const typename TestFixture::STLString __cmp(__helper, __pos, __count);

  //Act
  const typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, MyStringPosOutsideCounted) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __other(__ilist);

  size_type __pos = 1000;
  const size_type __count = 6;
  ADJUST_OUT(__other.length() + 1, __pos);

  //Act

  //Assert
  EXPECT_THROW( {
    const typename TestFixture::MyTestingString __str(__other, __pos, __count);
  }, MyTypes::MyException );
}

TYPED_TEST(ConstructorsTests, CStringLocalCounted) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  size_type __count = TestFixture::_localBufferCapThreshold - 2;
  ADJUST_IN(TestFixture::_localBufferLenThreshold, __count);

  const typename TestFixture::STLString __cmp(__ilist.begin(), __count);

  //Act
  const typename TestFixture::MyTestingString __str(__ilist.begin(), __count);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, CStringDynamicCounted) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  size_type __count = TestFixture::_localBufferLenThreshold + 1;
  ADJUST_OUT(TestFixture::_localBufferLenThreshold + 1, __count);

  const typename TestFixture::STLString __cmp(__ilist.begin(), __count);

  //Act
  const typename TestFixture::MyTestingString __str(__ilist.begin(), __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, CStringNullptrCountGTZero) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const value_type* __cStr = nullptr;
  size_type __count = 1;
  ADJUST_OUT(1, __count);

  //Act

  //Assert
  EXPECT_THROW({
    const typename TestFixture::MyTestingString __str(__cStr, __count);
  }, MyTypes::MyException);

}

TYPED_TEST(ConstructorsTests, CStringNullptrCountEQZero) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const value_type* __cStr = nullptr;
  const size_type __count = 0;

  //Act
  const typename TestFixture::MyTestingString __str(__cStr, __count);

  //Assert
  EXPECT_TRUE(__str.empty());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(ConstructorsTests, CStringLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;
  size_type __count = TestFixture::_localBufferLenThreshold;
  ADJUST_IN(TestFixture::_localBufferLenThreshold, __count);

  const typename TestFixture::STLString __cmp(__ilist.begin(), __count);

  //Act
  const typename TestFixture::MyTestingString __str(__ilist.begin(), __count);

  //Assert
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, CStringDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __cmp(__ilist.begin(), __ilist.size());

  //Act
  const typename TestFixture::MyTestingString __str(__ilist.begin(),
    __ilist.size());

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, CStringNullptr) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const value_type* __ilist = nullptr;

  //Act

  //Assert
  EXPECT_THROW({
    const typename TestFixture::MyTestingString __str(__ilist);
  }, MyTypes::MyException);

}

TYPED_TEST(ConstructorsTests, InputIterLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __other(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const typename TestFixture::STLString __cmp(__other.begin(), __other.end());

  //Act
  const typename TestFixture::MyTestingString __str(__other.begin(),
    __other.end());

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, InputIterDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp(__other.begin(), __other.end());

  //Act
  const typename TestFixture::MyTestingString __str(__other.begin(),
    __other.end());

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, STLStringLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __other(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const typename TestFixture::STLString __cmp(__other);

  //Act
  const typename TestFixture::MyTestingString __str(__other);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, STLStringDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp(__other);

  //Act
  const typename TestFixture::MyTestingString __str(__other);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, STLStringLocalAlloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using allocator_type = typename TestFixture::allocator_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __other(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const typename TestFixture::STLString __cmp(__other);

  //Act
  const typename TestFixture::MyTestingString __str(__other, allocator_type());

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, STLStringDynamicAlloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using allocator_type = typename TestFixture::allocator_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp(__other);

  //Act
  const typename TestFixture::MyTestingString __str(__other, allocator_type());

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, MyStringLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __other(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const typename TestFixture::STLString __cmp(__other.data());

  //Act
  const typename TestFixture::MyTestingString __str(__other);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, MyStringDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __other(__ilist);

  const typename TestFixture::STLString __cmp(__other.data());

  //Act
  const typename TestFixture::MyTestingString __str(__other);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, MyStringLocalAlloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using allocator_type = typename TestFixture::allocator_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __other(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  const typename TestFixture::STLString __cmp(__other.data());

  //Act
  const typename TestFixture::MyTestingString __str(__other, allocator_type());

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, MyStringDynamicAlloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using allocator_type = typename TestFixture::allocator_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __other(__ilist);

  const typename TestFixture::STLString __cmp(__other.data());

  //Act
  const typename TestFixture::MyTestingString __str(__other, allocator_type());

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, MoveMyStringLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __other(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevLen = __other.length();

  //Act
  const typename TestFixture::MyTestingString __str(std::move(__other));

  //Assert
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __str.length());
}

TYPED_TEST(ConstructorsTests, MoveMyStringDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __other(__ilist);
  auto __prevLen = __other.length();

  //Act
  const typename TestFixture::MyTestingString __str(std::move(__other));

  //Assert
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_GT(__str.capacity(), __prevLen);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __ilist.size());

  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(ConstructorsTests, MoveMyStringLocalAlloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using allocator_type = typename TestFixture::allocator_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __other(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  auto __prevLen = __other.length();

  //Act
  const typename TestFixture::MyTestingString __str(std::move(__other),
    allocator_type());

  //Assert
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __str.length());
}

TYPED_TEST(ConstructorsTests, MoveMyStringDynamicAlloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using allocator_type = typename TestFixture::allocator_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __other(__ilist);
  auto __prevLen = __other.length();

  //Act
  const typename TestFixture::MyTestingString __str(std::move(__other),
    allocator_type());

  //Assert
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __ilist.size());

  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(ConstructorsTests, InitaiazierListLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  const std::initializer_list<value_type> __ilist =  {'H', 'e', 'l'};

  const typename TestFixture::STLString __cmp(__ilist);

  //Act
  const typename TestFixture::MyTestingString __str(__ilist);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, InitaiazierListDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __cmp(__ilist);

  //Act
  const typename TestFixture::MyTestingString __str(__ilist);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}
