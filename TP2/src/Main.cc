#include <iostream>
#include <cmath>
#include <list>

#include "Store.h"
#include "Edge.h"

using namespace std;

// Calcula a distância cartesiana entre duas lojas.
double computeDistance(Store store1, Store store2)
{
    int xS1 = store1.getX();
    int yS1 = store1.getY();
    int xS2 = store2.getX();
    int yS2 = store2.getY();

    return sqrt(pow(xS1 - xS2, 2) + pow(yS1 - yS2, 2));
}

int main(int argc, char *argv[])
{
    // ==============\/ Entradas \/=================================

    int storeCount, motorcycleKmLimit, droneCount, costPerMotorcycleKm, costPerTruckKm;
    cin >> storeCount >> motorcycleKmLimit >> droneCount >> costPerMotorcycleKm >> costPerTruckKm;

    if (motorcycleKmLimit > 10000)
        throw "A distancia percorrida por motocicletas passa dos limites estipulados";
    if (droneCount >= storeCount)
        throw "Pode-se existir no maximo N drones";
    if (costPerTruckKm > 10)
        throw "O custo por kilometro do caminhao nao pode ser maior que 10";
    if (costPerMotorcycleKm < 1)
        throw "O custo por kilometro da moto nao pode ser menor que 1";
    if (costPerMotorcycleKm > costPerTruckKm)
        throw "O custo por kilometro da moto nao pode ser maior que a do caminhao";

    Store stores[storeCount];
    for (int i = 0; i < storeCount; i++)
    {
        int positionX, positionY;
        cin >> positionX >> positionY;
        stores[i] = Store(i, positionX, positionY);
    }

    // ==============\/ Calcula todas as distãncias \/==============

    // Calcula as arestas do grafo computando a distância entre todas
    // as lojas
    list<Edge> edges;
    for (int i = 0; i < storeCount; i++)
    {
        Store *store = &stores[i];
        for (int j = i + 1; j < storeCount; j++)
        {
            Store *auxStore = &stores[j];
            double distance = computeDistance(*store, *auxStore);

            edges.push_back(Edge(distance, store, auxStore));
        }
    }

    // ==============\/ Kruskal algorithm \/========================

    // Coloca todos os vértices em um conjunto próprio
    list<Store *> sets[storeCount];
    for (int i = 0; i < storeCount; i++)
    {
        sets[i].push_back(&stores[i]);
    }

    // Ordena as arestas de acordo com a distância
    edges.sort();
    list<Edge *> MST;

    // Enquanto o tamanho do conjunto de arestas for menor que
    // o número de lojas - 1 a MST ainda não está completa
    unsigned int MSTEdges = storeCount - 1;
    while (MST.size() < MSTEdges)
    {
        // Pega a primeira aresta e puxa as lojas conectada por ela
        Edge *edge = &edges.front();
        edges.pop_front();

        Store *storeA = edge->getStoreA();
        Store *storeB = edge->getStoreB();

        // Se forem de grupos separados, adiciona a aresta a MST e
        // faz o  merge dos dois conjuntos da loja A e da loja B
        if (storeA->getGroup() != storeB->getGroup())
        {
            int aGroup = storeA->getGroup();
            list<Store *> *aSet = &sets[aGroup];

            int bGroup = storeB->getGroup();
            list<Store *> *bSet = &sets[bGroup];

            // Faz o merge dos dois conjuntos
            while (!bSet->empty())
            {
                Store *store = bSet->front();
                store->setGroup(aGroup);
                aSet->push_back(store);
                bSet->pop_front();
            }

            MST.push_back(edge);
        }
    }

    // ==============\/ Cálculo dos preços \/=======================

    double motorcycleTotalCost = 0, truckTotalCost = 0;

    // ---- Motos ----
    // Começa pelas arestas de menor distância e coloca moto enquanto for possível.
    while (!MST.empty())
    {
        Edge *edge = MST.front();
        double len = edge->getLength();
        if (len <= motorcycleKmLimit)
        {
            motorcycleTotalCost += len * costPerMotorcycleKm;
            MST.pop_front();
        }
        else
            break;
    }

    // ---- Drones ----
    // Exclui os últimos D-1 elementos da MST (maiores arestas) gerando D 
    // subconjuntos (MSTs) de lojas que são conectadas por drones (exemplo 
    // dado no enunciado do trabalho, Secção 6, Pg. 4, Figura 2).
    MST.resize(MST.size() - (droneCount - 1));

    // ---- Caminhões ----
    // O que sobrar vai de caminhão
    while (!MST.empty())
    {
        Edge *edge = MST.back();
        MST.pop_back();

        double len = edge->getLength();
        truckTotalCost += len * costPerTruckKm;
    }

    // ==============\/ Formatação e saída \/=======================

    cout.precision(3);
    cout << fixed << motorcycleTotalCost << " " << truckTotalCost << endl;

    return 0;
}
