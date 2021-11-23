#ifndef STORE
#define STORE

class Client;
#include <list>
#include "Client.h"

using namespace std;

class Store
{
public:
  Store(){};
  // Inicializa uma instância da classe com os atributos passados
  Store(int id, int stock, int cordX, int cordY);

  // Getters - Creio que dispensa explicação
  int getId();
  int getStocks();
  int getX();
  int getY();
  list<Client *> getMatchings();
  int getMatchingCount();
  bool getFinished();

  // Seta finished pra true
  void setFinished();
  // Seta finished pra false
  void setUnfinished();

  // Adiciona o cliente passado a lista de matchings
  void addMatching(Client *client);
  // Remove o cliente passado da lista de matchings
  void removeMatching(Client *client);

private:
  int id;
  int stock;
  int cordX;
  int cordY;
  list<Client *> matchings;
  int matchingCount;
  bool finished;
};

#endif