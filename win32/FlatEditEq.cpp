// FlatEditEq.cpp : implementation file
//

#include "stdafx.h"
#include "grphcalc.h"
#include "FlatEditEq.h"
#include "globals.h"
#include "Graphview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlatEditEq

CFlatEditEq::CFlatEditEq()
{
	CFlatEdit::CFlatEdit();
	m_pwndParent = NULL;
	m_nEq = -1;
	m_uParametricEq = -1;
}

CFlatEditEq::~CFlatEditEq()
{
}

BEGIN_MESSAGE_MAP(CFlatEditEq, CEdit)
	//{{AFX_MSG_MAP(CFlatEditEq)
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_TIMER()
	ON_WM_SETFOCUS() 
	ON_WM_GETDLGCODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlatEditEq message handlers

void CFlatEditEq::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	switch(nChar)
		{
		case VK_RETURN: UpdateGraph(); break;
		}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
} 

void CFlatEditEq::OnKillFocus(CWnd* pNewWnd) 
{
	CFlatEdit::OnKillFocus(pNewWnd);

	CString strEq;
	GetWindowText(strEq);
	if(strEq != "" && !g_Calculator->IsValid(strEq))
		{
		SetFocus();
		return;
		}
	
	UpdateGraph();
}

void CFlatEditEq::UpdateGraph()
{
	CString strEq;
	GetWindowText(strEq);
	if(strEq != "" && !g_Calculator->IsValid(strEq, ghDlg))
		{
		SetFocus();
		return;
		}

	Assert(m_pwndParent);

	CGraphView *pGV = (CGraphView*)m_pwndParent;

	if(m_pwndParent && m_nEq >= 0)
		{
		switch(pGV->m_Mode)
			{
			case EUCLIDEAN:
			case POLAR:
				{	
				if(pGV->m_astrEquationsRaw[m_nEq] != strEq)
					{
					// if previous equation was empty, turn it on now
					if(pGV->m_astrEquationsRaw[m_nEq] == "")
						pGV->m_Equations[m_nEq].disp = true;
					
					pGV->SetEquation(m_nEq, strEq);

					if(pGV->m_Equations[m_nEq].disp)
						pGV->RePaintNow();
					}
				break;
				}
			case PARAMETRIC:
				{
				CString curEq;
				switch(m_uParametricEq){
					case PARAMETRIC_EQ_X: curEq = pGV->m_ParametricGraph.m_Equations[m_nEq].xt; break;
					case PARAMETRIC_EQ_Y: curEq = pGV->m_ParametricGraph.m_Equations[m_nEq].yt; break;
					}
				
				if(curEq != strEq)
					{
					pGV->SetEquation(m_nEq, strEq, m_uParametricEq);

					if(pGV->m_ParametricGraph.m_Equations[m_nEq].disp)
						pGV->RePaintNow();
					}
				break;
				}
			}
		}
		
} 

UINT CFlatEditEq::OnGetDlgCode() 
{ 
	return DLGC_WANTALLKEYS;	 
}
