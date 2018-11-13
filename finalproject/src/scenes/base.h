#pragma once
#include "ofGraphics.h"

namespace finalproject {

	class Scene {
		protected:
			bool should_dispose = false;

		public:
			virtual bool shouldDispose();

			virtual void update() = 0;
			virtual void draw() = 0;

			virtual void processKey(int key) = 0;
	};

} //namespace finalproject