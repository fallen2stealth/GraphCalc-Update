#if !defined(CGRAPHPOLAR)
#define CGRAPHPOLAR

#include <afxwin.h>
#include "CCalculator.h"
#include "Structs.h"

#define MAX_GRAPH_RINGS	20

#if !defined (DISTSTATUSE)
#define DISTSTATUSE
enum DistStatusE {OFF, FIRST, SECOND, DONE};
#endif

#if !defined (DRAWE)
#define DRAWE
enum DrawE {BMP, SCRN, PRINT};
#endif


#if !defined (GRAPHSTYLE)
#define GRAPHSTYLE
enum ELineStyle {GRAPH_STYLE_LINE, GRAPH_STYLE_POINT};

struct SEquationStyle{
	ELineStyle line;
	int		   size;
};
#endif

#if !defined (TRACEREDRAWMODE)
#define TRACEREDRAWMODE
enum TraceRedrawMode{TRACE_NONE, TRACE_PAN};
#endif

struct SPolarGrphRng{
	long double Theta_min;
	long double Theta_max;
	long double Theta_step;

	long double GridRadius;
	long double GridAngle;

	long double Xmin;
	long double Xmax;
	long double Ymin;
	long double Ymax;
};

#if !defined (LINESTYLE)
#define LINESTYLE
struct SLineStyle{
	COLORREF	color;
	int			size;
	};
#endif

#define GRAPH_THRESHOLD		10000

class CGraphPolar : public CObject{
public:
	void GetMinMaxRings(int &min_rings, int &max_rings);
	void DecreaseTraceTheta();
	void IncreaseTraceTheta();
	void ValidateRanges(TrigE trig_mode);
	CGraphPolar();
	~CGraphPolar();
	
	SPolarGrphRng m_PolarRange;
	SPolarGrphRng m_PrevPolarRange;
	void SwapPrevCurRanges();
	void SetPreviousRange();
	void StoreCurrentRange();

	void SetDistanceThetaTwo(long double val){ m_dDistanceThetaTwo = val; }
	void SetDistanceThetaPrev(long double val){ m_dDistanceThetaPrev = val; }
	void SetDistanceThetaOne(long double val){ m_dDistanceThetaOne = val; }
	long double GetDistanceThetaTwo(){ return m_dDistanceThetaTwo; }
	long double GetDistanceThetaPrev(){ return m_dDistanceThetaPrev; }
	long double GetDistanceThetaOne(){ return m_dDistanceThetaOne; }

	bool DrawEquation(const EquationT &eqT, 
					   
					  const SEquationStyle style, 
					  const CRect &window, 
					  CCalculator *pCalculator,
					  CDC *pDC);

	void DrawGrid(const SLineStyle style, const CRect window, CDC *pDC, CCalculator *pCalculator);
	void DrawAxis(const SLineStyle style, const CRect window, CDC *pDC);
	
	void DrawTangentLine(const EquationT &eqT, 
						 const long double &theta, 
						 const SEquationStyle &style, 
						 const CRect window, 
						 CCalculator *pCalculator,
						 DrawE destination,
						 CDC *pDC);

	ErrorT DyDx(const CString eq, 
					 CCalculator *pCalculator, 
					 long double theta,
					 long double &outAns);

	CString GetTangentEquation(const CString eq, 
							   CCalculator *pCalculator,
							   long double theta);	

	void DrawCoordsLabels(const double font_size,
						  const bool coords,
						  const bool labels,
						  const COLORREF color,
						  const CRect window, 
						  DrawE destination,
						  CDC *pDC);

	CString GetDrDthetaStr(const CString eq, long double theta, CCalculator *pCalculator);
	CString GetDyDxStr(const CString eq, long double theta, CCalculator *pCalculator);

	CString GetTraceDrDthetaStr(const CString eq);
	CString GetTraceDyDxStr(const CString eq);
	CString GetTraceXStr(CString eq);
	CString GetTraceYStr(CString eq);
	CString GetTraceThetaStr();
	CString GetTraceRStr(CString eq);

	void DrawDistance(DistStatusE distance,
					  const CString &EqOne,
					  const CString &EqTwo,
					  const COLORREF bgcolor,
					  const CRect window, 
					  DrawE destination,
					  const SEquationStyle &style, 
					  CCalculator *pCalculator,
					  CDC *pDC);

	void EraseDistance(const CString &EqOne,
					   const CString &EqTwo,
					   const COLORREF bgcolor,
					   const CRect window, 
					   const SEquationStyle &style, 
					   CCalculator *pCalculator,
					   CDC *pDC);
	
	CString GetDistanceStr( const CString &EqOne,
							const CString &EqTwo,
							CCalculator *pCalculator);

	void InitializeTrace();
	CString GetTraceCoordsStr(const CString eq, CCalculator *pCalculator);
	TraceRedrawMode DrawTrace(const CString eq,
							  const CRect window,
							  DrawE destination,
							  CCalculator *pCalculator,
							  CPen *pPen,
							  CDC *pDC);
	
	void ClearPrevTrace(const CString eq,
						CBitmap &bitmap,
						const CRect window,
						CCalculator *pCalculator,
						CDC *pDC);

	/////////////////////
	// Provide Access to member variables

	void SetTraceTheta(long double val){ m_TraceTheta = val; }
	long double GetTraceTheta(){ return m_TraceTheta; }
	void SetPrevTraceTheta(long double val){ m_PrevTraceTheta = val; }
	long double GetPrevTraceTheta(){ return m_PrevTraceTheta; }

private:
	
	long double m_dDistanceThetaTwo;
	long double m_dDistanceThetaPrev;
	long double m_dDistanceThetaOne;

	bool AutoPan(long double r, CCalculator *pCalculator);

	void DrawStarGrid(const SLineStyle style, const CRect window, CDC *pDC, CCalculator *pCalculator);
	void DrawCircularGrid(const SLineStyle style, const CRect window, CDC *pDC);

	long double DrDtheta(const CString eq, long double theta, CCalculator *pCalculator);
	
	//int GraphToBitmapX( const CRect window, long double x);
	//int GraphToBitmapY( const CRect window, long double y);

	int GraphToScreenX( const CRect window, long double x);
	int GraphToScreenY( const CRect window, long double y);

	// variables for tracing
	long double m_TraceTheta;		// the theta value of the tracer
	long double	m_PrevTraceTheta;	// the theta value of the previous trace point
};

#endif
