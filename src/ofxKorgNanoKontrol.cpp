#include "ofxKorgNanoKontrol.h"



ofxKorgNanoKontrol::ofxKorgNanoKontrol() {
    
    
}

ofxKorgNanoKontrol::~ofxKorgNanoKontrol() {
    // clean up
    midiIn.closePort();
    midiIn.removeListener(this);
    cout << "MIDI port is closed" << endl;
}

/***********************************/
/* autoset : set true to set MIDI port auto 
   _portNum : default 0
 */
/***********************************/
void ofxKorgNanoKontrol::setup(bool autoSet, int _portNum) {
    
    if(autoSet) {
        portNum = findKontrolPort();
    }else{
        portNum = _portNum;
    }
    
    sceneButton = false;
    
    // GUI related
    ySpace = 170;
    yPosMult = 0;
    yStartPos = 220;
    xPosMult = 0;
    
    
    midiIn.openPort(portNum);
    
    // don't ignore sysex, timing, & active sense messages,
    // these are ignored by default
    midiIn.ignoreTypes(false, false, false);
    
    // add ofApp as a listener
    midiIn.addListener(this);
    
    // print received messages to the console
    midiIn.setVerbose(true);
    
    
    //cout << nanoKontrolAxisMapping[0] << endl;
    
    //sliderVals.resize(nanoKontrolAxisMapping.size());
    
    
    sceneIdCounter = 1;
    
    //cout << "size : " << sizeof(sliders_v1) / sizeof(int) << endl;
    
    for (int i = 0; i < sizeof(sliders_v1) / sizeof(int); i++) {
        
        sliderVals.resize(sliderVals.size() + 1);
        sliderVals[i].val = 0;
        sliderVals[i].midiId = sliders_v1[i];
        sliderVals[i].scene = sceneIdCounter;
        
        potVals.resize(potVals.size() + 1);
        potVals[i].val = 0;
        potVals[i].midiId = potentiometers_v1[i];
        potVals[i].scene = sceneIdCounter;
        
        
        // Hacky thing, there is no better solution
        if(i > 26) {
            sceneIdCounter++;
        }
    }
    
    // Reset scene counter for buttons
    sceneIdCounter = 1;
    // We need two sets of buttons, so set a new for loop
    for (int i = 0; i < sizeof(buttons_v1) / sizeof(int); i++) {
        buttonVals.resize(buttonVals.size() + 1);
        buttonVals[i].val = 0;
        buttonVals[i].midiId = buttons_v1[i];
        buttonVals[i].scene = sceneIdCounter;
        
        // increase the scene id every two button
        if(buttonVals[i].midiId == 17) {
            //cout  << sceneIdCounter << " midiId : " << sliderVals[i].midiId <<endl;
            sceneIdCounter++;
        }
    }
    
    
    for (int i = 0; i < sizeof(kontrol_v1) / sizeof(int); i++) {
        kontrolVals.resize(kontrolVals.size() + 1);
        kontrolVals[i].val = 0;
        kontrolVals[i].midiId = kontrol_v1[i];
        
        // SCENE button scene id = 0
        if(i == 6)
            kontrolVals[i].scene = 0;
        else
            kontrolVals[i].scene = 1;
    }
    
}


void ofxKorgNanoKontrol::showGui(bool _showGui) {
    if(_showGui) {
        ofSetColor(0);
        
        ofPushMatrix();
        ofTranslate(0, 0);
        
        ofFill();
        ofSetColor(0, 0, 0, 100);
        ofRect(0, 0, 548, 740);
        
        for (int i = 0; i < 36; i++) {
            if(i > 8) {
                yPosMult = 1;
                xPosMult = 9;
            }else{
                yPosMult = 0;
                xPosMult = 0;
            }
            
            if(i > 17) {
                yPosMult = 2;
                xPosMult = 18;
            }
            
            if(i > 26) {
                yPosMult = 3;
                xPosMult = 27;
            }
            
            // Sliders
            
            ofSetColor(0);
            ofDrawBitmapString("P." + ofToString(i+1), ofPoint(60 * (i - xPosMult) + 30, (yStartPos - 15) + ySpace*yPosMult));
            ofFill();
            ofRect(60 * (i - xPosMult) + 30, (yStartPos - 30) + ySpace*yPosMult, 23, ofMap(-getVal(i),0,127,0,84));
            ofNoFill();
            ofRect(60 * (i - xPosMult) + 30, (yStartPos - 30) + ySpace*yPosMult - 84, 23, 84);
            
            ofFill();
            
            
            // Potentiometers
            ofPushMatrix();
            ofTranslate(13 + 60 * (i - xPosMult) + 30, (yStartPos - 134) + ySpace*yPosMult);
            
            ofRotate((ofMap(getVal(i,POT), 0, 127, 0, 240)));
            
            ofCircle(0,0, 13);
            ofSetColor(255);
            
            ofTranslate(-8, 5);
            ofCircle(0, 0, 1);
            
            ofPopMatrix();
            
            
        }
        
        for (int i = 0; i < 72; i++) {
            if(i > 17) {
                yPosMult = 2;
                xPosMult = 18;
            }else{
                yPosMult = 0;
                xPosMult = 0;
            }
            
            if(i > 35) {
                yPosMult = 4;
                xPosMult = 36;
            }
            
            if(i > 53) {
                yPosMult = 6;
                xPosMult = 54;
            }
            
            // Buttons
            ofSetColor(0);
            if(getVal(i,BUTTON) > 0)
                ofFill();
            else
                ofNoFill();
            
            if(i % 2 == 0) {
                ofRect(30 * (i - xPosMult) + 10,  (yStartPos - 30) + ySpace*yPosMult/2 - 84, 14, 14);
            }else{
                ofRect(30 * (i-1 - xPosMult) + 10,18 + (yStartPos - 30) + ySpace*yPosMult/2 - 84, 14, 14);
            }
            
            
            ofNoFill();
            
        }
        
        int yPosAdd = 24;
        // Addional Buttons
        if(getVal(0,MENU_BUTTONS) > 0)
            ofFill();
        else
            ofNoFill();
        ofSetColor(0);
        ofRect(10, 10, 50, 20);
        ofSetColor(255);
        ofDrawBitmapString("prev", 20, yPosAdd);
        
        
        if(getVal(1,MENU_BUTTONS) > 0)
            ofFill();
        else
            ofNoFill();
        ofSetColor(0);
        ofRect(63, 10, 50, 20);
        ofSetColor(255);
        ofDrawBitmapString("play", 72, yPosAdd);
        
        
        if(getVal(2,MENU_BUTTONS) > 0)
            ofFill();
        else
            ofNoFill();
        ofSetColor(0);
        ofRect(116, 10, 50, 20);
        ofSetColor(255);
        ofDrawBitmapString("next", 125, yPosAdd);
        
        if(getVal(3,MENU_BUTTONS) > 0)
            ofFill();
        else
            ofNoFill();
        ofSetColor(0);
        ofRect(10, 33, 50, 20);
        ofSetColor(255);
        ofDrawBitmapString("loop", 20, yPosAdd + 23);
        
        if(getVal(4,MENU_BUTTONS) > 0)
            ofFill();
        else
            ofNoFill();
        ofSetColor(0);
        ofRect(63, 33, 50, 20);
        ofSetColor(255);
        ofDrawBitmapString("stop", 72, yPosAdd + 23);
        
        if(getVal(5,MENU_BUTTONS) > 0)
            ofFill();
        else
            ofNoFill();
        ofSetColor(0);
        ofRect(116, 33, 50, 20);
        ofSetColor(255);
        ofDrawBitmapString("rec", 128, yPosAdd + 23);
        
        /*
        if(getVal(6,MENU_BUTTONS))
            ofFill();
        else
            ofNoFill();
        ofSetColor(0);
        ofRect(186, 10, 50, 20);
        ofSetColor(255);
        ofDrawBitmapString("scene", 191, yPosAdd);
        ofPopMatrix();
         */
    }else{
        return;
    }
}
/***********************************/
/* Return nanoKONTROL attached port number */
/***********************************/
int ofxKorgNanoKontrol::findKontrolPort() {
    unsigned int nPorts = midiIn.getNumPorts();
    std::string portName;
    
    for ( uint i=0; i < nPorts; i++ ) {
        portName = midiIn.getPortName(i);
        if(portName.find("nanoKONTROL") != std::string::npos) {
            cout << "Defaulting to port " << i << endl;
            return i;
        }
    }
    cout << ("Cannot find nanoKONTROL or nanoKONTROL2") << endl;
    cout << ("Check your midi device connection or try to set port number manually") << endl;
    
    return -1;

}

/***********************************/
/* Get list of active MIDI devices */
/***********************************/
void ofxKorgNanoKontrol::getListMidiDevices() {
    
    // print input ports to console
    unsigned int nPorts = midiIn.getNumPorts();
    cout << "port count: " << nPorts << endl;
    midiIn.listPorts(); // via instance
}


void ofxKorgNanoKontrol::newMidiMessage(ofxMidiMessage& msg) {
    
    // make a copy of the latest message
    midiMessage = msg;
    /*cout << "Received : " << ofxMidiMessage::getStatusString(midiMessage.status) << endl;
    cout << "channel: " << midiMessage.channel << endl;
    cout << "pitch: " << midiMessage.pitch << endl;
    cout << "velocity: " << midiMessage.velocity << endl;
    cout << "control: " << midiMessage.control << endl;
    cout << "value : " << msg.value << endl;
    cout << "delta: " << midiMessage.deltatime << endl;
    */
    
    // Slider Handler
    for (int i = 0; i < sliderVals.size(); i++) {
        
        if(midiMessage.channel == sliderVals[i].scene && midiMessage.control == sliderVals[i].midiId) {
            sliderVals[i].val = midiMessage.value;
        }
        
        
        if(midiMessage.channel == potVals[i].scene && midiMessage.control == potVals[i].midiId) {
            potVals[i].val = midiMessage.value;
        }
    }
    
    // Button Handler
    for (int i = 0; i < buttonVals.size(); i++) {
        if(midiMessage.channel == buttonVals[i].scene && midiMessage.control == buttonVals[i].midiId) {
            buttonVals[i].val = midiMessage.value;
            //cout << buttonVals[i].val << " : " << buttonVals[i].scene << " : " << buttonVals[i].midiId << " : " << i << endl;
        }
    }
    
    
    // Addional Handler
    for (int i = 0; i < kontrolVals.size(); i++) {
        if(midiMessage.channel == kontrolVals[i].scene && midiMessage.control == kontrolVals[i].midiId) {
            kontrolVals[i].val = midiMessage.value;
            //
            // The last one is the SCENE button on KORG Nano Kontrol. It sends 0, so set it manually to get message
            if(i == 6 && midiMessage.value == 0) {
                ofNotifyEvent(sceneButtonPressed, midiMessage.value, this);
                //sceneButton = !sceneButton;
                //kontrolVals[i].val = sceneButton;
            }else{
                //sceneButton = !sceneButton;
                //kontrolVals[i].val = sceneButton;
            }
            //cout << kontrolVals[i].val << " : " << kontrolVals[i].scene << " : " << kontrolVals[i].midiId << " : " << i << endl;
        }
    }
    
    //cout << midiMessage.status << " " << midiMessage.control << " " << midiMessage.channel  << endl;
    //cout << sliderVals[0].val << midiMessage.control << " : " << midiMessage.channel << " : " << midiMessage.value << endl;
}

int ofxKorgNanoKontrol::getVal(int _control,int _type, int _sceneId) {
    //cout << "value : " << sliderVals[_control].val << endl;
    
    
    // Todo: Need to edit this condition for buttons
    if(_sceneId > 1) {
        if(_sceneId == 2) {
            _control = 9 + _control;
        }
    
        if(_sceneId == 3) {
            _control = 18 + _control;
        }
        
        if(_sceneId == 4) {
            _control = 27 + _control;
        }
    
    }
    
    if(_type == SLIDER)
        return sliderVals[_control].val;
    
    if(_type == POT)
        return potVals[_control].val;
    
    if(_type == BUTTON)
        return buttonVals[_control].val;
    
    if(_type == MENU_BUTTONS)
        return kontrolVals[_control].val;
}

int ofxKorgNanoKontrol::getSliderVal(int _control,int _sceneId) {
    
}

int ofxKorgNanoKontrol::getPotVal(int _control,int _sceneId) {
    
}

int ofxKorgNanoKontrol::getButtonVal(int _control,int _sceneId) {
    
}
/*
 void ofxKorgNanoKontrol::exit() {
 cout << "MIDI port is closed via exit() function" << endl;
 }*/
