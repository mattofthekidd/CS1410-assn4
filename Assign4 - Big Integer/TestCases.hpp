#ifndef _TEST_CASES_HPP
#define _TEST_CASES_HPP

#include <functional>

class TestCases
{
	public:
		static void runTestCases();

		static bool testCase1(void);
		static bool testCase2(void);
		static bool testCase3(void);
		static bool testCase4(void);
		static bool testCase5(void);
		static bool testCase6(void);
		static bool testCase7(void);
		static bool testCase8(void);
		static bool testCase9(void);
		
	private:
		static void runTest(std::function<bool(void)> testCase, std::string label);

};

#endif // _TEST_CASES_HPP