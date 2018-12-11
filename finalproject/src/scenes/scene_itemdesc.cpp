#include "scene_itemdesc.h"

namespace finalproject {
	Scene_ItemDesc::Scene_ItemDesc(int index, const std::vector<InventoryItem>& inv) {
		font.load(constants::kFontFile, constants::kFontSize);
		bg.load("image_desc.png");
		inventory = inv;
		sel_index = index;

		refreshItem();
	}

	void Scene_ItemDesc::refreshItem() {
		item.load(inventory[sel_index].name + ".png");
		wrapped_desc = wordWrap(inventory[sel_index].desc, kTextWidth);
		wrapped_type = wordWrap(inventory[sel_index].type, kTypeWidth);
	}

	void Scene_ItemDesc::update() {}

	void Scene_ItemDesc::draw() {
		bg.draw(0, 0);
		item.draw(kImageX, kImageY);

		font.drawString(
			inventory[sel_index].name,
			kNameX + (kNameWidth - font.stringWidth(inventory[sel_index].name)) / 2,
			kNameY + (font.getLineHeight() + font.getDescenderHeight() / 2)
		);

		font.drawString(wrapped_desc, kTextX, kTextY + font.getSize());

		ofSetColor(0);
		font.drawString(wrapped_type, kTypeX, kTypeY + font.getSize());
		ofSetColor(255);
	}

	bool Scene_ItemDesc::pressedCancel(int key) {
		return key == 'x' || key == OF_KEY_ESC;
	}

	bool Scene_ItemDesc::pressedPresent(int key) {
		return key == 'd';
	}

	void Scene_ItemDesc::processKey(int key) {
		if (pressedCancel(key)) {
			scenes.pop();
			return;
		} else if (pressedPresent(key)) {
			scenes.setData(inventory[sel_index].name);
			scenes.pop();
			scenes.pop();
			return;
		}

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
