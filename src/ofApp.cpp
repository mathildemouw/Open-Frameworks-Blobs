#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

  float width     = ofGetWidth() * .12;
  float height    = ofGetHeight() * .12;
  
  cylinder.set(width*.7, height*2.2);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  ofDrawBitmapString("Check out the shape!", 80, 80);
  float spinX = sin(ofGetElapsedTimef()*.35f);
  float spinY = cos(ofGetElapsedTimef()*.075f);

  float screenWidth = ofGetWidth();
  float screenHeight = ofGetHeight();

  // setPosition(float px, float py, float pz)
//  cylinder.setPosition(  -screenWidth * .3 + screenWidth *  2/4.f, screenHeight * -.1/9.f, 0);

  cylinder.setPosition(  290, 290, 0);
  // Cylinder //
//    if (mode == 3) {
//        topCap = cylinder.getTopCapMesh();
//        bottomCap = cylinder.getBottomCapMesh();
//        body = cylinder.getCylinderMesh();
//    }

  cylinder.rotateDeg(spinX, 1.0, 0.0, 0.0);
  cylinder.rotateDeg(spinY, 0, 1.0, 0.0);
//  if (bFill) {
      material.begin();
      ofFill();
//      if (mode == 3) {
          cylinder.transformGL();
          ofPushMatrix(); {
              if (topCap.getNumNormals() > 0) {
                  ofTranslate(topCap.getNormal(0) * (cos(ofGetElapsedTimef() * 5) + 1)*.5f * 100);
                  topCap.draw();
              }
          } ofPopMatrix();
          ofPushMatrix(); {
              if (bottomCap.getNumNormals() > 0) {
                  ofTranslate(bottomCap.getNormal(0) * (cos(ofGetElapsedTimef() * 4) + 1)*.5f * 100);
                  bottomCap.draw();
              }
          } ofPopMatrix();
          ofPushMatrix(); {
              float scale = (cos(ofGetElapsedTimef() * 3) + 1)*.5f + .2;
              ofScale(scale, scale, scale);
              body.draw();
          } ofPopMatrix();
          cylinder.restoreTransformGL();
//      }
//      else {
//          cylinder.draw();
//      }
      material.end();
//  }
  
//  if (bWireframe) {
      ofNoFill();
      ofSetColor(255,20,147);
      cylinder.setScale(1.01f);
      cylinder.drawWireframe();
      cylinder.setScale(1.0f);
//  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
