#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	gui.setup();
	gui.add(lineWidth.setup("Width", 5, 4, 100, 200));
	gui.add(horizontal.setup("isHorizontal", true));
	gui.add(reverse.setup("isReverse", false));
	gui.add(move.setup("isMoving", false));
	gui.add(vel.setup("velocity", 0, -5, 5, 200));
	gui.add(reset.setup("Reset"));

	ofBackground(127, 0, 0);
	offset = 0;
	ofFill();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	offset += vel;
	if (offset >= -50) {
		offset -= lineWidth * (50 / lineWidth + 1);
	}
	else if (offset <= -150) {
		offset += lineWidth * (50 / lineWidth + 1);
	}
	if (reset) { offset = 0; }
	float basePos = -100 + offset;
	bool lineColor = reverse;
	if (horizontal) {
		while (basePos <= ofGetHeight())
		{
			if (lineColor) {
				ofSetColor(255);
			}
			else {
				ofSetColor(0);
			}
			ofDrawRectangle(0, basePos, ofGetWidth(), lineWidth / 2);
			basePos += lineWidth / 2;
			lineColor = !lineColor;
		}
	}
	else
	{
		while (basePos <= ofGetWidth())
		{
			if (lineColor) {
				ofSetColor(255);
			}
			else {
				ofSetColor(0);
			}
			ofDrawRectangle(basePos, 0, lineWidth / 2, ofGetHeight());
			basePos += lineWidth / 2;
			lineColor = !lineColor;
		}
		
	}

	gui.draw();
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

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
