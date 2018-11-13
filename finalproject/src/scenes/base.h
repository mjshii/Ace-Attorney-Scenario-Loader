#pragma once
#include "ofGraphics.h"

namespace finalproject {

	class Scene {
		public:
			virtual void update() = 0;
			virtual void draw() = 0;
	};

} //namespace finalproject