#if !defined(CGCCOMMAND)
#define CGCCOMMAND

//#include "stdafx.h"
//#include <afxtempl.h>
#include "resource.h"		// main symbols
#include "CCalculator.h"
#include "CommandData.h"
//#include "GrphCalcDlg.h"
#include "globals.h"

CString GetIfCondition(CString command);
CString GetElseIfCondition(CString command);
CString GetWhileCondition(CString command);

bool IsIfCommand(CString command, bool errors=false);
bool IsElseIfCommand(CString command, bool errors=false);
bool IsWhileCommand(CString command, bool errors=false);
bool IsScriptCommand(CString command, CString condition, CString error, bool errors=false);

enum ECommandError{SUCCESS,
				   UNKOWN_COMMAND,
				   FORMAT_ERROR, 
				   UNMATCHED_QUOTE,
				   INVALID_NUMBER,
				   TOO_MANY_ARGS,
				   TOO_FEW_ARGS,
				   UNKNOWN_ARG_VAL,
				   NOT_ON_3D,
				   NOT_ON_2D};

class CGCCommand : public CObject{
public:
	void HandleError(HWND window);
	CGCCommand();
	~CGCCommand();
	
	void SetControls(CCalculator *pCalc);
	bool ExecuteCommand(CString command);
	bool ParseCommand(CString command);
	bool GetComment(CString command, CString &comment);

	CString m_Command;
	
	// validated parameter storage
	CArray<CString, CString> m_StringParams;
	CArray<long double, long double> m_NumberParams;
	CArray<bool, bool> m_BoolParams;

private:
	SCommandParam NewParam(ParamTypeE type, bool required);
	SCommandParam NewParam(ParamTypeE type);
	bool PerformProgramCommand();
	bool Perform3DCommand();
	bool Perform2DCommand();
	bool ValidateParameters();
	bool PerformCommand();
	bool ParseParameters(CString &command);
	bool ExtractValidateCommand(CString &command);
	void InitializeCommands();

	// Command Functions
	void DispVal(long double val, CString msg="value");
	void PromptVal(CString var, CString msg="Please enter a value");

	COLORREF ColorLookupCOLORREF(CString color);
	ColorT   ColorLookupColorT(CString color);

	CCommandData m_aCommands[MAX_NUMBER_COMMANDS];
	
	CString m_sCommandAndArgs;

	int m_CommandIndex;
	CArray<CString, CString> m_Parameters;
	
	ECommandError m_eError;

	CCalculator *m_pCalculator;
	int	m_NumberCommands;
};

#endif
