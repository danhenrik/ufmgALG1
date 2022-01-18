#ifndef EDGE
#define EDGE

#include "Store.h"

class Edge
{
public:
  Edge(){};
  // Inicializa uma instância da classe com os atributos passados
  Edge(double len, Store *storeA, Store *storeB);

  // Getters - Creio que dispensa explicação
  Store *getStoreA();
  Store *getStoreB();
  double getLength();

  // Para que seja possível usar o método 'sort' na lista de arestas
  bool operator<(const Edge &compared);

private:
  Store *storeA;
  Store *storeB;
  double length;
};

#endif