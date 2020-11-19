// #include "Orders.h"
// using std::cout;
// using std::endl;
// using std::vector;

// int main()
// {

//     Player *p1 = new Player(std::string("Player 1"), std::vector<Territory>(), std::vector<Territory>(), Hand(), OrdersList());
//     Player *p2 = new Player(std::string("Player 2"), std::vector<Territory>(), std::vector<Territory>(), Hand(), OrdersList());

//     Territory *t11 = new Territory(11, "Territory 1", 25, 1, 2, *p1);
//     Territory *t12 = new Territory(12, "Territory 1", 10, 1, 2, *p1);
//     Territory *t21 = new Territory(21, "Territory 1", 10, 1, 2, *p2);
//     Territory *t22 = new Territory(22, "Territory 1", 10, 1, 2, *p2);


//     // Testing Deploy
//     Deploy deploy;
   
//     cout << "Executing INVALID deploy order" << endl;
//     cout << "\tArmies before deploying" << t21->getNumberOfOccupyingArmies() << endl;
//     deploy.execute(p1, 2, t21);
//     cout << "\tArmies after deploying" << t21->getNumberOfOccupyingArmies() << endl;

//     cout << "Executing VALID deploy order" << endl;
//     cout << "\tArmies before deploying" << t11->getNumberOfOccupyingArmies() << endl;
//     deploy.execute(p1, 2, t11);
//     cout << "\tArmies after deploying" << t11->getNumberOfOccupyingArmies() << endl;
//     cout << endl;

//      // Testing advance
//     Advance advance;
   
//     cout << "Executing INVALID advance order" << endl;
//     advance.execute(p1, 10, t12, t21);

//     cout << "Executing VALID advance order - target territory belongs to player" << endl;
//     cout << "\tSource territory armies before advancing" << t11->getNumberOfOccupyingArmies() << endl;
//     cout << "\tTarget territory armies before advancing" << t12->getNumberOfOccupyingArmies() << endl;
//     advance.execute(p1, 10, t12, t11 );
//     cout << "\tSource territory armies after advancing" << t11->getNumberOfOccupyingArmies() << endl;
//     cout << "\tTarget territory armies after advancing" << t12->getNumberOfOccupyingArmies() << endl;
//     cout << endl;

//     cout << "Executing VALID advance order - target territory belongs to enemy player" << endl;
//     cout << "\tTarget territory owner before advancing" << t22->getOwner() << endl;
//     cout << "\tTarget territory armies before advancing" << t22->getNumberOfOccupyingArmies() << endl;
//     advance.execute(p1, 10, t22, t11);
//     cout << "\\target territory owner after advancing" << t22->getOwner() << endl;
//     cout << "\tTarget territory armies after advancing" << t22->getNumberOfOccupyingArmies() << endl;
//     cout << endl;



//     // Testing bomb
//     Bomb bomb;
   
//     cout << "Executing INVALID bomb order" << endl;
//     cout << "\tArmies before bombing" << t12->getNumberOfOccupyingArmies() << endl;
//     bomb.execute(p1, t12);
//     cout << "\tArmies after bombing" << t12->getNumberOfOccupyingArmies() << endl;

//     cout << "Executing VALID bomb order" << endl;
//     cout << "\tArmies before bombing" << t21->getNumberOfOccupyingArmies() << endl; 
//     bomb.execute(p1, t21);
//     cout << "\tArmies after bombing" << t21->getNumberOfOccupyingArmies() << endl;
//     cout << endl;

//     // Testing blockade
//     Blockade blockade;
   
//     cout << "Executing INVALID blockade order" << endl;
//     cout << "\tOwner before blockading" << (t22->getOwner()) << endl;
//     cout << "\tArmies before blockading" << t22->getNumberOfOccupyingArmies() << endl;
//     blockade.execute(p1, t22);
//     cout << "\tOwner after blockading" << (t22->getOwner()) << endl;
//     cout << "\tArmies after blockading" << t22->getNumberOfOccupyingArmies() << endl;

//     cout << "Executing VALID blockade order" << endl;
//     cout << "\tOwner before blockading" << (t12->getOwner()) << endl;
//     cout << "\tArmies before blockading" << t12->getNumberOfOccupyingArmies() << endl;
//     blockade.execute(p1, t12);
//     cout << "\tOwner after blockading" << (t12->getOwner()) << endl;
//     cout << "\tArmies after blockading" << t12->getNumberOfOccupyingArmies() << endl;

//     // Testing negotiate
//     Negotiate negotiate;
//     std::vector<Territory> attack({*t21, *t22});
//     Player *p3 = new Player(std::string("Player 2"), attack, std::vector<Territory>(), Hand(), OrdersList());
//     Territory *t31 = new Territory(4, "Territory 4", 10, 1, 2, *p3);

    
//     cout << "Executing INVALID negotiate order" << endl;
//     negotiate.execute(p1, p1);

//     cout << "Executing VALID negotiate order" << endl;
//     negotiate.execute(p2, p3);
//     // p2->addToNegotiatorsList(*p3);
//     bomb.execute(p3, t21);
//     bomb.execute(p3, &((p3->toAttack())[1])); // attacklist[0] points to t2
//     bomb.execute(p2, t31);
//     bomb.execute(p1, t31); // p3 can still attack t31 (previous functionality would have set a doNotAttack flag on it)
//                            // thus making it unattackable by any player.

//     // Testing airlift
//     Airlift airlift;
   
//     cout << "Executing INVALID airlift order" << endl;
//     airlift.execute(p1, 5, t11, t21);
   
//     cout << "Executing VALID airlift order" << endl;
//     cout << "\tArmies source territory before airlifting" << t12->getNumberOfOccupyingArmies() << endl;
//     cout << "\tArmies target territory before airlifting" << t11->getNumberOfOccupyingArmies() << endl;
//     airlift.execute(p1, 5, t11, t12);
//     cout << "\tArmies source territory after airlifting" << t12->getNumberOfOccupyingArmies() << endl;
//     cout << "\tArmies target territory after airlifting" << t11->getNumberOfOccupyingArmies() << endl;

//     delete p1;
//     delete p2;
//     delete p3;
//     delete t11;
//     delete t12;
//     delete t21;
//     delete t22;
//     delete t31;
// }
