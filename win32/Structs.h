/*#if !defined(STRUCTS_H)
#define STRUCTS_H*/


#if !defined(SRGBSTRING)
#define SRGBSTRING
struct SRGBString{
		CString r;
		CString g;
		CString b;
};
#endif

#if !defined(COLORT)
#define COLORT
struct ColorT {
	double red;    // 0 - 1 for Red
	double green;  // 0 - 1 for Green
	double blue;   // 0 - 1 for Blue
};
#endif

#if !defined(SHADINGTYPEE)
#define SHADINGTYPEE
enum ShadingTypeE { FOUR_COLOR, TWO_COLOR };
#endif

#if !defined(WIRESE)
#define WIRESE
enum WiresE { W, C, CW, CWW};  //   C: Just Colored
								//   W: Just Wires
								//  CW: Colored with just top wires
								// CWW: Colored with both wires
#endif

#if !defined(FOURCOLORST)
#define FOURCOLORST
struct FourColorsT {
	ShadingTypeE type; // FOUR_COLOR for 4color, TWO_COLOR for 2color
	ColorT color1; // x-min, y-max
	ColorT color2; // x-max, y-max -- High Color
	ColorT color3; // x-min, y-min -- Low Color
	ColorT color4; // x-max, y-min
};
#endif

#if !defined(S3DEQUATION)
#define S3DEQUATION
struct S3DEquation {
	WiresE wires;
	FourColorsT color;
	CString eq; // the equation itself
	bool on;    // 0 for off, 1 for on
};
#endif

#if !defined(EQUATIONT)
#define EQUATIONT
struct EquationT{
	CString eq;
	BOOL disp;
	COLORREF color;
};

struct ParametricEquationT{
	CString xt;
	CString yt;
	BOOL disp;
	COLORREF color;
};
#endif

#if !defined(EGRAPHMODE)
#define EGRAPHMODE
enum EGraphMode{EUCLIDEAN, POLAR, PARAMETRIC};
#endif

#if !defined(SVARIABLET)
#define SVARIABLET
struct VariableT{
	CString str;
	long double num;
};
#endif

#if !defined(SPOINT)
#define SPOINT
struct SPoint{
	double x;
	double y;
};
#endif

#if !defined(SVERTEX)
#define SVERTEX
struct SVertex{
	float x;
	float y;
	float z;
};
#endif

#if !defined (DRAWE)
#define DRAWE
enum DrawE {BMP, SCRN, PRINT};
#endif


#if !defined (DISTSTATUSE)
#define DISTSTATUSE
enum DistStatusE {OFF, FIRST, SECOND, DONE};
#endif

#if !defined (GRAPHSTYLE)
#define GRAPHSTYLE
enum ELineStyle {GRAPH_STYLE_LINE, GRAPH_STYLE_POINT};

struct SEquationStyle{
	ELineStyle line;
	int		   size;
};
#endif

#if !defined (LINESTYLE)
#define LINESTYLE
struct SLineStyle{
	COLORREF	color;
	int			size;
	};
#endif

//#endif
