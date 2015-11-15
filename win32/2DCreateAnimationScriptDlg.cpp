// 2DCreateAnimationScriptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "grphcalc.h"
#include "2DCreateAnimationScriptDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
// C2DCreateAnimationScriptDlg dialog


C2DCreateAnimationScriptDlg::C2DCreateAnimationScriptDlg(CWnd* pParent /*=NULL*/)
	: CDialog(C2DCreateAnimationScriptDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(C2DCreateAnimationScriptDlg)
	m_nType = 0;
	m_nRangeOption = 0;
	m_nXTimes = 0;
	m_nTimesThrough = 1;
	m_fRun = FALSE;
	//}}AFX_DATA_INIT
}


void C2DCreateAnimationScriptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C2DCreateAnimationScriptDlg)
	DDX_Radio(pDX, IDC_TYPE_REALTIME, m_nType);
	DDX_Radio(pDX, IDC_RANGEOPTIONS_ONEWAY, m_nRangeOption);
	DDX_Radio(pDX, IDC_RANGEOPTIONS_TIMES_X, m_nXTimes);
	DDX_Text(pDX, IDC_RANGEOPTIONS_TIMES_THROUGH, m_nTimesThrough);
	DDV_MinMaxUInt(pDX, m_nTimesThrough, 1, 1000000);
	DDX_Check(pDX, IDC_RUN, m_fRun);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C2DCreateAnimationScriptDlg, CDialog)
	//{{AFX_MSG_MAP(C2DCreateAnimationScriptDlg)
	ON_BN_CLICKED(IDC_RANGEOPTIONS_TIMES_FOREVER, EnableDisableControls)
	ON_BN_CLICKED(IDC_RANGEOPTIONS_ONEWAY, EnableDisableControls)
	ON_BN_CLICKED(IDC_TYPE_FRAMES, EnableDisableControls)
	ON_BN_CLICKED(IDC_TYPE_REALTIME, EnableDisableControls)
	ON_BN_CLICKED(IDC_RANGEOPTIONS_XTIMES, EnableDisableControls)
	ON_BN_CLICKED(IDC_RANGEOPTIONS_TIMES_X, EnableDisableControls)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C2DCreateAnimationScriptDlg message handlers

void C2DCreateAnimationScriptDlg::EnableDisableControls()
{
	// first check animation type
	if(BST_CHECKED == IsDlgButtonChecked(IDC_TYPE_REALTIME)) // realtime
		{
		if(BST_CHECKED == IsDlgButtonChecked(IDC_RANGEOPTIONS_ONEWAY)) // one way
			{
			GetDlgItem(IDC_RANGEOPTIONS_TIMES_X)->EnableWindow(false);
			GetDlgItem(IDC_RANGEOPTIONS_TIMES_THROUGH)->EnableWindow(false);
			GetDlgItem(IDC_STATIC_TIMES)->EnableWindow(false);
			GetDlgItem(IDC_RANGEOPTIONS_TIMES_FOREVER)->EnableWindow(false);
			}
		else // round trip
			{
			GetDlgItem(IDC_RANGEOPTIONS_TIMES_X)->EnableWindow(true);
			GetDlgItem(IDC_RANGEOPTIONS_TIMES_THROUGH)->EnableWindow(true);
			GetDlgItem(IDC_STATIC_TIMES)->EnableWindow(true);
			GetDlgItem(IDC_RANGEOPTIONS_TIMES_FOREVER)->EnableWindow(true);
			}
		}
	else // creating animation frames
		{
		
		GetDlgItem(IDC_RANGEOPTIONS_TIMES_FOREVER)->EnableWindow(false);
			
		if(BST_CHECKED == IsDlgButtonChecked(IDC_RANGEOPTIONS_ONEWAY)) // one way
			{
			GetDlgItem(IDC_RANGEOPTIONS_TIMES_X)->EnableWindow(false);
			GetDlgItem(IDC_RANGEOPTIONS_TIMES_THROUGH)->EnableWindow(false);
			GetDlgItem(IDC_STATIC_TIMES)->EnableWindow(false);
			}
		else // round trip
			{
			CheckDlgButton(IDC_RANGEOPTIONS_TIMES_X, 1);
			CheckDlgButton(IDC_RANGEOPTIONS_TIMES_FOREVER, 0);
			
			GetDlgItem(IDC_RANGEOPTIONS_TIMES_X)->EnableWindow(true);
			GetDlgItem(IDC_RANGEOPTIONS_TIMES_THROUGH)->EnableWindow(true);
			GetDlgItem(IDC_STATIC_TIMES)->EnableWindow(true);
			}		
		}
}


BOOL C2DCreateAnimationScriptDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	EnableDisableControls();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void C2DCreateAnimationScriptDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
