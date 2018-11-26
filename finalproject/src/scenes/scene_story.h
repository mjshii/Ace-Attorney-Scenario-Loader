#pragma once
#include "base.h"
#include "scenemanager.h"
#include "../libs/json.hpp"

using nlohmann::json;

namespace finalproject {

	class Scene_Story : public Scene {
		json file;
		std::vector<InventoryItem> inventory;

	public:
		Scene_Story(const json &story_file);

		void update();
		void draw();
		void processKey(int key);
	};

} //namespace finalproject