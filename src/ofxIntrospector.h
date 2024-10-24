#pragma once

#include "ofFbo.h"
#include "ofAppRunner.h"

// Draw intermediate introspection shapes to this layer, which fade over time
class Introspector {
  
  class Shape {
  public:
    Shape(float x_, float y_, ofColor color_, uint64_t lifetimeFrames_);
    virtual ~Shape() = default;
    bool isDead() const;
    void update();
    virtual void draw() = 0;
  protected:
    float x, y;
    ofColor color;
    uint64_t lifetimeFrames;
    uint64_t lifetimeStartFrame { ofGetFrameNum() };
  };
  
  class Circle : public Shape {
  public:
    Circle(float x_, float y_, float r_, ofColor color_, bool filled_, uint64_t lifetimeFrames_);
    void draw() override;
  private:
    float r;
    bool filled;
  };
  
  class Line : public Shape {
  public:
    Line(float x_, float y_, float x2_, float y2_, ofColor color_, uint64_t lifetimeFrames_);
    void draw() override;
  private:
    float x2, y2;
  };

public:
  void update();
  void draw();
  bool keyPressed(int key); // return true if key press handled

  void addCircle(float x, float y, float r, ofColor color, bool filled, uint64_t lifetimeFrames=40);
  void addLine(float x, float y, float x2, float y2, ofColor color, uint64_t lifetimeFrames=40);
  
private:
  std::vector<std::unique_ptr<Introspector::Shape>> shapes;
  bool visible;
};
