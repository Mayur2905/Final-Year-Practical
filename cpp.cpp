#include <iostream> 
#include <vector> 
#include <stack> 
#include <omp.h> 
using namespace std ; 
void bfs (vector<vector< int >> &graph, vector< bool > &visited, int start_node) 
{ 
queue<int>q; 
q. push (start_node); 
visited[start_node] = true ; 
while (!q.empty ()) 
{ 
int curr_node = q. front (); 
q.pop (); 
cout << curr_node << " " ; 
# pragma omp parallel for 
for ( int i = 0 ; i < graph[curr_node]. size (); i++) 
{ 
int adj_node = graph[curr_node][i]; 
// Only process unvisited nodes 
if (!visited[adj_node]) 
{ 
# pragma omp critical 
{ 
if (!visited[adj_node]) 
{ 
visited[adj_node] = true ; 
q.push (adj_node); 
} 
} 
} 
} 
} 
} 
int main () 
{ 
vector<vector< int >> graph = {{ 1 , 2 }, { 0 , 2 , 3 }, { 0 , 1 , 3 , 4 }, { 1 , 2 }, { 2 }}; 
vector< bool > visited (graph. size (), false ); 
bfs (graph, visited, 0 ); 
return 0 ; 
} 
// For compilation - g++ -std=c++14 bfs.cpp -o bfs_output 
// For Execution - ./bfs_output