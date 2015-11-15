// GraphOptionsTwo.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "GraphOptionsTwo.h"
#include "GraphOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GraphOptionsTwo property page

IMPLEMENT_DYNCREATE(GraphOptionsTwo, CPropertyPage)

GraphOptionsTwo::GraphOptionsTwo() : CPropertyPage(GraphOptionsTwo::IDD)
{
	//{{AFX_DATA_INIT(GraphOptionsTwo)
	m_Axis = TRUE;
	m_Coords = TRUE;
	m_Labels = FALSE;
	m_Grid = FALSE;
	m_Width = 1;
	m_ZoomPerc = 20;
	m_ZoomDecPrec = 0.05;
	m_CursorPos = TRUE;
	m_Style = -1;
	m_GridSize = 2;
	m_AxisSize = 1;
	m_FixedGrid = TRUE;
	m_strFontSize = _T("");
	m_fGridLabels = true;
	m_nGridLabelInterval = 2;
	//}}AFX_DATA_INIT

	m_fDirty = false;
	
	m_BackgroundClr.SetSelectionMode(CP_MODE_BK);
	m_BackgroundClr.SetBkColour(RGB(255,255,255));
	m_AxisClr.SetSelectionMode(CP_MODE_BK);
	m_AxisClr.SetBkColour(RGB(90,90,90));
	m_GridClr.SetSelectionMode(CP_MODE_BK);
	m_GridClr.SetBkColour(RGB(215,215,215));
	m_CoordsClr.SetSelectionMode(CP_MODE_BK);
	m_CoordsClr.SetBkColour(RGB(128,128,128));
	m_TextClr.SetSelectionMode(CP_MODE_BK);
	m_TextClr.SetBkColour(RGB(192,128,128));
	m_AreaClr.SetSelectionMode(CP_MODE_BK);
	m_AreaClr.SetBkColour(RGB(192,192,230));
}

GraphOptionsTwo::~GraphOptionsTwo()
{
}

void GraphOptionsTwo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GraphOptionsTwo)
	DDX_Control(pDX, IDC_COLOR_BACKGROUND, m_BackgroundClr);
	DDX_Control(pDX, IDC_COLOR_AXIS, m_AxisClr);
	DDX_Control(pDX, IDC_COLOR_GRID, m_GridClr);
	DDX_Control(pDX, IDC_COLOR_COORDS, m_CoordsClr);
	DDX_Control(pDX, IDC_COLOR_TEXT, m_TextClr);
	DDX_Control(pDX, IDC_COLOR_AREA, m_AreaClr);
	DDX_Check(pDX, IDC_AXIS, m_Axis);
	DDX_Check(pDX, IDC_COORDS, m_Coords);
	DDX_Check(pDX, IDC_LABELS, m_Labels);
	DDX_Check(pDX, IDC_GRID, m_Grid);
	DDX_Text(pDX, IDC_WIDTH, m_Width);
	DDV_MinMaxInt(pDX, m_Width, 1, 50);
	DDX_Slider(pDX, IDC_ZOOM, m_ZoomPerc);
	DDX_Text(pDX, IDC_ZOOM_DEC_PREC, m_ZoomDecPrec);
	DDV_MinMaxDouble(pDX, m_ZoomDecPrec, 5.e-006, 10000.);
	DDX_Check(pDX, IDC_CURSOR_POS, m_CursorPos);
	DDX_Radio(pDX, IDC_LINE_STYLE, m_Style);
	DDX_Text(pDX, IDC_GRID_SIZE, m_GridSize);
	DDV_MinMaxInt(pDX, m_GridSize, 1, 50);
	DDX_Text(pDX, IDC_AXIS_SIZE, m_AxisSize);
	DDV_MinMaxInt(pDX, m_AxisSize, 1, 50);
	DDX_Check(pDX, IDC_FIXED_GRID, m_FixedGrid);
	DDX_CBString(pDX, IDC_FONT_SIZE, m_strFontSize);
	DDV_MaxChars(pDX, m_strFontSize, 2);
	DDX_Check(pDX, IDC_GRID_LABEL_ON, m_fGridLabels);
	DDX_Text(pDX, IDC_GRID_LABEL_INTERVAL, m_nGridLabelInterval);
	DDV_MinMaxInt(pDX, m_nGridLabelInterval, 1, 10000000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GraphOptionsTwo, CPropertyPage)
	//{{AFX_MSG_MAP(GraphOptionsTwo)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_GRID, OnGrid)
	ON_BN_CLICKED(IDC_AXIS, OnAxis)
	ON_BN_CLICKED(IDC_COORDS, OnCoords)
	ON_BN_CLICKED(IDC_LABELS, OnLabels)
	ON_EN_CHANGE(IDC_WIDTH, OnChangeWidth)
	ON_EN_CHANGE(IDC_ZOOM_DEC_PREC, OnChangeZoomDecPrec)
	ON_BN_CLICKED(IDC_COLOR_AXIS, OnColorAxis)
	ON_BN_CLICKED(IDC_COLOR_BACKGROUND, OnColorBackground)
	ON_BN_CLICKED(IDC_COLOR_COORDS, OnColorCoords)
	ON_BN_CLICKED(IDC_COLOR_GRID, OnColorGrid)
	ON_BN_CLICKED(IDC_COLOR_TEXT, OnColorText)
	ON_BN_CLICKED(IDC_COLOR_AREA, OnColorArea)
	ON_BN_CLICKED(IDC_CURSOR_POS, OnCursorPos)
	ON_BN_CLICKED(IDC_LINE_STYLE, OnStyle)
	ON_EN_CHANGE(IDC_AXIS_SIZE, OnChangeAxisSize)
	ON_EN_CHANGE(IDC_GRID_SIZE, OnChangeGridSize)
	ON_BN_CLICKED(IDC_FIXED_GRID, OnChangeFixedGrid)
	ON_BN_CLICKED(IDC_RADIO3, OnStyle)
	ON_CBN_EDITUPDATE(IDC_FONT_SIZE, OnChangeFontSize)
	ON_CBN_SELCHANGE(IDC_FONT_SIZE, OnChangeFontSize)
	ON_BN_CLICKED(IDC_GRID_LABEL_ON, OnGridLabels)
	ON_EN_CHANGE(IDC_GRID_LABEL_INTERVAL, SetDirty)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GraphOptionsTwo message handlers

/*********************************************************/
// GraphOptionsTwo::OnInitDialog()
// Pre: none
// Post: none
// Return Value: handled by parent function
// Intent: to initialize variables and control items
/*********************************************************/
BOOL GraphOptionsTwo::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CString str;
	// Set Zoom Control
	if(m_ZoomPerc > 1000)
		m_ZoomPerc = 1000;

	CSliderCtrl *pSlide = (CSliderCtrl*) GetDlgItem(IDC_ZOOM);
	pSlide->SetRange(100,1000, true);
	pSlide->SetPos(m_ZoomPerc);
	str.Format("%d%%", m_ZoomPerc);
	SetDlgItemText(IDC_ZOOMTRACK, str);

	// Set Spin controls
	CSpinButtonCtrl *pSpin = (CSpinButtonCtrl*) GetDlgItem(IDC_WIDTH_SPIN);
	pSpin->SetRange(1, 50);
	pSpin->SetPos(m_Width);

	pSpin = (CSpinButtonCtrl*) GetDlgItem(IDC_AXIS_SIZE_SPIN);
	pSpin->SetRange(1, 50);
	pSpin->SetPos(m_AxisSize);

	pSpin = (CSpinButtonCtrl*) GetDlgItem(IDC_GRID_SIZE_SPIN);
	pSpin->SetRange(1, 50);
	pSpin->SetPos(m_GridSize);
	//////////////////////

	m_BackgroundClr.SetTrackSelection(true);
	m_AxisClr.SetTrackSelection(true);
	m_GridClr.SetTrackSelection(true);
	m_CoordsClr.SetTrackSelection(true);
	m_TextClr.SetTrackSelection(true);
	m_AreaClr.SetTrackSelection(true);

	// init grid labels
	if(m_nGridLabelInterval == 0)
		{
		CheckDlgButton(IDC_GRID_LABEL_ON, 0);
		m_fGridLabels = false;
		SetDlgItemInt(IDC_GRID_LABEL_INTERVAL, 2);
		}
	else
		CheckDlgButton(IDC_GRID_LABEL_ON, 1);
	
	GetDlgItem(IDC_GRID_LABEL_INTERVAL)->EnableWindow(m_fGridLabels);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************/
// GraphOptionsTwo::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
// Pre: none
// Post: controls updated
// Return Value: none
// Intent: to handle the user moving the sliders for the various
//		   settings
/*********************************************************/
void GraphOptionsTwo::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(pScrollBar->GetDlgCtrlID() == IDC_ZOOM){

		//Control Zoom Percent
		CSliderCtrl* pSlide = (CSliderCtrl*) pScrollBar;
		CString str;
		m_ZoomPerc = pSlide->GetPos();
		str.Format("%d%%", m_ZoomPerc);
		SetDlgItemText(IDC_ZOOMTRACK, str);
	}

	SetDirty();
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}

/*********************************************************/
// GraphOptionsTwo::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle the user changing the linw width
//		   with the spin control
/*********************************************************/
void GraphOptionsTwo::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(nSBCode == SB_ENDSCROLL){
		return;
	}

	if(pScrollBar->GetDlgCtrlID() == IDC_WIDTH_SPIN){
		UpdateData(true);
		m_Width = nPos;
		UpdateData(false);
		SetDirty();
	}
	else if(pScrollBar->GetDlgCtrlID() == IDC_AXIS_SIZE_SPIN){
		UpdateData(true);
		m_AxisSize = nPos;
		UpdateData(false);
		SetDirty();
	}
	else if(pScrollBar->GetDlgCtrlID() == IDC_GRID_SIZE_SPIN){
		UpdateData(true);
		m_GridSize = nPos;
		UpdateData(false);
		SetDirty();
	}

	CPropertyPage::OnVScroll(nSBCode, nPos, pScrollBar);
}

void GraphOptionsTwo::Grid(bool fDirty) 
{
	if(BST_CHECKED == IsDlgButtonChecked(IDC_GRID)){
		m_GridClr.ModifyStyle(WS_DISABLED, 0);
	}
	else{
		m_GridClr.ModifyStyle(0, WS_DISABLED);
	}

	m_GridClr.Invalidate();
	
	if(fDirty) SetDirty(); 
}
void GraphOptionsTwo::Axis(bool fDirty) 
{
	if(BST_CHECKED == IsDlgButtonChecked(IDC_AXIS)){
		m_AxisClr.ModifyStyle(WS_DISABLED, 0);
	}
	else{
		m_AxisClr.ModifyStyle(0, WS_DISABLED);
	}

	m_AxisClr.Invalidate();
	
	if(fDirty) SetDirty(); 
}
void GraphOptionsTwo::Coords(bool fDirty) 
{
	if(BST_CHECKED == IsDlgButtonChecked(IDC_COORDS)){
		m_CoordsClr.ModifyStyle(WS_DISABLED, 0);
	}
	else{
		m_CoordsClr.ModifyStyle(0, WS_DISABLED);
	}

	m_CoordsClr.Invalidate();
	
	if(fDirty) SetDirty(); 
}

void GraphOptionsTwo::Style(bool fDirty) 
{
	UpdateData();

	CWnd* width =  GetDlgItem(IDC_WIDTH);
	CWnd* width_spin =  GetDlgItem(IDC_WIDTH_SPIN);
	CWnd* sizet =  GetDlgItem(IDC_SIZET);

	if(m_Style == 0){
		width->EnableWindow();
		width_spin->EnableWindow();
		sizet->EnableWindow();
	}
	else{
		width->EnableWindow(false);
		width_spin->EnableWindow(false);
		sizet->EnableWindow(false);
	}

	if(fDirty) SetDirty(); 
}

void GraphOptionsTwo::OnGrid() 
{
	Grid(true);
}
void GraphOptionsTwo::OnAxis() 
{
	Axis(true);
}
void GraphOptionsTwo::OnCoords() 
{
	Coords(true);
}
void GraphOptionsTwo::OnStyle() 
{
	Style(true);
}
void GraphOptionsTwo::OnLabels() { SetDirty();}
void GraphOptionsTwo::OnChangeZoomDecPrec() { SetDirty();}
void GraphOptionsTwo::OnCursorPos() {SetDirty();}


void GraphOptionsTwo::SetDirty() 
{
	m_fDirty = true;
	SetModified(true);
}

/*********************************************************/
// GraphOptionsTwo::OnApply()
// Pre: none
// Post: message is sent to CGrphCalcDlg
// Return Value: parent handles this
// Intent: to send notification to parent dlg that the user
//		   has hit th eapply button
/*********************************************************/
BOOL GraphOptionsTwo::OnApply() 
{
	if(m_fDirty)
		{
		CDialog* pDlg = STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
		pDlg->SendMessage(WM_USER_CHANGE_OBJECT_PROPERTIES, 0, 0);
		m_fDirty = false;
		}
	
	return CPropertyPage::OnApply();
}

void GraphOptionsTwo::OnColorAxis() { SetDirty(); m_AxisClr.OnClicked();}
void GraphOptionsTwo::OnColorBackground() { SetDirty(); m_BackgroundClr.OnClicked();}
void GraphOptionsTwo::OnColorCoords() { SetDirty(); m_CoordsClr.OnClicked();}
void GraphOptionsTwo::OnColorGrid() { SetDirty(); m_GridClr.OnClicked();}
void GraphOptionsTwo::OnColorText() { SetDirty(); m_TextClr.OnClicked();}
void GraphOptionsTwo::OnColorArea() { SetDirty(); m_AreaClr.OnClicked();}
void GraphOptionsTwo::OnChangeFixedGrid()   { SetDirty(); }
void GraphOptionsTwo::OnChangeFontSize()   { SetDirty(); }

BOOL GraphOptionsTwo::OnSetActive() 
{
	Coords(false);
	Axis(false);
	Grid(false);
	Style(false);

	return CPropertyPage::OnSetActive();
}


void GraphOptionsTwo::OnChangeWidth() 
{ 
	UpdateData();
	CSpinButtonCtrl *pSpin = (CSpinButtonCtrl*) GetDlgItem(IDC_WIDTH_SPIN);
	pSpin->SetPos(m_Width);
	SetDirty();
}

void GraphOptionsTwo::OnChangeAxisSize() 
{
	UpdateData();
	CSpinButtonCtrl *pSpin = (CSpinButtonCtrl*) GetDlgItem(IDC_AXIS_SIZE_SPIN);
	pSpin->SetPos(m_AxisSize);
	SetDirty();	
}

void GraphOptionsTwo::OnChangeGridSize() 
{
	UpdateData();
	CSpinButtonCtrl *pSpin = (CSpinButtonCtrl*) GetDlgItem(IDC_GRID_SIZE_SPIN);
	pSpin->SetPos(m_GridSize);
	SetDirty();
}

void GraphOptionsTwo::OnGridLabels() 
{
	SetDirty();

	if(BST_CHECKED == IsDlgButtonChecked(IDC_GRID_LABEL_ON))
		GetDlgItem(IDC_GRID_LABEL_INTERVAL)->EnableWindow(true);
	else
		GetDlgItem(IDC_GRID_LABEL_INTERVAL)->EnableWindow(false);
}

BOOL GraphOptionsTwo::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	LoadHelpFile(HELP_PAGE_2D_MISCDISPLAYCOMPONENTS);
	return true;
}
