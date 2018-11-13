#include "ofMain.h"
#include "ofApp.h"

#define DISPLAY_MODE OF_WINDOW // Can be OF_WINDOW or OF_FULLSCREEN

using namespace finalproject;

int main() {
	ofSetupOpenGL(1280, 720, DISPLAY_MODE);
	ofSetFrameRate(30);

	ofRunApp(new Game());
}