#include "stdafx.h"
using namespace std;

int wmain(int argc, wchar_t* argv[])
{
	Log::LOG log = Log::INITLOG;
	setlocale(LC_ALL, "Russian");
	try
	{
		Parm::PARM param = Parm::getparm(argc, argv);
		Out::clearOutFile(param.out);
		log = Log::getlog(param.log);
		In::IN in = In::getin(param.in);
		Out::OUT out = Out::getout(param.out, in);
		Out::preparationForOut(&out);
		Out::writeInsideTextTo_OutFile(out, param);

		//-------LEX ANALYSE-------
		Lex::Tables tables = Lex::lexAnalyse(out);
		//-------------------------

		//-------SYNTAX ANALYSE----
		/*MFST_TRACE_START;
		MFST::Mfst mfst(tables, GRB::getGreibach());
		mfst.start();*/
		//-------------------------
		
		//-------POLISH NOTATION---
		Polska::findForExpressions(tables.lexTable, tables.idenTable);
		//-------------------------

		Log::WriteLog(log);
		Log::WriteParm(log, param);
		Log::WriteIn(log, in);
		Lex::outLexAndIdenTables(param.in, tables);
		Log::Close(log);
		Out::CloseOut(out);
		LT::Delete(tables.lexTable);
		IT::Delete(tables.idenTable);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
		Log::Close(log);
	}
	system("pause");
	return 0;
}