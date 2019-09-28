#ifndef SICT_LINEMANAGER_H
#define SICT_LINEMANAGER_H

#include <vector>
#include <deque>
#include <algorithm>
#include "Station.h"
#include "CustomerOrder.h"


namespace sict {

	class LineManager {
		std::vector<size_t> m_assemble;
		std::vector<Station*> m_stations;
		size_t m_first = 0;
		size_t m_last = 0;
		std::vector<size_t> m_next;
		std::deque<CustomerOrder> m_finished;
		std::deque<CustomerOrder> m_toBeFilled;
		std::deque<CustomerOrder> m_incomplete;

	public:

		LineManager(std::vector<Station*>& station, std::vector<size_t>& nextwards, std::vector<CustomerOrder>& customers, size_t starting, std::ostream& os);
		void display(std::ostream& os) const;
		bool run(std::ostream& os);


	};




}




#endif
