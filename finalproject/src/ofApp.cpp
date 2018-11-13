#include "ofApp.h"
namespace finalproject {
	//--------------------------------------------------------------
	// Setup
	//
	void Game::setup() {
		ofSetWindowTitle("Game");
		scenes.push_back(ScenePtr(new Scene_Title()));
	}

	//--------------------------------------------------------------
	// Update
	//
	void Game::update() {
		if (scenes.empty()) {
			ofExit();
			return;
		}

		// update only the last scene
		scenes.back()->update();
		if (scenes.back()->shouldDispose()) {
			scenes.pop_back();
			update();
		}
	}

	//--------------------------------------------------------------
	// Draw
	//
	void Game::draw() {
		for (auto scene : scenes) {
			scene->draw();
		}
	}

	//--------------------------------------------------------------
	// Keypress
	//
	void Game::keyReleased(int key) {
		if (scenes.empty()) {
			return;
		}

		// send mouse info to the last scene only
		scenes.back()->processKey(key);
	}

	//--------------------------------------------------------------
	// Mouse Click
	//
	void Game::mouseReleased(int x, int y, int button) {

	}

	//--------------------------------------------------------------
	// Window Resize
	//
	void Game::windowResized(int w, int h) {

	}

} //namespace finalproject