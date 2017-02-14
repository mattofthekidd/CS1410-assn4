
#include "TestCases.hpp"
#include "BigInteger.hpp"


void TestCases::runTestCases()
{
	std::cout << "[=================]" << std::endl;
	std::cout << "[-----------------] Running tests" << std::endl;
	std::cout << "[-----------------]" << std::endl;

	runTest(testCase1, "Constructor Test");
	runTest(testCase2, "Integer Convert Constructor Test");
	runTest(testCase3, "String Convert Constructor Test");
	runTest(testCase4, "Copy Constructor Test");
	runTest(testCase5, "Assignment Operator Test");
	runTest(testCase6, "Add Test");
	runTest(testCase7, "Multiply Test");
	runTest(testCase8, "GetDigit Test");
	runTest(testCase9, "SetDigit Test");

	std::cout << "[-----------------]" << std::endl;
	std::cout << "[-----------------] Tests complete" << std::endl;
	std::cout << "[=================]" << std::endl;
}

void TestCases::runTest(std::function<bool(void)> testCase, std::string label)
{
	std::cout << "[ Running         ] " << label << std::endl;
	
	if (testCase())
	{
		std::cout << "[            PASS ]";
	}
	else
	{
		std::cout << "[          FAILED ]";
	}

	std::cout << " " << label << std::endl;
}

bool TestCases::testCase1(void)
{
	BigInteger i;
	
	return (i.m_number != nullptr) && (i.m_sizeReserved == 4) && (i.m_digitCount == 0);
}

bool TestCases::testCase2(void)
{
	BigInteger i(1234567);
	
	return (i.m_number != nullptr) && (i.m_sizeReserved > 0) && (i.m_digitCount == 7) && (i.m_number[6] == 1) && (i.m_number[5] == 2)
	  && (i.m_number[4] == 3) && (i.m_number[3] == 4) && (i.m_number[2] == 5) && (i.m_number[1] == 6) && (i.m_number[0] == 7);
}

bool TestCases::testCase3(void)
{
	bool ret = true;
	std::string value = "123456789123456789123456789";
	BigInteger i(value);
	
	if ((i.m_number == nullptr) || (i.m_sizeReserved <= 0) || (i.m_digitCount != value.length()))
	{
		ret = false;
	}
	else
	{
		for (int j = 0; j < value.length() && ret; j++)
		{
			if (i.m_number[j] != (value[value.length() - 1 - j] - '0'))
			{
				ret = false;
			}
		}
	}
	
	return ret;
}

bool TestCases::testCase4(void)
{
	bool ret = true;
	BigInteger i("123456789123456789123456789");
	BigInteger copy(i);
	
	if (copy.m_number == nullptr)
	{
		std::cout << "  The copy of m_number was 'nullptr'" << std::endl;
		ret = false;
	}
	else if (copy.m_sizeReserved != i.m_sizeReserved)
	{
		std::cout << "  The m_sizeReserved variables do not match" << std::endl;
		std::cout << "   Expected " << i.m_sizeReserved << std::endl;
		std::cout << "   Actual " << copy.m_sizeReserved << std::endl;
		ret = false;
	}
	else if (i.m_digitCount != copy.m_digitCount)
	{
		std::cout << "  The m_digitCount variables do not match" << std::endl;
		std::cout << "   Expected " << i.m_digitCount << std::endl;
		std::cout << "   Actual " << copy.m_digitCount << std::endl;
		ret = false;
	}
	else
	{
		for (unsigned int j = 0; j < copy.m_sizeReserved && j < i.m_sizeReserved && ret; j++)
		{
			if (i.m_number[j] != copy.m_number[j])
			{
				ret = false;
				std::cout << "  The m_number[" << j << "] Didn't match" << std::endl;
				std::cout << "   Expected " << i.m_number[j] << std::endl;
				std::cout << "   Actual " << copy.m_number[j] << std::endl;
			}
		}
	}
	
	return ret;
}

bool TestCases::testCase5(void)
{
	bool ret = true;
	BigInteger i("123456789123456789123456789");
	BigInteger copy("1");
	
	copy = i;
	
	if (copy.m_number == nullptr)
	{
		std::cout << "  The copy of m_number was 'nullptr'" << std::endl;
		ret = false;
	}
	else if (copy.m_sizeReserved != i.m_sizeReserved)
	{
		std::cout << "  The m_sizeReserved variables do not match" << std::endl;
		std::cout << "   Expected " << i.m_sizeReserved << std::endl;
		std::cout << "   Actual " << copy.m_sizeReserved << std::endl;
		ret = false;
	}
	else if (i.m_digitCount != copy.m_digitCount)
	{
		std::cout << "  The m_digitCount variables do not match" << std::endl;
		std::cout << "   Expected " << i.m_digitCount << std::endl;
		std::cout << "   Actual " << copy.m_digitCount << std::endl;
		ret = false;
	}
	else
	{
		for (unsigned int j = 0; j < copy.m_sizeReserved && j < i.m_sizeReserved && ret; j++)
		{
			if (i.m_number[j] != copy.m_number[j])
			{
				ret = false;
				std::cout << "  The m_number[" << j << "] Didn't match" << std::endl;
				std::cout << "   Expected " << i.m_number[j] << std::endl;
				std::cout << "   Actual " << copy.m_number[j] << std::endl;
			}
		}
	}
	
	return ret;
}

bool TestCases::testCase6(void)
{
	bool ret = true;
	BigInteger item1("11111111111111");
	BigInteger item2("22222222222222");
	BigInteger expect("33333333333333");
	BigInteger copy = item2.add(item1);
	
	if (copy.m_number == nullptr)
	{
		std::cout << "  The copy of m_number was 'nullptr'" << std::endl;
		ret = false;
	}
	else if (expect.m_digitCount != copy.m_digitCount)
	{
		std::cout << "  The m_digitCount variables do not match" << std::endl;
		std::cout << "   Expected " << expect.m_digitCount << std::endl;
		std::cout << "   Actual " << copy.m_digitCount << std::endl;
		ret = false;
	}
	else
	{
		for (unsigned int j = 0; j < copy.m_digitCount && j < expect.m_digitCount && ret; j++)
		{
			if (expect.m_number[j] != copy.m_number[j])
			{
				ret = false;
				std::cout << "  The m_number[" << j << "] Didn't match" << std::endl;
				std::cout << "   Expected " << expect.m_number[j] << std::endl;
				std::cout << "   Actual " << copy.m_number[j] << std::endl;
			}
		}
	}
	
	return ret;
}

bool TestCases::testCase7(void)
{
	bool ret = true;
	BigInteger item1("2345678904567");
	BigInteger item2("123456789056");
	BigInteger expect("289589985714237274018752");
	BigInteger copy = item2.multiply(item1);
	
	if (copy.m_number == nullptr)
	{
		std::cout << "  The copy of m_number was 'nullptr'" << std::endl;
		ret = false;
	}
	else if (expect.m_digitCount != copy.m_digitCount)
	{
		std::cout << "  The m_digitCount variables do not match" << std::endl;
		std::cout << "   Expected " << expect.m_digitCount << std::endl;
		std::cout << "   Actual " << copy.m_digitCount << std::endl;
		ret = false;
	}
	else
	{
		for (unsigned int j = 0; j < copy.m_digitCount && j < expect.m_digitCount && ret; j++)
		{
			if (expect.m_number[j] != copy.m_number[j])
			{
				ret = false;
				std::cout << "  The m_number[" << j << "] Didn't match" << std::endl;
				std::cout << "   Expected " << expect.m_number[j] << std::endl;
				std::cout << "   Actual " << copy.m_number[j] << std::endl;
			}
		}
	}
	
	return ret;
}

bool TestCases::testCase8(void)
{
	bool ret = true;
	std::string value = "2345678904567";
	BigInteger item(value);
	
	for (unsigned int i = 0; i < item.m_digitCount; i++)
	{
		unsigned int res = item.getDigit(item.m_digitCount - i - 1);
		if (res != value[i] - '0')
		{
			ret = false;
			std::cout << "  The getdigit(" << item.m_digitCount - i - 1 << ") Didn't match" << std::endl;
			std::cout << "   Expected " << res << std::endl;
			std::cout << "   Actual " << value[i] << std::endl;
		}
	}
	
	return ret;
}

bool TestCases::testCase9(void)
{
	unsigned int pos = 5;
	std::uint8_t digit = 1;
	BigInteger item;
	
	if (item.m_number == nullptr)
	{
		std::cout << "  An empty BigInteger should have a non-nullptr m_number variable" << std::endl;
		return false;
	}
	else if (item.m_digitCount != 0)
	{
		std::cout << "  The m_digitcount variable was incorrect" << std::endl;
		std::cout << "   Expected " << 0 << std::endl;
		std::cout << "   Actual " << item.m_digitCount << std::endl;
		return false;
	}

	for (unsigned int i = 0; i < pos; i++)
	{
//		item.setDigit(i, digit);
		
		if (item.m_number == nullptr)
		{
			std::cout << "  The m_number variable should not be 'nullptr'" << std::endl;
			return false;
		}
		else if (item.m_digitCount != i + 1)
		{
			std::cout << "  The m_digitcount variable was incorrect" << std::endl;
			std::cout << "   Expected " << i + 1 << std::endl;
			std::cout << "   Actual " << item.m_digitCount << std::endl;
			return false;
		}
		else if (item.getDigit(i) != digit)
		{
			std::cout << "  The getDigit(" << i << ") Didn't match" << std::endl;
			std::cout << "   Expected " << digit << std::endl;
			std::cout << "   Actual " << item.getDigit(i) << std::endl;
			return false;
		}

		digit++;
	}
	
	return true;
}
