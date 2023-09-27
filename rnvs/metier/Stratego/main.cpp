#include "controller/controller.h"

#include "model/board.h"        // rnvs : include / déclaration anticipée
#include "model/game.h"         // rnvs : include / déclaration anticipée
#include "view/view.h"          // rnvs : include / déclaration anticipée

int main()
{
    Board b = Board();
    Game g = Game(b);
    View v = View(&g);
    Controller c = Controller(&g, &v);
    c.play();

}
