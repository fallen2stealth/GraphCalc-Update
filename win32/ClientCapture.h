/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 by Andrew Bryan
// All rights reserved
//
// Send bug reports, bug fixes, enhancements, requests, etc. to:
//    abtb@ix.netcom.com
/////////////////////////////////////////////////////////////////////////////
//
// ClientCapture.h : interface of the CClientCapture class
//
// Much of this code is altered cut and pastes of other people's
// source (where they got them...I don't know but have seen very
// similar pieces from Microsoft).
//	
// I cannot find the original code pieces but I do know the one 
// author from which I used code is Zafir Anjum.
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTCAPTURE_H__F3017F4D_3A97_11D2_9506_F6C490433B31__INCLUDED_)
#define AFX_CLIENTCAPTURE_H__F3017F4D_3A97_11D2_9506_F6C490433B31__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CClientCapture 
{
public: // create from serialization only
	CClientCapture();
	~CClientCapture();
// Operations
public:
	void Release();
	BOOL WriteDIB( CString csFile);
	void OnDraw(HDC hDC, CRect rcRect, CRect rect);

	BOOL DrawBitmap(CDC *dc, HDC hDC, CRect *rect, CRect *dest, CBitmap &bitmap);

	BOOL Paint(HDC hDC, CPalette *pal, LPRECT lpDCRect, LPRECT lpDIBRect) const;
	void Capture(CDC *dc, CRect rectDIB);


	BOOL WriteBitmapToDIB(CDC* dc, CBitmap &bitmap);

private:
	
	int DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal, CDC* dc, int start, int lines);
	HANDLE DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal, CDC* dc);

	DWORD Height() const;
	BOOL WriteWindowToDIB( HDC hDC, CDC* dc, CRect rect);

	BOOL WriteWindowToDIB(CDC* dc, CRect rect);

	LPBITMAPINFO m_pBMI;
	LPBYTE 	m_pBits;
	HANDLE hDIB;
	CPalette pal;
	LPBITMAPINFOHEADER 	lpbi;
	

};

/////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_CLIENTCAPTURE_H__F3017F4D_3A97_11D2_9506_F6C490433B31__INCLUDED_)



