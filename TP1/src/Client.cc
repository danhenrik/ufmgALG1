#include "Client.h"

Client::Client(int id, int age, State state, PaymentMethod payment, int cordX, int cordY)
{
  this->id = id;
  this->age = age;
  this->originState = &state;
  this->paymentMethod = &payment;
  this->cordX = cordX;
  this->cordY = cordY;
  this->calculateTicket();
  this->initialized = false;
}

int Client::getId()
{
  return this->id;
}

int Client::getAge()
{
  return this->age;
}

State Client::getState()
{
  return *this->originState;
}

PaymentMethod Client::getPayment()
{
  return *this->paymentMethod;
}

int Client::getX()
{
  return this->cordX;
}

int Client::getY()
{
  return this->cordY;
}

float Client::getTicket()
{
  return this->ticket;
}

Store *Client::getMatching()
{
  return this->matching;
}

int Client::getMatchingDistance()
{
  return this->matchingDistance;
}

bool Client::getInit()
{
  return this->initialized;
}

void Client::setMatching(Store *store, int distance)
{
  this->matching = store;
  this->matchingDistance = distance;
  this->initialized = true;
}

void Client::calculateTicket()
{
  this->ticket = ((abs(60 - this->age) + this->originState->getScore()) / float(this->paymentMethod->getScore()));
}
