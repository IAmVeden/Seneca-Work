#ifndef SICT_UTILITIES_H
#define SICT_UTILITIES_H

#include <string>

namespace sict {

	class Utilities {

		static size_t m_FW;
		static char m_delim;

	public:

		Utilities() {};
		const std::string extractToken(const std::string& str, size_t& next_pos);
		const char getDelimiter() const;
		size_t getFieldWidth() const;
		static void setDelimiter(const char d);
		void setFieldWidth(size_t);



	};



}
#endif