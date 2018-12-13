#include "scene_story.h"
#include "../libs/cryptor.hpp"

namespace finalproject {
	Scene_Story::Scene_Story(const json &story_file, std::string filename) {
		file = story_file;
		save_name = filename + kSaveSuffix;
		for (auto& item : file["inventory"]) {
			addItem(item);
		}
		loadResources();
		processKey(kDefaultKey); // kick off story
	}

	void Scene_Story::loadResources() {
		font.load(constants::kFontFile, constants::kFontSize);
		name_font.load(constants::kFontFile, constants::kFontSize - kFontDecrement);
		testimony_arrows.load(kArrowsImage);
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
		updateBackground();
		updateSprite();
		updateOverlay();
		updateShout();
	}

	void Scene_Story::draw() {
		bg.draw(0, 0);
		sprite.draw(0, 0);
		overlay.draw(0, 0);
		shout.draw(0, 0);

		if (scenes.size() == 1) {
			text_bg.draw(0, 0);

			if (data.contains("text")) {
				drawTextbox();
			}
		}
		if (canPresent()) {
			testimony_arrows.draw(0, 0);
		}
	}

	void Scene_Story::drawTextbox() {
		name_font.drawString(
			shouldShowName() ? name_text : "",
			kDialogueX,
			kNameY + font.getSize()
		);

		font.drawString(
			current_text,
			kDialogueX,
			kDialogueY + font.getSize()
		);
	}

	bool Scene_Story::pressedOK(int key) {
		return key == OF_KEY_RETURN || key == ' ' || key == 'z';
	}

	bool Scene_Story::pressedCancel(int key) {
		return key == 'x';
	}

	void Scene_Story::processSaveLoad(int key) {
		if (data.contains("shout")) {
			return;
		}
		switch (key) {
			case 's': saveData();
				break;
			case 'l': loadData();
				break;
		}
	}

	bool Scene_Story::validKey(int key) {
		return pressedOK(key) || (canSave() && pressedCancel(key)) ||
			(canPresent() && (key == OF_KEY_LEFT || key == OF_KEY_RIGHT || key == OF_KEY_DOWN));
	}

	void Scene_Story::processKey(int key) {
		processSaveLoad(key);

		if (!validKey(key)) {
			return;
		} else if (pressedCancel(key)) {
			scenes.add(ScenePtr(new Scene_Inventory(inventory, canPresent())));
		} else {
			shout.clear();

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
			if (testimony_index < 0 && after_index < 0) {
				readStoryLine();
			} else {
				readTestimonyLine(key);
			}
			shouldUpdate = true;
		} catch (std::exception) {
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
			removeItem(data["remove item"]);
		}
		if (data.contains("text")) {
			current_text.clear();
			next_text = wordWrap(data["text"].get<std::string>(), kDialogueWidth);
		}
	}

	bool Scene_Story::addItem(json item) {
		InventoryItem new_item(
			item["name"],
			item.contains("image") ? item["image"] : (item["name"].get<std::string>() + ".png"),
			item.contains("type") ? item["type"] : "",
			item["desc"]
		);
		if (std::find(inventory.begin(), inventory.end(), new_item) == inventory.end()) {
			inventory.push_back(new_item);
			return true;
		}
		return false;
	}

	bool Scene_Story::removeItem(json list) {
		bool success = false;
		for (auto& i : list) {
			InventoryItem item(i.get<std::string>(), "", "");
			if (std::find(inventory.begin(), inventory.end(), item) == inventory.end()) {
				continue;
			}
			inventory.erase(std::remove(inventory.begin(), inventory.end(), item), inventory.end());
			success = true;
		}
		return success;
	}

	void Scene_Story::readPressLine(int key) {
		press_index++;
		data = file["story"][story_index]["testimony"]["statements"][testimony_index]["press"][press_index];

		if (data.contains("add item") && !addItem(data["add item"])) {
			readPressLine(key);
			return;
		}
		if (data.contains("text")) {
			next_text = wordWrap(data["text"].get<std::string>(), kDialogueWidth);
			current_text.clear();
		} else if (canSave()) {
			press_index = -1;
			readNextLine(key);
		}
	}

	void Scene_Story::readPresentLine(int key) {
		present_index++;
		data = file["story"][story_index]["testimony"]["statements"][testimony_index];
		if (data.contains("present " + last_data)) {
			data = data["present " + last_data][present_index];
		} else {
			data = file["story"][story_index]["testimony"]["default present"][present_index];
		}

		if (data.contains("text")) {
			next_text = wordWrap(data["text"].get<std::string>(), kDialogueWidth);
			current_text.clear();
		} else if (canSave()) {
			present_index = -1;
			last_data = "";
			if (data.contains("cmd") && data["cmd"].get<std::string>() == "exit") {
				exitTestimony();
				readNextLine(key);
			} else {
				testimony_index--;
				readTestimonyLine(key);
			}
		}
	}

	void Scene_Story::exitTestimony() {
		testimony_index = -1;
		press_index = -1;
		present_index = -1;
		after_index = -1;

		last_data = "";
		scenes.setData("");
		seen_after = false;
		press_flags.clear();
	}

	void Scene_Story::readAfterLine(int key) {
		after_index++;
		data = file["story"][story_index]["testimony"][seen_after ? "short afterword" : "afterword"][after_index];

		if (data.contains("text")) {
			next_text = wordWrap(data["text"].get<std::string>(), kDialogueWidth);
			current_text.clear();
		} else if (canSave()) {
			seen_after = true;
			after_index = -1;
			readStatementLine(key);
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
		} else if (canSave()) {
			testimony_index = -1;
			readAfterLine(key);
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
		} else if (after_index >= 0) {
			readAfterLine(key);
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
		return canSave() && testimony_index >= 0 && press_index < 0 && present_index < 0;
	}

	bool Scene_Story::canSave() {
		return !data.contains("shout");
	}

	bool Scene_Story::shouldShowName() {
		return !(data.contains("add item") || 
			data.contains("remove item"));
	}

	// Stretch goal - save files
	void Scene_Story::saveData() {
		json save;

		// save text
		save["current_text"] = current_text;
		save["next_text"] = next_text;
		save["name_text"] = name_text;

		// save indexes
		save["story_index"] = story_index;
		save["testimony_index"] = testimony_index;
		save["press_index"] = press_index;
		save["present_index"] = present_index;
		save["after_index"] = after_index;

		// save flags
		save["press_flags"] = press_flags;
		save["seen_after"] = seen_after;

		// save currently displayed images
		save["bg"] = resources.contains("bg") ? resources["bg"].get<std::string>() : "";
		save["image"] = resources.contains("image") ? resources["image"].get<std::string>() : "";
		save["overlay"] = resources.contains("overlay") ? resources["overlay"].get<std::string>() : "";

		// save current bgm
		save["bgm"] = resources.contains("bgm") ? resources["bgm"].get<std::string>() : "";

		// save inventory
		json json_bag;
		for (auto& i : inventory) {
			json_bag.push_back({
				{"name", i.name},
				{"image", i.image},
				{"type", i.type},
				{"desc", i.desc}
			});
		}
		save["inventory"] = json_bag;

		// dump data
		std::string save_data = save.dump();
		cryptor::set_key(kEncryptionKey);
		ofstream file(save_name, std::ios::trunc);
		file << cryptor::encrypt(save_data);
		file.close();
	}

	void Scene_Story::loadData() {
		std::string loaded_data;
		ifstream file(save_name);
		std::getline(file, loaded_data);
		file.close();

		// decrypt
		cryptor::set_key(kEncryptionKey);
		loaded_data = cryptor::decrypt(loaded_data);
		json load = json::parse(loaded_data);

		// load text
		current_text = load["current_text"].get<std::string>();
		next_text = load["next_text"].get<std::string>();
		name_text = load["name_text"].get<std::string>();

		// load indexes
		story_index = load["story_index"];
		testimony_index = load["testimony_index"];
		press_index = load["press_index"];
		present_index = load["present_index"];
		after_index = load["after_index"];

		// load flags
		press_flags.clear();
		for (auto& i : load["press_flags"]) {
			press_flags.push_back(i.get<bool>());
		}
		seen_after = load["seen_after"];

		// load images
		resources["bg"] = load["bg"];
		resources["image"] = load["image"];
		resources["overlay"] = load["overlay"];
		bg.load(resources["bg"].get<std::string>());
		sprite.load(resources["image"].get<std::string>());
		overlay.load(resources["overlay"].get<std::string>());

		// load music
		resources["overlay"] = load["bgm"];
		bgm_channel.load(resources["bgm"].get<std::string>());
		bgm_channel.setLoop(true);
		bgm_channel.play();

		// load inventory
		inventory.clear();
		for (auto& item : load["inventory"]) {
			addItem(item);
		}
	}

	void Scene_Story::updateBackground() {
		if (data.contains("bg")) {
			bg.load(data["bg"].get<std::string>());
			resources["bg"] = data["bg"];
		}
	}

	void Scene_Story::updateSprite() {
		if (data.contains("image")) {
			if (data["image"].size() > 0) {
				sprite.load(data["image"].get<std::string>());
				resources["image"] = data["image"];
			} else {
				sprite.clear();
			}
		}
	}

	void Scene_Story::updateOverlay() {
		if (data.contains("overlay")) {
			if (data["overlay"].size() > 0) {
				overlay.load(data["overlay"].get<std::string>());
				resources["overlay"] = data["overlay"];
			} else {
				overlay.clear();
			}
		}
	}

	void Scene_Story::updateShout() {
		if (data.contains("shout")) {
			shout.load(data["shout"].get<std::string>());
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
			resources["bgm"] = data["bgm"];
		}
		if (data.contains("sfx")) {
			sfx_channel.load(data["sfx"].get<std::string>());
			sfx_channel.play();
		}
	}
}
