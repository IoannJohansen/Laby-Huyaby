#include <iostream>
#include <ctime>
#include "Parm.h"
#include "Log.h"

namespace Log
{
	LOG getlog(wchar_t logfile[])
	{
		LOG log;
		log.stream = new ofstream;
		log.stream->open(logfile);
		if (!log.stream->is_open()) { throw ERROR_THROW(112) };
		wcscpy_s(log.logfile, logfile);
		return log;
	}

	void WriteLine(LOG log, const char* c, ...)
	{
		const char** pc = &c;
		while (*pc != "")
		{
			*log.stream << *pc;
			pc++;
		}
		*log.stream << endl;
	}

	void WriteLine(LOG log, const wchar_t* c, ...)
	{
		const wchar_t** pc = &c;
		while (*pc != L"")
		{
			const int SIZE = 10;
			char buff[SIZE];
			size_t tsize = 0;
			wcstombs_s(&tsize, buff, *pc, SIZE);
			*log.stream << buff;
			pc++;
		}
		*log.stream << endl;
	}

	void WriteLog(LOG log)
	{
		char date[100];
		tm local;
		time_t currentTime;
		currentTime = time(NULL);
		localtime_s(&local, &currentTime);	//������� ��������� �����, �������������� � ���������
		strftime(date, 100, "%d.%m.%Y %A %H:%M:%S\n", &local);
		*log.stream << "-----��������----- " << endl << "����: " << date << endl;
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		char buff[PARM_MAX_SIZE];
		size_t tsize = 0;

		*log.stream << "---���������---" << endl;

		wcstombs_s(&tsize, buff, parm.in, PARM_MAX_SIZE);
		*log.stream << "-in: " << buff << endl;

		wcstombs_s(&tsize, buff, parm.out, PARM_MAX_SIZE);
		*log.stream << "-out: " << buff << endl;

		wcstombs_s(&tsize, buff, parm.log, PARM_MAX_SIZE);
		*log.stream << "-log: " << buff << endl << endl;
	}

	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "-----�������� ������----- " << endl;
		*log.stream << "���������� ��������: " << in.size << endl;
		*log.stream << "���������� �����: " << in.lines << endl;
		*log.stream << "���������������: " << in.ignor << endl;
	}

	void WriteError(LOG log, Error::ERROR error)
	{
		cout << "������!" << endl;
		cout << "������ " << error.id << ':' << error.message << endl;
		*log.stream << "������ " << error.id << ':' << error.message << endl;
		if (error.errorPosition.line != -1)
		{
			*log.stream << "������ " << error.errorPosition.line << " | " << "�������: " << error.errorPosition.col << endl;
			cout << "������ " << error.errorPosition.line << " | " << "�������: " << error.errorPosition.col << endl;
		}
	}

	void Close(LOG log)
	{
		log.stream->close();
		delete log.stream;
	}
}