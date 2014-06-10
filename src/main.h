/*
* Copyright (C) 2014 Declan Ireland <http://github.com/torndeco/extDB>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/


#pragma once

#ifdef __GNUC__  
	// Code for GNU C compiler
	static void __attribute__((constructor))
	extension_init(void)
	{
		std::cout << "library init" << std::endl;
		init();
	}

	static void __attribute__((destructor))
	extension_destroy(void)
	{
		std::cout << "library destroy" << std::endl;
	}

	extern "C"
	{
	  void RVExtension(char *output, int outputSize, const char *function); 
	};

	void RVExtension(char *output, int outputSize, const char *function)
	{
	  outputSize -= 1;
	  std::strncpy(output,function,outputSize);
	}

#elif _MSC_VER
	// Code for MSVC compiler
	#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
	#include <windows.h>

	BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
	{
		switch (ul_reason_for_call)
		{
		case DLL_PROCESS_ATTACH:
			init();
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
		}
		return TRUE;
	}

	extern "C"
	{
	  __declspec(dllexport) void __stdcall RVExtension(char *output, int outputSize, const char *function); 
	};

	void __stdcall RVExtension(char *output, int outputSize, const char *function)
	{
	  outputSize -= 1;
	  std::strncpy(output,function,outputSize);
	}

#elif __MINGW32__
// Code for MINGW32 compiler
// Someone figure this out thanks...
#endif