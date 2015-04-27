#ifndef __tonicWaves_00__ringOsc__
#define __tonicWaves_00__ringOsc__

#include <stdio.h>
#include "ofMain.h"
#include "ofxTonic.h"
#define MIN_RADIUS 10
#define MIN_FREQUENCY 200
#define PLAY_DURATION 100

#endif /* defined(__tonicWaves_00__ringOsc__) */

using namespace Tonic;

class ringOsc {
public:
    int mainRadius;
    int numRings;
    vector<int> innerRadii;
    vector<float> frequencies;
    vector<ofPoint> positions;
    vector<ofColor> colors;
    vector<bool> playing;
    vector<int> playCounters;
    ofPoint center;
    ofColor ringColor;
    
    ofxTonicSynth synth;
    
    ringOsc();
    void setup(int _mainRadius, int _numRings, ofPoint _center);
    void update();
    void draw();
    void trigger(int degree);
};