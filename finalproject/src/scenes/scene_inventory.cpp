#include "scene_inventory.h"

namespace finalproject {
	Scene_Inventory::Scene_Inventory(const std::vector<InventoryItem> &i) {
		bg.load("inventory_bg.png");
		inventory = i;
	}

	void Scene_Inventory::update() {

	}

	void Scene_Inventory::draw() {
		bg.draw(0, 0);
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
		}
	}

}