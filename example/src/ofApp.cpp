#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
}

//--------------------------------------------------------------
void ofApp::update(){
  if (ofRandom(1.0) > 0.9) {
    introspector.addLine(ofRandomWidth(), ofRandomHeight(), ofRandomWidth(), ofRandomHeight(), ofFloatColor(ofRandom(1.0), ofRandom(1.0), ofRandom(1.0)), 20);
  }
  if (ofRandom(1.0) > 0.95) {
    introspector.addCircle(ofRandomWidth(), ofRandomHeight(), ofRandom(30.0), ofFloatColor(ofRandom(1.0), ofRandom(1.0), ofRandom(1.0)), ofRandomf() > 0.0, 30);
  }
  
  introspector.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(0);
  introspector.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (introspector.keyPressed(key)) return;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
