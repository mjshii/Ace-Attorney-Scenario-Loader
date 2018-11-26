#include "ofMain.h"
#include "ofApp.h"
#include "game_constants.h"

#define DISPLAY_MODE OF_WINDOW // Can be OF_WINDOW or OF_FULLSCREEN

using namespace finalproject;

int main() {
	ofSetupOpenGL(constants::kWindowWidth, constants::kWindowHeight, DISPLAY_MODE);
	ofSetFrameRate(15);

	ofRunApp(new Game());
}