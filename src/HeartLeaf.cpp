#include "HeartLeaf.hpp"

//--------------------------------------------------------------
HeartLeaf::HeartLeaf(){
    nowPoint = 0;
    isFillDraw = false;
    thenFrame = ofGetFrameNum();
}
//--------------------------------------------------------------
void HeartLeaf::calculation(float theta, float param, float h, float rotate, float scale, bool isXRotate){
    
    float x = cos(theta);
    float y = (pow(x, param) + sin(theta)) / h;
    if(isXRotate)x = -x;
    float rx = x*cos(rotate) + y*sin(rotate);
    float ry = x*sin(rotate) - y*cos(rotate);
    heart.addVertex(getPos.x + scale*rx, getPos.y - scale*ry);
    
}
//--------------------------------------------------------------
bool HeartLeaf::setup(ofPoint p, float rotate, ofColor c, int random){
    
    randomRotate = random; //random tree rotate
    
    //heart
    float skip = .01; //Á≤æÂ∫¶
    float h = ofRandom(1, 1.6);
    float scale = ofRandom(8, 30); //leaf size
    float translate = scale; //leaf translate
    float param = ofRandom(.4, .9);
    
    getPos = ofPoint(p.x + translate*cos(rotate),
                     p.y + translate*sin(rotate),
                     0);
    rotate = PI- rotate;
    
    for(float i=PI/2; i>=0; i-=skip){
        calculation(i, param, h, rotate, scale, false);
    }
    for(float i=TWO_PI; i>=3*PI/2; i-=skip){
        calculation(i, param, h, rotate, scale, false);
    }
    for(float i=3*PI/2; i<=TWO_PI; i+=skip){
        calculation(i, param, h, rotate, scale, true);
    }
    for(float i=0; i<=PI/2; i+=skip){
        calculation(i, param, h, rotate, scale, true);
    }
    heart.close();
    
    //color
    color = c;
    
}
//--------------------------------------------------------------
void HeartLeaf::draw(){ //draw heart
    
    ofPushMatrix();
    ofRotateY(randomRotate);
    
    //fill
    if(isFillDraw){
        ofSetColor(color);
        glBegin(GL_TRIANGLE_STRIP);
        for(int i=0; i<heart.getVertices().size(); i++){
            if(i%3 == 0) glVertex2f(getPos.x, getPos.y);
            glVertex2f(heart.getVertices()[i].x, heart.getVertices()[i].y);
        }
        glEnd();
    }
    
    //wire frame
    ofSetColor(0);
    glBegin(GL_LINE_STRIP);
    for(int i=0; i<nowPoint; i++){
        glVertex2f(heart.getVertices()[i].x, heart.getVertices()[i].y);
    }
    glEnd();
    //wire frame update
    nowPoint += 15;
    if(nowPoint>heart.getVertices().size()){
        nowPoint = heart.getVertices().size();
        isFillDraw = true; //draw heart fill
    }
    

    
    ofPopMatrix();
    
}
//--------------------------------------------------------------








