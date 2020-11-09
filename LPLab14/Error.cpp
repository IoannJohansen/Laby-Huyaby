#include "Error.h"

namespace Error
{
	// ����� ������: 0-99 - ��������� ������
	//				 100-109 - ������ ����������
	//				 110-119 - ������ �������� � ������ ������
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "������������ ��� ������"),
		ERROR_ENTRY(1, "��������� ����"),

		ERROR_ENTRY_NODEF(2),		ERROR_ENTRY_NODEF(3),		ERROR_ENTRY_NODEF(4),
		ERROR_ENTRY_NODEF(5),		ERROR_ENTRY_NODEF(6),		ERROR_ENTRY_NODEF(7),
		ERROR_ENTRY_NODEF(8),		ERROR_ENTRY_NODEF(9),		ERROR_ENTRY_NODEF10(10),
		ERROR_ENTRY_NODEF10(20),	ERROR_ENTRY_NODEF10(30),	ERROR_ENTRY_NODEF10(40),
		ERROR_ENTRY_NODEF10(50),	ERROR_ENTRY_NODEF10(60),	ERROR_ENTRY_NODEF10(70),
		ERROR_ENTRY_NODEF10(80),	ERROR_ENTRY_NODEF10(90),

		ERROR_ENTRY(100, "�������� -in ������ ���� �����"),

		ERROR_ENTRY_NODEF(101),		ERROR_ENTRY_NODEF(102),		ERROR_ENTRY_NODEF(103),

		ERROR_ENTRY(104, "��������� ����� �������� ���������"),

		ERROR_ENTRY_NODEF(105),		ERROR_ENTRY_NODEF(106),		ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),		ERROR_ENTRY_NODEF(109),

		ERROR_ENTRY(110, "������ ��� �������� ����� � �������� ����� (-in)"),
		ERROR_ENTRY(111, "������������ ������ � �������� ���� (-in)"),
		ERROR_ENTRY(112, "������ ��� �������� ����� ��������� (-log)"),
		ERROR_ENTRY(113, "����, ���������� ��� -in:, ����"),
		ERROR_ENTRY_NODEF(114),
		ERROR_ENTRY_NODEF(115),

		//------------------LEXICAL ANALYSE
		ERROR_ENTRY(116, "������������� �� ����� ��������� � ������ ��������� �����"),
		ERROR_ENTRY(117, "���-�� ����������� � ����������� �������� ������ �� ���������"),
		ERROR_ENTRY(118, "�������� ���������� �������"),
		ERROR_ENTRY(119, "�������� ���������� ��������� �������"),
		ERROR_ENTRY(120, "������� ������ �����������"),
		ERROR_ENTRY(121, "������������ ���������� ��������������"),
		ERROR_ENTRY(122, "������� ��������������� �����������"),
		ERROR_ENTRY(123, "��������������� ��������������"),
		ERROR_ENTRY(124, "������������� �������������� ��������������"),
		ERROR_ENTRY(125, "�� ������� ������� ���� � ���������(��� ����������������)"),
		ERROR_ENTRY(126, "������� ������� �������"),
		ERROR_ENTRY(127, "������� ���������� ���������� �������� � ���������� ���� integer"), 
		ERROR_ENTRY(128, "������� ������� ��� ��������������"),
		ERROR_ENTRY(129, "������� ���������� �������������� �������� � ���������� ���� string"), 
		ERROR_ENTRY(130, "��������� ����������� ������� ������� main"),
		ERROR_ENTRY(131, "����������� ������� � ����� �������������"),
		ERROR_ENTRY(132, "������� ������� �������� �������������� ��������"),
		ERROR_ENTRY(133, "�� ��������� ������� ������� main"),
		//------------------LEXICAL ANALYSE

		//------------------POLISH NOTATION
		ERROR_ENTRY(134, "���-�� �������� ������ ���� ������ ���-�� ���������"),
		ERROR_ENTRY(135, "���-�� ����������� �������� �� ��������� � ���-��� �����������"),
		ERROR_ENTRY(136, "�������������� ������ ������� ��������"),
		ERROR_ENTRY(137, "�������� ��������� ()"),
		ERROR_ENTRY(138, "������� ������� ������ ������� - ( , ����� - )"),
		ERROR_ENTRY(139, "��������� �� ����� ���������� � ��������"),
		ERROR_ENTRY(140, "������������ ������ � ���������"),
		ERROR_ENTRY(141, "�������� ���� �������� ����� �������"),
		ERROR_ENTRY(142, "��������� �����������: �������-��������"),
		ERROR_ENTRY_NODEF(143),
		ERROR_ENTRY_NODEF(144),
		ERROR_ENTRY_NODEF(145),
		ERROR_ENTRY_NODEF(146),
		ERROR_ENTRY_NODEF(147),
		ERROR_ENTRY_NODEF(148),
		ERROR_ENTRY_NODEF(149),
		//------------------POLISH NOTATION
		ERROR_ENTRY_NODEF10(150),
		//------------------SYNTAX ANAL
		ERROR_ENTRY(160, "�������� ��������� ��������"),
		ERROR_ENTRY_NODEF(161, "��������� ��������"),
		ERROR_ENTRY_NODEF(162, "������ � ���������"),
		ERROR_ENTRY_NODEF(163, "������ � ���������� �������"),
		ERROR_ENTRY_NODEF(164, "������ � ���������� ���������� �������"),
		ERROR_ENTRY_NODEF(165),
		ERROR_ENTRY_NODEF(166),
		ERROR_ENTRY_NODEF(167),
		ERROR_ENTRY_NODEF(168),
		ERROR_ENTRY_NODEF(169),
		//------------------SYNTAX ANAL
		ERROR_ENTRY_NODEF10(170),	ERROR_ENTRY_NODEF10(180),	ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200),	ERROR_ENTRY_NODEF100(300),	ERROR_ENTRY_NODEF100(400),
		ERROR_ENTRY_NODEF100(500),	ERROR_ENTRY_NODEF100(600),	ERROR_ENTRY_NODEF100(700),
		ERROR_ENTRY_NODEF100(800),	ERROR_ENTRY_NODEF100(900)
	};

	ERROR geterror(int id)
	{
		if (0 < id < ERROR_MAX_ENTRY)
			return errors[id];
		else
			return ERROR_ENTRY(0, "");
	}

	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		ERROR e;

		if (0 < id < ERROR_MAX_ENTRY)
		{
			e = errors[id];
			e.errorPosition.col = col;
			e.errorPosition.line = line;
			return e;
		}
		else
			return ERROR_ENTRY(0, "");
	}
}