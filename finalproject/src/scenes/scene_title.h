#pragma once
#include "base.h"
namespace finalproject {

	class Scene_Title : public Scene {
		const std::string kFontFile = constants::kFontFile;
		const int kFontSize = 45;

		std::string input;

		public:
			Scene_Title();

			void update();
			void draw();
			void processKey(int key);

			void submitScenario();
	};

} //namespace finalproject