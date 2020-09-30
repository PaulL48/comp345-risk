#include <iostream>
#include "Vec2f.h"
#include "Orders.h"

int main()
{
   
    OrdersList list;
      OrdersList ol2;
    Deploy *deploy = new Deploy;
    Bomb *bomb = new Bomb;
    Airlift *airlift = new Airlift;
    Blockade *blockade = new Blockade;
      // Bomb *bomb3 = new Bomb;
      
    list.addToList(*deploy); 
    list.addToList(*bomb);
    list.addToList(*airlift);
    list.addToList(*blockade);
        ol2 = list;

        vector<Order*>::iterator it;
list.moveToEnd(*bomb);

    vector<Order*> orders  = list.getList();
        vector<Order*> orders2  = ol2.getList();
    for(it = orders.begin(); it != orders.end(); ++it){
           cout << **it << "\n";

    }

    for(it = orders2.begin(); it != orders2.end(); ++it){
           cout << **it << "\n";

    }

  


  // Deploy deploy;
  // Bomb bomb;
  // Deploy deploy2;

  

  // cout << deploy << "\n";
  // cout << deploy2 << "\n";
  
  // deploy2 = deploy;
  // deploy.execute();

  // cout << deploy << "\n";
  // cout << deploy2 << "\n";

    return 0;
}

