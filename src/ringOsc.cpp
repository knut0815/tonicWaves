#include "ringOsc.h"

ringOsc::ringOsc() {
    
}

void ringOsc::setup(int _mainRadius, int _numRings, ofPoint _center) {
    vector<ofColor> palette;
    palette.push_back(ofColor(156, 205, 201));
    palette.push_back(ofColor(248, 177, 113));
    palette.push_back(ofColor(233, 158, 137));
    palette.push_back(ofColor(214, 115, 109));
    palette.push_back(ofColor(243, 220, 189));
    palette.push_back(ofColor(192, 49, 55));
    
    mainRadius = _mainRadius;
    numRings = _numRings;
    center = _center;
    for(int i = 0; i < numRings; i++) {
        int radius = ofMap(i, 0, numRings, MIN_RADIUS, mainRadius);
        float frequency = ofRandom(MIN_FREQUENCY, 250) + ofRandom(200); //ofMap(i, 0, numRings, MIN_FREQUENCY, 440);
        float x = radius + center.x;
        float y = center.y;
        
        innerRadii.push_back(radius);
        frequencies.push_back(frequency);
        positions.push_back(ofPoint(x,y));
        colors.push_back(palette[(int)ofRandom(palette.size())]);
        playing.push_back(false);
        playCounters.push_back(PLAY_DURATION);
    }
    ringColor.set(150, 150, 150);
    
    
    ControlGenerator midiNote = synth.addParameter("midiNumber");
    ControlGenerator noteFreq =  ControlMidiToFreq().input(midiNote);
    Generator tone = SawtoothWave().freq( noteFreq );
    tone = LPF12().input(tone).Q(10).cutoff(noteFreq * 2);
    ControlGenerator envelopeTrigger = synth.addParameter("trigger");
    Generator toneWithEnvelope = tone * ADSR().attack(0.01).decay(0.5).sustain(0).release(1.0).trigger(envelopeTrigger).legato(true);
    
    synth.setOutputGen( toneWithEnvelope );
}

void ringOsc::update() {
    for (int i = 0; i < numRings; i++) {
        float theta = frequencies[i] + ofGetElapsedTimef() * (i + 0.5);
        float x = innerRadii[i] * cos(theta) + center.x;
        float y = innerRadii[i] * sin(theta) + center.y;
        positions[i].set(x, y);
    }
}

void ringOsc::draw() {
    for (int i = 0; i < numRings; i++) {
        //Draw the ring
        ofNoFill();
        ofSetColor(ringColor);
        ofCircle(center, innerRadii[i]);
        
        //Draw the dot
        ofFill();
        ofSetColor(colors[i]);
        ofCircle(positions[i], 4);
        
        for (int j = i + 1; j < numRings; j++) {
            ofVec2f ic = center - positions[i];
            ofVec2f jc = center - positions[j];
            ic.normalize();
            jc.normalize();
            
            float angle = acos(ic.dot(jc));
            
            if(angle < (PI / 4.0)) {
                ofLine(positions[i], positions[j]);
                if(playing[i] == false) {
                    int degree = (int)ofMap(i, 0, numRings, 0, 10);
                    trigger(degree);
                    playing[i] = true;
                }
            }
            playCounters[i]--;
            if(playCounters[i] == 0) {
                playing[i] = false;
                playCounters[i] = PLAY_DURATION;
            }
        }
    }
}

void ringOsc::trigger(int degree) {
    static int twoOctavePentatonicScale[10] = {0, 2, 4, 7, 9, 12, 14, 16, 19, 21};
    synth.setParameter("midiNumber", 56 + twoOctavePentatonicScale[degree]);
    synth.setParameter("trigger", 1);
}
