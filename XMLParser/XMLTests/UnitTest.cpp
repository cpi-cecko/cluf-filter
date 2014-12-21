#include "stdafx.h"

#include <vector>
#include <string>

#include "../Tree/Tree.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace XMLTests
{
	[TestClass]
	public ref class UnitTest
	{
	private:
		TestContext^ testContextInstance;

	public: 
		/// <summary>
		///Gets or sets the test context which provides
		///information about and functionality for the current test run.
		///</summary>
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
		{
			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
			{
				return testContextInstance;
			}
			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
			{
				testContextInstance = value;
			}
		};

		#pragma region Additional test attributes
		//
		//You can use the following additional attributes as you write your tests:
		//
		//Use ClassInitialize to run code before running the first test in the class
		//[ClassInitialize()]
		//static void MyClassInitialize(TestContext^ testContext) {};
		//
		//Use ClassCleanup to run code after all tests in a class have run
		//[ClassCleanup()]
		//static void MyClassCleanup() {};
		//
		//Use TestInitialize to run code before running each test
		//[TestInitialize()]
		//void MyTestInitialize() {};
		//
		//Use TestCleanup to run code after each test has run
		//[TestCleanup()]
		//void MyTestCleanup() {};
		//
		#pragma endregion 

		[TestMethod]
		void TestTreeInsert()
		{
			Tree<std::string, int> testTree;

			// Simple insertion
			testTree.Insert("root", 5);
			testTree.Insert("my", 10);

			Assert::AreEqual(testTree.At("root").val[0], 5);
			Assert::AreEqual(testTree.At("my").val[0], 10);

			// Child nodes insertion
			testTree.Insert("root/newElem", 10);
			testTree.Insert("root/another", 90);
			testTree.Insert("root/another/last", 19);
			testTree.Insert("nonexist/here", 4);

			Assert::AreEqual(testTree.At("root/newElem").val[0], 10);
			Assert::AreEqual(testTree.At("root/another").val[0], 90);
			Assert::AreEqual(testTree.At("root/another/last").val[0], 19);
			Assert::AreEqual(testTree.At("root/here").val[0], 4);

			// Overwrite key
			testTree.Insert("my", 15);

			Assert::AreEqual(testTree.At("my").val[0], 15);

			// Really deep insertion
			testTree.Insert("deep/deep1/deep2/deep3/deep4/deep5/deep6/deep7/deep8/deep9/deep10/deep11/deep12/deep13/deep14/deep15/deep16/deep17/deep18", 999999);

			Assert::AreEqual(testTree.At("deep/deep1/deep2/deep3/deep4/deep5/deep6/deep7/deep8/deep9/deep10/deep11/deep12/deep13/deep14/deep15/deep16/deep17/deep18").val[0], 999999);

			// Keys with bad characters
			Assert::IsFalse(testTree.Insert("gosho:pesho()", 10));
			Assert::IsFalse(testTree.At("gosho:pesho()").isValid);

			// Keys begining with '/' (slash)
			testTree.Insert("/root", 10);
			Assert::AreEqual(testTree.At("/root").val[0], testTree.At("root").val[0]);

			// Insert at empty key
			Assert::IsFalse(testTree.Insert("", 5));
			Assert::IsFalse(testTree.At("").isValid);
		};

		[TestMethod]
		void TestTreeRemove()
		{
			Tree<std::string, double> testTree;

			testTree.Insert("root", 2.5);
			testTree.Insert("my/number", 13.4);
			testTree.Insert("/my/otherNumber", 5.4444);
			testTree.Insert("root/PI", 3.14);
			testTree.Insert("root/E", 2.79);
			testTree.Insert("root/PI/PISq", 9.86);

			// Removing value
			Assert::IsTrue(testTree.Remove("my/number"));
			Assert::IsFalse(testTree.At("my/number").isValid);

			// Removing whole subtree
			Assert::IsTrue(testTree.Remove("root"));
			Assert::IsFalse(testTree.At("root").isValid);
			Assert::IsFalse(testTree.At("root/PI").isValid);
			Assert::IsFalse(testTree.At("root/E").isValid);
			Assert::IsFalse(testTree.At("root/PI/PISq").isValid);

			Assert::IsTrue(testTree.IsEmpty());

			// Removing non-existent val
			Assert::IsFalse(testTree.Remove("nye"));

			// Removing non-existent val on non-empty tree
			testTree.Insert("nye", -1.09);
			Assert::IsFalse(testTree.Remove("ai"));

			Assert::IsFalse(testTree.IsEmpty());
		};

		// Optional
		/*
		[TestMethod]
		void TestTreeFind()
		{
			Tree<std::string, std::string> testTree;

			testTree.Insert("root/person/name", "One");
			testTree.Insert("root/person/name", "Something");
			testTree.Insert("root/person/name", "Two");
			testTree.Insert("root/person/email", "example@example.com");

			// Getting existant vals
			Assert::IsTrue(testTree.Find("name").isValid);
			std::vector<std::string> names = testTree.Find("name").val;
			Assert::IsFalse(names.empty());
			Assert::IsTrue(names.size() == 3);
			
			// Getting non-existant vals
			Assert::IsFalse(testTree.Find("job").isValid);

			// One val, part of path
			Assert::IsTrue(testTree.Find("person/email").isValid);
			std::vector<std::string> emails = testTree.Find("person/email").val;
			Assert::IsFalse(emails.empty());
			Assert::IsTrue(emails.size() == 1);
		};
		*/
	};
}
