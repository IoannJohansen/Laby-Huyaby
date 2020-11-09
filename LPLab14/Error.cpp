#include "Error.h"

namespace Error
{
	// серии ошибок: 0-99 - системные ошибки
	//				 100-109 - ошибки параметров
	//				 110-119 - ошибки открытия и чтения файлов
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"),
		ERROR_ENTRY(1, "Системный сбой"),

		ERROR_ENTRY_NODEF(2),		ERROR_ENTRY_NODEF(3),		ERROR_ENTRY_NODEF(4),
		ERROR_ENTRY_NODEF(5),		ERROR_ENTRY_NODEF(6),		ERROR_ENTRY_NODEF(7),
		ERROR_ENTRY_NODEF(8),		ERROR_ENTRY_NODEF(9),		ERROR_ENTRY_NODEF10(10),
		ERROR_ENTRY_NODEF10(20),	ERROR_ENTRY_NODEF10(30),	ERROR_ENTRY_NODEF10(40),
		ERROR_ENTRY_NODEF10(50),	ERROR_ENTRY_NODEF10(60),	ERROR_ENTRY_NODEF10(70),
		ERROR_ENTRY_NODEF10(80),	ERROR_ENTRY_NODEF10(90),

		ERROR_ENTRY(100, "Параметр -in должен быть задан"),

		ERROR_ENTRY_NODEF(101),		ERROR_ENTRY_NODEF(102),		ERROR_ENTRY_NODEF(103),

		ERROR_ENTRY(104, "Превышена длина входного параметра"),

		ERROR_ENTRY_NODEF(105),		ERROR_ENTRY_NODEF(106),		ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),		ERROR_ENTRY_NODEF(109),

		ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном коде (-in)"),
		ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113, "Файл, переданный как -in:, пуст"),
		ERROR_ENTRY_NODEF(114),
		ERROR_ENTRY_NODEF(115),

		//------------------LEXICAL ANALYSE
		ERROR_ENTRY(116, "Идентификатор не может совпадать с именем ключевого слова"),
		ERROR_ENTRY(117, "Кол-во открывающих и закрывающих фигурных скобок не совпадает"),
		ERROR_ENTRY(118, "Неверное объявление функции"),
		ERROR_ENTRY(119, "Неверное объявление параметра функции"),
		ERROR_ENTRY(120, "Таблица лексем переполнена"),
		ERROR_ENTRY(121, "Неправильное объявление идентификатора"),
		ERROR_ENTRY(122, "Таблица идентификаторов переполнена"),
		ERROR_ENTRY(123, "Переопределение идентификатора"),
		ERROR_ENTRY(124, "Использование необъявленного идентификатора"),
		ERROR_ENTRY(125, "Не удалось создать файл с лексемами(или идентификаторами)"),
		ERROR_ENTRY(126, "Слишком длинный литерал"),
		ERROR_ENTRY(127, "Попытка присвоения строкового литерала в переменную типа integer"), 
		ERROR_ENTRY(128, "Слишком большое имя идентификатора"),
		ERROR_ENTRY(129, "Попытка присвоения целочисленного литерала в переменную типа string"), 
		ERROR_ENTRY(130, "Повторное определение главной функций main"),
		ERROR_ENTRY(131, "Запрещенные символы в имени идетификатора"),
		ERROR_ENTRY(132, "Слишком большое значение целочисленного литерала"),
		ERROR_ENTRY(133, "Не объявлена главная функция main"),
		//------------------LEXICAL ANALYSE

		//------------------POLISH NOTATION
		ERROR_ENTRY(134, "Кол-во операции должно быть меньше кол-ва операндов"),
		ERROR_ENTRY(135, "Кол-во открывающих скобочек не совпадает с кол-вом закрывающих"),
		ERROR_ENTRY(136, "Результирующая строка длиннее исходной"),
		ERROR_ENTRY(137, "Неверное выражение ()"),
		ERROR_ENTRY(138, "Нарушен порядок скобок сначала - ( , потом - )"),
		ERROR_ENTRY(139, "Выражение не может начинаться с операции"),
		ERROR_ENTRY(140, "Недопустимый символ в выражений"),
		ERROR_ENTRY(141, "Пропущен знак операции перед скобкой"),
		ERROR_ENTRY(142, "Нарушение чередования: операнд-операция"),
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
		ERROR_ENTRY(160, "Неверная структура прграммы"),
		ERROR_ENTRY_NODEF(161, "Оишбочный оператор"),
		ERROR_ENTRY_NODEF(162, "Ошибка в выражении"),
		ERROR_ENTRY_NODEF(163, "Ошибка в параметрах функции"),
		ERROR_ENTRY_NODEF(164, "Ошибка в параметрах вызываемой функции"),
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