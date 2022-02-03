#include <iostream>
#include <cmath>
#include <stack>

#include "Node.h"

int main(int argc, char *argv[])
{
    // ==============\/ Entrada \/==================================

    int F, W;
    cin >> F >> W;

    Node *matrix[F][W];

    for (int i = 0; i < F; i++)
    {
        for (int j = 0; j < W; j++)
        {
            int value;
            cin >> value;
            Node *auxNode = new Node(value, j);
            /*
            ! Caso seja a primeira linha, em virtuda da mogelagem
            ! adotada para o problema a inicialização é diferente.
            */
            if (i == 0)
            {
                //? Na documentação isso é discutido mais profundamente.
                auxNode->setDistance(value);
            }
            else
            {
                matrix[i - 1][abs(j - 1)]->addNodePointer(auxNode);
                matrix[i - 1][j]->addNodePointer(auxNode);
                /*
                ? Se j+1 ==W isso significa que esse index estará fora do
                ? intervalo da matriz, nesse caso, não é criada a conexão.
                */
                if (j + 1 != W)
                    matrix[i - 1][j + 1]->addNodePointer(auxNode);
            }
            matrix[i][j] = auxNode;
        }
    }

    // ==============\/ Bellman-Ford-Moore Algorithm \/=============

    /*
    ! Como o grafo é construido em camadas, uma única iteração é o
    ! suficiente, por esse motivo nessa aplicação não se itera n-1
    ! vezes sobre o grafo.
    */

    /*
    ! Itera sobre a matriz pra evitar gastar mais memória realocando
    ! os mesmos elementos para um vetor. Isso tem o mesmo custo de
    ! iterar sobre o vetor apesar dos dois loops.
    */
    for (int y = 0; y < F; y++)
    {
        for (int x = 0; x < W; x++)
        {
            Node *matrixXY = matrix[y][x];
            vector<Node *> nodes = matrixXY->getNodePointers();
            int nodesSize = nodes.size();
            for (int j = 0; j < nodesSize; j++)
            {
                int currentDistance = nodes[j]->getDistance();
                int distanceViaMatrixXY = matrixXY->getDistance() + nodes[j]->getOutLength();
                if (currentDistance < distanceViaMatrixXY)
                {
                    nodes[j]->setDistance(distanceViaMatrixXY);
                    nodes[j]->setNext(matrixXY);
                }
            }
        }
    }

    // ==============\/ Saída \/====================================

    /*
    ! Como a distância é calculada de cima abaixo se checa na última
    ! linha qual o vertice com maior distância, a partir dele se extrai
    ! o caminho e o coloca na saída padrão.
    */

    // Acha o node com maior distância.
    Node *max = matrix[F - 1][0];
    for (int i = 1; i < W; i++)
    {
        if (matrix[F - 1][i]->getDistance() > max->getDistance())
            max = matrix[F - 1][i];
    }

    // Converte o caminho usando uma stack
    Node *next = max->getNext();
    stack<int> path;
    path.push(max->getY());
    while (next != NULL)
    {
        path.push(next->getY());
        next = next->getNext();
    }

    // Coloca a saída completa na saída padrão
    cout << max->getDistance() << endl;
    while (!path.empty())
    {
        cout << path.top() << " ";
        path.pop();
    }
    cout<<endl;

    return 0;
}
