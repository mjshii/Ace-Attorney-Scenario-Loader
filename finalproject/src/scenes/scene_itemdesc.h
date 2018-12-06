#pragma once
#include "base.h"
#include "scenemanager.h"

namespace finalproject {

	class Scene_ItemDesc : public Scene {
		std::vector<InventoryItem> inventory;

		ofImage bg;
		ofImage item;

		int sel_index = 0;
		
		bool pressedCancel(int key);

	public:
		Scene_ItemDesc(const std::vector<InventoryItem> &i);

		void update();
		void draw();
		void processKey(int key);
	};

} //namespace finalproject