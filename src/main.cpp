#include <iostream>
#include "Vec2f.h"
#include "Orders.h"

int main()
{
   
    OrdersList *list = new OrdersList();
  
    Deploy *deploy = new Deploy;
    Bomb *bomb = new Bomb;
    Airlift *airlift = new Airlift;
    Bomb *bomb2 = new Bomb;
   
    list->addToList(*deploy);
    list->addToList(*bomb);
    list->addToList(*airlift);
    list->addToList(*bomb2);

    list->move(*bomb2, 0);


    return 0;
}

