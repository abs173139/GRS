#pragma once

#ifndef GRSStdAfx_h
#define GRSStdAfx_h

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <stdio.h>
#include <tchar.h>


// Open Mesh

#pragma warning (disable : 4267 ) // TODO: remove
#pragma warning (disable : 4244 ) // TODO: remove
#define _USE_MATH_DEFINES

#include <iostream>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Utils/Property.hh>

#pragma warning (default : 4267 )
#pragma warning (default : 4244 )

#endif // GRSStdAfx_h
