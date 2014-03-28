//
//  ModelContainer.cpp
//  Meshwurst
//
//  Created by Florian Brueckner on 25/03/2014.
//
//

#include "ModelContainer.h"

ModelContainer::ModelContainer(int offset)
{
    position = ofVec3f((offset * 150.0), 0.0, 0.0);
    rotation = 0.0;
    selected = false;
}

string ModelContainer::getInfo()
{
    return info;
}

Wurst ModelContainer::getWurst() {
    Wurst result;
    if (model.hasMeshes()) {
        // Look for the biggest submesh /////////////////
        int vTop = 0;
        ofMesh tmpMesh;
        for (int i=0; i < model.getMeshCount(); i++) {
            tmpMesh = model.getMesh(i);
            if (tmpMesh.getVertices().size() > vTop) {
                result.mesh = tmpMesh;
                result.matrix = model.getModelMatrix();
                vTop = result.mesh.getVertices().size();
            }
        }
        result.scale = model.getNormalizedScale();
        result.mesh = wurst(result.mesh);
    }
    return result;
}

ofMesh ModelContainer::wurst(ofMesh mesh)
{
    ofVec3f* previousTriangle = new ofVec3f[3];
    previousTriangle[0] = mesh.getVertices()[0];
    previousTriangle[1] = mesh.getVertices()[1];
    previousTriangle[2] = mesh.getVertices()[2];
    ofVec3f* triangle = new ofVec3f[3];
    ofVec3f vertex;
    for (int v=3; v<mesh.getNumVertices(); v+=3) {
        triangle[0] = mesh.getVertices()[v];
        triangle[1] = mesh.getVertices()[v+1];
        triangle[2] = mesh.getVertices()[v+2];
        for (int i=0; i<3; i++) {
            vertex = triangle[i];
            vertex.y *= ofNoise(previousTriangle[i].x);
            mesh.setVertex(v+i, vertex);
            previousTriangle[i] = vertex;
        }
    }
    return mesh;
}

void ModelContainer::populate(string file) {
    model.loadModel(file);
    if (model.hasMeshes())
        info = ofSplitString(file, ".")[0];
    model.setScale(0.15, 0.15, 0.15);
    highlightColor.r = 0;
    highlightColor.g = 128;
    highlightColor.b = 128;
    highlightColor.a = 200;
}

void ModelContainer::draw()
{
    if (model.hasMeshes()) {
        if (selected)
            drawMesh();
        else
            drawOutline();
        ofNoFill();
        ofDrawBox(position.x, position.y, position.z, 100.0);
    }
}

void ModelContainer::drawMesh() {
    ofSetColor(highlightColor);
    model.setPosition(position.x, position.y, position.z);
    rotation += (TWO_PI / 360) * 5.0;
    model.setRotation(0, rotation, 0.0, 1.0, 0.0);
    model.drawFaces();
    ofColor(255);
    model.draw(OF_MESH_WIREFRAME);
}

void ModelContainer::drawOutline() {
    ofSetColor(200, 200, 200, 128);
    model.setPosition(position.x, position.y, position.z);
    model.draw(OF_MESH_WIREFRAME);
}