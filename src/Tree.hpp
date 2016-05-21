
#ifndef Tree_hpp
#define Tree_hpp

#include <stdio.h>
#include "ofMain.h"

typedef struct{
    ofPoint point[3];
}Arr;

class Tree{
public:
    void draw();
    Arr getPoint(bool random);
private:
};

#endif /* Tree_hpp */
