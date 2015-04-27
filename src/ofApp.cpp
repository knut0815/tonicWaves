#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
    
    stringColor.set(150, 150, 150);
    canvasColor.set(249, 242, 223);
    palette.push_back(ofColor(156, 205, 201));
    palette.push_back(ofColor(248, 177, 113));
    palette.push_back(ofColor(233, 158, 137));
    palette.push_back(ofColor(214, 115, 109));
    palette.push_back(ofColor(243, 220, 189));
    palette.push_back(ofColor(192, 49, 55));
    ofBackground(canvasColor);
    
    ofSetCircleResolution(100);
    
    mode = 1;
    ring.setup(ofGetWidth()/2, 5, ofPoint(ofGetWidth()/2, ofGetHeight()/2));
    line.setup(2, 2, 100, ofPoint(ofGetWidth()/2, ofGetHeight()/2));
}

//--------------------------------------------------------------
void ofApp::update(){
    if(mode == 0) {
        ring.update();
    }
    if(mode == 1) {
        line.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(mode == 0) {
        ring.draw();
    }
    if(mode == 1) {
        line.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_UP) {
        mode++;
        if(mode > NUM_MODES) {
            mode = NUM_MODES;
        }
    }
    if(key == OF_KEY_DOWN) {
        mode--;
        if(mode < 0) {
            mode = 0;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::audioRequested(float * output, int bufferSize, int nChannels){
    if(mode == 0) {
        ring.synth.fillBufferOfFloats(output, bufferSize, nChannels);
    }
    if(mode == 1) {
        line.synth.fillBufferOfFloats(output, bufferSize, nChannels);
    }
}
