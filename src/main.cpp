#include <iostream>
#include "Vec2f.h"
#include "Orders.h"

int main()
{
   
    // OrdersList *list = new OrdersList();
  
    // Deploy *deploy = new Deploy;
    // Bomb *bomb = new Bomb;
    // Airlift *airlift = new Airlift;
    // Blockade *blockade = new Blockade;
    //   // Bomb *bomb3 = new Bomb;

    // list->addToList(*deploy);
    // list->addToList(*bomb);
    // list->addToList(*airlift);
    // list->addToList(*blockade);

    // cout << *deploy;
    // cout << *bomb;
    // cout << *airlift;
    // cout << *blockade;

    // deploy->execute();
    // bomb->execute();
    // airlift->execute();
    // blockade->execute();


    // cout << *deploy;
    // cout << *bomb;
    // cout << *airlift;
    // cout << *blockade;
    ///list->remove(*deploy);

  Deploy deploy;
  Bomb bomb;
  Deploy deploy2 = deploy;

  cout << deploy << "\n";
  cout << deploy2 << "\n";

  deploy.execute();

  cout << deploy << "\n";
  cout << deploy2 << "\n";

    return 0;
}

