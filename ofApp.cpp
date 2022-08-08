
#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 30, true, true, true);
	this->word = "01234567890123456789";
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	int size = 30;
	
	for(int z = -330; z <= 330; z += size) {

		for (int x = -330; x <= 330; x += size) {

			for (int y = -330; y <= 330; y += size) {

				auto radius = ofMap(ofNoise(x * 0.008, y * 0.008, z * 0.001 + ofGetFrameNum() * 0.05), 0, 1, 50, 430);
				auto param = abs(radius - glm::length(glm::vec2(x, y)));
				int word_index = ofMap(ofNoise(x * 0.008, y * 0.008, z * 0.001 + ofGetFrameNum() * 0.05), 0, 1, 0, this->word.size());

				if (param < 50) {

					ofPushMatrix();
					ofTranslate(x - size * 0.5, y + size * 0.5, z);

					auto rad = atan2(y, x);
					ofRotate(rad * RAD_TO_DEG + 90);

					ofPath chara_path = this->font.getCharacterAsPoints(this->word[word_index], true, false);
					vector<ofPolyline> outline = chara_path.getOutline();

					ofFill();
					ofSetColor(0);

					ofBeginShape();
					for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

						ofNextContour(true);

						auto vertices = outline[outline_index].getVertices();
						ofVertices(vertices);
					}
					ofEndShape(true);

					ofNoFill();
					ofSetColor(255);

					ofBeginShape();
					for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

						ofNextContour(true);

						auto vertices = outline[outline_index].getVertices();
						ofVertices(vertices);
					}
					ofEndShape(true);

					ofPopMatrix();
				}
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}