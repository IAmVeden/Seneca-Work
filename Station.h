#ifndef SICT_STATION_H
#define SICT_STATION_H

#include <deque>
#include "ItemSet.h"
#include "Utilities.h"
#include "CustomerOrder.h"

namespace sict {



	class Station {

		std::deque<CustomerOrder> m_queue;
		ItemSet m_subObject;
		std::string m_name;

	public:

		Station(const std::string& str);
		void display(std::ostream& os) const;
		void fill(std::ostream& os);
		const std::string& getName() const;
		bool hasAnOrderToRelease() const;
		Station& operator--();
		Station& operator+=(CustomerOrder&& order);
		bool pop(CustomerOrder& ready);
		void validate(std::ostream& os) const;


		Station& operator=(const Station&) = delete;
		Station& operator=(Station&&) = delete;
		Station(const Station&) = delete;
		Station(Station&&) = delete;
	};



}



#endif