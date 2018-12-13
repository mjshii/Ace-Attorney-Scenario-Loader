#include "scene_inventory.h"
#include <algorithm>

namespace finalproject {

	Scene_Inventory::Scene_Inventory(const std::vector<InventoryItem>& i, bool present_ok) {
		bg.load(present_ok ? kPresentBG : kNormalBG);
		font.load(constants::kFontFile, constants::kFontSize);
		inventory = i;
		can_present = present_ok;
	}

	void Scene_Inventory::update() {}

	void Scene_Inventory::draw() {
		bg.draw(0, 0);
		drawItems();
		font.drawString(
			inventory[sel_index].name,
			kInputX + (kInputWidth - font.stringWidth(inventory[sel_index].name)) / 2,
			kInputY + (font.getLineHeight() + font.getDescenderHeight()/2)
		);
	}

	void Scene_Inventory::drawItems() {
		int start_i = (sel_index / kItemsPerPage) * kItemsPerPage;
		for (int i = start_i; i < std::min((int)inventory.size(), start_i + kRows * kCols); i++) {
			int adj_i = i % (kRows * kCols);
			item.load(inventory[i].image);
			item.draw(
				kItemX + (adj_i % kCols) * (kItemWidth + kItemXPad),
				kItemY + (adj_i / kCols) * (kItemHeight + kItemYPad),
				kItemWidth,
				kItemHeight
			);

			if (i == sel_index) {
				item.load(kSelectRect);
				item.draw(
					kItemX - kBorderWidth + (adj_i % kCols) * (kItemWidth + kItemXPad),
					kItemY - kBorderWidth + (adj_i / kCols) * (kItemHeight + kItemYPad)
				);
			}
		}
	}

	bool Scene_Inventory::pressedOK(int key) {
		return key == 'z' || key == OF_KEY_RETURN || key == ' ';
	}

	bool Scene_Inventory::pressedCancel(int key) {
		return key == 'x';
	}

	bool Scene_Inventory::pressedPresent(int key) {
		return key == 'd';
	}

	void Scene_Inventory::processKey(int key) {
		if (pressedCancel(key)) {
			scenes.pop();
			return;
		} else if (pressedOK(key)) {
			scenes.add(ScenePtr(new Scene_ItemDesc(sel_index, inventory, can_present)));
			return;
		} else if (pressedPresent(key)) {
			scenes.setData(inventory[sel_index].name);
			scenes.pop();
			return;
		}
		processScroll(key);
	}

	void Scene_Inventory::processScroll(int key) {
		switch (key) {
			case OF_KEY_RIGHT:
				sel_index++;
				break;

			case OF_KEY_LEFT:
				sel_index = (sel_index - 1 < 0) ? (inventory.size() - 1) : (sel_index - 1);
				break;

			case OF_KEY_UP:
				if (sel_index % (kRows * kCols) - kCols >= 0) {
					sel_index -= kCols;
				}
				break;

			case OF_KEY_DOWN:
				if (sel_index % (kRows * kCols) + kCols < kRows * kCols && sel_index + kCols < inventory.size()) {
					sel_index += kCols;
				}
				break;
		}
		sel_index %= inventory.size();
	}
}