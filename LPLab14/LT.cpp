#include "LT.h"
#include "Error.h"
#include <fstream>

namespace LT {
	LexTable Create(int size)
	{
		LexTable* New = new LexTable;
		New->maxsize = size;
		New->size = 0;
		New->table = new Entry[size];
		memset(New->table, 0xff, sizeof(Entry) * size);
		return *New;
	}

	void Add(LexTable& lextable, Entry entry)
	{
		if (lextable.size == lextable.maxsize) throw ERROR_THROW(120);
		lextable.table[lextable.size++] = entry;
	}

	Entry GetEntry(LexTable& lextable, int n)
	{
		return lextable.table[n];
	}

	void Delete(LexTable& lextable)
	{
		delete[] lextable.table;
		lextable = {};
	}
}