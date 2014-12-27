#include <iostream>

#include "../XMLLib/XMLPrinter.h"


int main()
{
	XMLTag rootTag;
	XMLTag personTagOne;
	XMLTag nameTagOne;
	nameTagOne.AddData("One");
	XMLTag nameTagTwo;
	nameTagTwo.AddData("Something");

	XMLTag personTagTwo;
	XMLTag nameTag;
	nameTag.AddData("Two");
	XMLTag emailTag;
	emailTag.AddAttrib("isMy", "false");
	emailTag.AddAttrib("password", "123");
	emailTag.AddData("example@example.com");

	XMLTag anotherTag;
	XMLTag oneDig;
	oneDig.AddData("1");
	XMLTag twoDig;
	twoDig.AddData("2");
	XMLTag oneTwoDig;
	oneTwoDig.AddData("12");
	XMLTag oneTwoThreeDig;
	oneTwoThreeDig.AddData("123");
	XMLTag oneTwoThreeFourDig;
	oneTwoThreeFourDig.AddData("1234");

	XMLDoc testDoc;
	testDoc.AddTag("root", rootTag);
	testDoc.AddTag("root/person", personTagOne);
	testDoc.AddTag("root/person/name", nameTagOne);
	testDoc.AddTag("root/person/name", nameTagTwo);
	testDoc.AddTag("root/person", personTagTwo);
	testDoc.AddTag("root/person/name", nameTag);
	testDoc.AddTag("root/person/email", emailTag);
	
	testDoc.AddTag("another", anotherTag);
	testDoc.AddTag("another/one", oneDig);
	testDoc.AddTag("another/two", twoDig);
	testDoc.AddTag("another/one/two", oneTwoDig);
	testDoc.AddTag("another/one/two/three", oneTwoThreeDig);
	testDoc.AddTag("another/one/two/three/four", oneTwoThreeFourDig);
	testDoc.AddTag("another/one", oneDig);
	testDoc.AddTag("another/one/two", oneTwoDig);


	TreeIterator<XMLTag> docIter = testDoc.GetIterator();
	XMLPrinter::PrettyPrint(docIter);


	return 0;
}