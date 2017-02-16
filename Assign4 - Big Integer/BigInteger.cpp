#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>

#include "BigInteger.hpp"


// ------------------------------------------------------------------
//
// Default Constructor
//
// ------------------------------------------------------------------
BigInteger::BigInteger() :
	m_sizeReserved(4),
	m_digitCount(0)
{
	m_number = new uint8_t[m_sizeReserved];
	fillArray();
}

// ------------------------------------------------------------------
//
// Overloaded Constructor for strings.
//
// ------------------------------------------------------------------
BigInteger::BigInteger(std::string line) :
	m_sizeReserved(4)
{
	init(line);
}

// ------------------------------------------------------------------
//
// Overloaded Constructor for int.
//
// ------------------------------------------------------------------
BigInteger::BigInteger(int num) :
	m_sizeReserved(4)
{
	std::string temp = std::to_string(num);
	init(temp);
}

BigInteger BigInteger::add(const BigInteger& rhs)
{
	//std::cout << "add\n";
	BigInteger result;
	unsigned int length = (this->m_digitCount > rhs.m_digitCount) ? this->m_digitCount : rhs.m_digitCount;

	int carry = 0;
	for (unsigned int digit = 0; digit < length; digit++)
	{
		int v1 = this->getDigit(digit);
		int v2 = rhs.getDigit(digit);
		int sum = v1 + v2 + carry;
		int single = sum % 10;
		carry = ((sum - single) > 0) ? (sum - single) / 10 : 0;

		result.setDigit(digit, single);
	}
	if (carry > 0)
	{
		result.setDigit(length, carry);
	}

	return result;
}

BigInteger BigInteger::multiply(const BigInteger& rhs)
{
	BigInteger result;
	const BigInteger& b = (this->m_digitCount < rhs.m_digitCount) ? *this : rhs;
	const BigInteger& t = (this->m_digitCount < rhs.m_digitCount) ? rhs : *this;

	for (unsigned int bDigit = 0; bDigit < b.m_digitCount; bDigit++)
	{
		BigInteger temp(0);
		int v1 = b.getDigit(bDigit);
		int carry = 0;
		for (unsigned int tDigit = 0; tDigit < t.m_digitCount; tDigit++)
		{
			int v2 = t.getDigit(tDigit);
			int sum = v1 * v2 + carry;
			int single = sum % 10;
			carry = ((sum - single) > 0) ? (sum - single) / 10 : 0;

			temp.setDigit(bDigit + tDigit, single);
		}
		if (carry > 0)
		{
			temp.setDigit(bDigit + t.m_digitCount, carry);
		}
		BigInteger temp2 = result.add(temp);
		result = temp2;
	}

	return result;
}

void BigInteger::display()
{
	for (unsigned int digit = m_digitCount; digit > 0; digit--)
	{
		std::cout << static_cast<int>(m_number[digit - 1]);
	}
}

// ------------------------------------------------------------------
//
// Copy Constructor
//
// ------------------------------------------------------------------
BigInteger::BigInteger(const BigInteger &rhs)
{
	copyArray(rhs);
}

// ------------------------------------------------------------------
//
// Assignment operator overload
//
// ------------------------------------------------------------------
BigInteger& BigInteger::operator=(const BigInteger &rhs)
{
	delete[] this->m_number;
	copyArray(rhs);
	return *this;
}

// ------------------------------------------------------------------
//
// Deconstructor
//
// ------------------------------------------------------------------
BigInteger::~BigInteger()
{
	if (m_number != nullptr) {
		delete[]m_number;
	}
}

// ------------------------------------------------------------------
//
// Initializes the BigInteger object using a string. Only used by overloaded constructors.
//
// ------------------------------------------------------------------
void BigInteger::init(std::string x) {
	m_digitCount = x.length();
	if (m_digitCount > m_sizeReserved) {
		checkSizeReserved(m_digitCount);
	}

	m_number = new uint8_t[m_sizeReserved];
	for (unsigned int i = 0; i < m_digitCount; i++) {
		if (x.length() > 0) {
			m_number[i] = x.back() - '0';
			x.pop_back();
		}
	}
	if (m_digitCount != m_sizeReserved) {
		fillArray();
	}
}

// ------------------------------------------------------------------
//
// Returns the digit as the specified positon.  If the position is greater
// that the number representation, a 0 is returned.
//
// ------------------------------------------------------------------
std::uint8_t BigInteger::getDigit(unsigned int position) const
{
	if (position < m_digitCount)
	{
		return m_number[position];
	}

	return 0;
}

// ------------------------------------------------------------------
//
// set digit
//
// ------------------------------------------------------------------
void BigInteger::setDigit(unsigned int position, std::uint8_t digit) {
	if (position >= m_sizeReserved) {

		checkSizeReserved(position);

		uint8_t *ptr_number = m_number;
		m_number = new uint8_t[m_sizeReserved];

		for (int i = 0; i < m_sizeReserved; i++) {
			m_number[i] = ptr_number[i];
		}
		fillArray();
	}
	m_number[position] = digit;
	m_digitCount = position + 1;
}

// ------------------------------------------------------------------
//
// Increases the size reserved until it is large enough to contain the position value.
//
// ------------------------------------------------------------------
void BigInteger::checkSizeReserved(unsigned int value) {
	while (value >= m_sizeReserved) {
		m_sizeReserved *= 2;
	}
}

// ------------------------------------------------------------------
//
// Copy the values on the right object to the left object.
//
// ------------------------------------------------------------------
void BigInteger::copyArray(const BigInteger &rhs)
{
	m_sizeReserved = rhs.m_sizeReserved;
	m_digitCount = rhs.m_digitCount;

	m_number = new uint8_t[m_sizeReserved];
	for (int i = 0; i < m_sizeReserved; i++) {
		m_number[i] = rhs.m_number[i];
	}
}

// ------------------------------------------------------------------
//
// Fills an array with zeros.
//
// ------------------------------------------------------------------
void BigInteger::fillArray() {
	for (int i = m_digitCount; i < m_sizeReserved; i++) {
		m_number[i] = 0;
	}
}