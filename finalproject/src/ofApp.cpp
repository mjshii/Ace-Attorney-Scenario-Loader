#include "ofApp.h"
namespace finalproject {
	//--------------------------------------------------------------
	void Game::setup() {
		ofSetWindowTitle("Game");
		scenes.push(sp(new Scene_Title()));
	}

	//--------------------------------------------------------------
	void Game::update() {
		scenes.top()->update();

	}

	//--------------------------------------------------------------
	void Game::draw() {
		scenes.top()->draw();
	}

	//--------------------------------------------------------------
	void Game::keyPressed(int key) {

	}

	//--------------------------------------------------------------
	void Game::keyReleased(int key) {

	}

	//--------------------------------------------------------------
	void Game::mouseMoved(int x, int y) {

	}

	//--------------------------------------------------------------
	void Game::mouseDragged(int x, int y, int button) {

	}

	//--------------------------------------------------------------
	void Game::mousePressed(int x, int y, int button) {

	}

	//--------------------------------------------------------------
	void Game::mouseReleased(int x, int y, int button) {

	}

	//--------------------------------------------------------------
	void Game::mouseEntered(int x, int y) {

	}

	//--------------------------------------------------------------
	void Game::mouseExited(int x, int y) {

	}

	//--------------------------------------------------------------
	void Game::windowResized(int w, int h) {

	}

	//--------------------------------------------------------------
	void Game::gotMessage(ofMessage msg) {

	}

	//--------------------------------------------------------------
	void Game::dragEvent(ofDragInfo dragInfo) {

	}

} //namespace finalproject