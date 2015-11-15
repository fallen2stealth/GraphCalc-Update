// GraphOptions.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "GraphOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GraphOptions

IMPLEMENT_DYNAMIC(GraphOptions, CPropertySheet)

GraphOptions::GraphOptions(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

GraphOptions::GraphOptions(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_Mode);
	m_ActiveRangeTab = -1;
	m_StartTab = 0;
}

GraphOptions::~GraphOptions()
{
}


BEGIN_MESSAGE_MAP(GraphOptions, CPropertySheet)
	//{{AFX_MSG_MAP(GraphOptions)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GraphOptions message handlers


BOOL GraphOptions::OnInitDialog() 
{
	CPropertySheet::OnInitDialog();

	/*CWnd* pWnd = GetDlgItem(IDHELP);
	if(pWnd)
		pWnd->ShowWindow(FALSE);

	CRect rc;
	pWnd = GetDlgItem(IDOK);     
	pWnd->GetWindowRect(&rc);  
	rc.left += 81;  
	rc.right += 81;
	ScreenToClient(&rc);
    pWnd->MoveWindow(&rc);

	pWnd = GetDlgItem(IDCANCEL);     
	pWnd->GetWindowRect(&rc);  
	rc.left += 81;  
	rc.right += 81;
	ScreenToClient(&rc);
    pWnd->MoveWindow(&rc);

	pWnd = GetDlgItem(ID_APPLY_NOW);     
	pWnd->GetWindowRect(&rc);  
	rc.left += 81;  
	rc.right += 81;
	ScreenToClient(&rc);
    pWnd->MoveWindow(&rc);*/

//	m_GOP0.m_GraphOptions = this;

	SetActivePage(m_StartTab);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************/
// GraphOptions::OnPaint()
// Pre: none
// Post: none
// Return Value: none
// Intent: called by framework to handle drawing of window
/*********************************************************/
void GraphOptions::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	/*if (m_LogoText.IsEmpty())
		return;

	BOOL bWizMode; 
        
	// Get the current style from PROPSHEETHEADER structure 
	if( m_psh.dwFlags & PSH_WIZARD ) 
		bWizMode = TRUE;                // It's in wizard mode
	else 
		bWizMode = FALSE;               // It's in property sheet mode


	// If this is a Wizard, cannot retrieve the tab control dimension. 
	// So Get the Dialog's Window Rect  

	CRect rectTabCtrl;
	if( bWizMode ) 
	{ 
		GetWindowRect(rectTabCtrl); 
		rectTabCtrl.OffsetRect(14,0);	// A little correction
	} 
	else 
	{ 
		GetTabControl()->GetWindowRect(rectTabCtrl);
	} 
	ScreenToClient(rectTabCtrl);


	CRect rectOk;
	GetDlgItem(IDOK)->GetWindowRect(rectOk);
	ScreenToClient(rectOk);

	dc.SetBkMode(TRANSPARENT);

	CRect rectText;
	rectText.left = rectTabCtrl.left;
	rectText.top = rectOk.top;
	rectText.bottom = rectOk.bottom;
	rectText.right = rectOk.left;

	CFont * OldFont = dc.SelectObject(&m_fontLogo);

	// draw text in DC
	COLORREF OldColor = dc.SetTextColor( ::GetSysColor( COLOR_3DHILIGHT));

	dc.DrawText(m_LogoText, rectText + CPoint(1,1), 
	            DT_SINGLELINE | DT_LEFT | DT_VCENTER);
	dc.SetTextColor( ::GetSysColor( COLOR_3DSHADOW));
	dc.DrawText( m_LogoText, rectText, DT_SINGLELINE | DT_LEFT | DT_VCENTER);

	// restore old text color
	dc.SetTextColor( OldColor);

	// restore old font
	dc.SelectObject(OldFont);
	*/

	// Do not call CPropertySheet::OnPaint() for painting messages
}

void GraphOptions::UpdateGraphMode(int mode)
{
	// this switch removes the current range and eq tabs and then the display tab.
	// the display tab needs to be removed so we can add back in the correct
	// tab then display tab and have everything in order still
	switch(m_ActiveRangeTab){
	case 0:
		if(mode == 0) return;

		RemovePage(&m_GOP0); // remove eq tab
		RemovePage(&m_GOP1); // remove euclidean range tab
		RemovePage(&m_GOP2); 
		break;
	case 1:
		if(mode == 1) return;

		RemovePage(&m_GOP0); // remove eq tab
		RemovePage(&m_PolarRange); // remove polar tab
		RemovePage(&m_GOP2); 
		break;
	case 2:
		if(mode == 2) return;

		RemovePage(&m_ParametricEqs); 
		RemovePage(&m_ParametricRange); 
		RemovePage(&m_GOP2); // remove parametric tab
		break;
	}
	
	switch(mode){
	case 0:  // euclidean mode
		AddPage(&m_GOP0); // euclidean equation tab
		AddPage(&m_GOP1); // euclidean range tab
		m_ActiveRangeTab = 0; 
		break; 
	case 1:  // polar mode
		AddPage(&m_GOP0); // polar equation tab
		AddPage(&m_PolarRange); // polar range tab
		m_ActiveRangeTab = 1; 
		break; 
	case 2:  
		AddPage(&m_ParametricEqs);
		AddPage(&m_ParametricRange);
		m_ActiveRangeTab = 2;
		break; // parametric mode
	}
	
	m_GOP0.m_Mode = (EGraphMode)mode; // set the mode on the polar/euclidean equation tab
	
	AddPage(&m_GOP2); // add the display tab back in
}
