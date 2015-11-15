// OptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "OptionsDlg.h"
#include <fstream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog

void AFXAPI DDV_FileName( CDataExchange* pDX, CString& value, int nIDC, int &script_on, bool &ok)
{
	if( pDX->m_bSaveAndValidate)
	{		
		if(script_on == 1){
			if(ok){
				if(value.IsEmpty()){
					pDX->m_pDlgWnd->MessageBox("Startup script file name is empty.");
					pDX->PrepareEditCtrl(nIDC);
					pDX->Fail();
					ok = false;
				}
				else{
					::ifstream ifile(value, ios::nocreate);
					
					if(ifile.rdstate() == ios::failbit){			
						pDX->m_pDlgWnd->MessageBox("Startup script file '" + value + "' does not exist.  Please check the path and file name.");
						pDX->PrepareEditCtrl(nIDC);
						pDX->Fail();
						ok = false;
					}
				}
			}
		}
	}
}

COptionsDlg::COptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsDlg)
	m_bDetailedOutput = FALSE;
	m_bSaveExprHistory = FALSE;
	m_bSaveOutputHistory = FALSE;
	m_bSaveSettings = FALSE;
	m_sScriptFile = _T("");
	m_sSettingsFile = _T("");
	m_bSoundEffects = FALSE;
	m_bStartupScript = FALSE;
	m_bTooltips = FALSE;
	m_bCommandErrors = FALSE;
	m_bDispScriptProgressDlg = FALSE;
	//}}AFX_DATA_INIT

	m_bOk = false;
}


void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDlg)
	DDX_Check(pDX, IDC_DETAILED_OUTPUT, m_bDetailedOutput);
	DDX_Check(pDX, IDC_SAVE_EXPR_HISTORY, m_bSaveExprHistory);
	DDX_Check(pDX, IDC_SAVE_OUTPUT_HISTORY, m_bSaveOutputHistory);
	DDX_Check(pDX, IDC_SAVE_SETTINGS, m_bSaveSettings);
	DDX_Text(pDX, IDC_SCRIPT_FILE, m_sScriptFile);
	DDX_Text(pDX, IDC_SETTINGS_FILE, m_sSettingsFile);
	DDX_Check(pDX, IDC_SOUNDFX, m_bSoundEffects);
	DDX_Check(pDX, IDC_STARTUP_SCRIPT_ENABLED, m_bStartupScript);
	DDX_Check(pDX, IDC_TOOLTIPS, m_bTooltips);
	DDX_Check(pDX, IDC_COMMAND_ERRORS, m_bCommandErrors);
	DDX_Check(pDX, IDC_DISP_SCRIPT_PROGRESS_DLG, m_bDispScriptProgressDlg);
	//}}AFX_DATA_MAP
	DDV_FileName(pDX, m_sScriptFile, IDC_SCRIPT_FILE, m_bStartupScript, m_bOk);
}


BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
	//{{AFX_MSG_MAP(COptionsDlg)
	ON_BN_CLICKED(IDC_STARTUP_SCRIPT_ENABLED, OnStartupScriptEnabled)
	ON_BN_CLICKED(IDC_SETTINGS_BROWSE, OnSettingsBrowse)
	ON_BN_CLICKED(IDC_SAVE_SETTINGS, OnSaveSettings)
	ON_BN_CLICKED(IDC_SCRIPT_BROWSE, OnScriptBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg message handlers

void COptionsDlg::OnStartupScriptEnabled() 
{
	UpdateData();

	if(m_bStartupScript == 1){
		GetDlgItem(IDC_SCRIPT_FILE)->EnableWindow(true);
		GetDlgItem(IDC_SCRIPT_BROWSE)->EnableWindow(true);
	}
	else{
		GetDlgItem(IDC_SCRIPT_FILE)->EnableWindow(false);
		GetDlgItem(IDC_SCRIPT_BROWSE)->EnableWindow(false);
	}
}

void COptionsDlg::OnScriptBrowse() 
{
	UpdateData(true);
	static char BASED_CODE szFilter[] = "GraphCalc Script (*.gcs)|*.gcs||";
	GetFile(m_sScriptFile, szFilter);
	UpdateData(false);	
}

void COptionsDlg::OnSettingsBrowse() 
{
	UpdateData(true);
	static char BASED_CODE szFilter[] = "GraphCalc Files (*.gcl)|*.gcl||";
	GetFile(m_sSettingsFile, szFilter);
	UpdateData(false);
}

void COptionsDlg::OnSaveSettings() 
{
	UpdateData();

	if(m_bSaveSettings == 1){
		GetDlgItem(IDC_SETTINGS_FILE)->EnableWindow(true);
		GetDlgItem(IDC_SETTINGS_BROWSE)->EnableWindow(true);
	}
	else{
		GetDlgItem(IDC_SETTINGS_FILE)->EnableWindow(false);
		GetDlgItem(IDC_SETTINGS_BROWSE)->EnableWindow(false);
	}
}

bool COptionsDlg::GetFile(CString &file, char BASED_CODE *szFilter)
{
	CFileDialog *fileDlg = new CFileDialog(true, 
										   szFilter,
										    NULL,
											OFN_ENABLESIZING 
											| OFN_FILEMUSTEXIST 
											| OFN_HIDEREADONLY 
											| OFN_OVERWRITEPROMPT 
											| OFN_READONLY,
											szFilter,
											this);

	if(fileDlg->DoModal() == IDOK){
		file = fileDlg->GetPathName();
		delete fileDlg;	
		return true;
	}

	delete fileDlg;
	return false;
}

BOOL COptionsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(m_bStartupScript == 1){
		GetDlgItem(IDC_SCRIPT_FILE)->EnableWindow(true);
		GetDlgItem(IDC_SCRIPT_BROWSE)->EnableWindow(true);
	}
	else{
		GetDlgItem(IDC_SCRIPT_FILE)->EnableWindow(false);
		GetDlgItem(IDC_SCRIPT_BROWSE)->EnableWindow(false);
	}
	if(m_bSaveSettings == 1){
		GetDlgItem(IDC_SETTINGS_FILE)->EnableWindow(true);
		GetDlgItem(IDC_SETTINGS_BROWSE)->EnableWindow(true);
	}
	else{
		GetDlgItem(IDC_SETTINGS_FILE)->EnableWindow(false);
		GetDlgItem(IDC_SETTINGS_BROWSE)->EnableWindow(false);
	}

	#ifdef GRAPHCALC_LIGHT
	GetDlgItem(IDC_SCRIPT_FILE)->EnableWindow(false);
	GetDlgItem(IDC_SCRIPT_BROWSE)->EnableWindow(false);
	GetDlgItem(IDC_COMMAND_ERRORS)->EnableWindow(false);
	GetDlgItem(IDC_DISP_SCRIPT_PROGRESS_DLG)->EnableWindow(false);
	GetDlgItem(IDC_STARTUP_SCRIPT)->EnableWindow(false);
	GetDlgItem(IDC_STARTUP_SCRIPT_ENABLED)->EnableWindow(false);
	#endif
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionsDlg::OnOK() 
{
	m_bOk = true;
	
	CDialog::OnOK();
}

