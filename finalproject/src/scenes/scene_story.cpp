#include "scene_story.h"

namespace finalproject {
	Scene_Story::Scene_Story(const json &story_file) {
		file = story_file;
		for (auto& item : file["inventory"]) {
			inventory.push_back(InventoryItem(item["name"], item["desc"]));
		}
		loadResources();
		processKey(0); // kick off story
	}

	void Scene_Story::loadResources() {
		font.load(constants::kFontFile, constants::kFontSize);
	}

	std::string Scene_Story::wordWrap(std::string sentence, int width) {
		if (font.stringWidth(sentence) <= width) {
			return sentence;
		}
		return "needs wrapping";
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
		text_bg.clear();
		if (data.contains("text")) {
			std::cout << data["text"] << std::endl;
			text_bg.load("text_bg.png");
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

		if (data.contains("text")) {
			if (!next_text.empty()) {
				current_text.push_back(next_text.front());
				next_text = next_text.substr(1, next_text.size() - 1);
			}

			font.drawString(
				wordWrap(current_text, 1050),
				15,
				520 + constants::kFontSize
			);
		}
	}

	void Scene_Story::processKey(int key) {
		if (!next_text.empty()) {
			current_text += next_text;
			next_text.clear();
			return;
		}

		try {
			current_index++;
			data = file["story"].at(current_index); //check that access is available

			if (data.contains("text")) {
				current_text = "";
				next_text = data["text"].get<std::string>();
			}
			shouldUpdate = true;

		} catch (std::out_of_range) {
			scenes.replace(new Scene_Title());
		}
	}

}
