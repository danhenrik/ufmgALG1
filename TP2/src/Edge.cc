#include "Edge.h"

Edge::Edge(double len, Store *storeA, Store *storeB)
{
  this->length = len;
  this->storeA = storeA;
  this->storeB = storeB;
}

double Edge::getLength()
{
  return this->length;
}

Store *Edge::getStoreA()
{
  return this->storeA;
}
Store *Edge::getStoreB()
{
  return this->storeB;
}

bool Edge::operator<(const Edge &compared)
{
  return this->length < compared.length;
}

void Edge::setLength(double value)
{
  this->length = value;
}