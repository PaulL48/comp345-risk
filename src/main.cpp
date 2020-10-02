#include "Orders.h"
using std::cout;
using std::vector;

int main()
{
    OrdersList list;
    OrdersList list2;
    
    //create orders
    Deploy deploy;
    Bomb bomb;
    Deploy deploy2;
    Negotiate negotiate;


   
    list.addToList(deploy);
    list.addToList(negotiate); 
        list.addToList(bomb); 

    list.addToList(deploy2); 


    
    list.moveToFront(negotiate);
 cout <<list;
      
    vector<Order*> orders  = list.getList();
  //   cout << "orders list prior to moving orders around \n";
  //   cout << list;

  //   // move bomb order to end
  //   list.moveToEnd(bomb);
  //   orders  = list.getList();
  //   cout << "orders list after moving bomb order to end \n";
  //   cout << list;

  // // move blockade order to front
  //   list.moveToFront(blockade);
  //   orders  = list.getList();
  //   cout << "orders list after moving blockade order tofront \n";
  //   cout << list;

  //    // move airlift order up the list
  //   list.moveUp(airlift);
  //   orders  = list.getList();
  //   cout << "orders list after moving airlift order up the list \n";
  //   cout << list;

    // move airlift order up the list
    // list.moveDown(blockade);
    // orders  = list.getList();
    // cout << "orders list after moving blockade order down the list \n";
    // cout << list;
  

    // cout << "\nPrinting orders list after removing deploy. \n";
    // list.remove(deploy);
    // cout << list;

    // cout << "\nPrinting list and list 2. \n";
    // cout << "List: \n";
    // cout << list;
    // cout << "List 2: \n";
    // cout << list2;

    // cout << "\nPrinting list and list 2 after copying list to list2 with assignment operator . \n";
    // list2 = list;
    // cout << "List: \n";
    // cout << list;
    // cout << "List 2: \n";
    // cout << list2;

    // cout << "\nPrinting list and list 2 after deleting blockade from list. \n";
    // list.remove(blockade);
    // cout << "List: \n";
    // cout << list;
    // cout << "List 2: \n";
    // cout << list2;

    // cout << "\nPrinting list3 created with orderslist copy constructor with list2 . \n";
    // OrdersList list3 = list2;
    // cout << "List3: \n";
    // cout << list3;

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

