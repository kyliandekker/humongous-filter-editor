#include "lowlevel/utils.h"

#include <string.h>

#include "lowlevel/Defines.h"

namespace HumongousFileEditor
{
	namespace utils
	{
		void* add(void* a_Ptr, size_t a_Size)
		{
			return reinterpret_cast<unsigned char*>(a_Ptr) + a_Size;
		}

		int chunkcmp(unsigned char* chunkID1, const char* chunkID2)
		{
			return strncmp(reinterpret_cast<const char*>(chunkID1), chunkID2, CHUNK_ID_SIZE);
		}

		void reverseBytes(unsigned char* start, int size)
		{
			unsigned char* lo = start;
			unsigned char* hi = start + size - 1;
			unsigned char swap;
			while (lo < hi)
			{
				swap = *lo;
				*lo++ = *hi;
				*hi-- = swap;
			}
		}
	}
}