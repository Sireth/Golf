#ifndef GOLF_COMPONENT_H
#define GOLF_COMPONENT_H

class GameObject;

class Component {
   public:
    virtual void start() = 0;
    virtual void update() = 0;
    virtual void fixedUpdate() = 0;
    GameObject *gameObject;
};

#endif  // GOLF_COMPONENT_H
