#include "ofMain.h"
#include "ofApp.h"

#define DISPLAY_MODE OF_WINDOW // Can be OF_WINDOW or OF_FULLSCREEN

using namespace finalproject;

int main() {
	ofSetupOpenGL(1280, 720, DISPLAY_MODE); // setup the GL context
	ofSetFrameRate(30);

	// this kicks off the running of my app
	ofRunApp(new Game());
}