#pragma once
#include <string>
#include <vector>
#include "ofMain.h"
#include "../inventory_item.h"
#include "../game_constants.h"

namespace finalproject {

	class Scene {
		protected:
			ofTrueTypeFont font;

		public:
			~Scene();
			virtual void update() = 0;
			virtual void draw() = 0;

			virtual void processKey(int key) = 0;
	};

} //namespace finalproject