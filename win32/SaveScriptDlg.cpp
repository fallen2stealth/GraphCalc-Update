// SaveScriptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "SaveScriptDlg.h"
#include <fstream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveScriptDlg dialog


CSaveScriptDlg::CSaveScriptDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveScriptDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSaveScriptDlg)
	m_sFile = _T("");
	//}}AFX_DATA_INIT
}


void CSaveScriptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveScriptDlg)
	DDX_Control(pDX, IDC_COMMANDS, m_CommandsCtrl);
	DDX_Text(pDX, IDC_FILE, m_sFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaveScriptDlg, CDialog)
	//{{AFX_MSG_MAP(CSaveScriptDlg)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_EN_CHANGE(IDC_FILE, OnChangeFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveScriptDlg message handlers

void CSaveScriptDlg::OnBrowse() 
{
	static char BASED_CODE szFilter[] = "GraphCalc Script (*.gcs)|*.gcs||";	

	CFileDialog *fileDlg = new CFileDialog(false, 
										   "gcs",
										    NULL,
											OFN_ENABLESIZING 
											| OFN_CREATEPROMPT
											| OFN_HIDEREADONLY 
											| OFN_OVERWRITEPROMPT,
											szFilter,
											this);

	if(fileDlg->DoModal() == IDOK){
		UpdateData(true);
		m_sFile = fileDlg->GetPathName();
		UpdateData(false);
		OnChangeFile();
	}

	delete fileDlg;		
}

BOOL CSaveScriptDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	for(int i(m_pFormulaCtrl->GetCount() - 1); i >= 0; --i){
		CString temp;
		m_pFormulaCtrl->GetLBText(i, temp);
		m_CommandsCtrl.AddString(temp);	
	}
	GetDlgItem(IDOK)->EnableWindow(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSaveScriptDlg::OnOK() 
{
	UpdateData();

	::ofstream outfile;
	
	outfile.open(m_sFile);
	
	for(int i(0); i < m_CommandsCtrl.GetCount(); ++i){
		
		if(m_CommandsCtrl.GetSel(i) > 0){
			CString temp;
			m_CommandsCtrl.GetText(i, temp);
			outfile.write(temp.GetBuffer(temp.GetLength()), temp.GetLength());
			char nl('\n');
			outfile.write(&nl, 1);
		}
	}		
	outfile.close();	

	CDialog::OnOK();
}

void CSaveScriptDlg::OnChangeFile() 
{
	UpdateData();
	if(m_sFile.IsEmpty())
		GetDlgItem(IDOK)->EnableWindow(false);
	else
		GetDlgItem(IDOK)->EnableWindow(true);
	
}
