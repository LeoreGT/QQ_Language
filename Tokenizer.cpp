#include "Tokenizer.h"
#include <iostream>
using namespace std;

/* --------------------------------------------------------------- */

void Tokenizer_t::Tokenize(const string& _line)
{
	string currTok;

	m_line = _line;
	m_currIt = m_line.begin();

	while((currTok = getCurrToken()) != "")
	{
		m_tokens.push_back(currTok);
	}
}

/* --------------------------------------------------------------- */

string Tokenizer_t::getNext()
{
	string nextToken;

	if(m_tokens.begin() != m_tokens.end())
	{
		nextToken = *(m_tokens.begin());
		m_tokens.erase( m_tokens.begin());
	}
	else {nextToken = "";}

	return nextToken;
}

/* --------------------------------------------------------------- */

string Tokenizer_t::getCurrToken()
{
	string token;

	if(m_line.size() <= 0) {return "";}

	passSpace();
	while(m_currIt != m_line.end())
	{
		if (!isspace (*m_currIt))
		{
			token += *m_currIt;
			m_currIt++;

			if((isDelim(*m_currIt))||(isDelim (*(m_currIt - 1))))
      {
        break;
      }
		}
		else
		{
			passSpace();
			break;
		}
	}
	return token;
}

/* --------------------------------------------------------------- */
