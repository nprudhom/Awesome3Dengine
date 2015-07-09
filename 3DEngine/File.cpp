#include "stdafx.h"
#include "File.h"
#include <algorithm>
#include <fstream>

namespace Yes
{
	CFile::CFile(const string& Name) : m_Name(Name)
	{
		replace(m_Name.begin(), m_Name.end(), '/', '\\');
	}

	CFile::CFile(const char* Name) : m_Name(Name)
	{
		replace(m_Name.begin(), m_Name.end(), '/', '\\');
	}

	bool CFile::Exists() const
	{
		ifstream File(m_Name.c_str());

		return File.is_open();
	}

	const string& CFile::Fullname() const
	{
		return m_Name;
	}

	string CFile::Filename() const
	{
		string::size_type Pos = m_Name.find_last_of("\\/");

		if (Pos != string::npos)
			return m_Name.substr(Pos + 1, string::npos);
		else
			return m_Name;
	}

	string CFile::ShortFilename() const
	{
		return Filename().substr(0, Filename().find_last_of("."));
	}

	string CFile::Extension() const
	{
		string::size_type Pos = m_Name.find_last_of(".");
		if (Pos != string::npos)
			return m_Name.substr(Pos + 1, string::npos);
		else
			return "";
	}
}