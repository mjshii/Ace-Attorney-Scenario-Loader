#pragma once
#include "base.h"
#include "scenemanager.h"

namespace finalproject {

	class Scene_ItemDesc : public Scene {
		std::vector<InventoryItem> inventory;

		ofImage bg;
		ofImage item;

		int sel_index = 0;
		
		const int kImageX = 89;
		const int kImageY = 153;

		const int kTextX = 53;
		const int kTextY = 465;
		const int kTextWidth = 975;
		
		bool pressedCancel(int key);

	public:
		Scene_ItemDesc(int index, const std::vector<InventoryItem>& bag);

		void update();
		void draw();
		void processKey(int key);
	};

} //namespace finalproject