#pragma once
#include "base.h"
#include "scenemanager.h"
#include "../libs/json.hpp"

using nlohmann::json;

namespace finalproject {

	class Scene_Story : public Scene {
		json file;
		json data;
		int current_index = 0;

		std::vector<InventoryItem> inventory;

		bool shouldUpdate = true;

		ofImage bg;
		ofImage sprite;
		ofImage overlay;
		ofImage text_bg;

		ofSoundPlayer bgm_channel;

		void loadResources();
		void updateImages();
		void updateTextbox();
		void updateSounds();

	public:
		Scene_Story(const json &story_file);

		void update();
		void draw();
		void processKey(int key);
	};

} //namespace finalproject