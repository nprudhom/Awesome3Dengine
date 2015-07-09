#include "stdafx.h"
#include "MemoryManager.h"
#include "Exceptions.h"
#include <sstream>
#include <iomanip>

using namespace std;

namespace Yes
{
	CMemoryManager::CMemoryManager() : m_File("MemoryLeaks.log")
	{
		if (!m_File)
			throw CLoadingFailed("Memory leaks.log", "Impossible d'accéder en écriture");

		m_File << "  ========================================" << endl;
		m_File << "     Engine v0.1 - Memory leak tracker    " << endl;
		m_File << "  ========================================" << endl << endl;
	}
	CMemoryManager& CMemoryManager::Instance()
	{
		static CMemoryManager Inst;
		return Inst;
	}

	CMemoryManager::~CMemoryManager()
	{
		if (m_Blocks.empty())
		{
			// Aucune fuite, bravo !
			m_File << endl;
			m_File << "  ========================================" << endl;
			m_File << "     No leak detected, congratulations !  " << endl;
			m_File << "  ========================================" << endl;
		}
		else
		{
			// Fuites mémoires =(
			m_File << endl;
			m_File << "  ========================================" << endl;
			m_File << "   Oops... Some leaks have been detected  " << endl;
			m_File << "  ========================================" << endl;
			m_File << endl;

			ReportLeaks();
		}
	}

	void CMemoryManager::ReportLeaks()
	{
		// Détail des fuites
		size_t TotalSize = 0;
		for (TBlockMap::iterator i = m_Blocks.begin(); i != m_Blocks.end(); ++i)
		{
			// Ajout de la taille du bloc au cumul
			TotalSize += i->second.Size;

			// Inscription dans le fichier des informations sur le bloc courant
			m_File << "-> 0x" << i->first
				<< " | " << setw(7) << setfill(' ') << static_cast<int>(i->second.Size) << " octets"
				<< " | " << i->second.File.Filename() << " (" << i->second.Line << ")" << endl;

			// Libération de la mémoire
			free(i->first);
		}

		// Affichage du cumul des fuites
		m_File << endl << endl << "-- "
			<< static_cast<int>(m_Blocks.size()) << " blocs non-libéré(s), "
			<< static_cast<int>(TotalSize) << " octets --"
			<< endl;
	}
}