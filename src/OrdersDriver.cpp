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

   cout << "Executing VALID deploy order" << endl;
   deploy.execute(p, 10, t1);
   cout << "Executing INVALID deploy order" << endl;
   deploy.execute(p, 10, t2);
}
