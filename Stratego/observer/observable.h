#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <set>
#include <string>
#include "model/enum.h"

class Observer;

/**
* @brief Represents the Observable class.
*/
class Observable {
private:
    std::set<Observer *> _observers{};

public:
    virtual ~Observable() = default;    // polymorphism

    //void notify() const;
    /**
     * Notifys all of its observers if the object has changed.
     * @param propertyName the name of the change.
     */
    void notify() const;

    /**
    * Adds an observer to the set of observers for this object.
    *
    */
    inline void addObserver(Observer *);

    /**
    * Deletes an observer to the set of observers for this object.
    *
    */
    inline void deleteObserver(Observer *);
};

// implements inline methods
void Observable::addObserver(Observer *observer) {
    _observers.insert(observer);
}

void Observable::deleteObserver(Observer *observer) {
    _observers.erase(observer);
}


#endif // OBSERVABLE_H
