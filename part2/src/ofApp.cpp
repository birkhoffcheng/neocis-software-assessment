#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	int i, j;
	ofSetWindowShape(410 * SCALE, 410 * SCALE + 90 * SCALE);
	for (i = 0; i < NUM_POINTS; i++) {
		for (j = 0; j < NUM_POINTS; j++) {
			squares[i * NUM_POINTS + j].set(j * 20 * SCALE + 10 * SCALE, i * 20 * SCALE + 10 * SCALE, 10 * SCALE, 10 * SCALE);
			square_blue[i * NUM_POINTS + j] = false;
		}
	}
	circle_center_x = 0;
	circle_center_y = 0;
	blue_circle_radius = 0;
	generate_button.set(10 * SCALE, 410 * SCALE, 390 * SCALE, 80 * SCALE);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofFill();
	for (int i = 0; i < NUM_POINTS * NUM_POINTS; i++) {
		if (square_blue[i]) {
			ofSetColor(0, 0, 255);
		}
		else {
			ofSetColor(255, 255, 255);
		}
		ofDrawRectangle(squares[i]);
	}
	ofSetColor(0, 127, 127);
	ofDrawRectangle(generate_button);
	ofSetColor(0, 0, 0);
	ofDrawBitmapString("Generate", 175 * SCALE, 450 * SCALE);
	ofSetColor(0, 0, 255);
	ofNoFill();
	ofDrawCircle(circle_center_x, circle_center_y, blue_circle_radius);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (y > 400 * SCALE || x > 400 * SCALE) {
		if (generate_button.inside(x, y)) {
			generate_circle();
		}
		return;
	}
	int i = (y - 5 * SCALE) / (20 * SCALE);
	int j = (x - 5 * SCALE) / (20 * SCALE);
	if (squares[i * NUM_POINTS + j].inside(x, y))
		square_blue[i * NUM_POINTS + j] = !square_blue[i * NUM_POINTS + j];
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

double ofApp::distance(int x1, int y1, int x2, int y2) {
	return sqrt(pow(abs(x1 - x2), 2) + pow(abs(y1 - y2), 2));
}

void ofApp::generate_circle() {
	int i, second_last_blue = 0, last_blue = 0;
	double Suu = 0, Suv = 0, Suuu = 0, Suvv = 0, Svv = 0, Svvv = 0, Svuu = 0, average_x = 0, average_y = 0, total_blues = 0, u, v, uc, vc, rhs1, rhs2, determinant;
	for (i = 0; i < NUM_POINTS * NUM_POINTS; i++) {
		if (square_blue[i]) {
			total_blues += 1;
			average_x += squares[i].x;
			average_y += squares[i].y;
			second_last_blue = last_blue;
			last_blue = i;
		}
	}
	average_x /= total_blues;
	average_y /= total_blues;

	if (total_blues == 2) {
		circle_center_x = average_x + 5 * SCALE;
		circle_center_y = average_y + 5 * SCALE;
		blue_circle_radius = distance(squares[second_last_blue].x, squares[second_last_blue].y, squares[last_blue].x, squares[last_blue].y) / 2.0;
		return;
	}

	for (i = 0; i < NUM_POINTS * NUM_POINTS; i++) {
		if (square_blue[i]) {
			u = squares[i].x - average_x;
			v = squares[i].y - average_y;
			Suu += u * u;
			Suv += u * v;
			Suuu += u * u * u;
			Suvv += u * v * v;
			Svv += v * v;
			Svvv += v * v * v;
			Svuu += v * u * u;
		}
	}

	rhs1 = (Suuu + Suvv) / 2.0;
	rhs2 = (Svvv + Svuu) / 2.0;
	determinant = Suu * Svv - Suv * Suv;
	if (determinant != 0) {
		uc = (Svv * rhs1 - Suv * rhs2) / determinant;
		vc = (Suu * rhs2 - Suv * rhs1) / determinant;
	}
	else {
		uc = 0;
		vc = 0;
	}

	circle_center_x = uc + average_x + 5 * SCALE;
	circle_center_y = vc + average_y + 5 * SCALE;
	blue_circle_radius = sqrt(uc * uc + vc * vc + (Suu + Svv) / total_blues);
}
