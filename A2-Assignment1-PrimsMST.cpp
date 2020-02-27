#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>
using namespace std;

struct node;

struct edge{
  int cost = 0;
  node* a = NULL;
  node* b = NULL;
};

struct node{
  vector<edge*> connections;
};

vector<node*> nodes;

int main()
{
  fstream f("test.txt");
  int NODES, EDGES;
  f>>NODES>>EDGES;
  for(int i = 0; i<NODES; ++i)
  {
    nodes.push_back(new node);
  } 
  int n1,n2,cost;
  for(int i = 0; i<EDGES; ++i)
  {
    f>>n1>>n2>>cost;
    edge* e = new edge;
    e->a = nodes[n1-1];
    e->b = nodes[n2-1];
    e->cost = cost;
  }

}
