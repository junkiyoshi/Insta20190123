#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	int radius_base = 45;
	int radius_span = 4;
	int deg_span = 24;
	int span = 144;
	for (int x = span * 0.5; x < ofGetWidth(); x += span) {

		for (int y = span * 0.5; y < ofGetHeight(); y += span) {

			for (int deg = 0; deg < 360; deg += deg_span) {

				glm::vec2 noise_point = glm::vec2(
					x + radius_span * cos((deg + deg_span * 0.5) * DEG_TO_RAD),
					y + radius_span * sin((deg + deg_span * 0.5) * DEG_TO_RAD));
				int noise_value = ofMap(ofNoise(noise_point.x * 0.01 + ofGetFrameNum() * 0.015, noise_point.y * 0.01 + ofGetFrameNum() * 0.015), 0, 1, -5, 5);

				int radius_start = noise_value > 0 ? radius_base : radius_base + noise_value * radius_span;
				int radius_end = noise_value > 0 ? radius_base + noise_value * radius_span : radius_base;

				for (int radius = radius_start; radius <= radius_end; radius += radius_span) {

					vector<glm::vec2> vertices;
					for (int tmp_deg = deg; tmp_deg <= deg + deg_span; tmp_deg++) {

						vertices.push_back(glm::vec2(x + (radius + radius_span * 0.5) * cos(tmp_deg * DEG_TO_RAD), y + (radius + radius_span * 0.5) * sin(tmp_deg * DEG_TO_RAD)));
					}
					for (int tmp_deg = deg + deg_span; tmp_deg >= deg; tmp_deg--) {

						vertices.push_back(glm::vec2(x + (radius - radius_span * 0.5) * cos(tmp_deg * DEG_TO_RAD), y + (radius - radius_span * 0.5) * sin(tmp_deg * DEG_TO_RAD)));
					}

					ofBeginShape();
					ofVertices(vertices);
					ofEndShape(true);
				}
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}