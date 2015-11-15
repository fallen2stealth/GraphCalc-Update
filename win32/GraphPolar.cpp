#include "GraphPolar.h"
#include "globals.h"

struct SPoint;
extern SPoint g_DrawFontSize;

// Function name	: CGraphPolar::CGraphPolar
// Description	    : 
// Return type		: 
CGraphPolar::CGraphPolar(){

	m_PolarRange.Theta_min = 0;
	m_PolarRange.Theta_max = 2*PI;
	m_PolarRange.Theta_step = 0.01;
	m_PolarRange.GridAngle = PI/6;
	m_PolarRange.GridRadius = 3;
	m_PolarRange.Xmin = m_PrevPolarRange.Xmin = -5;
	m_PolarRange.Xmax = m_PrevPolarRange.Xmax = 5;
	m_PolarRange.Ymin = m_PrevPolarRange.Ymin = -5;
	m_PolarRange.Ymax = m_PrevPolarRange.Ymax = 5;

}

CGraphPolar::~CGraphPolar(){


}

// Function name	: CGraphPolar::StoreCurrentRange
// Description	    : 
// Return type		: void 
void CGraphPolar::StoreCurrentRange()
{
	m_PrevPolarRange.Ymin = m_PolarRange.Ymin;
	m_PrevPolarRange.Ymax = m_PolarRange.Ymax;
	m_PrevPolarRange.Xmin = m_PolarRange.Xmin;
	m_PrevPolarRange.Xmax = m_PolarRange.Xmax;
}

// Function name	: CGraphPolar::SetPreviousRange
// Description	    : 
// Return type		: void 
void CGraphPolar::SetPreviousRange()
{
	m_PolarRange.Ymin = m_PrevPolarRange.Ymin;
	m_PolarRange.Ymax = m_PrevPolarRange.Ymax;
	m_PolarRange.Xmin = m_PrevPolarRange.Xmin;
	m_PolarRange.Xmax = m_PrevPolarRange.Xmax;
}

// Function name	: CGraphPolar::SwapPrevCurRanges
// Description	    : 
// Return type		: void 
void CGraphPolar::SwapPrevCurRanges()
{
	double xmax = m_PolarRange.Xmax;
	double xmin = m_PolarRange.Xmin;
	double ymax = m_PolarRange.Ymax;
	double ymin = m_PolarRange.Ymin;
	
	m_PolarRange.Ymin = m_PrevPolarRange.Ymin;
	m_PolarRange.Ymax = m_PrevPolarRange.Ymax;
	m_PolarRange.Xmin = m_PrevPolarRange.Xmin;
	m_PolarRange.Xmax = m_PrevPolarRange.Xmax;
	
	m_PrevPolarRange.Ymin = ymin;
	m_PrevPolarRange.Ymax = ymax;
	m_PrevPolarRange.Xmin = xmin;
	m_PrevPolarRange.Xmax = xmax;
}


// Function name	: CGraphPolar::DrawEquation
// Description	    : 
// Return type		: void 
// Argument         : const EquationT &eqT
// Argument         : const SEquationStyle style
// Argument         : const CRect &window
// Argument         : CCalculator *pCalculator
// Argument         : CDC *pDC
bool CGraphPolar::DrawEquation(const EquationT &eqT, const SEquationStyle style, const CRect &window, CCalculator *pCalculator, CDC *pDC)
{
	CPen *pen = new CPen, *pOldPen;
	ErrorT error;
	long double r, x, y, t;
	long double points ((m_PolarRange.Theta_max - m_PolarRange.Theta_min) / m_PolarRange.Theta_step);


	pen->CreatePen(PS_SOLID, style.size, eqT.color);
	pOldPen = pDC->SelectObject(pen);
	
	bool first(true);
	int prev_x, prev_y, y_coord(0), x_coord(0);
	CRect Threshold(window.left - GRAPH_THRESHOLD, window.top - GRAPH_THRESHOLD, window.Width() + GRAPH_THRESHOLD, window.Height() + GRAPH_THRESHOLD);
		pCalculator->SetErrorMode(ERROR_MODE_SILENT);
	
	for(int j(0); j < points; ++j){
		
		if((error = pCalculator->Compute(eqT.eq, "t", (m_PolarRange.Theta_min + (j*m_PolarRange.Theta_step)), r, 0)) != SUCCESSFULL){
			if(DIV_ZERO == error)
				continue; // we can just ignore this and continue

			pCalculator->SetErrorMode(ERROR_MODE_COMPLETE);
			pDC->SelectObject(pOldPen);
			delete pen;	
			return false;
		}
		
		t = m_PolarRange.Theta_min + (j*m_PolarRange.Theta_step);

		if(pCalculator->m_trig_state == DEGREE)	t = pCalculator->DegToRadian(t);
		
		x = r * cos(t);
		y = r * sin(t);

		prev_y = y_coord;
		prev_x = x_coord;
		y_coord = window.top + ((m_PolarRange.Ymax - y) / (double((m_PolarRange.Ymax - m_PolarRange.Ymin))/double(window.Height())));
		x_coord = window.left +  int(   (x - m_PolarRange.Xmin) /  ((m_PolarRange.Xmax - m_PolarRange.Xmin) / double(window.Width())));		
		
		if(style.line == GRAPH_STYLE_LINE){
			if((prev_y > window.bottom) && (y_coord < window.top))
				pDC->MoveTo(x_coord, window.top);
			else if((prev_y < window.top) && (y_coord > window.bottom))
				pDC->MoveTo(x_coord, window.bottom);

			if(-HUGE_VAL == r || HUGE_VAL == r)
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
	
	// compute last r
	if(pCalculator->Compute(eqT.eq, "t",  m_PolarRange.Theta_max, r, 0) != SUCCESSFULL){
		if(DIV_ZERO == error)
			goto End;
		pCalculator->SetErrorMode(ERROR_MODE_COMPLETE);
		pDC->SelectObject(pOldPen);
		delete pen;	
		return false;
	}
	
	t = m_PolarRange.Theta_max;
	
	if(pCalculator->m_trig_state == DEGREE)	t = pCalculator->DegToRadian(t);
	
	x = r * cos(t);
	y = r * sin(t);
	
	prev_y = y_coord;
	prev_x = x_coord;
	y_coord = window.top + ((m_PolarRange.Ymax - y) / (double((m_PolarRange.Ymax - m_PolarRange.Ymin))/double(window.Height())));
	x_coord = window.left +  int(   (x - m_PolarRange.Xmin) /  ((m_PolarRange.Xmax - m_PolarRange.Xmin) / double(window.Width())));	
	
	if(style.line == GRAPH_STYLE_LINE){
		if((prev_y > window.bottom) && (y_coord < window.top))
			pDC->MoveTo(x_coord, window.top);
		else if((prev_y < window.top) && (y_coord > window.bottom))
			pDC->MoveTo(x_coord, window.bottom);
		
		if(-HUGE_VAL == r || HUGE_VAL == r)
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
	///////////////////////////////////////

	End:
		pCalculator->SetErrorMode(ERROR_MODE_COMPLETE);
		pDC->SelectObject(pOldPen);
		delete pen;	
		return true;
}


// Function name	: CGraphPolar::DrawGrid
// Description	    : 
// Return type		: void 
// Argument         : const SLineStyle style
// Argument         : const CRect window
// Argument         : CDC *pDC
void CGraphPolar::DrawGrid(const SLineStyle style,  const CRect window, CDC *pDC, CCalculator *pCalculator)
{
	DrawCircularGrid(style, window, pDC);
	DrawStarGrid(style, window, pDC, pCalculator);
}


// Function name	: CGraphPolar::GetMinMaxRings
// Description	    : 
// Return type		: void 
// Argument         : int &min_rings
// Argument         : int &max_rings
void CGraphPolar::GetMinMaxRings(int &min_rings, int &max_rings)
{
	long double diagonal, d1, d2, d3, d4;
	diagonal = sqrt(powf(m_PolarRange.Xmax - m_PolarRange.Xmin, 2.0) + powf(m_PolarRange.Ymax - m_PolarRange.Ymin, 2.0));
	d1 = sqrt(powf(m_PolarRange.Xmax, 2.0) + powf(m_PolarRange.Ymax, 2.0));
	d2 = sqrt(powf(m_PolarRange.Xmax, 2.0) + powf(m_PolarRange.Ymin, 2.0));
	d3 = sqrt(powf(m_PolarRange.Xmin, 2.0) + powf(m_PolarRange.Ymax, 2.0));
	d4 = sqrt(powf(m_PolarRange.Xmin, 2.0) + powf(m_PolarRange.Ymin, 2.0));
	
	// find farthest visible point on graph away from origin
	long double maxx(d1), minn(d1);
	if(d2 > maxx) maxx = d2;
	if(d3 > maxx) maxx = d3;
	if(d4 > maxx) maxx = d4;
	
	max_rings = int(maxx / m_PolarRange.GridRadius);
	

	// find closest visible part on graph to origin

	// get corners minimum value
	if(d2 < minn) minn = d2;
	if(d3 < minn) minn = d3;
	if(d4 < minn) minn = d4;

	// get edge minimum
	if(m_PolarRange.Xmax > 0 && m_PolarRange.Xmin < 0){				// stratle y-axis
		if(m_PolarRange.Ymax > 0 && m_PolarRange.Ymin < 0)			// stratle x axis
			minn = 0;
		else if(m_PolarRange.Ymax > 0 && m_PolarRange.Ymin > 0)		// above x-axis
			minn = m_PolarRange.Ymin;
		else if(m_PolarRange.Ymax < 0 && m_PolarRange.Ymin < 0)		// below x-axis
			minn = m_PolarRange.Ymax;
	}
	else if(m_PolarRange.Ymax > 0 && m_PolarRange.Ymin < 0){		// stratle x-axis
		if(m_PolarRange.Xmax > 0 && m_PolarRange.Xmin > 0)		// above y-axis
			minn = m_PolarRange.Xmin;
		else if(m_PolarRange.Xmax < 0 && m_PolarRange.Xmin < 0)		// below y-axis
			minn = m_PolarRange.Xmax;
	}

	min_rings = int(minn / m_PolarRange.GridRadius);
}


// Function name	: CGraphPolar::DrawCircularGrid
// Description	    : 
// Return type		: void 
// Argument         : const SLineStyle style
// Argument         : const CRect window
// Argument         : CDC *pDC
void CGraphPolar::DrawCircularGrid(const SLineStyle style,  const CRect window, CDC *pDC)
{
	double x_ratio = (m_PolarRange.Xmax-m_PolarRange.Xmin)/window.Width();
	double y_ratio = (m_PolarRange.Ymax-m_PolarRange.Ymin)/window.Height();

	long double grid_radius = m_PolarRange.GridRadius;
	/////////  VALIDATE GRID DENSITY //////////////
	if((grid_radius/x_ratio) < 4)
		grid_radius = x_ratio*4;
	if((grid_radius/y_ratio) < 4)
		grid_radius = y_ratio*4;
	/////////  END VALIDATE GRID DENSITY //////////////

	CPen *pen = new CPen, *pOldPen;
	pen->CreatePen(PS_SOLID, style.size, style.color);
	pOldPen = pDC->SelectObject(pen);
	
	long double theta_step(0.1);
	long double points((2*PI / theta_step));
	bool first(true);
	int y_coord(0), x_coord(0);
	CRect Threshold(window.left - GRAPH_THRESHOLD, window.top - GRAPH_THRESHOLD, window.Width() + GRAPH_THRESHOLD, window.Height() + GRAPH_THRESHOLD);
	
	// calc max diagonal
	int max_rings, min_rings;
	GetMinMaxRings(min_rings, max_rings);
	///////////////////

	for(int i(min_rings + 1); i <= max_rings; ++i){
		first = true;
		for(int j(0); j < points; ++j){
			
			long double x = i*grid_radius * cos((j*theta_step));
			long double y = i*grid_radius * sin((j*theta_step));
			
			y_coord = window.top + ((m_PolarRange.Ymax - y) / (double((m_PolarRange.Ymax - m_PolarRange.Ymin))/double(window.Height())));
			x_coord = window.left + int(   (x - m_PolarRange.Xmin) /  ((m_PolarRange.Xmax - m_PolarRange.Xmin) / double(window.Width())));		
			
			if(Threshold.PtInRect(CPoint(x_coord, y_coord))){
				if(first){
					pDC->MoveTo(x_coord, y_coord);
					first = false;
				}
				else
					pDC->LineTo(x_coord, y_coord);
			}
		}

		long double x = i*grid_radius * cos(2*PI);
		long double y = i*grid_radius * sin(2*PI);
		
		y_coord = window.top + ((m_PolarRange.Ymax - y) / (double((m_PolarRange.Ymax - m_PolarRange.Ymin))/double(window.Height())));
		x_coord = window.left + int(   (x - m_PolarRange.Xmin) /  ((m_PolarRange.Xmax - m_PolarRange.Xmin) / double(window.Width())));
		pDC->LineTo(x_coord, y_coord);
	}

	pDC->SelectObject(pOldPen);
	delete pen;	
}


// Function name	: CGraphPolar::DrawStarGrid
// Description	    : 
// Return type		: void 
// Argument         : const SLineStyle style
// Argument         : const CRect window
// Argument         : CDC *pDC
void CGraphPolar::DrawStarGrid(const SLineStyle style,  const CRect window, CDC *pDC, CCalculator *pCalculator)
{
	CPen *pen = new CPen, *pOldPen;
	pen->CreatePen(PS_SOLID, style.size, style.color);
	pOldPen = pDC->SelectObject(pen);

	long double grid_angle(m_PolarRange.GridAngle);
	if(pCalculator->m_trig_state == DEGREE) grid_angle = pCalculator->DegToRadian(grid_angle);
	
	long double angle(0), x=0, y=0;
	bool plot(true);
	int x2, y2;
	int y1 = window.top + (m_PolarRange.Ymax / (double((m_PolarRange.Ymax - m_PolarRange.Ymin))/double(window.Height())));
	int x1 = window.left + int(   (0 - m_PolarRange.Xmin) /  ((m_PolarRange.Xmax - m_PolarRange.Xmin) / double(window.Width()))   );
	
	for(; angle < 2*PI; angle += grid_angle){
		plot = true;

		if(angle >= 0 && angle <= ((PI/2.0) + 0.000000000001)	&& 
			m_PolarRange.Xmax >= 0 && m_PolarRange.Ymax >= 0){

			long double diff(angle - (PI/2));
			if(diff < 1e-10 && diff > -1e-10){
				y = m_PolarRange.Ymax;
				x = 0;
			}
			else{
				y = m_PolarRange.Xmax * tan(angle);
				x = m_PolarRange.Xmax;
			}
		}
		else if(angle > (PI/2) && angle <= PI && 
			m_PolarRange.Xmin < 0 && m_PolarRange.Ymax > 0){
			y = m_PolarRange.Xmin * tan(angle);
			x = m_PolarRange.Xmin;
		}
		else if(angle > PI && angle <= ((1.5*PI) + 0.000000000001)	&& 
			m_PolarRange.Xmin < 0 && m_PolarRange.Ymin < 0){
			
			long double diff(angle - (1.5*PI));
			if(diff < 1e-10 && diff > -1e-10){
				y = m_PolarRange.Ymin;
				x = 0;
			}
			else{
				y = m_PolarRange.Xmin * tan(angle);
				x = m_PolarRange.Xmin;
			}
		}
		else if(angle > (1.5*PI) && angle < (2*PI)	&& 
			m_PolarRange.Xmax >= 0 && m_PolarRange.Ymin <= 0){
			y = m_PolarRange.Xmax * tan(angle);
			x = m_PolarRange.Xmax;
		}
		else
			plot = false;
		
		if(plot){
			y2 = window.top + ((m_PolarRange.Ymax - y) / (double((m_PolarRange.Ymax - m_PolarRange.Ymin))/double(window.Height())));
			x2 = window.left + int(   (x - m_PolarRange.Xmin) /  ((m_PolarRange.Xmax - m_PolarRange.Xmin) / double(window.Width()))   );
			
			pDC->MoveTo(x1, y1);
			pDC->LineTo(x2, y2);
		}
	}	
	
	pDC->SelectObject(pOldPen);
	delete pen;	
}

// Function name	: CGraphPolar::DrawAxis
// Description	    : 
// Return type		: void 
// Argument         : const SLineStyle style
// Argument         : const CRect window
// Argument         : CDC *pDC
void CGraphPolar::DrawAxis(const SLineStyle style,  const CRect window, CDC *pDC)
{
	int y_axis_x, y_axis_y, x_axis_y, x_axis_x;

	y_axis_x = int(window.Width() - ((m_PolarRange.Xmax * window.Width()) / (m_PolarRange.Xmax-m_PolarRange.Xmin)));
	y_axis_y = int(window.Height());
	x_axis_y = int((m_PolarRange.Ymax * window.Height()) / (m_PolarRange.Ymax-m_PolarRange.Ymin));
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


// Function name	: CGraphPolar::DyDx
// Description	    : 
// Return type		: long double 
// Argument         : const CString eq
// Argument         : CCalculator *pCalculator
// Argument         : long double theta
ErrorT CGraphPolar::DyDx(const CString eq, CCalculator *pCalculator, 
							long double theta, long double &outAns)
{
	long double theta1, theta2, r1, r2, delta_theta = 0.000001;
	ErrorT ec = SUCCESSFULL;
	theta1 = theta - delta_theta;
	theta2 = theta + delta_theta;
	outAns = 0;

	if((ec = pCalculator->Compute(eq, "t", theta1, r1, 0)) != SUCCESSFULL)	return ec;
	if((ec = pCalculator->Compute(eq, "t", theta2, r2, 0)) != SUCCESSFULL)	return ec;

	long double x1 = r1 * cos(((pCalculator->m_trig_state == DEGREE) ? pCalculator->DegToRadian(theta1) : theta1));
	long double y1 = r1 * sin(((pCalculator->m_trig_state == DEGREE) ? pCalculator->DegToRadian(theta1) : theta1));
	long double x2 = r2 * cos(((pCalculator->m_trig_state == DEGREE) ? pCalculator->DegToRadian(theta2) : theta2));
	long double y2 = r2 * sin(((pCalculator->m_trig_state == DEGREE) ? pCalculator->DegToRadian(theta2) : theta2));

	outAns = ((y2-y1)/(x2-x1));
	return ec;
}


// Function name	: CGraphPolar::GetTangentEquation
// Description	    : 
// Return type		: CString 
// Argument         : const CString eq
// Argument         : CCalculator *pCalculator
// Argument         : long double theta
CString CGraphPolar::GetTangentEquation(const CString eq, CCalculator *pCalculator, long double theta)
{
	long double m, b, r;
	DyDx(eq, pCalculator, theta, m);
	
	if(m == HUGE_VAL || m == -HUGE_VAL)	return "infinite";

	if(pCalculator->Compute(eq, "t", theta, r, 0) != SUCCESSFULL)	return "0";


	long double x = r * cos(((pCalculator->m_trig_state == DEGREE) ? pCalculator->DegToRadian(theta) : theta));
	long double y = r * sin(((pCalculator->m_trig_state == DEGREE) ? pCalculator->DegToRadian(theta) : theta));
	b = y - (m*x);

	CString yS, mS, bS;
	pCalculator->DecimalToString(yS, y);
	pCalculator->DecimalToString(mS, m);
	pCalculator->DecimalToString(bS, b);
	return mS + " * x + " + bS;
}


// Function name	: CGraphPolar::DrawTangentLine
// Description	    : 
// Return type		: void 
// Argument         : const EquationT &eqT
// Argument         : const long double &theta
// Argument         : const SEquationStyle &style
// Argument         : const CRect window
// Argument         : CCalculator *pCalculator
// Argument         : DrawE destination
// Argument         : CDC *pDC
void CGraphPolar::DrawTangentLine(const EquationT &eqT,
								  const long double &theta, 
								  const SEquationStyle &style, 
								  const CRect window, 
								  CCalculator *pCalculator,
								  DrawE destination,
								  CDC *pDC)
{
	CString tangentEq = GetTangentEquation(eqT.eq, pCalculator, theta);

	if(tangentEq == "infinite") return;

	long double y1, y2;
	if(pCalculator->Compute(tangentEq, "x", m_PolarRange.Xmin, y1, 0) != SUCCESSFULL)	return;
	if(pCalculator->Compute(tangentEq, "x", m_PolarRange.Xmax, y2, 0) != SUCCESSFULL)	return;
	
	int y_coord_1 = GraphToScreenY(window, y1);
	int x_coord_1 = GraphToScreenX(window, m_PolarRange.Xmin);
	int y_coord_2 = GraphToScreenY(window, y2);
	int x_coord_2 = GraphToScreenX(window, m_PolarRange.Xmax);
	
	/*if(destination == BMP || destination == PRINT){
		y_coord_1 -= window.top;
		x_coord_1 -= window.left;
		y_coord_2 -= window.top;
		x_coord_2 -= window.left;
	}*/

	CPen *pen = new CPen, *pOldPen;
	pen->CreatePen(PS_SOLID, style.size, eqT.color);
	pOldPen = pDC->SelectObject(pen);

	pDC->MoveTo(x_coord_1, y_coord_1);
	pDC->LineTo(x_coord_2, y_coord_2);
	
	pDC->SelectObject(pOldPen);
	delete pen;
}


// Function name	: CGraphPolar::DrawCoordsLabels
// Description	    : 
// Return type		: void 
// Argument         : const bool coords
// Argument         : const bool labels
// Argument         : const COLORREF color
// Argument         : const CRect window
// Argument         : DrawE destination
// Argument         : CDC *pDC
void CGraphPolar::DrawCoordsLabels(const double font_size, const bool coords,const bool labels,const COLORREF color,const CRect window,  DrawE destination,CDC *pDC)
{
	// calculate x and y coordiantes which start x and y axis
	int x = window.left + int(window.Width() - ((m_PolarRange.Xmax * window.Width()) / (m_PolarRange.Xmax-m_PolarRange.Xmin)));
	int y = window.top + int(((m_PolarRange.Ymax * window.Height()) / (m_PolarRange.Ymax-m_PolarRange.Ymin)));

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
		str = "-X: " + ConvertForDisplay(m_PolarRange.Xmin, 4);
	else if(coords)
		str = ConvertForDisplay(m_PolarRange.Xmin, 4);
	else if(labels)
		str = "-X";
	pDC->SetTextAlign(TA_LEFT);
	if(destination == PRINT)
		pDC->TextOut((pDC->GetDeviceCaps(LOGPIXELSX)*0.02), y+(pDC->GetDeviceCaps(LOGPIXELSY)*0.001), str);
	else
		pDC->TextOut(2, y+6, str);

	// draw x information ///////////////////////////
	if(labels && coords)
		str = "X: " + ConvertForDisplay(m_PolarRange.Xmax, 4);
	else if(coords)
		str = ConvertForDisplay(m_PolarRange.Xmax, 4);
	else if(labels)
		str = "X";
	pDC->SetTextAlign(TA_RIGHT);
	if(destination == PRINT)
		pDC->TextOut(window.right-(pDC->GetDeviceCaps(LOGPIXELSX)*0.02), y+(pDC->GetDeviceCaps(LOGPIXELSY)*0.001), str);
	else
		pDC->TextOut(window.right-2, y+6, str);

	// draw y information ///////////////////////////
	if(labels && coords)
		str = "Y: " + ConvertForDisplay(m_PolarRange.Ymax, 4);
	else if(coords)
		str = ConvertForDisplay(m_PolarRange.Ymax, 4);
	else if(labels)
		str = "Y";
	pDC->SetTextAlign(TA_CENTER);
	if(destination == PRINT)
		pDC->TextOut(x, (pDC->GetDeviceCaps(LOGPIXELSY)*0.02), str);
	else
		pDC->TextOut(x, 2, str);

	// draw -y information ///////////////////////////
	if(labels && coords)
		str = "-Y: " + ConvertForDisplay(m_PolarRange.Ymin, 4);
	else if(coords)
		str = ConvertForDisplay(m_PolarRange.Ymin, 4);
	else if(labels)
		str = "-Y";
	if(destination == PRINT)
		pDC->TextOut(x, window.bottom-(pDC->GetDeviceCaps(LOGPIXELSY)*0.1), str);
	else
		pDC->TextOut(x, window.bottom - font_size - 1, str);
	
	pDC->SelectObject(pOldFont);
}

int CGraphPolar::GraphToScreenX(const CRect window, 
									long double x)
{
	double increment = double((m_PolarRange.Xmax - m_PolarRange.Xmin) / window.Width());
	return int(((x - m_PolarRange.Xmin) / increment) + window.left);
}


int CGraphPolar::GraphToScreenY(const CRect window, 
									long double y)
{
	long double y_ratio = double((m_PolarRange.Ymax-m_PolarRange.Ymin))/double(window.Height());
	return int((m_PolarRange.Ymax - y) / y_ratio) + window.top;
}


// Function name	: CGraphPolar::DrDtheta
// Description	    : 
// Return type		: long double 
// Argument         : const CString eq
// Argument         : long double theta
// Argument         : CCalculator *pCalculator
long double CGraphPolar::DrDtheta(const CString eq, long double theta, CCalculator *pCalculator)
{
	long double theta1, theta2, r1, r2, delta_theta = 0.000001;
	theta1 = theta - delta_theta;
	theta2 = theta + delta_theta;

	if(pCalculator->Compute(eq, "t", theta1, r1, 0) != SUCCESSFULL)	return 0;
	if(pCalculator->Compute(eq, "t", theta2, r2, 0) != SUCCESSFULL)	return 0;

	return (r2-r1)/(theta2-theta1);
}


// Function name	: CGraphPolar::GetDrDthetaStr
// Description	    : 
// Return type		: CString 
// Argument         : const CString eq
// Argument         : long double theta
// Argument         : CCalculator *pCalculator
CString CGraphPolar::GetDrDthetaStr(const CString eq, long double theta, CCalculator *pCalculator)
{
	long double slope = DrDtheta(eq, theta, pCalculator);

	CString str;
	if(-HUGE_VAL == slope || HUGE_VAL == slope)
		str = "dr/dtheta = vertical line: infinite slope";
	else
		str.Format("dr/dtheta = %.5f", slope);

	return str;
}


// Function name	: CGraphPolar::GetDyDxStr
// Description	    : 
// Return type		: CString 
// Argument         : const CString eq
// Argument         : long double theta
// Argument         : CCalculator *pCalculator
CString CGraphPolar::GetDyDxStr(const CString eq, long double theta, CCalculator *pCalculator)
{
	long double slope;
	CString str;

	if(DIV_ZERO == DyDx(eq, pCalculator, theta, slope))
		str = "undefined";
	else if(-HUGE_VAL == slope || HUGE_VAL == slope)
		str = "dy/dx = vertical line: infinite slope";
	else
		str.Format("dy/dx = %.4f", slope);

	return str;
}

CString CGraphPolar::GetTraceDrDthetaStr(const CString eq)
{
	long double slope = DrDtheta(eq, m_TraceTheta, g_Calculator);

	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
	CString str;
	if(-HUGE_VAL == slope || HUGE_VAL == slope)
		str = "vertical line: infinite slope";
	else
		g_Calculator->DecimalToStringSci(str, slope, 10);

	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
	return str;
}

CString CGraphPolar::GetTraceDyDxStr(const CString eq)
{
	long double slope;
	CString str;

	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);

	if(DIV_ZERO == DyDx(eq, g_Calculator, m_TraceTheta, slope))
		str = "undefined";
	else if(-HUGE_VAL == slope || HUGE_VAL == slope)
		str = "vertical line: infinite slope";
	else
		g_Calculator->DecimalToStringSci(str, slope, 10);
	
	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
	return str;
}

CString CGraphPolar::GetTraceXStr(CString eq)
{
	long double r;
	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
	
	if(g_Calculator->Compute(eq, "t", m_TraceTheta, r, 0) != SUCCESSFULL)
		{
		g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
		return "";
		}
	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
	
	long double x = r * cos(m_TraceTheta);
	CString str;
	//str.Format("%.15f", x);
	g_Calculator->DecimalToStringSci(str, x, 10);
	return str;
}

CString CGraphPolar::GetTraceYStr(CString eq)
{
	long double r;
	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
	
	if(g_Calculator->Compute(eq, "t", m_TraceTheta, r, 0) != SUCCESSFULL)
		{
		g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
		return "";
		}
	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
	
	long double y = r * sin(m_TraceTheta);
	CString str;
	//str.Format("%.15f",y);
	g_Calculator->DecimalToStringSci(str, y, 10);
	return str;
}

CString CGraphPolar::GetTraceThetaStr()
{
	CString str;
	//str.Format("%.15f", m_TraceTheta);
	g_Calculator->DecimalToStringSci(str,m_TraceTheta , 10);
	return str;
}

CString CGraphPolar::GetTraceRStr(CString eq)
{
	long double r;
	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
	
	if(g_Calculator->Compute(eq, "t", m_TraceTheta, r, 0) != SUCCESSFULL)
		{
		g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
		return "";
		}
	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
	
	CString str;
	//str.Format("%.15f", r);
	g_Calculator->DecimalToStringSci(str, r, 10);
	return str;
}


// Function name	: CGraphPolar::DrawDistance
// Description	    : 
// Return type		: void 
// Argument         : DistStatusE distance
// Argument         : const CString &EqOne
// Argument         : const CString &EqTwo
// Argument         : const long double &OneTheta
// Argument         : const long double &TwoTheta
// Argument         : const COLORREF bgcolor
// Argument         : const CRect window
// Argument         : DrawE destination
// Argument         : const SEquationStyle &style
// Argument         : CCalculator *pCalculator
// Argument         : CDC *pDC
void CGraphPolar::DrawDistance(DistStatusE distance,
							   const CString &EqOne,
							   const CString &EqTwo,
							   const COLORREF bgcolor,
							   const CRect window, 
							   DrawE destination,
							   const SEquationStyle &style, 
							   CCalculator *pCalculator,CDC *pDC)
{	
	
	long double r1, r2;
	if(pCalculator->Compute(EqOne, "t", m_dDistanceThetaOne, r1, 0) != SUCCESSFULL)	return;
	if(pCalculator->Compute(EqTwo, "t", m_dDistanceThetaTwo, r2, 0) != SUCCESSFULL)	return;

	long double x1 = r1 * cos(((pCalculator->m_trig_state == DEGREE) ? pCalculator->DegToRadian(m_dDistanceThetaOne) : m_dDistanceThetaOne));
	long double y1 = r1 * sin(((pCalculator->m_trig_state == DEGREE) ? pCalculator->DegToRadian(m_dDistanceThetaOne) : m_dDistanceThetaOne));
	long double x2 = r2 * cos(((pCalculator->m_trig_state == DEGREE) ? pCalculator->DegToRadian(m_dDistanceThetaTwo) : m_dDistanceThetaTwo));
	long double y2 = r2 * sin(((pCalculator->m_trig_state == DEGREE) ? pCalculator->DegToRadian(m_dDistanceThetaTwo) : m_dDistanceThetaTwo));
	
	int y_coord_1, x_coord_1, y_coord_2, x_coord_2;
	
	y_coord_1 = GraphToScreenY(window, y1);
	x_coord_1 = GraphToScreenX(window, x1);
	y_coord_2 = GraphToScreenY(window, y2);
	x_coord_2 = GraphToScreenX(window, x2);
	
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

void CGraphPolar::EraseDistance(const CString &EqOne,
								   const CString &EqTwo,
								   const COLORREF bgcolor,
								   const CRect window, 
								   const SEquationStyle &style, 
								   CCalculator *pCalculator,
								   CDC *pDC)
{
		
	long double r1, r2;
	if(pCalculator->Compute(EqOne, "t", m_dDistanceThetaOne, r1, 0) != SUCCESSFULL)	return;
	if(pCalculator->Compute(EqTwo, "t", m_dDistanceThetaPrev, r2, 0) != SUCCESSFULL)	return;
	
	long double x1 = r1 * cos(((pCalculator->m_trig_state == DEGREE) ? pCalculator->DegToRadian(m_dDistanceThetaOne) : m_dDistanceThetaOne));
	long double y1 = r1 * sin(((pCalculator->m_trig_state == DEGREE) ? pCalculator->DegToRadian(m_dDistanceThetaOne) : m_dDistanceThetaOne));
	long double x2 = r2 * cos(((pCalculator->m_trig_state == DEGREE) ? pCalculator->DegToRadian(m_dDistanceThetaPrev) : m_dDistanceThetaPrev));
	long double y2 = r2 * sin(((pCalculator->m_trig_state == DEGREE) ? pCalculator->DegToRadian(m_dDistanceThetaPrev) : m_dDistanceThetaPrev));

	int y_coord_1 = GraphToScreenY(window, y1);
	int x_coord_1 = GraphToScreenX(window, x1); 
	int y_coord_2 = GraphToScreenY(window, y2);
	int x_coord_2 = GraphToScreenX(window, x2);
	
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


CString CGraphPolar::GetDistanceStr( const CString &EqOne,
									 const CString &EqTwo,
									 CCalculator *pCalculator)
{
	long double r1, r2;
	if(pCalculator->Compute(EqOne, "t", m_dDistanceThetaOne, r1, 0) != SUCCESSFULL)	return "";
	if(pCalculator->Compute(EqTwo, "t", m_dDistanceThetaTwo, r2, 0) != SUCCESSFULL)	return "";

	long double x1 = r1 * cos(((pCalculator->m_trig_state == DEGREE) ? pCalculator->DegToRadian(m_dDistanceThetaOne) : m_dDistanceThetaOne));
	long double y1 = r1 * sin(((pCalculator->m_trig_state == DEGREE) ? pCalculator->DegToRadian(m_dDistanceThetaOne) : m_dDistanceThetaOne));
	long double x2 = r2 * cos(((pCalculator->m_trig_state == DEGREE) ? pCalculator->DegToRadian(m_dDistanceThetaTwo) : m_dDistanceThetaTwo));
	long double y2 = r2 * sin(((pCalculator->m_trig_state == DEGREE) ? pCalculator->DegToRadian(m_dDistanceThetaTwo) : m_dDistanceThetaTwo));

	long double distance = sqrt( pow((x2 - x1), 2) + pow((y2 - y1), 2) );
	CString str;
	pCalculator->DecimalToStringSci(str, distance);
	return str;
}

void CGraphPolar::ValidateRanges(TrigE trig_mode)
{
	if(m_PolarRange.Theta_min >= m_PolarRange.Theta_max){
		m_PolarRange.Theta_min = 0;
		m_PolarRange.Theta_max = 2*PI;
	}
	
	if(m_PolarRange.Theta_step < 0.00001)
		m_PolarRange.Theta_step = 0.01;
	
	if(trig_mode == RADIAN && (m_PolarRange.GridAngle <= 0 || m_PolarRange.GridAngle >= MAX_POALR_GRID_ANGLE_RADIANS))
		m_PolarRange.GridAngle = PI/6;
	else if(trig_mode == DEGREE && (m_PolarRange.GridAngle <= 0 || m_PolarRange.GridAngle >= MAX_POALR_GRID_ANGLE_DEGREES))
		m_PolarRange.GridAngle = 30;
	
	if(m_PolarRange.GridRadius <= 0 || m_PolarRange.GridRadius >= 999999999999999)
		m_PolarRange.GridRadius = 1;
	
	if(m_PolarRange.Xmax > 99999999999999999.0)
		m_PolarRange.Xmax = 99999999999999999.0;
	if(m_PolarRange.Xmin < -99999999999999999.0)
		m_PolarRange.Xmin = -99999999999999999.0;
	
	if(m_PolarRange.Ymax > 99999999999999999.0)
		m_PolarRange.Ymax = 999999999999999990.0;
	if(m_PolarRange.Ymin < -999999999999999990.0)
		m_PolarRange.Ymin = -99999999999999999.0;
	
	if(m_PolarRange.Ymin >= m_PolarRange.Ymax){
		m_PolarRange.Ymax = 5;
		m_PolarRange.Ymin = -5;
	}
	if(m_PolarRange.Xmin >= m_PolarRange.Xmax){
		m_PolarRange.Xmax = 5;
		m_PolarRange.Xmin = -5;	
	}
}


void CGraphPolar::InitializeTrace()
{
	m_TraceTheta = m_PrevTraceTheta = m_PolarRange.Theta_min;
}
bool CGraphPolar::AutoPan(long double r, CCalculator *pCalculator)
{
	long double x = r * cos(m_TraceTheta);
	long double y = r * sin(m_TraceTheta);

	long double rangex(m_PolarRange.Xmax - m_PolarRange.Xmin);
	long double rangey(m_PolarRange.Ymax - m_PolarRange.Ymin);

	long double distx(pCalculator->abs(0.1 * rangex));
	long double disty(pCalculator->abs(0.1 * rangey));

	long double borderx(pCalculator->abs(0.01 * rangex));
	long double bordery(pCalculator->abs(0.01 * rangey));

	if(x >= (m_PolarRange.Xmax - borderx)){	
		m_PolarRange.Xmax = x + distx;
		m_PolarRange.Xmin = m_PolarRange.Xmax - rangex;
		return true;
	}
	else if(x <= (m_PolarRange.Xmin + borderx)){
		m_PolarRange.Xmin = x - distx;
		m_PolarRange.Xmax = m_PolarRange.Xmin + rangex;
		return true;
	}
	if(y >= (m_PolarRange.Ymax - bordery)){
		m_PolarRange.Ymax = y + disty;
		m_PolarRange.Ymin = m_PolarRange.Ymax - rangey;
		return true;
	}
	else if(y <= (m_PolarRange.Ymin + bordery)){
		m_PolarRange.Ymin = y - disty;
		m_PolarRange.Ymax = m_PolarRange.Ymin + rangey;
		return true;
	}
	return false;
}

/*********************************************************/
// CGraphPolar::DrawTrace()
// Pre: none
// Post: the tracing cross is drawn
// Return Value: none
// Intent: to draw the cross for tracing
/*********************************************************/
TraceRedrawMode CGraphPolar::DrawTrace(const CString eq,
									   const CRect window,
									   DrawE destination,
									   CCalculator *pCalculator,
									   CPen *pPen,
									   CDC *pDC)
{
	// figure out x and y coords of trace point
	long double r;
	if(pCalculator->Compute(eq, "t", m_TraceTheta, r, 0) != SUCCESSFULL) return TRACE_NONE;
	long double x = r * cos(m_TraceTheta);
	long double y = r * sin(m_TraceTheta);

	while(-HUGE_VAL == y || HUGE_VAL == y){
		if(m_TraceTheta > m_PrevTraceTheta){
			m_PrevTraceTheta -= m_PolarRange.Theta_step;
			m_TraceTheta -= m_PolarRange.Theta_step;
		}
		else{
			m_PrevTraceTheta += m_PolarRange.Theta_step;
			m_TraceTheta += m_PolarRange.Theta_step;
		}
		if(pCalculator->Compute(eq, "t", m_TraceTheta, r, 0) != SUCCESSFULL) return TRACE_NONE;
		x = r * cos(m_TraceTheta);
		y = r * sin(m_TraceTheta);

	}

	if(AutoPan(r, pCalculator)) return TRACE_PAN; 

	int x_coord = GraphToScreenX(window, x);
	int y_coord = GraphToScreenY(window, y);

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

void CGraphPolar::ClearPrevTrace(const CString eq,
									 CBitmap &bitmap,
									 const CRect window,
									 CCalculator *pCalculator,
									 CDC *pDC)
{
	// draw graph bitmap just over section where cross was displayed
	long double r;

	pCalculator->SetErrorMode(ERROR_MODE_SILENT);
	if(pCalculator->Compute(eq, "t", m_PrevTraceTheta, r, 0) != SUCCESSFULL) return;
	pCalculator->SetErrorMode(ERROR_MODE_COMPLETE);
	
	long double x = r * cos(m_PrevTraceTheta);
	long double y = r * sin(m_PrevTraceTheta);

	int prev_x_coord = GraphToScreenX(window, x);
	int prev_y_coord = GraphToScreenY(window, y);

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap *pOldBitmap = MemDC.SelectObject(&bitmap);

	// draw graph bitmap over last position of cursor
	pDC->BitBlt(prev_x_coord - 20, prev_y_coord - 20, 
				40, 40, 
				&MemDC, 
				prev_x_coord - 20, prev_y_coord - 20, 
				SRCCOPY);
	MemDC.SelectObject(pOldBitmap);
	DeleteDC(MemDC);
}

CString CGraphPolar::GetTraceCoordsStr(const CString eq, CCalculator *pCalculator)
{
	long double r;
	if(pCalculator->Compute(eq, "t", m_TraceTheta, r, 0) != SUCCESSFULL)
		return "";

	long double x = r * cos(m_TraceTheta);
	long double y = r * sin(m_TraceTheta);

	CString str;
	str.Format("theta = %.5f, r = %.5f, x = %.5f, y = %.5f", m_TraceTheta, r, x, y);
	return str;
}

void CGraphPolar::IncreaseTraceTheta(){	
	if((m_TraceTheta + m_PolarRange.Theta_step + 0.00001) <= m_PolarRange.Theta_max){
		m_PrevTraceTheta = m_TraceTheta;
		m_TraceTheta += m_PolarRange.Theta_step; 
	}
}
void CGraphPolar::DecreaseTraceTheta(){	
	if((m_TraceTheta - m_PolarRange.Theta_step + 0.00001) >= m_PolarRange.Theta_min){
		m_PrevTraceTheta = m_TraceTheta;
		m_TraceTheta -= m_PolarRange.Theta_step; 
	}
}


