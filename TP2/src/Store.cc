#include "Store.h"

Store::Store(int id, int cordX, int cordY)
{
  if (cordX < -10000 || cordX > 10000 || cordY < -10000 || cordY > 10000)
    throw "Loja fora dos limites";
  this->id = id;
  this->cordX = cordX;
  this->cordY = cordY;
  this->group = id;
}

int Store::getId()
{
  return this->id;
}

int Store::getX()
{
  return this->cordX;
}

int Store::getY()
{
  return this->cordY;
}

void Store::setGroup(int newGroup)
{
  this->group = newGroup;
}

int Store::getGroup()
{
  return this->group;
}
