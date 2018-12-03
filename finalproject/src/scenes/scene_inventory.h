#pragma once
#include "base.h"
#include "scenemanager.h"
#include "../libs/json.hpp"

using nlohmann::json;

namespace finalproject {

	class Scene_Inventory : public Scene {
		std::vector<InventoryItem> inventory;

		ofImage bg;
		ofImage item;

		const int kRows = 2;
		const int kCols = 4;

		bool pressedOK(int key);
		bool pressedCancel(int key);

	public:
		Scene_Inventory(const std::vector<InventoryItem> &i);

		void update();
		void draw();
		void processKey(int key);
	};

} //namespace finalproject