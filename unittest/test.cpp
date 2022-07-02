#include <iostream>
#include "../lib/my_string.h"

#include "../my_string.cpp"
#include <gtest/gtest.h>

const char testLongString[] = "I am honored to be with you today at your commencement from one of the finest universities in the world. I never graduated from college. Truth be told, this is the closest I’ve ever gotten to a college graduation. Today I want to tell you three stories from my life. That’s it. No big deal. Just three stories.";
const char testShortString[] = "Stay Hungry. Stay Foolish.";
const char *testNullptrString = nullptr;

TEST (Concatenate_test, string_string) {
	std::string sStr1 = testLongString;
	std::string sStr2 = testShortString;
	std::string sStr3;
	sStr3 = sStr1 + sStr2;
	
	MyString myStr1 = testLongString;
	MyString myStr2 = testShortString;
	MyString myStr3;
	myStr3 = myStr1 + myStr2;


	ASSERT_EQ(sStr3.length(), myStr3.length());
	for(size_t i = 0; i < sStr3.length(); ++i) {
		ASSERT_EQ(sStr3[i], myStr3[i]);
	}
}

TEST (Concatenate_test, nullstring_string) {
	std::string sStr1;
	std::string sStr2 = testShortString;
	std::string sStr3;
	sStr3 = sStr1 + sStr2;
	
	MyString myStr1;
	MyString myStr2 = testShortString;
	MyString myStr3;
	myStr3 = myStr1 + myStr2;


	ASSERT_EQ(sStr3.length(), myStr3.length());
	for(size_t i = 0; i < sStr3.length(); ++i) {
		ASSERT_EQ(sStr3[i], myStr3[i]);
	}
}

TEST (Concatenate_test, string_nullstring) {
	std::string sStr1;
	std::string sStr2 = testShortString;
	std::string sStr3;
	sStr3 = sStr2 + sStr1;
	
	MyString myStr1;
	MyString myStr2 = testShortString;
	MyString myStr3;
	myStr3 = myStr2 + myStr1;


	ASSERT_EQ(sStr3.length(), myStr3.length());
	for(size_t i = 0; i < sStr3.length(); ++i) {
		ASSERT_EQ(sStr3[i], myStr3[i]);
	}
}


TEST (Concatenate_test, string_and_char_string) {
	std::string sStr1 = testShortString;
	std::string sStr2;
	sStr2 = sStr1 + testLongString;
	
	MyString myStr1 = testShortString;
	MyString myStr2;
	myStr2 = myStr1 + testLongString;


	ASSERT_EQ(sStr2.length(), myStr2.length());
	for(size_t i = 0; i < sStr2.length(); ++i) {
		ASSERT_EQ(sStr2[i], myStr2[i]);
	}
}


TEST (Concatenate_test, nullstring_and_char_string) {
	std::string sStr1;
	std::string sStr2;
	sStr2 = sStr1 + testLongString;
	
	MyString myStr1;
	MyString myStr2;
	myStr2 = myStr1 + testLongString;


	ASSERT_EQ(sStr2.length(), myStr2.length());
	for(size_t i = 0; i < sStr2.length(); ++i) {
		ASSERT_EQ(sStr2[i], myStr2[i]);
	}
}


TEST (Concatenate_test, string_and_null_char_string) {
	
	std::string sStr1 = testShortString;
	std::string sStr2;
	
	sStr2 = sStr1 + std::string();
	

	MyString myStr1 = testShortString;
	MyString myStr2;
	myStr2 = myStr1 + testNullptrString;


	ASSERT_EQ(sStr2.length(), myStr2.length());
	for(size_t i = 0; i < sStr2.length(); ++i) {
		ASSERT_EQ(sStr2[i], myStr2[i]);
	}
}

TEST (Concatenate_test, string_and_std_string) {
	
	std::string sStr1 = testShortString;
	std::string sStr2 = testLongString;
	std::string sStr3;
	
	sStr3 = sStr1 + sStr2;
	

	MyString myStr1 = testShortString;
	MyString myStr3;
	myStr3 = myStr1 + sStr2;


	ASSERT_EQ(sStr3.length(), myStr3.length());
	for(size_t i = 0; i < sStr3.length(); ++i) {
		ASSERT_EQ(sStr3[i], myStr3[i]);
	}
}

TEST (Assignment_concatenate_test, string_and_char_string) {
	
	std::string sStr1 = testShortString;
	sStr1 += testLongString;	

	MyString myStr1 = testShortString;
	myStr1 += testLongString;


	ASSERT_EQ(sStr1.length(), myStr1.length());
	for(size_t i = 0; i < sStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}


TEST (Assignment_concatenate_test, string_and_null_char_string) {
	
	std::string sStr1 = testShortString;
	sStr1 += std::string();	

	MyString myStr1 = testShortString;
	myStr1 += testNullptrString;


	ASSERT_EQ(sStr1.length(), myStr1.length());
	for(size_t i = 0; i < sStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}

TEST (Assignment_concatenate_test, string_and_std_string) {
	
	std::string sStr1 = testShortString;
	std::string sStr2 = testLongString;
	sStr1 += sStr2;	

	MyString myStr1 = testShortString;
	myStr1 += sStr2;


	ASSERT_EQ(sStr1.length(), myStr1.length());
	for(size_t i = 0; i < sStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}


TEST (Assignment_concatenate_test, string_and_null_std_string) {
	
	std::string sStr1 = testShortString;
	std::string sStr2;
	sStr1 += sStr2;	

	MyString myStr1 = testShortString;
	myStr1 += sStr2;


	ASSERT_EQ(sStr1.length(), myStr1.length());
	for(size_t i = 0; i < sStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Assignment_test, string_and_char_string) {
	
	std::string sStr1 = testShortString;
	sStr1 = testLongString;	

	MyString myStr1 = testShortString;
	myStr1 = testLongString;


	ASSERT_EQ(sStr1.length(), myStr1.length());
	for(size_t i = 0; i < sStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Assignment_test, string_and_null_char_string) {
	
	std::string sStr1 = testShortString;
	sStr1 = std::string();	

	MyString myStr1 = testShortString;
	myStr1 = testNullptrString;


	ASSERT_EQ(sStr1.length(), myStr1.length());
	for(size_t i = 0; i < sStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Assignment_test, string_and_null_std_string) {
	
	std::string sStr1;
	std::string sStr2;
	sStr2 = sStr1;	

	MyString myStr2;
	myStr2 = sStr1;

	ASSERT_EQ(sStr2.length(), myStr2.length());
	for(size_t i = 0; i < sStr2.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr2[i]);
	}
}


TEST (Assignment_test, string_and_char) {
	
	std::string sStr1;
	sStr1 = '2';	

	MyString myStr1;
	myStr1 = '2';

	ASSERT_EQ(sStr1.length(), myStr1.length());
	for(size_t i = 0; i < sStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Compare_test, equal_str) {
	
	MyString myStr1 = testShortString;
	MyString myStr2 = testShortString;
	std::string sStr1 = testShortString;
	std::string sStr2 = testShortString;

	ASSERT_EQ(sStr1 > sStr2, myStr1 > myStr2);
	ASSERT_EQ(sStr1 < sStr2, myStr1 < myStr2);
	ASSERT_EQ(sStr1 >= sStr2, myStr1 >= myStr2);
	ASSERT_EQ(sStr1 <= sStr2, myStr1 <= myStr2);
	ASSERT_EQ(sStr1 == sStr2, myStr1 == myStr2);
	ASSERT_EQ(sStr1 != sStr2, myStr1 != myStr2);
}




TEST (Compare_test, unequal_str) {
	
	MyString myStr1 = testShortString;
	MyString myStr2 = testLongString;
	std::string sStr1 = testShortString;
	std::string sStr2 = testLongString;

	ASSERT_EQ(sStr1 > sStr2, myStr1 > myStr2);
	ASSERT_EQ(sStr1 < sStr2, myStr1 < myStr2);
	ASSERT_EQ(sStr1 >= sStr2, myStr1 >= myStr2);
	ASSERT_EQ(sStr1 <= sStr2, myStr1 <= myStr2);
	ASSERT_EQ(sStr1 == sStr2, myStr1 == myStr2);
	ASSERT_EQ(sStr1 != sStr2, myStr1 != myStr2);
}


TEST (Inner_test, c_str) {
	
	std::string sStr1 = testShortString;
	MyString myStr1 = testShortString;


	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}


TEST (Inner_test, data) {
	
	std::string sStr1 = testShortString;
	MyString myStr1 = testShortString;


	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}


TEST (Inner_test, length) {
	
	std::string sStr1 = testShortString;
	MyString myStr1 = testShortString;
	
	ASSERT_EQ(sStr1.length(), myStr1.length());
	
}


TEST (Inner_test, size) {
	
	std::string sStr1 = testShortString;
	MyString myStr1 = testShortString;
	
	ASSERT_EQ(sStr1.size(), myStr1.size());
	
}



TEST (Inner_test, empty) {
	
	std::string sStr1 = testShortString;
	MyString myStr1 = testShortString;
	
	ASSERT_EQ(sStr1.empty(), myStr1.empty());
	
}





TEST (Inner_test, shrink_to_fit_and_capacity) {
	
	MyString myStr1 = testShortString;
	
	myStr1.shrink_to_fit();
	
	ASSERT_EQ(strlen(testShortString)+1, myStr1.capacity());
	
}



TEST (Inner_test, clear) {
	
	std::string sStr1 = testShortString;
	MyString myStr1 = testShortString;
	
	sStr1.clear();
	myStr1.clear();
	ASSERT_EQ(sStr1.length(), myStr1.length());
	
}




TEST (Insert_test, insert_short_1000_0_a) {
	
	std::string sStr1 = testShortString;
	MyString myStr1 = testShortString;
	
	bool b_sStr, b_myStr;
	b_sStr = b_myStr = true;

	try {

		sStr1.insert(1000, 0, 'a');

	} catch(std::exception) {
		b_sStr = true;
	}
	
	try {

		myStr1.insert(1000, 0, 'a');

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Insert_test, insert_short_1000_20_a) {
	
	std::string sStr1 = testShortString;
	MyString myStr1 = testShortString;
	
	bool b_sStr, b_myStr;
	b_sStr = b_myStr = true;

	try {

		sStr1.insert(1000, 20, 'a');

	} catch(std::exception) {
		b_sStr = true;
	}
	
	try {

		myStr1.insert(1000, 20, 'a');

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_EQ(b_sStr, b_myStr);
	
	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}


TEST (Insert_test, insert_short_5_0_a) {
	
	std::string sStr1 = testShortString;
	MyString myStr1 = testShortString;
	
	bool b_sStr, b_myStr;
	b_sStr = b_myStr = true;

	try {

		sStr1.insert(5, 0, 'a');

	} catch(std::exception) {
		b_sStr = true;
	}
	
	try {

		myStr1.insert(5, 0, 'a');

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_EQ(b_sStr, b_myStr);
	
	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}


TEST (Insert_test, insert_short_5_5_a) {
	
	std::string sStr1 = testShortString;
	MyString myStr1 = testShortString;
	
	bool b_sStr, b_myStr;
	b_sStr = b_myStr = true;

	try {

		sStr1.insert(5, 5, 'a');

	} catch(std::exception) {
		b_sStr = true;
	}
	
	try {

		myStr1.insert(5, 5, 'a');

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_EQ(b_sStr, b_myStr);
	
	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Insert_test, insert_short_1000_longStr) {
	
	std::string sStr1 = testShortString;
	MyString myStr1 = testShortString;
	
	bool b_sStr, b_myStr;
	b_sStr = b_myStr = true;

	try {

		sStr1.insert(1000, testLongString);

	} catch(std::exception) {
		b_sStr = true;
	}
	
	try {

		myStr1.insert(1000, testLongString);

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_EQ(b_sStr, b_myStr);
	
	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}




TEST (Insert_test, insert_short_5_longStr) {
	
	std::string sStr1 = testShortString;
	MyString myStr1 = testShortString;
	
	bool b_sStr, b_myStr;
	b_sStr = b_myStr = true;

	try {

		sStr1.insert(5, testLongString);

	} catch(std::exception) {
		b_sStr = true;
	}
	
	try {

		myStr1.insert(5, testLongString);

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_EQ(b_sStr, b_myStr);
	
	ASSERT_EQ(sStr1.length(), myStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Insert_test, insert_short_5_longStr_5) {
	
	std::string sStr1 = testShortString;
	MyString myStr1 = testShortString;
	
	bool b_sStr, b_myStr;
	b_sStr = b_myStr = true;

	try {

		sStr1.insert(5, testLongString, 5);

	} catch(std::exception) {
		b_sStr = true;
	}
	
	try {

		myStr1.insert(5, testLongString, 5);

	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);
	
	ASSERT_EQ(sStr1.length(), myStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Insert_test, insert_short_5_longStr_1000) {

	char expected_output[] = "Stay I am honored to be with you today at your commencement from one of the finest universities in the world. I never graduated from college. Truth be told, this is the closest I’ve ever gotten to a college graduation. Today I want to tell you three stories from my life. That’s it. No big deal. Just three stories.Hungry. Stay Foolish.";

	MyString myStr1 = testShortString;
	bool b_myStr = false;	

	try {

		myStr1.insert(5, testLongString, 1000);

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_FALSE(b_myStr);

	ASSERT_EQ(myStr1.length(), strlen(expected_output));

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(expected_output[i], myStr1[i]);
	}
}



TEST (Insert_test, insert_short_1000_longStr_5) {
	
	std::string sStr1 = testShortString;
	bool b_sStr = false;	

	try {

		sStr1.insert(1000, testLongString, 5);

	} catch(std::exception) {

		b_sStr = true;
	}	

	MyString myStr1 = testShortString;
	bool b_myStr = false;	

	try {

		myStr1.insert(1000, testLongString, 5);

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_EQ(b_myStr, b_sStr);

	ASSERT_EQ(myStr1.length(), sStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}




TEST (Insert_test, insert_short_1000_std_longStr) {
	
	std::string sStr1 = testShortString;
	std::string sStr2 = testLongString;
	bool b_sStr = false;	

	try {

		sStr1.insert(1000, sStr2);

	} catch(std::exception) {

		b_sStr = true;
	}	

	MyString myStr1 = testShortString;
	bool b_myStr = false;	

	try {

		myStr1.insert(1000, sStr2);

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_EQ(b_myStr, b_sStr);

	ASSERT_EQ(myStr1.length(), sStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}





TEST (Insert_test, insert_short_5_std_longStr) {
	
	
	std::string sStr1 = testShortString;
	std::string sStr2 = testLongString;
	bool b_sStr = false;	

	try {

		sStr1.insert(5, sStr2);

	} catch(std::exception) {

		b_sStr = true;
	}	

	MyString myStr1 = testShortString;
	bool b_myStr = false;	

	try {

		myStr1.insert(5, sStr2);

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_EQ(b_myStr, b_sStr);

	ASSERT_EQ(myStr1.length(), sStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}






TEST (Insert_test, insert_short_1000_std_longStr_1000) {
	
	
	std::string sStr1 = testShortString;
	std::string sStr2 = testLongString;
	bool b_sStr = false;	

	try {

		sStr1.insert(1000, sStr2, 1000);

	} catch(std::exception) {

		b_sStr = true;
	}	

	MyString myStr1 = testShortString;
	bool b_myStr = false;	

	try {

		myStr1.insert(1000, sStr2, 1000);

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_EQ(b_myStr, b_sStr);

	ASSERT_EQ(myStr1.length(), sStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Insert_test, insert_short_5_std_longStr_1000) {
	
	MyString myStr1 = testShortString;
	char expected_output[] = "Stay I am honored to be with you today at your commencement from one of the finest universities in the world. I never graduated from college. Truth be told, this is the closest I’ve ever gotten to a college graduation. Today I want to tell you three stories from my life. That’s it. No big deal. Just three stories.Hungry. Stay Foolish.";
	std::string sStr2 = testLongString;
	bool b_myStr = false;
	try {

		myStr1.insert(5, sStr2, 1000);

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_FALSE(b_myStr);

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(expected_output[i], myStr1[i]);
	}
}



TEST (Insert_test, insert_short_5_std_longStr_5) {
	
	char expected_output[] = "Stay I am Hungry. Stay Foolish.";
	std::string sStr2 = testLongString;
	MyString myStr1 = testShortString;
	bool b_myStr = false;	

	try {

		myStr1.insert(5, sStr2, 5);

	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_FALSE(b_myStr);

	ASSERT_EQ(myStr1.length(), strlen(expected_output));

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(expected_output[i], myStr1[i]);
	}
}




TEST (Erase_test, erase_short_5_5) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	
	bool b_sStr = false;	

	try {

		sStr1.erase(5, 5);

	} catch(std::exception) {

		b_sStr = true;
	}

	bool b_myStr = false;	

	try {

		myStr1.erase(5, 5);

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}





TEST (Erase_test, erase_short_5_100) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	
	bool b_sStr = false;	

	try {

		sStr1.erase(5, 100);

	} catch(std::exception) {

		b_sStr = true;
	}

	bool b_myStr = false;	

	try {

		myStr1.erase(5, 100);

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}





TEST (Erase_test, erase_short_100_5) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	
	bool b_sStr = false;	

	try {

		sStr1.erase(100, 5);

	} catch(std::exception) {

		b_sStr = true;
	}

	bool b_myStr = false;	
	
	try {

		myStr1.erase(100, 5);

	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}





TEST (Append_test, append_char_4_a) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	
	bool b_sStr = false;	

	try {

		sStr1.append(4, 'a');

	} catch(std::exception) {

		b_sStr = true;
	}

	bool b_myStr = false;	
	
	try {

		myStr1.append(4, 'a');

	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Append_test, append_char_0_a) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	
	bool b_sStr = false;	

	try {

		sStr1.append(0, 'a');

	} catch(std::exception) {

		b_sStr = true;
	}

	bool b_myStr = false;	
	
	try {

		myStr1.append(0, 'a');

	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Append_test, append_str) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	
	bool b_sStr = false;	

	try {

		sStr1.append(testLongString);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.append(testLongString);

	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Append_test, append_str_0_10) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	
	bool b_sStr = false;	

	try {

		sStr1.append(testLongString, 0, 10);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.append(testLongString, 0,10);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Append_test, append_str_10_10) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	
	bool b_sStr = false;	

	try {

		sStr1.append(testLongString, 10 ,10);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.append(testLongString, 10, 10);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Append_test, append_str_1000_3) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	
	bool b_sStr = false;	

	try {

		sStr1.append(testLongString, 1000, 3);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.append(testLongString, 1000, 3);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}




TEST (Append_test, append_str_3_1000) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	
	bool b_sStr = false;	

	try {

		sStr1.append(testLongString, 3, 1000);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.append(testLongString, 3, 1000);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}




TEST (Append_test, append_str_1000_1000) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	
	bool b_sStr = false;	

	try {

		sStr1.append(testLongString, 1000, 1000);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.append(testLongString, 1000, 1000);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Append_test, append_std_str) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	std::string sStr2 = testLongString;
	bool b_sStr = false;	

	try {

		sStr1.append(sStr2);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.append(sStr2);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Append_test, append_null_std_str) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	std::string sStr2;
	bool b_sStr = false;	

	try {

		sStr1.append(sStr2);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.append(sStr2);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Append_test, append_null_std_str_0_10) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	std::string sStr2;
	bool b_sStr = false;	

	try {

		sStr1.append(sStr2, 0, 10);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.append(sStr2, 0 , 10);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Append_test, append_null_std_str_1000_1000) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	std::string sStr2;
	bool b_sStr = false;	

	try {

		sStr1.append(sStr2, 1000, 1000);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.append(sStr2, 1000, 1000);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}




TEST (Append_test, append_std_str_0_0) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	std::string sStr2 = testLongString;
	bool b_sStr = false;	

	try {

		sStr1.append(sStr2, 0, 0);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.append(sStr2, 0, 0);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}






TEST (Append_test, append_std_str_0_10) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	std::string sStr2 = testLongString;
	bool b_sStr = false;	

	try {

		sStr1.append(sStr2, 0, 10);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.append(sStr2, 0, 10);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}




TEST (Append_test, append_std_str_0_1000) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	std::string sStr2 = testLongString;
	bool b_sStr = false;	

	try {

		sStr1.append(sStr2, 0, 1000);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.append(sStr2, 0, 1000);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}




TEST (Append_test, append_std_str_6_1000) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	std::string sStr2 = testLongString;
	bool b_sStr = false;	

	try {

		sStr1.append(sStr2, 6, 1000);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.append(sStr2, 6, 1000);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}




TEST (Append_test, append_std_str_1000_6) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	std::string sStr2 = testLongString;
	bool b_sStr = false;	

	try {

		sStr1.append(sStr2, 1000, 6);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.append(sStr2, 1000, 6);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Append_test, append_std_str_1000_1000) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	std::string sStr2 = testLongString;
	bool b_sStr = false;	

	try {

		sStr1.append(sStr2, 1000, 1000);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.append(sStr2, 1000, 1000);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Replace_test, replace_str_1000_1000) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	bool b_sStr = false;	

	try {

		sStr1.replace(1000, 1000, testLongString);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.replace(1000, 1000, testLongString);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}




TEST (Replace_test, replace_str_3_1000) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	bool b_sStr = false;	

	try {

		sStr1.replace(3, 1000, testLongString);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.replace(3, 1000, testLongString);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}




TEST (Replace_test, replace_str_1000_3) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	bool b_sStr = false;	

	try {

		sStr1.replace(1000, 3, testLongString);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.replace(1000, 3, testLongString);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}

TEST (Replace_test, replace_str_3_3) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	bool b_sStr = false;	

	try {

		sStr1.replace(3, 3, testLongString);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.replace(3, 3, testLongString);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}




TEST (Replace_test, replace_std_str_1000_1000) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	std::string sStr2 = testLongString;
	bool b_sStr = false;	

	try {

		sStr1.replace(1000, 1000, sStr2);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.replace(1000, 1000, sStr2);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}




TEST (Replace_test, replace_std_str_3_1000) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	std::string sStr2 = testLongString;
	bool b_sStr = false;	

	try {

		sStr1.replace(3, 1000, sStr2);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.replace(3, 1000, sStr2);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}




TEST (Replace_test, replace_std_str_1000_3) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	std::string sStr2 = testLongString;
	bool b_sStr = false;	

	try {

		sStr1.replace(1000, 3, sStr2);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.replace(1000, 3, sStr2);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}


TEST (Replace_test, replace_std_str_3_3) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	std::string sStr2 = testLongString;
	bool b_sStr = false;	

	try {

		sStr1.replace(3, 3, sStr2);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.replace(3, 3, sStr2);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}


TEST (Substr_test, substr_1000_1000) {
	
	MyString myStr1 = testShortString, myStr2;
	std::string sStr1 = testShortString, sStr2;
	bool b_sStr = false;	

	try {

		sStr2 = sStr1.substr(1000, 1000);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr2 = myStr1.substr(1000, 1000);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr2.length(), myStr2.length());
	
	
	for(size_t i = 0; i < myStr2.length(); ++i) {
		ASSERT_EQ(sStr2[i], myStr2[i]);
	}
}


TEST (Substr_test, substr_1000_3) {
	
	MyString myStr1 = testShortString, myStr2;
	std::string sStr1 = testShortString, sStr2;
	bool b_sStr = false;	

	try {

		sStr2 = sStr1.substr(1000, 3);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr2 = myStr1.substr(1000, 3);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr2.length(), myStr2.length());
	
	for(size_t i = 0; i < myStr2.length(); ++i) {
		ASSERT_EQ(sStr2[i], myStr2[i]);
	}
}


TEST (Substr_test, substr_3_1000) {
	
	MyString myStr1 = testShortString, myStr2;
	std::string sStr1 = testShortString, sStr2;
	bool b_sStr = false;	

	try {

		sStr2 = sStr1.substr(3, 1000);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr2 = myStr1.substr(3, 1000);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr2.length(), myStr2.length());
	
	
	for(size_t i = 0; i < myStr2.length(); ++i) {
		ASSERT_EQ(sStr2[i], myStr2[i]);
	}
}


TEST (Substr_test, substr_3_3) {
	
	MyString myStr1 = testShortString, myStr2;
	std::string sStr1 = testShortString, sStr2;
	bool b_sStr = false;	

	try {

		sStr2 = sStr1.substr(3, 3);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr2 = myStr1.substr(3, 3);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr2.length(), myStr2.length());
	
	for(size_t i = 0; i < myStr2.length(); ++i) {
		ASSERT_EQ(sStr2[i], myStr2[i]);
	}
}


TEST (Substr_test, substr_1000) {
	
	MyString myStr1 = testShortString, myStr2;
	std::string sStr1 = testShortString, sStr2;
	bool b_sStr = false;	

	try {

		sStr2 = sStr1.substr(1000);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr2 = myStr1.substr(1000);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr2.length(), myStr2.length());
	
	for(size_t i = 0; i < myStr2.length(); ++i) {
		ASSERT_EQ(sStr2[i], myStr2[i]);
	}
}


TEST (Substr_test, substr_3) {
	
	MyString myStr1 = testShortString, myStr2;
	std::string sStr1 = testShortString, sStr2;
	bool b_sStr = false;	

	try {

		sStr2 = sStr1.substr(3);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr2 = myStr1.substr(3);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr2.length(), myStr2.length());
	
	for(size_t i = 0; i < myStr2.length(); ++i) {
		ASSERT_EQ(sStr2[i], myStr2[i]);
	}

}


TEST (Find_test, find_str_tay_short_0) {
	
	MyString myStr1 = testShortString;
	const char* toFind = "tay";
	std::string sStr1 = testShortString;
	long long int myPos = 0, sPos = 0; 
	
	myPos = myStr1.find(toFind);
	sPos = sStr1.find(toFind);

	ASSERT_EQ(myPos, sPos);
}




TEST (Find_test, find_str_tay_short_10) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	const char* toFind = "tay";
	long long int myPos = 0, sPos = 0; 
	
	myPos = myStr1.find(toFind, 10);
	sPos = sStr1.find(toFind, 10);

	ASSERT_EQ(myPos, sPos);
}


TEST (Find_test, find_str_tay_short_30) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	const char* toFind = "tay";
	long long int myPos = 0, sPos = 0; 
	
	myPos = myStr1.find(toFind, 30);
	sPos = sStr1.find(toFind, 30);

	ASSERT_EQ(myPos, sPos);
}



TEST (Find_test, find_str_lay_short_0) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	const char* toFind = "lay";
	long long int myPos = 0, sPos = 0; 
	
	myPos = myStr1.find(toFind);
	sPos = sStr1.find(toFind);

	ASSERT_EQ(myPos, sPos);
}




TEST (Find_test, find_str_lay_short_10) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	const char* toFind = "lay";
	long long int myPos = 0, sPos = 0; 
	
	myPos = myStr1.find(toFind, 10);
	sPos = sStr1.find(toFind, 10);

	ASSERT_EQ(myPos, sPos);
}


TEST (Find_test, find_str_lay_short_30) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	const char* toFind = "lay";
	long long int myPos = 0, sPos = 0; 
	
	myPos = myStr1.find(toFind, 30);
	sPos = sStr1.find(toFind, 30);

	ASSERT_EQ(myPos, sPos);
}


TEST (Find_test, find_std_str_tay_short_0) {
	
	MyString myStr1 = testShortString;
	std::string toFind = "tay";
	std::string sStr1 = testShortString;
	long long int myPos = 0, sPos = 0; 
	
	myPos = myStr1.find(toFind);
	sPos = sStr1.find(toFind);

	ASSERT_EQ(myPos, sPos);
}




TEST (Find_test, find_std_str_tay_short_10) {
	
	MyString myStr1 = testShortString;
	std::string toFind = "tay";
	std::string sStr1 = testShortString;
	long long int myPos = 0, sPos = 0; 
	
	myPos = myStr1.find(toFind, 10);
	sPos = sStr1.find(toFind, 10);

	ASSERT_EQ(myPos, sPos);
}


TEST (Find_test, find_std_str_tay_short_30) {
	
	MyString myStr1 = testShortString;
	std::string toFind = "tay";
	std::string sStr1 = testShortString;
	long long int myPos = 0, sPos = 0; 
	
	myPos = myStr1.find(toFind, 30);
	sPos = sStr1.find(toFind, 30);

	ASSERT_EQ(myPos, sPos);
}



TEST (Find_test, find_std_str_lay_short_0) {
	
	MyString myStr1 = testShortString;
	std::string toFind = "lay";
	std::string sStr1 = testShortString;
	long long int myPos = 0, sPos = 0; 
	
	myPos = myStr1.find(toFind);
	sPos = sStr1.find(toFind);

	ASSERT_EQ(myPos, sPos);
}




TEST (Find_test, find_std_str_lay_short_10) {
	
	MyString myStr1 = testShortString;
	std::string toFind = "lay";
	std::string sStr1 = testShortString;
	long long int myPos = 0, sPos = 0; 
	
	myPos = myStr1.find(toFind, 10);
	sPos = sStr1.find(toFind, 10);

	ASSERT_EQ(myPos, sPos);
}


TEST (Find_test, find_std_str_lay_short_30) {
	
	MyString myStr1 = testShortString;
	std::string toFind = "lay";
	std::string sStr1 = testShortString;
	long long int myPos = 0, sPos = 0; 
	
	myPos = myStr1.find(toFind, 30);
	sPos = sStr1.find(toFind, 30);

	ASSERT_EQ(myPos, sPos);
}

TEST (Integer_constructor_test, signed_long_long_int_47285623554) {
	
	char expected_output[] = "47285623554";
	
	long long int test = 47285623554;

	MyString myStr1 = test;


	ASSERT_EQ(strlen(expected_output), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}


TEST (Integer_constructor_test, signed_long_long_int_minus_47285623554) {
	
	char expected_output[] = "-47285623554";
	
	long long int test = -47285623554;

	MyString myStr1 = test;


	ASSERT_EQ(strlen(expected_output), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}

TEST (Integer_constructor_test, unsigned_long_long_int_735682375091) {
	
	char expected_output[] = "735682375091";
	
	unsigned long long int test = 735682375091;

	MyString myStr1 = test;


	ASSERT_EQ(strlen(expected_output), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}



TEST (Integer_constructor_test, signed_long_int_472856235) {
	
	char expected_output[] = "472856235";
	
	long int test = 472856235;

	MyString myStr1 = test;


	ASSERT_EQ(strlen(expected_output), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}


TEST (Integer_constructor_test, signed_long_int_minus_472856235) {
	
	char expected_output[] = "-472856235";
	
	long int test = -472856235;

	MyString myStr1 = test;


	ASSERT_EQ(strlen(expected_output), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}

TEST (Integer_constructor_test, unsigned_long_int_735682375) {
	
	char expected_output[] = "735682375";
	
	unsigned long int test = 735682375;

	MyString myStr1 = test;


	ASSERT_EQ(strlen(expected_output), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}



TEST (Integer_constructor_test, signed_int_4728562) {
	
	char expected_output[] = "4728562";
	
	int test = 4728562;

	MyString myStr1 = test;


	ASSERT_EQ(strlen(expected_output), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}


TEST (Integer_constructor_test, signed_int_minus_4728562) {
	
	char expected_output[] = "-4728562";
	
	int test = -4728562;

	MyString myStr1 = test;


	ASSERT_EQ(strlen(expected_output), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}

TEST (Integer_constructor_test, unsigned_int_7356823) {
	
	char expected_output[] = "7356823";
	
	unsigned int test = 7356823;

	MyString myStr1 = test;


	ASSERT_EQ(strlen(expected_output), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}



TEST (Integer_constructor_test, signed_short_4728) {
	
	char expected_output[] = "4728";
	
	short test = 4728;

	MyString myStr1 = test;


	ASSERT_EQ(strlen(expected_output), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}


TEST (Integer_constructor_test, signed_short_minus_4728562) {
	
	char expected_output[] = "-4728";
	
	int test = -4728;

	MyString myStr1 = test;


	ASSERT_EQ(strlen(expected_output), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}

TEST (Integer_constructor_test, unsigned_short_37356) {
	
	char expected_output[] = "37356";
	
	unsigned int test = 37356;

	MyString myStr1 = test;


	ASSERT_EQ(strlen(expected_output), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}


TEST (Float_constructor_test, long_double_3_1478862385) {
	
	long double test = 3.1478862385;
	std::string expected_output = std::to_string(test);

	MyString myStr1 = test;


	ASSERT_EQ(expected_output.length(), myStr1.length());
	

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}


TEST (Float_constructor_test, long_double_minus_3_1478862385) {
	
	long double test = -3.1478862385;

	std::string expected_output = std::to_string(test);
	MyString myStr1 = test;

	ASSERT_EQ(expected_output.length(), myStr1.length());
	

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}



TEST (Float_constructor_test, long_double_minus_888888888888888_8888888) {

	long double test = -888888888888888.8888888;

	std::string expected_output = std::to_string(test);
	MyString myStr1 = test;


	ASSERT_EQ(expected_output.length(), myStr1.length());
	

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}



TEST (Float_constructor_test, double_3_147886) {
	
	double test = 3.147886;
	std::string expected_output = std::to_string(test);
	MyString myStr1 = test;


	ASSERT_EQ(expected_output.length(), myStr1.length());
	

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}


TEST (Float_constructor_test, double_minus_3_147886) {
	
	double test = -3.147886;
	std::string expected_output = std::to_string(test);
	MyString myStr1 = test;


	ASSERT_EQ(expected_output.length(), myStr1.length());
	

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}



TEST (Float_constructor_test, double_111111111111111111111111_2222222222) {
	
	double test = 111111111111111111111111.2222222222;

	std::string expected_output = std::to_string(test);
	MyString myStr1 = test;


	ASSERT_EQ(expected_output.length(), myStr1.length());
	

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}



TEST (Float_constructor_test, double_3_1478) {
	
	float test = 3.1478;

	std::string expected_output = std::to_string(test);
	MyString myStr1 = test;


	ASSERT_EQ(expected_output.length(), myStr1.length());
	

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}


TEST (Float_constructor_test, float_minus_3_1478) {
	
	float test = -3.1478;

	std::string expected_output = std::to_string(test);
	MyString myStr1 = test;


	ASSERT_EQ(expected_output.length(), myStr1.length());
	

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}



TEST (Float_constructor_test, float_42) {
		
	float test = 42;

	std::string expected_output = std::to_string(test);
	MyString myStr1 = test;


	ASSERT_EQ(expected_output.length(), myStr1.length());
	

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], expected_output[i]);
	}
}




TEST (At_test, valid_idx) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	bool b_sStr = false;

	try {

		sStr1.at(2) = 'k';

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.at(2) = 'k';
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}

TEST (At_test, invalid_idx) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	bool b_sStr = false;

	try {

		sStr1.at(1000) = 'k';

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.at(1000) = 'k';
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}


TEST (IO_test, fstream_hello_world) {

	std::fstream test1;

	test1.open("test.input");

	MyString myStr1 = "Hello";
	std::string sStr1;

	test1 << myStr1;

	test1.seekg(0);

	test1 >> sStr1;

	ASSERT_EQ(sStr1.length(), myStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}

TEST (To_int_test, long_long_int_overflow) {

	MyString myStr1 = "11111111111111111111111111111111";
	long long int test = 0;
	bool bExc = false;
	try {
		test = myStr1.to_long_long_int();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}

TEST (To_int_test, long_long_int_invailid) {

	MyString myStr1 = "11111111111111a111111111111111111";
	long long int test = 0;
	bool bExc = false;
	try {
		test = myStr1.to_long_long_int();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}

TEST (To_int_test, long_long_int_vailid_positive) {

	long long expVal = 1111111;
	MyString myStr1 = expVal;
	long long int test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_long_long_int();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_EQ(expVal, test);
	ASSERT_FALSE(bExc);
}


TEST (To_int_test, long_long_int_vailid_negative) {

	long long expVal = -1111111;
	MyString myStr1 = expVal;
	long long int test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_long_long_int();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_EQ(expVal, test);
	ASSERT_FALSE(bExc);
}


TEST (To_int_test, int_overflow) {

	
	long long int val = INT_MAX + 4234;

	MyString myStr1 = val;
	int test = 0;
	bool bExc = false;
	try {
		test = myStr1.to_int();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}

TEST (To_int_test, int_invailid) {

	MyString myStr1 = "Hello world";
	int test = 0;
	bool bExc = false;
	try {
		test = myStr1.to_int();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}

TEST (To_int_test, int_vailid_positive) {

	long long int expVal = 2222222;
	MyString myStr1 = expVal;
	long long int test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_int();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_EQ(expVal, test);
	ASSERT_FALSE(bExc);
}


TEST (To_int_test, int_vailid_negative) {

	long long int expVal = -2222222;
	MyString myStr1 = expVal;
	long long int test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_int();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_EQ(expVal, test);
	ASSERT_FALSE(bExc);
}


TEST (To_int_test, short_overflow) {

	
	long long int val = SHORT_MAX + 4234;

	MyString myStr1 = val;
	short test = 0;
	bool bExc = false;
	try {
		test = myStr1.to_short();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}

TEST (To_int_test, short_invailid) {

	MyString myStr1 = "yegfhjaw562qd!";
	short test = 0;
	bool bExc = false;
	try {
		test = myStr1.to_short();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}

TEST (To_int_test, short_vailid_positive) {

	long long int expVal = 2222;
	MyString myStr1 = expVal;
	short test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_short();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_EQ(expVal, test);
	ASSERT_FALSE(bExc);
}


TEST (To_int_test, short_vailid_negative) {

	long long int expVal = -2222;
	MyString myStr1 = expVal;
	short test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_short();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_EQ(expVal, test);
	ASSERT_FALSE(bExc);
}


TEST (To_int_test, char_overflow) {

	
	long long int val = CHAR_MAX + 4234;

	MyString myStr1 = val;
	short test = 0;
	bool bExc = false;
	try {
		test = myStr1.to_char();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}

TEST (To_int_test, char_invailid) {

	MyString myStr1 = "yegfhjasfhsghw562qd!";
	short test = 0;
	bool bExc = false;
	try {
		test = myStr1.to_char();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}

TEST (To_int_test, char_vailid_positive) {

	long long int expVal = 127;
	MyString myStr1 = expVal;
	short test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_char();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_EQ(expVal, test);
	ASSERT_FALSE(bExc);
}


TEST (To_int_test, char_vailid_negative) {

	long long int expVal = -22;
	MyString myStr1 = expVal;
	char test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_char();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_EQ(expVal, test);
	ASSERT_FALSE(bExc);
}

TEST (To_int_test, unsigned_long_long_int_overflow) {

	MyString myStr1 = "11111111111111111111111111111111";
	unsigned long long int test = 0;
	bool bExc = false;
	try {
		test = myStr1.to_ulong_long_int();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}

TEST (To_int_test, unsigned_long_long_int_invailid) {

	MyString myStr1 = "11111111111111a111111111111111111";
	unsigned long long int test = 0;
	bool bExc = false;
	try {
		test = myStr1.to_ulong_long_int();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}

TEST (To_int_test, unsigned_long_long_int_vailid) {

	unsigned long long int expVal = 11111111111115;
	MyString myStr1 = expVal;
	long long int test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_ulong_long_int();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_EQ(expVal, test);
	ASSERT_FALSE(bExc);
}


TEST (To_int_test, unsigned_int_overflow) {

	MyString myStr1 = "1111111111111111111111111";
	unsigned int test = 0;
	bool bExc = false;
	try {
		test = myStr1.to_uint();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}

TEST (To_int_test, unsigned_int_invailid) {

	MyString myStr1 = "1111111a11";
	unsigned int test = 0;
	bool bExc = false;
	try {
		test = myStr1.to_uint();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}

TEST (To_int_test, unsigned_int_vailid) {

	unsigned long long int expVal = 111111115;
	MyString myStr1 = expVal;
	unsigned int test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_uint();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_EQ(expVal, test);
	ASSERT_FALSE(bExc);
}


TEST (To_int_test, unsigned_short_overflow) {

	MyString myStr1 = "11111111111111";
	unsigned short test = 0;
	bool bExc = false;
	try {
		test = myStr1.to_ushort();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}

TEST (To_int_test, unsigned_short_invailid) {

	MyString myStr1 = "11b1a11";
	unsigned short test = 0;
	bool bExc = false;
	try {
		test = myStr1.to_ushort();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}

TEST (To_int_test, unsigned_short_vailid) {

	unsigned long long int expVal = 51115;
	MyString myStr1 = expVal;
	unsigned short test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_ushort();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_EQ(expVal, test);
	ASSERT_FALSE(bExc);
}


TEST (To_int_test, unsigned_char_overflow) {

	MyString myStr1 = "11111111111111";
	unsigned char test = 0;
	bool bExc = false;
	try {
		test = myStr1.to_uchar();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}

TEST (To_int_test, unsigned_char_invailid) {

	MyString myStr1 = "11b1a11";
	unsigned char test = 0;
	bool bExc = false;
	try {
		test = myStr1.to_uchar();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}

TEST (To_int_test, unsigned_char_vailid) {

	unsigned long long int expVal = 255;
	MyString myStr1 = expVal;
	unsigned char test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_uchar();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_EQ(expVal, test);
	ASSERT_FALSE(bExc);
}


TEST (To_float_test, long_double_ovflw) {

	long double expVal = HUGE_VALL+ 1028942;
	MyString myStr1 = expVal;
	long double test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_long_double();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}

TEST (To_float_test, long_double_unflw) {

	long double expVal = -HUGE_VALL- 1028942;
	MyString myStr1 = expVal;
	long double test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_long_double();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}


TEST (To_float_test, long_double_valid_low) {

	long double expVal = 0.01000187526;
	MyString myStr1 = expVal;
	long double test1 = 1;
	bool bMyExc = false;
	try {
		test1 = myStr1.to_long_double();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bMyExc = true;
	}

	std::string sStr1 = std::to_string(expVal);
	long double test2 = 1;
	bool bSExc = false;
	try {
		test2 = stold(sStr1, nullptr);
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bSExc = true;
	}

	ASSERT_EQ(bMyExc, bSExc);
	ASSERT_EQ(test1, test2);
}

TEST (To_float_test, long_double_invailid) {

	MyString myStr1 = testShortString;
	long double test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_long_double();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}

TEST (To_float_test, long_double_valid_high) {

	long double expVal = 1000187526287568723.232872895;
	MyString myStr1 = expVal;
	long double test1 = 1;
	bool bMyExc = false;
	try {
		test1 = myStr1.to_long_double();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bMyExc = true;
	}

	std::string sStr1 = std::to_string(expVal);
	long double test2 = 1;
	bool bSExc = false;
	try {
		test2 = stold(sStr1, nullptr);
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bSExc = true;
	}

	ASSERT_EQ(bMyExc, bSExc);
	ASSERT_EQ(test1, test2);
}



TEST (To_float_test, double_ovflw) {

	double expVal = HUGE_VAL + 1028942;
	MyString myStr1 = expVal;
	double test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_double();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}

TEST (To_float_test, double_unflw) {

	double expVal = -HUGE_VAL- 1028942;
	MyString myStr1 = expVal;
	double test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_double();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}


TEST (To_float_test, double_invailid) {

	MyString myStr1 = testShortString;
	long double test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_double();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}



TEST (To_float_test, double_valid_low) {

	double expVal = 0.01000187526;
	MyString myStr1 = expVal;
	double test1 = 1;
	bool bMyExc = false;
	try {
		test1 = myStr1.to_double();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bMyExc = true;
	}

	std::string sStr1 = std::to_string(expVal);
	double test2 = 1;
	bool bSExc = false;
	try {
		test2 = stold(sStr1, nullptr);
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bSExc = true;
	}

	ASSERT_EQ(test1, test2);
	ASSERT_EQ(bMyExc, bSExc);
}


TEST (To_float_test, double_valid_high) {

	double expVal = 1000187526723.232872895;
	MyString myStr1 = expVal;
	double test1 = 1;
	bool bMyExc = false;
	try {
		test1 = myStr1.to_double();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bMyExc = true;
	}

	std::string sStr1 = std::to_string(expVal);
	double test2 = 1;
	bool bSExc = false;
	try {
		test2 = stold(sStr1, nullptr);
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bSExc = true;
	}
	
	ASSERT_EQ(bMyExc, bSExc);
	ASSERT_EQ(test1, test2);
}


TEST (To_float_test, float_ovflw) {

	float expVal = HUGE_VALF + 1028942;
	MyString myStr1 = expVal;
	float test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_float();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}

TEST (To_float_test, float_unflw) {

	float expVal = -HUGE_VALF- 1028942;
	MyString myStr1 = expVal;
	float test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_float();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}



TEST (To_float_test, float_invailid) {

	MyString myStr1 = testShortString;
	float test = 1;
	bool bExc = false;
	try {
		test = myStr1.to_float();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bExc = true;
	}

	ASSERT_TRUE(bExc);
}


TEST (To_float_test, float_valid_low) {

	float expVal = 0.01000187526;
	MyString myStr1 = expVal;
	float test1 = 1;
	bool bMyExc = false;
	try {
		test1 = myStr1.to_float();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bMyExc = true;
	}

	std::string sStr1 = std::to_string(expVal);
	float test2 = 1;
	bool bSExc = false;
	try {
		test2 = stold(sStr1, nullptr);
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bSExc = true;
	}

	ASSERT_EQ(test1, test2);
	ASSERT_EQ(bMyExc, bSExc);
}


TEST (To_float_test, float_valid_high) {

	float expVal = 1000187526723.232872895;
	MyString myStr1 = expVal;
	float test1 = 1;
	bool bMyExc = false;
	try {
		test1 = myStr1.to_float();
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bMyExc = true;
	}

	std::string sStr1 = std::to_string(expVal);
	float test2 = 1;
	bool bSExc = false;
	try {
		test2 = stold(sStr1, nullptr);
	} catch (MyException& e) {
		std::cout << e.what() << std::endl;
		bSExc = true;
	}
	
	ASSERT_EQ(bMyExc, bSExc);
	ASSERT_EQ(test1, test2);
}

TEST (Move_semantics_test, constructor) {
	
	MyString myStr1 = testLongString;
	MyString myStr2 = testLongString;
	MyString myStr3 = std::move(myStr2);


	ASSERT_EQ(myStr2.length(), 0);
	ASSERT_EQ(myStr3.length(), myStr1.length());
	

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], myStr3[i]);
	}
}

TEST (Move_semantics_test, assignment) {
	
	MyString myStr1 = testLongString;
	MyString myStr2 = testLongString;
	MyString myStr3;
	myStr3 = std::move(myStr2);


	ASSERT_EQ(myStr2.length(), 0);
	ASSERT_EQ(myStr3.length(), myStr1.length());
	

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], myStr3[i]);
	}
}

TEST (Iterators_test, insert_iter_ch_valid_iter) {
	

	MyString myStr1 = testShortString;
	MyString myStr2 = "Stay _Hungry. Stay Foolish.";
	auto iter = MyConstIterator(myStr1.data()+5);
	
	bool b_myStr = false;

	try {

		myStr1.insert(iter, '_');

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_FALSE(b_myStr);

	ASSERT_EQ(myStr2.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], myStr2[i]);
	}
}


TEST (Iterators_test, insert_iter_ch_invalid_iter) {
	
	MyString myStr1 = testShortString;
	MyString myStr2 = "Stay Hungry. Stay Foolish.";
	auto iter = MyConstIterator(myStr1.data()-5);
	
	
	bool b_myStr = false;

	try {

		myStr1.insert(iter, '_');

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_TRUE(b_myStr);

	ASSERT_EQ(myStr1.length(), myStr2.length());
	

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], myStr2[i]);
	}
}


TEST (Iterators_test, insert_iters_vailid) {
	
	MyString myStr1 = testShortString;
	MyString myStr2 = "Stay Hungry.";
	MyString myStr3 = testShortString;
	myStr3.insert(12, "Stay Hungry.");
	auto iter = MyConstIterator(myStr1.data()+12);
	
	bool b_myStr = false;

	try {

		myStr1.insert(iter, myStr2.begin(),myStr2.end());

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_FALSE(b_myStr);

	ASSERT_EQ(myStr3.length(), myStr1.length());
	

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], myStr3[i]);
	}
}


TEST (Iterators_test, insert_iters_invailid) {
	
	MyString myStr1 = testShortString;
	MyString myStr2 = "Stay Hungry.";
	MyString myStr3 = "Stay Hungry. Stay Foolish.";
	auto iter = MyConstIterator(myStr1.data()-12);
	
	bool b_myStr = false;

	try {

		myStr1.insert(iter, myStr2.begin(),myStr2.end());

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_TRUE(b_myStr);

	ASSERT_EQ(myStr3.length(), myStr1.length());
	

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], myStr3[i]);
	}
}



TEST (Iterators_test, insert_iter_and_list_vailid) {
	
	MyString myStr1 = testShortString;
	std::initializer_list<const char> list = {'S', 't', 'a', 'y',' ', 'H', 'u', 'n', 'g', 'r', 'y', '.'};
	MyString myStr2 = testShortString;
	myStr2.insert(12, "Stay Hungry.");
	auto iter = MyConstIterator(myStr1.data()+12);
	
	bool b_myStr = false;

	try {

		myStr1.insert(iter, list);

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_FALSE(b_myStr);

	ASSERT_EQ(myStr2.length(), myStr1.length());
	

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], myStr2[i]);
	}
}


TEST (Iterators_test, insert_iter_and_list_invailid) {
	
	MyString myStr1 = testShortString;
	std::initializer_list<const char> list = {'S', 't', 'a', 'y',' ', 'H', 'u', 'n', 'g', 'r', 'y', '.'};
	MyString myStr2 = "Stay Hungry. Stay Foolish.";
	auto iter = MyConstIterator(myStr1.data()-12);
	
	bool b_myStr = false;

	try {

		myStr1.insert(iter, list);

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_TRUE(b_myStr);

	ASSERT_EQ(myStr2.length(), myStr1.length());
	

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(myStr1[i], myStr2[i]);
	}
}


TEST (Iterators_test, erase_iter_short_5_5) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	
	bool b_sStr = false;	

	try {

		sStr1.erase(5, 5);

	} catch(std::exception) {

		b_sStr = true;
	}

	bool b_myStr = false;
	for(auto iter = MyConstIterator(myStr1.data()+5); iter != MyConstIterator(myStr1.data()+11); ++iter) 
		std::cout << *iter;
	std::cout << std::endl;	

	try {

		myStr1.erase(MyConstIterator(myStr1.data()+5), MyConstIterator(myStr1.data()+10));

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}


TEST (Iterators_test, erase_iter_short_5_100) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	
	bool b_sStr = false;	

	try {

		sStr1.erase(5, 100);

	} catch(std::exception) {

		b_sStr = true;
	}

	bool b_myStr = false;	

	try {

		myStr1.erase(MyConstIterator(myStr1.data()+5), MyConstIterator(myStr1.data()+106));

	} catch(MyException) {

		b_myStr = true;
	}

	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}





TEST (Iterators_test, erase_short_100_5) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	
	bool b_sStr = false;	

	try {

		sStr1.erase(100, 5);

	} catch(std::exception) {

		b_sStr = true;
	}

	bool b_myStr = false;	
	
	try {

		myStr1.erase(MyConstIterator(myStr1.data()+100), MyConstIterator(myStr1.data()+5));

	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}



TEST (Iterators_test, replace_str_1000_1000) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	bool b_sStr = false;	

	try {

		sStr1.replace(1000, 1000, testLongString);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.replace(MyConstIterator(myStr1.data()+1000) , MyConstIterator(myStr1.data()+2000), testLongString);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}




TEST (Iterators_test, replace_str_3_1000) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	bool b_sStr = false;	

	try {

		sStr1.replace(3, 1000, testLongString);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.replace(MyConstIterator(myStr1.data()+3) , MyConstIterator(myStr1.data()+1003), testLongString);

		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}




TEST (Iterators_test, replace_str_1000_3) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	bool b_sStr = false;	

	try {

		sStr1.replace(1000, 3, testLongString);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.replace(MyConstIterator(myStr1.data()+1000) , MyConstIterator(myStr1.data()+1003), testLongString);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());
	
	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}

TEST (Iterators_test, replace_str_3_3) {
	
	MyString myStr1 = testShortString;
	std::string sStr1 = testShortString;
	bool b_sStr = false;	

	try {

		sStr1.replace(3, 3, testLongString);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr1.replace(MyConstIterator(myStr1.data()+3) , MyConstIterator(myStr1.data()+6), testLongString);
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr1.length(), myStr1.length());

	for(size_t i = 0; i < myStr1.length(); ++i) {
		ASSERT_EQ(sStr1[i], myStr1[i]);
	}
}


TEST (Iterators_test, substr_1000_1000) {
	
	MyString myStr1 = testShortString, myStr2;
	std::string sStr1 = testShortString, sStr2;
	bool b_sStr = false;	

	try {

		sStr2 = sStr1.substr(1000, 1000);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr2 = myStr1.substr(MyConstIterator(myStr1.data()+1000), MyConstIterator(myStr1.data()+2000));
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr2.length(), myStr2.length());
	
	
	for(size_t i = 0; i < myStr2.length(); ++i) {
		ASSERT_EQ(sStr2[i], myStr2[i]);
	}
}


TEST (Iterators_test, substr_1000_3) {
	
	MyString myStr1 = testShortString, myStr2;
	std::string sStr1 = testShortString, sStr2;
	bool b_sStr = false;	

	try {

		sStr2 = sStr1.substr(1000, 3);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr2 = myStr1.substr(MyConstIterator(myStr1.data()+1000), MyConstIterator(myStr1.data()+1003));
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr2.length(), myStr2.length());
	
	for(size_t i = 0; i < myStr2.length(); ++i) {
		ASSERT_EQ(sStr2[i], myStr2[i]);
	}
}


TEST (Iterators_test, substr_3_1000) {
	
	MyString myStr1 = testShortString, myStr2;
	std::string sStr1 = testShortString, sStr2;
	bool b_sStr = false;	

	try {

		sStr2 = sStr1.substr(3, 1000);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr2 = myStr1.substr(MyConstIterator(myStr1.data()+3), MyConstIterator(myStr1.data()+1003));
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr2.length(), myStr2.length());
	
	
	for(size_t i = 0; i < myStr2.length(); ++i) {
		ASSERT_EQ(sStr2[i], myStr2[i]);
	}
}


TEST (Iterators_test, substr_3_3) {
	
	MyString myStr1 = testShortString, myStr2;
	std::string sStr1 = testShortString, sStr2;
	bool b_sStr = false;	

	try {

		sStr2 = sStr1.substr(3, 3);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr2 = myStr1.substr(MyConstIterator(myStr1.data()+3), MyConstIterator(myStr1.data()+6));
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr2.length(), myStr2.length());
	
	for(size_t i = 0; i < myStr2.length(); ++i) {
		ASSERT_EQ(sStr2[i], myStr2[i]);
	}
}


TEST (Iterators_test, substr_1000) {
	
	MyString myStr1 = testShortString, myStr2;
	std::string sStr1 = testShortString, sStr2;
	bool b_sStr = false;	

	try {

		sStr2 = sStr1.substr(1000);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr2 = myStr1.substr(MyConstIterator(myStr1.data()+1000));
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr2.length(), myStr2.length());
	
	for(size_t i = 0; i < myStr2.length(); ++i) {
		ASSERT_EQ(sStr2[i], myStr2[i]);
	}
}


TEST (Iterators_test, substr_3) {
	
	MyString myStr1 = testShortString, myStr2;
	std::string sStr1 = testShortString, sStr2;
	bool b_sStr = false;	

	try {

		sStr2 = sStr1.substr(3);

	} catch(std::exception) {

		b_sStr = true;
	}


	bool b_myStr = false;	
	
	try {

		myStr2 = myStr1.substr(MyConstIterator(myStr1.data()+3));
		
	} catch(MyException) {

		b_myStr = true;
	}


	ASSERT_EQ(b_sStr, b_myStr);

	ASSERT_EQ(sStr2.length(), myStr2.length());
	
	for(size_t i = 0; i < myStr2.length(); ++i) {
		ASSERT_EQ(sStr2[i], myStr2[i]);
	}

}

TEST (Iterators_test, find_str_tay_short_0) {
	
	
	MyString myStr1 = testShortString;
	MyString myStr2 = testShortString;
	std::string toFind = "tay";
	long long int myPos1 = 0, myPos2 = 0; 
	
	myPos1 = myStr1.find(toFind, myStr1.cbegin());
	myPos2 = myStr2.find(toFind);

	ASSERT_EQ(myPos1, myPos2);
}




TEST (Iterators_test, find_str_tay_short_10) {
	
	
	MyString myStr1 = testShortString;
	MyString myStr2 = testShortString;
	std::string toFind = "tay";
	long long int myPos1 = 0, myPos2 = 0; 
	
	myPos1 = myStr1.find(toFind, MyConstIterator(myStr1.data()+10));
	myPos2 = myStr2.find(toFind, 10);

	ASSERT_EQ(myPos1, myPos2);
}


TEST (Iterators_test, find_str_tay_short_30) {
	
	
	MyString myStr1 = testShortString;
	MyString myStr2 = testShortString;
	std::string toFind = "tay";
	long long int myPos1 = 0, myPos2 = 0; 
	
	myPos1 = myStr1.find(toFind, MyConstIterator(myStr1.data()+30));
	myPos2 = myStr2.find(toFind, 30);

	ASSERT_EQ(myPos1, myPos2);
}



TEST (Iterators_test, find_str_lay_short_0) {
	
	MyString myStr1 = testShortString;
	MyString myStr2 = testShortString;
	std::string toFind = "lay";
	long long int myPos1 = 0, myPos2 = 0; 
	
	myPos1 = myStr1.find(toFind, myStr1.cbegin());
	myPos2 = myStr2.find(toFind);

	ASSERT_EQ(myPos1, myPos2);
}




TEST (Iterators_test, find_str_lay_short_10) {
	
	MyString myStr1 = testShortString;
	MyString myStr2 = testShortString;
	std::string toFind = "lay";
	long long int myPos1 = 0, myPos2 = 0; 
	
	myPos1 = myStr1.find(toFind, MyConstIterator(myStr1.data()+10));
	myPos2 = myStr2.find(toFind, 10);

	ASSERT_EQ(myPos1, myPos2);
}


TEST (Iterators_test, find_str_lay_short_30) {
	
	MyString myStr1 = testShortString;
	MyString myStr2 = testShortString;
	std::string toFind = "lay";
	long long int myPos1 = 0, myPos2 = 0; 
	
	myPos1 = myStr1.find(toFind, MyConstIterator(myStr1.data()+30));
	myPos2 = myStr2.find(toFind, 30);

	ASSERT_EQ(myPos1, myPos2);
}


TEST (Iterators_test, find_std_str_tay_short_0) {
	
	MyString myStr1 = testShortString;
	std::string toFind = "tay";
	std::string sStr1 = testShortString;
	long long int myPos = 0, sPos = 0; 
	
	myPos = myStr1.find(toFind);
	sPos = sStr1.find(toFind);

	ASSERT_EQ(myPos, sPos);
}




TEST (Iterators_test, find_std_str_tay_short_10) {
	
	MyString myStr1 = testShortString;
	std::string toFind = "tay";
	std::string sStr1 = testShortString;
	long long int myPos = 0, sPos = 0; 
	
	myPos = myStr1.find(toFind, 10);
	sPos = sStr1.find(toFind, 10);

	ASSERT_EQ(myPos, sPos);
}


TEST (Iterators_test, find_std_str_tay_short_30) {
	
	MyString myStr1 = testShortString;
	std::string toFind = "tay";
	std::string sStr1 = testShortString;
	long long int myPos = 0, sPos = 0; 
	
	myPos = myStr1.find(toFind, 30);
	sPos = sStr1.find(toFind, 30);

	ASSERT_EQ(myPos, sPos);
}



TEST (Iterators_test, find_std_str_lay_short_0) {
	
	MyString myStr1 = testShortString;
	std::string toFind = "lay";
	std::string sStr1 = testShortString;
	long long int myPos = 0, sPos = 0; 
	
	myPos = myStr1.find(toFind);
	sPos = sStr1.find(toFind);

	ASSERT_EQ(myPos, sPos);
}




TEST (Iterators_test, find_std_str_lay_short_10) {
	
	MyString myStr1 = testShortString;
	std::string toFind = "lay";
	std::string sStr1 = testShortString;
	long long int myPos = 0, sPos = 0; 
	
	myPos = myStr1.find(toFind, 10);
	sPos = sStr1.find(toFind, 10);

	ASSERT_EQ(myPos, sPos);
}


TEST (Iterators_test, find_std_str_lay_short_30) {
	
	MyString myStr1 = testShortString;
	std::string toFind = "lay";
	std::string sStr1 = testShortString;
	long long int myPos = 0, sPos = 0; 
	
	myPos = myStr1.find(toFind, 30);
	sPos = sStr1.find(toFind, 30);

	ASSERT_EQ(myPos, sPos);
}

int main (int argc, char*argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
