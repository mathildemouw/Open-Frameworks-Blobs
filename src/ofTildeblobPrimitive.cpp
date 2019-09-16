//
//  ofTildeblobPrimitive.cpp
//  pinkBubbles
//
//  Created by Mathilde Mouw on 9/16/19.
//

#include "ofTildeblobPrimitive.hpp"
// Does including "of3dPrimitives.h" mean I have all I need for 3dPrimitives or
// do I need to explicitly call all  the other dependencies too?

#include "of3dPrimitives.h"
#include "ofGraphics.h"
#include "ofRectangle.h"
#include "ofVboMesh.h"
#include "ofTexture.h"
#include "of3dUtils.h"

using namespace std;

// ofCylinderPrimitive renamed to ofTildeblobPrimitive
// will this behave just as the ofCylinderPrimitive?
//--------------------------------------------------------------
ofTildeblobPrimitive::ofTildeblobPrimitive() {
    texCoords = {0.f, 0.f, 1.f, 1.f};
    set( 60, 80, 6, 3, 2, true );
}

//--------------------------------------------------------------
ofTildeblobPrimitive::ofTildeblobPrimitive( float radius, float height, int radiusSegments, int heightSegments, int capSegments, bool bCapped, ofPrimitiveMode mode ) {
    texCoords = {0.f, 0.f, 1.f, 1.f};
    set( radius, height, radiusSegments, heightSegments, capSegments, bCapped, mode );
}

//--------------------------------------------------------------
ofTildeblobPrimitive::~ofTildeblobPrimitive() {}

//--------------------------------------------------------------
void ofTildeblobPrimitive::set(float _radius, float _height, int radiusSegments, int heightSegments, int capSegments, bool _bCapped, ofPrimitiveMode mode) {
    radius = _radius;
    height = _height;
    bCapped = _bCapped;
    resolution = {radiusSegments, heightSegments, capSegments};
    
    int resX = std::max(getResolution().x,0.0f);
    int resY = std::max(getResolution().y-1,0.0f);
    int resZ = std::max(getResolution().z-1,0.0f);
    
    int indexStep = 2;
    if(mode == OF_PRIMITIVE_TRIANGLES) {
        indexStep = 6;
        resX = std::max(resX,0);
    }
    
    // 0 -> top cap
    strides[0][0] = 0;
    strides[0][1] = (resX+1) * (resZ+1) * indexStep;
    vertices[0][0] = 0;
    vertices[0][1] = (getResolution().x+1) * (getResolution().z+1);
    
    // 1 -> cylinder //
    if(bCapped) {
        strides[1][0]    = strides[0][0] + strides[0][1];
        vertices[1][0]    = vertices[0][0] + vertices[0][1];
    } else {
        strides[1][0]    = 0;
        vertices[1][0]    = 0;
    }
    strides[1][1] = (resX+1) * (resY+1) * indexStep;
    vertices[1][1] = (getResolution().x+1) * (getResolution().y+1);
    
    // 2 -> bottom cap
    strides[2][0] = strides[1][0] + strides[1][1];
    strides[2][1] = (resX+1) * (resZ+1) * indexStep;
    vertices[2][0] = vertices[1][0]+vertices[1][1];
    vertices[2][1] = (getResolution().x+1) * (getResolution().z+1);
    
    
    getMesh() = ofMesh::cylinder( getRadius(), getHeight(), getResolution().x, getResolution().y, getResolution().z, getCapped(), mode );
    
    normalizeAndApplySavedTexCoords();
    
}

//--------------------------------------------------------------
void ofTildeblobPrimitive::set( float _radius, float height, bool _bCapped ) {
    radius = _radius;
    bCapped = _bCapped;
    setHeight( height );
}

//--------------------------------------------------------------
void ofTildeblobPrimitive::setRadius( float _radius ) {
    radius = _radius;
    setResolution( getResolution().x, getResolution().y, getResolution().z );
}

//--------------------------------------------------------------
void ofTildeblobPrimitive::setHeight( float _height ) {
    height = _height;
    setResolution(getResolution().x, getResolution().y, getResolution().z);
}

//--------------------------------------------------------------
void ofTildeblobPrimitive::setCapped(bool _bCapped) {
    bCapped = _bCapped;
    setResolution( getResolution().x, getResolution().y, getResolution().z );
}

//--------------------------------------------------------------
void ofTildeblobPrimitive::setResolutionRadius( int radiusRes ) {
    setResolution( radiusRes, getResolutionHeight(), getResolutionCap() );
}

//--------------------------------------------------------------
void ofTildeblobPrimitive::setResolutionHeight( int heightRes ) {
    setResolution( getResolutionRadius(), heightRes, getResolutionCap() );
}

//--------------------------------------------------------------
void ofTildeblobPrimitive::setResolutionCap( int capRes ) {
    setResolution( getResolutionRadius(), getResolutionHeight(), capRes );
}

//--------------------------------------------------------------
void ofTildeblobPrimitive::setResolution( int radiusSegments, int heightSegments, int capSegments ) {
    ofPrimitiveMode mode = getMesh().getMode();
    set( getRadius(), getHeight(), radiusSegments, heightSegments, capSegments, getCapped(), mode );
}

//----------------------------------------------------------
void ofTildeblobPrimitive::setMode( ofPrimitiveMode mode ) {
    ofPrimitiveMode currMode = getMesh().getMode();
    if(currMode != mode)
        set( getRadius(), getHeight(), getResolution().x, getResolution().y, getResolution().z, getCapped(), mode );
}

//--------------------------------------------------------------
void ofTildeblobPrimitive::setTopCapColor( ofColor color ) {
    if(getMesh().getMode() != OF_PRIMITIVE_TRIANGLE_STRIP) {
        ofLogWarning("ofTildeblobPrimitive") << "setTopCapColor(): must be in triangle strip mode";
    }
    getMesh().setColorForIndices( strides[0][0], strides[0][0]+strides[0][1], color );
}

//--------------------------------------------------------------
void ofTildeblobPrimitive::setCylinderColor( ofColor color ) {
    if(getMesh().getMode() != OF_PRIMITIVE_TRIANGLE_STRIP) {
        ofLogWarning("ofTildeblobPrimitive") << "setCylinderMode(): must be in triangle strip mode";
    }
    getMesh().setColorForIndices( strides[1][0], strides[1][0]+strides[1][1], color );
}

//--------------------------------------------------------------
void ofTildeblobPrimitive::setBottomCapColor( ofColor color ) {
    if(getMesh().getMode() != OF_PRIMITIVE_TRIANGLE_STRIP) {
        ofLogWarning("ofTildeblobPrimitive") << "setBottomCapColor(): must be in triangle strip mode";
    }
    getMesh().setColorForIndices( strides[2][0], strides[2][0]+strides[2][1], color );
}

//--------------------------------------------------------------
vector<ofIndexType> ofTildeblobPrimitive::getTopCapIndices() const {
    return of3dPrimitive::getIndices( strides[0][0], strides[0][0] + strides[0][1] );
}

//--------------------------------------------------------------
ofMesh ofTildeblobPrimitive::getTopCapMesh() const {
    if(getMesh().getMode() != OF_PRIMITIVE_TRIANGLE_STRIP) {
        ofLogWarning("ofTildeblobPrimitive") << "getTopCapMesh(): must be in triangle strip mode";
        return ofMesh();
    }
    return getMesh().getMeshForIndices( strides[0][0], strides[0][0]+strides[0][1],
                                       vertices[0][0], vertices[0][0]+vertices[0][1] );
}

//--------------------------------------------------------------
vector<ofIndexType> ofTildeblobPrimitive::getCylinderIndices() const {
    if(getMesh().getMode() != OF_PRIMITIVE_TRIANGLE_STRIP) {
        ofLogWarning("ofTildeblobPrimitive") << "getCylinderIndices(): must be in triangle strip mode";
    }
    return of3dPrimitive::getIndices( strides[1][0], strides[1][0] + strides[1][1] );
}

//--------------------------------------------------------------
ofMesh ofTildeblobPrimitive::getCylinderMesh() const {
    if(getMesh().getMode() != OF_PRIMITIVE_TRIANGLE_STRIP) {
        ofLogWarning("ofTildeblobPrimitive") << "setCylinderMesh(): must be in triangle strip mode";
        return ofMesh();
    }
    return getMesh().getMeshForIndices( strides[1][0], strides[1][0]+strides[1][1],
                                       vertices[1][0], vertices[1][0]+vertices[1][1] );
}

//--------------------------------------------------------------
vector<ofIndexType> ofTildeblobPrimitive::getBottomCapIndices() const {
    if(getMesh().getMode() != OF_PRIMITIVE_TRIANGLE_STRIP) {
        ofLogWarning("ofTildeblobPrimitive") << "getBottomCapIndices(): must be in triangle strip mode";
    }
    return of3dPrimitive::getIndices( strides[2][0], strides[2][0] + strides[2][1] );
}

//--------------------------------------------------------------
ofMesh ofTildeblobPrimitive::getBottomCapMesh() const {
    if(getMesh().getMode() != OF_PRIMITIVE_TRIANGLE_STRIP) {
        ofLogWarning("ofTildeblobPrimitive") << "getBottomCapMesh(): must be in triangle strip mode";
        return ofMesh();
    }
    return getMesh().getMeshForIndices( strides[2][0], strides[2][0]+strides[2][1],
                                       vertices[2][0], vertices[2][0]+vertices[2][1] );
}

//--------------------------------------------------------------
int ofTildeblobPrimitive::getResolutionRadius() const {
    return (int)resolution.x;
}

//--------------------------------------------------------------
int ofTildeblobPrimitive::getResolutionHeight() const {
    return (int)resolution.y;
}

//--------------------------------------------------------------
int ofTildeblobPrimitive::getResolutionCap() const {
    return (int)resolution.z;
}

//--------------------------------------------------------------
glm::vec3 ofTildeblobPrimitive::getResolution() const {
    return resolution;
}

//--------------------------------------------------------------
float ofTildeblobPrimitive::getHeight() const {
    return height;
}

//--------------------------------------------------------------
float ofTildeblobPrimitive::getRadius() const {
    return radius;
}

//--------------------------------------------------------------
bool ofTildeblobPrimitive::getCapped() const {
    return bCapped;
}

