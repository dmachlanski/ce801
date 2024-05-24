#include "CppUnitTest.h"
#include "../fuzzy_logic1/Point.h"
#include "../fuzzy_logic1/FiringStrength.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{		
	TEST_CLASS(TestMisc)
	{
	public:
		
		TEST_METHOD(TestPoint)
		{
			double x = 2.5;
			double y = 3;
			Point p = Point(x, y);

			Assert::AreEqual(x, p.X);
			Assert::AreEqual(y, p.Y);

			double new_x = -1.5;
			p.X = new_x;

			Assert::AreEqual(new_x, p.X);
		}

		TEST_METHOD(TestFiringStrength)
		{
			string name = "test name";
			double value = 2.34;
			FiringStrength fs = FiringStrength(name, value);

			Assert::AreEqual(name, fs.Name);
			Assert::AreEqual(value, fs.Strength);
		}
	};
}