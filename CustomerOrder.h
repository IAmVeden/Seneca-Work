#ifndef SICT_CUSTOMERORDER_H
#define SICT_CUSTOMERORDER_H

#include <string>
#include "ItemSet.h"
#include "Utilities.h"

namespace sict {

	class CustomerOrder {

		struct ItemInfo {
			std::string m_mName;
			unsigned int m_mSerial = 0;
			bool m_mFillStatus = false;
		};

		std::string m_customerName;
		std::string m_productName;
		ItemInfo* m_stock = nullptr;
		size_t m_count = 0;
		Utilities utility;

	public:

		CustomerOrder() {};
		CustomerOrder(const std::string str);
		~CustomerOrder();
		CustomerOrder(CustomerOrder&& mov);
		CustomerOrder& operator=(CustomerOrder&& mov);
		void fillItem(ItemSet& item, std::ostream& os);
		bool isFilled() const;
		bool isItemFilled(const std::string& item) const;
		std::string getNameProduct() const;
		void display(std::ostream& os, bool showDetail = false) const;

		CustomerOrder(CustomerOrder&) = delete;
		CustomerOrder& operator=(CustomerOrder&) = delete;

	};





}


#endif
