#include "scene_story.h"

namespace finalproject {
	void Scene_Story::loadResources() {
		font.load(constants::kFontFile, constants::kFontSize);
	}

	Scene_Story::Scene_Story(const json &story_file) {
		file = story_file;
		for (auto& item : file["inventory"]) {
			inventory.push_back(InventoryItem(item["name"], item["desc"]));
		}

		loadResources();
	}


	void Scene_Story::update() {}

	void Scene_Story::draw() {
		bg.draw(0, 0);

	}

	void Scene_Story::processKey(int key) {
		for (auto& line : file["story"]) {
			std::cout << line << '\n';
		}
	}

}
