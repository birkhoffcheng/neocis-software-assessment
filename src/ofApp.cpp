#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	int i, j;
	ofSetWindowShape(410 * SCALE, 410 * SCALE);
	for (i = 0; i < NUM_POINTS; i++) {
		for (j = 0; j < NUM_POINTS; j++) {
			squares[i * NUM_POINTS + j].set(j * 20 * SCALE + 10 * SCALE, i * 20 * SCALE + 10 * SCALE, 10 * SCALE, 10 * SCALE);
			square_blue[i * NUM_POINTS + j] = false;
		}
	}
	circle_center_x = 0;
	circle_center_y = 0;
	blue_circle_radius = 0;
	inner_circle_radius = 0;
	outer_circle_radius = 0;
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
	ofSetColor(0, 0, 255);
	ofNoFill();
	ofDrawCircle(circle_center_x, circle_center_y, blue_circle_radius);
	ofSetColor(255, 0, 0);
	ofDrawCircle(circle_center_x, circle_center_y, inner_circle_radius);
	ofDrawCircle(circle_center_x, circle_center_y, outer_circle_radius);
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
	blue_circle_radius = distance(x, y, circle_center_x, circle_center_y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	circle_center_x = x;
	circle_center_y = y;
	blue_circle_radius = 0;
	inner_circle_radius = 0;
	outer_circle_radius = 0;
	for (int i = 0; i < NUM_POINTS * NUM_POINTS; i++) {
		square_blue[i] = false;
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	blue_circle_radius = distance(x, y, circle_center_x, circle_center_y);
	set_blue_squares();
	set_inner_circle();
	set_outer_circle();
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

void ofApp::set_blue_squares() {
	int i, j, center_x, center_y;
	for (i = 0; i < NUM_POINTS; i++) {
		for (j = 0; j < NUM_POINTS; j++) {
			center_x = squares[i * NUM_POINTS + j].x + 5 * SCALE;
			center_y = squares[i * NUM_POINTS + j].y + 5 * SCALE;
			if (abs(distance(circle_center_x, circle_center_y, center_x, center_y) - blue_circle_radius) <= 10.0 * SCALE)
				square_blue[i * NUM_POINTS + j] = true;
		}
	}
}

bool ofApp::radius_intersects_blue_squares(double radius) {
	double degree, radian;
	int x, y, i;
	for (degree = 0; degree < 360; degree += 2) {
		radian = degree * M_PI / 180;
		x = circle_center_x + radius * cos(radian);
		y = circle_center_y + radius * sin(radian);
		for (i = 0; i < NUM_POINTS * NUM_POINTS; i++) {
			if (square_blue[i] && squares[i].inside(x, y))
				return true;
		}
	}
	return false;
}

void ofApp::set_inner_circle() {
	double hi = blue_circle_radius, lo = 0, mid = blue_circle_radius;
	while (abs(hi - lo) > 0.1) {
		mid = (lo + hi) / 2;
		if (radius_intersects_blue_squares(mid))
			hi = mid;
		else
			lo = mid;
	}
	inner_circle_radius = mid;
}

void ofApp::set_outer_circle() {
	double lo = blue_circle_radius, hi = 410 * SCALE, mid = blue_circle_radius;
	while (abs(hi - lo) > 0.1) {
		mid = (lo + hi) / 2;
		if (radius_intersects_blue_squares(mid))
			lo = mid;
		else
			hi = mid;
	}
	outer_circle_radius = mid;
}
