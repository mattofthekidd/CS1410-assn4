#include <iostream>
#include <algorithm>
#include <cmath>

#include "BigInteger.hpp"

BigInteger::BigInteger() :
	m_number(new uint8_t[4]{0, 0, 0 ,0}),
	m_digitCount(0),
	m_sizeReserved(4)
{
	//m_number = 0;
}

BigInteger::BigInteger(int num) :
	m_sizeReserved(4)
{
	auto count = findDigitCount(num);
	m_number = new uint8_t[m_digitCount];
	for (unsigned int i = 0; i < count - 1; i++) {
		m_number[i] = (num % 10);
		num /= 10;
	}
}

BigInteger::BigInteger(std::string line) :
	m_digitCount(0),
	m_sizeReserved(4)
{

}

unsigned int BigInteger::getSizeReserved()
{
	return m_sizeReserved;
}

BigInteger BigInteger::add(const BigInteger& rhs)
{
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

		//result.setDigit(digit, single);
	}
	if (carry > 0)
	{
		//result.setDigit(length, carry);
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

			//temp.setDigit(bDigit + tDigit, single);
		}
		if (carry > 0)
		{
			//temp.setDigit(bDigit + t.m_digitCount, carry);
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

BigInteger::BigInteger(const BigInteger &rhs)
{
	copyArray(*this, rhs);
}

BigInteger& BigInteger::operator=(const BigInteger &rhs)
{
	// TODO: insert return statement here
}

BigInteger::~BigInteger()
{
	if (m_number != nullptr) {
		delete[]m_number;
		m_number = nullptr;
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
	if (position >= getSizeReserved()) {
		incSizeReserved(position);
	}
}

// ------------------------------------------------------------------
//
//
//
// ------------------------------------------------------------------
void BigInteger::incSizeReserved(unsigned int position) {
	while (position >= getSizeReserved()) {
		m_sizeReserved *= 2;
	}
}

void BigInteger::copyArray(BigInteger &lhs, const BigInteger &rhs)
{
	lhs.m_sizeReserved = rhs.m_sizeReserved;
	lhs.m_digitCount = rhs.m_digitCount;

	lhs.m_number = new uint8_t[m_sizeReserved];
	for (int i = 0; i < m_sizeReserved; i++) {
		lhs.m_number[0] = (rhs.m_number[0]);
	}
}

template <typename T>
unsigned int BigInteger::findDigitCount(T num) {
	unsigned int size = 0;
	while (num != 0) {
		num /= 10;
		size++;
		if (m_sizeReserved == size) {
			incSizeReserved();
		}
	}
	m_digitCount = size;
	return size;
}

