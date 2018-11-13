#include "scene_title.h"
#include <iostream>

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
	font.drawString(input, 166 + (739 - font.stringWidth(input)) / 2, 513 + font.getLineHeight() *0.6);
}

void Scene_Title::processKey(int key) {
	if (key != OF_KEY_RETURN) {
		input += (char)key;
		
	} else {
		should_dispose = true;
	}
}

} //namespace finalproject