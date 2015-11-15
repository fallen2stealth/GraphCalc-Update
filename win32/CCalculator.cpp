#include "CCalculator.h"
#include "globals.h" 

/*********************************************************/
// 
// Pre:
// Post:
// Return Value:
// Intent:
/*********************************************************/
extern VariableT GetVariable(CString var, long double num);

/*********************************************************/
// CCalculator::CCalculator()
// constructor for class
// it initializes data members and reads in data from
// units.dat and constants.dat
/*********************************************************/
CCalculator::CCalculator() : m_lststrAnswerHistory(ANSWER_HISTORY){
	
	m_base = 10;
	m_DecimalPlaces = 5;
	m_Float = true;
	m_trig_state = RADIAN;
	m_Normal = true;
	m_IntlMode = US;

	m_nAnswerHistoryCount = ANSWER_HISTORY;
		
	m_Constants.SetSize(0,1);
	InitConstants();
	InitUnits();	
	
	m_ShowBase = false;
	m_Validating = false;

	m_ErrorMode = ERROR_MODE_COMPLETE;

	m_NumberSeperator = true;
	m_NumberSeperatorAmount = 3;
	m_NumberSpaceSeperator = ',';           
	m_DecimalSeperator = false;
	m_DecimalSeperatorAmount = 3;
	m_DecimalSpaceSeperator = ' ';

	for(int i(0); i < 10; ++i)
		m_Frequency[i] = 9 - i;

	VarListEntryT entry;
	entry.name = "pi";
	entry.value = PI;
	m_VarList.AddTail(entry);
	entry.name = "e";
	entry.value = E;
	m_VarList.AddTail(entry);
	entry.name = "n";
	entry.value = 1;
	m_VarList.AddTail(entry);

	m_pVariables = 0;

}

/*********************************************************/
// CCalculator::~CCalculator()
// Pre:		none
// Post:	none
// Intent:	to destruct object
/*********************************************************/
CCalculator::~CCalculator(){
	m_Categories.RemoveAll();
	m_Constants.RemoveAll();
	m_VarList.RemoveAll();
}

int CCalculator::maximum(int *array, int size)
{
	int max;
	max = 0;

	for(int i(1); i < size; ++i){
		if(array[i] > array[max])
			max = i;
	}
	return max;
}

CString CCalculator::GetOperatorValue(Operators oper)
{
	switch(oper){
	case MIN:		return "min";
	case MAX:		return "max";
	case LCM:		return "lcm";
	case GCD:		return "gcd";
	case ROUND:		return "round";
	case IRAND:		return "irand";
	case FRAND:		return "frand";
	case FPART:		return "fpart";
	case IPART:		return "ipart";
	case INTEGER:		return "integer";
	case FACT:		return "!";
	case NPR:		return "npr";
	case NCR:		return "ncr";
	case ABS:		return "abs";
	case LOG:		return "log";
	case LN:		return "ln";
	case ARCSIN:		return "arcsin";
	case ARCCOS:		return "arccos";
	case ARCTAN:		return "arctan";
	case SIN:		return "sin";
	case COS:		return "cos";
	case TAN:		return "tan";
	case SINH:		return "sinh";
	case COSH:		return "cosh";
	case TANH:		return "tanh";
	case COLIN:		return ":";
	case PERCENT:		return "%";
	case FLOOR:		return "floor";
	case CEIL:		return "ceil";
	case SQRT:		return "sqrt";
	case POW:		return "^";
	case MULT:		return "*";
	case DIV:		return "/";
	case MOD:		return "mod";
	case ADD:		return "+";
	case SUBT:		return "-";
	case EQ:		return "==";
	case GT:		return ">";
	case GE:		return ">=";
	case LT:		return "<";
	case LE:		return "<=";
	case NE:		return "!=";
	case EQUAL:		return "=";
	case CONV_BASE:		return "convbase";
	case FC:		return "farenheit->celcius";
	case FR:		return "farenheit->rankin";
	case FK:		return "farenheit->kelvin";
	case CF:		return "celcius->farenheit";
	case CK:		return "celcius->kelvin";
	case CR:		return "celcius->rankin";
	case KF:		return "kelvin->farenheit";
	case KR:		return "kelvin->rankin";
	case KC:		return "kelvin->celcius";
	case RF:		return "rankin->farenheit";
	case RC:		return "rankin->celcius";
	case RK:		return "rankin->kelvin";
	case MEAN:		return "mean";
	case MEDIAN:		return "median";
	case MODE:		return "mode";
	case STDEV:		return "stdev";
	case VARIANCE:		return "variance";
	case FIB:		return "fib";
	}
	return "(unknown operator)";
}

/*********************************************************/
// CCalculator::IsOp(char val)
// Pre:		none
// Post:	none
// Return	Value:
// Intent:	to see if we have a one character operator
/*********************************************************/
bool CCalculator::IsOp(char val){
	return ((val == '+') 
	 	 || (val == '-') 
	 	 || (val == '*') 
	 	 || (val == '/') 
	 	 || (val == '^') 
	 	 || (val == '%') 
		 || (val == '(') 
		 || (val == ')') 
		 || (val == '!') 
		 || (val == ':'));
}

/*********************************************************/
// CCalculator::IsLogic(char val)
// Pre:	none
// Return Value: returns whether or not we have a character found in 
//		 logical operators
// Intent: to determine if we have a logical operator
/*********************************************************/
bool CCalculator::IsLogic(char val)
{
	return ((val == '=') 
		 || (val == '>') 
		 || (val == '<') 
		 || (val == '!'));
}

/*********************************************************/
// CCalculator::IsMath(CString val)
// Pre: none
// Return Value: returns true if val is one of the strings listed
// Intent: to see if we have an operator
/*********************************************************/
bool CCalculator::IsMath(CString val){
	return((val == "sin") 
		|| (val == "cos") 
		|| (val == "tan")
		|| (val == "arcsin") 
		|| (val == "arccos") 
		|| (val == "arctan")
		|| (val == "hypsin") 
		|| (val == "hypcos") 
		|| (val == "hyptan")
		|| (val == "log") 
		|| (val == "ln")
		|| (val == "sqrt")
		|| (val == "ans") 
		|| (val == "ncr")
		|| (val == "npr")
		|| (val == "abs") 
		|| (val == "ipart")
		|| (val == "fpart") 
		|| (val == "int")
		|| (val == "gcd") 
		|| (val == "min")
		|| (val == "max") 
		|| (val == "convbase")
		|| (val == "irand") 
		|| (val == "frand")
		|| (val == "lcm")
		|| (val == "round")
		|| (val == "mod")
		|| (val == "ceil")
		|| (val == "floor")
		|| (val == "farenheitcelcius")
		|| (val == "farenheitkelvin")
		|| (val == "farenheitrankin")
		|| (val == "celciusfarenheit")
		|| (val == "celciuskelvin")
		|| (val == "celciusrankin")
		|| (val == "kelvinfarenheit")
		|| (val == "kelvincelcius")
		|| (val == "kelvinrankin")
		|| (val == "rankinfarenheit")
		|| (val == "rankinkelvin")
		|| (val == "rankincelcius")
		|| (val == "mean")
		|| (val == "median")
		|| (val == "mode")
		|| (val == "stdev")
		|| (val == "variance")
		|| (val == "fib")
		);
}

bool CCalculator::IsPrefix(Operators oper)
{
	return ((oper == SIN)
		|| (oper == COS) 
		|| (oper == TAN) 
		|| (oper == ARCSIN) 
		|| (oper == ARCCOS) 
		|| (oper == ARCTAN) 
		|| (oper == SINH) 
		|| (oper == COSH) 
		|| (oper == TANH)
		|| (oper == LOG) 
		|| (oper == LN) 
		|| (oper == SQRT)
		|| (oper == ABS) 
		|| (oper == INTEGER) 
		|| (oper == FPART) 
		|| (oper == IPART) 
		|| (oper == ROUND)
		|| (oper == FLOOR)
		|| (oper == CEIL)
		|| IsMultiParamOp(oper));
}

bool CCalculator::IsPostfix(Operators oper)
{
	return ((oper == FACT) 
		||  (oper == PERCENT)
		||  (oper == FC)
		||  (oper == FK)
		||  (oper == FR)
		||  (oper == CF)
		||  (oper == CR)
		||  (oper == CK)
		||  (oper == KF)
		||  (oper == KC)
		||  (oper == KR)
		||  (oper == RF)
		||  (oper == RC)
		||  (oper == RK));
}

bool CCalculator::IsInfix(Operators oper)
{
	return ((oper == NPR) 
		|| (oper == NCR)
		|| (oper == DIV) 
		|| (oper == MULT) 
		|| (oper == MOD) 
		|| (oper == ADD) 
		|| (oper == SUBT) 
		|| (oper == EQUAL)
		|| (oper == CONV_BASE)
		|| (oper == POW)
		|| IsLogicOP(oper));
}
bool CCalculator::IsMultiParamOp(Operators oper)
{
	return (oper == MIN
	 	|| oper == MAX
		|| oper == GCD
		|| oper == LCM
		|| oper == IRAND
		|| oper == FRAND
		|| oper == MEAN
		|| oper == MEDIAN
		|| oper == MODE
		|| oper == STDEV
		|| oper == VARIANCE
		|| oper == FIB);
}

/*********************************************************/
// CCalculator::IsLogicOP(Operators val)
// Pre: none
// Post: none
// Return Value: true or false
// Intent: to return true if val is a logical operator
/*********************************************************/
bool CCalculator::IsLogicOP(Operators val)
{
	return ((val == EQ) 
		 || (val == GT) 
		 || (val == GE) 
		 || (val == LT) 
		 || (val == LE) 
		 || (val == NE));
}

/*********************************************************/
// CCalculator::IsNum(char val)
// Pre: none
// Post: none
// Return Value: returns true if we have a number or 
//				 capital letter
// Intent: to determine if val is a number (in any base)
/*********************************************************/
bool CCalculator::IsNum(char val)
{
	return (((int(val) >= 48) && (int(val) <= 57)) ||
		((int(val) >= 65) && (int(val) <= 90)) );
}

/*********************************************************/
// CCalculator::IsVar(char val)
// Pre: none
// Post: none
// Return Value: returns true if val is a lowercase letter
// Intent: to determine if we have a lowercase letter
/*********************************************************/
bool CCalculator::IsVar(char val)
{
	return ((int(val) >= 97) && (int(val) <= 122));
}

/*********************************************************/
// CCalculator::IsCharNotInBase(int base, char badchar)
// Pre: base >= 2 && base <= 36
// Post: none
// Return Value: false if badchar is valid for the current 
//				 base
// Intent: to determine if badchar is valid in the current
//		   base
/*********************************************************/
bool CCalculator::IsCharNotInBase(int base, char badchar)
{
	if((base > (badchar - '0')) && (badchar >= '0'))
		return false;
	else if((badchar < (base + 'A' - 10)) && (badchar >= 'A') && (base > 10))
		return false;
	else if((m_IntlMode == US && badchar == '.') || (m_IntlMode == EUROPEAN && badchar == ','))
		return false;
	
	return true;
}

/*********************************************************/
// CCalculator::IsWhiteSpace(char val)
// Pre: nonw
// Post: nonw
// Return Value: true is val is a space, tab, or new line
// Intent: to determine if val is a space, new line, or tab
/*********************************************************/
bool CCalculator::IsWhiteSpace(char val)
{
	return ((val == ' ') || (val == '\n') || (val == '\t'));
}

/*********************************************************/
// CCalculator::DegToRadian(long double val)
// Pre: none
// Post: none
// Return Value: val converted to radians
// Intent: to convert a value from degrees to radians
/*********************************************************/
long double CCalculator::DegToRadian(long double val)
{
	return ((PI / 180.0) * val);
}

/*********************************************************/
// CCalculator::RadianToDeg(long double val)
// Pre: none
// Post: none
// Return Value: val converted to degrees
// Intent: to convert val to degrees form radians
/*********************************************************/
long double CCalculator::RadianToDeg(long double val)
{
	return ((180.0 * val) / PI);
}

/*********************************************************/
// CCalculator::GetNextChar(CString &form)
// Pre:	none
// Post:none
// Return Value: the next character from form
// Intent: to ge tthe next non whitespace character from
//		   the formula form
/*********************************************************/
char CCalculator::GetNextChar(CString &form)
{	
	if (form.GetLength() == 0)
		return ' ';
	
	char nextchar = form[0];
	form = form.Right(form.GetLength() - 1);
	
	// loop through and remove whitespace up to next 
	// non-whitespace character
	while((form.GetLength() != 0) && (IsWhiteSpace(nextchar))){
		nextchar = form[0];
		form = form.Right(form.GetLength() - 1);
	}
	
	if ((form.GetLength() == 0) && (IsWhiteSpace(nextchar)))
		return ' ';
	
	return nextchar;
}

/*********************************************************/
// CCalculator::GetEntry(int stack_pos)
// Pre: m_RunTimeStack has at least 1 entry
// Post: none
// Return Value: the StackEntry at index stackpos in
//				 m_RuntTimeStack
// Intent: to access the run-time stakc using indexes
/*********************************************************/
ErrorT CCalculator::GetEntry(int stack_pos, StackEntry &entry)
{
	if(stack_pos > m_RunTimeStack.GetCount())
		return OUT_OF_STACK_RANGE;

	entry = m_RunTimeStack.GetAt(m_RunTimeStack.FindIndex(stack_pos));
	return SUCCESSFULL;
}

/*********************************************************/
// CCalculator::SetEntry(int stack_pos, StackEntry entry)
// Pre: m_RunTimeStack has at least stack_pos + 1 entries
// Post: the value at index stack_pos in the run-time stack
//		 is set to entry
// Return Value: none
// Intent: to set a value in the runtime stack using indexes
/*********************************************************/
ErrorT CCalculator::SetEntry(int stack_pos, StackEntry entry)
{
	if(stack_pos > m_RunTimeStack.GetCount())
		return OUT_OF_STACK_RANGE;

	m_RunTimeStack.SetAt(m_RunTimeStack.FindIndex(stack_pos), entry);
	return SUCCESSFULL;
}

/*********************************************************/
// CCalculator::OpInState(Operators oper, int state)
// Pre: none
// Post: none
// Return Value: true if any of the cases are entered
//				 and fase if it is the default case
// Intent: to determine if oper is in state: state
/*********************************************************/
bool CCalculator::OpInState(Operators oper, int state)
{
	switch(state){
	case 0:	return (oper == GCD 
				 || oper == LCM 
				 || oper == MIN  
				 || oper == MAX  
				 || oper == IRAND  
				 || oper == FRAND
				 || oper == FIB);
	case 1: return (oper == LPAREN 
				 || oper == RPAREN);
	case 2:	return (oper == LOG 
				 || oper == LN 
				 || oper == ABS 
				 || oper == ROUND 
				 || oper == FACT
				 || oper == PERCENT
				 || oper == FC
				 || oper == FR
				 || oper == FK
				 || oper == CF
				 || oper == CK
				 || oper == CR
				 || oper == KF
				 || oper == KC
				 || oper == KR
				 || oper == RF
				 || oper == RC
				 || oper == RK
				 || oper == MEAN
				 || oper == MEDIAN
				 || oper == MODE
				 || oper == STDEV
				 || oper == VARIANCE);
	case 3:	return (oper == NCR
				 || oper == NPR  
				 || oper == INTEGER  
				 || oper == FPART 
				 || oper == IPART);
	case 4: return (oper == SQRT 
				 || oper == POW);
	case 5:	return (oper == ARCSIN 
				 || oper == ARCCOS 
				 || oper == ARCTAN 
				 || oper == SIN 
				 || oper == TAN 
				 || oper == COS 
				 || oper == SINH 
				 || oper == COSH 
				 || oper == TANH 
				 || oper == FLOOR 
				 || oper == CEIL);
	case 6: return (oper == MULT 
				 || oper == DIV);
	case 7: return (oper == MOD);
	case 8: return (oper == ADD 
				 || oper == SUBT);
	case 9: return (oper == EQ 
				 || oper == GT 
				 || oper == GE 
				 || oper == LE 
				 || oper == LT 
				 || oper == NE);
	case 10: return (oper == EQUAL);
	case 11: return (oper == CONV_BASE);

	default:
		return false; // Avoids compile errors.  Should never come to this line
	}
}

/*********************************************************/
// CCalculator::OpLevel(Operators val)
// Pre: none
// Post: none
// Return Value: the state that val is in
// Intent: to get the state that val belongs to
/*********************************************************/
int  CCalculator::OpLevel(Operators val)
{
	switch(val){
	case GCD:
	case LCM:
	case MIN:
	case MAX:
	case IRAND:
	case FRAND:
	case FIB:
		return 0;
	case LPAREN:
	case RPAREN:
		return 1;
	case LOG:
	case LN:
	case ABS:
	case ROUND:
	case FACT:
	case PERCENT:
	case FC:
	case FR:
	case FK:
	case CF:
	case CK:
	case CR:
	case KC:
	case KF:
	case KR:
	case RF:
	case RC:
	case RK:
	case MEAN:
	case MEDIAN:
	case MODE:
	case STDEV:
	case VARIANCE:
		return 2;
	case NCR:
	case NPR:
	case INTEGER:
	case FPART:
	case IPART:
		return 3;
	case SQRT: 
	case POW:
		return 4;
	case ARCSIN:
	case ARCCOS:
	case ARCTAN:
	case SIN:
	case TAN:
	case COS:
	case SINH:
	case COSH:
	case TANH:
	case FLOOR:
	case CEIL:
		return 5;
	case MULT:
	case DIV:
		return 6;
	case MOD:
		return 7;
	case ADD:
	case SUBT:
		return 8;
	case EQ:
	case GT:
	case GE:
	case LE:
	case LT:
	case NE:
		return 9;
	case EQUAL:
		return 10;
	case CONV_BASE:
		return 11;
	}
	return -1;
}


long double CCalculator::RoundTrig(long double num)
{
	if ((num < 0.000000000000001) && (num > -0.000000000000001)) return 0;
	return num;
}

/*********************************************************/
// CCalculator::IsValid(CString formula,  HWND window)
// Pre: none
// Post: m_Equation = formula
//		 m_Hwnd = &window
// Return Value: true if formula is a valid equation
// Intent: to validate an equation
/*********************************************************/
bool CCalculator::IsValid(CString formula,  HWND window)
{
	ErrorT status = SUCCESSFULL;
	m_Hwnd = &window;
	GetAvailableStack(formula);
	m_Validating = true;
	status = Translate(m_CurStack);
	m_Validating = false;

	if(status != SUCCESSFULL){
		HandleError(status, formula);
		return false;
	}
	else
		return true;
}


/*********************************************************/
// CCalculator::IsValid(CString formula)
// Pre: none
// Post: m_Equation = formula
//		 m_Hwnd = &window
// Return Value: true if formula is a valid equation
// Intent: to validate an equation
/*********************************************************/
bool CCalculator::IsValid(CString formula)
{
	ErrorT status = SUCCESSFULL;
	GetAvailableStack(formula);
	m_Validating = true;
	status = Translate(m_CurStack);
	m_Validating = false;

	if(status != SUCCESSFULL)
		return false;
	else
		return true;
}

/*********************************************************/
// CCalculator::Compute(CString formula, long double &answer, HWND window)
// Pre: none
// Post: m_Equation = formula
//		 m_Hwnd = &window
// Return Value: the status of the evaluation
// Intent: to parse and evaluate formula
/*********************************************************/
ErrorT CCalculator::Compute(CString formula, long double &answer, HWND window)
{	
	ErrorT status = SUCCESSFULL;
	m_Hwnd = &window;
	m_LongOutput.Empty();

	if(formula.IsEmpty()){
		status = EMPTYEQ;
		HandleError(status, formula);
		return status;
	}
	else if(GetAvailableStack(formula)){
		status = Translate(m_CurStack);
	}
	
	if(status == SUCCESSFULL){
		m_ShowBase = false;
		status = EvaluateTree(&m_Tree[m_CurStack], answer);

		if(m_ErrorMode != ERROR_MODE_SILENT)
			{
			if(status != SUCCESSFULL && m_ErrorMode == ERROR_MODE_COMPLETE)
				HandleRunTimeError(status, m_Equation[m_CurStack]);
			else
				status = SUCCESSFULL;
			}
	}
	else
		HandleError(status, m_Equation[m_CurStack]);

	return status;
}

ErrorT CCalculator::Compute(CString formula, CString str, long double num, long double &answer, HWND window){
	CArray<VariableT, VariableT> mmvariables; 
	VariableT var;
	var.str = str;
	var.num = num;
	mmvariables.Add(var);
	return Compute(formula, &mmvariables, answer, window);
}

ErrorT CCalculator::Compute(CString formula, CArray<VariableT, VariableT> *variables, long double &answer, HWND window){
	return Compute3D(formula,  variables, answer, window);
}

ErrorT CCalculator::Compute3D(CString formula, CArray<VariableT, VariableT> *variables, long double &answer, HWND window){
	ErrorT status = SUCCESSFULL;
	m_Hwnd = &window;
	m_LongOutput.Empty();

	if(formula.IsEmpty()){
		status = EMPTYEQ;
		HandleError(status, formula);
		return status;
	}
	else if(GetAvailableStack(formula)){
		status = Translate(m_CurStack);
	}
	
	if(status == SUCCESSFULL){
		m_pVariables = variables;
		m_ShowBase = false;
		status = EvaluateTree(&m_Tree[m_CurStack], answer);

		if(m_ErrorMode != ERROR_MODE_SILENT)
			{
			if(status != SUCCESSFULL)
				if(m_ErrorMode == ERROR_MODE_COMPLETE || status == UNKNOWN_VARIABLE)
					HandleRunTimeError(status, m_Equation[m_CurStack]);
			else
				status = SUCCESSFULL;
			}
	}
	else
		HandleError(status, m_Equation[m_CurStack]);

	m_pVariables = 0;
	return status;
}

/*********************************************************/
// CCalculator::Translate()
// Pre: none
// Post: m_Stack is cleared and rebuilt for new formula
// Return Value: any error messages
// Intent: to parse m_Formula
/*********************************************************/
ErrorT CCalculator::Translate(int stack)
{	
	/////////// CLEAR STACKS /////////////////////////
	int count = m_RunTimeStack.GetCount();
	for(int i = 0; count > i; ++i)
		m_RunTimeStack.RemoveHead();
	
	count = m_Stack[stack].GetCount();
	for(i = 0; count > i; ++i)
		m_Stack[stack].RemoveHead();
	////////// END CLEAR STACKS /////////////////////
	
	CString formula = m_Equation[stack], var_name, num_string;
	
	// REPLACE CONSTANTS AND UNIT CONVERSIONS ///////
	ReplaceConversions(formula);
	ReplaceConstants(formula);

	if(formula.Find("|") != -1)
		return UNKNOWN_CONSTANT;
	
	m_ShowBase = false;
	CString prevS;
	if(m_PrevAnswerStr.Find("e+") == -1
		&& m_PrevAnswerStr.Find("e-") == -1){
		long double prevans;
		StringToDecimal(m_PrevAnswerStr, m_prevbase, prevans);
		DecimalToString(prevS, prevans);
	}
	else{
		prevS = m_PrevAnswerStr ;
		prevS.Replace("e+", "*10^");
		prevS.Replace("e-", "*10^-");
	}
	formula.Replace("ans", prevS);
	// END REPLACE CONSTANTS AND UNIT CONVERSIONS ///
	
	int associative_parens(0), store_base(-1), dec(0), neg(0), parens(0);

	int fn_number;
	CArray<int,int> fn_colons, fn_parens;
	CArray<Operators, Operators> fn_ops;
	fn_number = -1;

	char nextchar(GetNextChar(formula)), prevchar=0;
	Trans state(STARTT);
	
	num_string.Empty();
	var_name.Empty();
	
	// LOOP TO ERROR_MODE_TRANSLATE STRING
	while(nextchar != ' '){
		switch(state){
		case STARTT:{
			
			if(m_Stack[stack].GetCount()){
				StackEntry tail = m_Stack[stack].GetTail();
				
				if(IsMultiParamOp(tail.oper) && tail.type == OPERATOR && nextchar != '(')
					return EXPECTED_LPAREN;	

				// implicit multiplication
				else if(((IsNum(nextchar) || ((m_IntlMode == US && nextchar == '.') || (m_IntlMode == EUROPEAN && nextchar == ',')) || IsVar(nextchar)) && (prevchar == ')'))
					|| ((tail.type == NUMBER || tail.type == VARIABLE || (tail.type == OPERATOR && tail.oper == RPAREN)) && nextchar == '(')
					|| (IsVar(nextchar) && tail.type == NUMBER)){
					StackEntry temp;
					temp.type = OPERATOR;
					temp.oper = MULT;
					m_Stack[stack].AddTail(temp);
					prevchar = '*';
				}
			}
			
			// unary negation
			if(nextchar == '-' && (m_Stack[stack].GetCount() == 0 || 
								IsLogicOP(m_Stack[stack].GetTail().oper) || 
								m_Stack[stack].GetTail().oper == EQUAL ||
								prevchar =='(' || 
								IsPrefix(m_Stack[stack].GetTail().oper))){
				StackEntry temp;
				temp.type = NUMBER;
				temp.num = -1;
				m_Stack[stack].AddTail(temp);
				
				temp.type = OPERATOR;
				temp.oper = MULT;
				m_Stack[stack].AddTail(temp);
				
				prevchar = '*';
				nextchar = GetNextChar(formula);
			}
			if(((m_IntlMode == US && nextchar == '.') || (m_IntlMode == EUROPEAN && nextchar == ',')) || IsNum(nextchar)){
				if(IsCharNotInBase(m_base, nextchar))
					return BASE_OUT_OF_RANGE;
				state = NUMT;
			}
			else if(IsVar(nextchar))
				state = VART;
			else if(IsLogic(nextchar))
				state = LOGICT;
			else if(IsOp(nextchar))
				state = OPT;
			else
				return UNKNOWNERR;
			break;
					}
		case NUMT:
			{
				bool done = false;
				
				if(IsCharNotInBase(m_base, nextchar) && ((m_IntlMode == US && nextchar != '.') || (m_IntlMode == EUROPEAN && nextchar != ',')))
					done = true;
				
				if(done){
					
					StackEntry temp;
					temp.type = NUMBER;
					ErrorT error;
					
					if(SUCCESSFULL != (error = StringToDecimal(num_string, m_base, temp.num)))
						return error;
					
					if(store_base != -1){
						m_base = store_base;
						store_base = -1;
					}
					
					if(neg)
						temp.num *= -1;
					
					m_Stack[stack].AddTail(temp);
					
					neg = dec = 0;
					num_string.Empty();
					
					state = STARTT;
					break;
				}
				
				if(m_IntlMode == EUROPEAN && nextchar == ',')
					num_string += '.';
				else
					num_string += nextchar;
				
				prevchar = nextchar;
				nextchar = GetNextChar(formula);
				break;
			}
		case VART:
			{	
				if(IsMath(var_name) && !(var_name == "mod" && nextchar == 'e')){
					state = MATHT;
					break;
				}
				
				//  new code to use (and finish up) for next release
				//if(var_name == "mod" && !(var_name == "mod" && nextchar == 'e')){
				//	state = MATHT;
				//	break;
				//}
				
				if(!IsNum(nextchar) && !IsVar(nextchar)){
					
					if(neg)
						var_name = '-' + var_name;
					
					StackEntry temp;
					temp.type = VARIABLE;
					temp.var = var_name;
					m_Stack[stack].AddTail(temp);
					
					neg = 0;
					var_name.Empty();
					
					state = STARTT;
					break;
				}
				
				var_name += nextchar;
				prevchar = nextchar;
				nextchar = GetNextChar(formula);
				break;
			}
		case MATHT:
			{
				StackEntry temp;
				temp.type = OPERATOR;
				
				temp.oper = GetMathOp(var_name);

				if(temp.oper == CONV_BASE){
					store_base = m_base;
					m_base = 10;
				}
				
				if(m_Stack[stack].GetCount()){
					if(m_Stack[stack].GetTail().type == OPERATOR && (IsInfix(temp.oper) || IsPostfix(temp.oper))){
						if(m_Stack[stack].GetTail().oper == MULT)
							m_Stack[stack].RemoveTail();
						else if(OpLevel(m_Stack[stack].GetTail().oper) > OpLevel(temp.oper)
							|| (IsInfix(temp.oper) && !IsPostfix(m_Stack[stack].GetTail().oper)))
							return MULTOPERATORS;
					}
				}
				
				if(associative_parens != 0){
					if(m_Stack[stack].GetTail().type == OPERATOR 
						&& (OpLevel(m_Stack[stack].GetTail().oper) < OpLevel(temp.oper)) 
						&& (IsInfix(temp.oper) || IsLogicOP(temp.oper))){
						
						StackEntry temp;
						temp.type = OPERATOR;
						temp.oper = RPAREN;
						
						for(int i = 0; i < associative_parens; ++i)
							m_Stack[stack].AddTail(temp);
						
						associative_parens = 0;
					}
				}
				if(IsMultiParamOp(temp.oper)){
					m_Stack[stack].AddTail(temp);
					++fn_number;
					fn_ops.SetAtGrow(fn_number, temp.oper);
					fn_colons.SetAtGrow(fn_number, 0);
					fn_parens.SetAtGrow(fn_number, 0);
				}
				else if(temp.oper != -1 && !IsPostfix(temp.oper)){
					m_Stack[stack].AddTail(temp);
					temp.oper = LPAREN;
					m_Stack[stack].AddTail(temp);
					++associative_parens;
					prevchar = '(';
				}
				else if(temp.oper != -1){
					m_Stack[stack].AddTail(temp);
				}
				
				var_name.Empty();
				state = STARTT;
				neg = 0;
				break;
			}
		case LOGICT:
			{
				char tprev = prevchar;
				prevchar = nextchar;
				nextchar = GetNextChar(formula);
				
				StackEntry temp;
				temp.type = OPERATOR;
				
				if(prevchar == '!' && !IsLogic(nextchar)){
					formula = nextchar + formula;
					nextchar = '!';
					prevchar = tprev;
					state = OPT;
					break;
				}
				else if(!IsLogic(nextchar)){
					if(prevchar == '>')
						temp.oper = GT;
					else if(prevchar == '<')
						temp.oper = LT;
					else if(nextchar != '=' && prevchar == '=')
						temp.oper = EQUAL; // assignment eg n=34
					else
						return UNKNOWNERR;
				}
				else{
					if(nextchar == '='  && prevchar == '=')
						temp.oper = EQ;
					else if(nextchar == '='  && prevchar == '>')
						temp.oper = GE;
					else if(nextchar == '='  && prevchar == '<')
						temp.oper = LE;
					else if(nextchar == '='  && prevchar == '!')
						temp.oper = NE;
					else
						return UNKNOWNERR;
					
					prevchar = nextchar;
					nextchar = GetNextChar(formula);
				}			
				StackEntry tail;
				
				if(m_Stack[stack].GetCount() && temp.oper == EQUAL){
					tail = m_Stack[stack].GetTail();
					if(tail.type != VARIABLE)
						return MISSING_VAR;
				}
				else if(temp.oper == EQUAL)
					return MISSING_VAR;

				m_Stack[stack].AddTail(temp);
				state = STARTT;
				
				break;	
			}
		case OPT:
			{
				StackEntry tail;
				
				StackEntry temp;
				temp.type = OPERATOR;
				
				if(nextchar == '+')
					temp.oper = ADD;
				else if(nextchar == '-'){
					if(IsOp(prevchar) && prevchar != ')' && !IsPostfix(m_Stack[stack].GetTail().oper))
						neg = 1;
					else
						temp.oper = SUBT;
				}
				else if(nextchar == '*')
					temp.oper = MULT;
				else if(nextchar == '/')
					temp.oper = DIV;
				else if(nextchar == '^')
					temp.oper = POW;
				else if(nextchar == '%')
					temp.oper = PERCENT;
				else if(nextchar == ':'){
					
					if(fn_number < 0 || fn_parens[fn_number] != 1 || prevchar == '(')
						return UNEXPECTED_OPERATOR;

					temp.oper = COLIN;
					++fn_colons[fn_number];	
				}

				else if(nextchar == '('){
					++parens;
					temp.oper = LPAREN;
				}
				else if(nextchar == ')'){
					if(parens == 0)
						return MISSINGPAREN;
					if(prevchar == '(')
						return EMPTYPARENS;
					if(prevchar == ':')
						return MISSINGPARAM;
					
					--parens;
					temp.oper = RPAREN;
				}
				else if(nextchar == '!')
					temp.oper = FACT;

				// ERROR CHECKING FOR MULTIPLE OPERATORS
				if(m_Stack[stack].GetCount()){
					tail = m_Stack[stack].GetTail();

					if(tail.type == OPERATOR){
						if((((IsInfix(tail.oper) || IsPrefix(tail.oper)) && IsPostfix(temp.oper))
						 ||(IsPrefix(tail.oper) && IsInfix(temp.oper))
						 ||(IsInfix(tail.oper) && IsInfix(temp.oper))
						 ||((IsInfix(tail.oper) || IsPrefix(tail.oper)) && temp.oper == RPAREN)
						 ||(tail.oper == LPAREN && temp.oper != SUBT && temp.oper != LPAREN)
						 ||(IsPostfix(tail.oper) && IsInfix(temp.oper) && (OpLevel(tail.oper) > OpLevel(temp.oper)))
						 //||((IsInfix(tail.oper) || IsPrefix(tail.oper)) 
						 ||(IsPrefix(tail.oper) 
							&& (OpLevel(tail.oper) <= OpLevel(temp.oper)) 
							&& temp.oper != LPAREN
							&& temp.oper != RPAREN)
						    )
							
							&& neg != 1)

							return MULTOPERATORS;
					}
				}
				
				if(!neg){
					if(tail.type == OPERATOR && tail.oper == LPAREN && associative_parens > 0){
						--associative_parens;
						m_Stack[stack].RemoveTail();
					}
					
					if(m_Stack[stack].GetCount()){
						StackEntry tail = m_Stack[stack].GetTail();
						
						// check if we are in a function and we have an LPAREN
						if((IsMultiParamOp(tail.oper) || fn_number >= 0) && temp.oper == LPAREN){
							++fn_parens[fn_number];
						}
						// check if we are in a function and we have an RPAREN
						else if(fn_number >= 0 && temp.oper == RPAREN){
							--fn_parens[fn_number];

							// check to see if we are at end of function, make sure we have
							// at least two params
							if(fn_parens[fn_number] == 0){
								RangeT range = RequiredParams(fn_ops[fn_number]);
								if(fn_colons[fn_number] < range.min)
									return MISSINGPARAM;
								else if(fn_colons[fn_number] > range.max && range.max != -1)
									return EXTRA_PARAMS;
								--fn_number;
							}
						}
					}
					
					//if((associative_parens != 0) && fn_number < 0){
					if((associative_parens != 0)){
						
						StackEntry temp;
						temp.type = OPERATOR;
						temp.oper = RPAREN;
						
						for(; 0 < associative_parens; --associative_parens)
							m_Stack[stack].AddTail(temp);
					}
					
					m_Stack[stack].AddTail(temp);
				}
				
				prevchar = nextchar;
				nextchar = GetNextChar(formula);
				state = STARTT;
				
				break;
			}
			}
	}
	
	if((IsNum(prevchar) || ((m_IntlMode == US && prevchar == '.') || (m_IntlMode == EUROPEAN && prevchar == ','))) && var_name.IsEmpty()){
		
		StackEntry temp;
		temp.type = NUMBER;
		
		ErrorT error;
		if(SUCCESSFULL != (error = StringToDecimal(num_string, m_base, temp.num)))
			return error;
		
		if(store_base != -1){
			m_base = store_base;
			store_base = -1;
		}
		
		if(neg)
			temp.num *= -1;
		
		m_Stack[stack].AddTail(temp);
	}
	else if(IsMath(var_name)){
		// must handle postfix operators here
		StackEntry temp;
		temp.type = OPERATOR;
		
		temp.oper = GetMathOp(var_name);

		if(!IsPostfix(temp.oper))
			return MISSING_OPERAND_END;
		
		if(m_Stack[stack].GetCount()){
			if(m_Stack[stack].GetTail().type == OPERATOR && (IsInfix(temp.oper) || IsPostfix(temp.oper))){
				if(m_Stack[stack].GetTail().oper == MULT)
					m_Stack[stack].RemoveTail();
				else if(OpLevel(m_Stack[stack].GetTail().oper) > OpLevel(temp.oper)
					|| (IsInfix(temp.oper) && !IsPostfix(m_Stack[stack].GetTail().oper)))
					return MULTOPERATORS;
			}
		}
		
		m_Stack[stack].AddTail(temp);
	}
	else if(IsVar(prevchar) || !var_name.IsEmpty()){
		if(neg)
			var_name = '-' + var_name;
		
		StackEntry temp;
		temp.type = VARIABLE;
		temp.var = var_name;
		m_Stack[stack].AddTail(temp);
	}
	
	if(associative_parens != 0){
		
		StackEntry temp;
		temp.type = OPERATOR;
		temp.oper = RPAREN;
		
		for(int i = 0; i < associative_parens; ++i)
			m_Stack[stack].AddTail(temp);
		
		associative_parens = 0;
	}
	
	//////////////////////////////////////////////////////////////////////
	// ERROR CHECKING 
	
	// FOR PARENS
	if(fn_number >= 0)
		return MISSINGPARAM;
	
	// FOR PARENS
	if(parens != 0)
		return MISSINGPAREN;
	
	// EMPTY EQUATION
	if(m_Equation[stack].GetLength() == 0)
		return EMPTYEQ;
	
	//EMPTY STACK
	if(m_Stack[stack].GetCount() == 0)
		return EMPTY_STACK;
	
	// ONLY AN OPERATOR IS ENTERED
	if(m_Stack[stack].GetCount() == 1 && m_Stack[stack].GetHead().type == OPERATOR)
		return NOOPERANDS;
	
	// NO VALUE FOR MATH OPERATOR
	if(m_Stack[stack].GetTail().type == OPERATOR && m_Stack[stack].GetTail().oper != RPAREN
		&& !IsPostfix(m_Stack[stack].GetTail().oper))
		return MISSINGONEOPERAND;
	
	// NO TWO PARAM OPERATOR AT BEGINING OF EXPRESSION
	if(m_Stack[stack].GetHead().type == OPERATOR
	&& !IsPrefix(m_Stack[stack].GetHead().oper)
	&& !IsMultiParamOp(m_Stack[stack].GetHead().oper)
	&& m_Stack[stack].GetHead().oper != LPAREN 
	&& m_Stack[stack].GetHead().oper != RPAREN)
		return MISSINGOPERAND;
	
	//////////////////////////////////////////////////////////////////////
	//ReplaceVars(stack);

	CreateTree();
	return SUCCESSFULL;
}

/*********************************************************/
// CCalculator::GetMathOp(CString var_name)
// Pre: none
// Post: none
// Return Value: the operator specified by var_name
// Intent: to determine which operator var_name is
//		   and return it
/*********************************************************/
Operators CCalculator::GetMathOp(CString var_name)
{
	if(var_name == "sin")
		return SIN;
	else if(var_name == "cos")
		return COS;
	else if(var_name == "tan")
		return TAN;
	else if(var_name == "arcsin")
		return ARCSIN;
	else if(var_name == "arccos")
		return ARCCOS;
	else if(var_name == "arctan")
		return ARCTAN;
	else if(var_name == "hypsin")
		return SINH;
	else if(var_name == "hypcos")
		return COSH;
	else if(var_name == "hyptan")
		return TANH;
	else if(var_name == "log")
		return LOG;
	else if(var_name == "ln")
	    return LN;
	else if(var_name == "sqrt")
		return SQRT;
	else if(var_name == "abs")
		return ABS;
	else if(var_name == "int")
		return INTEGER;
	else if(var_name == "gcd")
		return GCD;
	else if(var_name == "lcm")
		return LCM;
	else if(var_name == "min")
		return MIN;
	else if(var_name == "max")
		return MAX;
	else if(var_name == "fpart")
		return FPART;
	else if(var_name == "ipart")
		return IPART;
	else if(var_name == "irand")
		return IRAND;
	else if(var_name == "frand")
		return FRAND;
	else if(var_name == "round")
		return ROUND;
	else if(var_name == "mod")
		return MOD;
	else if(var_name == "ceil")
		return CEIL;
	else if(var_name == "floor")
		return FLOOR;
	else if(var_name == "farenheitcelcius")
		return FC;
	else if(var_name == "farenheitkelvin")
		return FK;
	else if(var_name == "farenheitrankin")
		return FR;
	else if(var_name == "celciusfarenheit")
		return CF;
	else if(var_name == "celciuskelvin")
		return CK;
	else if(var_name == "celciusrankin")
		return CR;
	else if(var_name == "kelvinfarenheit")
		return KF;
	else if(var_name == "kelvincelcius")
		return KC;
	else if(var_name == "kelvinrankin")
		return KR;
	else if(var_name == "rankinfarenheit")
		return RF;
	else if(var_name == "rankinkelvin")
		return RK;
	else if(var_name == "rankincelcius")
		return RC;
	else if(var_name == "convbase")
		return CONV_BASE;
	else if(var_name == "ncr")
		return NCR;
	else if(var_name == "npr")
		return NPR;
	else if(var_name == "mean")
		return MEAN;
	else if(var_name == "median")
		return MEDIAN;
	else if(var_name == "mode")
		return MODE;
	else if(var_name == "stdev")
		return STDEV;
	else if(var_name == "variance")
		return VARIANCE;
	else if(var_name == "fib")
		return FIB;

	return ADD;
}

/*********************************************************/
// CCalculator::SetRunTimeStack()
// Pre: none
// Post: m_RunTimeStack = m_Stack
// Return Value: none
// Intent: to set the runtime stack
/*********************************************************/
void CCalculator::SetRunTimeStack(int stack)
{
	// CLEAR STACK ///////////////////////
	int count = m_RunTimeStack.GetCount();
	for(int i = 0; count > i; ++i)
		m_RunTimeStack.RemoveHead();
	
	count = m_Stack[stack].GetCount();
	for(i = 0; count > i; ++i)
		m_RunTimeStack.AddTail(m_Stack[stack].GetAt(m_Stack[stack].FindIndex(i)));
}

/*********************************************************/
// CCalculator::HandleRunTimeError(ErrorT error)
// Pre: m_Hwnd is set;
// Post: none
// Return Value: none
// Intent: to display a message box with an appropriate 
//		   error message in it for runtime errors
/*********************************************************/
void CCalculator::HandleRunTimeError(ErrorT error, CString eq)
{
	CString message("Runtime Error");
	
	switch(error){
	case DIV_ZERO:		message = "Illegal attempt to divide by zero";		break;
	case NCR_SIZE:		message = "The first value in nCr must be larger than the second";		break;
	case NCR_INTEGERS:		message = "nCr requires integers only";		break;
	case GCD_ZERO:		message = "gcd requires non 0 values";		break;
	case LCM_ZERO:		message = "lcm requires non 0 values";		break;
	case FACT_INT_ZERO:		message = "Factorial requires positive integers";		break;
	case NPR_INTEGERS:		message = "nPr requires integers only";		break;
	case NPR_SIZE:		message = "The first value in nPr must be larger than the second";		break;
	case GCD_INTEGERS:		message = "gcd must take integer parameters";		break;
	case LCM_INTEGERS:		message = "lcm must take integer parameters";		break;
	case OUT_OF_STACK_RANGE:		message = "Stack index out of range!";		break;
	case INVALID_BASE:		message = "You can only convert values to a base between 2 and 36";		break;
	case FIB_VALUE:		message = "You must enter a positive integer for a fibonacci number - eg fib(6)"; break;
	case ERR_UNKNOWN_OP_TYPE: message = "Unknown operator type"; break;
	case UNKNOWN_VARIABLE: message = "Undefined constant"; break;
	case UNKNOWNERR:		
	default:	break;
	}
	
	MessageBox(ghDlg, ("ERROR: " + message + "\nEQUATION ENTERED: " + eq),"Runtime Error", MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
}

/*********************************************************/
// CCalculator::HandleError(ErrorT error)
// Pre: m_Hwnd is set;
// Post: none
// Return Value: none
// Intent: to display a message box with an appropriate 
//		   error message in it
/*********************************************************/
void CCalculator::HandleError(ErrorT error, CString eq)
{
	CString message("Equation Error");
	
	switch(error){
	case UNKNOWNERR:
		break;
	case MULTOPERATORS:
		message = "You are not allowed multiple operators in a row";
		break;
	case MISSINGPAREN:
		message = "Unmatched parenthesis"; 
		break;
	case NOOPERANDS:
		message = "You did not enter any operands"; 
		break;
	case MISSINGONEOPERAND:
		message = "You did not enter an operand for the last operator"; 
		break;
	case MISSINGOPERAND:
		message = "Missing operand before first operator"; 
		break;
	case EMPTYPARENS:
		message = "Empty set of parenthesis"; 
		break;
	case EMPTYEQ:
		message = "Please enter an equation first"; 
		break;
	case BASE_OUT_OF_RANGE:
		message = "character in formula is out of range for the current base";
		break;
	case BASE_ERROR:
		message = "unknown error converting base";
		break;
	case MULTIPLE_DECIMAL:
		message = "multiple decimals";
		break;
	case EXPECTED_LPAREN:
		message = "Expected left paranthesis. Paranthesis are required for function calls. eg max(2,3)";
		break;
	case MISSING_OPERAND_END:
		message = "Missing operand(s) at end of expression";
		break;
	case EMPTY_STACK:
		message = "The run-time stack is empty. Please makre sur eyou have entered a valid equation.  All constants must be enclosed in parenthesis";
		break;
	case MISSINGPARAM:
		message = "Missing parameter to function.  Make sure you have entered the corrcet number of parameters";
		break;
	case EXTRA_PARAMS:
		message = "Too many parameters to funciton.  Make sure you have entered the corrcet number of parameters";
		break;
	case MISSING_VAR:
		message = "A Variable must precede '='";
		break;
	case UNEXPECTED_OPERATOR:
		message = "Unexpected operator";
		break;
	case UNKNOWN_CONSTANT:
		message = "Unknown constant in expression";
		break;
	}
	
	MessageBox(ghDlg, ("ERROR: " + message + "\nEQUATION ENTERED: " + eq),"Equation Error", MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
}

/*********************************************************/
// CCalculator::ReplaceConstants(CString &formula)
// Pre: none
// Post: none
// Return Value: none
// Intent: to start off the recursive call to replace
//		   any constans in formula
/*********************************************************/
void CCalculator::ReplaceConstants(CString &formula)
{	
	ReplaceConstantsFn(m_Constants, "", formula);
}

/*********************************************************/
// CCalculator::ReplaceConstantsFn(CArray<ConstCatT, 
//								   ConstCatT> &cons, 
//								   CString menu_name, 
//								   CString &formula)
// Pre: none
// Post: formula has all the constants replaced with their values
// Return Value: none
// Intent: to replace constants with their values
/*********************************************************/
void CCalculator::ReplaceConstantsFn(CArray<ConstCatT, ConstCatT> &cons, CString menu_name, CString &formula)
{	
	for(int i = 0; i < cons.GetSize(); ++i){
		
		if(cons[i].sub_menu.GetSize() > 0)
			ReplaceConstantsFn(cons[i].sub_menu, menu_name + cons[i].name + "|", formula);
		
		int num_entries = cons[i].entries.GetSize();
		for(int j = 0; j < num_entries; ++j)
		{
			CString replace = "(" + cons[i].entries[j].value + ")";
			
			if(m_IntlMode == EUROPEAN)
				replace.Replace(".", ",");

			formula.Replace("(" + menu_name + cons[i].name + "|" + cons[i].entries[j].name + ")", replace);
		}
	}
}

/*********************************************************/
// CCalculator::ReplaceConversions(CString &formula)
// Pre: none
// Post: formula has all the conversions replaced with their values
// Return Value: none
// Intent: to replace conversions with their values
/*********************************************************/
void CCalculator::ReplaceConversions(CString &formula)
{
	int i, j, k;
	CString conv, replace;
	
	// REPLACE TEMPERATURE CONVERSIONS: THEY MUST BE HARD CODED
	conv = "(Fahrenheit->Celsius)";
	replace = "farenheitcelcius";
	formula.Replace(conv, replace);
	
	conv = "(Fahrenheit->Kelvin)";
	replace = "farenheitkelvin";
	formula.Replace(conv, replace);
	
	conv = "(Fahrenheit->Rankin)";
	replace = "farenheitrankin";
	formula.Replace(conv, replace);
	
	
	conv = "(Celsius->Fahrenheit)";
	replace = "celciusfarenheit";
	formula.Replace(conv, replace);
	
	conv = "(Celsius->Kelvin)";
	replace = "celciuskelvin";
	formula.Replace(conv, replace);
	
	conv = "(Celsius->Rankin)";
	replace = "celciusrankin";
	formula.Replace(conv, replace);
		
	conv = "(Kelvin->Fahrenheit)";
	replace = "kelvinfarenheit";
	formula.Replace(conv, replace);
	
	conv = "(Kelvin->Celsius)";
	replace = "kelvincelcius";
	formula.Replace(conv, replace);
	
	conv = "(Kelvin->Rankin)";
	replace = "kelvinrankin";
	formula.Replace(conv, replace);
	
	conv = "(Rankin->Fahrenheit)";
	replace = "rankinfarenheit";
	formula.Replace(conv, replace);
	
	conv = "(Rankin->Kelvin)";
	replace = "rankinkelvin";
	formula.Replace(conv, replace);
	
	conv = "(Rankin->Celsius)";
	replace = "rankincelcius";
	formula.Replace(conv, replace);
	// END TEMPERATURE REPLACING
	
	for(i = 0; i < m_Categories.GetSize(); ++i){
		int num_entries = m_Categories[i].entries.GetSize();
		for(j = 0; j < num_entries; ++j){
			for(k = 0; k < num_entries; ++k){
				conv = "(" + m_Categories[i].entries[j].unit + "->" +
					m_Categories[i].entries[k].unit + ")";
				
				if(m_Categories[i].entries[k].type == m_Categories[i].entries[j].type)
					replace = "*((" + m_Categories[i].entries[k].value + 
					")/(" + m_Categories[i].entries[j].value + "))";
				
				else if(m_Categories[i].entries[k].type == m_Categories[i].type_two)
					replace = "*((" + m_Categories[i].entries[k].value + 
					")/((" + m_Categories[i].entries[j].value +
					")*(" + m_Categories[i].conversion + ")))";
				
				else if(m_Categories[i].entries[k].type == m_Categories[i].type_one)
					replace = "*(((" + m_Categories[i].entries[k].value + 
					")*(" + m_Categories[i].conversion +
					"))/(" + m_Categories[i].entries[j].value + "))";
				
				if(m_IntlMode == EUROPEAN)
					replace.Replace(".", ",");

				formula.Replace(conv, replace);
			}
		}
	}
}

/*********************************************************/
// CCalculator::InitConstants()
// Pre: none
// Post: m_Constants has all constants read in from 
//		 constants.dat
// Return Value: none
// Intent: to start off recursive loop to read in constants
/*********************************************************/
void CCalculator::InitConstants()
{
	::ifstream infile;
	CString CSline;
	
	char *cline = new char[100];

	infile.open("constants.dat", ios::nocreate);
	
	if(infile.rdstate() == ios::failbit)
		return;
	
	// read in for GROUP
	infile.getline(cline, 100, '\n');
	CSline = (LPCTSTR)cline;
	CSline.TrimLeft();
	
	if(CSline != "*GROUP*"){
		delete cline;
		return; // ERROR
	}
	
	InitConstCat(m_Constants, &infile, 1);

	delete cline;
	
	infile.close();
}

/*********************************************************/
// CCalculator::InitConstCat(CArray<ConstCatT, ConstCatT> &cat, 
//							::ifstream *infile, int level)
// Pre: none
// Post: m_Constants has values set
// Return Value: the level that the last group read in is at
// Intent: to read in constants.dat and parse it for constants
/*********************************************************/
int CCalculator::InitConstCat(CArray<ConstCatT, ConstCatT> &cat, ::ifstream *infile, int level)
{
	int i(0), stars(0);
	CString CSline;
	char *cline = new char[200];
	
	cat.SetSize(1, 1);

	while(!infile->eof()){

		cat.SetSize(i+1, 1);

		// get group name
		infile->getline(cline, 200, '\n');
		cat[i].name = (LPCTSTR)cline;
		cat[i].name.TrimLeft();
		
		// get the first constant name
		infile->getline(cline, 200, '\n');
		CSline = (LPCTSTR)cline;
		CSline.TrimLeft();
		
		bool new_group(false);
		
		while(!infile->eof() && !new_group){
			if(CSline[0] == '*'){
				// we have a sub menu
				stars = CSline.GetLength();
				CSline.TrimLeft('*');
				stars = stars - CSline.GetLength();
				
				if(stars > level){
					new_group = true;
					stars = InitConstCat(cat[i].sub_menu, infile, level + 1);
				}
				else if(stars <= level)
					new_group = true;
			}
			else{
				// we have constant not sub menu
				ConstantT temp;
				temp.name = CSline;
				
				infile->getline(cline, 200, '\n');
				temp.value = (LPCTSTR)cline;
				temp.value.TrimLeft();
				
				cat[i].entries.Add(temp);
			}
			
			if(!infile->eof() && !new_group){
				infile->getline(cline, 200, '\n');
				CSline = (LPCTSTR)cline;
				CSline.TrimLeft();
			}	
		}
		
		++i;
		
		if(stars < level){
			delete cline;
			return stars;
		}
	}	
	
	delete cline;
	return -1;
}


/*********************************************************/
// CCalculator::InitUnits()
// Pre: none
// Post: m_Categories is filled with all the units
//		 in units.dat
// Return Value: none
// Intent: to read in all the units and store them
/*********************************************************/
void CCalculator::InitUnits()
{
	m_Categories.SetSize(20, -1);
	
	::ifstream infile;
	CString CSline;
	int cat(0);
	
	char *cline = new char[LINE_LENGTH];
	infile.open("units.dat", ios::nocreate);
	
	if(infile.rdstate() == ios::failbit)
		return;
	
	// read in for Standard
	infile.getline(cline, 50, '\n');
	CSline = (LPCTSTR)cline;
	CSline.TrimLeft();
	
	if(CSline != "****STANDARD****"){
		delete cline;
		return; // ERROR
	}
	
	while(!infile.eof()){

		m_Categories.SetSize(cat+1, 1);
		
		// get category name
		infile.getline(cline, LINE_LENGTH, '\n');
		m_Categories[cat].name = (LPCTSTR)cline;
		m_Categories[cat].name.TrimLeft();
		
		// get standard_one unit type
		infile.getline(cline, LINE_LENGTH, '\n');
		m_Categories[cat].type_one = (LPCTSTR)cline;
		m_Categories[cat].type_one.TrimLeft();
		
		// get standard_one unit name
		infile.getline(cline, LINE_LENGTH, '\n');
		m_Categories[cat].standard_one = (LPCTSTR)cline;
		m_Categories[cat].standard_one.TrimLeft();
		
		// get standard_two unit name
		infile.getline(cline, LINE_LENGTH, '\n');
		m_Categories[cat].type_two = (LPCTSTR)cline;
		m_Categories[cat].type_two.TrimLeft();
		
		// get standard_two name name
		infile.getline(cline, LINE_LENGTH, '\n');
		m_Categories[cat].standard_two = (LPCTSTR)cline;
		m_Categories[cat].standard_two.TrimLeft();
		
		// get conversion between types
		infile.getline(cline, LINE_LENGTH, '\n');
		m_Categories[cat].conversion = (LPCTSTR)cline;
		m_Categories[cat].conversion.TrimLeft();
		
		// get the first unit name
		infile.getline(cline, LINE_LENGTH, '\n');
		CSline = (LPCTSTR)cline;
		CSline.TrimLeft();
		
		while(CSline != "****STANDARD****"  && !infile.eof()){
			UnitT tempU;
			tempU.unit = CSline;
			
			// get unit type
			infile.getline(cline, LINE_LENGTH, '\n');
			tempU.type = (LPCTSTR)cline;
			tempU.type.TrimLeft();
			
			// get unit value
			infile.getline(cline, LINE_LENGTH, '\n');
			tempU.value = (LPCTSTR)cline;
			tempU.value.TrimLeft();
			
			m_Categories[cat].entries.Add(tempU);
			
			if(!infile.eof()){
				infile.getline(cline, LINE_LENGTH, '\n');
				CSline = (LPCTSTR)cline;
				CSline.TrimLeft();
			}
		}
		++cat;
	}
	infile.close();
	delete cline;
}

/*********************************************************/
// CCalculator::nCr(long double first, long double second)
// Pre: none
// Post: none
// Return Value: first nCr second
// Intent: the number of combinations of second values
//		   given first values
/*********************************************************/
long double CCalculator::nCr(long double first, long double second)
{
	
	if(first < second)
		return 0;
	else if(int(first) != first || int(second) != second)
		return 0;
	return (nPr(first,second)/factorial(second));
}

/*********************************************************/
// CCalculator::nPr(long double first, long double second)
// Pre: none
// Post: none
// Return Value: first nPr second
// Intent: the number of permutations of second values
//		   given first values
/*********************************************************/
long double CCalculator::nPr(long double first, long double second)
{
	if(int(first) != first || int(second) != second){
		return 0;
	}
	
	return (factorial(first) / factorial(first-second));
}

/*********************************************************/
// CCalculator::factorial(long double first)
// Pre: none
// Post: none
// Return Value: first!
// Intent: to find the factorial of first
/*********************************************************/
long double CCalculator::factorial(long double first)
{
	if(int(first) != first || first < 0){
		return 0;
	}
	
	if(first == 1 || first == 0)
		return 1;
	
	return first * factorial(first - 1);
}

/*********************************************************/
// CCalculator::StringToDecimal(CString theNum, int base, long double &total)
// Pre: m_base >= 2 && m_base <= 36
// Post: total has the answer now
// Return Value: error messages
// Intent: to convert a string in base m_base to a decimal
//		   value in base 10
/*********************************************************/
ErrorT CCalculator::StringToDecimal(CString theNum, int base, long double &total)
{
	theNum.Replace(",", ".");  // if in international mode a '.' is actually a '.'

	if(theNum.IsEmpty()){
		total = 0;
		return SUCCESSFULL;
	}

	bool neg(false);
	char cur;
	total = 0;
	int dec_flag(0);

	if(theNum[0] == '-'){
		neg = true;
		theNum = theNum.Right(theNum.GetLength() - 1);
	}

	int count = theNum.GetLength();
	
	for (int n = 0; n < count; ++n){
		cur = theNum[0];
		
		bool badchar(true);
		
		if((base > (cur - '0')) && (cur >= '0'))
			badchar = false;
		else if((cur < (base + 'a' - 10)) && (cur >= 'a') && (base > 10))
			badchar = false;
		else if((cur < (base + 'A' - 10)) && (cur >= 'A') && (base > 10))
			badchar = false;
		else if(cur == '.')
			badchar = false;
		
		if(badchar)
			return BASE_OUT_OF_RANGE;
		
		if (cur == '.' && !dec_flag)
			dec_flag = 1;
		else if(cur == '.' && dec_flag)
			return MULTIPLE_DECIMAL;
		else{
			if (dec_flag == 0){
				//Handle characters before the decimal
				total *= base;
				if ((cur >= '0') && (cur <= '9'))
					total += (cur - '0');
				else if ((cur >= 'a') && (cur <= 'z'))
					total += (cur - 'a' + 10);
				else if ((cur >= 'A') && (cur <= 'Z'))
					total += (cur - 'A' + 10);
				else
					return BASE_ERROR;  // Bad character... very bad character
			}
			else{
				//Handle character after the decimal
				if ((cur >= '0') && (cur <= '9'))
					total += pow(base, (-1 * dec_flag)) * (cur - '0');
				else if ((cur >= 'a') && (cur <= 'z'))
					total += pow(base, (-1 * dec_flag)) * (cur - 'a' + 10);
				else if ((cur >= 'A') && (cur <= 'Z'))
					total += pow(base, (-1 * dec_flag)) * (cur - 'A' + 10);
				else
					return BASE_ERROR;  // Bad character... very bad character
				++dec_flag;
			}
		}
		theNum = theNum.Mid(1,theNum.GetLength()-1);
	}

	if(neg)
		total *= -1;

	return SUCCESSFULL;
}

/*********************************************************/
// CCalculator::ReplaceVars(int stack)
// Pre: none
// Post: none
// Return Value: none
// Intent: to look through m_Stack and replace variables
//		   with their values that are stored in m_VarList
/*********************************************************/
void CCalculator::ReplaceVars(int stack)
{
	StackEntry temp;
	VarListEntryT entry;
	for(int i = 0; i < m_Stack[stack].GetCount(); ++i){
		temp = m_Stack[stack].GetAt(m_Stack[stack].FindIndex(i));
		if (temp.type == VARIABLE){
			for (int j = 0; j < m_VarList.GetCount(); ++j){
				entry = m_VarList.GetAt(m_VarList.FindIndex(j));
				if (entry.name == temp.var){
					temp.type = NUMBER;
					temp.num = entry.value;
					m_Stack[stack].SetAt(m_Stack[stack].FindIndex(i), temp);
				}
			}
		}		
	}
}

/*********************************************************/
// CCalculator::abs(long double num)
// Pre: one
// Post: none
// Return Value: |num|
// Intent: to find the absolute value of num
/*********************************************************/
long double CCalculator::abs(long double num)
{
	if(num >= 0)
		return num;
	else
		return (-1*num);
}

long double CCalculator::fibonacci(int n)
{
	if(n == 1 || n == 2)
		return 1;

	int a(1), b(1);

	for(int i(2); i < n; ++i){
		int t(b);
		b += a;
		a = t;
	}

	return b;
}

/*********************************************************/
// CCalculator::Logarithm(int new_base, long double num)
// Pre: none
// Post: none
// Return Value: the log os num in base new_base
// Intent: to find the log of num in an arbitrary base
/*********************************************************/
/*long double CCalculator::Logarithm(int new_base, long double num)
{
	long double diff, multiplier(1);
	
	diff = 10 - pow(double(new_base), multiplier);
	
	while(abs(diff) > 0.00000000001){	
		diff = 10 - pow(double(new_base), multiplier);
		multiplier += (diff / 100.0);
	}
	return (log10f(num)*multiplier);
}*/

/*********************************************************/
// CCalculator::roundint(long double num)
// Pre: none
// Post: none
// Return Value: the rounded value of num
// Intent: to round num to the nearest integer
/*********************************************************/
int CCalculator::roundint(long double num)
{
	if (num > 0){
		if ((num - int(num)) >= .5)
			return (int(num) + 1);
		else
			return (int(num));
	}
	else{
		if ((num - int(num)) < -.5)
			return (int(num) - 1);
		else
			return (int(num));
	}
}

/*********************************************************/
// CCalculator::gcd(int num1, int num2)
// Pre: m_Hwnd is set
// Post: none
// Return Value: the gcd of num1 and num2
// Intent: to find the gcd of two numbers
/*********************************************************/
int CCalculator::gcd(CArray<long double, long double> &params)
{	
	// check for errors
	// values must not be > 0
	for(int i = 0; i < params.GetSize(); ++i){
		if(params[i] <= 0)
			return 0;
	}
	
	int one, two;

	while(params.GetSize() > 1){
		one = params[0];
		two = params[1];
		params.RemoveAt(0,2);

		if(one == two)
			params.InsertAt(0, one, 1);
		else{
			int mod(-1);
			
			while (mod!=0){
				int temp(two);
				two = one % two;
				
				if(two == 0)
					break;
				
				one = temp;
				mod = one % two;
			}
			params.InsertAt(0, two, 1);
		}
	}
	return params[0];
}

/*********************************************************/
// CCalculator::lcm(int num1, int num2)
// Pre: none
// Post: none
// Return Value: the lcm of num1 and num2
// Intent: to find the lcm of two numbers
/*********************************************************/
int CCalculator::lcm(CArray<long double, long double> &params)
{	
	// check for errors
	// values must not be > 0
	for(int i = 0; i < params.GetSize(); ++i){
		if(params[i] <= 0)
			return 0;
	}

	int n(1), small, large;
	
	while(params.GetSize() > 1){		
		n = 1;
		
		if(params[0] > params[1]){
			large = params[0];
			small = params[1];
		}
		else{
			large = params[1];
			small = params[0];
		}
		params.RemoveAt(0,2);
		
		while(large*n % small != 0)
			++n;
		
		params.InsertAt(0, large*n, 1);
	}

	return params[0];
}

/*********************************************************/
// CCalculator::frand(long double min, long double max)
// Pre: none
// Post: none
// Return Value: a random double between min and max
// Intent: to find a random double in a given range
/*********************************************************/
long double CCalculator::frand(long double min, long double max)
{
	if( min > max ){
		long double t=min;
		min = max;
		max = t;
	}
	return(rand()*((max-min)/RAND_MAX) + min);
}

/*********************************************************/
// CCalculator::irand(int min, int max)
// Pre: none
// Post: none
// Return Value: a random integer between min and max
// Intent: to find a random integer in a given range
/*********************************************************/
int CCalculator::irand(int min, int max)
{
	if( min > max ){
		int t=min;
		min = max;
		max = t;
	}
		
	return(int(rand()*((double(max + 1)-double(min))/RAND_MAX) + min));
}

bool CCalculator::divisible(long double dValOne, long double dValTwo)
{
	long double division = dValTwo/dValOne;
	return (0 == division - int(division));
}

bool CCalculator::GetAvailableStack(CString new_eq)
{
	int i;
	for(i = 0; i < MAX_EQUATIONS; ++i){
		if(m_Equation[i] == new_eq){
			m_CurStack = i;
			return false;
		}
	}
	m_CurStack = maximum(m_Frequency, MAX_EQUATIONS);
	for(i = 0; i < MAX_EQUATIONS; ++i)
		++m_Frequency[i];

	m_Frequency[m_CurStack] = 0;
	m_Equation[m_CurStack] = new_eq;
	return true;
}

///////////////////////////////////////////////////////////////////////
// Functions for DecimalToString conversion


/*********************************************************/
// CCalculator::intLog(long double num)
// Pre: none
// Post: none
// Return Value: ?????????
// Intent: ??????????
/*********************************************************/
int CCalculator::intLog(long double num)
{
	int theLog(0);
	while(pow(m_base, theLog) <= num){
		theLog++;
	}
	return (--theLog);
}

/*********************************************************/
// CCalculator::addDigit(CString &theString, int digit)
// Pre: none
// Post: digit is added to theString
// Return Value: none
// Intent: to add digit to theString
/*********************************************************/
void CCalculator::addDigit(CString &theString, int digit)
{
	if (digit < 10) theString += char(digit + 48);  //case of a number
	else			theString += char(digit + 55);  //case of a letter
}

/*********************************************************/
// CCalculator::maxDigit(char digit)
// Pre: none
// Post: none
// Return Value: true if digit is a maxmimum digit for the
//				 current base
// Intent: to find out if digit is a maximum digit in the
//		   current base
/*********************************************************/
bool CCalculator::maxDigit(char digit)
{
	if ((m_base <= 10) && (digit - 47 == m_base))
		return true;
	else if((m_base > 10) && (digit - 54 == m_base))
		return true;
	else
		return false;
}

/*********************************************************/
// CCalculator::increaseDigit(char digit)
// Pre: none
// Post: none
// Return Value: half the base
// Intent: to figure out what half the base is for
//			the purpose of rounding
/*********************************************************/
char CCalculator::halfDigit()
{
	if (m_base <= 18) return (char(int(m_base/2)+48));
	else return (char(int(m_base/2)+65));
}

/*********************************************************/
// CCalculator::roundString(CString &theString)
// Pre: none
// Post: theString is rounded
// Return Value: none
// Intent: to round a string if the answer is off slightly
//		   or we have reached maxmimum precision
/*********************************************************/
bool CCalculator::roundString(CString &theString, int num)
{
	int length = theString.GetLength();
	
	if (length != max_places[m_base]) return false;
	if(length < num) return false;

	bool ru(false); //round up flag

	if (theString[(length-num)-1] >= halfDigit()){
		ru = true;
	}
	theString = theString.Left(length-num);
	int count = (length - 1) - num;
	while (ru && (count >= 0)){
		if (maxDigit(theString[count]))	ru = true;
		else ru = false;
		//increment theString[count]
		if (ru){
			theString.SetAt(count,'0');
		}
		else{
			theString.SetAt(count, theString[count] + 1);
			if ((m_base > 10) && (theString[count] == ':')) //the ascii digit after 9
				theString.SetAt(count, 'A');
		}

		count--;
	}
	return ru;
}

/*********************************************************/
// CCalculator::FormatString(CString &theString)
// Pre: theString is a semi formatted number
// Post: theString contains commas and/or spaces, etc.
// Return Value: none
// Intent: to add nice formatting to output strings
/*********************************************************/
void CCalculator::FormatString(CString &theString){

	if(theString.IsEmpty())
		return;
	if(theString == "overflow")
		return;

	int length, decpos, end;
	
	bool neg(false);
	if (theString[0] == '-'){
		neg = true;
		theString.TrimLeft('-');
	}

	if(m_IntlMode == US) theString.Replace('.', '~'); 
	else theString.Replace(',', '~');

	if (m_NumberSeperator){
		length = theString.GetLength();
		decpos = theString.Find('~');
		if (decpos == -1) 
			decpos = theString.Find('e');
		if (decpos == -1)
			decpos = length;
		for (decpos -= m_NumberSeperatorAmount;
			 decpos > 0;
			 decpos -= m_NumberSeperatorAmount){
				theString.Insert(decpos,m_NumberSpaceSeperator);
		}
	}
	
	if (m_DecimalSeperator){
		length = theString.GetLength();
		decpos = theString.Find('~');
		end = theString.Find('e');
		if (decpos == -1) decpos = length;
		if (end == -1) end = length;
		//adding the extra '1' due to the fact that we're
		// inserting the char each time through the loop
		// making the string larger each time
		for (decpos = decpos + 1 + m_DecimalSeperatorAmount;
			 decpos < end;
			 decpos = decpos + 1 + m_DecimalSeperatorAmount){
				theString.Insert(decpos,m_DecimalSpaceSeperator);
				end++;
		}
	}

	if (neg) theString = '-' + theString;

	if(m_IntlMode == US) theString.Replace('~', '.'); 
	else theString.Replace('~', ',');
}


void CCalculator::DecimalToStringSci(CString &str, long double num, int nDecimalPlaces)
{
	if(num > 9999999999999
	|| num < -9999999999999
	|| ((num < 0.0000000000001) && (num > 0))
	|| (num > -0.0000000000001 && (num < 0))){
		
		str.Format("%e", num);

		if(-HUGE_VAL == num || HUGE_VAL == num)
			str = "overflow";	
		else
			DecimalForDisplay(str);
	}
	else if(0 == nDecimalPlaces)
		{
		DecimalToString(str, num);
		DecimalForDisplay(str);
		}
	else
		str.Format("%.*f", nDecimalPlaces, num);
}

/*********************************************************/
// CCalculator::DecimalToString(CString &theString,
//								long double decAnswer)
// Pre: m_base >= 2 && m_base <= 36
// Post: theString is decAnswer converted to its value in
//		 m_base, if m_ShowBase is true, then decAnswer will
//		 be converted to base m_ConvertToBase
// Return Value: any error messages
// Intent: to convert any decimal number to a string in any
//		   base between 2 and 36
/*********************************************************/
ErrorT CCalculator::DecimalToString(CString &theString, long double decAnswer)
{
	bool neg(false);
	if(-HUGE_VAL == decAnswer || HUGE_VAL == decAnswer){
		theString = "overflow";
		return SUCCESSFULL;
	}

	int old_base=10;
	if(m_ShowBase){
		old_base = m_base;
		m_base = m_ConvertToBase;
	}

	if(!m_Validating)
		m_prevbase = m_base;

	theString.Empty();
	if (decAnswer < 0){
		neg = true;
		decAnswer = _chgsign( decAnswer );
	}	

	__int64 int_part (floor(decAnswer));
	double int_trash;
	decAnswer = modf(decAnswer, &int_trash);

	decAnswer = decAnswer * pow(m_base, max_places[m_base]);	
	char decBuffer[100];
	_ui64toa(floor(decAnswer), decBuffer, m_base);
	theString.Format(decBuffer);

	while (theString.GetLength() < max_places[m_base])
		theString = "0" + theString;
	
	CString newString("");
	char numBuffer[100];
	_ui64toa( int_part, numBuffer, m_base );
	
	newString.Format(numBuffer);
	
	if (roundString(theString, newString.GetLength()))
		{
		_ui64toa( ++int_part, numBuffer, m_base );
		newString.Format(numBuffer);
		}
	
	theString = newString + '.' + theString;

	theString.MakeUpper();

	if(m_ShowBase)
		m_base = old_base;

	if(theString.Find(".") != -1)
		theString.TrimRight("0");
	if(theString[theString.GetLength()-1] == '.')
		theString.TrimRight(".");
	if(neg && theString != "0")
		theString = '-' + theString;

	if(m_IntlMode == EUROPEAN)
		theString.Replace(".", ",");

	return SUCCESSFULL;
}

void CCalculator::SetPrevAnswerStr(CString str)
{
	if(m_IntlMode == EUROPEAN)
		str.Replace(".", ",");

	m_PrevAnswerStr = str;
	AddAnsToHistory(str);
}

void CCalculator::AddAnsToHistory(CString str)
{
	if(m_lststrAnswerHistory.GetCount() == m_nAnswerHistoryCount)
		m_lststrAnswerHistory.RemoveTail();
	m_lststrAnswerHistory.AddHead(str);
}


int CCalculator::GetHistoryCount()
{
	return m_lststrAnswerHistory.GetCount();
}

CString CCalculator::GetHistoryStrByIndex(int index)
{
	ASSERT(index < m_lststrAnswerHistory.GetCount());
	return m_lststrAnswerHistory.GetAt(m_lststrAnswerHistory.FindIndex(index));
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void CCalculator::AppendLongOutput(Operators oper, const CArray<long double, long double> &params)
{
	if(oper == CONV_BASE)
	{
		CString base;
		DecimalToStringSci(base, params[1]);
		m_LongOutput += "the entire expression will be converted to base " + base;
	}
	else if(IsPrefix(oper)){
		CString param;
		DecimalToStringSci(param, params[0]);
		m_LongOutput += GetOperatorValue(oper) + "(" + param;
		
		for(int count(1); count < params.GetSize(); ++count){
			DecimalToStringSci(param, params[count]);
			m_LongOutput += ":" + param;
		}

		m_LongOutput += ")";
	}
	else if(IsInfix(oper)){
		CString pre, post;
		DecimalToStringSci(pre, params[0]);
		DecimalToStringSci(post, params[1]);
		m_LongOutput += pre + " " + GetOperatorValue(oper) + " " + post;
	}
	else if(IsPostfix(oper)){
		CString pre;
		DecimalToStringSci(pre, params[0]);
		m_LongOutput += pre + GetOperatorValue(oper);
	}

	m_LongOutput += "\n";
}

long double CCalculator::DoOp(Operators oper, CArray<long double, long double> &params, ErrorT &error)
{	
	if(m_ErrorMode != ERROR_MODE_TRANSLATE)
		AppendLongOutput(oper, params);

	if(oper == SIN || oper == COS || oper == TAN)
		{
		switch(m_trig_state)
			{
			case RADIAN:	params[0] = fmod(params[0],(2*PI)); break;
			case DEGREE:	params[0] = fmod(params[0],360.0); break;
			}
		}

	// if the trig state is DEGREE we need to convert the value 
	// to radians
	if(m_trig_state == DEGREE && 
		(  (oper == SIN) 
		|| (oper == COS) 
		|| (oper == TAN) 
		|| (oper == SINH) 
		|| (oper == COSH) 
		|| (oper == TANH)))
		params[0] = DegToRadian(params[0]);
	
	switch(oper){
	case LOG:		return log10(params[0]);
	case LN:		return log(params[0]);
	case SIN:		return RoundTrig(sin(params[0]));
	case COS:		return RoundTrig(cos(params[0]));
	case TAN:		return RoundTrig(tan(params[0]));
	case ARCSIN:	if(m_trig_state == DEGREE) return RadianToDeg(asin(params[0])); else return asin(params[0]);
	case ARCCOS:	if(m_trig_state == DEGREE) return RadianToDeg(acos(params[0])); else return acos(params[0]);
	case ARCTAN:	if(m_trig_state == DEGREE) return RadianToDeg(atan(params[0])); else return atan(params[0]);
	case SINH:		return sinh(params[0]);
	case COSH:		return cosh(params[0]);
	case TANH:		return tanh(params[0]);
	case SQRT:		return sqrt(params[0]);
	case FACT:		if(int(params[0]) != params[0] || params[0] < 0){ error = FACT_INT_ZERO; return 0.0;} return factorial(params[0]);
	case ABS:		return abs(params[0]);
	case IPART:		return int(params[0]);
	case FPART:		return (params[0] - int(params[0]));
	case INTEGER:	return (int(params[0]));
	case ROUND:		return roundint(params[0]);
	case PERCENT:	return (params[0] / 100.0);
	case FLOOR:		return floor(params[0]);
	case CEIL:		return ceil(params[0]);
	case FC:		return ((params[0]-32.0)*(5.0/9.0));
	case FR:		return (params[0]+459.67);
	case FK:		return (((params[0]-32.0)*(5.0/9.0)) + 273.15);
	case CF:		return ((params[0]*(9.0/5.0))+32.0);
	case CK:		return (params[0] + 273.15);
	case CR:		return (((params[0]*(9.0/5.0))+32.0) + 459.67);
	case KC:		return (params[0] - 273.15);
	case KF:		return (((params[0]-273.15)*(9.0/5.0)) + 32.0);
	case KR:		return (params[0]*(9.0/5.0));
	case RF:		return (params[0]-459.67);
	case RC:		return (((params[0]-459.67)-32.0)*(5.0/9.0));
	case RK:		return (params[0]*(5.0/9.0));


	case POW:   
		if(params[0] >= 0)
			return (long double(::pow(params[0],params[1])));
		else if((1.0/params[1]) == int(1.0/params[1])){  // check to make sure inverse of
														 // params[1] is an integer
			if(int(1.0/params[1]) % 2 == 0) // we have an even number
				return (long double(pow(params[0],params[1]))); // will always return overflow
			else{
				return (-1*(long double(pow((-1*params[0]),params[1])))); 
				// make params[0] positive, and raise to params[1] power
				// and return negative of that
			}
		}
		else{
			return (long double(pow(params[0],params[1])));
		}


	case MULT:  return (params[0]*params[1]);
	case DIV:   if(params[1] == 0){ error = DIV_ZERO; return 0.0;	}
				else return (params[0]/params[1]);
	case MOD:   return (long double(fmod(params[0],params[1])));
	case ADD:	return (params[0]+params[1]);
	case SUBT:	return (params[0]-params[1]);
	case NCR:	if(params[0] < params[1]) error = NCR_SIZE;
				else if(int(params[0]) != params[0] || int(params[1]) != params[1]) error = NCR_INTEGERS;	
				return nCr(params[0], params[1]);
	case NPR:	if(params[0] < params[1]) error = NPR_SIZE;
				else if(int(params[0]) != params[0] || int(params[1]) != params[1]) error = NPR_INTEGERS; return nPr(params[0], params[1]);
	case EQ:	return (params[0] == params[1]);
	case GT:	return (params[0] > params[1]);
	case GE:	return (params[0] >= params[1]);
	case LT:	return (params[0] < params[1]);
	case LE:	return (params[0] <= params[1]);
	case NE:	return (params[0] != params[1]);
	case GCD:	
		{
			for(int i = 0; i < params.GetSize(); ++i){
				if(params[i] <= 0){
					error = GCD_ZERO; 
					return 0.0;
				}
				if(int(params[i]) != params[i]){
					error = GCD_INTEGERS;
					return 0.0;
				}
			} 
			return gcd(params);
		}
	case LCM:	
		{
			for(int i = 0; i < params.GetSize(); ++i){
				if(params[i] <= 0){
					error = LCM_ZERO; 
					return 0.0;
				}
				if(int(params[i]) != params[i]){
					error = LCM_INTEGERS;
					return 0.0;
				}
			}
			return lcm(params);
		}
	case MIN:	return Min(params);
	case MAX:	return Max(params);
	case IRAND:	return irand(params[0], params[1]);
	case FRAND:	return frand(params[0], params[1]);
	case CONV_BASE: m_ConvertToBase = params[1]; m_ShowBase = true; return params[0];
	case MEAN:  return mean(params);
	case MEDIAN:  return median(params);
	case MODE:  return mode(params);
	case STDEV:  return stdev(params);
	case VARIANCE:  return variance(params);
	case FIB: if((params[0] < 1) || (int(params[0]) != params[0])) { error = FIB_VALUE; return 0; }
			  else return fibonacci(params[0]);
		
	}
	error = RUNTIME_ERROR;
	return 0.0;
}


ErrorT CCalculator::EvaluateTree(NodeT *node, long double &answer)
{
	switch(node->type){
	case NUMBER:
		{
			answer = node->num;
			return SUCCESSFULL;
		}
	case VARIABLE:
		{
			bool found_var(false);
			if(m_pVariables){
				for(int i(0); i < m_pVariables->GetSize(); ++i){
					if(m_pVariables->GetAt(i).str == node->var){
						answer = m_pVariables->GetAt(i).num;
						found_var = true;
						break;
					}
				}				
			}
			
			if(!found_var){
				for(int i(0); i < m_VarList.GetCount(); ++i){
					if(m_VarList.GetAt(m_VarList.FindIndex(i)).name == node->var){
						answer = m_VarList.GetAt(m_VarList.FindIndex(i)).value;
						found_var = true;
						break;
					}
				}
			}
			
			if(!found_var)
				return UNKNOWN_VARIABLE;

			return SUCCESSFULL;
		}
	case OPERATOR:
		{
			ErrorT error = SUCCESSFULL;
			CArray<long double, long double> params;
			params.SetSize(node->children.GetSize());

			if(IsPrefix(node->oper)){

				for(int count(0); count < node->children.GetSize(); ++count){
					if((error = EvaluateTree(&node->children[count], params[count])) != SUCCESSFULL)
						return error;
				}

				answer = DoOp(node->oper, params, error);
				return error;
			}
			else if(IsInfix(node->oper)){
								
				if(node->oper != EQUAL){
					
					if((error = EvaluateTree(&node->children[0], params[0])) != SUCCESSFULL)
						return error;
					if((error = EvaluateTree(&node->children[1], params[1])) != SUCCESSFULL)
						return error;
					
					answer = DoOp(node->oper, params, error);			
				}
				else // we have an assigment, eg a=2
				{
					if((error = EvaluateTree(&node->children[1], params[1])) != SUCCESSFULL)
						return error;

					// need to change this list so that it looks at all parameters
					if(node->children[0].var != "x" && node->children[0].var != "y" 
					&& node->children[0].var != "r" && node->children[0].var != "t"){

						bool in_list(false);
						VarListEntryT entry, temp;
						entry.name = node->children[0].var;
						entry.value  = params[1];

						for(int i(0); i < m_VarList.GetCount(); ++i){
							
							temp = m_VarList.GetAt(m_VarList.FindIndex(i));

							if(temp.name == entry.name){ // check to see if variable is already in list
								in_list = true;
								m_VarList.SetAt(m_VarList.FindIndex(i), entry);
								break;
							}
						}
						
						// else, var is not in list, add it
						if(!in_list)
							m_VarList.AddTail(entry);
					}
					answer = params[1];
				}
				return error;
			}
			else if(IsPostfix(node->oper)){

				if((error = EvaluateTree(&node->children[0], params[0])) != SUCCESSFULL)
					return error;
				
				answer = DoOp(node->oper, params, error);
				return error;
			}
			// still need multiparam op
			else
				return RUNTIME_ERROR;
		}
	default:
		return ERR_UNKNOWN_OP_TYPE;
	}
}

ErrorT CCalculator::CreateTree()
{	
	m_Tree[m_CurStack].children.SetSize(0);

	CreateNodes(0, m_Stack[m_CurStack].GetCount() - 1, &m_Tree[m_CurStack]);

	return SUCCESSFULL;
}

ErrorT CCalculator::CreateNodes(int start, int end, NodeT *node)
{
	if(end >= m_Stack[m_CurStack].GetCount())
		return OUT_OF_STACK_RANGE;

	StackEntry current_entry;

	if(!GetStackEntry(start, current_entry))
		return OUT_OF_STACK_RANGE;

	while(current_entry.oper == LPAREN && start <= end){
		int parens(0), stack_pos(start + 1);

		while(stack_pos <= end && parens != -1){
			GetStackEntry(stack_pos++, current_entry);
			if(current_entry.type == OPERATOR && current_entry.oper == LPAREN)
				++parens;
			else if(current_entry.type == OPERATOR && current_entry.oper == RPAREN)
				--parens;
		}
		
		if(parens == -1 && (stack_pos - 1) == end){
			++start;
			--end;
			if(!GetStackEntry(start, current_entry))
				return OUT_OF_STACK_RANGE;
		}
		else
			break;		
	}
	
	int pos;

	if(start == end){
		if(!GetStackEntry(start, current_entry))
			return OUT_OF_STACK_RANGE;
		node->type = current_entry.type;
		node->var = current_entry.var;
		node->num = current_entry.num;
	}
	else{
		// find lowest operator
		pos = FindLowestOper(start, end);

		if(!GetStackEntry(pos, current_entry))
			return OUT_OF_STACK_RANGE;
		node->type = OPERATOR;
		node->oper = current_entry.oper;
		
		if(IsInfix(current_entry.oper)){
			node->children.SetSize(2);
			CreateNodes(start, pos - 1, &node->children[0]);
			CreateNodes(pos + 1, end, &node->children[1]);
		}
		else if(IsPostfix(current_entry.oper)){
			node->children.SetSize(1);
			CreateNodes(start, pos - 1, &node->children[0]);
		}
		else if(IsPrefix(current_entry.oper)){

			if(IsMultiParamOp(current_entry.oper)){
				int params(0), stack_pos(pos + 2), rec_start(pos + 2), rec_end;
				
				while(params != -1){
					
					if(!GetStackEntry(stack_pos, current_entry))
						return OUT_OF_STACK_RANGE;
					while(current_entry.type != OPERATOR && stack_pos < end)
						if(!GetStackEntry(++stack_pos, current_entry))
							return OUT_OF_STACK_RANGE;

					if(current_entry.oper == LPAREN)
						++params;
					else if(current_entry.oper == RPAREN)
						--params;
					
					if(((current_entry.oper == COLIN) && (params == 0)) 
						|| (params == -1)){
						
						rec_end = stack_pos - 1; // stack_pos is at : or )
						
						node->children.SetSize(node->children.GetSize() + 1);
						CreateNodes(rec_start, rec_end, &node->children[node->children.GetSize() - 1]);
						
						//rec_start == rec_end && ':' == rec_start + 1
						
						rec_start = stack_pos + 1; 
						
					}
					++stack_pos;
				}
			}
			else{
				node->children.SetSize(1);
				CreateNodes(pos + 1, end, &node->children[0]);
			}
		}
	}
	
	return SUCCESSFULL;
}

bool CCalculator::GetStackEntry(int i, StackEntry &entry)
{
	if(m_Stack[m_CurStack].GetCount() > i && i >= 0){
		entry = m_Stack[m_CurStack].GetAt(m_Stack[m_CurStack].FindIndex(i));
		return true;
	}
	else
		return false;
}

void CCalculator::SetStackEntry(StackEntry entry, int i)
{

}

int CCalculator::FindLowestOper(int start, int end)
{
	if(end >= m_Stack[m_CurStack].GetCount())
		return -1;

	StackEntry current_entry;
	int pos(-1), state(-1);

	for(int stack_pos = start; stack_pos <= end; ++stack_pos){
		
		if(!GetStackEntry(stack_pos, current_entry))
			return pos;
		while(current_entry.type != OPERATOR && end > stack_pos)
			if(!GetStackEntry(++stack_pos, current_entry))
				return pos;

		int parens(0);
		while(parens > 0 || current_entry.oper == LPAREN){
			
			if(current_entry.oper == RPAREN)
				--parens;
			else if(current_entry.oper == LPAREN)
				++parens;
			
			if(stack_pos >= end)
				return pos;
			if(!GetStackEntry(++stack_pos, current_entry))
				return pos;
			while(current_entry.type != OPERATOR && end > stack_pos)
				if(!GetStackEntry(++stack_pos, current_entry))
					return pos;
		}
		
		if(OpLevel(current_entry.oper) >= state && OpLevel(current_entry.oper) != 1){
			state = OpLevel(current_entry.oper);
			pos = stack_pos;
		}
	}
	return pos;
}



long double CCalculator::mean(const CArray<long double, long double> &params)
{
	long double total(0);
	for(int i(0); i < params.GetSize(); ++i)
		total += params[i];

	return total/long double(params.GetSize());
}

long double CCalculator::mode(const CArray<long double, long double> &params)
{
	CArray<int, int> freq;
	freq.SetSize(params.GetSize());
	freq.InsertAt(0, 0, params.GetSize());

	for (int i(params.GetSize() - 1); i >= 0; --i){
		int n;
		for (n = 0; n < i; ++n)
			if (params[i] == params[n]){
				freq[n]++;
				break;
			}
		if (n == i)
			freq[i]++;
	}
	int max = 0;
	for (int m(0); m < freq.GetSize(); ++m)
		if (freq[m] > freq[max])
			max = m;

	return params[max];
}

RangeT CCalculator::RequiredParams(const Operators &oper)
{
	// all numbers are 1 less than the actual number, eg  0 means 1 param, 1 means 2 param
	// the number is the count of param seperators (ie Colons)
	RangeT range;
	range.min = -1;
	range.max = -1;

	// do switch for min
	switch(oper){
	case MEAN:
	case MIN:
	case MAX:
	case GCD:
	case LCM:
	case MEDIAN:
	case MODE:
	case STDEV:
	case VARIANCE:
	case FIB:
		range.min = 0;
		break;
	case IRAND:
	case FRAND:
		range.min = 1;
		break;
	}

	// do switch for max
	switch(oper){
	case FIB:
		range.max = 0;
		break;
	case MEAN:
	case MIN:
	case MAX:
	case GCD:
	case LCM:
	case MEDIAN:
	case MODE:
	case STDEV:
	case VARIANCE:
		range.max = -1; // -1 means there is no maximum # of params
		break;
	case IRAND:
	case FRAND:
		range.max = 1;
		break;
	}

	return range;
}

long double CCalculator::Min(const CArray<long double, long double> &params)
{
	long double min = params[0];

	for(int i(1); i < params.GetSize(); ++i){
		if(params[i] < min)
			min = params[i];
	}
	return min;
}

long double CCalculator::Max(const CArray<long double, long double> &params)
{
	long double max = params[0];

	for(int i(1); i < params.GetSize(); ++i){
		if(params[i] > max)
			max = params[i];
	}
	return max;
}

void CCalculator::sort(CArray<long double, long double> &params)
{
	for(int i(0); i < (params.GetSize()-1); ++i){
		int min = i;
		for(int j = i; j < params.GetSize(); ++j){
			if (params[j] < params[min]){
				min = j;
			}
		}
		long double tmp = params[i];
		params[i] = params[min];
		params[min] = tmp;
	}
}

long double CCalculator::median(CArray<long double, long double> &params)
{	
	sort(params);
	if (params.GetSize() % 2)
		return params[int(long double(params.GetSize())/2.0-.5)];
	return ((params[params.GetSize() / 2] + 
			params[params.GetSize() /2 - 1]) / 2.0);
}


long double CCalculator::stdev(const CArray<long double, long double>  &params)
{
	return sqrt(variance(params));
}

long double CCalculator::variance(const CArray<long double, long double>  &params)
{
	long double ans(0);
	CArray<long double, long double> deviations;
	deviations.SetSize(params.GetSize());

	for(int i(0); i < params.GetSize(); ++i)
		ans += pow(params[i], 2.0);

	return (ans / long double(params.GetSize())) - pow(mean(params), 2);	
}

void CCalculator::SetErrorMode(ErrorModeE mode){	m_ErrorMode = mode;  }

void CCalculator::SetTrigState(CString val){ 
	if(val == "rad" || val == "radians")
		m_trig_state = RADIAN;
	else if(val == "deg" || val == "degrees")
		m_trig_state = DEGREE;
}

void CCalculator::SetIntlMode(CString val){ 
	if(val == "US" || val == "us")
		m_IntlMode = US;
	else if(val == "EUROPEAN" || val == "european" ||  val == "euro")
		m_IntlMode = EUROPEAN;
}

void CCalculator::SetNormal(bool val){
	m_Normal = val; 
	}

/*********************************************************/
// 
// Pre:
// Post:
// Return Value:
// Intent:
/*********************************************************/
ErrorT CCalculator::EqSolver(CString eq, CString var, double dGuess, 
								long double &ldAnsOut, CString &strAnsOut)
{
	ErrorT error = SUCCESSFULL;
	// search for = and get everyhting on 1 side
	int eq_pos = eq.Find('=');
	if(eq_pos >= 0)
	{
		CString fixed;
		fixed = "(" + eq.Left(eq_pos) + ")-(" + eq.Right(eq.GetLength() - eq_pos-1) + ")";
		eq = fixed;
	}

	long double x1 = dGuess;
	long double x2 = dGuess;
	long double fx, fpx;
	int count(0);
	
	while(abs(x2-x1) > SOLVER_DECIMAL_PRECISION || !count)
	{
		++count;
		x1 = x2;

		if(count >= 1000)
		{
			error = NO_ROOTS;
			goto Error;
		}

		if(SUCCESSFULL != Compute(eq, var, x1, fx, NULL))
			return INVALID_EQ;

		// error checking
		CString strFX, strIND;
		strFX.Format("%f", fx);
		strIND.Format("%f", INDEFINITE);

		if(strFX == strIND)
		{
			error = UNDEFINED_VALUE;
			goto Error;
		}
		else if((fx == HUGE_VAL) || (fx == -HUGE_VAL))
		{
			error = INFINITE_VALUE;
			goto Error;
		}

		// calculate slope
		if(SUCCESSFULL != DyDx(eq, var, x1, fpx))
			return INVALID_EQ;

		// error checking
		if ((fpx == HUGE_VAL) || (fpx == -HUGE_VAL))
		{
			error = INFINITE_VALUE;
			goto Error;
		}

		if(count==1 && -1e-10 < fpx && fpx < 1e-10)
			return ZERO_SLOPE;

		x2 = x1 - (fx/fpx);
	}

	// lets convert to string and see if we can round this
	DecimalToString(strAnsOut, x2);
	StringToDecimal(strAnsOut, 10, ldAnsOut);
	return error;
		
	Error:

		// lets see if bisesction method gets a better answer
		long double ldBiAns;
		ErrorT biError = EqSolverBisection(eq, var, dGuess, ldBiAns);
		if(biError == SUCCESSFULL)
		{
			// lets convert to string and see if we can round this
			DecimalToString(strAnsOut, ldBiAns);
			StringToDecimal(strAnsOut, 10, ldAnsOut);
		}
		return biError;		
}

ErrorT CCalculator::DyDx(const CString eq, CString var, long double x, long double &ldAnsOut)
{
	long double x1, x2, y1, y2;
	x1 = x - DYDX_DELTA;
	x2 = x + DYDX_DELTA;

	if(Compute(eq, var , x1, y1, 0) != SUCCESSFULL)	return UNKNOWNERR;
	if(Compute(eq, var , x2, y2, 0) != SUCCESSFULL)	return UNKNOWNERR;

	ldAnsOut = ((y2-y1)/(x2-x1));

	return SUCCESSFULL;
}


ErrorT CCalculator::EqSolverBisection(CString eq, CString var, double dGuess, long double &ldAns)
{
	int percent = 10;
	long double range = abs((double(percent)/100.0) * dGuess);
	
	if(range < MIN_SOLVER_RANGE)
	{
		range = MIN_SOLVER_RANGE;
	}

	long double min = dGuess - range;
	long double max = dGuess + range;
	long double a = min;
	long double b = max;
	long double a_old, b_old;
	long double p(0), p_old(1);
	long double fp, fa, fb;
	int count(0);
	bool fGreaterThan = false;
	bool fLessThan = false;
	bool fBrokeOut = false;

	while(abs(b-a) > SOLVER_DECIMAL_PRECISION)
	{
		++count;

		p_old = p;
		p = (a+b)/2.0;

		if(p_old == p && count != 1)
			{
			fBrokeOut = true;
			break; // probably cought in a loop, break out
			}

		if(SUCCESSFULL != Compute(eq, var, p, fp, NULL))
			return INVALID_EQ;

		if(a_old != a || count == 1)
			if(SUCCESSFULL != Compute(eq, var, a, fa, NULL))
				return INVALID_EQ;
				
		a_old = a;

		if((fp == 0) && (fp != HUGE_VAL) && (fp != -HUGE_VAL))
			break; // we have exact answer
		else if((fa != HUGE_VAL) && (fa != -HUGE_VAL))
		{	
			if((fp*fa) < 0)
				{
				b = p;
				fLessThan = true;
				}
			else if((fp*fa) > 0)
				{
				a = p;
				fGreaterThan = true;
				}
		}
		else
		{
			if(b_old != b || count == 1)
				if(SUCCESSFULL != Compute(eq, var, b, fb, NULL))
					return INVALID_EQ;
			b_old = b;

			if((fb != HUGE_VAL) && (fb != -HUGE_VAL))
			{	
				if((fp*fb) < 0)
					{
					a = p;
					fGreaterThan = true;
					}
				else if((fp*fb) > 0)
					{
					b = p;
					fLessThan = true;
					}
			}
			else
			{
				// we need to narrow our range a bit
				count = 0;
				--percent;
	
				if(percent == 0)
					return UNDEFINED_VALUE;
				
				a = min = dGuess - abs((double(percent)/100.0) * range);
				b = max = abs((double(percent)/100.0) * range) + dGuess;
				p = 0;
				fGreaterThan = fLessThan = false;
			}
		}
	}

	ldAns = p;

	// we just converged to one of the end points, we didn't really find a root
	if(fLessThan != fGreaterThan && ((abs(a-max) < SOLVER_DECIMAL_PRECISION) || (abs(b-min) < SOLVER_DECIMAL_PRECISION)))
		return NO_ROOTS;
	else if(fBrokeOut)
		return UNKNOWNERR;
	else if((fp == HUGE_VAL) || (fp == -HUGE_VAL))
		return NO_ROOTS;
	else
		return SUCCESSFULL;
}

ErrorT CCalculator::MinMaxSolverBisection(CString eq, CString var, double dMin, 
											double dMax, long double &ldAns, CString &strAns, int &stationary_point)
{
	stationary_point = 0;
	long double a = dMin;
	long double b = dMax;
	long double a_old, b_old;
	long double p = 0, p_old = 1;
	long double fpp, fpa, fpb;
	int count(0);
	bool fGreaterThan = false;
	bool fLessThan = false;
	bool fBrokeOut = false;

	while(abs(b-a) > SOLVER_DECIMAL_PRECISION)
	//while(abs(fpp) > SOLVER_DECIMAL_PRECISION)
	{
		++count;
		p_old = p;
		p = (a+b)/2.0;

		if(p_old == p && count != 1)
			{
			fBrokeOut = true;
			break; // probably cought in a loop, break out
			}

		if(SUCCESSFULL != DyDx(eq, var, p, fpp))
				return INVALID_EQ;

		if(a_old != a || count == 1)
			if(SUCCESSFULL != DyDx(eq, var, a, fpa))
				return INVALID_EQ;
		a_old = a;

		if((fpp == 0) && (fpp != HUGE_VAL) && (fpp != -HUGE_VAL))
			break; // we have exact answer
		else if((fpa != HUGE_VAL) && (fpa != -HUGE_VAL))
		{	
			if((fpp*fpa) < 0)
				{
				b = p;
				fLessThan = true;
				}
			else if((fpp*fpa) > 0)
				{
				a = p;
				fGreaterThan = true;
				}
		}
		else
		{
			if(b_old != b || count == 1)
				if(SUCCESSFULL != DyDx(eq, var, b, fpb))
					return INVALID_EQ;
			b_old = b;

			if((fpb != HUGE_VAL) && (fpb != -HUGE_VAL))
			{	
				if((fpp*fpb) < 0)
					{
					a = p;
					fGreaterThan = true;
					}
				else if((fpp*fpb) > 0)
					{
					b = p;
					fLessThan = true;
					}
			}
			else
				return UNDEFINED_VALUE;
		}
	}

	// we just converged to one of the end points, we didn't really find a root
	if(fLessThan != fGreaterThan && ((abs(a-dMax) < SOLVER_DECIMAL_PRECISION) || (abs(b-dMin) < SOLVER_DECIMAL_PRECISION)))
		return NO_ROOTS;
	else if(fBrokeOut)
		return UNKNOWNERR;

	if(fpa > 0)
		stationary_point = 1;
	else
		stationary_point = -1;
	
	ldAns = p;
	DecimalToString(strAns, p);
	StringToDecimal(strAns, 10, ldAns);
	
	return SUCCESSFULL;
}
