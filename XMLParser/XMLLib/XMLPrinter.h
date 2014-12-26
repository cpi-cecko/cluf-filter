#pragma once


#include "XMLDoc.h"


class XMLPrinter
{
public:
	static void PrettyPrint(TreeIterator<XMLTag> iter);
	static void CompactPrint(TreeIterator<XMLTag> iter);
};