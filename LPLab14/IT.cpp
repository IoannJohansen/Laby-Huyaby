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
			if (!strcmp(idtable.table[i].id, id) && idtable.table[i].idtype == F && !strcmp(idtable.table[i].parrentBlock, TI_BLOCK_DEFAULT))
				return i;
		}
		return TI_NULLIDX;
	}

	void IdTable::writeIT(const wchar_t* in)
	{
		int i = 0;
		wchar_t id[300];
		for (; in[i] != '\0'; i++)
			id[i] = in[i];
		id[i] = '\0';
		wcscat_s(id, PARM_ID_DEFAULT_EXT);

		std::ofstream* idStream = new std::ofstream;
		idStream->open(id);

		if (idStream->is_open())
		{
			bool flagForFirst = false;

#pragma region Literals

			* (idStream) << "====================================================================================" << std::endl;
			*(idStream) << "| ��������                                                                         |" << std::endl;
			*(idStream) << "====================================================================================" << std::endl;
			*(idStream) << '|' << std::setw(15) << "��� ������: " << "|" << std::setw(50) << "��������: " << '|' << std::setw(15) << "����� ������: " << '|' << std::endl;
			*(idStream) << "====================================================================================" << std::endl;

			for (int i = 0; i < this->size; i++)
			{
				if (this->table[i].idtype == IT::IDTYPE::L)
				{
					if (flagForFirst)
						*(idStream) << "------------------------------------------------------------------------------------" << std::endl;

					switch (this->table[i].iddatatype)
					{
					case IT::IDDATATYPE::INT:
					{
						*(idStream) << '|' << std::setw(15) << "INT  " << '|' << std::setw(50) << this->table[i].value.vint << "||" << this->table[i].idxfirstLE << '|' << std::setw(15) << "-" << '|' << std::endl;
						break;
					}
					case IT::IDDATATYPE::STR:
					{
						*(idStream) << '|' << std::setw(15) << "STR  " << '|' << std::setw(50) << this->table[i].value.vstr.str << "||" << this->table[i].idxfirstLE << '|' << std::setw(15) << (int)this->table[i].value.vstr.len << '|' << std::endl;
						break;
					}
					}

					flagForFirst = true;
				}
			}

			*(idStream) << "====================================================================================" << std::endl;


#pragma endregion
			* (idStream) << "\n\n\n";
#pragma region Functions

			flagForFirst = false;
			char buf[50]{};

			*(idStream) << "=====================================================" << std::endl;
			*(idStream) << "| �������                                           |" << std::endl;
			*(idStream) << "=====================================================" << std::endl;
			*(idStream) << '|' << std::setw(20) << "�������������: " << '|' << std::setw(30) << "��� ������������� ��������: " << '|' << std::endl;
			*(idStream) << "=====================================================" << std::endl;

			for (int i = 0; i < this->size; i++)
			{
				if (this->table[i].idtype == IT::IDTYPE::F)
				{
					strcat_s(buf, "  ");

					if (flagForFirst)
						*(idStream) << "-----------------------------------------------------" << std::endl;

					switch (this->table[i].iddatatype)
					{
					case IT::IDDATATYPE::INT:
					{
						*(idStream) << '|' << std::setw(20) << this->table[i].id << "||" << this->table[i].idxfirstLE << '|' << std::setw(30) << "INT " << '|' << std::endl;
						break;
					}
					case IT::IDDATATYPE::STR:
					{
						*(idStream) << '|' << std::setw(20) << this->table[i].id << "||" << this->table[i].idxfirstLE << '|' << std::setw(30) << "STR " << '|' << std::endl;
						break;
					}
					}

					flagForFirst = true;
				}


			}

			*(idStream) << "=====================================================" << std::endl;

#pragma endregion
			* (idStream) << "\n\n\n";
#pragma region Parameteres
			flagForFirst = false;
			*buf = '\0';
			*(idStream) << "=========================================================================" << std::endl;
			*(idStream) << "| ���������                                                             |" << std::endl;
			*(idStream) << "=========================================================================" << std::endl;
			*(idStream) << '|' << std::setw(20) << "��������: " << '|' << std::setw(30) << "������������ ����: " << '|' << std::setw(19) << "��� ������: " << '|' << std::endl;
			*(idStream) << "=========================================================================" << std::endl;
			for (int i = 0; i < this->size; i++)
			{
				if (this->table[i].idtype == IT::IDTYPE::P)
				{
					strcat_s(buf, "   ");

					if (flagForFirst)
						*(idStream) << "-------------------------------------------------------------------------" << std::endl;

					*(idStream) << '|' << std::setw(20) << this->table[i].id << "||" << this->table[i].idxfirstLE << '|' << std::setw(30) << this->table[i].parrentBlock << '|' << std::setw(19);
					if (this->table[i].iddatatype == IT::STR)*(idStream) << "STR" << '|' << std::endl;
					if (this->table[i].iddatatype == IT::INT)*(idStream) << "INT" << '|' << std::endl;
					flagForFirst = true;
				}
			}
			*(idStream) << "=========================================================================" << std::endl;
#pragma endregion
			*(idStream) << "\n\n\n";
#pragma region Variables

			flagForFirst = false;

			*(idStream) << "==================================================================================================================================================================" << std::endl;
			*(idStream) << "| ����������                                                                                                                                                     |" << std::endl;
			*(idStream) << "==================================================================================================================================================================" << std::endl;
			*(idStream) << '|' << std::setw(30) << "��� ������������� �����: " << '|' << std::setw(20) << "�������������: " << '|' << std::setw(15) << "��� ������: " << '|' << std::setw(25) << "��� ��������������: " << '|' << std::setw(50) << "��������: " << '|' << std::setw(15) << "����� ������: " << '|' << std::endl;
			*(idStream) << "==================================================================================================================================================================" << std::endl;

			for (int i = 0; i < this->size; i++)
			{
				if (this->table[i].idtype == IT::IDTYPE::V)
				{
					if (flagForFirst)
						*(idStream) << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

					switch (this->table[i].iddatatype)
					{
					case IT::IDDATATYPE::INT:
					{
						*(idStream) << '|' << std::setw(30) << this->table[i].parrentBlock << '|' << std::setw(20) << this->table[i].id << "||" << this->table[i].idxfirstLE << '|' << std::setw(15) << "INT " << '|' << std::setw(25) << "V  " << '|' << std::setw(50) << this->table[i].value.vint << '|' << std::setw(15) << "- " << '|' << std::endl;
						break;
					}
					case IT::IDDATATYPE::STR:
					{
						*(idStream) << '|' << std::setw(30) << this->table[i].parrentBlock << '|' << std::setw(20) << this->table[i].id << "||" << this->table[i].idxfirstLE << '|' << std::setw(15) << "STR " << '|' << std::setw(25) << "V  " << '|' << std::setw(50) << this->table[i].value.vstr.str << '|' << std::setw(15) << (int)this->table[i].value.vstr.len << '|' << std::endl;
						break;
					}
					}

					flagForFirst = true;
				}

				/*if (this->table[i].idtype == IT::IDTYPE::P)
				{
					if (flagForFirst)
						*(idStream) << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

					switch (this->table[i].iddatatype)
					{
					case IT::IDDATATYPE::INT:
					{
						*(idStream) << '|' << std::setw(30) << this->table[i].parrentBlock << '|' << std::setw(20) << this->table[i].id << '|' << std::setw(15) << "INT " << '|' << std::setw(25) << "V  " << '|' << std::setw(50) << this->table[i].value.vint << '|' << std::setw(15) << "- " << '|' << std::endl;
						break;
					}
					case IT::IDDATATYPE::STR:
					{
						*(idStream) << '|' << std::setw(30) << this->table[i].parrentBlock << '|' << std::setw(20) << this->table[i].id << '|' << std::setw(15) << "STR " << '|' << std::setw(25) << "V  " << '|' << std::setw(50) << this->table[i].value.vstr.str << '|' << std::setw(15) << (int)this->table[i].value.vstr.len << '|' << std::endl;
						break;
					}
					}

					flagForFirst = true;
				}*/


			}

			*(idStream) << "==================================================================================================================================================================" << std::endl;

#pragma endregion
			* (idStream) << "\n\n\n";

		}
		else
			throw ERROR_THROW(125);
		idStream->close();
		delete idStream;
	}

	void Delete(IdTable& idtable)
	{
		delete[] idtable.table;
		idtable = {};
	}
}