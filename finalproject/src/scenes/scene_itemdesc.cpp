#include "scene_itemdesc.h"

namespace finalproject {
	Scene_ItemDesc::Scene_ItemDesc(int index, const std::vector<InventoryItem>& inv) {
		bg.load("image_desc.png");
		item.load(inv[index].name + ".png");
		font.load(constants::kFontFile, constants::kFontSize);

		inventory = inv;
		sel_index = index;
	}

	void Scene_ItemDesc::update() {}

	void Scene_ItemDesc::draw() {
		bg.draw(0, 0);
		item.draw(kImageX, kImageY);

		//TODO: draw item and description

		font.drawString(
			wordWrap(inventory[sel_index].desc, kTextWidth),
			kTextX,
			kTextY + font.getSize()
		);
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
		item.load(inventory[sel_index].name + ".png");
	}
}
