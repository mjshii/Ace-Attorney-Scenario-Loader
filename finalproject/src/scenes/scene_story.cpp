#include "scene_story.h"

namespace finalproject {
	Scene_Story::Scene_Story(const json &story_file) {
		file = story_file;
		for (auto& item : file["inventory"]) {
			inventory.push_back(InventoryItem(item["name"], item["desc"]));
		}

		loadResources();
	}

	void Scene_Story::loadResources() {
		font.load(constants::kFontFile, constants::kFontSize);
	}

	void Scene_Story::update() {
		if (shouldUpdate) {
			json data = file["story"].at(current_index);
			
			text_bg.clear();

			if (data.contains("bg")) {
				bg.load(data["bg"].get<std::string>());
			}
			if (data.contains("bgm")) {

			}
			if (data.contains("text")) {
				text_bg.load("text_bg.png");
			}

			shouldUpdate = false;
		}
	}

	void Scene_Story::draw() {
		ofSetColor(255);
		bg.draw(0, 0);
		text_bg.draw(0, 0);
	}

	void Scene_Story::processKey(int key) {
		try {
			current_index++;
			file["story"].at(current_index); //check that access is available
			shouldUpdate = true;

		} catch (std::out_of_range) {
			scenes.replace(new Scene_Title());
		}
	}

}
