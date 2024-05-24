#include "CppUnitTest.h"
#include "../fuzzy_logic1/MembershipFunction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{
	TEST_CLASS(TestMemFunction)
	{
	public:

		TEST_METHOD(TestMFunctionName)
		{
			string name = "function";
			MembershipFunction mf = MembershipFunction(name);

			Assert::AreEqual(name, mf.Name);
		}

		TEST_METHOD(TestMFunctionContainsX)
		{
			MembershipFunction func1 = GetMFunction();

			Assert::IsFalse(func1.Points.empty());
			Assert::AreEqual(4, int(func1.Points.size()));

			Assert::IsTrue(func1.ContainsX(0));
			Assert::IsTrue(func1.ContainsX(0.1));
			Assert::IsTrue(func1.ContainsX(0.01));
			Assert::IsTrue(func1.ContainsX(1.1));
			Assert::IsTrue(func1.ContainsX(1.99));
			Assert::IsTrue(func1.ContainsX(2));
			Assert::IsTrue(func1.ContainsX(2.99));
			Assert::IsTrue(func1.ContainsX(3.0));

			Assert::IsFalse(func1.ContainsX(-1));
			Assert::IsFalse(func1.ContainsX(-0.01));
			Assert::IsFalse(func1.ContainsX(-0.1));
			Assert::IsFalse(func1.ContainsX(-10));
			Assert::IsFalse(func1.ContainsX(3.01));
			Assert::IsFalse(func1.ContainsX(3.1));
			Assert::IsFalse(func1.ContainsX(5));
		}

		TEST_METHOD(TestMFunctionGetValue)
		{
			MembershipFunction func1 = GetMFunction();

			Assert::AreEqual(1.0, func1.GetValue(1));
			Assert::AreEqual(0.0, func1.GetValue(0));
			Assert::AreEqual(0.0, func1.GetValue(-1));
			Assert::AreEqual(0.4, func1.GetValue(0.4));
			Assert::AreEqual(0.6, func1.GetValue(0.6));
			Assert::AreEqual(0.1, func1.GetValue(0.1));
			Assert::AreEqual(1.0, func1.GetValue(2));
			Assert::AreEqual(1.0, func1.GetValue(1.5));
			Assert::AreEqual(0.5, func1.GetValue(2.5));
			Assert::AreEqual(0.0, func1.GetValue(3));
			Assert::AreEqual(0.0, func1.GetValue(3.1));
		}

	private:
		MembershipFunction GetMFunction()
		{
			MembershipFunction func1 = MembershipFunction("Func 1");
			func1.Points.push_back(Point(0, 0));
			func1.Points.push_back(Point(1, 1));
			func1.Points.push_back(Point(2, 1));
			func1.Points.push_back(Point(3, 0));

			return func1;
		}
	};
}