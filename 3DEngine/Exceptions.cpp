#include "stdafx.h"
#include "Exceptions.h"
#include <sstream>

using namespace std;

namespace Yes
{

	////////////////////////////////////////////////////////////
	// Constructeur
	//
	// [in] Message : Message d'erreur
	//
	////////////////////////////////////////////////////////////
	CException::CException(const std::string& Message) :
		m_Message(Message)
	{

	}


	////////////////////////////////////////////////////////////
	// Destructeur
	//
	////////////////////////////////////////////////////////////
	CException::~CException()
	{

	}


	////////////////////////////////////////////////////////////
	// Renvoie le message associé à l'exception
	//
	// [retval] Pointeur sur le message
	//
	////////////////////////////////////////////////////////////
	const char* CException::what() const
	{
		return m_Message.c_str();
	}


	////////////////////////////////////////////////////////////
	// Constructeur
	//
	// [in] File :    Fichier source contenant l'erreur
	// [in] Line :    Ligne à laquelle se trouve l'erreur dans le fichier source
	// [in] Message : Message d'erreur
	//
	////////////////////////////////////////////////////////////
	CAssertException::CAssertException(const std::string& File, int Line, const std::string& Message)
	{
		// Formatage du message d'erreur
		std::ostringstream oss;
		oss << Message << std::endl << std::endl;
		oss << File << " (" << Line << ")";

		m_Message = oss.str();
	}


	////////////////////////////////////////////////////////////
	// Constructeur
	//
	// [in] Ptr :      Adresse du bloc
	// [in] File :     Fichier source
	// [in] Line :     Ligne dan sle fichier source
	// [in] NewArray : Indique si le [] se trouve sur le new ou le delete
	//
	////////////////////////////////////////////////////////////
	CBadDelete::CBadDelete(const void* Ptr, const std::string& File, int Line, bool NewArray)
	{
		// Formatage du message d'erreur
		std::ostringstream oss;
		oss << "Anomalie "
			<< (NewArray ? "new[] / delete" : "new / delete[]")
			<< " detectee" << std::endl << std::endl
			<< "Adresse : 0x" << Ptr << std::endl
			<< "Fichier source : " << File << " (" << Line << ")";

		m_Message = oss.str();
	}


	////////////////////////////////////////////////////////////
	// Constructeur
	//
	// [in] File :    Fichier
	// [in] Message : Message d'erreur
	//
	////////////////////////////////////////////////////////////
	CLoadingFailed::CLoadingFailed(const std::string& File, const std::string& Message)
	{
		// Formatage du message d'erreur
		std::ostringstream oss;
		oss << "Erreur dans le chargement de " << File << std::endl << std::endl << Message;

		m_Message = oss.str();
	}


	////////////////////////////////////////////////////////////
	// Constructeur
	//
	// [in] Message : Message d'erreur
	//
	////////////////////////////////////////////////////////////
	COutOfMemory::COutOfMemory(const std::string& Message) :
		CException(Message)
	{

	}
}