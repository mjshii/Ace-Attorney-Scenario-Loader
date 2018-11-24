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
		float scale = ((float)ofGetWindowWidth()) / constants::kWindowWidth;
		ofScale(scale, scale, scale);
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
		float adjusted_h = ((float) w) * constants::kWindowHeight / constants::kWindowWidth;
		ofSetWindowShape(w, adjusted_h);
	}

} //namespace finalproject