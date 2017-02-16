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
	BigInteger(std::string line);
	BigInteger(int num);
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

	void init(std::string x);

	std::uint8_t getDigit(unsigned int position) const;
	void setDigit(unsigned int position, std::uint8_t digit);
	void checkSizeReserved(unsigned int position);

	void copyArray(const BigInteger &rhs);
	void fillArray();
};

#endif
