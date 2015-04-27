#pragma once

#include "ofMain.h"
#include "ringOsc.h"
#include "lineOsc.h"
#define NUM_MODES 1

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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void audioRequested(float * output, int bufferSize, int nChannels);
    
    int mode;
    ofColor stringColor;
    ofColor canvasColor;
    vector<ofColor> palette;
    
    ringOsc ring;
    lineOsc line;
};
