#pragma once
#include "base.h"
#include "scenemanager.h"

namespace finalproject {

	class Scene_Controls : public Scene {
		ofImage bg;
		const std::string kControlsBG = "controls.png";

		public:
			Scene_Controls();

			void update();
			void draw();
			void processKey(int key);
	};

} //namespace finalproject