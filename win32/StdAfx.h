// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__90096E0E_C105_11D2_98BC_00104B0D20F9__INCLUDED_)
#define AFX_STDAFX_H__90096E0E_C105_11D2_98BC_00104B0D20F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#include <htmlhelp.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include "Structs.h"

#ifdef DEBUG
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_CHECK_CRT
#include <CRTDBG.H>
#endif

#include "globals.h" 

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

/*	#define _ATL_APARTMENT_THREADED
#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
class CGrphCalcModule : public CComModule
{
public:
	LONG Unlock();
	LONG Lock();
	LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2);
	DWORD dwThreadID;
};
extern CGrphCalcModule _Module;
#include <atlcom.h>
*/

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__90096E0E_C105_11D2_98BC_00104B0D20F9__INCLUDED_)
