#include <iostream>
#include "Vec2f.h"
#include "Orders.h"

int main()
{
   
  //   OrdersList *list = new OrdersList();
  
  //   Deploy *deploy = new Deploy;
  //   Bomb *bomb = new Bomb;
  //   Airlift *airlift = new Airlift;
  //   Blockade *blockade = new Blockade;
  //     // Bomb *bomb3 = new Bomb;

      
  //   list->addToList(*deploy); 
  //   list->addToList(*bomb);
  //   list->addToList(*airlift);
  //   list->addToList(*blockade);
  //       vector<Order*>::iterator it;

  //   vector<Order*> orders  = list->getList();
  //   for(it = orders.begin(); it != orders.end(); ++it){
  //          cout << **it << "\n";

  //   }

  //   list->moveToFront(*airlift);
  //   airlift->execute(); 
  //  orders  = list->getList();
  //   for(it = list->getList().begin(); it != orders.end(); ++it){
  //           cout << **it << "\n";

  //   }



  Deploy deploy;
  Bomb bomb;
  Deploy deploy2;

  

  cout << deploy << "\n";
  cout << deploy2 << "\n";
  
  deploy2 = deploy;
  deploy.execute();

  cout << deploy << "\n";
  cout << deploy2 << "\n";

    return 0;
}

