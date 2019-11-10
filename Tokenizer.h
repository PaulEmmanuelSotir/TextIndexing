#pragma once

#include <string>
#include <sstream>

#include "utility.h"

/**
* separate tags from data
**/
class PreprocessorTagsData
{
public:
	std::string separateTagsData(std::istream& is);

private:
	enum class status_t { data, tag, eof } status = status_t::data;
};

struct Token_t {
	
	enum TokenType_t {
		SEPARATOR,
		LITERAL,
		NUMBER,
		MONEY,
		PERCENTAGE,
	};
	
	TokenType_t type;
	std::string word;
	double value;
	
	Token_t(const std::string& word, TokenType_t type)
		: word(word), type(type)
	{}

	Token_t(const std::string& number, double value, TokenType_t type)
		: word(number), value(value), type(type)
	{}

};

/**
* extract the tokens of a string
**/
class Tokenizer
{
public:
	Tokenizer();

	/**
	 * extract a token from a stream
	 * @param is the stream
	 * @return the first token of the stream
	 */
	Token_t extractToken(std::istream & is);

	bool Tokenizer::extract(const std::string& data, const string_view& range, string_view& result);

	bool isNextTokenASeparator(std::istream& is, std::string& separator);

private:
	/// look up table of valid litteral characters
	bool isCharValidText[256] = {};
	/// look up table of valid single char tokens
	bool isCharValidToken[256] = {};
	/// array of valid separators
	std::vector<std::string> separators;

	void initializeLUTs();
	void initializeSeparators();
};
