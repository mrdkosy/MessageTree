#ifndef HeartLeaf_hpp
#define HeartLeaf_hpp
#endif /* HeartLeaf_hpp */

#include <stdio.h>
#include "ofMain.h"
#include "ofxTrueTypeFontUL2.h"

class HeartLeaf{
public:
    bool setup(ofPoint p, float rotate, ofColor c, int random);
    void draw();
    void calculation(float theta, float param, float h, float rotate, float scale, bool isXRotate);
    HeartLeaf();
private:
    ofPolyline heart;
    ofPoint getPos; //draw pos
    int thenFrame, nowPoint, randomRotate; //draw frame, now point num
    ofColor color; //leaf color
    bool isFillDraw;
};


