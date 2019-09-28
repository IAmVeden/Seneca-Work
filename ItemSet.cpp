/*
 ============================================================================
 Name        : ItemSet.cpp
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
  Manages the stock inventory of a particular item. Divides a string into four
  member variables that contain the information for the item to go into the
  inventory.
  ============================================================================
 */
#include "ItemSet.h"

namespace sict {

	//constructor that recieves a string and parses the string into four member variables
	//
	ItemSet::ItemSet(const std::string str) {
		size_t next = 0;
		try {
			m_name = m_utilObj.extractToken(str, next);
			if (m_name.size() > m_utilObj.getFieldWidth())
				m_utilObj.setFieldWidth(m_name.size());


			if (next <= str.size())
				m_serial = std::stoul(m_utilObj.extractToken(str, next));

			if (next <= str.size())
				m_numberOfItems = std::stoul(m_utilObj.extractToken(str, next));

			if (next <= str.size())
				m_description = m_utilObj.extractToken(str, next);
		}
		catch (std::string str) {
			std::cerr << str << std::endl;
		}

	}

	//move operator definition
	//
	ItemSet::ItemSet(ItemSet && copy) {
		if (this != &copy) {
			m_name = copy.m_name;
			m_description = copy.m_description;
			m_numberOfItems = copy.m_numberOfItems;
			m_serial = copy.m_serial;
			copy.m_name.clear();
			copy.m_description.clear();
			copy.m_numberOfItems = 0;
			copy.m_serial = 0;

		}

	}

	//query that returns the member variable name
	//
	const std::string& ItemSet::getName() const {
		return m_name;
	}

	//query that returns the member variable serial
	//
	const unsigned int ItemSet::getSerialNumber() const {
		return m_serial;
	}

	//query that returns the member variable number of items
	//
	const unsigned int ItemSet::getQuantity() const {
		return m_numberOfItems;
	}

	//function that decrements the number of items by one, increments the serial by one and returns the current object 
	ItemSet& ItemSet::operator--() {
		m_numberOfItems--;
		m_serial++;
		return *this;
	}

	//formats and displays the output
	void ItemSet::display(std::ostream& os, bool full) const {

		if (!full) {
			os.width(m_utilObj.getFieldWidth());
			os << m_name << " [";
			os.width(5);
			os << m_serial << "]" << std::endl;
		}
		else {
			os.width(m_utilObj.getFieldWidth());
			os.setf(std::ios::left);
			os << m_name << " [";
			os.width(5);
			os << m_serial << "] Quantity ";
			os.width(3);
			os << m_numberOfItems << " Description: " << m_description << std::endl;
		}

	}

}