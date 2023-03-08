#ifndef _MY_EXCEPTION_H
#define _MY_EXCEPTION_H
#define SIZE (1 << 10)

#include <iostream>
#include <cstring>
// std::min
#include <algorithm>
#include <exception>
#include <cstdarg>

namespace MyTypes {

class MyException : public std::exception {
 private:
  char _err_msg[SIZE] = {0};
  
 public:
    MyException() {}
    MyException(const char* what_arg) {
      memcpy(_err_msg, what_arg, std::min(strlen(what_arg), size_t(SIZE - 1)));
    }

    MyException(const std::string what_arg) : MyException(what_arg.data()) {}
    
    MyException(const MyException& e) { *this = e; }
    
    ~MyException() = default;
    
    MyException& operator=(const MyException& e) noexcept {
      memcpy(_err_msg, e.what(), strlen(e._err_msg));
      return *this;
    }
    
    inline const char* what() const noexcept {return _err_msg;}
};

class MyOutOfRange : public MyException {
  using MyException::MyException;
};

class MyLengthError : public MyException {
  using MyException::MyException;
};

class MyLogicError : public MyException {
  using MyException::MyException;
};

class MyBadArrayLength : public MyException {
  using MyException::MyException;
};

template <typename _ExceptionType>
void __ThrowMyExceptionFmt(const char* __fmt,...) {
  char buffer[SIZE] = {0};
  std::va_list args;
  va_start(args, __fmt);
  vsnprintf(buffer, SIZE, __fmt, args);
  va_end(args);
  throw _ExceptionType(buffer);
}

} // namespace MyTypes

#endif //_MY_EXCEPTION_H
