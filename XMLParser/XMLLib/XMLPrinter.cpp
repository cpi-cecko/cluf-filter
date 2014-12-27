#include "stdafx.h"
#include "XMLPrinter.h"

#include <iostream>


void PrettyPrintH(TreeIterator<XMLTag> &iter, size_t depth);

void XMLPrinter::PrettyPrint(TreeIterator<XMLTag> &iter)
{
	PrettyPrintH(iter, 0);
}

std::string Spaces(size_t depth);

void PrettyPrintH(TreeIterator<XMLTag> &iter, size_t depth)
{
	Tree<XMLTag> *current = iter.Deref();
	if ( ! current) return;

	std::cout << Spaces(depth) << "<" << current->GetKey();
	if (current->HasVal())
	{
		auto attribs = current->GetVal()->GetAttribs();
		for (auto attrib = attribs.begin(); attrib != attribs.end(); ++attrib)
		{
			std::cout << " \"" << attrib->first << "\"=\"" << attrib->second << "\"";
		}
		std::cout << ">\n";
		if (current->GetVal()->HasData())
		{
			std::cout << Spaces(depth + 1) << current->GetVal()->GetData() << "\n";
		}
	}
	if (iter.HasChild())
	{
		PrettyPrintH(iter.Child(), depth+1);
	}
	std::cout << Spaces(depth) << "</" << current->GetKey() << ">\n";

	while (iter.HasNext())
	{
		PrettyPrintH(iter.Next(), depth);
	}
}

std::string Spaces(size_t depth)
{
	return std::string(depth * 2, ' ');
}


void XMLPrinter::CompactPrint(TreeIterator<XMLTag> &iter)
{
	Tree<XMLTag> *current = iter.Deref();
	if ( ! current) return;

	std::cout << "<" << current->GetKey();
	if (current->HasVal())
	{
		auto attribs = current->GetVal()->GetAttribs();
		for (auto attrib = attribs.begin(); attrib != attribs.end(); ++attrib)
		{
			std::cout << " \"" << attrib->first << "\"=\"" << attrib->second << "\"";
		}
		std::cout << ">";
		if (current->GetVal()->HasData())
		{
			std::cout << current->GetVal()->GetData();
		}
	}
	if (iter.HasChild())
	{
		CompactPrint(iter.Child());
	}
	std::cout << "</" << current->GetKey() << ">";

	while (iter.HasNext())
	{
		CompactPrint(iter.Next());
	}
}