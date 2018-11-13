#pragma once
#include "ofMain.h"
#include "scenes/scenelist.h"
#include <stack>
#include <string>
#include <vector>
#include <memory>

// sp stands for "scene pointer"
using sp = std::unique_ptr<finalproject::Scene>;

namespace finalproject {

	class Game : public ofBaseApp {
		std::stack<sp> scenes;

		public:
			void setup();
			void update();
			void draw();

			void keyPressed(int key);
			void keyReleased(int key);
			void mouseMoved(int x, int y );
			void mouseDragged(int x, int y, int button);
			void mousePressed(int x, int y, int button);
			void mouseReleased(int x, int y, int button);
			void mouseEntered(int x, int y);
			void mouseExited(int x, int y);
			void windowResized(int w, int h);
			void dragEvent(ofDragInfo dragInfo);
			void gotMessage(ofMessage msg);
		
	};

} //namespace finalproject