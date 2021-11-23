#include "State.h"

State::State(string name, int score)
{
  this->name = name;
  this->score = score;
}

int State::getScore()
{
  return this->score;
}