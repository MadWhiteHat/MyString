#include "lib/my_string.h"

#include <cmath>
#include <fstream>
#include <cstdlib>
	

//----------------------------Constructors----------------------------------------//


MyString::MyString() noexcept : _str(nullptr), _length(0), _capacity(0) {
} 

MyString::MyString(const char* str) : MyString(str, strlength(str)) {}

MyString::MyString(const char* str, const size_t count) : MyString() {	
	if(empty(str)) return;
	_length = (strlength(str) < count) ? strlength(str) : count;
	_capacity = count;
	realloc_copy(str);
	std::cout << "Alloc" << std::hex << int64_t(_str) << std::dec << std::endl;
}

MyString::MyString(const std::initializer_list<char>& list) : MyString() {
	if(!list.size()) return;
	_length = _capacity = list.size();
	_str = new(std::nothrow) char[++_capacity];
	if(!empty()) {
		size_t i = 0;
		for(auto &el : list) 
			*(_str + i++) = el; 
		zero();
	} else {
		std::cout << "Throwning bad alloc" << std::endl;
		throw MyException("Bad Allocation");
	}
	
}

MyString::MyString(const std::string& str) : MyString() {
	if(str.empty()) return;
	_length = _capacity = str.length();
	realloc_copy(str.c_str());

}

MyString::MyString(const size_t count, const char ch) : MyString() {
	if(!count) return;
	_length = _capacity = count;
	_str = new(std::nothrow) char[++_capacity];
	if(!empty()) {
		for (size_t i = 0 ;i < _length; ++i) 
			*(_str + i) = ch;
		zero();
	} else {
		std::cout << "Throwning bad alloc" << std::endl;
		throw MyException("Bad Allocation");
	}
}

MyString::MyString(const MyString& str) : MyString() {
	std::cout << "Copy constructor" << std::endl;
	if(str.empty()) return;

	_length = _capacity = str.length();
	realloc_copy(str.c_str());
}


MyString::MyString(const unsigned long long int& cNum) noexcept : MyString() {
	unsigned long long int num = cNum;
	int size = 0;
	while (num) {++size; num /= 10;}
	_length = _capacity = size;
	num = cNum;	
	_str = new(std::nothrow) char[++_capacity];
	if(empty()) return;
	for (int i = size - 1; i >= 0; --i) {
		_str[i] = num % 10 + '0';
		num /=10; 
	}
	zero();
} 

MyString::MyString(const unsigned long int& cNum) noexcept : MyString(static_cast<const unsigned long long int&>(cNum)) {}
MyString::MyString(const unsigned int& cNum) noexcept : MyString(static_cast<const unsigned long long int&>(cNum)) {}
MyString::MyString(const unsigned short& cNum) noexcept : MyString(static_cast<const unsigned long long int&>(cNum)) {}


MyString::MyString(const long long int& cNum) noexcept : MyString() {
	unsigned long long int num = (cNum >0)? cNum : (-cNum);
	if(cNum < 0) ++_length;
	while (num) {++_length; num /= 10;}
	_capacity  = _length ;
	_str = new(std::nothrow) char[++_capacity];
	if(empty()) return;
	_str[0] = '-';	
	num = num = (cNum >0)? cNum : (-cNum);
	if(_str == nullptr) return;
	for (size_t i = _length - 1; num ; --i) {
		_str[i] = num % 10 + '0';
		num /=10; 
	}
	zero();
} 


MyString::MyString(const long int& cNum) noexcept : MyString(static_cast<const long long int&>(cNum)) {}
MyString::MyString(const int& cNum) noexcept : MyString(static_cast<const long long int&>(cNum)) {}
MyString::MyString(const short& cNum) noexcept : MyString(static_cast<const long long int&>(cNum)) {}

MyString::MyString(const long double& cNum) noexcept : MyString() {
	char buf[128];
	for(size_t i = 0; i < 128; ++i) buf[i] = 0;
	std::sprintf(buf, "%Lf", cNum);
	*this = buf;
}
MyString::MyString(const double& cNum) noexcept : MyString() {
	char buf[128];
	for(size_t i = 0; i < 128; ++i) buf[i] = 0;
	std::sprintf(buf, "%f", cNum);
	*this = buf;
}
MyString::MyString(const float& cNum) noexcept : MyString(static_cast<const double&>(cNum)) {}

MyString::MyString(MyString&& str) noexcept : MyString() {
	std::cout << "Move constructor" << std::endl;
	if(!empty()) delete[] _str;
	_str = str._str;
	str._str = nullptr;
	
	_length = str._length;
	str._length = 0;

	_capacity = str._capacity;
	str._capacity = 0;
}


MyString::~MyString() {
	std::cout << "Dealloc" << std::hex << int64_t(_str) << std::dec << std::endl;
	if (!empty()) delete[] _str;
}


//----------------------------Operators----------------------------------------//


MyString MyString::operator+ (const MyString& str) const noexcept{
	return *this + str.c_str();
}
MyString MyString::operator+ (const char* str) const noexcept {
	MyString res_str = *this;
	return res_str += str;
}
MyString MyString::operator+ (const std::string& str) const noexcept {
	return *this + str.c_str();
}
MyString& MyString::operator+= (const MyString& str) noexcept{
	return *this += str.c_str();
}
MyString& MyString::operator+= (const std::string& str)  noexcept {
	return *this += str.c_str();	
}
MyString& MyString::operator+= (const char* str) noexcept {
	if (empty(str)) return *this;	
	if(empty()) return *this = str;
	size_t len1 = _length;
	size_t len2 = strlength(str);
	const char* tmp_str = str;
	if(len1 + len2 < _capacity) {
  		for(size_t i = 0; i < len2; ++i) *(_str + i + len1) = *(tmp_str + i);
		zero(len1 + len2);
	} 				
	else {
		const char* tmp_str = _str;
		_length = _capacity = len1 + len2;
		_str = new(std::nothrow) char[++_capacity];
			if (!empty()) {
				for (size_t i = 0; i < len1; ++i) 
					*(_str + i) = *(tmp_str + i);
				delete[] tmp_str;
				for (size_t i = 0; i < len2; ++i) 
					*(_str + i + len1) = *(str + i);
		}
		zero(len1 + len2);
	}


	return *this;
}
MyString& MyString::operator= (const MyString& str) {
	return (&str == this) ? *this : *this = str.c_str();
}
MyString& MyString::operator= (MyString&& str) noexcept {
	if (&str == this) 
		return *this;
	
	if(!empty()) delete[] _str;
	_str = str._str;
	str._str = nullptr;
	
	_length = str._length;
	str._length = 0;

	_capacity = str._capacity;
	str._capacity = 0;

	return *this;
}

MyString& MyString::operator= (const std::string& str) {
	return *this = str.c_str();
}
MyString& MyString::operator= (const char* str) {
	clear();
	if(empty(str)) { 
		clear(); 
		return *this;
	}
	_length = strlength(str);

	if(_length < _capacity) {
		for(size_t i = 0; i < _length; ++i) *(_str + i) = *(str + i);
	} else {
		delete[] _str;
		_capacity = _length;
		realloc_copy(str);

	}
	return *this;
}
MyString& MyString::operator= (const char str) {
	const char buf[2] = {str, 0};
	return *this = buf;	
}

const char& MyString::operator[] (const size_t idx) const noexcept {return *(_str+idx);}

char& MyString::operator[] (const size_t idx) noexcept {return *(_str+idx);}


bool MyString::operator<(const MyString& str) const noexcept{
	return below(c_str(), str.c_str());
}

bool MyString::operator>(const MyString& str) const noexcept {
	return str < *this;
}

bool MyString::operator>=(const MyString& str) const noexcept {
	return !(*this < str);
}

bool MyString::operator<=(const MyString& str) const noexcept {
	return !(*this > str);
}

bool MyString::operator==(const MyString& str) const noexcept {
	return !(*this > str || *this < str);
}

bool MyString::operator!=(const MyString& str) const noexcept {
	return !(*this == str);
}


const char* MyString::c_str() const noexcept {return _str;}

const char* MyString::data() const noexcept {return _str;}

bool MyString::empty() const noexcept {return empty(_str);}

size_t MyString::length() const noexcept { return _length;}

size_t MyString::size() const noexcept { return _length;}

size_t MyString::capacity() const noexcept {return _capacity;}

void MyString::clear() noexcept {
	_length = 0;
	zero();
}

void MyString::shrink_to_fit() {
	_capacity = _length;
	char* tmp_str_ = _str;
	realloc_copy(tmp_str_);
	delete[] tmp_str_;
}

char& MyString::at(const size_t idx) {
	if(idx >= length()) {
		std::cout << "Throwing out of range" << std::endl;	
		throw MyException("Out of range");

	} else 
		return _str[idx];
}

const char& MyString::at(const size_t idx) const {
	if(idx >= length()) {
		std::cout << "Throwing out of range" << std::endl;	
		throw MyException("Out of range");

	} else 
		return _str[idx];
}


//----------------------------Insert----------------------------------------//



MyString& MyString::insert(const size_t idx, const size_t count, const char sym) {
	char* buf = new(std::nothrow) char[count + 1];
	for(size_t i = 0; i < count; ++i) buf[i] = sym;
	return insert(idx, buf, count);
}


MyString& MyString::insert(const size_t idx, const char* str, const size_t count){
	if(idx > length()) {
		std::cout << "Throwing out of range" << std::endl;	
		throw MyException("Out of range");
		return *this;
	}

	size_t size = 0;

	if(count > strlength(str)) {
		size =  strlength(str);
	} else 
		size = count;
	_length += size;
	if( _capacity < _length) {
		const char* tmp = _str;
		_capacity = _length;
		realloc_copy(tmp);
		delete[] tmp;
	}


	for(size_t i = _length - size; i >= idx; --i) *(_str + i + size) = *(_str + i);
	for(size_t i = 0; i < size; ++i) *(_str + i + idx) = str[i];
	zero();
	return *this;
} 
MyString& MyString::insert(const size_t idx, const char* str) {
	return insert(idx, str, strlength(str));
}
MyString& MyString::insert(const size_t idx, const std::string& str) {
	return insert(idx, str.c_str(), str.length());	
}
MyString& MyString::insert(const size_t idx, const std::string& str, const size_t count) {
	return insert(idx, str.c_str(), count);		
}


//----------------------------Erase----------------------------------------//

MyString& MyString::erase(const size_t idx, const size_t count) {
	if(idx > length()) {
		std::cout << "Throwing out of range" << std::endl;	
		throw MyException("Out of range");
		return *this;
	}

	_length = (idx + count > _length || count > _length)?idx:_length - count;

	for(size_t i = idx ; i < _length; ++i) *(_str + i) = *(_str + i + count);

	return *this;

}


//----------------------------Append----------------------------------------//

MyString&  MyString::append(const size_t count, const char sym) {
	char* buf = new(std::nothrow) char[count+1];
	if (buf == nullptr) return *this;
	for(size_t i = 0; i < count; ++i) buf[i] = sym;
	return append(buf, 0 , count + 1);
}
MyString&  MyString::append(const char* str) {
	return append(str, 0, strlength(str) );
}
MyString&  MyString::append(const char* str, const size_t idx, const size_t count) {
	
	if (idx > strlength(str)) {
		std::cout << "Throwing out of range" << std::endl;	
		throw MyException("Out of range");
		return *this;
	}
	if (count < 2) return *this;
	size_t total = (idx + count > strlength(str)) ? strlength(str) : (idx + count);
	char *temp = new char[total];
	for(size_t i = 0; i < total ; ++i) temp[i] = str[i];
	temp[total] = '\0';
	char* temp_ = temp + idx;
	*this += temp_;
	delete[] temp;
	return *this;

}
MyString&  MyString::append(const std::string& str) {
	return append(str.data(), 0, str.length());
}
MyString&  MyString::append(const std::string& str, const size_t idx, const size_t count){
	return append(str.data(), idx, count);
}


//----------------------------Replace----------------------------------------//


MyString& MyString::replace(const size_t idx, const size_t count, const char* str) {
	try {erase(idx, count);} catch(...) {}
	return insert(idx, str);
}
MyString& MyString::replace(const size_t idx, const size_t count, const std::string& str){
	return replace(idx, count, str.data());
}

//----------------------------Substr----------------------------------------//

MyString MyString::substr(const size_t idx, const size_t count) const {
	if(idx > length()) {
		std::cout << "Throwing out of range" << std::endl;	
		throw MyException("Out of range");
		return *this;
	}

	return MyString(_str + idx, count);
}

MyString MyString::substr(const size_t idx) const {
	return substr(idx, length()-idx);
}

//----------------------------Find----------------------------------------//

long long int MyString::find(const char* str) const noexcept {
	return find(str, 0);
}


long long int MyString::find(const char* str, const size_t idx) const noexcept {
	AhoCorasik a;
	auto vect = a.find(_str, str);
	for(auto &el : vect) {
		if(el > idx) return el;
	}
	return -1;
}

long long int MyString::find(const std::string& str) const noexcept {
	return find(str, 0);
}


long long int MyString::find(const std::string& str, size_t idx) const noexcept {
	return find(str.data(), idx);
}


//----------------------------To_int----------------------------------------//

char MyString::to_char() {
	long long int ch = 0;
	try {
		ch = to_long_long_int();
	} catch (MyException& e) {
		throw e;
		return 0LL;
	}
	if(ch > CHAR_MAX || ch < CHAR_MIN)  {
		std::cout << "Throwing out of range" << std::endl;	
		throw MyException("Out of range");
		return 0LL;
	}
	return static_cast<char>(ch);
}
short MyString::to_short() { 
	long long int sh = 0;
	try {
		sh = to_long_long_int();
	} catch (MyException& e) {
		throw e;
		return 0LL;
	}
	if(sh > SHORT_MAX || sh < SHORT_MIN)  {
		std::cout << "Throwing out of range" << std::endl;	
		throw MyException("Out of range");
		return 0LL;
	}
	return static_cast<short>(sh);
}
int MyString::to_int() { 
	long long int i = 0;
	try {
		i = to_long_long_int();
	} catch (MyException& e) {
		throw e;
		return 0LL;
	}
	if(i > INT_MAX || i < INT_MIN)  {
		std::cout << "Throwing out of range" << std::endl;	
		throw MyException("Out of range");
		return 0LL;
	}
	return static_cast<int>(i);
}

long long int MyString::to_long_long_int() {
	if(empty()) {
		std::cout << "Throwing invailid argument" << std::endl;	
		throw MyException("Invailid argument");
		return 0LL;
	}
	bool bNeg = (_str[0] == '-')?true:false;
	for(int i= (bNeg)?1:0; i < _length; ++i) 
		if(_str[i] > 0x3a || _str[i] < 0x2f) {
			std::cout << "Throwing invailid argument" << std::endl;	
			throw MyException("Invailid argument");
			return 0LL;
		}
	long long int lli = 0, prev = 0;
	for(int i= (bNeg)?1:0; i < _length; ++i) {
		prev = lli;
		lli*=10;
		lli += (_str[i] - '0');
		if(prev > lli) {
			std::cout << "Throwing out of range" << std::endl;	
			throw MyException("Out of range");
			return 0LL;
		}
	}
	return (bNeg)?(-lli):lli;
}

unsigned char MyString::to_uchar() {
	unsigned long long int uCh = 0;
	try {
		uCh = to_ulong_long_int();
	} catch (MyException& e) {
		throw e;
		return 0ULL;
	}
	if(uCh > UCHAR_MAX)  {
		std::cout << "Throwing out of range" << std::endl;	
		throw MyException("Out of range");
		return 0ULL;
	}
	return static_cast<unsigned char>(uCh);
}
unsigned short MyString::to_ushort() {
	unsigned long long int uSh = 0;
	try {
		uSh = to_ulong_long_int();
	} catch (MyException& e) {
		throw e;
		return 0ULL;
	}
	if(uSh > USHORT_MAX)  {
		std::cout << "Throwing out of range" << std::endl;	
		throw MyException("Out of range");
		return 0ULL;
	}
	return static_cast<unsigned short>(uSh);
}
unsigned int MyString::to_uint() {
	unsigned long long int uI = 0;
	try {
		uI = to_ulong_long_int();
	} catch (MyException& e) {
		throw e;
		return 0ULL;
	}
	if(uI > UINT_MAX)  {
		std::cout << "Throwing out of range" << std::endl;	
		throw MyException("Out of range");
		return 0ULL;
	}
	return static_cast<unsigned int>(uI);	
}
unsigned long long int MyString::to_ulong_long_int() {
	if(empty()) {
		std::cout << "Throwing invailid argument" << std::endl;	
		throw MyException("Invailid argument");
		return 0ULL;
	}
	for(int i = 0; i < _length; ++i) 
		if(_str[i] > 0x3a || _str[i] < 0x2f) {
			std::cout << "Throwing invailid argument" << std::endl;	
			throw MyException("Invailid argument");
			return 0ULL;
		}
	unsigned long long int ulli = 0, prev = 0;
	for(int i = 0; i < _length; ++i) {
		prev = ulli;
		ulli*=10;
		ulli += (_str[i] - '0');
		if(prev > ulli) {
			std::cout << "Throwing out of range" << std::endl;	
			throw MyException("Out of range");
			return 0ULL;
		}
	}
	return ulli;
}

//----------------------------To_float----------------------------------------//

long double MyString::to_long_double() {
	char* ptr = nullptr;
	long double ld = strtold(_str, &ptr);
	if(ptr == _str && ld == 0) {
		std::cout << "Throwing invailid argument" << std::endl;	
		throw MyException("Invailid argument");
				
	} else if (ld == HUGE_VALL || ld == -HUGE_VALL) {
		std::cout << "Throwing out of range" << std::endl;	
		throw MyException("Out of range");
	}
	return ld;
}
double MyString::to_double() {
	char* ptr = nullptr;
	long double d = strtod(_str, &ptr);
	if(ptr == _str && d == 0) {
		std::cout << "Throwing invailid argument" << std::endl;	
		throw MyException("Invailid argument");
				
	} else if (d == HUGE_VAL || d == -HUGE_VAL) {
		std::cout << "Throwing out of range" << std::endl;	
		throw MyException("Out of range");
	}
	return d;
}

float MyString::to_float() {
	char* ptr = nullptr;
	long double f = strtof(_str, &ptr);
	if(ptr == _str && f == 0) {
		std::cout << "Throwing invailid argument" << std::endl;	
		throw MyException("Invailid argument");
				
	} else if (f == HUGE_VALF || f == -HUGE_VALF) {
		std::cout << "Throwing out of range" << std::endl;	
		throw MyException("Out of range");
	}
	return f;	
}
		
//----------------------------Iterators----------------------------------------//

using MyConstIterator = MyGenericIterator<const char>;
using MyIterator = MyGenericIterator<char>;

MyIterator MyString::begin() noexcept {
	return MyIterator(_str);
}

MyConstIterator MyString::begin() const noexcept {
	return MyConstIterator(_str);
}


MyConstIterator MyString::cbegin() const noexcept {
	return MyConstIterator(_str);
}


MyIterator MyString::end() noexcept {
	return MyIterator(_str + _length);
}

MyConstIterator MyString::end() const noexcept {
	return MyConstIterator(_str + _length);
}


MyConstIterator MyString::cend() const noexcept {
	return MyConstIterator(_str + _length);
}

MyIterator MyString::rbegin() noexcept {
	return MyIterator(_str + _length - 1, true);
}

MyConstIterator MyString::rbegin() const noexcept {
	return MyConstIterator(_str + _length - 1, true);
}


MyConstIterator MyString::crbegin() const noexcept {
	return MyConstIterator(_str + _length - 1, true);
}


MyIterator MyString::rend() noexcept {
	return MyIterator(_str - 1);
}

MyConstIterator MyString::rend() const noexcept {
	return MyConstIterator(_str - 1);
}


MyConstIterator MyString::crend() const noexcept {
	return MyConstIterator(_str - 1);
}


//----------------------------Insert----------------------------------------//
		
MyIterator MyString::insert(MyConstIterator iter, const char ch) {
	return insert(iter, 1, ch);
}

MyIterator MyString::insert(MyConstIterator iter, size_t count, const char ch) {
	MyString ret = *this;
	return (( ret == insert(iter - cbegin(), count, ch))?MyIterator(_str+(iter - cbegin())-count):MyIterator(_str+(iter - cbegin())));
}
MyIterator MyString::insert(MyConstIterator iter, MyIterator startIter, MyIterator finishIter) {
	int size = finishIter - startIter;
	if(size > 0) {
		auto newIter = startIter;
		char* buf = new char[size];
		buf[size-1] = '\0';	
		for(size_t i = 0; newIter != finishIter; ++newIter) 
			buf[i++] = *newIter;
		MyString ret = *this;
		return (( ret == insert(iter - cbegin(), buf, size))?MyIterator(_str+(iter - cbegin())-size+1):MyIterator(_str+(iter - cbegin())));
	}
	return MyIterator(_str+(iter - cbegin()));
}

MyIterator MyString::insert(MyConstIterator iter, std::initializer_list<const char>& list) {
	size_t size = 0;
	for(auto &el : list) {
		++size;
	}
	char* buf = new(std::nothrow) char[++size];
	size_t i = 0;
	for(auto &el : list) {
		buf[i++] = el;
	}
	buf[size - 1] = '\0';
	MyString ret = *this;
	return (( ret == insert(iter - cbegin(), buf, strlength(buf)))?MyIterator(_str+(iter - cbegin())-strlength(buf)+1):MyIterator(_str+(iter - cbegin())));
}

// //----------------------------Erase----------------------------------------//

MyIterator MyString::erase(MyConstIterator startIter) {
	return erase(startIter, cend());
}
		
MyIterator MyString::erase(MyConstIterator startIter, MyConstIterator finishIter) {
	MyString ret = *this;
	return (( ret == erase(startIter - cbegin(), finishIter - startIter))?MyIterator(_str+(startIter - cbegin())-(finishIter - startIter)+1):MyIterator(_str+(startIter - cbegin())));
}
		
// //----------------------------Replace----------------------------------------//

MyString& MyString::replace(MyConstIterator startIter, MyConstIterator finishIter, const MyString& str) {
	return replace(startIter - cbegin(), finishIter - startIter, str.data());
}
MyString& MyString::replace(MyConstIterator startIter, MyConstIterator finishIter, const char* str, size_t count) {

	char* buf = new(std::nothrow) char[count+1];
	for(size_t i = 0; i < count; ++i) {
		buf[i] = str[i];
	}
	buf[count] = '\0';
	return replace(startIter - cbegin(), finishIter - startIter, str);

}
MyString& MyString::replace(MyConstIterator startIter, MyConstIterator finishIter, const char* str) {
	
	return replace(startIter - cbegin(), finishIter - startIter, str);

}
MyString& MyString::replace(MyConstIterator startIter, MyConstIterator finishIter, size_t count, const char ch) {
	char* buf = new(std::nothrow) char[count+1];
	if(buf == nullptr) return *this;
	for (int i = 0; i < count; ++i) 
		buf[i] = ch;
	buf[count] = '\0'; 
	return replace(startIter - cbegin(), finishIter - startIter, buf);	
}
MyString& MyString::replace(MyConstIterator startIter, MyConstIterator finishIter, std::initializer_list<const char>& list) {
	char* buf = new(std::nothrow) char[list.size() + 1];
	size_t idx = 0;
	for (auto &el : list) 
		buf[idx++] = el;
	buf[idx] = '\0'; 
	return replace(startIter - cbegin(), finishIter - startIter, buf);	
	
}

		
// //----------------------------Substr----------------------------------------//

MyString MyString::substr(MyConstIterator startIter) const {
	return substr(startIter - cbegin());	
}

MyString MyString::substr(MyConstIterator startIter, MyConstIterator finishIter) const {
	return substr(startIter - cbegin(), finishIter - startIter);	
}


// //----------------------------Find----------------------------------------//

long long int MyString::find(const char* str, MyConstIterator iter) const noexcept {
	return find(str, iter - cbegin());
}
long long int MyString::find(std::string& str, MyConstIterator iter) const noexcept {
	return find(str, iter - cbegin());
}


// Private methods

const size_t MyString::strlength(const char * str) noexcept {
	size_t len = 0;
	if(str != nullptr)
		for(; *str != '\0'; ++str, ++len);
	return len;
}

bool MyString::empty(const char* str) const noexcept {return (str == nullptr)?true:false;}


void MyString::zero() noexcept {zero(_length);};

void MyString::zero(const size_t idx) noexcept {
	for(size_t i = idx; i < _capacity; ++i) *(_str+i) = 0;
}

void MyString::realloc_copy(const char* str) {
	_str = new(std::nothrow) char[++_capacity];
	
	if(empty()) {
		std::cout << "Throwning bad alloc" << std::endl;
		throw MyException("Bad Allocation");
		return;
	} else {
		for (size_t i = 0 ;i < _length; ++i) 
			*(_str + i) = str[i];
		zero();
	}
}


bool MyString::below(const char* s1, const char* s2) const noexcept{
	if(s1 == nullptr) return false;
	if(s2 == nullptr) return true;
	for (; *s1 &&  *s1 == *s2; ++s1, ++s2);
	return (*s1 < *s2) ;
}


std::ostream& operator<<(std::ostream& out, const MyString& str) noexcept {
	out << str.c_str();
	return out;
}

std::istream& operator>>(std::istream& in, MyString& str) noexcept {
	char* buffer = new(std::nothrow) char[IN_BUFFER_SIZE];
	if(buffer == nullptr) return in;
	char c = 0;
	in.get(c);
	for(size_t i = 0; !(c == 0x20 || c == 0x0a || c == 0x0d) ; ++i)  {
		buffer[i%IN_BUFFER_SIZE] = c;
		in.get(c);
	}
	
	str = buffer;	

	delete[] buffer;
	return in;
}

std::fstream& operator<<(std::fstream& out, const MyString& str) noexcept {
	
	out << str.data();
	return out;
}

std::fstream& operator>>(std::fstream& in, MyString& str) noexcept {
	if(!(in.is_open())) return in;
	char* buffer = new(std::nothrow) char[IN_BUFFER_SIZE];
	if(buffer == nullptr) return in;
	char c = 0;
	in.get(c);
	for(size_t i = 0; !(c == 0x20 || c == 0x0a || c == 0x0d || in.eof()) ; ++i)  {
		buffer[i%IN_BUFFER_SIZE] = c;
		in.get(c);
	}
	
	str = buffer;	

	delete[] buffer;
	return in;
}

int main() {
	MyString a1("hel"), a2("lo"), a3;
	a3 = a1+a2;
	std::cout << a3 << std::endl;
}