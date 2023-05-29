#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

struct Node {
  int id;
  vector<int> neighbors;
  bool visited;

  Node(int id) {
    this->id = id;
    visited = false;
  }
};

void bfs(vector<Node> &nodes, int start) {
  queue<int> queue;
  queue.push(start);

  while (!queue.empty()) {
    int current = queue.front();
    queue.pop();

    cout << current << " ";

    #pragma omp parallel for
    for (int neighbor : nodes[current].neighbors) {
      if (!nodes[neighbor].visited) {
        nodes[neighbor].visited = true;
        queue.push(neighbor);
      }
    }
  }
}

int main() {
  int n;
  cout << "Enter the number of nodes: ";
  cin >> n;

  vector<Node> nodes;

  for (int i = 0; i < n; i++) {
    nodes.push_back(Node(i));
  }

  for (int i = 0; i < n; i++) {
    int num_neighbors;
    cout << "Enter the number of neighbors for node " << i + 1 << ": ";
    cin >> num_neighbors;

    for (int j = 0; j < num_neighbors; j++) {
      int neighbor;
      cout << "Enter the neighbor " << j + 1 << " for node " << i + 1 << ": ";
      cin >> neighbor;

      nodes[i].neighbors.push_back(neighbor);
    }
  }

  nodes[0].visited = true;

  bfs(nodes, 0);

  cout << endl;

  return 0;
}
