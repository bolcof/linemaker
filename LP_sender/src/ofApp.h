#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#define PORT 12345

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
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void sendMessage(float videoPos, bool isPaused);
    
    string HOST, HOST2;
    
    ofVideoPlayer video;
    ofxOscSender sender, sender2;
    ofVec2f cursorPos;
    bool is_setting, selected_seek;
    
    ofImage screen;
    ofMesh mesh;
    ofVec3f p[4];
    ofVec3f center;
    int selected_pos;
};
