#include "PaymentMethod.h"

PaymentMethod::PaymentMethod(string name, int score)
{
  this->name = name;
  this->score = score;
}

int PaymentMethod::getScore()
{
  return this->score;
}