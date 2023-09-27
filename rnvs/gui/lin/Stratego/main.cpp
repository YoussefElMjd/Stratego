//#include "controller/controller.h"
//#include "view/viewgui.h"
#include "controller/controllerGui.h"
//#include "view/viewgui.h"
//int main()
//{
//    Board b = Board();
//    Game g = Game(b);
//    View v = View(&g);
//    Controller c = Controller(&g,&v);
//    c.play();

//}
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Board b = Board();
    Game g = Game(b);
    ViewGui w =  ViewGui(&g);
    ControllerGui ctrl = ControllerGui(g,w);
    ctrl.start();
    return a.exec();
}
