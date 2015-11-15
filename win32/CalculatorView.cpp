// CalculatorView.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "CalculatorView.h"
#include "GraphTabNameDlg.h"
#include "GrphCalcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalculatorView

IMPLEMENT_DYNAMIC(CCalculatorView, CPropertySheet)

CCalculatorView::CCalculatorView(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	Initialization();
}

CCalculatorView::CCalculatorView(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	Initialization();
}

CCalculatorView::~CCalculatorView()
{
}


BEGIN_MESSAGE_MAP(CCalculatorView, CPropertySheet)
	//{{AFX_MSG_MAP(CCalculatorView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_RESIZEPAGE, OnResizePage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalculatorView message handlers
void CCalculatorView::Initialization()
{
	initialzed = false;
}

BOOL CCalculatorView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	NMHDR* pnmh = (LPNMHDR) lParam;

	// the sheet resizes the page whenever it is activated
	// so we need to resize it to what we want
	if (TCN_SELCHANGE == pnmh->code)
		// user-defined message needs to be posted because page must
		// be resized after TCN_SELCHANGE has been processed
		PostMessage (WM_RESIZEPAGE);


	return CPropertySheet::OnNotify(wParam, lParam, pResult);
}

void CCalculatorView::OnSize(UINT nType, int cx, int cy) 
{
	CPropertySheet::OnSize(nType, cx, cy);
	
	/*CPropertyPage* pPage = GetActivePage ();     
	if(pPage)
		pPage->MoveWindow (&m_PageRect);  */
}

LONG CCalculatorView::OnResizePage(UINT, LONG)
{
	CPropertyPage* pPage = GetActivePage ();
	ASSERT (pPage);
	pPage->MoveWindow (&m_PageRect);	
	return 0;
}


BOOL CCalculatorView::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
		
	// SET PAGE RECT
	m_PageRect.left = SHEET_MARGIN_LEFT + TAB_MARGIN_LEFT;
	m_PageRect.right = (m_PageRect.left + DEFAULT_TAB_WIDTH) - TAB_PAGE_DIFFERENCE_X;
	
	m_PageRect.top = TABS_HEIGHT + SHEET_MARGIN_TOP + TAB_MARGIN_TOP;
	m_PageRect.bottom = (m_PageRect.top + DEFAULT_TAB_HEIGHT) - TAB_PAGE_DIFFERENCE_Y;
	// END SET PAGE RECT

	// Set the fonts for all of the property sheet's tabs
	m_fontTab.CreateFont(-8, 0, 0, 0, FW_NORMAL, 0, 0,
		0, 1, 0, 0, 0, 0, _T("MS Sans Serif"));	

	CTabCtrl* pTab = GetTabControl();
	ASSERT(pTab);
	if (pTab)
	{
		pTab->SetFont(&m_fontTab);

		CRect rect(TAB_MARGIN_LEFT, 
				   TAB_MARGIN_TOP, 
				   (TAB_MARGIN_LEFT + DEFAULT_TAB_WIDTH) - SHEET_TAB_DIFFERENCE, 
				   (TAB_MARGIN_TOP + DEFAULT_TAB_HEIGHT) - SHEET_TAB_DIFFERENCE);
		pTab->MoveWindow(&rect);
	}

	// set the images for the tabs
	m_imageTab.Create( IDB_TAB_IMG, 13, 1, RGB(255,255,255));
	pTab->SetImageList( &m_imageTab );

	TC_ITEM tcItem;
	tcItem.mask = TCIF_IMAGE;

	tcItem.iImage = 0;
	pTab->SetItem( 0, &tcItem );
	
	///// INIT Graph Tabs //////
	int index(1);
	CGrphCalcDlg* pDlg = (CGrphCalcDlg*)STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
	
	for(int i = 0; i < MAXTABS; ++i){
		if(pDlg->IsActive2DGraph(i)){
			CString tempS;
			tempS.Format("Graph %d", i+1);
			tcItem.mask = TCIF_TEXT | TCIF_IMAGE;
			tcItem.pszText = tempS.GetBuffer(0);
			tcItem.iImage = 1;
			pTab->SetItem(index , &tcItem );

			++index;
		}
	}
	
	tcItem.mask = TCIF_IMAGE;
	tcItem.iImage = 2;
	pTab->SetItem(index, &tcItem );
	
	initialzed = true;
	return bResult;
}
