#include "scene_itemdesc.h"

namespace finalproject {
	Scene_ItemDesc::Scene_ItemDesc(int index, const std::vector<InventoryItem>& bag, bool present_ok) {
		can_present = present_ok;
		font.load(constants::kFontFile, constants::kFontSize);
		bg.load(present_ok ? kPresentBG : kNormalBG);
		inventory = bag;
		sel_index = index;

		refreshItem();
	}

	void Scene_ItemDesc::refreshItem() {
		item.load(inventory[sel_index].image);
		wrapped_desc = wordWrap(inventory[sel_index].desc, kTextWidth);
		wrapped_type = wordWrap(inventory[sel_index].type, kTypeWidth);
	}

	void Scene_ItemDesc::update() {}

	void Scene_ItemDesc::draw() {
		bg.draw(0, 0);
		item.draw(kImageX, kImageY);
		font.drawString(
			inventory[sel_index].image,
			kNameX + (kNameWidth - font.stringWidth(inventory[sel_index].name)) / 2,
			kNameY + (font.getLineHeight() + font.getDescenderHeight() / 2)
		);
		
		ofSetColor(0);
		font.drawString(wrapped_type, kTypeX, kTypeY + font.getSize());
		ofSetColor(255);
		font.drawString(wrapped_desc, kTextX, kTextY + font.getSize());
	}

	bool Scene_ItemDesc::pressedCancel(int key) {
		return key == 'x';
	}

	bool Scene_ItemDesc::pressedPresent(int key) {
		return key == OF_KEY_UP || key == 'd';
	}

	void Scene_ItemDesc::processKey(int key) {
		if (pressedCancel(key)) {
			scenes.pop();
			return;
		} else if (can_present && pressedPresent(key)) {
			scenes.setData(inventory[sel_index].name);
			scenes.pop();
			scenes.pop();
			return;
		}
		processScroll(key);
	}

	void Scene_ItemDesc::processScroll(int key) {
		switch (key) {
		case OF_KEY_RIGHT:	sel_index++;
			break;
		case OF_KEY_LEFT:	sel_index--;
			break;
		}

		if (sel_index < 0) {
			sel_index += inventory.size();
		} else if (sel_index >= inventory.size()) {
			sel_index -= inventory.size();
		}
		refreshItem();
	}
}
