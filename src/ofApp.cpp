#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofToggleFullscreen();
    ofSetFrameRate(30);
    ofSetLineWidth(3);
    ofEnableAlphaBlending();
    
    //trans paint
    shader.load("", "shader.frag");
    fbo.allocate(ofGetWidth(), ofGetHeight());
    
    //camera
    cam.setup();
    cam.setCamSpeed(.05);
    
    //gui
    gui.setup();
    gui.add(g_rotate.setup("tree rotate", 10, 0, 50));
    gui.add(g_scale.setup("tree scale", 1.6, 1., 3.));
    
    //font
    font.loadFont("mplus-1c-light.ttf", 5);
    font.setStrokeWidth(1.5f);
    
    //twitter
    preText = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    cam.update();   //rollCam's rotate update.
}
//--------------------------------------------------------------
void ofApp::draw(){
    
    ofEnableDepthTest();
    ofSetColor(255, 255);
    
    fbo.begin();
    ofBackground(255);
    ofSetColor(0);
    cam.begin();
    ofPushMatrix();
    ofTranslate(0, -250);
    tree.draw();
    for(int i=0; i<heart.size(); i++){
        heart[i].draw();
        ofSetColor(drawFont[i].color);
        ofPushMatrix();
        ofRotateY(drawFont[i].rotate);
        font.drawString(drawFont[i].str,drawFont[i].pos.x, drawFont[i].pos.y,0,0,0);
        ofPopMatrix();
        
    }
    ofPopMatrix();
    cam.end();
    fbo.end();
    
    
    //----draw sketch----
    Shader();
    
    //----twitter----
    getTweet();
    
    
    //    ofDrawBitmapStringHighlight(ofToString(heart.size()), 20, 20,
    //                                ofColor(255, 255), ofColor(0, 255));
    ofDisableDepthTest();
    //    gui.draw();
    
    
}
//--------------------------------------------------------------
void ofApp::Shader(){
    shader.begin();
    
    float f = 0.48;
    float c = 1-2*f;
    float coef[] = {
        f, 0, 0,
        0, c, 0,
        0, 0, f
    };
    
    shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    shader.setUniformTexture("_texture", fbo.getTexture(), 1);
    shader.setUniform1fv("coef", coef, 9);
    
    ofSetColor(255,255);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2d(0, 0);
    glVertex2d(0, 0);
    glTexCoord2d(ofGetWidth(), 0);
    glVertex2d(ofGetWidth(), 0);
    glTexCoord2d(0, ofGetHeight());
    glVertex2d(0, ofGetHeight());
    glTexCoord2d(ofGetWidth(),ofGetHeight());
    glVertex2d(ofGetWidth(), ofGetHeight());
    glEnd();
    
    shader.end();
}
//--------------------------------------------------------------
void ofApp::getTweet(){
    string text = string(ofBufferFromFile("tweet.txt")); //get text
    
    vector<string> texts = ofSplitString(text, ",#&&");
    
    if( preText != texts.size() ){
        int num = (texts.size() - preText)/2; //user id, text
        for(int i=0; i<num; i++){
            drawHeartFlower(texts[i+1]);
        }
        preText = texts.size();
    }
    
}
//--------------------------------------------------------------
void ofApp::drawHeartFlower(string s){
    
    //draw flower
    Arr arr;
    int random; //heart angle for tree position
    if(heart.size() < 30 || heart.size()%10 == 0 ){ //near tree
        arr = tree.getPoint(true); //heart position
        int vertical = ofRandom(4);
        random = 90*vertical;
    }else{ //around tree
        arr = tree.getPoint(false);
        random = ofRandom(0, 360);
    }
    
    HeartLeaf hl;
    hl.setup(arr.point[1],
             atan2(arr.point[2].y-arr.point[0].y, arr.point[2].x-arr.point[0].x),
             ofColor(255, ofRandom(100), ofRandom(100), ofRandom(100, 255)),
             random);
    heart.push_back(hl);
    
    //font
    Font f;
    f.pos = arr.point[1];
    f.rotate = random;
    f.str = s;
    //    f.color = ofColor::fromHsb(ofRandom(50, 110), 255, ofRandom(150, 255), 255);
    f.color = ofColor(ofRandom(255), 255, 0, 255);
    drawFont.push_back(f);
    
    
    //camera
    cam.setRotateY( random+ofRandom(-g_rotate, g_rotate) );
    cam.setRandomScale(1., g_scale);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'p'){
        drawHeartFlower("");
    }
    if(key == 'c'){
        cam.setRandomScale(ofRandom(1.), g_scale);
        cam.setRotateY( ofRandom(-180, 180) );
    }
}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    //    line.addVertex(x,y);
    //    printf("%d, %d,\n", x, y);
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}
