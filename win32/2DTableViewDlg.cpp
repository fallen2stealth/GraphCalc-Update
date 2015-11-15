// 2DTableViewDlg.cpp : implementation file
//
// test comments for check in/out

#include "stdafx.h"
#include "GrphCalc.h"
#include "2DTableViewDlg.h"
#include "globals.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CCalculator *g_Calculator;

#define COLUMN_WIDTH	60
#define ERROR_TITLE "Error in settings"

/////////////////////////////////////////////////////////////////////////////
// C2DTableViewDlg dialog


C2DTableViewDlg::C2DTableViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(C2DTableViewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(C2DTableViewDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_ldMin = 0;
	m_ldMax = 10;
	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
}

C2DTableViewDlg::~C2DTableViewDlg()
{
	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
}

void C2DTableViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C2DTableViewDlg)
	DDX_Control(pDX, IDC_TABLE, m_ctrlTableList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C2DTableViewDlg, CDialog)
	//{{AFX_MSG_MAP(C2DTableViewDlg)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_CLICKED(IDC_HELP_BUTTON, OnHelpButton)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_HELP, OnHelp)
	ON_BN_CLICKED(IDC_EXPORT, OnExport)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C2DTableViewDlg message handlers

BOOL C2DTableViewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	ASSERT(m_Eqs);
	ASSERT(m_astrEquations);


	CString strMin, strMax;
	
	g_Calculator->DecimalToString(strMin, m_ldMin);
	CleanupAnswer(strMin);

	g_Calculator->DecimalToString(strMax, m_ldMax);
	CleanupAnswer(strMax);

	SetDlgItemText(IDC_MIN_VAL, strMin);
	SetDlgItemText(IDC_MAX_VAL, strMax);

	switch(g_Calculator->m_IntlMode)
		{
		case US:
			SetDlgItemText(IDC_STEP, "0.5");
			break;
		case EUROPEAN:
			SetDlgItemText(IDC_STEP, "0,5");
			break;
		}

	
	SetDlgItemText(IDC_DECIMAL_PLACES, "5");
			
	int nColumns=0;
	switch(m_Mode)
		{
		case EUCLIDEAN:	
			m_ctrlTableList.InsertColumn(nColumns++,"x",LVCFMT_LEFT,COLUMN_WIDTH,-1);    
			SetDlgItemText(IDC_MIN_TEXT, "x min:");
			SetDlgItemText(IDC_MAX_TEXT, "x max:");
			break;
		case POLAR:		
			m_ctrlTableList.InsertColumn(nColumns++,"theta",LVCFMT_LEFT,COLUMN_WIDTH,-1); 
			SetDlgItemText(IDC_MIN_TEXT, "theta min:");
			SetDlgItemText(IDC_MAX_TEXT, "theta max:");
			break;
		}

	for(int i=0; i < MAX_EQUATIONS; ++i)
		if(m_Eqs[i].disp)
			{
			m_ctrlTableList.InsertColumn(nColumns,m_astrEquations[i],LVCFMT_RIGHT,COLUMN_WIDTH,nColumns);
			++nColumns;
			}

	OnUpdate();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

long double C2DTableViewDlg::ComputeValue(UINT field)
{
	CString Val;
	long double answer;

	GetDlgItem(field)->GetWindowText(Val);

	if(g_Calculator->Compute(Val, answer, this->m_hWnd) != SUCCESSFULL){
		GetDlgItem(field)->SetFocus();
		return 0;
	}

	g_Calculator->DecimalToString(Val, answer);
	
	CleanupAnswer(Val);

	GetDlgItem(field)->SetWindowText(Val);
	return answer;
}

void C2DTableViewDlg::OnUpdate() 
{
	long double min = ComputeValue(IDC_MIN_VAL);
	long double max = ComputeValue(IDC_MAX_VAL);
	long double step = ComputeValue(IDC_STEP);
	int 	   decimals = ComputeValue(IDC_DECIMAL_PLACES);

	if(min >= max)
		{
		MessageBox("The minimum must be less than the maximum.", ERROR_TITLE, MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
		return;
		}
	if(step <= 0)
		{
		MessageBox("The step must be greater than zero.", ERROR_TITLE, MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
		return;
		}
	if(decimals < -1 || decimals > 15)
		{
		MessageBox("Decimal places must be between 0 and 15", ERROR_TITLE, MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
		return;
		}

	BeginWaitCursor();

	m_ctrlTableList.DeleteAllItems();

	CString variable;
	switch(m_Mode)
		{
		case EUCLIDEAN: variable="x"; break;
		case POLAR: variable="t"; break;
		default: variable="x"; break;
		}
	
	CString xtText;
	CString strAnswer;
	long double xt=min;
	long double answer;
	int nColumns=1;
	
	for (int i=0;xt <= max;)
	{
	
		g_Calculator->DecimalToString(xtText, xt);
		CleanupFormatAnswer(xtText);
		
		m_ctrlTableList.InsertItem(LVIF_TEXT|LVIF_STATE, i, xtText, 0, LVIS_SELECTED,0, 0);

		nColumns = 1;
		for(int j=0; j < MAX_EQUATIONS; ++j)
			if(m_Eqs[j].disp)
				{
				if(g_Calculator->Compute(m_Eqs[j].eq, variable, xt, answer, this->m_hWnd) == SUCCESSFULL)
					{
					if(-HUGE_VAL == answer || HUGE_VAL == answer)
						strAnswer = "overflow";	
					else
						{
						if(decimals == -1) // -1 is float
							{
							g_Calculator->DecimalToString(strAnswer, answer);
							CleanupFormatAnswer(strAnswer);
							}
						else
							{
							strAnswer.Format("%.*f", decimals, answer);
							ConvertCleanupFormatAnswer(strAnswer);
							}
						}
					m_ctrlTableList.SetItemText(i, nColumns, strAnswer);
					}
				else
					m_ctrlTableList.SetItemText(i, nColumns, "error");				
				++nColumns;
				}
		xt=min+(++i*step);
	}

	EndWaitCursor();
}

void C2DTableViewDlg::OnHelpButton() 
{
	OnHelp();
}

void C2DTableViewDlg::OnHelp() 
{
	LoadHelpFile(HELP_PAGE_2D_TABLEVIEW);
}

void C2DTableViewDlg::ExportToCSV(CString strFile)
{
	::ofstream outfile;
	CString CSline;

	outfile.open(strFile);
	
	long double min = ComputeValue(IDC_MIN_VAL);
	long double max = ComputeValue(IDC_MAX_VAL);
	long double step = ComputeValue(IDC_STEP);
	int 	   decimals = ComputeValue(IDC_DECIMAL_PLACES);

	BeginWaitCursor();

	CString variable;
	switch(m_Mode)
		{
		case EUCLIDEAN: variable="x"; break;
		case POLAR: variable="t"; break;
		default: variable="x"; break;
		}
	
	CString xtText;
	CString strAnswer;
	long double xt=min;
	long double answer;
	bool bFirst = true;
	
	for (int i=0;xt < max;)
	{	
		g_Calculator->DecimalToString(xtText, xt);
		CleanupFormatAnswer(xtText);
		
		xtText += ";";
		outfile.write(xtText.GetBuffer(xtText.GetLength()), xtText.GetLength());

		bFirst = true;
		for(int j=0; j < MAX_EQUATIONS; ++j)
		{
			if(m_Eqs[j].disp)
				{
				if(!bFirst)
					outfile.write(";", 1);

				if(g_Calculator->Compute(m_Eqs[j].eq, variable, xt, answer, this->m_hWnd) == SUCCESSFULL)
					{
					if(-HUGE_VAL == answer || HUGE_VAL == answer)
						strAnswer = "overflow";	
					else
						{
						if(decimals == -1) // -1 is float
							{
							g_Calculator->DecimalToString(strAnswer, answer);
							CleanupFormatAnswer(strAnswer);
							}
						else
							{
							strAnswer.Format("%.*f", decimals, answer);
							ConvertCleanupFormatAnswer(strAnswer);
							}
						}
					outfile.write(strAnswer.GetBuffer(strAnswer.GetLength()), strAnswer.GetLength());
					}
				else
					outfile.write("error", 5);	
				bFirst = false;
				}
		}
		outfile.write("\n", 1);
		xt=min+(++i*step);
	}

	EndWaitCursor();	
	outfile.close();
}

void C2DTableViewDlg::OnExport() 
{
	long double min = ComputeValue(IDC_MIN_VAL);
	long double max = ComputeValue(IDC_MAX_VAL);
	long double step = ComputeValue(IDC_STEP);
	int 	   decimals = ComputeValue(IDC_DECIMAL_PLACES);

	if(min >= max)
		{
		MessageBox("The minimum must be less than the maximum.", ERROR_TITLE, MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
		return;
		}
	if(step <= 0)
		{
		MessageBox("The step must be greater than zero.", ERROR_TITLE, MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
		return;
		}
	if(decimals < -1 || decimals > 15)
		{
		MessageBox("Decimal places must be between 0 and 15", ERROR_TITLE, MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
		return;
		}	

	static char BASED_CODE szFilter[] = "Tab delimited(*.txt)|*.txt||";	

	CFileDialog *fileDlg = new CFileDialog(false, 
										   "gcl",
										    NULL,
											OFN_ENABLESIZING 
											| OFN_CREATEPROMPT
											| OFN_HIDEREADONLY 
											| OFN_OVERWRITEPROMPT,
											szFilter,
											this);

	if(fileDlg->DoModal() == IDOK){
		ExportToCSV(fileDlg->GetPathName());
		MessageBox("Export completed!", "Export", MB_OK | MB_SETFOREGROUND);
	}
}

void C2DTableViewDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 485;
	lpMMI->ptMinTrackSize.y = 200;
}

void C2DTableViewDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	RECT rc;
	GetClientRect(&rc);
		
	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_TABLE);
    if(pWnd != NULL){
		pWnd->SetWindowPos(this, 11, 89, rc.right-20, rc.bottom-89-9, SWP_NOOWNERZORDER | SWP_NOZORDER);
	}
}
