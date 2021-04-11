#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    font.load("Teko-Regular.ttf",32);
    gui.setup();
    
    gui.add(intSlider.setup("int radius", 4, 1, 60));
    gui.add(vec2Slider.setup("vec2 coordinate", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));
    gui.add(vec3Slider.setup("vec3 color", ofVec3f(0, 122, 255), ofVec3f(0, 0, 0), ofVec3f(255, 255, 255)));

    
    ofBackground(255,255,255);
    ofEnableSmoothing();
    
    //Initialize the drawing variables
    for (int i = 0; i < ofGetWidth(); ++i) {
        waveform[i] = 0;
    }
    waveIndex = 0;
    
    // Maximilian audio stuff
    int sampleRate = 44100; /* Sampling Rate */
    int bufferSize= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    myClock.setTempo(120);
    myClock.setTicksPerBeat(4);
    
    mySample.load(ofToDataPath("endMusic.wav"));
    // Setup ofSound
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
    
    // Setup audio
    bass.load("bassDubberC.wav");
    bass.setVolume(0.8);

}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
//    font.drawString(">_<", ofGetMouseX(), ofGetMouseY());

    font.drawString("Try GUI, move mouse", ofGetWidth()/20, ofGetHeight()*15/16);
    font.drawString("Press'l', 'h' or 'space'", ofGetWidth()/20, ofGetHeight()*7/8);
    gui.draw();
    /////////////// waveform
    ofTranslate(0, ofGetHeight()/2);
    ofSetColor(vec3Slider->x, vec3Slider->y, vec3Slider->z);
    ofNoFill();
    ofDrawLine(0, 0, 1, waveform[1] * ofGetHeight()/2.); //first line
    for(int i = 1; i < (ofGetWidth() - 1); ++i) {
       // ofDrawLine(i, waveform[i] * ofGetHeight()/2., i + vec2Slider->x, waveform[i+1] * ofGetHeight()/2.+vec2Slider->y);
        ofDrawCircle(i+vec2Slider->x, waveform[i] * ofGetHeight()/2.+vec2Slider->y, intSlider);

    }
}


//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer& input){
    std::size_t nChannels = input.getNumChannels();
    for (size_t i = 0; i < input.getNumFrames(); i++)
    {
        // handle input here
    }
}
//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer& output){
    
    int time;
    time = ofGetElapsedTimef();
    std::size_t outChannels = output.getNumChannels();
    for (int i = 0; i < output.getNumFrames(); ++i){
        
//        myClock.ticker();
//        if (myClock.tick && ofRandom(1.0)>0.5) {
//            myFreq += 100;
//
//        }
//
//        if (myClock.tick && ofRandom(1.0) < 0.25) {
//            myFreq -= 200;
//        }
        
        if (myClock.tick && time % 2 == 1) {
            myFreq +=3*(ofGetMouseX()+ofGetMouseY())/(ofGetWidth()+ofGetHeight());
        }else {
            myFreq -=3*(ofGetMouseX()+ofGetMouseY())/(ofGetWidth()+ofGetHeight());
        }
//      output[i * outChannels] = myOsc1.square(532) * 0.5;
//      output[i * outChannels] = myOsc1.sinewave(220 + (myOsc2.sinewave(0.1)*100)) * 0.5;
//      output[i * outChannels] = myOsc1.sinewave(220 + (myOsc2.sinewave(400)*100)) * 0.5;
//      output[i * outChannels] = myOsc1.sinewave(myFreq + abs(myOsc2.sinewave(0.4) * myOsc3.coswave(myFreq))) * (ofRandom(0.01) + 0.35);
        output[i * outChannels] = myOsc1.sinewave(myFreq + abs(myOsc2.sinewave(43.066) * myOsc3.coswave(myFreq)*0.043))*0.7*(ofGetMouseX()+ofGetMouseY())/(ofGetWidth()+ofGetHeight());
        
        output[i * outChannels + 1] = output[i * outChannels];
        
        
        float myOut = mySample.play(-1.5);
        //Hold the values so the draw method can draw them
        waveform[waveIndex] =  output[i * outChannels];
        if (waveIndex < (ofGetWidth() - 1)) {
            ++waveIndex;
        } else {
            waveIndex = 0;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        case 'h':
            myFreq = 3141;
            break;
            
        case 'l':
            myFreq = 10;
            break;
            
        case ' ':
            bass.play();
            break;

        default:
            break;
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
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
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
