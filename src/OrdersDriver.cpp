// #include "Orders.h"
// using std::cout;
// using std::endl;
// using std::vector;

// int main()
// {

//     Player *p1 = new Player(std::string("Player 1"));
//     Player *p2 = new Player(std::string("Player 2"));

//     Territory *t11 = new Territory(11, "Territory 1", 25, 1, 2, *p1);
//     Territory *t12 = new Territory(12, "Territory 2", 10, 1, 2, *p1);
//     Territory *t21 = new Territory(21, "Territory 3", 10, 1, 2, *p2);
//     Territory *t22 = new Territory(22, "Territory 4", 10, 1, 2, *p2);

//     Map map;
//     map.addContinent(Continent("C1", 2, "blue"));
//     map.addTerritory(*t11, 1);
//     map.addTerritory(*t12, 1);
//     map.addTerritory(*t21, 1);
//     map.addTerritory(*t22, 1);

//     for (int i = 0; i < 4; ++i)
//     {
//         for (int j = 0; j < 4; ++j)
//         {
//             if (i != j)
//             {
//                 map.connectTerritories(i, j);
//             }
//         }
//     }


//     // Testing Deploy
//     Deploy deploy;
   
//     cout << "Executing INVALID deploy order" << endl;
//     cout << "\tArmies before deploying " << map.getGraph().find(*t21)->getOccupyingArmies() << endl;
//     deploy.execute(map, p1, 2, t21, nullptr, nullptr);
//     cout << "\tArmies after deploying" << map.getGraph().find(*t21)->getOccupyingArmies() << endl;

//     cout << "Executing VALID deploy order" << endl;
//     cout << "\tArmies before deploying " << map.getGraph().find(*t11)->getOccupyingArmies() << endl;
//     deploy.execute(map, p1, 2, t11, nullptr, nullptr);
//     cout << "\tArmies after deploying " << map.getGraph().find(*t11)->getOccupyingArmies() << endl;
//     cout << endl;

//      // Testing advance
//     Advance advance;
   
//     cout << "Executing INVALID advance order" << endl;
//     advance.execute(map, p1, 10, t12, t21, nullptr);

//     cout << "Executing VALID advance order - target territory belongs to player" << endl;
//     cout << "\tSource territory armies before advancing " << map.getGraph().find(*t11)->getOccupyingArmies() << endl;
//     cout << "\tTarget territory armies before advancing " << map.getGraph().find(*t12)->getOccupyingArmies() << endl;
//     advance.execute(map, p1, 10, t12, t11, nullptr);
//     cout << "\tSource territory armies after advancing " << map.getGraph().find(*t11)->getOccupyingArmies() << endl;
//     cout << "\tTarget territory armies after advancing " << map.getGraph().find(*t12)->getOccupyingArmies() << endl;
//     cout << endl;

//     cout << "Executing VALID advance order - target territory belongs to enemy player" << endl;
//     cout << "\tTarget territory owner before advancing " << *map.getGraph().find(*t22)->getOwningPlayer() << endl;
//     cout << "\tTarget territory armies before advancing " << map.getGraph().find(*t22)->getOccupyingArmies() << endl;
//     advance.execute(map, p1, 10, t22, t11, nullptr);
//     cout << "\\target territory owner after advancing " << *map.getGraph().find(*t22)->getOwningPlayer() << endl;
//     cout << "\tTarget territory armies after advancing " << map.getGraph().find(*t22)->getOccupyingArmies() << endl;
//     cout << endl;



//     // Testing bomb
//     Bomb bomb;
   
//     cout << "Executing INVALID bomb order" << endl;
//     cout << "\tArmies before bombing " << map.getGraph().find(*t12)->getOccupyingArmies() << endl;
//     bomb.execute(map, p1, 0, t12, nullptr, nullptr);
//     cout << "\tArmies after bombing " << map.getGraph().find(*t12)->getOccupyingArmies() << endl;

//     cout << "Executing VALID bomb order" << endl;
//     cout << "\tArmies before bombing " << map.getGraph().find(*t21)->getOccupyingArmies() << endl; 
//     bomb.execute(map, p1, 0, t21, nullptr, nullptr);
//     cout << "\tArmies after bombing " << map.getGraph().find(*t21)->getOccupyingArmies() << endl;
//     cout << endl;

//     // Testing blockade
//     Blockade blockade;
   
//     cout << "Executing INVALID blockade order" << endl;
//     cout << "\tOwner before blockading " << *map.getGraph().find(*t22)->getOwningPlayer() << endl;
//     cout << "\tArmies before blockading " << map.getGraph().find(*t22)->getOccupyingArmies() << endl;
//     blockade.execute(map, p1, 0, t22, nullptr, nullptr);
//     cout << "\tOwner after blockading " << map.getGraph().find(*t22)->getOwningPlayer() << endl;
//     cout << "\tArmies after blockading " << map.getGraph().find(*t22)->getOccupyingArmies() << endl;

//     cout << "Executing VALID blockade order" << endl;
//     cout << "\tOwner before blockading " << *map.getGraph().find(*t12)->getOwningPlayer() << endl;
//     cout << "\tArmies before blockading " << map.getGraph().find(*t12)->getOccupyingArmies() << endl;
//     blockade.execute(map, p1, 0, t12, nullptr, nullptr);
//     cout << "\tOwner after blockading " << map.getGraph().find(*t12)->getOwningPlayer() << endl;
//     cout << "\tArmies after blockading " << map.getGraph().find(*t12)->getOccupyingArmies() << endl;

//     // Testing negotiate
//     Negotiate negotiate;
//     std::vector<Territory> attack({*t21, *t22});
//     Player *p3 = new Player(std::string("Player 2"), attack, std::vector<Territory>(), Hand(), OrdersList(), 0, std::vector<int>());
//     Territory *t31 = new Territory(4, "Territory 4", 10, 1, 2, *p3);
//     for (int i = 0; i < 4; ++i)
//     {
//         map.connectTerritories(4, i);
//         map.connectTerritories(i, 4);
//     }

    
//     cout << "Executing INVALID negotiate order" << endl;
//     negotiate.execute(map, p1, 0, nullptr, nullptr, p1);

//     cout << "Executing VALID negotiate order" << endl;
//     negotiate.execute(map, p2,  0, nullptr, nullptr, p3);
//     // p2->addToNegotiatorsList(*p3);
//     bomb.execute(map, p3, 0, t21, nullptr, nullptr);
//     bomb.execute(map, p3, 0, &((p3->toAttack())[1]), nullptr, nullptr); // attacklist[0] points to t2
//     bomb.execute(map, p2, 0, t31, nullptr, nullptr);
//     bomb.execute(map, p1, 0, t31, nullptr, nullptr); // p3 can still attack t31 (previous functionality would have set a doNotAttack flag on it)
//                            // thus making it unattackable by any player.

//     // Testing airlift
//     Airlift airlift;
   
//     cout << "Executing INVALID airlift order" << endl;
//     airlift.execute(map, p1, 5, t11, t21, nullptr);
   
//     cout << "Executing VALID airlift order" << endl;
//     cout << "\tArmies source territory before airlifting " << map.getGraph().find(*t12)->getOccupyingArmies() << endl;
//     cout << "\tArmies target territory before airlifting " << map.getGraph().find(*t11)->getOccupyingArmies() << endl;
//     airlift.execute(map, p1, 5, t11, t12, nullptr);
//     cout << "\tArmies source territory after airlifting " << map.getGraph().find(*t12)->getOccupyingArmies() << endl;
//     cout << "\tArmies target territory after airlifting " << map.getGraph().find(*t11)->getOccupyingArmies() << endl;

//     delete p1;
//     delete p2;
//     delete p3;
//     delete t11;
//     delete t12;
//     delete t21;
//     delete t22;
//     delete t31;
// }
