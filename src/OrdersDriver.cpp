#include "Orders.h"
using std::cout;
using std::endl;
using std::vector;

int main()
{

    Player *p = new Player(std::string("Player 1"), std::vector<Territory>(), std::vector<Territory>(), Hand(), OrdersList());
    Player *p2 = new Player(std::string("Player 2"), std::vector<Territory>(), std::vector<Territory>(), Hand(), OrdersList());

    Territory *t1 = new Territory(1, "Territory 1", 10, 1, 2, *p);
    Territory *t2 = new Territory(2, "Territory 1", 10, 1, 2, *p2);


    // Testing Deploy
    Deploy deploy;
   
    cout << "Executing INVALID deploy order" << endl;
    cout << "\tArmies before deploying" << t2->getNumberOfOccupyingArmies() << endl;
    deploy.execute(p, 10, t2);
    cout << "\tArmies after deploying" << t2->getNumberOfOccupyingArmies() << endl;

    cout << "Executing VALID deploy order" << endl;
    cout << "\tArmies before deploying" << t1->getNumberOfOccupyingArmies() << endl;
    deploy.execute(p, 10, t1);
    cout << "\tArmies after deploying" << t1->getNumberOfOccupyingArmies() << endl;
    cout << endl;


    // Testing bomb
    Bomb bomb;
   
    cout << "Executing INVALID bomb order" << endl;
    cout << "\tArmies before bombing" << t1->getNumberOfOccupyingArmies() << endl;
    bomb.execute(p, t1);
    cout << "\tArmies after bombing" << t1->getNumberOfOccupyingArmies() << endl;

    cout << "Executing VALID bomb order" << endl;
    cout << "\tArmies before bombing" << t2->getNumberOfOccupyingArmies() << endl; 
    bomb.execute(p, t2);
    cout << "\tArmies after bombing" << t2->getNumberOfOccupyingArmies() << endl;
    cout << endl;

     // Testing blockade
    Blockade blockade;
   
    cout << "Executing INVALID blockade order" << endl;
    cout << "\tOwner before blockading" << (t2->getOwner()) << endl;
    cout << "\tArmies before blockading" << t2->getNumberOfOccupyingArmies() << endl;
    blockade.execute(p, t2);
    cout << "\tOwner after blockading" << (t2->getOwner()) << endl;
    cout << "\tArmies after blockading" << t2->getNumberOfOccupyingArmies() << endl;

    cout << "Executing VALID blockade order" << endl;
    cout << "\tOwner before blockading" << (t1->getOwner()) << endl;
    cout << "\tArmies before blockading" << t1->getNumberOfOccupyingArmies() << endl;
    blockade.execute(p, t1);
    cout << "\tOwner after blockading" << (t1->getOwner()) << endl;
    cout << "\tArmies after blockading" << t1->getNumberOfOccupyingArmies() << endl;

    // Testing negotiate
    Negotiate negotiate;
    std::vector<Territory> attack({*t1, *t2});
    Player *p3 = new Player(std::string("Player 2"), attack, std::vector<Territory>(), Hand(), OrdersList());
    //Territory *t3 = new Territory(4, "Territory 4", 10, 1, 2, *p3);

    
    cout << "Executing INVALID negotiate order" << endl;
    negotiate.execute(p3, p3);

    cout << "Executing VALID negotiate order" << endl;
    negotiate.execute(p3, p2);
    bomb.execute(p3, t2);
    bomb.execute(p3, &((p3->toAttack())[1])); // attacklist[0] points to t2


    delete p;
    delete p2;
    delete p3;
    delete t1;
    delete t2;
}
