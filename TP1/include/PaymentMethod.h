#ifndef PAYMENT_METHOD
#define PAYMENT_METHOD

#include <string>

using namespace std;

class PaymentMethod
{
public:
  PaymentMethod(){};
  // Inicializa uma instância da classe com os atributos passados
  PaymentMethod(string name, int score);

  // Getters - Creio que dispensa explicação
  int getScore();

private:
  string name;
  int score;
};

#endif