#ifndef GOLF_COMPONENT_H
#define GOLF_COMPONENT_H

class GameObject;

class Component {
   public:

    GameObject *gameObject;


    virtual void start() = 0;
    virtual void update() = 0;
    virtual void fixedUpdate() = 0;
};

#endif  // GOLF_COMPONENT_H
