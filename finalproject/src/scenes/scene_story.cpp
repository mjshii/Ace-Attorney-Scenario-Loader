#include "scene_story.h"

namespace finalproject {
	Scene_Story::Scene_Story(const json &story_file) {
		file = story_file;
		for (auto& item : file["inventory"]) {
			inventory.push_back(InventoryItem(
				item["name"],
				item.contains("type") ? item["type"] : "",
				item["desc"]
			));
		}
		loadResources();
		processKey(OF_KEY_RETURN); // kick off story
	}

	void Scene_Story::loadResources() {
		font.load(constants::kFontFile, constants::kFontSize);
		name_font.load(constants::kFontFile, constants::kFontSize - 5);
	}

	void Scene_Story::update() {
		if (shouldUpdate) {
			updateImages();
			updateTextbox();
			updateSounds();
			shouldUpdate = false;
		}

		// always update text
		if (!next_text.empty()) {
			current_text.push_back(next_text.front());
			next_text = next_text.substr(1, next_text.size() - 1);
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
			text_bg.load("text_bg.png");
		}

		if (data.contains("name")) {
			name_text = data["name"].get<std::string>();
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
		bg.draw(0, 0);
		sprite.draw(0, 0);
		overlay.draw(0, 0);

		if (scenes.size() == 1) {
			text_bg.draw(0, 0);

			if (data.contains("text")) {
				drawTextbox();
			}
		}
	}

	void Scene_Story::drawTextbox() {
		name_font.drawString(
			name_text,
			constants::kDialogueX,
			constants::kNameY + font.getSize()
		);

		font.drawString(
			current_text,
			constants::kDialogueX,
			constants::kDialogueY + font.getSize()
		);
	}

	bool Scene_Story::pressedOK(int key) {
		return key == OF_KEY_RETURN || key == ' ' || key == 'z';
	}

	bool Scene_Story::pressedCancel(int key) {
		return key == OF_KEY_ESC || key == 'x';
	}

	bool Scene_Story::validKey(int key) {
		return pressedOK(key) || pressedCancel(key) || 
			key == OF_KEY_LEFT || key == OF_KEY_RIGHT || key == OF_KEY_UP || key == OF_KEY_DOWN;
	}

	void Scene_Story::processKey(int key) {
		if (!validKey(key)) {
			return;
		}

		if (pressedCancel(key)) {
			scenes.add(ScenePtr(new Scene_Inventory(inventory)));

		} else {
			// fast forward text
			if (!next_text.empty()) {
				current_text += next_text;
				next_text.clear();
				return;
			}
			readNextLine(key);
		}
	}

	void Scene_Story::readNextLine(int key) {
		if (testimony_index < 0) {
			readStoryLine();
		} else {
			readTestimonyLine(key);
		}
	}

	void Scene_Story::readStoryLine() {
		std::cout << "Reading story" << std::endl;
		try {
			current_index++;
			data = file["story"].at(current_index);

			if (data.contains("testimony")) {
				readTestimonyLine(0);
				return;
			}

			if (data.contains("text")) {
				current_text = "";
				next_text = wordWrap(data["text"].get<std::string>(), kDialogueWidth);
			}

			shouldUpdate = true;

		} catch (std::out_of_range) {
			bgm_channel.stop();
			scenes.replace(ScenePtr(new Scene_Title()));
		}
	}

	void Scene_Story::readTestimonyLine(int key) {
		std::cout << "Reading testimony" << std::endl;
		try {
			updateTestimonyIndex(key);

			std::cout << "Index " << testimony_index << std::endl;
			data = file["story"][current_index]["testimony"]["statements"][testimony_index];

			if (data.contains("text")) {
				current_text = wordWrap(data["text"].get<std::string>(), kDialogueWidth);
			} else {
				testimony_index = -1;
				readTestimonyLine(0);
			}

			shouldUpdate = true;

		} catch (std::out_of_range) {
			std::cout << "Out of range." << std::endl;
			testimony_index = -1;
			readStoryLine();
		}
	}

	void Scene_Story::updateTestimonyIndex(int key) {
		if (key == OF_KEY_LEFT) {
			if (testimony_index <= 0) {
				return;
			}
			testimony_index--;
		} else {
			testimony_index++;
		}
	}

}
