#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetWindowPosition(0, 0);
    //nano.getListMidiDevices();
    nano.setup(true);
    
    kontrolGui = true;
    ofAddListener(nano.sceneButtonPressed, this, &ofApp::sceneButtonPressed);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    // Draw circle
    // By default Midi values are between 0-127
    // By default type is K_TYPE_SLIDER and Scene is K_SCENE_1
    // Check out the ofxKorgNanoKontrol.h file...
    int xpos = ofMap(nano.getVal(K_SLIDER_1),0,127,0,ofGetWidth());
    int ypos = ofMap(nano.getVal(K_SLIDER_2),0,127,0,ofGetHeight());
    int rad = ofMap(nano.getVal(K_SLIDER_3),0,127,20,300);
    
    
    
    
    
    // Set Circle Resolution via potentiometer at Scene 1 at first column
    int resVal = ofMap(nano.getVal(K_POT_1,K_TYPE_POT,K_SCENE_1), 0, 127, 3, 100);
    ofSetCircleResolution(resVal);
    
    
    
    
    // Set Fill Type via push buttons at Scene 1 at first column
    if(nano.getVal(K_BUTTON_1,K_TYPE_BUTTON) > 0)
        ofNoFill();
    else
        ofFill();
    
    
    
    
    ofDrawCircle(xpos,ypos,rad);
    
    //cout << "nano.getVal(K_SLIDER_1): " << nano.getVal(K_SLIDER_1) << endl;
    //cout << "nano.getVal(K_POT_1,K_TYPE_POT,K_SCENE_1): " << nano.getVal(K_POT_1,K_TYPE_POT) << endl;
    //cout << nano.getVal(K_BUTTON_1,K_TYPE_BUTTON) << endl;
    
    ofDrawBitmapStringHighlight("Korg Nano Kontrol Version 1 - Press 'g' to show/hide gui", ofPoint(20,20));
    
    // Show/hide gui
    nano.showGui(kontrolGui, 0, 25);
}

//--------------------------------------------------------------
void ofApp::sceneButtonPressed(int &e) {
    cout <<  "Scene button pressed" << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'g') {
        kontrolGui = !kontrolGui;
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

void ofApp::exit() {
    ofRemoveListener(nano.sceneButtonPressed, this, &ofApp::sceneButtonPressed);
}
