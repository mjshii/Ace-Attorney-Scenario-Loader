#include "scene_title.h"
#include <iostream>

namespace finalproject {

void Scene_Title::update() {
	std::cout << "updating\n";
}

void Scene_Title::draw() {
	ofSetColor(0);
	ofDrawRectangle(0, 0, 100, 100);
}

void Scene_Title::processKey(int key) {
	std::cout << "exiting\n";
	should_dispose = true;
}

} //namespace finalproject