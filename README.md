
# Openframework Demo: ofxGui and ofxMaxim

This is a simple openframework demo. The project references font files, shortcut key operations, and two addons: `ofxGui` and `ofxMaxim`, which can change the frequency through the GUI, keyboard shortcuts, and control the movement of wave by moving your mouse, it also supports the keyboard to play sounds.

![](https://miro.medium.com/max/700/1*2sFuI4yEf7hKqXEYTdGlvA.gif)

The following is a demo video case, and code can be cloned from my github:

YouTube: https://youtu.be/CAi0WaeSEC8

Github:  https://github.com/ShuSQ/CCI_ACC_W2_openframework

**keyPressed:**

'h' -> myFreq = 3141;

'l' -> myFreq = 10;

'space' -> bass.play();



First, in the `main.cpp` file, we create the size of the window:

```c++
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}
```

Then in the `ofApp.h` file, we need to create maxiOsc and the vector to control the GUI, as well as the audio to be played (keyboard control):

```c++
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
```

In `ofApp.cpp`, write our main program:

```c++
void ofApp::setup(){
    
    font.load("Teko-Regular.ttf",32);		// load font files
    gui.setup();	// set our gui content
    
    gui.add(intSlider.setup("int radius", 4, 1, 60));
    gui.add(vec2Slider.setup("vec2 coordinate", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));
    gui.add(vec3Slider.setup("vec3 color", ofVec3f(0, 122, 255), ofVec3f(0, 0, 0), ofVec3f(255, 255, 255)));

    
    ofBackground(255,255,255);	// set background colour
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
```

Then set the content of audioIn and audioOut, this part is mainly realized by `ofxMaxim`:

```c++
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

```

Then draw our GUI and text information in the ofApp:draw() function:

```c++
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
```

Finally, add a simple shortcut key operation:

```c++
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
```

