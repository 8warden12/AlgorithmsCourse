#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>
using namespace std;

struct node;

struct edge{
  int weight = 0;
  node* a = NULL;
  node* b = NULL;
};

struct node{
  vector<edge*> connections;
};

int main()
{
  fstream f("test.txt");
  int nodes, edges;
  f>>nodes>>edges;

}
