#include "CommandData.h"

CCommandData::CCommandData(){
	
	
}

void CCommandData::ClearAll(){
	name.Empty();
	params.RemoveAll();
}

int CCommandData::GetRequiredArguments(){
	int count(0);
	for(int i(0); i < params.GetSize(); ++i){
		if(params[i].required) ++count;
	}

	return count;
}