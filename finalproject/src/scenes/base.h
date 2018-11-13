#pragma once
#include "ofGraphics.h"

namespace finalproject {

	class Scene {
		bool should_dispose = false;

		public:
			virtual void update() = 0;
			virtual void draw() = 0;
			virtual bool shouldDispose();
	};

} //namespace finalproject