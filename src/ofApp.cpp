#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    
    int bufferSize = 256;
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    
    bufferCounter	= 0;
    smoothedVol = 0.0;
    scaledVol = 0.0;
    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);

	for (int i = 0; i<NBULBS; i++) {
		myBulb[i].setup(i);
	}
}

//--------------------------------------------------------------
void ofApp::update() {
    
    //scale the vol up to a 0-1 range
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
	for (int i = 0; i<NBULBS; i++) {
		myBulb[i].update();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofBackground(0);
    
    ofSetColor(225);
    ofDrawBitmapString("Scaled average vol (0-255): " + ofToString(scaledVol * 255.0, 0), 4, 18);

    ofEnableAlphaBlending();
	ofFill();
	ofSetColor(255, 63-(scaledVol * 255.0));
	ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, ofGetMouseX() / 5, ofGetMouseX() / 5);
    ofDisableAlphaBlending();
    
	for (int i = 0; i<NBULBS; i++) {
		myBulb[i].draw();
	}
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	for (int i = 0; i<NBULBS; i++) {
		myBulb[i].mouseDragged();
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	for (int i = 0; i<NBULBS; i++) {
		myBulb[i].mousePressed();
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	for (int i = 0; i<NBULBS; i++) {
		myBulb[i].mouseReleased();
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
