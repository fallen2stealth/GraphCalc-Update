// ProgramOptions.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "ProgramOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgramOptions dialog


CProgramOptions::CProgramOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CProgramOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgramOptions)
	m_SndEffects = 0;
	//}}AFX_DATA_INIT
}


void CProgramOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgramOptions)
	DDX_Radio(pDX, IDC_SOUND_EFFECTS, m_SndEffects);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgramOptions, CDialog)
	//{{AFX_MSG_MAP(CProgramOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgramOptions message handlers


BOOL CProgramOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
