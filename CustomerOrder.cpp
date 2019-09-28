/*
 ============================================================================
 Name        : CustomerOrder.cpp
 Author      : Robert Parker-Lak
 Email       : rparker-lak@myseneca.ca
 Student #   : 128246170
 Course Code : OOP345
 Section     : SCC
 Date        : July 24, 2019
 Workshop    : Milestone 2
 ============================================================================
 */

 /*
  ============================================================================
  Uses an ItemInfo subobject and the Utilities module to categorize and fill 
  customer orders. Also allows querying if item is filled and formats and 
  displays customer orders.
  ============================================================================
 */
#include "CustomerOrder.h"

namespace sict {

	//one argument constructor that extracts values from passed string and fills the CustomerOrder member variables and the name of the ItemInfo sub-object
	//
	CustomerOrder::CustomerOrder(const std::string str) {
		size_t intermitent = 0;
		m_customerName = utility.extractToken(str, intermitent);
		if (m_customerName.size() > utility.getFieldWidth()) 
			utility.setFieldWidth(m_customerName.size());
		
		if (intermitent <= str.size()) 
			m_productName = utility.extractToken(str, intermitent);
		
		while (intermitent <= str.size()) {
			ItemInfo* temp;
			temp = new ItemInfo[m_count];
			for (size_t i = 0; i < m_count; i++) 
				temp[i] = m_stock[i]; 

			delete[] m_stock;
			m_stock = new ItemInfo[++m_count];
			for (size_t i = 0; i < m_count - 1; i++) 
				m_stock[i] = temp[i]; 

			delete[] temp;
			m_stock[m_count - 1].m_mName = utility.extractToken(str, intermitent);
		}

		static int hack = 0;  //These few lines deal with formating. Without them there would be no space between getQuantity() and the customer orders line
		if (hack == 0) {
			std::cout << std::endl;
			hack++;
		}
	}


	//move consructor
	//
	CustomerOrder::CustomerOrder(CustomerOrder&& mov) {
		if (this != &mov)
			*this = std::move(mov);

	}


	//move assignment operator
	//
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& mov) {
		if (this != &mov) {
			delete[] m_stock;
			m_stock = nullptr;
			m_customerName = mov.m_customerName;
			m_productName = mov.m_productName;
			m_count = mov.m_count;
			m_stock = mov.m_stock;
			mov.m_customerName = "";
			mov.m_productName = "";
			mov.m_count = 0;
			mov.m_stock = nullptr;
		}
		return *this;
	}


	//destructor, deallocates memory
	//
	CustomerOrder::~CustomerOrder() {
		delete[] m_stock;
	}


	//loops through the ItemInfo array and fills the items that are empty, decrements the stock in ItemSet if accepted and outputs relevant information 
	//
	void CustomerOrder::fillItem(ItemSet& item, std::ostream& os) {

		for (size_t i = 0; i < m_count; i++) {
			if (item.getName() == m_stock[i].m_mName) {
				if (item.getQuantity() > 0 && m_stock[i].m_mFillStatus == false) {
					m_stock[i].m_mSerial = item.getSerialNumber();
					m_stock[i].m_mFillStatus = true;
					os << " Filled " << this->getNameProduct() << "[" << m_stock[i].m_mName << "][" << m_stock[i].m_mSerial << "]" << std::endl;
					--item;
				}
				else if (item.getQuantity() > 0 && m_stock[i].m_mFillStatus == true)
					os << " Unable to fill " << this->getNameProduct() << "[" << m_stock[i].m_mName << "][" << m_stock[i].m_mSerial << "] already filled" << std::endl;

				else
					os << " Unable to fill " << this->getNameProduct() << "[" << m_stock[i].m_mName << "][" << m_stock[i].m_mSerial << "] out of stock" << std::endl;
			}
		}

	}


	//query that checks to see if all items in the m_stock array are filled
	//
	bool CustomerOrder::isFilled() const {
		int checker = 1;
		for (size_t i = 0; i < m_count; i++) {
			checker *= static_cast<int>(m_stock[i].m_mFillStatus);
		}
		return static_cast<bool>(checker);

	}


	//query that checks to see if a particular item in the m_stock array is filled
	//
	bool CustomerOrder::isItemFilled(const std::string& item) const {
		int checker = 1;
		for (size_t i = 0; i < m_count; i++) {
			if (m_stock[i].m_mName == item) {
				checker *= static_cast<int>(m_stock[i].m_mFillStatus);
			}
		}
		return static_cast<bool>(checker);

	}


	//query that returns the formated name of customer and product
	//
	std::string CustomerOrder::getNameProduct() const {
		std::string name = m_customerName + " [" + m_productName + "]";
		return name;
	}


	//formats and displays output
	//
	void CustomerOrder::display(std::ostream& os, bool showDetail) const {
		if (!showDetail) {
			os.width(utility.getFieldWidth());
			os << m_customerName; 
			os.setf(std::ios::left);
			os << " [" << m_productName << "]" << std::endl;
			if (m_count > 0) {
				for (size_t i = 0; i < m_count; i++) {

					for (size_t i = 0; i < utility.getFieldWidth() + 1; i++)
						os << ' ';

					os << m_stock[i].m_mName << std::endl;
				}
			}
		}
		else {
			os.width(utility.getFieldWidth());
			os << m_customerName;  
			os << " [" << m_productName << "]" << std::endl;
			if (m_count > 0) {
				for (size_t i = 0; i < m_count; i++) {

					for (size_t i = 0; i < utility.getFieldWidth() + 1; i++)
						os << ' ';

					os << "[" << m_stock[i].m_mSerial << "] ";
					os << m_stock[i].m_mName << " - ";
					if (m_stock[i].m_mFillStatus == true)
						os << "FILLED" << std::endl;
					else
						os << "MISSING" << std::endl;

				}
			}
		}



	}
}