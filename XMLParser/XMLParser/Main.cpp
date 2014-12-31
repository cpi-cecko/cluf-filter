#include <iostream>

#include "../XMLLib/XMLPrinter.h"
#include "../XMLLib/XMLReader.h"


int main()
{
	// Look at the tests to see how this stuff works.


	/*
	// I was a bit adventurous and tried to develop an XML parser.
	// Sadly, I didn't have the time/nerves to finish it.
	XMLReader reader;
	XMLDoc testDoc;
	if (reader.ReadInto(&testDoc, "../compact.xml"))
	{
		TreeIterator<XMLTag> docIter = testDoc.GetIterator();
		XMLPrinter::PrettyPrint(docIter);
	}
	*/

	return 0;
}