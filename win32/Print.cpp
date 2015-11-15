// Print.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "Print.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrint dialog


CPrint::CPrint(CWnd* pParent /*=NULL*/)
	: CDialog(CPrint::IDD, pParent), m_PrintDlg(true, PD_RETURNDC)
									 /*m_PrintDlg(true, PD_ENABLEPRINTHOOK
													| PD_HIDEPRINTTOFILE
													| PD_NOPAGENUMS
													| PD_NOSELECTION
													| PD_PAGENUMS
													| PD_USEDEVMODECOPIESANDCOLLATE)*/
{
	//{{AFX_DATA_INIT(CPrint)
	m_bCenter = TRUE;
	m_bEquations = FALSE;
	m_sHeight = _T("4.0");
	m_sHUnits = _T("inches");
	m_sWidth = _T("4.0");
	m_sWUnits = _T("inches");
	m_bTitleOn = FALSE;
	m_sTitle = _T("");
	m_iPageSize = 1;
	//}}AFX_DATA_INIT
	
	m_PrintDlg.GetDefaults();
	m_PrintDlg.m_pd.Flags = 320;
	m_bRepaintPreview = true;
}

void CPrint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrint)
	DDX_Check(pDX, IDC_CENTER, m_bCenter);
	DDX_Check(pDX, IDC_EQUATIONS, m_bEquations);
	DDX_Text(pDX, IDC_HEIGHT, m_sHeight);
	DDX_CBString(pDX, IDC_HEIGHT_UNITS, m_sHUnits);
	DDX_Text(pDX, IDC_WIDTH, m_sWidth);
	DDX_CBString(pDX, IDC_WIDTH_UNITS, m_sWUnits);
	DDX_Check(pDX, IDC_TITLE_ON, m_bTitleOn);
	DDX_Text(pDX, IDC_TITLE, m_sTitle);
	DDV_MaxChars(pDX, m_sTitle, 25);
	DDX_Radio(pDX, IDC_PAGESIZE, m_iPageSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrint, CDialog)
	//{{AFX_MSG_MAP(CPrint)
	ON_BN_CLICKED(IDC_SETUP, OnSetup)
	ON_BN_CLICKED(IDC_TITLE_ON, OnTitleOn)
	ON_BN_CLICKED(IDC_CENTER, OnCenter)
	ON_BN_CLICKED(IDC_EQUATIONS, OnEquations)
	ON_EN_CHANGE(IDC_WIDTH, OnChangeWidth)
	ON_EN_CHANGE(IDC_HEIGHT, OnChangeHeight)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_WIDTH_UNITS, OnSelchangeWidthUnits)
	ON_CBN_SELCHANGE(IDC_HEIGHT_UNITS, OnSelchangeHeightUnits)
	ON_BN_CLICKED(IDC_AUTOSIZE, OnAutosize)
	ON_BN_CLICKED(IDC_PAGESIZE, OnPagesize)
	ON_BN_CLICKED(IDC_SPECIFY, OnSpecify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrint message handlers

BOOL CPrint::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetDlgItemText(IDC_PRINTER, m_PrintDlg.GetDeviceName());

	OnTitleOn();
	OnAutosize();
	UpdateSizeView();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrint::OnSetup() 
{
	PRINTDLG print;
	print = m_PrintDlg.m_pd;
	m_bRepaintPreview = false;

	if(IDCANCEL == m_PrintDlg.DoModal()){
		m_PrintDlg.m_pd = print;
		InvalidatePreview();
		m_bRepaintPreview = true;
		return;
	}
	
	SetDlgItemText(IDC_PRINTER, m_PrintDlg.GetDeviceName());
	m_bRepaintPreview = true;
	InvalidatePreview();
}

void CPrint::OnTitleOn() 
{
	CWnd* item =  GetDlgItem(IDC_TITLE);

	if(BST_CHECKED == IsDlgButtonChecked(IDC_TITLE_ON))
		item->EnableWindow();
	else
		item->EnableWindow(false);

	InvalidatePreview();
}

void CPrint::OnCenter() { InvalidatePreview();}

void CPrint::OnEquations() { InvalidatePreview();}

void CPrint::OnChangeWidth() { InvalidatePreview();}

void CPrint::OnChangeHeight() {	InvalidatePreview();}

void CPrint::OnPaint() 
{
	if(m_bRepaintPreview){
		CWnd* item = GetDlgItem(IDC_PREVIEW_FRAME);
		CRect prerect;
		item->GetWindowRect(prerect);
		ScreenToClient(prerect);
		
		int obase = m_Calculator->m_base;
		m_Calculator->m_base = 10;
		
		UpdateData();
		CDC print_dc;
		print_dc.Attach(m_PrintDlg.GetPrinterDC());         // Attach a printer DC
		
		CPaintDC dc(this); // device context for painting
		CPoint ul(prerect.left + 10, prerect.top + 19);
		CRect print_rect(0,0, print_dc.GetDeviceCaps(HORZRES), print_dc.GetDeviceCaps(VERTRES));
		CRect window_rect(0,0,prerect.Width() - 20, prerect.Height() - 25);
		double scale_factor;
		
		TRACE("print_rect.Width=%d print_rect.Height=%d\n", print_rect.Width(), print_rect.Height());
		
		if((double(print_rect.Width())/double(print_rect.Height())) >
			(double(window_rect.Width())/double(window_rect.Height())))
			scale_factor = double(window_rect.Width()) / double(print_rect.Width());
		else
			scale_factor = double(window_rect.Height()) / double(print_rect.Height());
		
		CPoint start;
		start.x = ul.x + (double(window_rect.Width() - (print_rect.Width() * scale_factor)) / 2.0);
		start.y = ul.y + (double(window_rect.Height() - (print_rect.Height() * scale_factor)) / 2.0);
		
		//////////// DRAW PAPER
		CBrush brush(RGB(255,255,255)), *pOldBrush;
		pOldBrush = dc.SelectObject(&brush);
		CPen penBlack;
		penBlack.CreatePen(PS_SOLID, 0, RGB(0,0,0));
		CPen* pOldPen = dc.SelectObject(&penBlack);
		
		dc.Rectangle(start.x - 3, start.y - 3, 
			start.x + (print_rect.Width() * scale_factor) + 3, 
			start.y + (print_rect.Height() * scale_factor) + 3);
		dc.SelectObject(pOldPen);
		//////////// END DRAW PAPER
		
		//////////// Calculate width and height
		long double w, h;
		
		if(m_iPageSize == 1){
			double scale;
			if((double(print_rect.Width()) / double(m_graph_width)) > 
				(double(print_rect.Height()) / double(m_graph_height)))
				scale = (double(print_rect.Height()) / 2.0) / double(m_graph_height);
			else
				scale = (double(print_rect.Width()) / 2.0) / double(m_graph_width);
			
			h = (double(m_graph_height)/double(print_dc.GetDeviceCaps(LOGPIXELSY))) * scale;
			w = (double(m_graph_width)/double(print_dc.GetDeviceCaps(LOGPIXELSX))) * scale;
		}
		else if(m_iPageSize == 0){
			w = double(print_rect.Width()) / double(print_dc.GetDeviceCaps(LOGPIXELSX));
			h = double(print_rect.Height()) / double(print_dc.GetDeviceCaps(LOGPIXELSY));
		}
		else{
			m_Calculator->StringToDecimal(m_sWidth, 10, w);
			m_Calculator->StringToDecimal(m_sHeight, 10, h);
			w = m_Calculator->abs(w);
			h = m_Calculator->abs(h);
			// convert width
			if(m_sWUnits == "cm")
				w *= 0.39370078740157;
			// convert height
			if(m_sHUnits == "cm")
				h *= 0.39370078740157;
		}
		
		// I now have desired width and height in inches
		CPoint gstart(start.x, start.y);
		
		double max_h((double(print_rect.Height()) / double(print_dc.GetDeviceCaps(LOGPIXELSY))));
		double max_w((double(print_rect.Width()) / double(print_dc.GetDeviceCaps(LOGPIXELSX))));
		
		// resize max height based on printing options
		if(m_bTitleOn){
			max_h -= (0.25 + 0.125);
			gstart.y += ((0.25 + 0.125) * print_dc.GetDeviceCaps(LOGPIXELSY) * scale_factor);
		}
		if(m_bEquations)
			max_h -= (1.5 + 0.125);
		
		// error check for desired size too large too large
		if(w > (max_w + 0.0001)){
			w = max_w;
			m_Calculator->DecimalToString(m_sWidth, w);
			if(m_iPageSize == 2)
				SetDimensionsW(w);
		}
		if(h > (max_h + 0.0001)){
			h = max_h;
			m_Calculator->DecimalToString(m_sHeight, h);
			if(m_iPageSize == 2)
				SetDimensionsH(h);
		}
		
		// now convert inches into device units (ie device pixels)
		w *= print_dc.GetDeviceCaps(LOGPIXELSX) * scale_factor;			// scale w for window
		h *= print_dc.GetDeviceCaps(LOGPIXELSY) * scale_factor;			// scale h for window
		//////////// END Calculate width and height
		
		//////////// Draw Graph Rectangle
		CBrush gray(RGB(128,128,128));
		dc.SelectObject(&gray);
		
		if(m_bCenter){
			gstart.x += ((print_rect.Width() * scale_factor) / 2.0) - (w / 2.0);
			
			double th(h);
			if(m_bTitleOn)
				th += ((0.25 + 0.125) * print_dc.GetDeviceCaps(LOGPIXELSY) * scale_factor);
			if(m_bEquations)
				th += ((1.5 + 0.125) * print_dc.GetDeviceCaps(LOGPIXELSY) * scale_factor);
			
			gstart.y += (double(print_rect.Height() * scale_factor) / 2.0) - (double(th) / 2.0);
		}
		dc.Rectangle(gstart.x, 
			gstart.y, 
			gstart.x + w, 
			gstart.y + h);
		//////////// END Draw Graph Rectangle
		
		if(m_bEquations){
			//////////// Draw Equations List
			CPoint estart(gstart.x, gstart.y + h +(0.125 * print_dc.GetDeviceCaps(LOGPIXELSY) * scale_factor));
			CPoint eend(gstart.x + w, gstart.y + h + (1.625 * print_dc.GetDeviceCaps(LOGPIXELSY) * scale_factor));
			
			int ew(w);
			
			if(ew < (5 * print_dc.GetDeviceCaps(LOGPIXELSX) * scale_factor)) // check for min eqs list size
				ew = (5 * print_dc.GetDeviceCaps(LOGPIXELSX) * scale_factor);
			
			if(ew > (max_w * print_dc.GetDeviceCaps(LOGPIXELSX) * scale_factor))
				ew = max_w;
			if((eend.y - estart.y) > (max_h * print_dc.GetDeviceCaps(LOGPIXELSY) * scale_factor))
				eend.y = estart.y + max_h;
			
			estart.x = (gstart.x + (double(w) / 2.0)) - (double(ew) / 2.0);
			if(estart.x < start.x)
				estart.x = start.x;
			
			eend.x = estart.x + ew;
			
			dc.SelectObject(&brush);
			dc.Rectangle(estart.x, estart.y, eend.x, eend.y);
			//////////// END Draw Equations List
		}
		
		if(m_bTitleOn){
			//////////// Draw Title Rectangle
			dc.SelectObject(&brush);
			dc.Rectangle(start.x, 
				start.y, 
				start.x + (print_rect.Width() * scale_factor), 
				start.y + (0.25 * print_dc.GetDeviceCaps(LOGPIXELSY) * scale_factor));
			//////////// END Draw Title Rectangle
		}
		
		dc.SelectObject(pOldBrush);
		print_dc.Detach();
		UpdateData(true);
		
		m_Calculator->m_base = obase;
	}
	
}

void CPrint::SetDimensionsH(double h)
{
	if(m_sHUnits == "cm")
		h /= 0.39370078740157;
	
	m_Calculator->DecimalToString(m_sHeight, h);
	SetDlgItemText(IDC_HEIGHT, m_sHeight);
}

void CPrint::SetDimensionsW(double w)
{
	if(m_sWUnits == "cm")
		w /= 0.39370078740157;
	
	m_Calculator->DecimalToString(m_sWidth, w);
	SetDlgItemText(IDC_WIDTH, m_sWidth);
}

void CPrint::OnSelchangeWidthUnits() {	InvalidatePreview();}

void CPrint::OnSelchangeHeightUnits() {	InvalidatePreview();}

void CPrint::OnSpecify() {	UpdateSizeView();}

void CPrint::OnAutosize() {	UpdateSizeView();}

void CPrint::OnPagesize() {	UpdateSizeView();}

void CPrint::UpdateSizeView()
{
	UpdateData();
	CWnd* item =  GetDlgItem(IDC_STATIC_WIDTH);

	if(2 == m_iPageSize)
	{
		item->EnableWindow();
		item =  GetDlgItem(IDC_WIDTH);
		item->EnableWindow();
		item =  GetDlgItem(IDC_WIDTH_UNITS);
		item->EnableWindow();
		item =  GetDlgItem(IDC_STATIC_HEIGHT);
		item->EnableWindow();
		item =  GetDlgItem(IDC_HEIGHT);
		item->EnableWindow();
		item =  GetDlgItem(IDC_HEIGHT_UNITS);
		item->EnableWindow();
	}
	else
	{
		item->EnableWindow(false);
		item =  GetDlgItem(IDC_WIDTH);
		item->EnableWindow(false);
		item =  GetDlgItem(IDC_WIDTH_UNITS);
		item->EnableWindow(false);
		item =  GetDlgItem(IDC_STATIC_HEIGHT);
		item->EnableWindow(false);
		item =  GetDlgItem(IDC_HEIGHT);
		item->EnableWindow(false);
		item =  GetDlgItem(IDC_HEIGHT_UNITS);
		item->EnableWindow(false);
	}
	InvalidatePreview();
}

void CPrint::InvalidatePreview()
{
	CWnd* item = GetDlgItem(IDC_PREVIEW_FRAME);
	CRect prerect;
	item->GetWindowRect(prerect);
	ScreenToClient(prerect);
	InvalidateRect(prerect, true);
}
