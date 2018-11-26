#pragma once
#include "base.h"
#include "scenemanager.h"
#include "../libs/json.hpp"

using nlohmann::json;

namespace finalproject {

	class Scene_Story : public Scene {
		std::string file;
		json story;

	public:
		Scene_Story(std::string file_name);

		void update();
		void draw();
		void processKey(int key);
	};

} //namespace finalproject