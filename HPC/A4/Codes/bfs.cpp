
#include<iostream>
#include<omp.h>

using namespace std;
int q[100];
int visited[7];
int local_q;

void bfs(int adj_matrix[7][7], int first, int last, int q[], int n_nodes) {
    if(first==last)
      return;
    
    int cur_node = q[first++];
    cout<<"  "<<cur_node;
    
    omp_set_num_threads(3);
    
    #pragma omp parallel for shared(visited)
    for(int i=0; i<n_nodes; i++) {
        if(adj_matrix[cur_node][i] == 1 && visited[i] == 0){
            q[last++] = i;
            visited[i] = 1;
        }
    }
    
    bfs(adj_matrix, first, last, q, n_nodes);
}

int main() {
    int first = -1;
    int last = 0;
    int n_nodes = 7;
    
    for(int i=0; i<n_nodes; i++) {
        visited[i] = 0;
    }
    
    int adj_matrix[7][7] = {
      {0, 1, 1, 0, 0, 0, 0},
      {1, 0, 1, 1, 0, 0, 0},
      {1, 1, 0, 0, 1, 0, 0},
      {0, 1, 0, 0, 1, 0, 0},
      {0, 0, 1, 1, 0, 1, 0},
      {0, 0, 0, 0, 1, 0, 1},
      {0, 0, 0, 0, 0, 1, 0}
    };
    
    int start_node = 3;
    q[last++] = start_node;
    first++;
    visited[start_node] = 1;
 
    bfs(adj_matrix, first, last, q, n_nodes);
    
    return 0;
    
}
