#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofFile prop;
    prop.open("prop.txt", ofFile::ReadOnly);
    
    string str, filename;
    int count = 0;
    if (prop.fail())
    {
        std::cout << "prop.txt:error" << std::endl;
    }
    while (getline(prop, str))
    {
        cout << count << ":" << str << endl;
        switch (count)
        {
            case 0:
                HOST = str;
                break;
            case 1:
                HOST2 = str;
                break;
            case 2:
                filename = str;
                break;
            default:
                std::cout << count << ":[" << str << "]" << std::endl;
                break;
        }
        count++;
    }
    
    ofFile points;
    points.open("points.txt", ofFile::ReadOnly);
    count = 0;
    if (points.fail())
    {
        std::cout << "points.txt:error" << std::endl;
    }
    while (getline(points, str))
    {
        if (count <= 7) {
            if (count % 2 == 0) {
                p[count / 2].x = stof(str);
            }
            else {
                p[count / 2].y = stof(str);
            }
        }
        else {
            if (count == 8) {
                center.x = stof(str);
            }
            else if (count == 9) {
                center.y = stof(str);
            }
        }
        if (count >= 10) { cout << "anything wrong" << endl; }
        count++;
    }
    
    
    sender.setup(HOST, PORT);
    sender2.setup(HOST2, PORT);
    
    video.load(filename);
    video.setPaused(true);
    video.setLoopState(OF_LOOP_NORMAL);
    
    is_setting = true;
    selected_seek = false;
    
    sendMessage(video.getPosition(), video.isPaused());
    
    //mesh
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    
    ofSetFrameRate(30);
    
    selected_pos = -1;
    std::cout << "setup" << endl;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (!selected_seek) {
        video.update();
        if (video.getPosition() == 0) {
            sendMessage(video.getPosition(), video.isPaused());
        }
    }
    cursorPos = ofVec2f(ofGetWidth()*0.15 + ofGetWidth()*0.7*video.getPosition(), ofGetHeight()*0.9);
    
    
    mesh.clear();
    mesh.addVertex(center);
    mesh.addVertex(p[0]);
    mesh.addVertex(p[1]);
    mesh.addVertex(p[2]);
    mesh.addVertex(p[3]);
    mesh.addVertex(p[0]);
    
    mesh.addTexCoord(ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2));
    mesh.addTexCoord(ofVec2f(0, 0));
    mesh.addTexCoord(ofVec2f(0, ofGetHeight()));
    mesh.addTexCoord(ofVec2f(ofGetWidth(), ofGetHeight()));
    mesh.addTexCoord(ofVec2f(ofGetWidth(), 0));
    mesh.addTexCoord(ofVec2f(0, 0));
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofSetColor(255);
    video.draw(0, 0, ofGetWidth(), ofGetHeight());
    screen.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    ofBackground(0);
    
    ofSetColor(255);
    screen.bind();
    mesh.draw();
    screen.unbind();
    
    if (is_setting) {
        
        //about mesh
        ofSetLineWidth(1);
        ofSetColor(255, 150, 150);
        ofNoFill();
        ofDrawCircle(center, 10);
        ofFill();
        for (int i = 0; i < 4; i++) {
            ofDrawCircle(p[i], 10);
        }
        ofSetColor(255);
        mesh.drawWireframe();
        ofDrawBitmapString(ofToString(ofGetFrameRate()) + "fps", 20, 40);
        
        //seek
        ofSetColor(0, 180);
        ofDrawRectangle(ofGetWidth()*0.1, ofGetHeight()*0.85, ofGetWidth()*0.8, ofGetHeight()*0.1);
        ofSetColor(255, 180);
        ofSetLineWidth(10);
        ofDrawLine(ofGetWidth()*0.15, ofGetHeight()*0.9, ofGetWidth()*0.85, ofGetHeight()*0.9);
        ofDrawCircle(cursorPos, 15);
        ofDrawBitmapString("It's sender", 20, 20);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    if (key == 'p') {
        if (video.isPaused()) {
            video.setPaused(false);
        }
        else {
            video.setPaused(true);
        }
        sendMessage(video.getPosition(), video.isPaused());
    }
    else if (key == 's') {
        is_setting = !is_setting;
        sendMessage(video.getPosition(), video.isPaused());
    }else if (key == 'w') {
        
        ofFile outputfile;
        outputfile.open("points_output.txt", ofFile::WriteOnly);
        outputfile << p[0].x << "\n";
        outputfile << p[0].y << "\n";
        outputfile << p[1].x << "\n";
        outputfile << p[1].y << "\n";
        outputfile << p[2].x << "\n";
        outputfile << p[2].y << "\n";
        outputfile << p[3].x << "\n";
        outputfile << p[3].y << "\n";
        outputfile << center.x << "\n";
        outputfile << center.y;
        outputfile.close();
        cout << "write done." << endl;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    if (selected_seek) {
        if (x >= ofGetWidth()*0.15 && x <= ofGetWidth()*0.85) {
            cursorPos.x = x;
            video.setPosition(((float)cursorPos.x - ofGetWidth()*0.15) / (ofGetWidth()*0.7));
        }
        else if (x < ofGetWidth()*0.15) {
            cursorPos.x = ofGetWidth()*0.15;
            video.setPosition(0.0);
        }
        else if (x > ofGetWidth()*0.85) {
            cursorPos.x = ofGetWidth()*0.85;
            video.setPosition(0.9999);
        }
        else {
            cout << "error" << endl;
        }
        sendMessage(video.getPosition(), video.isPaused());
    }
    
    if (is_setting) {
        if (selected_pos == 99) {
            center.x = x;
            center.y = y;
        }
        else if (selected_pos != -1) {
            p[selected_pos].x = x;
            p[selected_pos].y = y;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    video.setPaused(true);
    for (int i = 0; i < 4; i++) {
        if (p[i].distance(ofVec3f(x, y, 0)) < 8) {
            selected_pos = i;
            break;
        }
    }
    if (selected_pos == -1 && center.distance(ofVec3f(x, y, 0)) < 8) {
        selected_pos = 99;
    }
    
    if (is_setting) {
        cursorPos = ofVec2f(ofGetWidth()*0.15 + ofGetWidth()*0.7*video.getPosition(), ofGetHeight()*0.9);
        cout << cursorPos.distance(ofVec2f(x, y)) << endl;
        if (cursorPos.distance(ofVec2f(x, y)) < 16) {
            selected_seek = true;
            video.setPaused(true);
        }
    }
    
    sendMessage(video.getPosition(), video.isPaused());
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    selected_seek = false;
    
    if (selected_pos != 99 && selected_pos != -1) {
        center.x = (p[0].x + p[1].x + p[2].x + p[3].x) / 4;
        center.y = (p[0].y + p[1].y + p[2].y + p[3].y) / 4;
    }
    selected_pos = -1;
    mesh.clear();
    
    sendMessage(video.getPosition(), video.isPaused());
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

void ofApp::sendMessage(float videoPos, bool isPaused) {
    ofxOscMessage m;
    
    m.setAddress("/state/isPaused");
    m.addBoolArg(video.isPaused());
    
    sender.sendMessage(m, false);
    sender2.sendMessage(m, false);
    
    m.clear();
    
    m.setAddress("/state/position");
    m.addFloatArg(video.getPosition());
    
    sender.sendMessage(m, false);
    sender2.sendMessage(m, false);
}

