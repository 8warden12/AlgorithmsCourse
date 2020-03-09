#include <stdio.h>
#include <vector>
#include <cassert>
#include <map>
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
  int tag = 0;
  int index = 0;
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

  int shortestPaths[N+1][N];
  //shortestPaths[i][v] contains the value of the length of the shortest path
  //from the source vertex to the vertex at vertex v, using at most i edges.

  printf("%d %d\n",N,M);

  for(int i = 0; i<N; ++i)
  {
    node *n = new node;
    n->index = i;
    nodes.push_back(n);
  }
  assert(nodes.size() == N);
  int from,to,weight;
  for(int i = 0; i<M; ++i)
  {
    fscanf(f,"%d %d %d\n",&from,&to,&weight);
    connect(from-1,to-1,weight);
  //  printf("Connecting %d and %d with weight %d\n",from,to,weight);
  }

  //PHASE I: REWEIGHTING

  //add a new vertex that will function as the source
  nodes.push_back(new node);

  for(int i = 0; i<nodes.size()-1; ++i)
  {
    //create an arc of length 0 from the source to every other vertex
    connect(nodes.size()-1,i,0);
  }

  const int s = nodes.size()-1;
  //run the Bellman-Ford algorithm
  shortestPaths[0][s] = 0;
  for(int i = 0; i<s-1; ++i)
  {
    shortestPaths[0][s] = 999999999; //"infinity"
  }

  //where i is the number of edges used
  for(int i = 1; i<N; ++i)
  {
    //cycle through all the vertices, including the source vertex
    for(int v = 0; v<N+1; ++v)
    {
      //get minimum for case 2 (when you find a different path and don't reuse the //one from the previous iteration)
      
      int minLength = -99;
      for(int w = 0; w<nodes[v]->inbound.size(); ++w)
      {
        if(shortestPaths[i-1][w] + )
      }

    }
  }

  //final iteration to detect negative cycles:
}
