#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include <string>
#include <deque>
#include <vector>

using namespace std;

class Tokenizer_t
{
	public:
			Tokenizer_t(const string& _delimiters):m_line(""),m_currIt(m_line.begin()),m_delimiters(_delimiters) {};
			~Tokenizer_t(){}

			void Tokenize(const string& _line);
			string getNext();

	private:
      string            m_line;
      string            m_delimiters;
      string::iterator  m_currIt;
      deque <string>    m_tokens;

      bool   isDelim(char _ch) {return (m_delimiters.find(_ch) != std::string::npos);};
      void   passSpace()       {while((m_currIt != m_line.end()) && (isspace(*m_currIt))){ ++m_currIt;};};
      string getCurrToken();
			Tokenizer_t(const Tokenizer_t& _other);
			Tokenizer_t&	operator=(const Tokenizer_t& _other);
};


#endif /* __TOKENIZER_H__ */

