#include "lineOsc.h"

lineOsc::lineOsc() {
    
}

void lineOsc::setup(int _gridResolutionX, int _gridResolutionY, int _size, ofPoint _center) {
    gridResolutionX = _gridResolutionX;
    gridResolutionY = _gridResolutionY;
    size = _size;
    center = _center;
    
    vector<ofColor> palette;
    palette.push_back(ofColor(156, 205, 201));
    palette.push_back(ofColor(248, 177, 113));
    palette.push_back(ofColor(233, 158, 137));
    palette.push_back(ofColor(214, 115, 109));
    palette.push_back(ofColor(243, 220, 189));
    palette.push_back(ofColor(192, 49, 55));
    
    int xSpacing = size / gridResolutionX;
    int ySpacing = size / gridResolutionY;
    
    for(int x = 0; x <= gridResolutionX; x++) {
        lineObj lo;
        
        lo.start.set(center.x - size / 2, x * xSpacing + (center.x - size / 2));
        lo.end.set(center.x + size / 2, x * xSpacing + (center.x - size / 2));
        lo.position = lo.start;
        
        lo.fillColor.set(palette[(int) ofRandom(palette.size())]);
        lo.frequency = ofRandom(MIN_FREQUENCY, MAX_FREQUENCY) + ofRandom(200);
        lo.playing = false;
        lo.playCounter = PLAY_DURATION;
        
        lineObjs.push_back(lo);
    }
    for(int y = 0; y <= gridResolutionY; y++) {
        lineObj lo;
        
        lo.start.set(y * ySpacing + (center.y - size / 2) + 0.5, center.y - size / 2);
        lo.end.set(y * ySpacing + (center.y - size / 2) + 0.5, center.y + size / 2);
        lo.position = lo.start;
        
        lo.fillColor.set(palette[(int) ofRandom(palette.size())]);
        lo.frequency = ofRandom(MIN_FREQUENCY, MAX_FREQUENCY);
        lo.playing = false;
        lo.playCounter = PLAY_DURATION;
        
        lineObjs.push_back(lo);
    }
    
    ControlGenerator midiNote = synth.addParameter("midiNumber");
    ControlGenerator noteFreq =  ControlMidiToFreq().input(midiNote);
    Generator tone = SawtoothWave().freq( noteFreq );
    tone = LPF12().input(tone).Q(10).cutoff(noteFreq * 2);
    ControlGenerator envelopeTrigger = synth.addParameter("trigger");
    Generator toneWithEnvelope = 0.05 * tone * ADSR().attack(0.02).decay(0.2).sustain(0).release(0).trigger(envelopeTrigger);//.legato(true);
    
    synth.setOutputGen( toneWithEnvelope );
    
    stringColor.set(150, 150, 150);
}

void lineOsc::update() {
    for (int i = 0; i < lineObjs.size(); i++) {
        float t = ofMap(sin(TWO_PI * ofGetFrameNum() / lineObjs[i].frequency), -1, 1, 0, 1);
        lineObjs[i].position.x = ofLerp(lineObjs[i].start.x, lineObjs[i].end.x, t);
        lineObjs[i].position.y = ofLerp(lineObjs[i].start.y, lineObjs[i].end.y, t);
        
        for (int j = 0; j < lineObjs.size(); j++) {
            if(j != i && lineObjs[i].playing == false) {
                
                float ac = ofDist(lineObjs[j].start.x, lineObjs[j].start.y, lineObjs[i].position.x, lineObjs[i].position.y);
                float cb = ofDist(lineObjs[i].position.x, lineObjs[i].position.y, lineObjs[j].end.x, lineObjs[j].end.y);
                float ab = ofDist(lineObjs[j].start.x, lineObjs[j].start.y, lineObjs[j].end.x, lineObjs[j].end.y);
                if (abs((ac + cb) - ab) <= 1.0) {
                    //Wave Object i collided with the string of Wave Object j
                    
                    lineObjs[i].playing = true;
                    int degree = (int)ofMap(i, 0, lineObjs.size(), 0, 10);
                    trigger(degree);
                    
                }
            }
            lineObjs[i].playCounter--;
            if(lineObjs[i].playCounter == 0) {
                lineObjs[i].playing = false;
                lineObjs[i].playCounter = PLAY_DURATION;
            }
        }
    }
}

void lineOsc::draw() {
    for (int i = 0; i < lineObjs.size(); i++) {
        ofSetColor(stringColor);
        ofLine(lineObjs[i].start, lineObjs[i].end);
        
        ofSetColor(lineObjs[i].fillColor);
        ofCircle(lineObjs[i].position, 4);
    }
}

void lineOsc::trigger(int degree) {
    static int twoOctavePentatonicScale[10] = {0, 2, 4, 7, 9, 12, 14, 16, 19, 21};
    synth.setParameter("midiNumber", 56 + twoOctavePentatonicScale[degree]);
    synth.setParameter("trigger", 1);
}