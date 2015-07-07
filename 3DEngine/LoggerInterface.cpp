#include "stdafx.h"
#include "3DEngine.h"
#include <string>

using namespace std;

class ILogger
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

private:

	//----------------------------------------------------------
	// Inscrit un message - à redéfinir dans les classes dérivées
	//----------------------------------------------------------
	virtual void Write(const std::string& Message) = 0;

	//----------------------------------------------------------
	// Données membres
	//----------------------------------------------------------
	static ILogger* s_Instance; // Pointeur sur le logger actuel
};