#include "stdafx.h"
#include "Config\Export.h"
#include <string>

using namespace std;

namespace Yes
{
	class YES_EXPORT CFile
	{
	public:

		CFile(const string& Name = "unknown");

		CFile(const char* Name);

		bool Exists() const;

		const string& Fullname() const;

		string Filename() const;

		string ShortFilename() const;

		string Extension() const;

	private:
		string m_Name;
	};
}