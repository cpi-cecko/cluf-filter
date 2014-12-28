#include <iostream>

#include "../XMLLib/XMLPrinter.h"
#include "../XMLLib/XMLReader.h"


int main()
{
	XMLReader reader;
	XMLDoc testDoc;
	if (reader.ReadInto(&testDoc, "../sample.xml"))
	{
		TreeIterator<XMLTag> docIter = testDoc.GetIterator();
		XMLPrinter::PrettyPrint(docIter);
	}


	return 0;
}