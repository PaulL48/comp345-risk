#include <iostream>
#include "Orders.h"

int main()
{
    OrdersList list;
    OrdersList list2;
    
    //create orders
    Deploy deploy;
    Bomb bomb;
    Airlift airlift;
    Blockade blockade;
    Airlift airlift2;

    cout << "Printing deploy order. Will not print the effect of the order. \n";
    cout << deploy;

    cout << "\n Printing deploy order after calling execute. Will now also print effect of ther order. \n";
    deploy.execute();
    cout << deploy;
   
    cout << "\n printing airlift & airlift2 after assigning airlift to airlift 2 and then calling execute on airlift.\n";
    airlift2 = airlift;
    airlift.execute();
    cout << "Airlift: " << airlift;
    cout << "Airlift 2: " <<airlift2;

    cout << "\n printing airlift 3 after initializing in with the copy constructor with airlift order \n";
    Airlift airlift3 = airlift;
    cout << "Airlift: " << airlift;
    cout << "Airlift 3: " <<airlift3;
      
    //add orders to list  
    list.addToList(deploy); 
    list.addToList(bomb);
    list.addToList(airlift);
    list.addToList(blockade);
      
    vector<Order*> orders  = list.getList();
    cout << "orders list prior to moving orders around \n";
    cout << list;

    // move bomb order to end
    list.moveToEnd(bomb);
    orders  = list.getList();
    cout << "orders list after moving bomb order to end \n";
    cout << list;

  // move blockade order to front
    list.moveToFront(blockade);
    orders  = list.getList();
    cout << "orders list after moving blockade order tofront \n";
    cout << list;

     // move airlift order up the list
    list.moveUp(airlift);
    orders  = list.getList();
    cout << "orders list after moving airlift order up the list \n";
    cout << list;

    // move airlift order up the list
    list.moveDown(blockade);
    orders  = list.getList();
    cout << "orders list after moving blockade order down the list \n";
    cout << list;
  

    cout << "\nPrinting orders list after removing deploy. \n";
    list.remove(deploy);
    cout << list;

    cout << "\nPrinting list and list 2. \n";
    cout << "List: \n";
    cout << list;
    cout << "List 2: \n";
    cout << list2;

    cout << "\nPrinting list and list 2 after copying list to list2 with assignment operator . \n";
    list2 = list;
    cout << "List: \n";
    cout << list;
    cout << "List 2: \n";
    cout << list2;

    cout << "\nPrinting list and list 2 after deleting blockade from list. \n";
    list.remove(blockade);
    cout << "List: \n";
    cout << list;
    cout << "List 2: \n";
    cout << list2;

    cout << "\nPrinting list3 created with orderslist copy constructor with list2 . \n";
    OrdersList list3 = list2;
    cout << "List3: \n";
    cout << list3;

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

