#include "ofxIntrospector.h"

#include "ofGraphics.h"
#include "ofUtils.h"

constexpr float FADE_FACTOR = 0.95;
constexpr float LINE_WIDTH = 1.0;

Introspector::Shape::Shape(float x_, float y_, ofColor color_, uint64_t lifetimeFrames_) :
x(x_), y(y_), color(color_), lifetimeFrames(lifetimeFrames_)
{}

bool Introspector::Shape::isDead() const {
  return (ofGetFrameNum() - lifetimeStartFrame > lifetimeFrames);
}

void Introspector::Shape::update() {
  color.a = color.a * FADE_FACTOR;
}

Introspector::Circle::Circle(float x_, float y_, float r_, ofColor color_, bool filled_, uint64_t lifetimeFrames_) :
Introspector::Shape(x_, y_, color_, lifetimeFrames_),
r(r_), filled(filled_)
{}

void Introspector::Circle::draw() {
  ofPushStyle();
  {
    ofSetColor(color);
    if (filled) {
      ofFill();
    } else {
      ofNoFill();
      ofSetLineWidth(LINE_WIDTH);
    }
    ofDrawCircle(x, y, r);
  }
  ofPopStyle();
}

Introspector::Line::Line(float x_, float y_, float x2_, float y2_, ofColor color_, uint64_t lifetimeFrames_) :
Introspector::Shape(x_, y_, color_, lifetimeFrames_),
x2(x2_), y2(y2_)
{}

void Introspector::Line::draw() {
  ofPushStyle();
  {
    ofSetColor(color);
    ofSetLineWidth(LINE_WIDTH);
    ofDrawLine(x, y, x2, y2);
  }
  ofPopStyle();
}



void Introspector::update() {
  if (!visible) return;
  std::for_each(shapes.begin(),
                shapes.end(),
                [](auto& s) { s->update(); });
  shapes.erase(std::remove_if(
                              shapes.begin(),
                              shapes.end(),
                              [](const auto& s) { return s->isDead(); }),
               shapes.end());
}

void Introspector::draw() {
  if (!visible) return;
  ofEnableBlendMode(OF_BLENDMODE_ALPHA);
  std::for_each(shapes.begin(),
                shapes.end(),
                [](auto& s) { s->draw(); });
}

// drawing on Introspection is usually normalised so scale up
void Introspector::draw(int scale) {
  ofPushStyle();
  ofPushView();
  ofEnableBlendMode(OF_BLENDMODE_ALPHA);
  ofScale(scale);
  draw();
  ofPopView();
  ofPopStyle();
}

bool Introspector::keyPressed(int key) {
  if (key == 'i') {
    visible = !visible;
    return true;
  }
  return false;
}

void Introspector::addCircle(float x, float y, float r, ofColor color, bool filled, uint64_t lifetimeFrames) {
  if (!visible) return;
  shapes.push_back(std::make_unique<Introspector::Circle>(x, y, r, color, filled, lifetimeFrames));
}

void Introspector::addLine(float x, float y, float x2, float y2, ofColor color, uint64_t lifetimeFrames) {
  if (!visible) return;
  shapes.push_back(std::make_unique<Introspector::Line>(x, y, x2, y2, color, lifetimeFrames));
}
