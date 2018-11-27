#include "scene_story.h"

namespace finalproject {
	Scene_Story::Scene_Story(const json &story_file) {
		file = story_file;
		data = file["story"].at(current_index);

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
			updateImages();
			updateTextbox();
			updateSounds();
			shouldUpdate = false;
		}
	}

	void Scene_Story::updateImages() {
		if (data.contains("bg")) {
			bg.load(data["bg"].get<std::string>());
		}
		if (data.contains("image")) {
			if (data["image"].size() > 0) {
				sprite.load(data["image"].get<std::string>());
			} else {
				sprite.clear();
			}
		}
		if (data.contains("overlay")) {
			if (data["overlay"].size() > 0) {
				overlay.load(data["overlay"].get<std::string>());
			} else {
				overlay.clear();
			}
		}
	}

	void Scene_Story::updateTextbox() {
		if (data.contains("text")) {
			std::cout << data["text"] << std::endl;
			text_bg.load("text_bg.png");
		} else {
			text_bg.clear();
		}
	}

	void Scene_Story::updateSounds() {
		if (data.contains("bgm")) {
			bgm_channel.load(data["bgm"].get<std::string>());
			bgm_channel.setLoop(true);
			bgm_channel.play();
		}
	}

	void Scene_Story::draw() {
		ofSetColor(255);
		bg.draw(0, 0);
		sprite.draw(0, 0);
		overlay.draw(0, 0);
		text_bg.draw(0, 0);
	}

	void Scene_Story::processKey(int key) {
		try {
			current_index++;
			data = file["story"].at(current_index); //check that access is available
			shouldUpdate = true;

		} catch (std::out_of_range) {
			scenes.replace(new Scene_Title());
		}
	}

}
