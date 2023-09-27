#ifndef OBSERVER_H
#define OBSERVER_H

#include "model/enum.h"
class Observer {

public:
    //destructor
    virtual ~Observer() = default;
    /*
    * virtual void update() = 0
    * simple update, extended class must have reference to observable
    */
    /*
    * virtual void update(const Observable & source) = 0;
    * update with Observable in parametre… not usefull because is "difficult"
    * to cast Observable to child
    */
    //virtual void update(const Observable & source) = 0;
    /**
     * Called when an observer is notified of a change.
     * @param The name of the change
     */
    virtual void update() = 0;
};


#endif // OBSERVER_H
