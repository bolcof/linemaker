#pragma once

#include "ofMain.h"
#include "Candle.h"

class ofApp : public ofBaseApp{

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofVec2f offset;

		bool fukase,saori,love,nakajin;
		int fukase_alpha,saori_alpha,love_alpha,nakajin_alpha;

		int al,fl;
		float allScale;

		bool candle_f[8];
		bool candle_fix[8];

		bool candle_all;

		ofImage back, trim, fukaseImg, saoriImg, LOVEImg, nakajinImg, light;
		Candle myCandle[NUM];

		int sec,presec;
		bool idle;
		bool calibMode;
		bool PinMode;

		ofPoint point[4];
		bool pointSelected[4];
};
