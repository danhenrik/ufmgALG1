#ifndef STATE
#define STATE

#include <string>

using namespace std;

class State
{
public:
  State(){};
  // Inicializa uma instância da classe com os atributos passados
  State(string name, int score);

  // Getters - Creio que dispensa explicação
  int getScore();

private:
  string name;
  int score;
};

#endif