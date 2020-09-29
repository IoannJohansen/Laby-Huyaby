#pragma once
#include "stdafx.h"
#define ID_MAXSIZE 5
#define TI_MAXSIZE 4096
#define TI_INT_DEFAULT 0X00000000
#define TI_STR_DEFAULT 0X00
#define TI_NULLIDX 0Xffffffff
#define TI_STR_MAXSIZE 255
namespace IT {
	enum IDDATATYPE {INT = 1, STR = 2};
	enum IDTYPE {V = 1, F = 2, P = 3, L = 3};

	struct Entry
	{
		int idFirstLE;
		char id[ID_MAXSIZE];
		IDDATATYPE iddatatype;
		IDTYPE idtype;
		union
		{
			int vint;
			struct
			{
				char len;
				char str[TI_STR_MAXSIZE-1];
			} vstr[TI_STR_MAXSIZE];
		} value;
	};
	struct IdTable				//экземпл€р таблицы идентификаторов
	{
		int maxsize;			//емкость таблицы идентификаторов < TI_MAXSIZE
		int size;				//текущий размер таблицы идентификаторов < maxsize
		Entry* table;			//массив строк таблицы идентификаторов
	};
	IdTable Create(				//создать таблицу идентификаторов
		int size				//емкость таблицы идентификаторов
	);
	void Add(					//добавить строку в таблицу идентификаторов
		IdTable& idtable,		//экземпл€р таблицы идентификаторов
		Entry entry				//строка таблицы идентификаторов
	);
	Entry GetEntry(				//получить строку таблицы идентификаторов
		IdTable& idtable,		//экземпл€р таблицы идентификаторов
		int n					//номер получаемой строки
	);
	int IsId(					//возврат: номер строки(если есть), TI_NULLIDX(если нет)
		IdTable& idtable,		//экземпл€р таблицы идентификаторов
		char id[ID_MAXSIZE]		//идентафикатор
	);
	void Delete(IdTable& idtable);
	int checkId(IdTable& idtable, char value[ID_MAXSIZE]);
	int IsDublId(IdTable& idtable, char id[ID_MAXSIZE]); //проверка на дублирвание ид
	int checkId(IdTable& idtable, int value);			//удалить таблицу лексем
}