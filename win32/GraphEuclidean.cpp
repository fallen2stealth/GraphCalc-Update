#include "GraphEuclidean.h"
#include "globals.h"
extern CCalculator *g_Calculator;

extern VariableT GetVariable(CString var, long double num);
struct SPoint;
extern SPoint g_DrawFontSize;

CGraphEuclidean::CGraphEuclidean(){
	m_EuclideanRange.Ymin = m_PrevEuclideanRange.Ymin = -10;
	m_EuclideanRange.Ymax = m_PrevEuclideanRange.Ymax = 10;
	m_EuclideanRange.Yscl = m_PrevEuclideanRange.Yscl = 1;
	m_EuclideanRange.Xmin = m_PrevEuclideanRange.Xmin = -10;
	m_EuclideanRange.Xmax = m_PrevEuclideanRange.Xmax = 10;
	m_EuclideanRange.Xscl = m_PrevEuclideanRange.Xscl = 1;
	
	m_LinePrec = 100;
}

CGraphEuclidean::~CGraphEuclidean(){


}

/*********************************************************/
// CGraphView::StoreCurrentRange()
// Pre: none
// Post: range is stored
// Return Value: none
// Intent: to store the current range
/*********************************************************/
void CGraphEuclidean::StoreCurrentRange()
{
	m_PrevEuclideanRange.Ymin = m_EuclideanRange.Ymin;
	m_PrevEuclideanRange.Ymax = m_EuclideanRange.Ymax;
	m_PrevEuclideanRange.Yscl = m_EuclideanRange.Yscl;
	m_PrevEuclideanRange.Xmin = m_EuclideanRange.Xmin;
	m_PrevEuclideanRange.Xmax = m_EuclideanRange.Xmax;
	m_PrevEuclideanRange.Xscl = m_EuclideanRange.Xscl;
}

/*********************************************************/
// CGraphView::SetPreviousRange()
// Pre: none
// Post: none
// Return Value: none
// Intent: sets the previous range
/*********************************************************/
void CGraphEuclidean::SetPreviousRange()
{
	m_EuclideanRange.Ymin = m_PrevEuclideanRange.Ymin;
	m_EuclideanRange.Ymax = m_PrevEuclideanRange.Ymax;
	m_EuclideanRange.Yscl = m_PrevEuclideanRange.Yscl;
	m_EuclideanRange.Xmin = m_PrevEuclideanRange.Xmin;
	m_EuclideanRange.Xmax = m_PrevEuclideanRange.Xmax;
	m_EuclideanRange.Xscl = m_PrevEuclideanRange.Xscl;
}

/*********************************************************/
// CGraphView::SwapPrevCurRanges()
// Pre: none
// Post: ranges are swapped
// Return Value: none
// Intent: to swp the previous range with the current one
/*********************************************************/
void CGraphEuclidean::SwapPrevCurRanges()
{
	double xmax = m_EuclideanRange.Xmax;
	double xmin = m_EuclideanRange.Xmin;
	double xscl = m_EuclideanRange.Xscl;
	double ymax = m_EuclideanRange.Ymax;
	double ymin = m_EuclideanRange.Ymin;
	double yscl = m_EuclideanRange.Yscl;
	
	m_EuclideanRange.Ymin = m_PrevEuclideanRange.Ymin;
	m_EuclideanRange.Ymax = m_PrevEuclideanRange.Ymax;
	m_EuclideanRange.Yscl = m_PrevEuclideanRange.Yscl;
	m_EuclideanRange.Xmin = m_PrevEuclideanRange.Xmin;
	m_EuclideanRange.Xmax = m_PrevEuclideanRange.Xmax;
	m_EuclideanRange.Xscl = m_PrevEuclideanRange.Xscl;
	
	m_PrevEuclideanRange.Ymin = ymin;
	m_PrevEuclideanRange.Ymax = ymax;
	m_PrevEuclideanRange.Yscl = yscl;
	m_PrevEuclideanRange.Xmin = xmin;
	m_PrevEuclideanRange.Xmax = xmax;
	m_PrevEuclideanRange.Xscl = xscl;
}

bool CGraphEuclidean::DrawEquation(const EquationT &eqT, 
								   const SEquationStyle &style, 
								   const CRect &window, 
								   CCalculator *pCalculator,
								   CDC *pDC)
{
	CPen *pen = new CPen, *pOldPen;
	ErrorT error;
	
	pen->CreatePen(PS_SOLID, style.size, eqT.color);
	pOldPen = pDC->SelectObject(pen);
	
	long double x(m_EuclideanRange.Xmin), y;	
	long double x_step((m_EuclideanRange.Xmax - m_EuclideanRange.Xmin) / double(window.Width()) / (m_LinePrec / 100.0));

	bool first(true);
	int prev_y, y_coord(0), x_coord;
	CRect Threshold(0, 0 - GRAPH_THRESHOLD, window.Width(), window.Height() + GRAPH_THRESHOLD);
	pCalculator->SetErrorMode(ERROR_MODE_SILENT);
	
	for(int j(0); j < window.Width(); ++j){
		
		
		if((error = pCalculator->Compute(eqT.eq, "x", (m_EuclideanRange.Xmin + (j*x_step)), y, 0)) != SUCCESSFULL){
			if(DIV_ZERO == error)
				continue; // we can just ignore this and continue
			
			pCalculator->SetErrorMode(ERROR_MODE_COMPLETE);
			pDC->SelectObject(pOldPen);
			delete pen;	
			return false;
		}
		
		prev_y = y_coord;
		y_coord = ((m_EuclideanRange.Ymax - y) / (double((m_EuclideanRange.Ymax - m_EuclideanRange.Ymin))/double(window.Height()))) + window.top;
		x_coord = (double(j) / (double(m_LinePrec)/100.0)) + window.left;		
				
		if(style.line == GRAPH_STYLE_LINE){
			// checking for graph out of view
			if((prev_y > window.bottom) && (y_coord < window.top))
				pDC->MoveTo(x_coord, window.top);
			else if((prev_y < window.top) && (y_coord > window.bottom))
				pDC->MoveTo(x_coord, window.bottom);
			
			if(-HUGE_VAL == y || HUGE_VAL == y)
				first = true;
			else if(Threshold.PtInRect(CPoint(x_coord, y_coord))){
				if(first){
					pDC->MoveTo(x_coord, y_coord);
					first = false;
				}
				else
					pDC->LineTo(x_coord, y_coord);
			}
		}
		else if(style.line == GRAPH_STYLE_POINT){
			pDC->SetPixel(x_coord, y_coord, eqT.color);
		}
	}
	
	pCalculator->SetErrorMode(ERROR_MODE_COMPLETE);
	pDC->SelectObject(pOldPen);
	delete pen;	
	return true;
}

void CGraphEuclidean::DrawXLabel(long double x, CRect window, CDC *pDC, 
						DrawE destination, double font_size, COLORREF color)
{
	pDC->SetTextColor(color);
	CFont fontText;
	CString str;

	if(destination == PRINT)
		fontText.CreateFont(pDC->GetDeviceCaps(LOGPIXELSY)*0.08, 
							pDC->GetDeviceCaps(LOGPIXELSX)*0.05,
							0,0,400,FALSE,FALSE,0,ANSI_CHARSET, OUT_DEFAULT_PRECIS,
							DEFAULT_QUALITY, CLIP_DEFAULT_PRECIS, DEFAULT_PITCH | FF_SWISS, "Arial");
	else
		fontText.CreateFont(font_size-2,0,0,0,400,FALSE,FALSE,0,ANSI_CHARSET, OUT_DEFAULT_PRECIS,
							DEFAULT_QUALITY, CLIP_DEFAULT_PRECIS, DEFAULT_PITCH | FF_SWISS, "Arial");

	CFont *pOldFont = (CFont*) pDC->SelectObject(&fontText);
	pDC->SetBkMode(TRANSPARENT);

	str.Format("%.5f", x);
	DecimalForDisplay(str);
		
	pDC->SetTextAlign(TA_CENTER);

	if(destination != PRINT)
		pDC->TextOut(GraphToScreenX(window, x, 100), GetXAxisY(window)-(2+font_size), str);
	else
		;  // TODO: enable this for printing	

	pDC->SelectObject(pOldFont);	
}

void CGraphEuclidean::DrawGrid(const SLineStyle &style, 
							   bool &grid_on, 
							   const CRect window, 
							   CDC *pDC,
							   DrawE destination, 
							   double font_size, 
							   COLORREF color,
							   int label_interval)
{
	int x, y;
	double x_ratio, y_ratio;
	int height, width, vert_y, vert_x, horz_y, horz_x;

	x_ratio = (m_EuclideanRange.Xmax-m_EuclideanRange.Xmin)/window.Width();
	y_ratio = (m_EuclideanRange.Ymax-m_EuclideanRange.Ymin)/window.Height();


	long double x_scale = m_EuclideanRange.Xscl;
	long double y_scale = m_EuclideanRange.Yscl;

	/////////  VALIDATE GRID DENSITY //////////////
	if((x_scale/x_ratio) < 4)
		x_scale = x_ratio*4;

	if((y_scale/y_ratio) < 4)
		y_scale = y_ratio*4;
	/////////  END VALIDATE GRID DENSITY //////////////

	// calculate x and y coordiantes which start x and y axis
	x = GetYAxisX(window);
	y = GetXAxisY(window);

	while(x < 0)
		x = int(x + x_scale/x_ratio);
	
	while(x > window.Width())
		x = int(x - x_scale/x_ratio);

	while(y < 0)
		y = int(y + y_scale/y_ratio);
	
	while(y > window.Height())
		y = int(y - y_scale/y_ratio);

	// determine length of lines
	if(grid_on){
		height = window.Height();
		width = window.Width();
		vert_y = 0;
		horz_x = 0;
	}
	else{
		height = 10;
		width = 10;
		vert_y = y - height/2;
		horz_x = x - width/2;
	}

	// Brush needed Draw the x and y axis
	CPen *grid, *pOldPen;
	grid = new CPen;
	grid->CreatePen(PS_SOLID, style.size, style.color);
	pOldPen = pDC->SelectObject(grid);
	/////////////////////////////////////
	int count;

	// convert values to offset in window
	vert_y += window.top;
	horz_x += window.left;

	// draw lines left of y axis
	count = 1;
	vert_x = GraphToScreenX(window, -1 * x_scale * count++, 100);
	
	while((vert_x > 0) && ((m_EuclideanRange.Ymin <= 0 && m_EuclideanRange.Ymax >= 0) || grid_on)){
		if(vert_x >= window.left){
			pDC->MoveTo(CPoint(vert_x, vert_y));
			pDC->LineTo(CPoint(vert_x, vert_y + height));

			// draw x value
			if((label_interval != 0) && (count % label_interval) == 0)
				DrawXLabel(-1 * x_scale * (count-1), window, pDC, SCRN, font_size, color);
		}
		vert_x = GraphToScreenX(window, -1 * x_scale * count++, 100);
	}
	
	// draw lines right of y axis
	count = 1;
	vert_x = GraphToScreenX(window, x_scale * count++, 100);
	
	while((vert_x < window.Width()) && ((m_EuclideanRange.Ymin <= 0 && m_EuclideanRange.Ymax >= 0) || grid_on)){
		if(vert_x <= window.right){
			pDC->MoveTo(CPoint(vert_x, vert_y));
			pDC->LineTo(CPoint(vert_x, vert_y + height));

			// draw x value
			if((label_interval != 0) && (count % label_interval) == 0)
				DrawXLabel(x_scale * (count-1), window, pDC, SCRN, font_size, color);
		}
		vert_x = GraphToScreenX(window, x_scale * count++, 100);
	}
	
	// draw lines above x axis
	count = 1;
	horz_y = GraphToScreenY(window, y_scale * count++);
	
	while((horz_y > 0) && ((m_EuclideanRange.Xmin <= 0 && m_EuclideanRange.Xmax >= 0) || grid_on)){
		if(horz_y >= window.top){
			pDC->MoveTo(CPoint(horz_x, horz_y));
			pDC->LineTo(CPoint(horz_x + width, horz_y));
		}
		horz_y = GraphToScreenY(window, y_scale * count++);
	}
	
	// draw lines below x axis
	count = 1;
	horz_y = GraphToScreenY(window, -1 * y_scale * count++);
	
	while((horz_y < window.Height()) && ((m_EuclideanRange.Xmin <= 0 && m_EuclideanRange.Xmax >= 0) || grid_on)){
		if(horz_y <= window.bottom){
			pDC->MoveTo(CPoint(horz_x, horz_y));
			pDC->LineTo(CPoint(horz_x + width, horz_y));
		}
		horz_y = GraphToScreenY(window, -1 * y_scale * count++);
	}

	pDC->SelectObject(pOldPen);
	delete grid;
}

/*********************************************************/
// DrawAxis
// Pre: none
// Post: axis are drawn to pDC
// Return Value: none
// Intent: to draw the axis of the graph
/*********************************************************/
void CGraphEuclidean::DrawAxis(const SLineStyle &style, 
							   const CRect window, 
							   CDC *pDC)
{
	int y_axis_x, y_axis_y, x_axis_y, x_axis_x;

	y_axis_x = int(window.Width() - ((m_EuclideanRange.Xmax * window.Width()) / (m_EuclideanRange.Xmax-m_EuclideanRange.Xmin)));
	y_axis_y = int(window.Height());
	x_axis_y = int((m_EuclideanRange.Ymax * window.Height()) / (m_EuclideanRange.Ymax-m_EuclideanRange.Ymin));
	x_axis_x = int(window.Width());

	CPen *axis = new CPen, *pOldPen;
	axis->CreatePen(PS_SOLID, style.size, style.color);
	pOldPen = pDC->SelectObject(axis);

	// Draw Y-axis
	pDC->MoveTo(y_axis_x + window.left, window.top);
	pDC->LineTo(y_axis_x + window.left, y_axis_y + window.top);
	// Draw X-axis
	pDC->MoveTo(window.left, x_axis_y + window.top);
	pDC->LineTo(x_axis_x + window.left, x_axis_y + window.top);

	pDC->SelectObject(pOldPen);
	delete axis;
}

ErrorT CGraphEuclidean::DyDx(const CString eq, 
								  CCalculator *pCalculator, 
								  long double x,
								  long double &outAns)
{
	long double x1, x2, y1, y2, delta_x = 0.000001;
	ErrorT ec = SUCCESSFULL;
	x1 = x - delta_x;
	x2 = x + delta_x;
	outAns = 0;

	if((ec = pCalculator->Compute(eq, "x" , x1, y1, 0)) != SUCCESSFULL)	return ec;
	if((ec = pCalculator->Compute(eq, "x" , x2, y2, 0)) != SUCCESSFULL)	return ec;

	outAns = ((y2-y1)/(x2-x1));
	return ec;
}

CString CGraphEuclidean::GetTangentEquation(const CString eq, 
											CCalculator *pCalculator,
											long double x)
{
	long double y, m, b;
	DyDx(eq, pCalculator, x, m);

	if(pCalculator->Compute(eq, "x" , x, y, 0) != SUCCESSFULL)	return "0";
	b = y - (m*x);

	CString yS, mS, bS;
	pCalculator->DecimalToString(yS, y);
	pCalculator->DecimalToString(mS, m);
	pCalculator->DecimalToString(bS, b);
	return mS + " * x + " + bS;
}

void CGraphEuclidean::DrawTangentLine(const EquationT &eqT,
									  const long double &x, 
									  const SEquationStyle &style, 
									  const CRect window, 
									  CCalculator *pCalculator,
									  DrawE destination,
									  CDC *pDC)
{
	CString tangentEq = GetTangentEquation(eqT.eq, pCalculator, x);

	long double y1, y2;

	if(pCalculator->Compute(tangentEq, "x" , m_EuclideanRange.Xmin, y1, 0) != SUCCESSFULL)	return;
	if(pCalculator->Compute(tangentEq, "x" , m_EuclideanRange.Xmax, y2, 0) != SUCCESSFULL)	return;
	
	int y_coord_1 = GraphToScreenY(window, y1);
	int x_coord_1 = GraphToScreenX(window, m_EuclideanRange.Xmin, 100);
	int y_coord_2 = GraphToScreenY(window, y2);
	int x_coord_2 = GraphToScreenX(window, m_EuclideanRange.Xmax, 100);

	CPen *pen = new CPen, *pOldPen;
	pen->CreatePen(PS_SOLID, style.size, eqT.color);
	pOldPen = pDC->SelectObject(pen);

	pDC->MoveTo(x_coord_1, y_coord_1);
	pDC->LineTo(x_coord_2, y_coord_2);
	
	pDC->SelectObject(pOldPen);
	delete pen;
}

/*********************************************************/
// CGraphEuclidean::DrawCoordsLabels(CDC *pDC)
// Pre: none
// Post: coordinates and/or labels drawn on graph
// Return Value: none
// Intent: to draw coordinates and labels on graph
/*********************************************************/
void CGraphEuclidean::DrawCoordsLabels(const double font_size,
									   const bool coords,
									   const bool labels,
									   const COLORREF color,
									   const CRect window, 
									   DrawE destination,
									   CDC *pDC)
{
	// calculate x and y coordiantes which start x and y axis
	int x = GetYAxisX(window) + window.left;
	int y = GetXAxisY(window) + window.top;

	pDC->SetTextColor(color);
	CFont fontText;
	CString str;

	if(destination == PRINT)
		fontText.CreateFont(pDC->GetDeviceCaps(LOGPIXELSY)*0.08, 
							pDC->GetDeviceCaps(LOGPIXELSX)*0.05,
							0,0,400,FALSE,FALSE,0,ANSI_CHARSET, OUT_DEFAULT_PRECIS,
							DEFAULT_QUALITY, CLIP_DEFAULT_PRECIS, DEFAULT_PITCH | FF_SWISS, "Arial");
	else
		fontText.CreateFont(font_size,0,0,0,400,FALSE,FALSE,0,ANSI_CHARSET, OUT_DEFAULT_PRECIS,
							DEFAULT_QUALITY, CLIP_DEFAULT_PRECIS, DEFAULT_PITCH | FF_SWISS, "Arial");

	CFont *pOldFont = (CFont*) pDC->SelectObject(&fontText);
	pDC->SetBkMode(TRANSPARENT);

	// draw -x information ///////////////////////////
	if(labels && coords)
		str = "-X: " + ConvertForDisplay(m_EuclideanRange.Xmin, 4);
	else if(coords)
		str = ConvertForDisplay(m_EuclideanRange.Xmin, 4);
	else if(labels)
		str = "-X";
	pDC->SetTextAlign(TA_LEFT);
	if(destination == PRINT)
		pDC->TextOut((pDC->GetDeviceCaps(LOGPIXELSX)*0.02), y+(pDC->GetDeviceCaps(LOGPIXELSY)*0.001), str);
	else
		pDC->TextOut(2, y+6, str);

	// draw x information ///////////////////////////
	if(labels && coords)
		str = "X: " + ConvertForDisplay(m_EuclideanRange.Xmax, 4);
	else if(coords)
		str =  ConvertForDisplay(m_EuclideanRange.Xmax, 4);
	else if(labels)
		str = "X";
	pDC->SetTextAlign(TA_RIGHT);
	if(destination == PRINT)
		pDC->TextOut(window.right-(pDC->GetDeviceCaps(LOGPIXELSX)*0.02), y+(pDC->GetDeviceCaps(LOGPIXELSY)*0.001), str);
	else
		pDC->TextOut(window.right-2, y+6, str);

	// draw y information ///////////////////////////
	if(labels && coords)
		str = "Y: " +  ConvertForDisplay(m_EuclideanRange.Ymax, 4);
	else if(coords)
		str = ConvertForDisplay(m_EuclideanRange.Ymax, 4);
	else if(labels)
		str = "Y";
	pDC->SetTextAlign(TA_CENTER);
	if(destination == PRINT)
		pDC->TextOut(x, (pDC->GetDeviceCaps(LOGPIXELSY)*0.02), str);
	else
		pDC->TextOut(x, 2, str);

	// draw -y information ///////////////////////////
	if(labels && coords)
		str = "-Y: " + ConvertForDisplay(m_EuclideanRange.Ymin, 4);
	else if(coords)
		str = ConvertForDisplay(m_EuclideanRange.Ymin, 4);
	else if(labels)
		str = "-Y";
	if(destination == PRINT)
		pDC->TextOut(x, window.bottom-(pDC->GetDeviceCaps(LOGPIXELSY)*0.1), str);
	else
		pDC->TextOut(x, window.bottom - font_size - 1, str);
	
	pDC->SelectObject(pOldFont);
}


CString CGraphEuclidean::GetTraceDyDxStr(const CString eq)
{
	long double slope;
	CString str;

	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
	
	if(DIV_ZERO == DyDx(eq, g_Calculator, m_TraceX, slope))
		str = "undefined";
	else if(-HUGE_VAL == slope || HUGE_VAL == slope)
		str = "vertical line: infinite slope";
	else
		g_Calculator->DecimalToStringSci(str, slope, 10);
	
	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);

	return str;
}

CString CGraphEuclidean::GetDyDxStr(const CString eq, long double x)
{
	long double slope;
	CString str;
	
	if(DIV_ZERO == DyDx(eq, g_Calculator, x, slope))
		str = "undefined";
	else if(-HUGE_VAL == slope || HUGE_VAL == slope)
		str = "dy/dx = vertical line: infinite slope";
	else
		str.Format("dy/dx = %.4f", slope);

	return str;
}

void CGraphEuclidean::DrawDistance(DistStatusE distance,
								   const CString &EqOne,
								   const CString &EqTwo,
								   const long double &OneX,
								   const long double &TwoX,
								   const COLORREF bgcolor,
								   const CRect window, 
								   DrawE destination,
								   const SEquationStyle &style, 
								   CCalculator *pCalculator,
								   CDC *pDC)
{	
	
	long double y1, y2;

	if(pCalculator->Compute(EqOne, "x", OneX, y1, 0) != SUCCESSFULL)	return;
	if(pCalculator->Compute(EqTwo, "x", TwoX, y2, 0) != SUCCESSFULL)	return;
	
	int y_coord_1, x_coord_1, y_coord_2, x_coord_2;
	
	y_coord_1 = GraphToScreenY(window, y1);
	x_coord_1 = GraphToScreenX(window, OneX, m_LinePrec);
	y_coord_2 = GraphToScreenY(window, y2);
	x_coord_2 = GraphToScreenX(window, TwoX, m_LinePrec);
	
	CPen pen;
	int rop = pDC->GetROP2();
	
	if(distance == SECOND && destination != PRINT){
		pen.CreatePen(PS_SOLID, style.size, bgcolor);
		pDC->SetROP2(R2_NOT);
	}
	else if(destination == PRINT){
		pen.CreatePen(PS_SOLID, style.size, RGB(0,0,0));
		pDC->SetROP2(R2_COPYPEN);
	}
	else{
		pen.CreatePen(PS_SOLID, style.size, bgcolor);
		pDC->SetROP2(R2_NOTCOPYPEN);
	}

	CPen* pOldPen = pDC->SelectObject(&pen);
	pDC->MoveTo(x_coord_1, y_coord_1);
	pDC->LineTo(x_coord_2, y_coord_2);
	pDC->SetROP2(rop);
	pDC->SelectObject(pOldPen);
}

void CGraphEuclidean::EraseDistance(const CString &EqOne,
								   const CString &EqTwo,
								   const long double &OneX,
								   const long double &TwoX,
								   const COLORREF bgcolor,
								   const CRect window, 
								   const SEquationStyle &style, 
								   CCalculator *pCalculator,
								   CDC *pDC)
{
		
	long double y1, y2;
	if(pCalculator->Compute(EqOne, "x", OneX, y1, 0) != SUCCESSFULL)	return;
	if(pCalculator->Compute(EqTwo, "x", TwoX, y2, 0) != SUCCESSFULL)	return;
	
	int y_coord_1 = GraphToScreenY(window, y1);
	int x_coord_1 = GraphToScreenX(window, OneX, m_LinePrec); 
	int y_coord_2 = GraphToScreenY(window, y2);
	int x_coord_2 = GraphToScreenX(window, TwoX, m_LinePrec);
	
	CPen* pOldPen;
	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, style.size, bgcolor);
	pOldPen = pDC->SelectObject(&penBlack);
	
	int rop = pDC->GetROP2();
	pDC->SetROP2(R2_NOT);          /* Erases the previous line */
	pDC->MoveTo(x_coord_1, y_coord_1);
	pDC->LineTo(x_coord_2, y_coord_2);
	pDC->SelectObject(pOldPen);
	pDC->SetROP2(rop);
}


CString CGraphEuclidean::GetDistanceStr( const CString &EqOne,
										 const CString &EqTwo,
										 const long double &OneX,
										 const long double &TwoX,
										 CCalculator *pCalculator)
{
	CString str;
	long double y1, y2;

	if(pCalculator->Compute(EqOne, "x", OneX, y1, 0) != SUCCESSFULL)	return "";
	if(pCalculator->Compute(EqTwo, "x", TwoX, y2, 0) != SUCCESSFULL)	return "";
	
	double distance = sqrt( pow((TwoX - OneX), 2) + pow((y2 - y1), 2) );
	pCalculator->DecimalToStringSci(str, distance);
	return str;
}

void CGraphEuclidean::ClearPrevTrace(const CString eq,
									 CBitmap &bitmap,
									 const CRect window,
									 CCalculator *pCalculator,
									 CDC *pDC)
{
	// draw graph bitmap just over section where cross was displayed /////////
	long double prev_traceY;

	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
	if(pCalculator->Compute(eq, "x", ScreenToGraphX(window, m_PrevTracePixel, m_LinePrec), prev_traceY, 0) != SUCCESSFULL) return;
	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);

	int prev_y_coord = GraphToScreenY(window, prev_traceY);
	int prev_x_coord = GraphToScreenX(window, ScreenToGraphX(window, m_PrevTracePixel, m_LinePrec), 100);
	
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap *pOldBitmap = MemDC.SelectObject(&bitmap);

	// draw graph bitmap over last position of cursor
	pDC->BitBlt(prev_x_coord - 15, prev_y_coord - 15, 
				30, 30, 
				&MemDC, 
				prev_x_coord - 15, prev_y_coord - 15, 
				SRCCOPY);

	MemDC.SelectObject(pOldBitmap);
	DeleteDC(MemDC);
}

bool CGraphEuclidean::AutoPan(long double y, CCalculator *pCalculator)
{
	long double rangex(m_EuclideanRange.Xmax - m_EuclideanRange.Xmin);
	long double rangey(m_EuclideanRange.Ymax - m_EuclideanRange.Ymin);

	long double distx(pCalculator->abs(0.1 * rangex));
	long double disty(pCalculator->abs(0.1 * rangey));

	long double borderx(pCalculator->abs(0.01 * rangex));
	long double bordery(pCalculator->abs(0.01 * rangey));

	if(m_TraceX >= (m_EuclideanRange.Xmax - borderx)){	
		m_EuclideanRange.Xmax = m_TraceX + distx;
		m_EuclideanRange.Xmin = m_EuclideanRange.Xmax - rangex;
		return true;
	}
	else if(m_TraceX <= (m_EuclideanRange.Xmin + borderx)){
		m_EuclideanRange.Xmin = m_TraceX - distx;
		m_EuclideanRange.Xmax = m_EuclideanRange.Xmin + rangex;
		return true;
	}
	if(y >= (m_EuclideanRange.Ymax - bordery)){
		m_EuclideanRange.Ymax = y + disty;
		m_EuclideanRange.Ymin = m_EuclideanRange.Ymax - rangey;
		return true;
	}
	else if(y <= (m_EuclideanRange.Ymin + bordery)){
		m_EuclideanRange.Ymin = y - disty;
		m_EuclideanRange.Ymax = m_EuclideanRange.Ymin + rangey;
		return true;
	}
	return false;
}

/*********************************************************/
// CGraphView::DrawTrace()
// Pre: none
// Post: the tracing cross is drawn
// Return Value: none
// Intent: to draw the cross for tracing and display the
//		   DY/DX at the current tracing point
/*********************************************************/
TraceRedrawMode CGraphEuclidean::DrawTrace(const CString eq,
								const CRect window,
								DrawE destination,
								CCalculator *pCalculator,
								CPen *pPen,
								CDC *pDC)
{
	int num_points = int((double(m_LinePrec)/100.0)*window.Width());
	double increment = (m_EuclideanRange.Xmax-m_EuclideanRange.Xmin) / num_points;
	++num_points;

	// figure out x and y coords of trace point
	long double traceY;

	pCalculator->SetErrorMode(ERROR_MODE_SILENT);
	if(pCalculator->Compute(eq, "x", m_TraceX, traceY, 0) != SUCCESSFULL) 
		{
		pCalculator->SetErrorMode(ERROR_MODE_COMPLETE);
		return TRACE_NONE;
		}

	while(-HUGE_VAL == traceY || HUGE_VAL == traceY){
		if(m_TracePixel > m_PrevTracePixel){
			--m_PrevTracePixel;
			--m_TracePixel;
		}
		else{
			++m_PrevTracePixel;
			++m_TracePixel;
		}

		m_TraceX = ScreenToGraphX(window, m_TracePixel, m_LinePrec);
		if(pCalculator->Compute(eq, "x", m_TraceX, traceY, 0) != SUCCESSFULL)
			{
			pCalculator->SetErrorMode(ERROR_MODE_COMPLETE);
			return TRACE_NONE;
			}
	}
	pCalculator->SetErrorMode(ERROR_MODE_COMPLETE);

	if(AutoPan(traceY, pCalculator))	return TRACE_PAN; 

	int x_coord = GraphToScreenX(window, m_TraceX, m_LinePrec);
	int y_coord = GraphToScreenY(window, traceY);


	// draw the cross
	CPen *pOldPen = pDC->SelectObject(pPen);
	int rop = pDC->GetROP2();
	pDC->SetROP2(R2_NOT);
	pDC->MoveTo(x_coord, y_coord - 10);
	pDC->LineTo(x_coord, y_coord + 10);
	pDC->MoveTo(x_coord - 10, y_coord);
	pDC->LineTo(x_coord + 10, y_coord);
	pDC->SelectObject(pOldPen);
	pDC->SetROP2(rop);

	return TRACE_NONE;
}

/*int CGraphEuclidean::GraphToBitmapX(const CRect window, 
									long double x, 
									int precision)
{
	return (window.left + int(((x - m_EuclideanRange.Xmin) / double((m_EuclideanRange.Xmax - m_EuclideanRange.Xmin) / (double(precision) * double(window.Width()) / 100.0)))));
}*/


/*int CGraphEuclidean::GraphToBitmapY(const CRect window, 
									long double y)
{
	long double y_ratio = double((m_EuclideanRange.Ymax-m_EuclideanRange.Ymin))/double(window.Height());
	return (window.top + int((m_EuclideanRange.Ymax - y) / y_ratio));
}*/


int CGraphEuclidean::GraphToScreenX(const CRect window, 
									long double x, 
									int precision)
{
	double points = (double(precision) * double(window.Width()) / 100.0);
	double increment = double((m_EuclideanRange.Xmax - m_EuclideanRange.Xmin) / points);
	return (int((x - m_EuclideanRange.Xmin) / increment) / (double(precision)/100.0)) + window.left;
}


int CGraphEuclidean::GraphToScreenY(const CRect window, long double y)
{
	long double y_ratio = double((m_EuclideanRange.Ymax-m_EuclideanRange.Ymin))/double(window.Height());
	return int((m_EuclideanRange.Ymax - y) / y_ratio) + window.top;
}

long double CGraphEuclidean::ScreenToGraphX(const CRect window, int x, int precision)
{
	double points = (double(precision) * double(window.Width()) / 100.0);
	double increment = double((m_EuclideanRange.Xmax - m_EuclideanRange.Xmin) / points);
	return (m_EuclideanRange.Xmin + (double(x - window.left) * increment));
}

void CGraphEuclidean::ValidateRanges()
{
	if(m_EuclideanRange.Xmax > 99999999999999999.0)
		m_EuclideanRange.Xmax = 99999999999999999.0;
	if(m_EuclideanRange.Xmin < -99999999999999999.0)
		m_EuclideanRange.Xmin = -99999999999999999.0;
	if(m_EuclideanRange.Xscl <= 0)
		m_EuclideanRange.Xscl = 1;
	if(m_EuclideanRange.Ymax > 99999999999999999.0)
		m_EuclideanRange.Ymax = 999999999999999990.0;
	if(m_EuclideanRange.Ymin < -999999999999999990.0)
		m_EuclideanRange.Ymin = -99999999999999999.0;
	if(m_EuclideanRange.Yscl <= 0)
		m_EuclideanRange.Yscl = 1;
	
	if(m_EuclideanRange.Ymin >= m_EuclideanRange.Ymax){
		m_EuclideanRange.Ymax = 10;
		m_EuclideanRange.Ymin = -10;
	}
	if(m_EuclideanRange.Xmin >= m_EuclideanRange.Xmax){
		m_EuclideanRange.Xmax = 10;
		m_EuclideanRange.Xmin = -10;	
	}
	
	if(m_EuclideanRange.Xscl <= 0)
		m_EuclideanRange.Xscl = 1;
	if(m_EuclideanRange.Yscl <= 0)
		m_EuclideanRange.Yscl = 1;
}

void CGraphEuclidean::InitializeTrace(const CRect window)
{
	m_TraceX = 0.0;
	m_PrevTracePixel = m_TracePixel = GraphToScreenX(window, m_TraceX, m_LinePrec);
}

CString CGraphEuclidean::GetTraceXStr()
{
	CString str;
	g_Calculator->DecimalToStringSci(str, m_TraceX, 10);
	return str;
}

CString CGraphEuclidean::GetTraceYStr(CString eq)
{
	long double traceY;
	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
	if(g_Calculator->Compute(eq, "x", m_TraceX, traceY, 0) != SUCCESSFULL)
		{
		g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
		return "";
		}
	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);

	CString str;
	g_Calculator->DecimalToStringSci(str, traceY, 10);
	return str;
}

CString CGraphEuclidean::GetTraceCoordsStr(const CString eq, CCalculator *pCalculator)
{
	long double traceY;
	pCalculator->SetErrorMode(ERROR_MODE_SILENT);
	if(pCalculator->Compute(eq, "x", m_TraceX, traceY, 0) != SUCCESSFULL)
		{
		pCalculator->SetErrorMode(ERROR_MODE_COMPLETE);
		return "";
		}
	pCalculator->SetErrorMode(ERROR_MODE_COMPLETE);

	CString strX, strY;
	g_Calculator->DecimalToStringSci(strX, m_TraceX,7);
	g_Calculator->DecimalToStringSci(strY, traceY,7);
	return "x = " + strX + ", y = " + strY;
}

// gets the x-coord, relative to the upper left corner of the graph, of the y axis
int CGraphEuclidean::GetYAxisX(CRect window)
{
	return int(window.Width() - ((m_EuclideanRange.Xmax * window.Width()) / (m_EuclideanRange.Xmax-m_EuclideanRange.Xmin)));
}

// gets the y-coord, relative to the upper left corner of the graph, of the x axis
int CGraphEuclidean::GetXAxisY(CRect window)
{
	return int(((m_EuclideanRange.Ymax * window.Height()) / (m_EuclideanRange.Ymax-m_EuclideanRange.Ymin)));
}

