/*
 ============================================================================
 Name        : Station.cpp
 Author      : Robert Parker-Lak
 Email       : rparker-lak@myseneca.ca
 Student #   : 128246170
 Course Code : OOP345
 Section     : SCC
 Date        : August 2, 2019
 Workshop    : Milestone 3
 ============================================================================
 */

 /*
  ============================================================================
  Contains the functionality for filling customer orders with the items. Manages
  a set of identical items and processes a queue of customer orders. 
  ============================================================================
 */
#include "Station.h"

namespace sict {

	//one argument cnstructor that uses an initilization list to set the ItemSet object and sets the name by calling the getname function in the ItemSet subobject
	//
	Station::Station(const std::string& str) : m_subObject(str) {
		m_name = m_subObject.getName();
	}

	//displays the output by calling the display function of the ItemSet subobject
	//
	void Station::display(std::ostream& os) const {
		m_subObject.display(os, true);
	}

	//Uses fillItem() from its queue of CustomerOrder(s) to fill the last order in the queue
	//
	void Station::fill(std::ostream& os) {
		if (!m_queue.empty()) 
			m_queue.front().fillItem(m_subObject, os);
	}

	//query that returns the name of the ItemSet sub_object
	//
	const std::string& Station::getName() const {
		return m_subObject.getName();
	}

	//returns true if the item requests have been filled or there are no items left. False otherwise.
	//
	bool Station::hasAnOrderToRelease() const {
		bool checker = false;
		if (!m_queue.empty()) {
			if (!m_subObject.getQuantity()) 
				checker = true;
			
			else
				checker = m_queue.front().isItemFilled(m_name);
		}
		return checker;
	}

	//modifer that reduces number of items by one, adds one to the serial number and returns a reference to the current object. Calls ItemSet--
	//
	Station& Station::operator--() {
		std::cout << std::endl;
		--m_subObject;
		return *this;
	}

	//pushes the recieved customer order rvalue to the back of the queue.
	//
	Station& Station::operator+=(CustomerOrder&& order) {
		m_queue.push_back(std::move(order));
		return *this;
	}

	//returns true if the item requests have been filled or there are no items left. False otherwise. Also insert the order recieved at the front of the queue
	//
	bool Station::pop(CustomerOrder& ready) {
		bool checker = false;
		if (!m_queue.empty()) {
			checker = m_queue.front().isItemFilled(m_name);
			ready = std::move(m_queue.front());
			m_queue.pop_front();
		}
		return checker;
	}

	//query that formats and outputs the data of the ItemSet subobject
	//
	void Station::validate(std::ostream& os) const {
		os << " getName(): " << m_subObject.getName() << std::endl;
		os << " getSerialNumber(): " << m_subObject.getSerialNumber() << std::endl;
		os << " getQuantity(): " << m_subObject.getQuantity();

	}


}