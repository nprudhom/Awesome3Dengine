#include "stdafx.h"
#include "3DEngine.h"
#include "Exceptions.h"
#include "LoggerInterface.h"
#include <fstream>
#include <ctime>

using namespace std;

namespace Yes
{
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
	private:
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

	ILogger* ILogger::s_Instance = NULL;

	////////////////////////////////////////////////////////////
	// Destructeur
	//
	////////////////////////////////////////////////////////////
	ILogger::~ILogger()
	{

	}


	////////////////////////////////////////////////////////////
	// Change l'instance du logger
	// L'instance pass� ici sera d�truite par le Logger, elle doit
	// don avoir �t� allou�e dynamiquement
	//
	// [in] Logger : Nouveau logger
	//
	////////////////////////////////////////////////////////////
	void ILogger::SetLogger(ILogger* Logger)
	{
		Destroy();
		s_Instance = Logger;
	}


	////////////////////////////////////////////////////////////
	// D�truit l'instance du logger
	//
	////////////////////////////////////////////////////////////
	void ILogger::Destroy()
	{
		delete s_Instance;
		s_Instance = NULL;
	}


	////////////////////////////////////////////////////////////
	// Log un message
	//
	// [in] sFormat : Format du message � logger
	// [in] ... :     Param�tres optionnels
	//
	////////////////////////////////////////////////////////////
	void ILogger::Log(const char* Format, ...)
	{
		Assert(s_Instance != NULL);

		// Formatage du message dans une cha�ne de caract�re
		char sBuffer[512];
		va_list Params;
		va_start(Params, Format);
		vsprintf_s(sBuffer, Format, Params);
		va_end(Params);

		// Loggization
		s_Instance->Write(sBuffer);
	}


	////////////////////////////////////////////////////////////
	// Renvoie l'instance du logger
	// Utilis� pour logger � la fa�on C++ avec l'op�rateur <<
	//
	// Ex : ILogger::Log() << 5 << "hehe" << v
	//
	// [retval] R�f�rence sur l'instance du logger
	//
	////////////////////////////////////////////////////////////
	ILogger& ILogger::Log()
	{
		return *s_Instance;
	}


	////////////////////////////////////////////////////////////
	// Renvoie la date courante
	//
	// [retval] Date courante sous forme de cha�ne de caract�res
	//
	////////////////////////////////////////////////////////////
	string ILogger::CurrentDate() const
	{
		// R�cup�ration et formatage de la date
		char sTime[24];
		const time_t CurrentTime = time(NULL);
		struct tm timeinfo;
		localtime_s(&timeinfo, &CurrentTime);
		strftime(sTime, sizeof(sTime), "%d/%m/%Y", &timeinfo);

		return sTime;
	}


	////////////////////////////////////////////////////////////
	// Renvoie l'heure courante
	//
	// [retval] Heure courante sous forme de cha�ne de caract�res
	//
	////////////////////////////////////////////////////////////
	string ILogger::CurrentTime() const
	{
		// R�cup�ration et formatage de la date
		char sTime[24];
		time_t CurrentTime = time(NULL);
		struct tm timeinfo;
		localtime_s(&timeinfo, &CurrentTime);
		strftime(sTime, sizeof(sTime), "%H:%M:%S", &timeinfo);

		return sTime;
	}

}