#include "Store.h"

Store::Store(int id, int stock, int cordX, int cordY)
{
  this->id = id;
  this->stock = stock;
  this->cordX = cordX;
  this->cordY = cordY;
  this->matchingCount = 0;
  this->finished = false;
}

int Store::getId()
{
  return this->id;
}

int Store::getStocks()
{
  return this->stock;
}

int Store::getX()
{
  return this->cordX;
}

int Store::getY()
{
  return this->cordY;
}

list<Client *> Store::getMatchings()
{
  return this->matchings;
}

int Store::getMatchingCount()
{
  return this->matchingCount;
}

bool Store::getFinished()
{
  return this->finished;
}

void Store::setFinished()
{
  this->finished = true;
}

void Store::setUnfinished()
{
  this->finished = false;
}

void Store::addMatching(Client *client)
{
  this->matchings.push_back(client);
  this->matchingCount++;
  if (this->matchingCount == this->stock)
    this->finished = true;
}

void Store::removeMatching(Client *client)
{
  this->matchings.remove(client);
  this->matchingCount--;
  if (this->finished)
    this->finished = false;
}