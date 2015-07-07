#include "stdafx.h"
#include "3DEngine.h"
#include "Config/Export.h"
#include <string>

using namespace std;
namespace yes
{
	class YES_EXPORT ILogger
	{
	public:

		//----------------------------------------------------------
		// Destructeur
		//----------------------------------------------------------
		virtual ~ILogger();

		//----------------------------------------------------------
		// Change l'instance du logger
		//----------------------------------------------------------
		static void SetLogger(ILogger* Logger);

		//----------------------------------------------------------
		// Log un message (fa�on C)
		//----------------------------------------------------------
		static void Log(const char* Format, ...);

		//----------------------------------------------------------
		// Log un message (fa�on C++)
		//----------------------------------------------------------
		static ILogger& Log();
		template <class T> ILogger& operator <<(const T& ToLog);

	private:

		//----------------------------------------------------------
		// Inscrit un message - � red�finir dans les classes d�riv�es
		//----------------------------------------------------------
		virtual void Write(const std::string& Message) = 0;

		//----------------------------------------------------------
		// Donn�es membres
		//----------------------------------------------------------
		static ILogger* s_Instance; // Pointeur sur le logger actuel

		//----------------------------------------------------------
		// Loggage
		//----------------------------------------------------------

		template <class T> ILogger& ILogger::operator <<(const T& ToLog)
		{
			ostringstream Stream;
			Stream << ToLog;
			Write(Stream.str());

			// On n'oublie pas de toujours renvoyer notre instance, pour pouvoir cha�ner les appels � <<
			return Log();
		}
	};
}
