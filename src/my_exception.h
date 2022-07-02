#ifndef _MY_EXCEPTION_H
#define _MY_EXCEPTION_H


// #ifdef _ENABLE_EXCEPTIONS
// #define THROW(X) throw MyException(X)
// #else
// #define THROW(X) X
// #endif

#pragma once
#include <iostream>
#include <string>
#include <exception>

class MyException : private std::exception {
	std::string _err_msg;
	
	public:
		MyException(const char* str) : _err_msg(str) {}
		~MyException() = default;
		const std::string& operator=(const MyException& e) {
			_err_msg = e._err_msg;
			return _err_msg;
		}
		const char* what() {return _err_msg.c_str();}
};
	
#endif //_MY_EXCEPTION_H