#include "ofApp.h"
#include "game_constants.h"

using namespace finalproject::constants;

namespace finalproject {
	//--------------------------------------------------------------
	// Setup
	//
	void Game::setup() {
		ofSetWindowTitle("Game");

		loadFonts();
		loadSounds();
		loadImages();
		loadScenes();
	}

	void Game::loadFonts() {
		font.load(kFontFile, kFontSize);
	}

	void Game::loadSounds() {
	}

	void Game::loadImages() {
	}

	void Game::loadScenes()	{
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
	void Game::keyPressed(int key) {
		if (scenes.empty()) {
			return;
		}

		// send mouse info to the last scene only
		scenes.back()->processKey(key);
	}

	//--------------------------------------------------------------
	// Mouse Click
	//
	void Game::mousePressed(int x, int y, int button) {

	}

	//--------------------------------------------------------------
	// Window Resize
	//
	void Game::windowResized(int w, int h) {

	}

} //namespace finalproject