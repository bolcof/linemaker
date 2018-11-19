#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // listen on the given port
    cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup(PORT);
    
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
    
    
    video.load(filename);
    video.setPaused(true);
    video.setLoopState(OF_LOOP_NORMAL);
    
    current_msg_string = 0;
    
    //mesh
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    
    ofSetFrameRate(30);
    
    is_setting = true;
    selected = -1;
    std::cout << "setup" << endl;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    video.update();
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
    
    // hide old messages
    for (int i = 0; i < NUM_MSG_STRINGS; i++) {
        if (timers[i] < ofGetElapsedTimef()) {
            msg_strings[i] = "";
        }
    }
    
    while (receiver.hasWaitingMessages()) {
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        if (m.getAddress() == "/state/isPaused") {
            video.setPaused(m.getArgAsBool(0));
        }
        
        // check for mouse moved message
        if (m.getAddress() == "/state/position") {
            video.setPosition(m.getArgAsFloat(0));
        }
    }
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
        ofDrawBitmapString("It's reciever", 20, 20);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 's') {
        is_setting = !is_setting;
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
    
    if (is_setting) {
        if (selected == 99) {
            center.x = x;
            center.y = y;
        }
        else if (selected != -1) {
            p[selected].x = x;
            p[selected].y = y;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    for (int i = 0; i < 4; i++) {
        if (p[i].distance(ofVec3f(x, y, 0)) < 8) {
            selected = i;
            break;
        }
    }
    if (selected == -1 && center.distance(ofVec3f(x, y, 0)) < 8) {
        selected = 99;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    if (selected != 99 && selected != -1) {
        center.x = (p[0].x + p[1].x + p[2].x + p[3].x) / 4;
        center.y = (p[0].y + p[1].y + p[2].y + p[3].y) / 4;
    }
    selected = -1;
    mesh.clear();
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
