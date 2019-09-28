/*
 ============================================================================
 Name        : Utilities.cpp
 Author      : Robert Parker-Lak
 Email       : rparker-lak@myseneca.ca
 Student #   : 128246170
 Course Code : OOP345
 Section     : SCC
 Date        : July 14, 2019
 Workshop    : Milestone 1
 ============================================================================
 */

 /*
  ============================================================================
  Description : Support module that determines field width, and extracts parts
  of a string called "tokens"
  ============================================================================
 */

#include "Utilities.h"

namespace sict {

	//static variables delimiter and field width
	size_t Utilities::m_FW = 0;
	char Utilities::m_delim = '|';

	//function that extracts next token in the string, increases field width size if needed,
	//returns the token
	//
	const std::string Utilities::extractToken(const std::string& str, size_t& next_pos) {
		std::string temp;
		if (str.size() > next_pos)
			temp = str.substr(next_pos, str.find(m_delim, next_pos) - next_pos);


		else
			temp = "";


		if (str.find(m_delim, next_pos) != std::string::npos)
			next_pos = str.find(m_delim, next_pos) + 1;


		else
			next_pos = std::string::npos;

		if (temp.size() == 0)
			throw "Tis most empty";

		return temp;

	}

	//query that returns the current delimeter
	//
	const char Utilities::getDelimiter() const {
		return m_delim;
	}

	//query that returns the current field width
	//
	size_t Utilities::getFieldWidth() const {
		return m_FW;
	}

	//modifier that sets the delemiter to the passed variable
	//
	void Utilities::setDelimiter(const char d) {
		m_delim = d;
	}

	//modifier that sets the field width to the passed variable
	//
	void Utilities::setFieldWidth(size_t fw) {
		if (fw > m_FW)
			m_FW = fw;
	}





}