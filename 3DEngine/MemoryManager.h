#include "stdafx.h"
#include "Config/Export.h"
#include "File.h"
#include <fstream>
#include <map>
#include <stack>


namespace Yes
{
	class YES_EXPORT CMemoryManager
	{
	public:
		static CMemoryManager& Instance();

		void* Allocate(size_t Size, const CFile& File, int Line, bool Array);

		void Free(void* Ptr, bool Array);

		void NextDelete(const CFile& File, int Line);

	private :
		CMemoryManager();

		~CMemoryManager();

		void ReportLeaks();

		struct TBlock
		{
			size_t Size;
			CFile File;
			int Line;
			bool Array;
		};

		typedef map<void*, TBlock> TBlockMap;

		ofstream m_File;
		TBlockMap m_Blocks;
		stack<TBlock> m_DeleteStack;
	};
}