#include "pch.h"
#include "CppUnitTest.h"
#include "../Personal/Personal.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Line line1(1, 0, 0, -1);
			Point p1(0, 0);
			Circle c1(p1, 1);
		}

		TEST_METHOD(TestMethod2)
		{
			Line line1(1, 0, 3, -1);
			Point p1(0, 0);
			Circle c1(p1, 1);
			Assert::AreEqual(c1.GetCrossToLine(line1), 0);
		}
		TEST_METHOD(TestMethod3) {
			Line line1(0, 0, 0, -1);
			Point p1(0, 0);
			Circle c1(p1, 1);
			Assert::AreEqual(c1.GetCrossToLine(line1), 2);
		}
		TEST_METHOD(TestMethod4) {
			Line line1(1, 0, 1, 1);
			Point p1(0, 0);
			Circle c1(p1, 1);
			Assert::AreEqual(c1.GetCrossToLine(line1), 1);
		}
		TEST_METHOD(TestMethod5) {
			Circle c1(Point(0, 0), 1);
			Circle c2(Point(0, 0), 5);
			Assert::AreEqual(c1.GetCrossToCircle(c2), 2);
		}
	};
}
