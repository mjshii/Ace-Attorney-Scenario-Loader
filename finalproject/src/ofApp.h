#pragma once
#include "ofMain.h"
#include "scenes/scenelist.h"
#include <stack>
#include <string>
#include <vector>
#include <memory>

// sp stands for "scene pointer"
using ScenePtr = std::shared_ptr<finalproject::Scene>;

namespace finalproject {

	class Game : public ofBaseApp {
		// Scene list
		std::vector<ScenePtr> scenes;

		// Resources
		ofTrueTypeFont font;

		public:
			void setup();
			void loadFonts();
			void loadSounds();
			void loadImages();
			void loadScenes();

			void update();
			void draw();

			void keyReleased(int key);
			void mouseReleased(int x, int y, int button);
			void windowResized(int w, int h);
		
	};

} //namespace finalproject