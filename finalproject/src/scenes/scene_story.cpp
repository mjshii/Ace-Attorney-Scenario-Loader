#include "scene_story.h"

namespace finalproject {

	Scene_Story::Scene_Story(const json &story_file) {
		file = story_file;
		for (auto& item : file["inventory"]) {
			inventory.push_back(InventoryItem(item["name"], item["desc"]));
		}
	}

	void Scene_Story::update() {}

	void Scene_Story::draw() {

	}

	void Scene_Story::processKey(int key) {
		for (auto& line : file["story"]) {
			std::cout << line << '\n';
		}
	}

}
