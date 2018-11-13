#pragma once

#include "ofMain.h"
#include "scenes/scenemanager.h"
#include <string>
#include <vector>

namespace finalproject {

	class Game : public ofBaseApp {
		public:
			void setup();
			void loadScenes();

			void update();
			void draw();

			void keyPressed(int key);
			void mousePressed(int x, int y, int button);
			void windowResized(int w, int h);
	};

} //namespace finalproject