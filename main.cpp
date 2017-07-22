#include "Parser.h"
#include "Tokenizer.h"

#include <iostream>
using namespace std;

int main(int argc , char * argv[])
{
	int i;

	for (i = 1; i < argc ; ++i )
	{
		Parser_t p1 (argv[i]);
    cout << endl << i << ": ERRORS FOR FILE: " << argv[i] << endl;
		p1.ParseFile();
    cout << endl;
	}
	return 0;
}
