#include <iostream>

#include "BigInteger.hpp"
#include "TestCases.hpp"

// ------------------------------------------------------------------
//
// Site to compare long factorial results: http://www.dcode.fr/factorial
//
// ------------------------------------------------------------------
BigInteger factorial(unsigned int value)
{
	BigInteger result(1);

	for (unsigned int next = 1; next <= value; next++)
	{
		result = result.multiply(next);
	}

	return result;
}

int main()
{
	BigInteger one(1234);
	BigInteger two(9999);
	BigInteger result = one.add(two);
	std::cout << "one + two = ";
	result.display();
	std::cout << std::endl;

	//
	// Site to get big number results: https://defuse.ca/big-number-calculator.htm

	BigInteger three("1234567890");
	BigInteger four("123456789");
	BigInteger result2 = three.multiply(four);
	std::cout << "three * four = ";
	result2.display();
	std::cout << std::endl;

	/*BigInteger f = factorial(123);
	std::cout << "factorial of 123 is: ";
	f.display();
	std::cout << std::endl;*/

	//TestCases::runTestCases();

	return 0;
}
