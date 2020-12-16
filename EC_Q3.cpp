// QUESTION 3: Longest Path 
#include<bits/stdc++.h>
using namespace std;

// n_1 is our origin node, sumLen is the length up to the current node, & maxLen is a pointer that stores the max length
void
DFS (vector < pair < int, int > >graph[], int n_1,
     int sumLen, int *maxLen, vector < bool > &visited)
{
  // visited tells us if we have been to that node or not (0=no, 1=yes)
  visited[n_1] = 1;

  // currLen is for length from n_1 to current node
  int currLen = 0;

  // adj stores the destination node and the length
  pair < int, int >adj;

  // traverses all adjacent nodes
  for (int i = 0; i < graph[n_1].size (); i++)
    {
      adj = graph[n_1][i];

      // checks to see if node was visited
      if (!visited[adj.first])
	{
	  // total distance from n_1 to the adjacent node
	  currLen = sumLen + adj.second;

	  // does depth-first-search for the adjacent node 
	  DFS (graph, adj.first, currLen, maxLen, visited);
	}

      // if the total distance at this point is greater than the previous distance, we need to update it 
      if ((*maxLen) < currLen)
	*maxLen = currLen;

      // make currLen = 0 for the next node
      currLen = 0;
    }
}


// n is the number of nodes in the graph & edges is the number of edges
int
longestDistance (vector < pair < int, int > >graph[], int n)
{
  // longest distance between the nodes
  int maxLen = INT_MIN;

  // call depth-first-search for each node to find the max distance
  for (int i = 1; i <= n; i++)
    {
      // initialize visited array with 0 
      vector < bool > visited (n + 1, false);

      // call depth-first-search for n_1 vertex i 
      DFS (graph, i, 0, &maxLen, visited);
    }

  return maxLen;
}

// main function 
int
main ()
{
  // number of nodes
  int n = 6;

  vector < pair < int, int >>graph[n + 1];

  // creates graph and first edge
  graph[1].push_back (make_pair (2, 3));
  graph[2].push_back (make_pair (1, 3));

  // second edge 
  graph[2].push_back (make_pair (3, 4));
  graph[3].push_back (make_pair (2, 4));

  // third edge 
  graph[2].push_back (make_pair (6, 2));
  graph[6].push_back (make_pair (2, 2));

  // fourth edge 
  graph[4].push_back (make_pair (6, 6));
  graph[6].push_back (make_pair (4, 6));

  // fifth edge 
  graph[5].push_back (make_pair (6, 5));
  graph[6].push_back (make_pair (5, 5));

  cout << "Longest Path = " << longestDistance (graph, n);

  return 0;
}
