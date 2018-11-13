#pragma once
#include "base.h"
namespace finalproject {

	class Scene_Title : public Scene {
		public:
			void update();
			void draw();
			void processKey(int key);
	};

} //namespace finalproject