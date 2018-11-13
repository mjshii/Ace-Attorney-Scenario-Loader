#include "scene_title.h"
#include <iostream>
#include <fstream>

namespace finalproject {

Scene_Title::Scene_Title() {
	font.load(constants::kFontFile, kFontSize);
	bg.load("title.png");
}

void Scene_Title::update() {

}

void Scene_Title::draw() {
	ofSetColor(255);
	bg.draw(0, 0);
	ofSetColor(0);
	font.drawString(input, 166 + (739 - font.stringWidth(input)) / 2, 513 + font.getLineHeight() *0.6);
}

void Scene_Title::processKey(int key) {
	switch (key) {
		case OF_KEY_BACKSPACE:
			if (!input.empty()) {
				input.pop_back();
			}
			return;

		case OF_KEY_RETURN:
			submitScenario();
			return;

		default:
			if (isValidCharacter(key)) {
				input += (char)key;
			}
	}
}

bool Scene_Title::isValidCharacter(int key) {
	return (key >= 'A' && key <= 'Z') || 
		(key >= 'a' && key <= 'z') ||
		(key >= '0' && key <= '9') || 
		(key == '-' || key == '_' || key == '.');
}

void Scene_Title::submitScenario() {
	std::ofstream file("test.txt", std::ios::trunc);
	file << "Test to find the directory location";
	file.close();
	scenes.pop();
}

} //namespace finalproject