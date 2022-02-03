#ifndef NODE
#define NODE

#include <vector>

using namespace std;

class Node
{
public:
  Node(){};
  /**
   * Inicializa uma instância da classe com os atributos passados
   */
  Node(int outLen, int cordY);

  /**
   * Adiciona um node que aponta para essa instância
   */
  void addNodePointer(Node *node);
  /**
   * Retorna todos os nodes que apontam para essa instância
   */
  vector<Node *> getNodePointers();

  /**
   * Seta o valor do campo distância
   */
  void setDistance(int distance);
  /**
   * Retorna a distância
   */
  int getDistance();

  /**
   *  Seta qual o próximo vetor no caminho sendo criado
   */
  void setNext(Node *node);
  /**
   *  Retorna o próximo vetor no caminho
   */
  Node *getNext();

  // Getters - Creio que dispensam explicação
  int getOutLength();
  int getY();

private:
  int outLength;
  int cordY;

  int distance;
  Node *next;
  vector<Node *> pointedBy;
};

#endif