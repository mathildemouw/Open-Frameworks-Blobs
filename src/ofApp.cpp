#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  bFill       = false;
  bWireframe  = true;

  float width     = ofGetWidth() * .12;
  float height    = ofGetHeight() * .12;

  tildeblob.set(width*.7, height*2.2);

  mode = 0;
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
  // tildeblob.setPosition(  -screenWidth * .3 + screenWidth *  2/4.f, screenHeight * -.1/9.f, 0);
  tildeblob.setPosition(290, 290, 0);

  // Tildeblob (copied from Cylinder) //
  // TODO: clarify what TopCapMesh, BottomCapMesh, and CylinderMesh are
  //  and why we only have to get them in mode 3
    if (mode == 3) {
        topCap = tildeblob.getTopCapMesh();
        bottomCap = tildeblob.getBottomCapMesh();
        body = tildeblob.getCylinderMesh();
    }

  tildeblob.rotateDeg(spinX, 1.0, 0.0, 0.0);
  tildeblob.rotateDeg(spinY, 0, 1.0, 0.0);

  if (bFill) {
      material.begin();
      ofFill();
      if (mode == 3) {
          tildeblob.transformGL();
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
          tildeblob.restoreTransformGL();
      }
      else {
          tildeblob.draw();
      }
      material.end();
  }

  if (bWireframe) {
      ofNoFill();
      ofSetColor(255,20,147);
      tildeblob.setScale(1.01f);
      tildeblob.drawWireframe();
      tildeblob.setScale(1.0f);
  }
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
