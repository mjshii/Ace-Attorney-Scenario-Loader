#include "scenemanager.h"

namespace finalproject {
	SceneManager scenes;

	void SceneManager::add(ScenePtr scene) {
		scene_list.push_back(scene);
	}

	void SceneManager::replace(ScenePtr scene) {
		pop();
		scene_list.push_back(scene);
	}

	void SceneManager::pop() {
		scene_list.pop_back();
	}

	void SceneManager::update() {
		if (empty()) {
			return;
		}
		// update only the last scene
		scene_list.back()->update();
	}

	void SceneManager::draw() {
		ofSetColor(255);
		for (int i = 0; i < scene_list.size(); i++)	{
			scene_list[i]->draw();
		}
	}

	void SceneManager::processKey(int key) {
		// send mouse info to the last scene only
		scene_list.back()->processKey(key);
	}

	bool SceneManager::empty() {
		return scene_list.empty();
	}

	int SceneManager::size() {
		return scene_list.size();
	}

	void SceneManager::setData(std::string d) {
		data = d;
	}

	std::string SceneManager::getData() {
		return std::string();
	}

}