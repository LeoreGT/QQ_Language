#include <ctype.h>
#include <algorithm>
#include <iostream>
#include "Analyzer.h"

using namespace std;

#define OP_SIZE 12
#define P_TYPE_SIZE 11
#define KEYW_SIZE 11

/* --------------------------------------------------------------- */

void Syntax_t::setTypes()
{
  int i;
  string predefTypesArr[P_TYPE_SIZE] = {"char", "short", "int", "long", "float", "double", "void"};
  string operatorArr[OP_SIZE]        = {"++", "--" "==", "->" , "=", "+", "-", "*", "&", "<<", ">>", "<", ">"};
  string keywordArr[KEYW_SIZE]       = {"if", "else", "for" , "while", "class", "private", "public", "protected", "main", "const", "virtual"};

  for(i = 0; i < OP_SIZE; i++)
  {
    m_operators.push_back(operatorArr[i]);
  }

  for(i = 0; i < P_TYPE_SIZE; i++)
  {
    m_types.push_back(predefTypesArr[i]);
  }

  for(i = 0; i < KEYW_SIZE; i++)
  {
    m_keyWords.push_back(keywordArr[i]);
  }
}

/* --------------------------------------------------------------- */

Syntax_t::Syntax_t(const Tokenizer_t* _tokenizer):m_numPlus(0) , m_numMinus(0), m_numBraces(0), m_numParenthesis(0), m_numBrackets(0), m_predefinedType(0), m_numIf(0), m_starter(0)
{
	if(!_tokenizer)
  {
    throw("Something went wring with the tokenizer pointer.");
  }

  m_tokenizer =(Tokenizer_t*) _tokenizer;
  setTypes();
}

/* --------------------------------------------------------------- */

void Syntax_t::checkKeyword(size_t _lineNumber, const string& _token)
{
  if(m_predefinedType == 1)
  {
    cout << "ERROR on line " << _lineNumber << ", " << _token << " cannot be used as a variable, it is already a keyword" << endl;
    m_predefinedType = 0;
  }

  if(_token == "if")
  {
    m_numIf = 1;
  }

  if(_token == "else")
  {
    if(m_numIf != 1)
    {
      cout << "ERROR on line " << _lineNumber << ", you have an 'else' without an 'if' before it" << endl;
    }
  }

  setOperatorsToZero();
}

/* --------------------------------------------------------------- */

void Syntax_t::checkOperator(size_t _lineNumber, const string& _token)
{
  if(_token == "+")
  {
    m_numPlus++;
    if(m_numPlus > 2) // if more than 2, is illegal
    {
      cout << "ERROR on line " << _lineNumber << ", operator +++ is not legal" << endl;
      m_numPlus = 0;
    }
    m_numMinus = 0;
  }
  if(_token == "-")
  {
    m_numMinus++;
    if(m_numMinus > 2) // if more than 2, is illegal
    {
      cout << "ERROR on line " << _lineNumber << ", operator --- is not legal" << endl;
      m_numMinus = 0;
    }
    m_numPlus = 0;
  }
}

/* --------------------------------------------------------------- */

void Syntax_t::checkBraceOpen(const string& _token)
{
  if(_token == "{")      {m_numBraces++;}
  else if(_token == "[") {m_numBrackets++;}
  else if(_token == "(") {m_numParenthesis++;}
  setOperatorsToZero();
}

/* --------------------------------------------------------------- */

void Syntax_t::checkBraceClosing(size_t _lineNumber, const string& _token)
{
  if(_token == "}")
  {
    (m_numBraces == 0) ? cout << "ERROR on line " << _lineNumber << ", you must first have { to use }" << endl : m_numBraces--;
  }
  else if(_token == "]")
  {
    (m_numBrackets == 0) ? cout << "ERROR on line " << _lineNumber << ", you must first have ( to use )" << endl : m_numBrackets--;
  }
  else if(_token == ")")
  {
    (m_numParenthesis == 0) ? cout << "ERROR on line " << _lineNumber << ", you must first have [ to use ]" << endl : m_numParenthesis--;
  }
  setOperatorsToZero();
}

/* --------------------------------------------------------------- */

void Syntax_t::checkVars(size_t _lineNumber, const string& _token)
{
  if(m_predefinedType != 1){cout << "ERROR on line " << _lineNumber << ", your variable " << _token << " is not a valid name" << endl;}
  else
  {
    if(!isVarDeclared(_token))
    {
      m_usedVariable.push_back(_token);
    }
    else {cout << "ERROR on line " << _lineNumber << ", your variable " << _token << " has been used before, you can't use it again" << endl;}
    m_predefinedType = 0;
  }
  setOperatorsToZero();
}

/* --------------------------------------------------------------- */

void Syntax_t::analyzeValidity(size_t _lineNumber)
{
	string lineSegment;

	while((lineSegment = m_tokenizer->getNext()) != "")
	{
		if(!m_starter)                     {checkMain(_lineNumber, lineSegment); m_starter = 1;}
		if(isType(lineSegment))            {checkType(_lineNumber);}
    else if(isTrueKeyWord(lineSegment)){checkKeyword(_lineNumber, lineSegment);}
    else if(isOperator(lineSegment))   {checkOperator(_lineNumber, lineSegment);}
		else if(isOpenBrace(lineSegment))  {checkBraceOpen(lineSegment);}
    else if(isCloseBrace(lineSegment)) {checkBraceClosing(_lineNumber, lineSegment);}
		else if(isLegalVariableName(lineSegment)) {checkVars(_lineNumber, lineSegment);}
		else if(m_predefinedType == 1)
		{
			cout << "ERROR on line " << _lineNumber << ", " << lineSegment << " is not a valid variable name" << endl;
			m_predefinedType = 0;
		}
	}
}

/* --------------------------------------------------------------- */

void Syntax_t::finalCheck()
{
  if(m_numParenthesis > 0) {cout << "ERROR in file, there are " << m_numParenthesis << " parentheses ( that have not been closed" << endl;}
  if(m_numBrackets > 0)    {cout << "ERROR in file, there are " << m_numBrackets << " brackets [ that have not been closed" << endl;}
  if(m_numBraces > 0)      {cout << "ERROR in file, there are " << m_numBraces << " braces { that have not been closed" << endl;}
}

/* --------------------------------------------------------------- */
