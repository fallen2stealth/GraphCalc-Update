// InsertUnitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "InsertUnitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsertUnitDlg dialog


CInsertUnitDlg::CInsertUnitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInsertUnitDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInsertUnitDlg)
	m_BaseUnit = _T("feet");
	m_Category = _T("Length");
	m_Name = _T("");
	m_Type = _T("english");
	m_Value = _T("");
	//}}AFX_DATA_INIT
	m_NewCat = false;
}

void CInsertUnitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsertUnitDlg)
	DDX_Control(pDX, IDC_UNITTYPE, m_TypeCtrl);
	DDX_Control(pDX, IDC_CATEGORY, m_CategoryCtrl);
	DDX_Text(pDX, IDC_BASEUNIT, m_BaseUnit);
	DDX_CBString(pDX, IDC_CATEGORY, m_Category);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDX_CBString(pDX, IDC_UNITTYPE, m_Type);
	DDX_Text(pDX, IDC_VALUE, m_Value);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsertUnitDlg, CDialog)
	//{{AFX_MSG_MAP(CInsertUnitDlg)
	ON_CBN_KILLFOCUS(IDC_UNITTYPE, OnKillfocusUnittype)
	ON_CBN_KILLFOCUS(IDC_CATEGORY, OnKillfocusCategory)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsertUnitDlg message handlers

void CInsertUnitDlg::OnKillfocusUnittype() 
{
	UpdateData(true);
	int size = m_Calculator->m_Categories.GetSize();

	for(int i(0); i < size; ++i)
		if(m_Calculator->m_Categories[i].name == m_Category)
			break;


	if(i == size)
		if(m_NewCat){
			if(m_Type == m_NewCategoryDlg.m_TypeOne)
				m_BaseUnit = m_NewCategoryDlg.m_BaseOne;
			else if(m_Type == m_NewCategoryDlg.m_TypeTwo)
				m_BaseUnit = m_NewCategoryDlg.m_BaseTwo;
		}
		else
			return; // error
	else{
		if(m_Type == m_Calculator->m_Categories[i].type_one)
			m_BaseUnit = m_Calculator->m_Categories[i].standard_one;
		else if(m_Type == m_Calculator->m_Categories[i].type_two)
			m_BaseUnit = m_Calculator->m_Categories[i].standard_two;
	}

	UpdateData(false);
}

void CInsertUnitDlg::OnKillfocusCategory() 
{
	UpdateData(true);
	int size = m_Calculator->m_Categories.GetSize();

	for(int i(0); i < size; ++i)
		if(m_Calculator->m_Categories[i].name == m_Category)
			break;

	
	if(i == size && !m_NewCat){
		m_NewCategoryDlg.m_Category = m_Category;

		if(m_NewCategoryDlg.DoModal() == IDOK){
			m_NewCat = true;

			m_TypeCtrl.DeleteString(0);
			m_TypeCtrl.DeleteString(0);
			m_TypeCtrl.InsertString(0, m_NewCategoryDlg.m_TypeOne);
			m_TypeCtrl.InsertString(1, m_NewCategoryDlg.m_TypeTwo);
			m_TypeCtrl.SelectString(0, m_NewCategoryDlg.m_TypeOne);
			m_Type = m_NewCategoryDlg.m_TypeOne;

			m_CategoryCtrl.AddString(m_NewCategoryDlg.m_Category);
			m_CategoryCtrl.SelectString(0, m_NewCategoryDlg.m_Category);
		}

	}
	else if(m_NewCat && i == size){
		m_TypeCtrl.DeleteString(0);
		m_TypeCtrl.DeleteString(0);
		m_TypeCtrl.InsertString(0, m_NewCategoryDlg.m_TypeOne);
		m_TypeCtrl.InsertString(1, m_NewCategoryDlg.m_TypeTwo);
		m_TypeCtrl.SelectString(0, m_NewCategoryDlg.m_TypeOne);
		m_Type = m_NewCategoryDlg.m_TypeOne;
	}
	else if(i == size)
		return;
	else{
		m_TypeCtrl.DeleteString(0);
		m_TypeCtrl.DeleteString(0);
		m_TypeCtrl.InsertString(0, m_Calculator->m_Categories[i].type_one);	
		m_TypeCtrl.InsertString(1, m_Calculator->m_Categories[i].type_two);
		m_TypeCtrl.SelectString(0, m_Calculator->m_Categories[i].type_one);	
		m_Type = m_Calculator->m_Categories[i].type_one;
	}

	UpdateData(false);

	OnKillfocusUnittype();
}

BOOL CInsertUnitDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int size = m_Calculator->m_Constants.GetSize();

	for(int i(0); i < size; ++i)
		m_CategoryCtrl.InsertString(i, m_Calculator->m_Categories[i].name);

	m_TypeCtrl.InsertString(0, m_Calculator->m_Categories[0].type_one);	
	m_TypeCtrl.InsertString(1, m_Calculator->m_Categories[0].type_two);

	m_CategoryCtrl.SelectString(0, m_Calculator->m_Categories[0].name);	
	m_TypeCtrl.SelectString(0, m_Calculator->m_Categories[0].type_one);	

	OnKillfocusUnittype();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
