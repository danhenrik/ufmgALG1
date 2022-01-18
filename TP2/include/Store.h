#ifndef STORE
#define STORE

class Store
{
public:
  Store(){};
  // Inicializa uma instância da classe com os atributos passados
  Store(int id, int cordX, int cordY);

  // Getters - Creio que dispensa explicação
  int getId();
  int getX();
  int getY();

  // Setter e getter pro grupo da loja
  void setGroup(int newGroup);
  int getGroup();

private:
  int id;
  int cordX;
  int cordY;
  int group;
};

#endif