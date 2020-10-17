#include "stdafx.h"
#include <iomanip>
#include "IT.h"
namespace IT
{

	IdTable Create(int size)
	{
		IdTable* New = new IdTable;
		New->maxsize = size;
		New->size = 0;
		New->table = new Entry[size];
		return *New;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		if (idtable.size == idtable.maxsize) throw ERROR_THROW(122);
		idtable.table[idtable.size++] = entry;
	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		return idtable.table[n];
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE], char block[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (!strcmp(idtable.table[i].id, id) && !strcmp(idtable.table[i].parrentBlock, block))
				return i;
			if (!strcmp(idtable.table[i].id, id) && idtable.table[i].idtype == F)
				return i;
		}
		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable)
	{
		delete[] idtable.table;
		idtable = {};
	}
}