#include <string>
#include <fstream.h>

using namespace std ;

void CCalculator::InitKeywords()
{
	KeywordT temp;
	ifstream infile;
	string kwd, rstr;
	infile.open("keywords.txt");

	while(!infile.eof()){
		temp.newstring.Empty();
		temp.keyword.Empty();
		
		infile >> kwd;
		infile >> rstr;

		for(int i = 0; i < kwd.length(); ++i)
			temp.keyword += kwd[i];

		for(int i = 0; i < rstr.length(); ++i)
			temp.newstring += rstr[i];

		temp.newstring = "*" + temp.newstring;
		m_Keywords.AddTail(temp);
}