#pragma once
#include "EC3D/Common/Config.h"

namespace ec
{
	#ifdef EC3D_DLL_EXPORT
	#define EC3D_DECLSPEC __declspec(dllexport)
	#endif
	#ifdef EC3D_DLL_IMPORT
	#define EC3D_DECLSPEC __declspec(dllimport)
	#endif

	#ifndef EC3D_DECLSPEC
	#define EC3D_DECLSPEC
	#endif
}