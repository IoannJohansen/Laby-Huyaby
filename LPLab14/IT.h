#pragma once
#pragma once

#define ID_MAXSIZE		5				//������������ ���������� ������� � ��������������
#define TI_MAXSIZE		1024			// ������������ ���������� ��-�� � ������� ��������������� 
#define TI_INT_DEFAULT	0x00000000		// �������� �� ��������� ��� ���� integer 
#define TI_STR_DEFAULT	0x00			// �������� �� ��������� ��� ���� string 
#define TI_NULLIDX		-1				// ��� �������� ������� ���������������
#define TI_STR_MAXSIZE	255

#define PARM_ID_DEFAULT_EXT L".id.txt" //��� ����� � ������ ������������ ������a(�������������� � ��������)

namespace IT	// ������� �������������
{
	enum IDDATATYPE { INT = 1, STR = 2 };		// ���� ������ �������������: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4 };			// ���� ���������������: ����������, �������, ��������, �������


	struct Entry						// ��-� ������� ���������������
	{
		
		char id[ID_MAXSIZE];			// ������������� (������������� ��������� �� ID_MAXSIZE
		IDDATATYPE	iddatatype;			// ��� ������
		IDTYPE	idtype;					// ��� ������������
		union VALUE
		{
			int vint;					// �������� integer
			struct
			{
				unsigned char len;				// ��������� �������� � string
				char str[TI_STR_MAXSIZE-1]; // ������� string
			} vstr[TI_STR_MAXSIZE];	// �������� string
		}value;	// �������� ��������������
	};

	struct IdTable // ��������� ������� ���������������
	{
		int maxsize;				// ������� ������� ��������������� < TI_MAXSIZE
		int current_size;			// ������� ������ ������� ��������������� < maxsize
		Entry* table;				// ������ ����� ������� ���������������
	};

	IdTable Create(int size);
	void Add(IdTable& idTable, Entry entry);
	Entry GetEntry(IdTable& idTable, int n);
	int IsId(IdTable& idTable, char id[ID_MAXSIZE]);
	void Delete(IdTable& idTable);
}
