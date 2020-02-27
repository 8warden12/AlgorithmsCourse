#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include <stdio.h>
using namespace std;

struct job;

//27423814258
//27423814258

//A:
//have not tried:
/*188636482260

69119377652 WORKING
*/

/*
B: 
39829594388

67311454237 WORKS
*/

struct job{
  int weight = 0;
  int length = 0;
  float score = 0.0f;
};


struct jobComp{
  bool operator()(const job& a,const job& b)
  {

   /* if((float)a.weight/a.length < (float)b.weight/b.length)
    {
      return false;
    }
  return true;*/

    if(a.weight - a.length > b.weight - b.length)
    return true;
    
   if(a.weight - a.length == b.weight - b.length)
    if(a.weight > b.weight)
    return true;

    return false;
  }
};

multiset<job,jobComp> jobsQueue;

int main()
{
  ifstream f ("test.txt");
  int n = 0;
  f>>n;
  for(int i = 0; i<n; ++i)
  {
    job j;
    f>>j.weight>>j.length;
    jobsQueue.insert(j);
    printf("%d %d\n",j.weight,j.length);
  }
  cout<<"L:"<<jobsQueue.size()<<"\n";
  int totalTime = 0;
  long long int wsum = 0;
  for(set<job,jobComp>::iterator i = jobsQueue.begin(); i != jobsQueue.end(); ++i)
  {
   
    totalTime += i->length;
    wsum += totalTime * i->weight;
     cout<<"s: "<<wsum<<"\n";
  }
  cout<<wsum;

}
