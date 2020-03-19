#include <stdio.h>
#include <stack>
#include <vector>
#include <set>
#include <cassert>
using namespace std;

/* fail:
1191
1333
1483
2757
6481

30
35
39
42
44

*/

struct node;



struct edge{
	node* to = NULL;
	node* from = NULL;
};

struct node{
	vector<edge*> outbound;
	vector<edge*> inbound;
	int finishingTime = 0;
	bool explored = false;
	node* leader = NULL;
	
	int index = 0;
	int status = 0;
};

struct nodeComp{
	bool operator()(node* a, node* b)
	{
		assert(a->finishingTime != b->finishingTime);
		
		if(a->finishingTime > b->finishingTime)
			return true;
			
		return false;
	}
};

void connect(node* from, node* to)
{
	edge* e = new edge;
	e->from = from;
	e->to = to;
	to->inbound.push_back(e);
	from->outbound.push_back(e);
}

vector<node*> nodes;

set<node*,nodeComp> orderedNodes;

set<int> SCC_sizes;

static node* leader = NULL;
bool FIRST_PASS = false;
static int FINISHING_TIME = 0;
static int CURRENT_SCC_SIZE = 0;


void reset()
{
	for(int i = 0; i<nodes.size(); ++i)
	{
		//nodes[i]->finishingTime = 0;
		nodes[i]->explored = false;
		nodes[i]->status = 0;
	}
}

stack<node*> toBeExplored;


void explore_stack(node* n)
{
//	printf("Exploring %d\n",n->index);
	assert(toBeExplored.size() == 0);
	n->explored = true;
	n->leader = leader;
	
	toBeExplored.push(n);
	
	for(;;)
	{
		if(toBeExplored.size() <= 0)
		break;
	//	if(toBeExplored.size() % 1000 < 10)
	//	printf("%d\n",toBeExplored.size());
		node* t = toBeExplored.top();

	//	printf("%d\n",t->status);
		if(t->status == 0)
		{
			++CURRENT_SCC_SIZE;
			++t->status;
			
			if(!FIRST_PASS)
			{
				for(int i = 0; i<n->outbound.size(); ++i)
				{
					if(!n->outbound[i]->to->explored && n->outbound[i]->to->status == 0)	
					{
						n->outbound[i]->to->explored = true;
						toBeExplored.push(n->outbound[i]->to);
						//explore(n->outbound[i]->to);
					}
				}	
		
		
			}else{
		//		printf("SIZE: %d\n",n->inbound.size());
				for(int i = 0; i<n->inbound.size(); ++i)
				{
					if(!n->inbound[i]->from->explored && n->inbound[i]->to->status == 0)
					{
						n->inbound[i]->from->explored = true;
						toBeExplored.push(n->inbound[i]->from);
						//explore(n->inbound[i]->from);
					}
				}	
			}
			
		}else if(t->status >= 1)
		{
			++t->status;
			toBeExplored.pop();
			t->finishingTime = ++FINISHING_TIME;
			t->explored = true;
		}
		
		
		
//		t->explored = true;
	}
//	++CURRENT_SCC_SIZE;
//	n->finishingTime = ++FINISHING_TIME;
}



void explore(node* n)
{
	printf("Exploring %d\n",n->index);
	
	n->explored = true;
	n->leader = leader;
	
	if(!FIRST_PASS)
	{
		printf("here %d %d\n",n->outbound.size(),n->inbound.size());
		for(int i = 0; i<n->outbound.size(); ++i)
		{
			printf("asdasdasd: %d %d\n",n->index,n->outbound[i]->to->index);
			if(!n->outbound[i]->to->explored)	
			{
				explore(n->outbound[i]->to);
			}
		}	
	}else{
		for(int i = 0; i<n->inbound.size(); ++i)
		{
			if(!n->inbound[i]->from->explored)
			{
				explore(n->inbound[i]->from);
			}
		}	
	}
	
	++CURRENT_SCC_SIZE;
	n->finishingTime = ++FINISHING_TIME;
}

void DFS_Loop_1()
{
	for(int i = 0; i<nodes.size(); ++i)
	{
		if(!nodes[i]->explored)
		{
		//	printf("exploring %d\n",nodes[i]->index);
			leader = nodes[i];
			explore(nodes[i]);
		}
	}
}


void DFS_Loop_2()
{
	node* n = NULL;
	for(;;)
	{
	//	printf("SIZE: %d\n",orderedNodes.size());
		if(orderedNodes.size() <= 0)
		break;
		
	//	if(orderedNodes.size() % 1000 == 0)
	//	printf("%d\n",orderedNodes.size());
		
		n = *orderedNodes.begin();		
		orderedNodes.erase(orderedNodes.begin());
		
		if(!n->explored)
		{
			CURRENT_SCC_SIZE = 0;
			explore(n);
			SCC_sizes.insert(CURRENT_SCC_SIZE);
			printf("Inserting %d\n",CURRENT_SCC_SIZE);
		}
		
	}
}


int main()
{
		
	FILE *f = fopen("SCC2est.txt","r");
	int vertices = 0;
	
	fscanf(f,"%d\n",&vertices);
	
	for(int i = 0; i<vertices; ++i)
	{
		nodes.push_back(new node);		
		(*nodes.rbegin())->index = i;
	}	
	printf("Finished adding nodes\n");

	
	int to,from;
	
	for(;;)
	{
		fscanf(f,"%d %d\n",&from,&to);
		if(feof(f))
		{
			connect(nodes[from-1],nodes[to-1]);
			break;
		}
		
		connect(nodes[from-1],nodes[to-1]);
	}
	fclose(f);	
	
	printf("Finished Loading, size %d\n",nodes.size());
	
	FIRST_PASS = true;
	DFS_Loop_1();
	
	printf("Finished the 1st pass\n");
	
	for(int i = 0; i<nodes.size(); ++i)
	{
		orderedNodes.insert(nodes[i]);
	}
	FIRST_PASS = false;
	reset();
	for(int i = 0; i<nodes.size(); ++i)
	{
	//	printf("ON? %d\n",nodes[i]->explored);
	}
	DFS_Loop_2();
	
	printf("Exiting 2nd pass\n");
	
	for(set<int>::iterator i = SCC_sizes.begin(); i != SCC_sizes.end(); ++i)
	{
		printf("%d\n",*i);
	}
}




