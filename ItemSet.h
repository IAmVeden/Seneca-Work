#ifndef SICT_ITEMSET_H
#define SICT_ITEMSET_H

#include <string>
#include <iostream>
#include "Utilities.h"

namespace sict {

	class ItemSet {

		Utilities m_utilObj;
		unsigned int m_serial;
		std::string m_name;
		unsigned int m_numberOfItems;
		std::string m_description;

	public:

		ItemSet() {};
		ItemSet(const std::string str);
		const std::string& getName() const;
		const unsigned int getSerialNumber() const;
		const unsigned int getQuantity() const;
		ItemSet& operator--();
		void display(std::ostream& os, bool full) const;
		ItemSet(ItemSet && copy);


		ItemSet(const ItemSet&) = delete;
		ItemSet& operator=(const ItemSet&) = delete;
		ItemSet& operator=(ItemSet&&) = delete;

	};




}



#endif
