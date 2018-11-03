#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(24);
	defaultMovie.load("default_sharp2.mp4");
	defaultMovie.setLoopState(OF_LOOP_NONE);
	firstImg.loadImage("first.jpg");

	defaultOrigin.set((-704 + 80)*ofGetWidth() / 1440, (-705 + 45)*ofGetHeight() / 810);
	firstOrigin = defaultOrigin;

	for (int i = 0; i < 18; i++) {
		string filename = "movies/ball" + to_string(i + 1) + "_new3.mp4";
		balls[i].load(filename);
		balls[i].setLoopState(OF_LOOP_NONE);
	}

	firstPos[0].set(26.1111, 90.3704);
	firstPos[1].set(23.8889, 86.7901);
	firstPos[2].set(26.0417, 83.8272);
	firstPos[3].set(26.0417, 77.1605);
	firstPos[4].set(23.6806, 74.1975);
	firstPos[5].set(25.9028, 70.8642);
	firstPos[6].set(23.9583, 67.037);
	firstPos[7].set(25.8333, 62.963);
	firstPos[8].set(25.7639, 56.6667);
	firstPos[9].set(23.125, 53.4568);
	firstPos[10].set(25.3472, 50.3704);
	firstPos[11].set(25.625, 43.8272);
	firstPos[12].set(25.4167, 37.284);
	firstPos[13].set(25.3472, 30.7407);
	firstPos[14].set(25.2083, 24.321);
	firstPos[15].set(23.6111, 20.2469);
	firstPos[16].set(25.1389, 15.9259);
	firstPos[17].set(25.2778, 9.38272);
	for (int i = 0; i < 18; i++) {
		firstPos[i].x *= ((float)ofGetWidth() / 100);
		firstPos[i].y *= ((float)ofGetHeight() / 100);
	}

	started = false;
	ended = false;
	repeating = false;
	selected = -1;
	repeatCount = 0;

	ofHideCursor();
	ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update() {
	if (started) {
		if (selected == -1){
			defaultMovie.update();
			if (defaultMovie.getIsMovieDone()) {
				ended = true;
			}
		}
		else {
			balls[selected].update();
			if (balls[selected].getIsMovieDone()) {
				ended = true;
			}
		}
	}
	
	if(repeating){
		repeatCount++;
		cout << "repeating " << repeatCount << endl;
		if(repeatCount >= 16){
			started = false;
			selected = -1;
			if(repeatCount >= 32){
				repeating = false;
				repeatCount = 0;
				ended = false;
				cout << "started=" << started << ", ended=" << ended << ", repeating=" << repeating << ", selected=" << selected << endl;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSetColor(255);
	if (started){
		if (selected == -1) {
			defaultMovie.draw(0, 0, ofGetWidth(), ofGetHeight());
		}
		else {
			balls[selected].draw(0, 0, ofGetWidth(), ofGetHeight());
		}
	}
	else {
		firstImg.draw(firstOrigin, firstImg.getWidth()*ofGetWidth() / 1440, firstImg.getHeight()*ofGetHeight() / 810);
		ofSetColor(255, 125);
		ofNoFill();
		ofSetLineWidth(1.5);
		ofDrawCircle(ofGetWidth() / 2 + 25, ofGetHeight() / 2, 18);
		ofDrawCircle(ofGetWidth() / 2 + 25, ofGetHeight() / 2, 30);
	}
	if(repeating){
		ofFill();
		ofSetColor(0,abs(256 - abs(256 - repeatCount * 16)));
		ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (!started) {
		ofVec2f center;
		center.set(ofGetWidth() / 2 + 25, ofGetHeight() / 2);
		ofVec2f now;
		now.set(x - 10, y);

		if (defaultOrigin.x + x - mouseClicked.x < 0) {
			firstOrigin.set(defaultOrigin.x + x - mouseClicked.x, defaultOrigin.y + y - mouseClicked.y);
		}
		if (selected != -1 && center.distance(now) < 25 && !started) {
			started = true;
			balls[selected].play();
			cout << "GO" << endl;
			cout << "started=" << started << ", ended=" << ended << ", repeating=" << repeating << ", selected=" << selected << endl;
		}
		//cout << center.distance(now) << endl;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (!started) {
		mouseClicked.set(x - 10, y);
		for (int i = 0; i < 18; i++) {
			float min = 20;
			if (firstPos[i].distance(mouseClicked) < min) {
				selected = i;
				min = firstPos[i].distance(mouseClicked);
			}
		}
		cout << "select " << selected << endl;
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	ofVec2f Released;
	Released.set(x - 10, y);

	if (!started) {
		selected = -1;

		if (Released.distance(mouseClicked) < 15) {
			if (selected == -1) {
				started = true;
				defaultMovie.play();
			}
		}
		firstOrigin = defaultOrigin;
	}
	else if(ended)
	{
		defaultOrigin.set((-704 + 80)*ofGetWidth() / 1440, (-705 + 45)*ofGetHeight() / 810);
		firstOrigin = defaultOrigin;
		ended = false;
		repeating = true;
	}
	cout << "started=" << started << ", ended=" << ended << ", repeating=" << repeating << ", selected=" << selected << endl;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
