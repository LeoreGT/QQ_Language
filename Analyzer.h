#ifndef __ANALYZER_H__
#define __ANALYZER_H__

#include <iostream>
#include "Tokenizer.h"

class Syntax_t
{
	public :
			inline ~Syntax_t();
			Syntax_t(const Tokenizer_t* _tokenizer);
			void analyzeValidity(size_t _lineNumber);
			void finalCheck();

	private :
			Tokenizer_t*	m_tokenizer;
			size_t m_numPlus;
      size_t m_numMinus;
      size_t m_numBraces;
      size_t m_numParenthesis;
      size_t m_numBrackets;
      int    m_predefinedType;
      int    m_numIf;
      int    m_starter;
      vector <string>	m_keyWords;
			vector <string>	m_types;
			vector <string>	m_operators;
			vector <string>	m_usedVariable;

      Syntax_t() ;
      Syntax_t  ( const Syntax_t& _other);
      Syntax_t& operator =( const Syntax_t& _other);

      bool isLegalVariableName(const string& _str){return(isalpha(*(_str.begin())));};
			bool isTrueKeyWord(const string& _str)      {return(find(m_keyWords.begin(),     m_keyWords.end(), _str)     != m_keyWords.end());};
			bool isOperator(const string& _str)         {return(find(m_operators.begin(),    m_operators.end(), _str)    != m_operators.end());};
			bool isType(const string& _str)             {return(find(m_types.begin(),        m_types.end(), _str)        != m_types.end());};
			bool isVarDeclared(const string& _str)      {return(find(m_usedVariable.begin(), m_usedVariable.end(), _str) != m_usedVariable.end());};
			bool isOpenBrace(const string& _str)        {return(_str == "{" || _str == "(" || _str == "[");};
			bool isCloseBrace(const string& _str)       {return(_str == "}" || _str == ")" || _str == "]");};

      void setTypes();
      void setOperatorsToZero();
			void checkKeyword(size_t _lineNumber, const string& _token);
      void checkOperator(size_t _lineNumber, const string& _token);
      void checkBraceOpen(const string& _token);
      void checkBraceClosing(size_t _lineNumber, const string& _token);
      void checkVars(size_t _lineNumber, const string& _token);

      inline void checkMain(size_t _lineNumber, const string& _token);
			inline void checkType(size_t _lineNumber);
};

/* --------------------------------------------------------------- */

inline Syntax_t::~Syntax_t()
{
  m_numPlus = 0 ;
  m_numMinus = 0;
  m_numBraces = 0;
  m_numParenthesis = 0;
  m_numBrackets = 0;
  m_predefinedType = 0;
  m_numIf = 0;
  m_starter = 0;
}

/* --------------------------------------------------------------- */

inline void Syntax_t::setOperatorsToZero()
{
  if(m_numMinus == 2){ m_numMinus = 0;}
  if(m_numPlus == 2) {m_numPlus = 0;}
}

/* --------------------------------------------------------------- */

inline void Syntax_t::checkMain(size_t _lineNumber, const string& _token)
{
  if(_token != "main")
  {
    cout << "ERROR on line " << _lineNumber << ", you need to start with 'main'" <<endl;
  }
}

/* --------------------------------------------------------------- */

inline void Syntax_t::checkType(size_t _lineNumber)
{
  if(m_predefinedType == 1)
  {
    cout << "ERROR on line " << _lineNumber << ", you have two predefined types" << endl;
    m_predefinedType = 0;
  }
  else
  {
    m_predefinedType = 1;
  }

  setOperatorsToZero();
}

/* --------------------------------------------------------------- */


#endif /* __ANALYZER_H__ */
