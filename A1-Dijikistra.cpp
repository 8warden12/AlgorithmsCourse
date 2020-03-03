#include <stdio.h>
#include <assert.h>
#include <vector>
#include <iostream>
#include <sstream>//klashdklashdjkashdkjhaskjdhakjsdhjkasdasdasd
#include <fstream>
using namespace std;

struct node;

struct edge{
  node* sender;
  node* receiver;
  int weight;
};

struct node{
  vector<edge*> outbound;
  vector<edge*> inbound;
  int shortestPath;
};


vector<node*> nodes;


void connect(node* sender, node* receiver, int weight)
{
  edge* e = new edge;
  e->weight = weight;
  e->receiver = receiver;
  e->sender = sender;
  sender->outbound.push_back(e);
  receiver->inbound.push_back(e);
}

int main()
{
  for(int i = 0; i<200; ++i)
  {
    nodes.push_back(new node);
  }

 fstream f("dijkstraData.txt");

  string s;
  stringstream ss;

  int sender,receiver,weight;

for(int i = 0; i<200; ++i)
{
  for(;;)
  {
    getline(f,s);
    ss.clear();
    ss.str("");
    ss<<s;
    
    
    
    for(;;)
    {
      
    }
  }
}

f.close();

}
