#include <iostream>
#include "Orders.h"

int main()
{
  

    OrdersList list;
    OrdersList ol2;
    
    //create orders
    Deploy *deploy = new Deploy;
    Bomb *bomb = new Bomb;
    Airlift *airlift = new Airlift;
    Blockade *blockade = new Blockade;
      
    //add orders to list  
    list.addToList(*deploy); 
    list.addToList(*bomb);
    list.addToList(*airlift);
    list.addToList(*blockade);
      
    vector<Order*> orders  = list.getList();
    cout << "orders list prior to moving orders around \n";
    cout << list;

    // move bomb order to end
    list.moveToEnd(*bomb);
    orders  = list.getList();
    cout << "orders list after moving bomb order to end \n";
    cout << list;

  // move blockade order to front
    list.moveToFront(*blockade);
    orders  = list.getList();
    cout << "orders list after moving blockade order tofront \n";
    cout << list;

     // move airlift order up the list
    list.moveUp(*airlift);
    orders  = list.getList();
    cout << "orders list after moving airlift order up the list \n";
    cout << list;

    // move airlift order up the list
    list.moveDown(*blockade);
    orders  = list.getList();
    cout << "orders list after moving blockade order down the list \n";
    cout << list;
  


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

