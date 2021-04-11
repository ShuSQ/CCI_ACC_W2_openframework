#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxMaxim.h"

class ofApp : public ofBaseApp{
    
public:
    void setup() override;
    void update() override;
    void draw() override;
    
    void keyPressed(int key) override;
    void keyReleased(int key) override;
    void mouseMoved(int x, int y ) override;
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void mouseEntered(int x, int y) override;
    void mouseExited(int x, int y) override;
    void windowResized(int w, int h) override;
    void dragEvent(ofDragInfo dragInfo) override;
    void gotMessage(ofMessage msg) override;
    
    // For drawing
    float waveform[4096]; //make this bigger, just in case
    int waveIndex;
    
    ofSoundStream soundStream;
    ofTrueTypeFont font;
    
    /* ofxMaxi*/
    void audioIn(ofSoundBuffer& input) override; // not used in this example
    void audioOut(ofSoundBuffer& output) override;
    maxiOsc myOsc1;
    maxiOsc myOsc2;
    maxiOsc myOsc3;
    maxiClock myClock;
    float myFreq = 2000;
    
    maxiSample mySample;
    
    // add Gui
    ofxPanel gui;
    ofxIntSlider intSlider;
    ofxVec2Slider vec2Slider;
    ofxVec3Slider vec3Slider;
    
    // add Audio
    ofSoundPlayer bass;
};
