#include "scene_title.h"
#include <iostream>
#include <fstream>
#include "../libs/json.hpp"

namespace finalproject {

	Scene_Title::Scene_Title() {
		font.load(constants::kFontFile, kFontSize);
		bg.load("title.png");
	}

	void Scene_Title::update() {}

	void Scene_Title::draw() {
		ofSetColor(255);
		bg.draw(0, 0);
		ofSetColor(0);
		font.drawString(
			input,
			kInputX + (kInputWidth - font.stringWidth(input)) / 2,
			kInputY + kInputHeight + font.getDescenderHeight()
		);
	}

	void Scene_Title::processKey(int key) {
		if (input == "Bad file!") {
			input.clear();
			return;
		}

		if (!input.empty()) {
			switch (key) {
				case OF_KEY_BACKSPACE: input.pop_back();
					return;
				case OF_KEY_RETURN: submitScenario();
					return;
			}
		}
		if (isValidCharacter(key)) {
			input += (char)key;
		}
	}

	bool Scene_Title::isValidCharacter(int key) {
		return (key >= 'A' && key <= 'Z') || 
			(key >= 'a' && key <= 'z') ||
			(key >= '0' && key <= '9') || 
			(key == '-' || key == '_' || key == '.' || key == '/');
	}

	void Scene_Title::submitScenario() {
		std::ifstream file(input);
		if (file.good()) {
			json story;
			file >> story;
			scenes.replace(new Scene_Story(story));
		} else {
			input = "Bad file!";
		}
		file.close();
	}

} //namespace finalproject