#pragma once
#define ID_MAXSIZE		6				//������������ ���������� ������� � ��������������
#define TI_MAXSIZE		1024			// ������������ ���������� ��-�� � ������� ��������������� 
#define TI_INT_DEFAULT	0x00000000		// �������� �� ��������� ��� ���� integer 
#define TI_STR_DEFAULT	0x00			// �������� �� ��������� ��� ���� string 
#define TI_NULLIDX		-1				// ��� �������� ������� ���������������
#define TI_STR_MAXSIZE	255
#define TI_BLOCK_DEFAULT "GLOBAL"
#define TI_BLOCK_MAIN	"MAIN"

namespace IT	// ������� �������������
{
	enum IDDATATYPE { INT = 1, STR = 2 };	//���� ������ ���������������: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4 };		//���� ���������������: ����������, �������, ��������, �������

	struct Entry	//������ ������� ���������������
	{
		char parrentBlock[ID_MAXSIZE+1];	//!!!
		int			idxfirstLE;		//������ ������ ������ � ������� ������
		char		id[ID_MAXSIZE+1];		//������������� (������������� ��������� �� ID_MAXSIZE)
		IDDATATYPE  iddatatype;		//��� ������
		IDTYPE		idtype;		//��� ��������������
		union VALUE
		{
			int vint = NULL;	//�������� integer 
			struct
			{
				int len;	//���-�� �������� � string
				char str[TI_STR_MAXSIZE];	//������� string
			} vstr;		//�������� string
		} value;
	};

	struct IdTable		//��������� ������� ���������������
	{
		int maxsize;	//������� ������� ��������������� < TI_MAXSIZE
		int size;	//������� ������ ������� ��������������� < maxsize
		Entry* table;	//������ ����� ������� ���������������

	};
	IdTable Create(		//������� ������� ���������������
		int size		//������� ������� ��������������� < TI_MAXSIZE
	);
	void Add(	//�������� ������ � ������� ���������������
		IdTable& idtable,	//��������� ������� ���������������
		Entry entry		//������ ������� ���������������
	);
	int IsId(	//�������: ����� ������ (���� ����), TI_NULLIDX(���� ���)
		IdTable& idtable,	//��������� ������� ���������������
		char id[ID_MAXSIZE],		//�������������
		char block[ID_MAXSIZE]
		);

	void Delete(IdTable& idtable);		//������� ������� ������ (���������� ������)
	Entry GetEntry(IdTable& idtable, int n);

}
