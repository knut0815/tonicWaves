#ifndef __tonicWaves_00__lineOsc__
#define __tonicWaves_00__lineOsc__

#include <stdio.h>
#include "ofMain.h"
#include "ofxTonic.h"
#define MIN_FREQUENCY 100
#define MAX_FREQUENCY 200
#define PLAY_DURATION 200

#endif /* defined(__tonicWaves_00__lineOsc__) */

using namespace Tonic;

struct lineObj {
    ofPoint start;
    ofPoint end;
    ofPoint position;
    ofColor fillColor;
    float frequency;
    bool playing;
    int playCounter;
};

class lineOsc {
public:
    int gridResolutionX;
    int gridResolutionY;
    int size;
    
    vector<lineObj> lineObjs;
    ofPoint center;
    ofColor stringColor;
    
    ofxTonicSynth synth;
    
    lineOsc();
    void setup(int _gridResolutionX, int _gridResolutionY, int _size, ofPoint _center);
    void update();
    void draw();
    void trigger(int degree);
};