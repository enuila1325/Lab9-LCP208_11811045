#ifndef GUN_H
#define GUN_H
#include <iostream>
using namespace std;
class Gun
{
private:
   string type;
   int damage;
   double price;

public:
   Gun(){};
   Gun(string _type, int _damage, double _price)
   {
      this->type = _type;
      this->damage = _damage;
      this->price = _price;
   }
   void set_type(string);
   void set_damage(int);
   void set_price(double);
   string get_type();
   int get_damage();
   double get_price();
};
#endif