#pragma once
#include "ofxGui.h"
#include "ofMain.h"
#include <cmath>
#define NUM_POINTS 20
#define SCALE 1

class ofApp : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofRectangle squares[NUM_POINTS * NUM_POINTS];
		bool square_blue[NUM_POINTS * NUM_POINTS];
		int circle_center_x;
		int circle_center_y;
		double blue_circle_radius;
		double inner_circle_radius;
		double outer_circle_radius;
		double distance(int x1, int y1, int x2, int y2);
		void set_blue_squares();
		bool radius_intersects_blue_squares(double radius);
		void set_inner_circle();
		void set_outer_circle();
};
