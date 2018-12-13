#pragma once
#include "base.h"
#include "scenemanager.h"

namespace finalproject {

	class Scene_Title : public Scene {
		const int kInputX = 166;
		const int kInputY = 513;
		const int kInputWidth = 739;
		const int kInputHeight = 63;
		const std::string kBadText = "Bad file!";

		std::string input;
		ofImage bg;

		public:
			Scene_Title();

			void update();
			void draw();
			void processKey(int key);
			bool isValidCharacter(int key);

			void submitScenario();
	};

} //namespace finalproject