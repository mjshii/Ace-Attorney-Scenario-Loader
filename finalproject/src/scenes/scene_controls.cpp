#include "scene_controls.h"
#include <iostream>
#include <fstream>
#include "../libs/json.hpp"

namespace finalproject {

	Scene_Controls::Scene_Controls() {
		bg.load(kControlsBG);
	}

	void Scene_Controls::update() {}

	void Scene_Controls::draw() {
		ofSetColor(255);
		bg.draw(0, 0);
	}

	void Scene_Controls::processKey(int key) {
		if (key == OF_KEY_CONTROL) {
			scenes.pop();
		}
	}

} //namespace finalproject