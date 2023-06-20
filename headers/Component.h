#ifndef PONG_COMPONENT_H
#define PONG_COMPONENT_H

class Component {
   public:
    virtual void start() = 0;
    virtual void update() = 0;
    virtual void fixedUpdate() = 0;
};

#endif  // PONG_COMPONENT_H
