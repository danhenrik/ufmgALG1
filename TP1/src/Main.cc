#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

#include <map>
#include <set>

#include "Store.h"
#include "Client.h"

using namespace std;

// Calcula a distância entre uma loja e um cliente em quadrados de distância
int computeDistance(Store store, Client client)
{
    int xC = client.getX();
    int yC = client.getY();
    int xS = store.getX();
    int yS = store.getY();

    int dx = abs(xC - xS);
    int dy = abs(yC - yS);

    int min = fmin(dx, dy);
    int max = fmax(dx, dy);

    int diagonalSteps = min;
    int straightSteps = max - min;

    return diagonalSteps + straightSteps - 1;
}

void Particao(Client *A, int Esq, int Mid, int Dir)
{
    int EsqArrSize = Mid - Esq + 1;
    int DirArrSize = Dir - Mid;

    // Cria as arrays auxiliares
    Client *valuesL = new Client[EsqArrSize];
    Client *valuesR = new Client[DirArrSize];

    // Divide os dados entre as duas arrays
    for (int i = 0; i < EsqArrSize; i++)
        valuesL[i] = A[Esq + i];
    for (int j = 0; j < DirArrSize; j++)
        valuesR[j] = A[Mid + 1 + j];

    int indexValuesL = 0;
    int indexValuesR = 0;
    int indexA = Esq;

    // Junta as duas arrays de volta a array principal de acordo com os valores do ticket.
    while (indexValuesL < EsqArrSize && indexValuesR < DirArrSize)
    {
        if (valuesL[indexValuesL].getTicket() >= valuesR[indexValuesR].getTicket())
        {
            A[indexA] = valuesL[indexValuesL];
            indexValuesL++;
        }
        else
        {
            A[indexA] = valuesR[indexValuesR];
            indexValuesR++;
        }
        indexA++;
    }
    while (indexValuesL < EsqArrSize)
    {
        A[indexA] = valuesL[indexValuesL];
        indexValuesL++;
        indexA++;
    }
    while (indexValuesR < DirArrSize)
    {
        A[indexA] = valuesR[indexValuesR];
        indexValuesR++;
        indexA++;
    }
}

void Merge(Client *A, int Esq, int Dir)
{
    if (Esq >= Dir)
        return; // Condição de parada da recursão
    int Mid = Esq + (Dir - Esq) / 2;
    Merge(A, Esq, Mid);
    Merge(A, Mid + 1, Dir);
    Particao(A, Esq, Mid, Dir);
}

void MergeSort(Client *A, int len)
{
    Merge(A, 0, len - 1);
}

int main(int argc, char *argv[])
{
    // ==============\/ Criação Estados e Métodos de pagamento \/===

    map<string, State> stateMap;
    stateMap["MG"] = State("MG", 0);
    stateMap["PR"] = State("PR", 10);
    stateMap["SP"] = State("SP", 20);
    stateMap["SC"] = State("SC", 30);
    stateMap["RJ"] = State("RJ", 40);
    stateMap["RN"] = State("RN", 50);
    stateMap["RS"] = State("RS", 60);

    map<string, PaymentMethod> paymentMap;
    paymentMap["DINHEIRO"] = PaymentMethod("MONEY", 1);
    paymentMap["DEBITO"] = PaymentMethod("DEBIT", 2);
    paymentMap["CREDITO"] = PaymentMethod("CREDIT", 3);

    // ==============\/ Entrada tamanho do grid \/==================

    int gridX, gridY;
    cin >> gridX >> gridY;

    // ==============\/ Entrada lojas \/============================

    int storeCount;
    cin >> storeCount;
    Store stores[storeCount];

    int i = 0;
    while (i < storeCount)
    {
        int stock, cordX, cordY;
        cin >> stock >> cordX >> cordY;
        if (cordX > gridX || cordY > gridY || cordX < 0 || cordY < 0)
            throw "Coordinates either too large or too small for grid";
        stores[i] = Store(i, stock, cordX, cordY);
        i++;
    }

    // ==============\/ Entrada clientes \/=========================

    int clientCount;
    cin >> clientCount;
    Client clients[clientCount];

    i = 0;
    while (i < clientCount)
    {
        int age, cordX, cordY;
        string stateName, paymentName;
        cin >> age >> stateName >> paymentName >> cordX >> cordY;
        State state = stateMap.at(stateName);
        PaymentMethod paymentMethod = paymentMap.at(paymentName);
        if (cordX > gridX || cordY > gridY || cordX < 0 || cordY < 0)
            throw "Coordinates either too large or too small for grid";
        clients[i] = Client(i, age, state, paymentMethod, cordX, cordY);
        i++;
    }

    // ==============\/ Criação listas de prioridade lojas \/=======

    MergeSort(clients, clientCount);

    // ==============\/ GS - Gale Shapley \/========================

    set<Store *> completedSet;
    i = 0;
    // Enquanto tiver ao menos uma loja não finalizada, itera sobre as lojas
    while (int(completedSet.size()) < storeCount)
    {
        Store *store = &stores[i];
        // Pra pular lojas já completadas
        if (store->getFinished())
        {
            i++;
            if (i == storeCount)
                i = 0;
            continue;
        }
        // Itera sobre os clientes da lista de preferência (global entre as lojas) até encontrar um
        // que aceite ou não encontrar ninguém
        int j = 0;
        while (j < clientCount)
        {
            Client *client = &clients[j];

            int distance = computeDistance(*store, *client);
            int matchingDistance = client->getMatchingDistance();

            // Se o cliente não estiver inicializado ele ainda não tem matching e por isso aceita a loja
            if (!client->getInit())
            {
                client->setMatching(store, distance);
                store->addMatching(client);
                break;
            }
            // Se a distância pra essa loja for menor que pra loja que ele ja esta alocado ele
            // prefere ela e por isso aceita
            else if (distance < matchingDistance)
            {
                Store *oldMatching = client->getMatching();
                if (oldMatching->getFinished())
                    completedSet.erase(oldMatching);
                oldMatching->removeMatching(client);
                client->setMatching(store, distance);
                store->addMatching(client);
                break;
            }
            // Critério de desempate, caso as distâncias sejam iguais prevalece a loja de menor id
            // Quanto a outro critério de desempate, pelo uso do mergesort(estável), os clientes de
            // menor id já vem primeiro e não precisamos nos preocupar com esse caso específico.
            else if (distance == matchingDistance)
            {
                Store *currentMatching = client->getMatching();
                if (store->getId() < currentMatching->getId())
                {
                    if (currentMatching->getFinished())
                        completedSet.erase(currentMatching);
                    currentMatching->removeMatching(client);
                    client->setMatching(store, distance);
                    store->addMatching(client);
                    break;
                }
            }
            j++;
            // Caso passem todos os clientes e nenhum aceite a loja, isso significa que esta loja
            // não esta nas preferências de mais ninguem, e como o cliente n vai descer na sua
            // prioridade, essa é uma loja considerada completa.
            if (j == clientCount)
                store->setFinished();
        }
        // Se ao adicionar um cliente a loja bate estoque == matchings coloca ela no set de lojas finalizadas.
        if (store->getFinished())
            completedSet.insert(store);

        // Faz com que o loop fique dando voltas nas lojas, formando um tipo de anel.
        i++;
        if (i == storeCount)
            i = 0;
    }

    // ==============\/ Formatação e saída \/=======================

    for (int i = 0; i < storeCount; i++)
    {
        Store store = stores[i];
        cout << store.getId() << endl;
        list<Client *> matchings = store.getMatchings();
        cout << matchings.front()->getId();
        matchings.pop_front();
        while (!matchings.empty())
        {
            cout << " " << matchings.front()->getId();
            matchings.pop_front();
        };
        cout << endl;
    }

    return 0;
}
