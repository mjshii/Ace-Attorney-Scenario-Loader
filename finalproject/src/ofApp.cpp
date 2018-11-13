#include "ofApp.h"

namespace finalproject {
	//--------------------------------------------------------------
	// Setup
	//
	void Game::setup() {
		ofSetWindowTitle("Game");
		loadScenes();
	}

	void Game::loadScenes()	{
		scenes.add(new Scene_Title());
	}

	//--------------------------------------------------------------
	// Update
	//
	void Game::update() {
		if (scenes.empty()) {
			ofExit();
		}
		scenes.update();
	}

	//--------------------------------------------------------------
	// Draw
	//
	void Game::draw() {
		scenes.draw();
	}

	//--------------------------------------------------------------
	// Keypress
	//
	void Game::keyPressed(int key) {
		scenes.processKey(key);
	}

	//--------------------------------------------------------------
	// Mouse Click
	//
	void Game::mousePressed(int x, int y, int button) {}

	//--------------------------------------------------------------
	// Window Resize
	//
	void Game::windowResized(int w, int h) {

	}

} //namespace finalproject