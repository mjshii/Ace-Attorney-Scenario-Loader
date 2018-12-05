#include "scene_inventory.h"
#include <algorithm>

namespace finalproject {
	Scene_Inventory::Scene_Inventory(const std::vector<InventoryItem> &i) {
		bg.load("inventory_bg.png");
		font.load(constants::kFontFile, constants::kFontSize);
		inventory = i;
	}

	void Scene_Inventory::update() {

	}

	void Scene_Inventory::draw() {
		bg.draw(0, 0);

		for (int i = sel_index; i < std::min((int)inventory.size(), kRows*kCols); i++) {
			item.load(inventory[i].name + ".png");
			item.draw(
				kItemX + (i % kCols) * (item.getWidth() + kItemXPad),
				kItemY + (i / kCols) * (item.getHeight() + kItemYPad)
			);

			if (i == sel_index) {
				item.load("rect.png");
				item.draw(
					kItemX - kBorderWidth + (i % kCols) * (item.getWidth() + kItemXPad - kBorderWidth*2),
					kItemY - kBorderWidth + (i / kCols) * (item.getHeight() + kItemYPad - kBorderWidth*2)
				);
			}
		}

		font.drawString(
			inventory[sel_index].name,
			kInputX + (kInputWidth - font.stringWidth(inventory[sel_index].name)) / 2,
			kInputY + (font.getLineHeight() + font.getDescenderHeight()/2)
		);
	}

	bool Scene_Inventory::pressedOK(int key) {
		return key == 'z' || key == OF_KEY_RETURN;
	}

	bool Scene_Inventory::pressedCancel(int key) {
		return key == 'x' || key == OF_KEY_ESC;
	}

	void Scene_Inventory::processKey(int key) {
		if (pressedCancel(key)) {
			scenes.pop();
			return;
		}

		switch (key) {
			case OF_KEY_RIGHT:	sel_index++;
				break;
			case OF_KEY_LEFT:	sel_index--;
				break;
			case OF_KEY_UP:		sel_index -= kCols;
				break;
			case OF_KEY_DOWN:	sel_index += kCols;
				break;
		}
		
		sel_index %= inventory.size();
	}

}