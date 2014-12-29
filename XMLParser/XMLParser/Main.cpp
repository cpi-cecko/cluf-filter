#include <iostream>

#include "../XMLLib/XMLPrinter.h"
#include "../XMLLib/XMLReader.h"


int main()
{
	XMLReader reader;
	XMLDoc testDoc;
	if (reader.ReadInto(&testDoc, "../compact.xml"))
	{
		TreeIterator<XMLTag> docIter = testDoc.GetIterator();
		XMLPrinter::PrettyPrint(docIter);
	}


	return 0;
}