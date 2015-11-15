#if !defined(CCALCULATOR)
#define CCALCULATOR

#include <afxtempl.h>
#include <math.h>
#include <string>
#include <fstream.h>
#include <iostream.h>
#include <float.h>
#include "Structs.h"
#include <limits>

using namespace std;

enum Operators{UNKNOWN_OPERATOR,
				LPAREN,
				RPAREN,
				MIN,
				MAX,
				LCM,
				GCD,
				ROUND,
				IRAND,
				FRAND,
				FPART,
				IPART,
				INTEGER,
				FACT,
				NPR,
				NCR,
				ABS,
				LOG,
				LN,
				ARCSIN,
				ARCCOS,
				ARCTAN,
				SIN,
				COS,
				TAN,
				SINH,
				COSH,
				TANH,
				COLIN,
				PERCENT,
				FLOOR,
				CEIL,
				SQRT,
				POW,
				MULT,
				DIV,
				MOD,
				ADD,
				SUBT,
				EQ,
				GT,
				GE,
				LT,
				LE,
				NE,
				EQUAL,
				CONV_BASE,
				FC,
				FR,
				FK,
				CF,
				CK,
				CR,
				KF,
				KC,
				KR,
				RF,
				RC,
				RK,
				MEAN,
				MEDIAN,
				MODE,
				STDEV,
				VARIANCE,
				FIB}; 

enum Trans{STARTT,
			NUMT,
			OPT,
			VART,
			PAREN,
			MATHT,
			LOGICT};

enum OpType{UNKNOWN_OP_TYPE,VARIABLE,NUMBER,OPERATOR};
enum TrigE{RADIAN, DEGREE};
enum InternationalModeE {US, EUROPEAN};

enum ErrorT{SUCCESSFULL=0, 
			UNKNOWNERR, 
			MULTOPERATORS, 
			MISSINGPAREN, 
			EMPTYEQ, 
			INVALIDEXP, 
			NOOPERANDS, 
			MISSINGONEOPERAND, 
			MISSINGOPERAND, 
			UNEXPECTED_OPERATOR,
			EMPTYPARENS, 
			BASE_OUT_OF_RANGE, 
			BASE_ERROR, 
			MULTIPLE_DECIMAL, 
			EXPECTED_LPAREN,
			MISSING_OPERAND_END, 
			EMPTY_STACK, 
			MISSINGPARAM, 
			EXTRA_PARAMS, 
			MISSING_VAR, 
			UNKNOWN_CONSTANT,
			RUNTIME_ERROR, 
			DIV_ZERO, 
			NCR_SIZE, 
			NCR_INTEGERS, 
			GCD_ZERO,
			FACT_INT_ZERO, 
			NPR_INTEGERS,
			NPR_SIZE,
			GCD_INTEGERS,
			LCM_ZERO,
			LCM_INTEGERS,
			OUT_OF_STACK_RANGE,
			INVALID_BASE,
			FIB_VALUE, 
			UNKNOWN_VARIABLE, 
			NO_ROOTS, 
			INVALID_EQ, 
			UNDEFINED_VALUE,
			ZERO_SLOPE, 
			INFINITE_VALUE,
			ERR_UNKNOWN_OP_TYPE};

enum ErrorModeE {ERROR_MODE_COMPLETE, 
					ERROR_MODE_RUNTIME, 
					ERROR_MODE_TRANSLATE, 
					ERROR_MODE_SILENT};

#define SOLVER_DECIMAL_PRECISION 0.000000000000001
#define DYDX_DELTA 0.000000001
#define PI	3.1415926535897932384626 
#define E	2.71828182846
#define MAX_STATE 12
#define MAX_EQUATIONS 10
#define MAX_PARAMETRIC_EQUATIONS 5
#define MIN_SOLVER_RANGE 5.0
#define LINE_LENGTH		256

#define INDEFINITE	numeric_limits<float>::quiet_NaN()

#ifndef MAX_PLACES
#define MAX_PLACES
const int max_places[37] = {0 , 0,52,32,26,22,20,18,17,16,
							15,15,14,14,13,13,13,12,12,12,
							12,11,11,11,11,11,11,10,10,10,
							10,10,10,10,10,10,10};  
#endif


/*********************************************************/
// This structure is used for an entry on our stack
// used in calculations.  It stores the type and value
// of the entry
/*********************************************************/
struct StackEntry{
	StackEntry()
		{
		type = UNKNOWN_OP_TYPE;
		num = 0;
		var.Empty();
		oper = UNKNOWN_OPERATOR;
		}
	OpType type;
	long double num;
	CString var;
	Operators oper;
};

/*********************************************************/
// An entry into our variabel list.
// It stores the name and value of a variable
/*********************************************************/
struct VarListEntryT{
	CString name;
	long double value;
};

/*********************************************************/
// Stores the name and value of a constant
// for our constants read in from constants.dat
/*********************************************************/
struct ConstantT{
	CString name;
	CString value;
};

/*********************************************************/
// This structure defines a constant category
// It stores subcategories and constants
/*********************************************************/
struct ConstCatT{
	CString name;
	CArray<ConstantT, ConstantT> entries;
	CArray<ConstCatT, ConstCatT> sub_menu;
};

/*********************************************************/
// This structure defines a unit
// It stores the unit name, value, and type (english or metric)
/*********************************************************/
struct UnitT{
	CString unit;
	CString value;
	CString type;
};

/*********************************************************/
// This structure defines a unit category, eg length
// It stores the names of the two unit types, english or metric,
// the base units used for the conversion factors, and the
// conversion factor between the two base units
/*********************************************************/
struct CategoryT{
	CArray<UnitT, UnitT> entries;
	CString name;
	CString type_one;
	CString type_two;
	CString standard_one;
	CString standard_two;
	CString conversion;
};

/*********************************************************/
// this struct is used to pass answers and results
// from functions used in evaluating the stack
/*********************************************************/
struct EvalResultT{
	ErrorT error;
	long double ans;
};


/*struct NodeValueT{
	Operators oper;
	long double num;
	CString var;
};*/

struct NodeT{
	OpType type;
	Operators oper;
	long double num;
	CString var;
	CArray<NodeT, NodeT> children;
};

struct RangeT{
	int min;
	int max;
};

/*struct VariableT{
	CString str;
	long double num;
};*/

class AFX_EXT_CLASS CCalculator{

public:
	void SetTrigState(CString val);
	void SetIntlMode(CString val);
	void SetNormal(bool val);
	void SetErrorMode(ErrorModeE mode);
	void SetPrevAnswerStr(CString str);
	void AddAnsToHistory(CString str);
	int GetHistoryCount();
	CString GetHistoryStrByIndex(int index);
	
	long double RadianToDeg(long double val);
	long double DegToRadian(long double val);

	///////////////////////////////////////////////////////////////////////////////////
	//////// MEMBER FUNCTIONS /////////
	///////////////////////////////////
	
	CCalculator();
	~CCalculator();

	// Functions used to validate or compute an expression
	bool IsValid(CString formula,  HWND window);
	bool IsValid(CString formula);
	ErrorT Compute(CString formula, long double &answer, HWND window=NULL);
	//ErrorT Compute(long double var_val, long double &answer, HWND window);
	//ErrorT Compute(CString formula, long double var_val, long double &answer, HWND window);
	ErrorT Compute(CString formula, CString str, long double num, long double &answer, HWND window=NULL);
	ErrorT Compute(CString formula, CArray<VariableT, VariableT> *variables, long double &answer, HWND window=NULL);
	ErrorT Compute3D(CString formula, CArray<VariableT, VariableT> *variables, long double &answer, HWND window=NULL);

	//ErrorT Compute(CString formula, CArray<CString, CString> var_strings, CArray<long double, long double> var_values, 
	//			   long double &answer, HWND window);
	//////////////////////////////////////////////////////
	
	// Converts a decimal answer to a string in the current base
	ErrorT DecimalToString(CString &theString, long double decAnswer);
	void DecimalToStringSci(CString &str, long double num, int nDecimalPlaces=0);
	ErrorT StringToDecimal(CString theNum, int base, long double &total);
	void FormatString(CString &theString);

	// used by other classes since the math.h abs is not very good
	long double abs(long double num);

	ErrorT EqSolver(CString eq, CString var, double dGuess, long double &ldAnsOut, CString &strAnsOut);
	ErrorT EqSolverBisection(CString eq, CString var, double dGuess, long double &ldAns);
	ErrorT MinMaxSolverBisection(CString eq, CString var, double dMin, double dMax, 
									long double &ldAns, CString &strAns, int &stationary_point);
	ErrorT DyDx(const CString eq, CString var, long double x, long double &ldAnsOut);

	
	// Functions used by operators defined in the calculator
	long double 	factorial(long double first);
	long double 	nPr(long double first, long double second);
	long double 	nCr(long double first, long double second);
	int 			roundint(long double num);
	int 			gcd(CArray<long double, long double> &params);
	int 			lcm(CArray<long double, long double> &params);
	long double 	frand(long double min, long double max);
	int 			irand(int min, int max);
	bool			divisible(long double dValOne, long double dValTwo);
	///////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////
	//////// MEMBER VARIABLES /////////
	///////////////////////////////////
	
	// member variables to format output
	bool m_NumberSeperator;
	int m_NumberSeperatorAmount;
	char m_NumberSpaceSeperator;           
	bool m_DecimalSeperator;
	int m_DecimalSeperatorAmount;
	char m_DecimalSpaceSeperator;

	// member variables that control the mode of the calculator
	int m_ConvertToBase;
	int m_base;
	int m_DecimalPlaces;
	bool m_Float;
	bool m_Normal;
	bool m_ShowBase;
	InternationalModeE m_IntlMode;
	TrigE m_trig_state;
	CString m_LongOutput;
	///////////////////////////////////////////////////
	
	CArray<CategoryT, CategoryT>			m_Categories;
	CArray<ConstCatT, ConstCatT>			m_Constants;
	CList<VarListEntryT, VarListEntryT>		m_VarList;
	CList<CString,CString>					m_lststrAnswerHistory;
	int										m_nAnswerHistoryCount;

private:
	CArray<VariableT, VariableT> *m_pVariables;


	long double fibonacci(int n);
	ErrorModeE m_ErrorMode;
	void AppendLongOutput(Operators oper, const CArray<long double, long double>  &params);
	long double stdev(const CArray<long double, long double>  &params);
	long double variance(const CArray<long double, long double>  &params);
	long double mode(const CArray<long double, long double> &params);
	long double median(CArray<long double, long double> &params);
	void sort(CArray<long double, long double> &params);
	long double Max(const CArray<long double, long double> &params);
	RangeT RequiredParams(const Operators &oper);
	long double mean(const CArray<long double, long double> &params);
	long double Min(const CArray<long double, long double> &params);
	long double DoOp(Operators oper, CArray<long double, long double> &params, ErrorT &error);

	ErrorT EvaluateTree(NodeT *node, long double &answer);
	bool IsMultiParamOp(Operators oper);
	bool IsInfix(Operators oper);
	bool IsPostfix(Operators oper);
	bool IsPrefix(Operators oper);
	int FindLowestOper(int start, int end);
	int m_CurStack;
	ErrorT CreateNodes(int start, int end, NodeT *node);
	void SetStackEntry(StackEntry entry, int i);
	bool GetStackEntry(int i, StackEntry &entry);
	NodeT m_Tree[10];
	ErrorT CreateTree();
	
	
	bool GetAvailableStack(CString new_eq);

	CString GetOperatorValue(Operators oper);

	int maximum(int *array, int size);

	///////////////////////////////////////////////////////////////////////////////////
	//////// MEMBER FUNCTIONS /////////
	///////////////////////////////////
	
	// Initialization Functions /////////////////////
	void InitUnits();
	void InitConstants();
	int InitConstCat(CArray<ConstCatT, ConstCatT> &cat, ::ifstream *infile, int level);
	void SetRunTimeStack(int stack);
	///////////////////////////////////////////////////

	// FUNCTIONS USED BY DecimalToString() ///////////
	int intLog(long double num);
	bool roundString(CString &theString, int num);
	bool maxDigit(char digit);
	char halfDigit();
	void addDigit(CString &theString, int digit);
	///////////////////////////////////////////////////
	
	// Functions used to evaluate the stack ///////////
	//EvalResultT Evaluate(int start, int &end, long double var_val);
	long double RoundTrig(long double num);
	bool OpInState(Operators oper, int state);
	bool IsLogicOP(Operators val);
	//bool IsPostfixOp(Operators val);
	//bool IsInfixOp(Operators val);
	//bool IsOneParamOP(Operators val);
	//bool IsTwoParamOP(Operators val);
	bool IsTrigOp(Operators val);

	ErrorT GetEntry(int stack_pos, StackEntry &entry);
	ErrorT SetEntry(int stack_pos, StackEntry entry);
	/////////////////////////////////////////////////
	
	// Functions used to parse expression ///////////
	ErrorT Translate(int stack);
	
	void ReplaceVars(int stack);
	void ReplaceConversions(CString &formula);
	void ReplaceConstants(CString &formula);
	void ReplaceConstantsFn(CArray<ConstCatT, ConstCatT> &cons, CString menu_name, CString &formula);

	char GetNextChar(CString &form);
	bool IsWhiteSpace(char val);
	bool IsCharNotInBase(int base, char badchar);
	bool IsOp(char val);
	bool IsLogic(char val);
	bool IsNum(char val);
	bool IsVar(char val);
	bool IsMath(CString val);
	Operators GetMathOp(CString var_name);
	int  OpLevel(Operators val);
		
	void HandleError(ErrorT error, CString eq);
	void HandleRunTimeError(ErrorT error, CString eq);
	/////////////////////////////////////////////////
	

	//long double Logarithm(int new_base, long double num);
	
	///////////////////////////////////////////////////////////////////////////////////
	//////// MEMBER VARIABLES /////////
	///////////////////////////////////

	CString 							m_PrevAnswerStr; // stores the previous answer
	CList<StackEntry, StackEntry>		m_RunTimeStack;
	CList<StackEntry, StackEntry>		m_Stack[MAX_EQUATIONS];
	CString								m_Equation[MAX_EQUATIONS];
	int									m_Frequency[MAX_EQUATIONS];
	int									m_prevbase;
	bool								m_Validating;
	HWND								*m_Hwnd;	
};

#endif

/*********************************************************/
//
//
//
/*********************************************************/
