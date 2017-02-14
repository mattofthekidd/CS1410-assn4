#include <iostream>
#include <algorithm>
#include <utility>
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
	m_number = new uint8_t[getSizeReserved()];
	for (unsigned int i = 0; i < count; i++) {
		m_number[i] = (num % 10);
		num /= 10;
	}
	if (count != getSizeReserved()) {
		fillArray();
	}
	std::cout << "int constructor: " << m_digitCount << ", " << m_sizeReserved << std::endl;
}

BigInteger::BigInteger(std::string line) :
	m_digitCount(line.length()),
	m_sizeReserved(4)
{
	if (m_digitCount > getSizeReserved()) {
		checkSizeReserved(m_digitCount);
	}

	m_number = new uint8_t[getSizeReserved()];
	for (unsigned int i = 0; i < m_digitCount; i++) {
		if (line.length() > 0) {
			m_number[i] = line.back() - '0';
			line.pop_back();
		}
	}
	if (m_digitCount != getSizeReserved()) {
		fillArray();
	}
	std::cout << "string constructor: " << m_digitCount << ", " << m_sizeReserved << std::endl;
}

unsigned int BigInteger::getSizeReserved()
{
	return m_sizeReserved;
}

BigInteger BigInteger::add(const BigInteger& rhs)
{
	std::cout << "add\n";
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

//copy constructor
BigInteger::BigInteger(const BigInteger &rhs)
{
	std::cout << "copy constructor: " << rhs.m_sizeReserved << ", " << rhs.m_digitCount << std::endl;
	copyArray(rhs);

}

//assignment operator
BigInteger& BigInteger::operator=(const BigInteger &rhs)
{
	std::cout << "assignment\n";
	delete[] this->m_number;
	copyArray(rhs);
	return *this;
}

BigInteger::~BigInteger()
{
	if (m_number != nullptr) {

		//delete[]m_number;

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
	//if pos > size resereved
	if (position >= getSizeReserved()) {
		int oldSize = m_sizeReserved;
		checkSizeReserved(position);
		int newSize = m_sizeReserved;
		BigInteger *ptr = this;
		m_number = new uint8_t[newSize];
		for (int i = 0; i < oldSize; i++) {
			std::cout << "setDigit: " << ptr->m_number[i] << std::endl;
			m_number[i] = ptr->m_number[i];
		}
		m_number[position] = digit;

	}
	else {
		m_number[position] = digit;
		std::cout << "setDigit, else: " << m_number[position]-1 << ", " << m_digitCount << ", " << m_sizeReserved << std::endl;
	}
	m_digitCount++;
	

}

// ------------------------------------------------------------------
//
//
//
// ------------------------------------------------------------------
void BigInteger::checkSizeReserved(unsigned int value) {
		while (value >= getSizeReserved()) {
			m_sizeReserved *= 2;
		}
}

void BigInteger::copyArray(const BigInteger &rhs)
{
	//std::cout << "inside copyArray: " << rhs.m_sizeReserved << ", " << rhs.m_digitCount << std::endl;
	m_sizeReserved = rhs.m_sizeReserved;
	m_digitCount = rhs.m_digitCount;

	m_number = new uint8_t[m_sizeReserved];
	for (int i = 0; i < m_digitCount; i++) {
		m_number[i] = rhs.m_number[i];
		std::cout << "for loop in copyArray: " << rhs.m_number[i]-1 << std::endl;
	}
}

template <typename T>
unsigned int BigInteger::findDigitCount(T num) {
	unsigned int size = 0;
	while (num != 0) {
		num /= 10;
		size++;
		if (size > m_sizeReserved) {
			checkSizeReserved(size);
		}
	}
	m_digitCount = size;
	return size;
}

void BigInteger::fillArray() {
	for (int i = m_digitCount; i < m_sizeReserved; i++) {
		m_number[i] = 0;
	}
}