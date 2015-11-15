/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 by Andrew Bryan
// All rights reserved
//
// Send bug reports, bug fixes, enhancements, requests, etc. to:
//    abtb@ix.netcom.com
//
// Much of this code is altered cut and pastes of other people's
// source (where they got them...I don't know but have seen very
// similar pieces from Microsoft).
//	
// I cannot find the original code pieces but I do know the one 
// author from which I used code is Zafir Anjum.
//
// fixes:
//	9 Dec 98 -- fix for hDIB memory problem of freeing memory
//		    that was not allocated
//
//	9 Dec 98 -- fix as reported by Patrick Monier for saving of
//		    bitmaps with >256 colours
//
/////////////////////////////////////////////////////////////////////////////
//
// ClientCapture.cpp : implementation of the CClientCapture class
//
/////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "ClientCapture.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/* DIB Macros*/
#define RECTWIDTH(lpRect)     ((lpRect)->right - (lpRect)->left)
#define RECTHEIGHT(lpRect)    ((lpRect)->bottom - (lpRect)->top)


/////////////////////////////////////////////////////////////////////////////
// CClientCapture::CClientCapture - Constructor

CClientCapture::CClientCapture()
{
	m_pBMI = 0;
	m_pBits = 0;
	hDIB = 0;
}


/////////////////////////////////////////////////////////////////////////////
// CClientCapture::~CClientCapture - Destructor

CClientCapture::~CClientCapture()
{
	if(hDIB)
		GlobalFree( hDIB );

	hDIB = 0;
	m_pBMI = 0;
	m_pBits = 0;

}



void CClientCapture::Capture(CDC *dc, CRect rectDIB) 
{

	WriteWindowToDIB(dc, rectDIB);

}



BOOL CClientCapture::WriteWindowToDIB( CDC* dc, CRect rect)
{
	CBitmap 	bitmap;
	CDC 		memDC;

	memDC.CreateCompatibleDC(dc); 
	bitmap.CreateCompatibleBitmap(dc, rect.Width(),rect.Height() );
	
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.BitBlt(0, 0, rect.Width(),rect.Height(), dc, 0, 0, SRCCOPY); 

	// Create logical palette if device support a palette
	
	if( dc->GetDeviceCaps(RASTERCAPS) & RC_PALETTE )
	{
		UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * 256);
		LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];
		pLP->palVersion = 0x300;

		pLP->palNumEntries = GetSystemPaletteEntries( *dc, 0, 255, pLP->palPalEntry );

		// Create the palette
		pal.CreatePalette( pLP );

		delete[] pLP;
	}

	memDC.SelectObject(pOldBitmap);

	// Convert the bitmap to a DIB
	hDIB = DDBToDIB( bitmap, BI_RGB, &pal, dc);

	if( hDIB == NULL )
		return FALSE;

	return TRUE;
}

BOOL CClientCapture::WriteBitmapToDIB( CDC* dc, CBitmap &bitmap)
{
	// Create logical palette if device support a palette
	
	if( dc->GetDeviceCaps(RASTERCAPS) & RC_PALETTE )
	{
		UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * 256);
		LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];
		pLP->palVersion = 0x300;

		pLP->palNumEntries = GetSystemPaletteEntries( *dc, 0, 255, pLP->palPalEntry );

		// Create the palette
		pal.CreatePalette( pLP );

		delete[] pLP;
	}

	// Convert the bitmap to a DIB
	hDIB = DDBToDIB(bitmap, BI_RGB, &pal, dc);

	if( hDIB == NULL )
		return FALSE;

	return TRUE;
}


BOOL CClientCapture::Paint(HDC hDC, CPalette * m_pPalette, LPRECT lpDCRect, LPRECT lpDIBRect) const
{

	if (!m_pBMI)
		return FALSE;

	HPALETTE hPal = NULL;           // Our DIB's palette
	HPALETTE hOldPal = NULL;        // Previous palette

	// Get the DIB's palette, then select it into DC
	if (m_pPalette != NULL)
	{
		hPal = (HPALETTE) m_pPalette->m_hObject;

		// Select as background since we have
		// already realized in forground if needed
		hOldPal = ::SelectPalette(hDC, hPal, TRUE);
	}

	/* Make sure to use the stretching mode best for color pictures */
	::SetStretchBltMode(hDC, COLORONCOLOR);

	/* Determine whether to call StretchDIBits() or SetDIBitsToDevice() */
	BOOL bSuccess = FALSE;
	
	if ((RECTWIDTH(lpDCRect)  == RECTWIDTH(lpDIBRect)) &&
		(RECTHEIGHT(lpDCRect) == RECTHEIGHT(lpDIBRect))){
		
				bSuccess = ::SetDIBitsToDevice(hDC,        // hDC		
				lpDCRect->left,             // DestX
				lpDCRect->top,              // DestY
				RECTWIDTH(lpDCRect),        // nDestWidth
				RECTHEIGHT(lpDCRect),       // nDestHeight
				lpDIBRect->left,            // SrcX
				(int)Height() -
				lpDIBRect->top -
				RECTHEIGHT(lpDIBRect),     // SrcY
				0,                          // nStartScan
				(WORD)Height(),             // nNumScans
				m_pBits,                    // lpBits
				m_pBMI,                     // lpBitsInfo
				DIB_RGB_COLORS);            // wUsage

	}
   else
	  bSuccess = ::StretchDIBits(hDC,            // hDC
							   lpDCRect->left,               // DestX
							   lpDCRect->top,                // DestY
							   RECTWIDTH(lpDCRect),          // nDestWidth
							   RECTHEIGHT(lpDCRect),         // nDestHeight
							   lpDIBRect->left,              // SrcX
							   lpDIBRect->top,               // SrcY
							   RECTWIDTH(lpDIBRect),         // wSrcWidth
							   RECTHEIGHT(lpDIBRect),        // wSrcHeight
							   m_pBits,                      // lpBits
							   m_pBMI,                       // lpBitsInfo
							   DIB_RGB_COLORS,               // wUsage
							   SRCCOPY);                     // dwROP

 
	/* Reselect old palette */
	if (hOldPal != NULL)
	{
		::SelectPalette(hDC, hOldPal, TRUE);
	}

   return bSuccess;
}

/*BOOL CClientCapture::Paint(HDC hDC, CPalette * m_pPalette, LPRECT lpDCRect, LPRECT lpDIBRect) const
{

	if (!m_pBMI)
		return FALSE;

	HPALETTE hPal = NULL;           // Our DIB's palette
	HPALETTE hOldPal = NULL;        // Previous palette

	// Get the DIB's palette, then select it into DC
	if (m_pPalette != NULL)
	{
		hPal = (HPALETTE) m_pPalette->m_hObject;

		// Select as background since we have
		// already realized in forground if needed
		hOldPal = ::SelectPalette(hDC, hPal, TRUE);
	}

	// Make sure to use the stretching mode best for color pictures
	::SetStretchBltMode(hDC, COLORONCOLOR);

	// Determine whether to call StretchDIBits() or SetDIBitsToDevice()
	
	BOOL bSuccess = FALSE;
	if ((RECTWIDTH(lpDCRect)  == RECTWIDTH(lpDIBRect)) &&
	   (RECTHEIGHT(lpDCRect) == RECTHEIGHT(lpDIBRect)))
		bSuccess = ::SetDIBitsToDevice(hDC,        // hDC
								   lpDCRect->left,             // DestX
								   lpDCRect->top,              // DestY
								   RECTWIDTH(lpDCRect),        // nDestWidth
								   RECTHEIGHT(lpDCRect),       // nDestHeight
								   lpDIBRect->left,            // SrcX
								   (int)Height() -
									  lpDIBRect->top -
									  RECTHEIGHT(lpDIBRect),     // SrcY
								   0,                          // nStartScan
								   (WORD)Height(),             // nNumScans
								   m_pBits,                    // lpBits
								   m_pBMI,                     // lpBitsInfo
								   DIB_RGB_COLORS);            // wUsage
   else
	  bSuccess = ::StretchDIBits(hDC,            // hDC
							   lpDCRect->left,               // DestX
							   lpDCRect->top,                // DestY
							   RECTWIDTH(lpDCRect),          // nDestWidth
							   RECTHEIGHT(lpDCRect),         // nDestHeight
							   lpDIBRect->left,              // SrcX
							   lpDIBRect->top,               // SrcY
							   RECTWIDTH(lpDIBRect),         // wSrcWidth
							   RECTHEIGHT(lpDIBRect),        // wSrcHeight
							   m_pBits,                      // lpBits
							   m_pBMI,                       // lpBitsInfo
							   DIB_RGB_COLORS,               // wUsage
							   SRCCOPY);                     // dwROP

 
	// Reselect old palette
	if (hOldPal != NULL)
	{
		::SelectPalette(hDC, hOldPal, TRUE);
	}

   return bSuccess;
}*/


// DDBToDIB		- Creates a DIB from a DDB
// bitmap		- Device dependent bitmap
// dwCompression	- Type of compression - see BITMAPINFOHEADER
// pPal			- Logical palette
int CClientCapture::DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal, CDC* dc, int start, int lines)
{
	BITMAP			bm;
	BITMAPINFOHEADER	bi;
	//LPBITMAPINFOHEADER 	lpbi;
	DWORD			dwLen;
	//HANDLE			hDIB;
	HANDLE			handle;
	HDC 			hDC;
	HPALETTE		hPal;

	int lines_read(lines);


	ASSERT( bitmap.GetSafeHandle() );

	// The function has no arg for bitfields
	if( dwCompression == BI_BITFIELDS )
		return NULL;

	// If a palette has not been supplied use defaul palette
	hPal = (HPALETTE) pPal->GetSafeHandle();
	if (hPal==NULL)
		hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);

	// Get bitmap information
	bitmap.GetObject(sizeof(bm),(LPSTR)&bm);

	// Initialize the bitmapinfoheader
	bi.biSize		= sizeof(BITMAPINFOHEADER);
	bi.biWidth		= bm.bmWidth;

	/*if((start + lines) > bm.bmHeight){
		lines_read = bm.bmHeight - start;
		lines = lines_read;
	}

	bi.biHeight = lines;*/
	
	bi.biHeight = bm.bmHeight;

	bi.biPlanes 		= 1;
	bi.biBitCount		= bm.bmPlanes * bm.bmBitsPixel;
	bi.biCompression	= dwCompression;
	bi.biSizeImage		= 0;
	bi.biXPelsPerMeter	= 0;
	bi.biYPelsPerMeter	= 0;
	bi.biClrUsed		= 0;
	bi.biClrImportant	= 0;

	// Compute the size of the  infoheader and the color table
	int nColors = (1 << bi.biBitCount);
	if( nColors > 256 ) 
		nColors = 0;
	dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);

	// We need a device context to get the DIB from
	hDC = dc->GetSafeHdc();

	//hDC = GetDC(NULL);
	hPal = SelectPalette(hDC,hPal,FALSE);
	RealizePalette(hDC);

	
	// Allocate enough memory to hold bitmapinfoheader and color table
	if(hDIB) GlobalFree( hDIB );

	hDIB = GlobalAlloc(GMEM_FIXED,dwLen);

	if (!hDIB){
		SelectPalette(hDC,hPal,FALSE);
		return 0;
	}

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	*lpbi = bi;

	// Call GetDIBits with a NULL lpBits param, so the device driver 
	// will calculate the biSizeImage field 
	GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(), 0L, (DWORD)bi.biHeight,
			(LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

	bi = *lpbi;

	// If the driver did not fill in the biSizeImage field, then compute it
	// Each scan line of the image is aligned on a DWORD (32bit) boundary
	if (bi.biSizeImage == 0){
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) 
						* bi.biHeight;

		// If a compression scheme is used the result may infact be larger
		// Increase the size to account for this.
		if (dwCompression != BI_RGB)
			bi.biSizeImage = (bi.biSizeImage * 3) / 2;
	}

	// Realloc the buffer so that it can hold all the bits
	dwLen += bi.biSizeImage;
	if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		hDIB = handle;
	else{
		GlobalFree(hDIB);
		hDIB = 0;
		// Reselect the original palette
		SelectPalette(hDC,hPal,FALSE);

		return 0;
	}

	// Get the bitmap bits
	lpbi = (LPBITMAPINFOHEADER)hDIB;
	m_pBMI = (LPBITMAPINFO)hDIB;
	m_pBits = (LPBYTE)hDIB + (bi.biSize + nColors * sizeof(RGBQUAD));

	// FINALLY get the DIB
	BOOL bGotBits = GetDIBits( hDC, (HBITMAP)bitmap.GetSafeHandle(),
								start,				// Start scan line
								lines,				// # of scan lines
								(LPBYTE) m_pBits,	//lpbi 			// address for bitmap bits
								(LPBITMAPINFO)lpbi,		// address of bitmapinfo
								(DWORD)DIB_RGB_COLORS);		// Use RGB for color table

	if( !bGotBits )
	{
		GlobalFree(hDIB);
		hDIB = 0;
		SelectPalette(hDC,hPal,FALSE);

		return 0;
	}

	SelectPalette(hDC,hPal,FALSE);

	return lines_read;
}


// DDBToDIB		- Creates a DIB from a DDB
// bitmap		- Device dependent bitmap
// dwCompression	- Type of compression - see BITMAPINFOHEADER
// pPal			- Logical palette
HANDLE CClientCapture::DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal, 	CDC *dc) 
{
	BITMAP			bm;
	BITMAPINFOHEADER	bi;
	//LPBITMAPINFOHEADER 	lpbi;
	DWORD			dwLen;
	//HANDLE			hDIB;
	HANDLE			handle;
	HDC 			hDC;
	HPALETTE		hPal;


	ASSERT( bitmap.GetSafeHandle() );

	// The function has no arg for bitfields
	if( dwCompression == BI_BITFIELDS )
		return NULL;

	// If a palette has not been supplied use defaul palette
	hPal = (HPALETTE) pPal->GetSafeHandle();
	if (hPal==NULL)
		hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);

	// Get bitmap information
	bitmap.GetObject(sizeof(bm),(LPSTR)&bm);

	// Initialize the bitmapinfoheader
	bi.biSize		= sizeof(BITMAPINFOHEADER);
	bi.biWidth		= bm.bmWidth;
	bi.biHeight 		= bm.bmHeight;
	bi.biPlanes 		= 1;
	bi.biBitCount		= bm.bmPlanes * bm.bmBitsPixel;
	bi.biCompression	= dwCompression;
	bi.biSizeImage		= 0;
	bi.biXPelsPerMeter	= 0;
	bi.biYPelsPerMeter	= 0;
	bi.biClrUsed		= 0;
	bi.biClrImportant	= 0;

	// Compute the size of the  infoheader and the color table
	int nColors = (1 << bi.biBitCount);
	if( nColors > 256 ) 
		nColors = 0;
	dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);

	// We need a device context to get the DIB from
	hDC = dc->GetSafeHdc();

	//hDC = GetDC(NULL);
	hPal = SelectPalette(hDC,hPal,FALSE);
	RealizePalette(hDC);

	
	// Allocate enough memory to hold bitmapinfoheader and color table
	if(hDIB) GlobalFree( hDIB );

	hDIB = GlobalAlloc(GMEM_FIXED,dwLen);

	if (!hDIB){
		SelectPalette(hDC,hPal,FALSE);
		return NULL;
	}

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	*lpbi = bi;

	// Call GetDIBits with a NULL lpBits param, so the device driver 
	// will calculate the biSizeImage field 
	GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(), 0L, (DWORD)bi.biHeight,
			(LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

	bi = *lpbi;

	// If the driver did not fill in the biSizeImage field, then compute it
	// Each scan line of the image is aligned on a DWORD (32bit) boundary
	if (bi.biSizeImage == 0){
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) 
						* bi.biHeight;

		// If a compression scheme is used the result may infact be larger
		// Increase the size to account for this.
		if (dwCompression != BI_RGB)
			bi.biSizeImage = (bi.biSizeImage * 3) / 2;
	}

	// Realloc the buffer so that it can hold all the bits
	dwLen += bi.biSizeImage;
	if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		hDIB = handle;
	else{
		GlobalFree(hDIB);
		hDIB = 0;
		// Reselect the original palette
		SelectPalette(hDC,hPal,FALSE);

		return NULL;
	}

	// Get the bitmap bits
	lpbi = (LPBITMAPINFOHEADER)hDIB;
	m_pBMI = (LPBITMAPINFO)hDIB;
	m_pBits = (LPBYTE)hDIB + (bi.biSize + nColors * sizeof(RGBQUAD));

	// FINALLY get the DIB
	BOOL bGotBits = GetDIBits( hDC, (HBITMAP)bitmap.GetSafeHandle(),
				0L,				// Start scan line
				(DWORD)bi.biHeight,		// # of scan lines
				(LPBYTE) m_pBits,//lpbi 			// address for bitmap bits
				(LPBITMAPINFO)lpbi,		// address of bitmapinfo
				(DWORD)DIB_RGB_COLORS);		// Use RGB for color table

	if( !bGotBits )
	{
		GlobalFree(hDIB);
		hDIB = 0;
		SelectPalette(hDC,hPal,FALSE);

		return NULL;
	}

	SelectPalette(hDC,hPal,FALSE);

	return hDIB;
}

DWORD CClientCapture::Height() const
{
	if (!m_pBMI)
		return 0;
	
	/* return the DIB height */
	return m_pBMI->bmiHeader.biHeight;
}


BOOL CClientCapture::DrawBitmap(CDC *dc, HDC hDC, CRect *rect, CRect *dest, CBitmap &bitmap){

	//////////////////////////////////////////////////////
	// Create logical palette if device support a palette
	if( dc->GetDeviceCaps(RASTERCAPS) & RC_PALETTE )
	{
		UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * 256);
		LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];
		pLP->palVersion = 0x300;

		pLP->palNumEntries = GetSystemPaletteEntries( *dc, 0, 255, pLP->palPalEntry );

		// Create the palette
		pal.CreatePalette( pLP );

		delete[] pLP;
	}
	// END CREATE PALETTE
	//////////////////////////////////////////////////////

	/////////////////////////////
	/////////////////////////////
	BITMAP			bm;
	BITMAPINFOHEADER	bi;
	DWORD			dwLen;
	HANDLE			handle;
	HDC 			hPDC;
	HPALETTE		hPal;

	ASSERT( bitmap.GetSafeHandle() );

	// If a palette has not been supplied use defaul palette
	hPal = (HPALETTE) pal.GetSafeHandle();
	if (hPal==NULL)
		hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);

	// Get bitmap information
	bitmap.GetObject(sizeof(bm),(LPSTR)&bm);

	// Initialize the bitmapinfoheader
	bi.biSize		= sizeof(BITMAPINFOHEADER);
	bi.biWidth		= bm.bmWidth;
	bi.biHeight 		= bm.bmHeight;
	bi.biPlanes 		= 1;
	bi.biBitCount		= bm.bmPlanes * bm.bmBitsPixel;
	bi.biCompression	= BI_RGB;
	bi.biSizeImage		= 0;
	bi.biXPelsPerMeter	= 0;
	bi.biYPelsPerMeter	= 0;
	bi.biClrUsed		= 0;
	bi.biClrImportant	= 0;

	// Compute the size of the  infoheader and the color table
	int nColors = (1 << bi.biBitCount);
	if( nColors > 256 ) 
		nColors = 0;
	dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);

	// We need a device context to get the DIB from
	hPDC = dc->GetSafeHdc();

	//hDC = GetDC(NULL);
	hPal = SelectPalette(hPDC,hPal,FALSE);
	RealizePalette(hPDC);

	
	// Allocate enough memory to hold bitmapinfoheader and color table
	if(hDIB) GlobalFree( hDIB );

	hDIB = GlobalAlloc(GMEM_FIXED,dwLen);

	if (!hDIB){
		SelectPalette(hPDC,hPal,FALSE);
		return NULL;
	}

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	*lpbi = bi;

	// Call GetDIBits with a NULL lpBits param, so the device driver 
	// will calculate the biSizeImage field 
	GetDIBits(hPDC, (HBITMAP)bitmap.GetSafeHandle(), 0L, (DWORD)bi.biHeight,
			(LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

	bi = *lpbi;

	// If the driver did not fill in the biSizeImage field, then compute it
	// Each scan line of the image is aligned on a DWORD (32bit) boundary
	if (bi.biSizeImage == 0){
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) 
						* bi.biHeight;
	}

	// Realloc the buffer so that it can hold all the bits
	dwLen += bi.biSizeImage;
	if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		hDIB = handle;
	else{
		GlobalFree(hDIB);
		hDIB = 0;
		// Reselect the original palette
		SelectPalette(hDC,hPal,FALSE);

		return NULL;
	}

	// Get the bitmap bits
	lpbi = (LPBITMAPINFOHEADER)hDIB;
	m_pBMI = (LPBITMAPINFO)hDIB;
	m_pBits = (LPBYTE)hDIB + (bi.biSize + nColors * sizeof(RGBQUAD));
	///////////////////////////////////////////////
	///////////////////////////////////////////////

	HPALETTE hOldPal = NULL;        // Previous palette
	
	// Get the DIB's palette, then select it into DC
	if (&pal != NULL)
	{
		hPal = (HPALETTE) pal.m_hObject;
		
		// Select as background since we have
		// already realized in forground if needed
		hOldPal = ::SelectPalette(hDC, hPal, TRUE);
	}
	
	/* Make sure to use the stretching mode best for color pictures */
	::SetStretchBltMode(hDC, COLORONCOLOR);	
	BOOL bSuccess = FALSE;
	
	UINT start(0), end, step_size(1);//, offset_y(0);

	end = step_size;
	
	if((UINT)bm.bmHeight < step_size)
		end = (int)bm.bmHeight;
	
	while(start < (UINT)bm.bmHeight){
		
		GetDIBits( hPDC, (HBITMAP)bitmap.GetSafeHandle(),
								start,				// Start scan line
								end - start,				// # of scan lines
								(LPBYTE) m_pBits,	//lpbi 			// address for bitmap bits
								(LPBITMAPINFO)lpbi,		// address of bitmapinfo
								(DWORD)DIB_RGB_COLORS);		// Use RGB for color table
		
		bSuccess = ::SetDIBitsToDevice(hDC,        // hDC		
			rect->left,             // DestX
			rect->top,              // DestY
			RECTWIDTH(rect),        // nDestWidth
			RECTHEIGHT(rect),		// nDestHeight
			rect->left,             // SrcX
			(int)Height() -
			rect->top -
			RECTHEIGHT(rect),		// SrcY
			start,                  // nStartScan
			end - start,			// nNumScans
			m_pBits,                // lpBits
			m_pBMI,                 // lpBitsInfo
			DIB_RGB_COLORS);        // wUsage
		
	    

		start = end;
		end = start + step_size;
		if((UINT)bm.bmHeight < end)
			end = (UINT)bm.bmHeight;
	}
	
	/* Reselect old palette */
	if (hOldPal != NULL)
	{
		::SelectPalette(hDC, hOldPal, TRUE);
	}
	
	return bSuccess;

}

void CClientCapture::OnDraw(HDC hDC, CRect rcRect, CRect rect)
{
	Paint(hDC, &pal, rcRect, rect);
}

// WriteDIB		- Writes a DIB to file
// Returns		- TRUE on success
// szFile		- Name of file to write to
// hDIB			- Handle of the DIB
BOOL CClientCapture::WriteDIB( CString csFile)
{
	BITMAPFILEHEADER	hdr;
	LPBITMAPINFOHEADER	lpbi;

	if (!hDIB)
		return FALSE;

	CFile file;
	if( !file.Open( csFile, CFile::modeWrite|CFile::modeCreate) )
		return FALSE;

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	int nColors = 1 << lpbi->biBitCount;
	if( nColors > 256 ) 
		nColors = 0;

	// Fill in the fields of the file header 
	hdr.bfType		= ((WORD) ('M' << 8) | 'B');	// is always "BM"
	hdr.bfSize		= GlobalSize (hDIB) + sizeof( hdr );
	hdr.bfReserved1 	= 0;
	hdr.bfReserved2 	= 0;
	hdr.bfOffBits		= (DWORD) (sizeof( hdr ) + lpbi->biSize +
						nColors * sizeof(RGBQUAD));

	// Write the file header 
	file.Write( &hdr, sizeof(hdr) );

	// Write the DIB header and the bits 
	file.Write( lpbi, GlobalSize(hDIB) );

	return TRUE;
}

void CClientCapture::Release()
{
	if(hDIB)
		GlobalFree( hDIB );

	hDIB = 0;
	m_pBMI = 0;
	m_pBits = 0;

}
