#include "pch.h"
#include "CppUnitTest.h"
#include "../1/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			const int n = 3; // Adjust the size as needed
			int** a = new int* [n];
			for (int i = 0; i < n; i++)
				a[i] = new int[n];

			CreateRecursive(a, n, 0, 0, 7, 65);

		

			for (int i = 0; i < n; i++)
				delete[] a[i];
			delete[] a;
		}
	};
}
