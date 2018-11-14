#pragma once
#include "base.h"
#include "scenemanager.h"

namespace finalproject {

	class Scene_Title : public Scene {
		const std::string kFontFile = constants::kFontFile;
		const int kFontSize = 45;

		const int kInputX = 166;
		const int kInputY = 513;
		const int kInputWidth = 739;
		const int kInputHeight = 63;

		std::string input;

		public:
			Scene_Title();

			void update();
			void draw();
			void processKey(int key);
			bool isValidCharacter(int key);

			void submitScenario();
	};

} //namespace finalproject