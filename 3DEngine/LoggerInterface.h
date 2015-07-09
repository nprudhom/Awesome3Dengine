#include "stdafx.h"
#include "3DEngine.h"
#include "Config/Export.h"
#include <string>

using namespace std;
namespace Yes
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
		// Log un message (façon C)
		//----------------------------------------------------------
		static void Log(const char* Format, ...);

		//----------------------------------------------------------
		// Log un message (façon C++)
		//----------------------------------------------------------
		static ILogger& Log();
		template <class T> ILogger& operator <<(const T& ToLog);

		string CurrentDate() const;

		string CurrentTime() const;

	private:

		//----------------------------------------------------------
		// Inscrit un message - à redéfinir dans les classes dérivées
		//----------------------------------------------------------
		virtual void Write(const std::string& Message) = 0;

		//----------------------------------------------------------
		// Détruit l'instance du logger
		//----------------------------------------------------------
		static void Destroy();

		//----------------------------------------------------------
		// Données membres
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

			// On n'oublie pas de toujours renvoyer notre instance, pour pouvoir chaîner les appels à <<
			return Log();
		}
	};
}
