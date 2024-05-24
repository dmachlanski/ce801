#include "CppUnitTest.h"
#include "../fuzzy_logic1/FuzzySet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{
	TEST_CLASS(TestFuzzySet)
	{
	public:

		TEST_METHOD(TestFuzzySet1)
		{
			string func1Name = "Func 1";
			MembershipFunction func1 = MembershipFunction(func1Name);
			func1.Points.push_back(Point(0, 0));
			func1.Points.push_back(Point(1, 1));
			func1.Points.push_back(Point(2, 1));
			func1.Points.push_back(Point(3, 0));

			string func2Name = "Func 2";
			MembershipFunction func2 = MembershipFunction(func2Name);
			func2.Points.push_back(Point(2, 0));
			func2.Points.push_back(Point(3, 1));
			func2.Points.push_back(Point(4, 0));

			string name = "Set 1";
			FuzzySet set1 = FuzzySet();
			set1.Functions.push_back(func1);
			set1.Functions.push_back(func2);

			Assert::AreEqual(2, int(set1.Functions.size()));
			
			auto res = set1.GetFiringStrength(2.75);
			
			Assert::AreEqual(2, int(res.size()));
			Assert::AreEqual(func1Name, res[0].Name);
			Assert::AreEqual(0.25, res[0].Strength);
			Assert::AreEqual(func2Name, res[1].Name);
			Assert::AreEqual(0.75, res[1].Strength);
		}
	};
}