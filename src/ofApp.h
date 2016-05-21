#pragma once

#include <string>

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxRollingCam.h"
#include "HeartLeaf.hpp"
#include "Tree.hpp"

class Font{
public:
    ofPoint pos;
    float rotate;
    string str;
    ofColor color;
};

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
    
    vector<HeartLeaf> heart;
    Tree tree;
    ofShader shader;
    ofFbo fbo;
    ofxRollingCam cam;
    void Shader();
    void getTweet();
    void drawHeartFlower(string s);
    int preText;
    
    ofxPanel gui;
    ofxFloatSlider g_rotate, g_scale;
    
    ofxTrueTypeFontUL2 font;
    vector<Font> drawFont;
    
    ofPolyline line;
};
