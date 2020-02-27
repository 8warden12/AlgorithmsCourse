#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <set>
#include <assert.h>
#include <chrono>
#include <thread>
using namespace std;

struct node;
 int DISCOVERED = 0;
struct edge{
  int cost = 0;
  node* a = NULL;
  node* b = NULL;
  bool used = false;
};

/*
tested:
3704858
-3612829 WORKS
*/

struct edgeComp{
  bool operator()(const edge* a, const edge* b)
  {
    if(a->cost < b->cost)
    return true;

    return false;
  }
};

struct node{
  vector<edge*> connections;
  bool discovered = false;
};

vector<node*> nodes;

multiset<edge*,edgeComp> pioneers;

int totalCost = 0;

void iterate()
{
  
  assert(pioneers.size() > 0);
  
  edge* e = *pioneers.begin();
  pioneers.erase(pioneers.begin());
  
  if(!e->a->discovered)
  {
    ++DISCOVERED;
    totalCost += e->cost;
    e->used = true;
    e->a->discovered = true;
    for(int i = 0; i<e->a->connections.size(); ++i)
    {
        if(e->a->connections[i]->used == false)
        {
          pioneers.insert(e->a->connections[i]);
        }
    }
  }else if(!e->b->discovered)
  {
    ++DISCOVERED;
    totalCost += e->cost;
     e->used = true;
    e->b->discovered = true;
    for(int i = 0; i<e->b->connections.size(); ++i)
    {
        if(e->b->connections[i]->used == false)
        {
          pioneers.insert(e->b->connections[i]);
        }
    }
  }

  assert(e->a->discovered && e->b->discovered);
}

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
    nodes[n1-1]->connections.push_back(e);
    nodes[n2-1]->connections.push_back(e);
  }

  nodes[0]->discovered = true;
  for(int i = 0; i<nodes[0]->connections.size(); ++i)
  {
    pioneers.insert(nodes[0]->connections[i]);
  }

 DISCOVERED = 1;
  for(;;)
  {
    if(DISCOVERED == nodes.size())
    break;
    iterate();
    printf("%d\n",totalCost);
   // printf("%d %d %d\n",DISCOVERED,nodes.size(),pioneers.size());
   std::this_thread::sleep_for(std::chrono::milliseconds(2));
  }
  printf("Total cost: %d\n",totalCost);

}
