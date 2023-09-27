#include "observer/observable.h"
#include "observer/observer.h"
#include <string>
void Observable::notify(const std::string &propertyName) const {
    for (auto *observer : _observers) {
        observer->update(propertyName);
    }
}
