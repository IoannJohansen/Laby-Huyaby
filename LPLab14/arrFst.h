#pragma once
#include "stdafx.h"
#define fstCount 6

#pragma region FSTs

#define A_FUNCTION(string) string, 9,			  \
			FST::NODE(1, FST::RELATION('f', 1)),  \
			FST::NODE(1, FST::RELATION('u', 2)),  \
			FST::NODE(1, FST::RELATION('n', 3)),  \
			FST::NODE(1, FST::RELATION('c', 4)),  \
			FST::NODE(1, FST::RELATION('t', 5)),  \
			FST::NODE(1, FST::RELATION('i', 6)),  \
			FST::NODE(1, FST::RELATION('o', 7)),  \
			FST::NODE(1, FST::RELATION('n', 8)),  \
			FST::NODE()		

#define A_INTEGER(string) string, 8,\
			FST::NODE(1, FST::RELATION('i', 1)),\
			FST::NODE(1, FST::RELATION('n', 2)),\
			FST::NODE(1, FST::RELATION('t', 3)),\
			FST::NODE(1, FST::RELATION('e', 4)),\
			FST::NODE(1, FST::RELATION('g', 5)),\
			FST::NODE(1, FST::RELATION('e', 6)),\
			FST::NODE(1, FST::RELATION('r', 7)),\
			FST::NODE()

#define A_DECLARE(string) string, 8,\
			FST::NODE(1, FST::RELATION('d', 1)),\
			FST::NODE(1, FST::RELATION('e', 2)),\
			FST::NODE(1, FST::RELATION('c', 3)),\
			FST::NODE(1, FST::RELATION('l', 4)),\
			FST::NODE(1, FST::RELATION('a', 5)),\
		    FST::NODE(1, FST::RELATION('r', 6)),\
			FST::NODE(1, FST::RELATION('e', 7)),\
			FST::NODE()

#define A_RETURN(string) string, 7,\
			FST::NODE(1, FST::RELATION('r', 1)),\
			FST::NODE(1, FST::RELATION('e', 2)),\
			FST::NODE(1, FST::RELATION('t', 3)),\
			FST::NODE(1, FST::RELATION('u', 4)),\
			FST::NODE(1, FST::RELATION('r', 5)),\
			FST::NODE(1, FST::RELATION('n', 6)),\
			FST::NODE()


#define A_STRING(string) string, 7,				  \
			FST::NODE(1, FST::RELATION('s', 1)),  \
			FST::NODE(1, FST::RELATION('t', 2)),  \
			FST::NODE(1, FST::RELATION('r', 3)),  \
			FST::NODE(1, FST::RELATION('i', 4)),  \
			FST::NODE(1, FST::RELATION('n', 5)),  \
			FST::NODE(1, FST::RELATION('g', 6)),  \
			FST::NODE()	

#define A_PRINT(string) string, 6,				  \
			FST::NODE(1, FST::RELATION('p', 1)),  \
			FST::NODE(1, FST::RELATION('r', 2)),  \
			FST::NODE(1, FST::RELATION('i', 3)),  \
			FST::NODE(1, FST::RELATION('n', 4)),  \
			FST::NODE(1, FST::RELATION('t', 5)),  \
			FST::NODE()

#define A_INTEGER_LITERAL(string) string, 1,	\
	FST::NODE(10,	FST::RELATION('0', 0),	\
					FST::RELATION('1', 0),	\
					FST::RELATION('2', 0),	\
					FST::RELATION('3', 0),	\
					FST::RELATION('4', 0),	\
					FST::RELATION('5', 0),	\
					FST::RELATION('6', 0),	\
					FST::RELATION('7', 0),	\
					FST::RELATION('8', 0),	\
					FST::RELATION('9', 0)),	\
	FST::NODE()



#pragma endregion