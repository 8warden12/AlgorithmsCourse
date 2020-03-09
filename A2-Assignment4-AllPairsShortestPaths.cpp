#include <stdio.h>
#include <vector>
using namespace std;

//all pairs shortest paths

struct node;

struct edge{
  node* from = NULL;
  node* to = NULL;
  int weight = 0;
};

struct node{
  vector<edge*> outbound;
  vector<edge*> inbound;
};

vector<node*> nodes;

void connect(int from, int to, int weight)
{
  edge* e = new edge;
  e->from = nodes[from];
  e->to = nodes[to];
  e->weight = weight;
  nodes[from]->outbound.push_back(e);
  nodes[to]->inbound.push_back(e);
}

int main() {
  int N, M;
  FILE*f = fopen("g1.txt","r");

  fscanf(f,"%d %d\n",&N,&M);

printf("%d %d\n",N,M);

  for(int i = 0; i<N; ++i)
  {
    nodes.push_back(new node);
  }

  int from,to,weight;
  for(int i = 0; i<M; ++i)
  {
    fscanf(f,"%d %d %d\n",&from,&to,&weight);
    connect(from,to,weight);
    printf("Connecting %d and %d with weight %d\n",from,to,weight);
  }

}
