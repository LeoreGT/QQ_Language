#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <fstream>
#include "Analyzer.h"
#include "Tokenizer.h"

using namespace std;

class Parser_t
{
	public :
			inline Parser_t(const char* _fileName) ;
			inline ~Parser_t();			// DTOR

			inline void ParseFile ();

	private :
			ifstream		  m_file;
			unsigned int 	m_lineNumber;
			Tokenizer_t*	m_tokenizer;
			Syntax_t*		  m_analyzer;

			Parser_t();
			Parser_t(const Parser_t& _other);
			Parser_t&	operator =(const Parser_t& _other);
};

/* --------------------------------------------------------------- */

inline Parser_t::Parser_t(const char* _fileName):m_lineNumber(0)
{
  if (!_fileName)
  {
    throw ("Please put the filname in the command line.");
  }
  m_file.open(_fileName, ifstream::in);
  m_tokenizer = new Tokenizer_t("()[]{}<>=+-*&");
  m_analyzer  = new Syntax_t(m_tokenizer);
}

/* --------------------------------------------------------------- */

inline void Parser_t::ParseFile ()
{
  string newLine;
  int i;

  while (!m_file.eof())
  {
    i = getline(m_file, newLine);
    if(i == -1)
    {
      throw ("Couldn't grab a line, but didn't hit the end of the file");
    }
    m_lineNumber++;
    m_tokenizer->Tokenize(newLine);
    m_analyzer->analyzeValidity(m_lineNumber);
  }
  m_analyzer->finalCheck();
}
/* --------------------------------------------------------------- */

inline Parser_t::~Parser_t()
{
  m_file.close();
  m_lineNumber = 0;
  delete m_tokenizer;
  delete m_analyzer;
}

/* --------------------------------------------------------------- */

#endif /* __PARSER_H__ */
