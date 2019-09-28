/*
 ============================================================================
 Name        : LineManager.cpp
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
  Processes customer orders across the assembly line. Moves orders along assembly
  line step by step, filling station orders that are ready until they are filled
  or incomplete due to lack of inventory.
  ============================================================================
 */
#include "LineManager.h"

namespace sict {

	//Five argument constructor that loops though the customer orders to push them to the front of the queue which holds the orders to be filled. Also finds and sets the index of the last station
	//
	LineManager::LineManager(std::vector<Station*>& station, std::vector<size_t>& nextwards, std::vector<CustomerOrder>& customers, size_t starting, std::ostream& os) {
		m_stations.resize(station.size());
		for (size_t i = 0; i < station.size(); i++) 
			m_stations.at(i) = station.at(i);
		

		for (size_t i = 0; i < customers.size(); i++) 
			m_toBeFilled.push_back(std::move(customers.at(i)));
		
		m_first = starting;

		m_next.resize(nextwards.size());

		for (size_t i = 0; i < m_next.size(); i++) 
			m_next.at(i) = nextwards.at(i);
		

		m_last = m_first;
		while (m_next.at(m_last) != m_stations.size()) 
			m_last = m_next.at(m_last);
		

	}

	//Sorts the queue into completed and missing objects and outputs them using CustomerOrders display
	//
	void LineManager::display(std::ostream& os) const {
		os << "COMPLETED ORDERS" << std::endl;
		for (auto& i : m_finished) 
			i.display(os, true); 

		os << std::endl;

		os << "INCOMPLETE ORDERS" << std::endl;
		for (auto& i : m_incomplete) 
			i.display(os, true); 
	}


	//Runs the program by  running the customer orders through the stations
	//
	bool LineManager::run(std::ostream& os) {
		bool checker = false;
		size_t total = m_toBeFilled.size();
		std::string old;
		std::string next;
		std::string name;

		while (!m_toBeFilled.empty() || total) {

			if (!m_toBeFilled.empty()) {
				*(m_stations.at(m_first)) += std::move(m_toBeFilled.front());
				m_toBeFilled.pop_front();
			}

			for (size_t i = 0; i < m_stations.size(); i++) 
				m_stations.at(i)->fill(os);
			

			size_t index = m_first;
			CustomerOrder temp;
			for (size_t i = 0; i < m_stations.size(); i++) {
				if (m_stations.at(i)->hasAnOrderToRelease()) {
					m_stations.at(i)->pop(temp);
					if (i != m_last) {
						old = m_stations.at(i)->getName();
						index = m_next.at(i);
						if (index != m_stations.size()) {
							next = m_stations.at(index)->getName();
							name = temp.getNameProduct();
							*(m_stations.at(index)) += std::move(temp);
							os << " --> " << name << " moved from " << old << " to " << next << std::endl;
						}
					}
					else {
						name = temp.getNameProduct();
						old = m_stations.at(i)->getName();
						os << " --> " << name << " moved from " << old << " to ";
						if (temp.isFilled()) {
							os << "Completed Set" << std::endl;
							m_finished.push_back(std::move(temp));
						}
						else {
							os << "Incomplete Set" << std::endl;
							m_incomplete.push_back(std::move(temp));
						}
						--total;
					}
				}
			}
		}
		if (!total) 
			checker = true;
		
		return checker;
	}
	

}