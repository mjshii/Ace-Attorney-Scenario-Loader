#pragma once
#include <string>

namespace finalproject {

	struct InventoryItem {
		std::string name;
		std::string desc;

		InventoryItem(std::string n, std::string d) : name(n), desc(d) {};
	};

}