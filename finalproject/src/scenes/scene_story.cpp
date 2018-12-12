#include "scene_story.h"

namespace finalproject {
	Scene_Story::Scene_Story(const json &story_file) {
		file = story_file;
		for (auto& item : file["inventory"]) {
			addItem(item);
		}
		loadResources();
		processKey(kDefaultKey); // kick off story
	}

	void Scene_Story::loadResources() {
		font.load(constants::kFontFile, constants::kFontSize);
		name_font.load(constants::kFontFile, constants::kFontSize - 5);
		testimony_arrows.load("testimony_arrows.png");
	}

	void Scene_Story::update() {
		updateData();
		updateText();

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
			}
			else {
				sprite.clear();
			}
		}

		if (data.contains("overlay")) {
			if (data["overlay"].size() > 0) {
				overlay.load(data["overlay"].get<std::string>());
			}
			else {
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
		if (testimony_index >= 0 && press_index < 0) {
			testimony_arrows.draw(0, 0);
		}
	}

	void Scene_Story::drawTextbox() {
		name_font.drawString(
			data.contains("add item") ? "" : name_text,
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
		return key == 'x';
	}

	bool Scene_Story::validKey(int key) {
		return pressedOK(key) || pressedCancel(key) ||
			(canPresent() && (key == OF_KEY_LEFT || key == OF_KEY_RIGHT || key == OF_KEY_DOWN));
	}

	void Scene_Story::processKey(int key) {
		if (!validKey(key)) {
			return;
		}

		if (pressedCancel(key)) {
			scenes.add(ScenePtr(new Scene_Inventory(inventory, canPresent())));

		}
		else {
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
		try {
			if (testimony_index < 0) {
				readStoryLine();
			}
			else {
				readTestimonyLine(key);
			}
			shouldUpdate = true;
		}
		catch (std::exception) {
			bgm_channel.stop();
			scenes.replace(ScenePtr(new Scene_Title()));
		}
	}

	void Scene_Story::readStoryLine() {
		story_index++;
		data = file["story"].at(story_index);
		if (data.contains("testimony")) {
			readTestimonyLine(kDefaultKey);
			return;
		}

		if (data.contains("add item")) {
			addItem(data["add item"]);
		}
		if (data.contains("remove item")) {
			removeItem(data["remove item"].get<std::string>());
		}
		if (data.contains("text")) {
			current_text.clear();
			next_text = wordWrap(data["text"].get<std::string>(), kDialogueWidth);
		}
	}

	bool Scene_Story::addItem(json item) {
		InventoryItem new_item(
			item["name"],
			item.contains("image") ? item["image"] : item["name"],
			item.contains("type") ? item["type"] : "",
			item["desc"]
		);
		if (std::find(inventory.begin(), inventory.end(), new_item) == inventory.end()) {
			inventory.push_back(new_item);
			return true;
		}
		return false;
	}

	bool Scene_Story::removeItem(std::string name) {
		InventoryItem item(name, "", "");
		if (std::find(inventory.begin(), inventory.end(), item) == inventory.end()) {
			return false;
		}
		inventory.erase(std::remove(inventory.begin(), inventory.end(), item), inventory.end());
		return true;
	}

	void Scene_Story::readPressLine(int key) {
		press_index++;
		data = file["story"][story_index]["testimony"]["statements"][testimony_index]["press"][press_index];

		if ((data.contains("add item") && !addItem(data["add item"])) ||
			(data.contains("remove item") && !removeItem(data["remove item"].get<std::string>()))) {
			readPressLine(key);
			return;
		}
		if (data.contains("text")) {
			next_text = wordWrap(data["text"].get<std::string>(), kDialogueWidth);
			current_text.clear();
		} else {
			press_index = -1;
			readTestimonyLine(kDefaultKey);
		}
	}

	void Scene_Story::readPresentLine(int key) {
		present_index++;
		std::cout << present_index << std::endl;

		data = file["story"][story_index]["testimony"]["statements"][testimony_index];
		if (data.contains("present " + last_data)) {
			data = data["present " + last_data][present_index];
		} else {
			data = file["story"][story_index]["default present"][present_index];
		}

		std::cout << data << std::endl;

		if (data.contains("text")) {
			next_text = wordWrap(data["text"].get<std::string>(), kDialogueWidth);
			current_text.clear();
		} else {
			present_index = -1;
			readTestimonyLine(kDefaultKey);
		}
	}

	void Scene_Story::readStatementLine(int key) {
		updateTestimonyIndex(key);
		data = file["story"][story_index]["testimony"]["statements"][testimony_index];

		if (data.contains("condition")) {
			int check_press = data["condition"].get<int>() - 1;
			if (!(press_flags.size() > check_press && press_flags[check_press])) {
				readStatementLine(key);
				return;
			}
		}
		if (data.contains("text")) {
			current_text = wordWrap(data["text"].get<std::string>(), kDialogueWidth);
		} else {
			testimony_index = -1;
			readTestimonyLine(kDefaultKey);
		}
	}

	void Scene_Story::updatePressFlags() {
		if (press_flags.size() < testimony_index + 1) {
			press_flags.resize(testimony_index + 1);
		}
		press_flags[testimony_index] = true;
	}

	void Scene_Story::updateData() {
		if (!scenes.getData().empty() && last_data != scenes.getData()) {
			std::cout << "updating data" << std::endl;
			// update item presenting
			last_data = scenes.getData();
			scenes.setData("");

			readPresentLine(kDefaultKey);
			shouldUpdate = true;
		}
	}

	void Scene_Story::updateText() {
		// append the next character
		if (!next_text.empty()) {
			current_text.push_back(next_text.front());
			next_text = next_text.substr(1, next_text.size() - 1);
		}
	}

	void Scene_Story::readTestimonyLine(int key) {
		if (press_index >= 0 || key == OF_KEY_DOWN) {
			updatePressFlags();
			readPressLine(key);
		} else if (present_index >= 0) {
			readPresentLine(key);
		} else {
			readStatementLine(key);
		}
	}

	void Scene_Story::updateTestimonyIndex(int key) {
		if (key == OF_KEY_LEFT && testimony_index > 0) {
			testimony_index--;
		} else if (pressedOK(key) || key == OF_KEY_RIGHT) {
			testimony_index++;
		}
	}

	bool Scene_Story::canPresent() {
		return testimony_index >= 0 && press_index < 0 && present_index < 0;
	}

}
