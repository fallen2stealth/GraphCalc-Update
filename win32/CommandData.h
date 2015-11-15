#if !defined(CCOMMANDDATA)
#define CCOMMANDDATA

#include "stdafx.h"
#include <afxtempl.h>

enum ParamTypeE {PARAM_STRING, PARAM_NUMBER, PARAM_BOOL};

struct SCommandParam{
	bool required;
	ParamTypeE type;
};

class CCommandData : public CObject{	
public:
	CCommandData();
	void ClearAll();
	int GetRequiredArguments();

	CString name;
	CArray<SCommandParam, SCommandParam> params;
};

#endif