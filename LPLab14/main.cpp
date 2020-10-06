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
		Log::WriteLog(log);
		Log::WriteParm(log, param);
		In::IN in = In::getin(param.in);
		Out::OUT out = Out::getout(param.out, in);
		Log::WriteIn(log, in);
		Out::preparationForOut(&out);
		Lex::textDivision(out);
		Out::writeInsideTextTo_OutFile(out, param);
		Log::Close(log);
		Out::CloseOut(out);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
		Log::Close(log);
	}
	system("pause");
	return 0;
}