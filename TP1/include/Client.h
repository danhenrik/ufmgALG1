#ifndef CLIENT
#define CLIENT

class Store;
#include "Store.h"
#include "State.h"
#include "PaymentMethod.h"

using namespace std;

class Client
{
public:
  Client(){};
  // Inicializa uma instância da classe com os atributos passados
  Client(int id, int age, State state, PaymentMethod payment, int cordX, int cordY);

  // Getters - Creio que dispensa explicação
  int getId();
  int getAge();
  State getState();
  PaymentMethod getPayment();
  int getX();
  int getY();
  float getTicket();
  Store *getMatching();
  int getMatchingDistance();
  bool getInit();

  // Seta o matching do cliente para uma nova loha, armazenando também
  // sua distância até ali, isso é feito pra facilitar a consulta do 
  // outro lado
  void setMatching(Store *store, int distance);

private:
  int id;
  int age;
  State *originState;
  PaymentMethod *paymentMethod;
  int cordX;
  int cordY;
  float ticket;
  Store *matching;
  int matchingDistance;
  bool initialized;

  void calculateTicket();
};

#endif
