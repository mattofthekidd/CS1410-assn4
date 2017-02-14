#ifndef _BIGINTEGER_HPP_
#define _BIGINTEGER_HPP_

#include <cstdint>
#include <iostream>
#include <string>

class TestCases;

class BigInteger
{
public:
	BigInteger();
	BigInteger(int num);
	BigInteger(std::string line);
	unsigned int getSizeReserved();
	BigInteger add(const BigInteger& rhs);
	BigInteger multiply(const BigInteger& rhs);
	void display();

	//copy constructor
	BigInteger(const BigInteger &rhs);

	//assignment operator
	BigInteger& operator=(const BigInteger &rhs);

	//deconstructor
	~BigInteger();

	friend TestCases; // TODO Have students do this first thing

private:
	std::uint8_t* m_number;		// Internal representation of the number.
	unsigned int m_sizeReserved;	// Total size of the allocated space used to internally store the number
	unsigned int m_digitCount;	// How many digits are in the number.

	std::uint8_t getDigit(unsigned int position) const;
	void setDigit(unsigned int position, std::uint8_t digit);
	void checkSizeReserved(unsigned int position);
	template <typename T>
	unsigned int findDigitCount(T num);

	void copyArray(const BigInteger &rhs);
	void fillArray();

};

#endif
