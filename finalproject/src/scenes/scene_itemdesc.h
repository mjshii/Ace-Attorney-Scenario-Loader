#pragma once
#include "base.h"
#include "scenemanager.h"

namespace finalproject {

	class Scene_ItemDesc : public Scene {
		std::vector<InventoryItem> inventory;
		std::string wrapped_type;
		std::string wrapped_desc;
		bool can_present = false;

		ofImage bg;
		ofImage item;

		int sel_index = 0;
		
		const int kImageX = 89;
		const int kImageY = 153;

		const int kNameX = 386;
		const int kNameY = 155;
		const int kNameWidth = 606;
		const int kNameHeight = 67;

		const int kTextX = 53;
		const int kTextY = 465;
		const int kTextWidth = 975;

		const int kTypeX = 398;
		const int kTypeY = 236;
		const int kTypeWidth = 583;

		bool pressedCancel(int key);
		bool pressedPresent(int key);
		void refreshItem();

	public:
		Scene_ItemDesc(int index, const std::vector<InventoryItem>& bag, bool present_ok = false);

		void update();
		void draw();
		void processKey(int key);
	};

} //namespace finalproject