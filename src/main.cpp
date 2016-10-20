#include <iostream>
#include "headerlist.hpp"

using namespace std;

int main()
{
    GameEntity g1 ({1, 1},{2, 2},"al", 30, 10);
    Bullet b1 ({1,1}, {2,2}, 15);
    BulletManager bm1;
    shared_ptr<Bullet> b1_ptr(new Bullet(b1));
    bm1.SetAmmo(b1_ptr, 5);
    shared_ptr<BulletManager> bm1_ptr(new BulletManager(bm1));
    g1.SetBulletManager(bm1_ptr);
    //cout << g1.GetBulletManager().GetAmmo(b1_ptr) << endl;
    /*try{
    Alien a1 ({1,1}, {2,2}, 30, 5, 3, 3);
    }
    catch (std::exception const & ex)
    {
      std::cerr << ex.what();
    }
    catch(...)
    {
      std::cerr << "error";
    }
    int t = 30;
    unsigned s = t;
    cout << s;
    return 0;*/
    Box2D b({1,1},{2,2});
    b /= 0;
    cout<<b;
}
