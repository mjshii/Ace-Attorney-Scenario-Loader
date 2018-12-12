#pragma once
#include <string>

namespace finalproject {

	struct InventoryItem {
		std::string name;
		std::string type;
		std::string desc;

		InventoryItem(std::string n, std::string t, ::string d) : name(n), type(t), desc(d) {};
		bool operator==(const InventoryItem& item) { return name == item.name; }
	};

}