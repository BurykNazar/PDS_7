#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab_7\Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestCalculateDegrees)
		{
			vector<vector<int>> edges = { {0, 1}, {1, 2}, {2, 0}, {3, 4} };
			vector<int> inDegrees, outDegrees, Degrees;
			N = 5; 
			M = 4; 

			calculateDegrees(edges, inDegrees, outDegrees, Degrees);

			Assert::AreEqual(inDegrees[0], 1);
			Assert::AreEqual(inDegrees[1], 1);
			Assert::AreEqual(inDegrees[2], 1);
			Assert::AreEqual(inDegrees[3], 0);
			Assert::AreEqual(inDegrees[4], 1);

			Assert::AreEqual(outDegrees[0], 1);
			Assert::AreEqual(outDegrees[1], 1);
			Assert::AreEqual(outDegrees[2], 1);
			Assert::AreEqual(outDegrees[3], 1);
			Assert::AreEqual(outDegrees[4], 0);

			Assert::AreEqual(Degrees[0], 2);
			Assert::AreEqual(Degrees[1], 2);
			Assert::AreEqual(Degrees[2], 2);
			Assert::AreEqual(Degrees[3], 1);
			Assert::AreEqual(Degrees[4], 1);
		}




		TEST_METHOD(TestIsHomogeneous)
		{
			vector<int> inDegrees = { 1, 1, 1, 1, 1 };
			vector<int> outDegrees = { 1, 1, 1, 1, 1 };
			Assert::IsTrue(isHomogeneous(inDegrees, outDegrees)); 

			vector<int> inDegrees2 = { 1, 2, 1, 0, 0 };
			vector<int> outDegrees2 = { 1, 1, 1, 1, 1 };
			Assert::IsFalse(isHomogeneous(inDegrees2, outDegrees2));

			vector<int> inDegrees3 = { 1, 1, 1, 1, 1 };
			vector<int> outDegrees3 = { 1, 2, 1, 1, 1 };
			Assert::IsFalse(isHomogeneous(inDegrees3, outDegrees3));
		}


		TEST_METHOD(TestGetIsolatedVertices)
		{
			vector<int> inDegrees = { 0, 1, 1, 0, 0 };
			vector<int> outDegrees = { 1, 0, 0, 0, 0 };

			vector<int> isolated = getIsolatedVertices(inDegrees, outDegrees);
			Assert::AreEqual((int)isolated.size(), 2);
			Assert::AreEqual(isolated[0], 4);
			Assert::AreEqual(isolated[1], 5);
		}

		TEST_METHOD(TestGetHangingVertices)
		{
			vector<int> inDegrees = { 1, 0, 0, 0, 0 };
			vector<int> outDegrees = { 0, 1, 0, 0, 0 };

			vector<int> hanging = getHangingVertices(inDegrees, outDegrees);
			Assert::AreEqual((int)hanging.size(), 2);
			Assert::AreEqual(hanging[0], 1);
			Assert::AreEqual(hanging[1], 2);
		}
	};
}
