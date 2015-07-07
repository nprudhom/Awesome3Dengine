#include "stdafx.h"
#include "3DEngine.h"
#include "LoggerInterface.h"
#include <fstream>

using namespace std;

//----------------------------------------------------------
// Dans la fen�tre de debug
//----------------------------------------------------------
class CLoggerDebug : public ILogger
{
	virtual void Write(const string& Message)
	{
		OutputDebugString((LPCTSTR)(Message + '\n').c_str());
	}
};

//----------------------------------------------------------
// Dans des bo�tes de dialogue
//----------------------------------------------------------
class CLoggerMsgBox : public ILogger
{
	virtual void Write(const string& Message)
	{
		MessageBox(NULL, (LPTSTR)(Message.c_str()), L"Yes::Engine", MB_OK);
	}
};


//----------------------------------------------------------
// Dans un fichier
//----------------------------------------------------------
class CLoggerFile : public ILogger
{
private :
	ofstream m_File;

public:

	CLoggerFile(const string& Filename = "Output.log") : m_File(Filename)
	{

	}

private:

	virtual void Write(const string& Message)
	{
		m_File << Message;
	}

};