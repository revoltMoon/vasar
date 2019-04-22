//
//  main.cpp
//  Graphs
//
//  Created by Влад Купряков on 14/04/2019.
//  Copyright © 2019 Влад Купряков. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int used[99];
int maxNodes[99];
int maxxNodes[99];
int i, ptr;
#define nodesMax 99 // Количество вершин
#define edgesMax 784
#define secondNodesMax 75
#define secondEdgesMax 748
int matrix[nodesMax][nodesMax]; // Матрица смежности
int matrixTrans[nodesMax][nodesMax];
int maxMatrix[secondNodesMax][secondNodesMax];
int nodesCount = 1;
int maxNodesCount = 0;
ifstream fin("edgesOr.txt"), fin2("nodes.txt");
ofstream fout("maxEdges.txt"), fout2("Maxnodes.txt");
string edges[edgesMax]; // Ребра Из;В
string secondEdges[secondEdgesMax];
int nodeFrom[edgesMax]; // Вершина, из которой шли
int nodeTo[edgesMax]; // Вершина, в которую пришли
int nodes[nodesMax]; // Вершины

int secondNodeFrom[secondEdgesMax];
int secondNodeTo[secondEdgesMax];

int secondNodes[secondNodesMax];

vector<int> order, component;

void dfs(int v)

{
    used[v] = 1;
    maxxNodes[v] = 1;
    printf("Vertex %d is visited\n",v);
    
    for (int i = 0; i <nodesMax; i++)
        if (matrix[v][i] && !used[i]) {
            nodesCount++;
            dfs(i);
        }
}

void dfs1 (int v) {
    
    used[v] = 1;
    
    for (int i = 0; i <nodesMax; i++)
        if (matrix[v][i] && !used[i])
            dfs1(i);
    
    order.push_back (v);
}

void dfs2 (int v) {
    used[v] = 1;
    component.push_back (v);
    for (int i = 0; i <nodesMax; i++)
        if (matrixTrans[v][i] && !used[i])
            dfs2(i);
}

int MIN (int a, int b)
{
    return (a>b ? b : a);
}

int Diam()
{
    int **edge = new int *[secondNodesMax];
    for (int i = 0; i < secondNodesMax; i++)
        edge[i] = new int [secondNodesMax];
    for (int i = 0; i < secondNodesMax; i++)
    {
        for (int j = 0; j < secondNodesMax; j++) {
            edge[i][j] = maxMatrix[i][j];
            if (!edge[i][j])
                edge[i][j] = 10000;
        }
    }
    for (int k = 0; k < secondNodesMax; k++)
        for (int i = 0; i < secondNodesMax; i++)
            for (int j = 0; j < secondNodesMax; j++)
                if (i != j)
                    edge[i][j] = MIN(edge[i][j], edge[i][k]+edge[k][j]);
    for (int i = 0; i < secondNodesMax; i++) {
        for (int j = 0; j < secondNodesMax; j++) {
            if (edge[i][j] == 10000)
                edge[i][j] = 0;
        }
    }
    int max = edge[0][1];
    for(int i = 0; i < secondNodesMax; i++)
    {
        for (int j = i+1; j < secondNodesMax; j++) {
            if(edge[i][j] > max)
                max = edge[i][j];
        }
    }
    delete [] edge;
    return max;
}

int Radius()
{
    int **edge = new int *[nodesMax];
    for (int i = 0; i < nodesMax; i++)
        edge[i] = new int [nodesMax];
    for (int i = 0; i < nodesMax; i++)
        for (int j = 0; j < nodesMax; j++) {
            edge[i][j] = matrix[i][j];
            if (!edge[i][j])
                edge[i][j] = 10000;
        }
    for (int k = 0; k < nodesMax; k++)
        for (int i = 0; i < nodesMax; i++)
            for (int j = 0; j < nodesMax; j++)
                if (i != j)
                    edge[i][j] = MIN(edge[i][j], edge[i][k]+edge[k][j]);
    for (int i = 0; i < nodesMax; i++) {
        for (int j = 0; j < nodesMax; j++) {
            if (edge[i][j] == 10000)
                edge[i][j] = 0;
        }
    }
//    int min = edge[f][f+1];
//    for (int j = f+1; j < nodesMax; j++) {
//        if(edge[f][j] < min)
//            min = edge[f][j];
//    }
    int min = 10000;
    for(int i = 0; i < secondNodesMax; i++)
    {
        for (int j = i+1; j < secondNodesMax; j++) {
            if(edge[i][j] < min)
                min = edge[i][j];
        }
    }
    
    delete [] edge;
    
    return min;
}

void Centr()
{
//    for (int i=0;i<secondNodesMax;i++)
//        for (int j=0;j<secondNodesMax;j++) {
//            cout << maxMatrix[i][j] << " ";
//        }
    
    int **edge = new int *[secondNodesMax];
    
    for (int i = 0; i < secondNodesMax; i++)
        edge[i] = new int [secondNodesMax];
    for (int i = 0; i < secondNodesMax; i++)
        for (int j = 0; j < secondNodesMax; j++) {
            edge[i][j] = maxMatrix[i][j];
            if (!edge[i][j])
                edge[i][j] = 10000;
        }
    for (int k = 0; k < secondNodesMax; k++)
        for (int i = 0; i < secondNodesMax; i++)
            for (int j = 0; j < secondNodesMax; j++)
                if (i != j)
                    edge[i][j] = MIN(edge[i][j], edge[i][k]+edge[k][j]);
//    cout << "Расстояния: \n" << endl;
    for (int i = 0; i < secondNodesMax; i++) {
        for (int j = 0; j < secondNodesMax; j++) {
            if (edge[i][j] == 10000)
                edge[i][j] = 0;
//            cout << edge[i][j] << " ";
        }
//        cout << endl;
    }
    
    int summ = 0;
    int counter = 0;
    for (int i=0;i<secondNodesMax;i++)
        for (int j=0;j<secondNodesMax;j++) {
            if ((edge[i][j] != 0) && (i != j)) {
                summ += edge[i][j];
                counter++;
            }
        }
    
    cout << "Средняя длина пути: " << summ/counter << endl;
    
    
    
    int ecc[secondNodesMax];
    int max = 0;
    for (int i=0;i<secondNodesMax;i++) {
        for (int j=0;j<secondNodesMax;j++)
            if (edge[i][j] > max) max = edge[i][j];
        ecc[i] = max;
        if (ecc[i] == 0)
        max = 0;
    }
    
//    cout << "ecc: " << endl;
//    for (int i=0;i<secondNodesMax;i++) {
//        cout << ecc[i] << endl;
//    }
    
    int min = 10000;
    max = 0;
    
    for (int i=0;i<secondNodesMax;i++) {
        if ((ecc[i] < min) && (ecc[i] > 0)) min = ecc[i];
        if (ecc[i] > max) max = ecc[i];
    }
    
    cout << "Radius: " << min << endl;
    cout << "Diameter: " << max << endl;
    
    cout << "Центральные точки: " << endl;
    for (int i=0;i<secondNodesMax;i++) {
        if (ecc[i] == min) cout << secondNodes[i] << " ";
    }
    cout << endl;
    
    cout << "Периферийные точки: " << endl;
    
    for (int i=0;i<secondNodesMax;i++) {
        if (ecc[i] == max) cout << secondNodes[i] << " ";
    }
    
    cout << endl;
//    int min, max;
//    int *ecc = new int [secondNodesMax];
//    int *rad = new int [secondNodesMax];
//    int *deg = new int [secondNodesMax];
//    for (int i = 0; i < secondNodesMax; i++) {
//        rad[i] = ecc[i] = deg[i] = 0;
//        min = edge[i][i+1];
//        max = edge[i][i+1];
//        for (int j = i+1; j < secondNodesMax; j++) {
//            if(edge[i][j] < min)
//            {
//                min = edge[i][j];
//            }
//            if(edge[i][j] > max)
//                max = edge[i][j];
//        }
//        deg[i] = min;
//        ecc[i] = max;
//    }
//    int j = 0;
//
//    for(int i = 0; i < secondNodesMax; i++)
//    {
//        if(deg[i] == ecc[i]) {
//            rad[j++] = i;
//        }
//    }
//    cout << "\n";
//    cout << "Центры графа: ";
//    for(int i = 0; i < j; i++)
//        cout << rad[i] << " ";
//    delete [] edge;
//    delete [] deg;
//    delete [] rad;
//    delete [] ecc;
}

int main()
{
    for (int i=0;i<nodesMax;i++)
        for (int j=0;j<nodesMax;j++) {
            matrix[i][j] = 0;
            matrixTrans[i][j] = 0;
            used[i] = 0;
            maxxNodes[i] = 0;
            maxNodes[i] = 0;
        }
    
    if(fin.is_open())
    {
        string a;
        int k=0;
        while (fin >> a) {
            edges[k] = a;
            char str[30];
            strcpy(str, a.c_str());
            char *ptr = 0;
            ptr = strtok(str,";");
            nodeFrom[k] = stoi(string(ptr));
//            cout << "from: " << edgesFrom[k] << "\n";
            while (ptr){
                nodeTo[k] = stoi(string(ptr));
//                cout << "to: " << edgesTo[k] << "\n";
                ptr = strtok(0,";");
            }
            k++;
        }
    }
    
    if(fin2.is_open())
    {
        string a;
        int k=0;
        while (fin2 >> a) {
            a.erase(a.find(';'), 1);
            nodes[k] = stoi(a);
            k++;
        }
    }
    
    for (int i=0; i<nodesMax; i++)
        for (int k=0; k<edgesMax; k++) {
            if (nodes[i] == nodeFrom[k]) {
                for (int h=0;h<nodesMax;h++) {
                    if (nodes[h] == nodeTo[k]) {
                        matrix[i][h] = 1;
                        matrixTrans[h][i] = 1;
                    }
                }
            }
        }
    
//    for (int i=0;i<nodesMax;i++) {
//        for (int j=0;j<nodesMax;j++) {
//            fout << matrix[i][j] << " ";
//        }
//        fout << "\n";
//    }
    
    int componentsCount = 0;
    for (int i=0; i<nodesMax; i++) {
        if (!used[i]) {
            
            cout << "Количество вершин в текущей компоненте: " << nodesCount << "\n";
            
            cout << "Новая компонента связности" << "\n";
            
            componentsCount++;
            
            if (nodesCount > maxNodesCount) {
                maxNodesCount = nodesCount;
                for (int i=0;i<nodesMax;i++) maxNodes[i] = 0;
                for (int i=0;i<nodesMax;i++)
                    if (maxxNodes[i] == 1)
                        maxNodes[i] = 1;
            }
            
            for (int i=0;i<nodesMax;i++) maxxNodes[i] = 0;
            
            nodesCount = 1;
            dfs(i);
        }
    }
    cout << "Число компонент слабой связности: " << componentsCount << "\n";
    cout << "Максимальное число вершин в компоненте: " << maxNodesCount << "\n";
    
    order.clear();
    
    for (int i=0;i<nodesMax;i++)
        used[i] = 0;
    
    for (int i=0; i<nodesMax; i++)
        if (!used[i])
            dfs1(i);
    
    for (int i=0; i<nodesMax; i++)
        used[i] = 0;
    
    componentsCount = 0;
    
    for (int i=0; i<nodesMax; ++i) {
        int v = order[nodesMax-1-i];
        if (!used[v]) {
            componentsCount++;
            dfs2 (v);
//            for(int i=0; i<component.size(); i++)
//                cout << component[i] << ' ';
            component.clear();
        }
    }
    
    cout << "Число сильнейших компонент: " << componentsCount << "\n";
    
    for (int i=0;i<75;i++)
        for (int j=0; j<75; j++) {
            maxMatrix[i][j] = 0;
        }
    
    for (int j=0;j<nodesMax;j++) {
        if (maxNodes[j] == 0) {
            for (int i=0; i<edgesMax;i++) {
                if ((nodeFrom[i] == nodes[j]) || (nodeTo[i] == nodes[j])) {
                    nodeFrom[i] = 10000;
                    nodeTo[i] = 10000;
                }
            }
        }
    }
    
    
    
    for (int i=0;i<edgesMax;i++) {
        if (nodeFrom[i] != 10000)
            fout << nodeFrom[i] << ";" << nodeTo[i] << "\n";
    }
    
    for (int i=0;i<nodesMax;i++)
        if (maxNodes[i] == 1)
            fout2 << nodes[i] << ";\n";
    
    
    
    fout.close();
    fout2.close();
    ifstream fin3("maxEdges.txt"), fin4("Maxnodes.txt");
    
    for (int i=0;i<secondNodesMax;i++)
        for (int j=0;j<secondNodesMax;j++) {
            maxMatrix[i][j] = 0;
            secondNodes[i] = 0;
        }
    
    for (int i=0;i<secondEdgesMax;i++) {
        secondNodeFrom[i] = 0;
        secondNodeTo[i] = 0;
    }
    
    if(fin3.is_open())
    {
        string a;
        int k=0;
        while (fin3 >> a) {
            secondEdges[k] = a;
            char str[30];
            strcpy(str, a.c_str());
            char *ptr = 0;
            ptr = strtok(str,";");
            secondNodeFrom[k] = stoi(string(ptr));
            //            cout << "from: " << edgesFrom[k] << "\n";
            while (ptr){
                secondNodeTo[k] = stoi(string(ptr));
                //                cout << "to: " << edgesTo[k] << "\n";
                ptr = strtok(0,";");
            }
            k++;
        }
    }
    
    if(fin4.is_open())
    {
        string a;
        int k=0;
        while (fin4 >> a) {
            a.erase(a.find(';'), 1);
            secondNodes[k] = stoi(a);
            k++;
        }
    }
    
    for (int i=0; i<secondNodesMax; i++)
        for (int k=0; k<secondEdgesMax; k++) {
            if (secondNodes[i] == secondNodeFrom[k]) {
                for (int h=0;h<secondNodesMax;h++) {
                    if (secondNodes[h] == secondNodeTo[k]) {
                        maxMatrix[i][h] = 1;
                    }
                }
            }
        }
    
    int nodesStepen[secondNodesMax];
    for (int i=0;i<secondNodesMax;i++)
        nodesStepen[i] = 0;
    
    int counter = 0;
    for (int i=0;i<secondNodesMax;i++) {
            for (int j=0;j<secondNodesMax;j++) {
                if (maxMatrix[i][j] == 1)
                    counter++;
            }
            nodesStepen[i] = counter;
            counter = 0;
        }
    
    counter = 0;
    int summ=0;
    for (int i=0;i<secondNodesMax;i++)
        if (nodesStepen[i] > 0) {
            summ += nodesStepen[i];
            counter++;
        }
    cout << "Средняя степень вершины: " << summ/counter << "\n";
    
    int gistogramma[secondNodesMax];
    
    for (int i=0; i<secondNodesMax;i++)
        gistogramma[i] = 0;
    
    cout <<  "Гистограмма: " << endl;
    for (int i=0;i<secondNodesMax;i++)
        if (nodesStepen[i] != 0)
            gistogramma[nodesStepen[i]]++;
    
    for (int i=0;i<secondNodesMax;i++)
        if (gistogramma[i] != 0)
            cout << "Вершин со степенью " << i << ": " << gistogramma[i] << endl;
    
    Centr();
    
    fin.close();
    fin2.close();
    fin3.close();
    fin4.close();
    
    return 0;
}
