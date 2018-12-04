#pragma once
#include "base.h"
#include "scenemanager.h"
#include "../libs/json.hpp"

using nlohmann::json;

namespace finalproject {

	class Scene_Story : public Scene {
		json file;
		json data;
		int current_index = -1;
		std::string name_text;
		std::string current_text;
		std::string next_text;

		std::vector<InventoryItem> inventory;

		bool shouldUpdate = true;

		ofImage bg;
		ofImage sprite;
		ofImage overlay;
		ofImage text_bg;

		ofSoundPlayer bgm_channel;
		ofTrueTypeFont name_font;

		void loadResources();
		std::string wordWrap(std::string sentence, int width);
		void updateImages();
		void updateTextbox();
		void updateSounds();

		void drawTextbox();
		bool validKey(int key);
		bool pressedOK(int key);
		bool pressedCancel(int key);

		void readNextLine();

	public:
		Scene_Story(const json &story_file);

		void update();
		void draw();
		void processKey(int key);
	};

} //namespace finalproject