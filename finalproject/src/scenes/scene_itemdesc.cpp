#include "scene_itemdesc.h"

namespace finalproject {
	Scene_ItemDesc::Scene_ItemDesc(const std::vector<InventoryItem>& i) {
		bg.load("image_desc.png");
		font.load(constants::kFontFile, constants::kFontSize);
		inventory = i;
	}

	void Scene_ItemDesc::update() {}

	void Scene_ItemDesc::draw() {
		bg.draw(0, 0);

		//TODO: draw item and description
	}

	bool Scene_ItemDesc::pressedCancel(int key) {
		return key == 'x' || key == OF_KEY_ESC;
	}

	void Scene_ItemDesc::processKey(int key) {
		if (pressedCancel(key)) {
			scenes.pop();
			return;
		}

		switch (key) {
			case OF_KEY_RIGHT:	sel_index++;
				break;
			case OF_KEY_LEFT:	sel_index--;
				break;
		}
		sel_index %= inventory.size();
	}
}
