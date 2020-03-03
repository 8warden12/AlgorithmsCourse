#include <stdio.h>
#include <assert.h>
#include <vector>
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

  FILE *f = fopen("dijkstraData.txt","r");
  assert(f != NULL);

  int sID = 0;
  int rID = 0;
  int weight = 0;
  char check = ' ';
  for(int i = 0; i<200; ++i)
  {   
    fscanf(f,"%d",&sID);
   
    for(;;)
    {
      fscanf(f,"%c",&check);
      if(check == ' ')
      {
        printf("exiting");
        break;  
      }

      fscanf(f,"%d",&rID);
      fgetc(f);
      fscanf(f,"%d",&weight);

      assert(sID-1 == i);
      connect(nodes[i],nodes[rID-1],weight);
      printf("connecting %d and %d",i+1,sID);
    }
  }


}
