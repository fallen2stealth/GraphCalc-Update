// FlatEdit.cpp : implementation file
//

#include "stdafx.h"
#include "FlatEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CWinApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CFlatEdit

CFlatEdit::CFlatEdit()
{
	
	m_clrHilite = GetSysColor(COLOR_BTNHIGHLIGHT);
	m_clrShadow = GetSysColor(COLOR_BTNSHADOW);
	m_clrDkShad = GetSysColor(COLOR_3DDKSHADOW);
	m_clrButton = GetSysColor(COLOR_BTNFACE);
	m_bFlatStyle = TRUE;

}

CFlatEdit::~CFlatEdit()
{
}


BEGIN_MESSAGE_MAP(CFlatEdit, CEdit)
	//{{AFX_MSG_MAP(CFlatEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_TIMER()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlatEdit message handlers
void CFlatEdit::OnMouseMove(UINT nFlags, CPoint point) 
{
	SetTimer(1, 10, NULL);
	CEdit::OnMouseMove(nFlags, point);
}

void CFlatEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bLBtnDown = true;
	CEdit::OnLButtonDown(nFlags, point);
}

void CFlatEdit::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bLBtnDown = false;
	CEdit::OnLButtonUp(nFlags, point);
}

void CFlatEdit::OnTimer(UINT nIDEvent) 
{
	POINT pt;
	GetCursorPos(&pt);
	CRect rcItem;
	GetWindowRect(&rcItem);

	static bool bPainted = false;

	if(rcItem.PtInRect(pt))
		{		
		DrawEdit(FE_MOUSEOVER, m_clrShadow, m_clrHilite);
   		return;
		}
	else
		{
		KillTimer(1);
		if (GetFocus() != this)
		  	DrawEdit(FE_MOUSEOUT, m_clrButton, m_clrButton);
		}

	CEdit::OnTimer(nIDEvent);
}

void CFlatEdit::OnPaint() 
{
	Default();

	CPoint pt;
	GetCursorPos(&pt);

	CRect rcItem;
	GetWindowRect(&rcItem);

   if ((rcItem.PtInRect(pt)) || (::GetFocus() == m_hWnd))
		DrawEdit(FE_MOUSEOVER, m_clrShadow, m_clrHilite);
    else
		DrawEdit(FE_MOUSEOUT, m_clrButton, m_clrButton);
}

void CFlatEdit::OnSysColorChange() 
{
	CEdit::OnSysColorChange();
	m_clrHilite = GetSysColor(COLOR_BTNHIGHLIGHT);
	m_clrShadow = GetSysColor(COLOR_BTNSHADOW);
	m_clrDkShad = GetSysColor(COLOR_3DDKSHADOW);
	m_clrButton = GetSysColor(COLOR_BTNFACE);
	m_clrEditBackground = GetSysColor(COLOR_WINDOW);
	
}

void CFlatEdit::DrawEdit(int style, COLORREF clrTopLeft, COLORREF clrBottomRight)
{
	CRect rcItem;
	CRect rcGripper;
	CRect rcSeperator;

	GetClientRect(&rcItem);
	GetClientRect(&rcGripper);
	GetClientRect(&rcSeperator);

	CDC* pDC = GetDC();

	if(m_bFlatStyle)
	{
		if(style == FE_MOUSEOVER || IsWindowEnabled())
			{
			rcItem.InflateRect(1, 1, 0, 1);
			pDC->Draw3dRect(rcItem, clrTopLeft, clrBottomRight);
			}			
	}
	else {
		rcItem.InflateRect(1, 1, 0, 1);
		pDC->Draw3dRect(rcItem, m_clrEditBackground, m_clrEditBackground);
	}

	ReleaseDC(pDC);
}

void CFlatEdit::SetIndent(int margin)
{
	SetMargins(margin, 1);
}

void CFlatEdit::OnSetFocus(CWnd* pOldWnd) 
{
	CEdit::OnSetFocus(pOldWnd);
	SetReadOnly(false);
    DrawEdit(FE_MOUSEOVER, m_clrShadow, m_clrHilite);
}

void CFlatEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
	
	// The same code found in the timer handler
    POINT pt;
    GetCursorPos(&pt);
    CRect rcItem;
    GetWindowRect(&rcItem);
    SetReadOnly(true);

    if(!rcItem.PtInRect(pt)) {
 		DrawEdit(FE_MOUSEOUT, m_clrButton, m_clrButton);
 		return;
    }
}
