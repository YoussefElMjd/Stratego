#include "controller/controllerGui.h"
#include <algorithm>
using namespace std;
void ControllerGui::start(){
    this->view.show();
    this->view.controller(this);
}
