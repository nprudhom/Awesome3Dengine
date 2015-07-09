#include "stdafx.h"
#include <exception>
#include <string>

using namespace std;

namespace Yes
{
	//==========================================================
	// Classe de base pour les exceptions
	//==========================================================
	class CException : public exception
	{
	public:
		CException(const string& Message = "");

		virtual ~CException();

		//----------------------------------------------------------
		// Renvoie le message associé à l'exception
		//----------------------------------------------------------
		virtual const char* what() const;

	protected:

		//----------------------------------------------------------
		// Données membres
		//----------------------------------------------------------
		string m_Message; // Message associé à l'exception
	};


	//==========================================================
	// Exception lancée si une condition n'est pas vérifiée
	//==========================================================
	struct CAssertException : public CException
	{
		CAssertException(const string& File, int Line, const string& Message);
	};
#ifdef _DEBUG
#   define Assert(condition) if (!(condition)) throw CAssertException(__FILE__, __LINE__, "Condition non satisfaite\n\n" #condition)
#else
	inline void DoNothing(bool) {}
#   define Assert(condition) DoNothing(!(condition))
#endif


	//==========================================================
	// Anomalie d'allocation mémoire
	//==========================================================
	struct CBadDelete : public CException
	{
		CBadDelete(const void* Ptr, const string& File, int Line, bool NewArray);
	};


	//==========================================================
	// Exception lancée lors d'erreur de chargement de fichiers
	//==========================================================
	struct CLoadingFailed : public CException
	{
		CLoadingFailed(const string& File, const string& Message);
	};


	//==========================================================
	// Exception lancée lors de saturations de mémoire
	//==========================================================
	struct COutOfMemory : public CException
	{
		COutOfMemory(const string& Message);
	};

}