//
//  ofTildeblobPrimitive.hpp
//  pinkBubbles
//
//  Created by Mathilde Mouw on 9/16/19.
//

#ifndef ofTildeblobPrimitive_hpp
#define ofTildeblobPrimitive_hpp

#include "ofMesh.h"
#include "ofNode.h"
#include "of3dPrimitives.h"
#include <stdio.h>

/// \brief The ofTildeblobPrimitive (direct copy of ofCylinderPrimitive)
///allows you to create an cylinder mesh.
///
/// Like all primitives it allows you to set the size, for the cylinder
/// a radius and height, draw it, set positions, etc, as a simple example:
///
/// ~~~~{.cpp}
///
/// void setup()
/// {
///
///     cylinder.set( cylinderRadius, cylinderHeight );
/// }
///
/// void draw()
/// {
///
///     cylinder.setPosition(ofGetWidth()*.2, ofGetHeight()*.75, 0);
///     cylinder.rotate(spinX, 1.0, 0.0, 0.0);
///     cylinder.rotate(spinY, 0, 1.0, 0.0);
///
///     // get all the faces from the icoSphere, handy when you want to copy
///     // individual vertices or tweak them a little ;)
///     vector<ofMeshFace> triangles = cylinder.getMesh().getUniqueFaces();
///
///     // now draw
///     cylinder.draw();
/// }
/// ~~~~
///
/// To draw a texture over any primitive, simply bind the ofTexture instance
/// and then draw your primitive:
///
/// ~~~~{.cpp}
///
/// texture.getTextureReference().bind();
/// // now draw
/// cylinder.draw();
///
/// ~~~~

class ofTildeblobPrimitive : public of3dPrimitive {
public:
    ofTildeblobPrimitive();
    ofTildeblobPrimitive( float radius, float height, int radiusSegments,
                        int heightSegments, int capSegments=2, bool bCapped = true,
                        ofPrimitiveMode mode=OF_PRIMITIVE_TRIANGLE_STRIP );
    ~ofTildeblobPrimitive();
    
    void set( float radius, float height, int radiusSegments,
             int heightSegments, int capSegments=2, bool bCapped=true,
             ofPrimitiveMode mode=OF_PRIMITIVE_TRIANGLE_STRIP );
    void set( float radius, float height, bool bCapped=true );
    void setRadius( float radius );
    void setHeight( float height );
    void setCapped( bool bCapped );
    
    void setResolutionRadius( int radiusRes );
    void setResolutionHeight( int heightRes );
    void setResolutionCap( int capRes );
    void setResolution( int radiusSegments, int heightSegments, int capSegments=2 );
    void setMode( ofPrimitiveMode mode );
    
    void setTopCapColor( ofColor color );
    void setCylinderColor( ofColor color );
    void setBottomCapColor( ofColor color );
    
    std::vector<ofIndexType> getTopCapIndices() const;
    ofMesh getTopCapMesh() const;
    std::vector<ofIndexType> getCylinderIndices() const;
    ofMesh getCylinderMesh() const;
    std::vector<ofIndexType> getBottomCapIndices() const;
    ofMesh getBottomCapMesh() const;
    
    int getResolutionRadius() const;
    int getResolutionHeight() const;
    int getResolutionCap() const;
    glm::vec3 getResolution() const;
    
    float getHeight() const;
    float getRadius() const;
    bool getCapped() const;
protected:
    float radius;
    float height;
    bool bCapped;
    int strides[3][2];
    int vertices[3][2];
    glm::vec3 resolution;
};

#endif /* ofTildeblobPrimitive_hpp */
