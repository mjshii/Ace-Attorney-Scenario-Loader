#pragma once
#include <string>

namespace finalproject {

	struct InventoryItem {
		std::string name;
		std::string image;
		std::string type;
		std::string desc;

		InventoryItem(std::string n, std::string t, ::string d) : name(n), image(n), type(t), desc(d) {};
		InventoryItem(std::string n, std::string i, std::string t, ::string d) : name(n), image(i), type(t), desc(d)  {};
		bool operator==(const InventoryItem& item) { return name == item.name; }
	};

}