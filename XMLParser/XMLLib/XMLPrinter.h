#pragma once


#include "XMLDoc.h"
#include "XMLTag.h"


class XMLPrinter
{
public:
	static void PrettyPrint(TreeIterator<XMLTag> &iter);
	static void CompactPrint(TreeIterator<XMLTag> &iter);
};