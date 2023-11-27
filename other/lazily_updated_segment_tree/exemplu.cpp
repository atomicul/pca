#include <algorithm>
#include <fstream>
#include <iostream>

const int N = 100000;
const long long INF = (1LL << 50);

struct tree_node {
  long long minim;
  int position;
  long long lazy;
};

long long height[N + 1];
tree_node segment_tree[N * 4 + 1];

void update_lazy(int node, int left, int right) {
  if (segment_tree[node].lazy) { // daca nodul curent trebuie sa creasca
                                 // scandurile din intervalul curent
    segment_tree[node].minim += segment_tree[node].lazy; // minimul creste si el

    if (left != right) { // vedem daca nodul are fii carora sa le paseze
                         // responsabilitatea
      segment_tree[node * 2].lazy += segment_tree[node].lazy;
      segment_tree[node * 2 + 1].lazy += segment_tree[node].lazy;
    }

    segment_tree[node].lazy = 0; // nodul curent si-a terminat treaba
  }
}

void update_node(int node) {
  segment_tree[node].minim =
      std::min(segment_tree[node * 2].minim,
               segment_tree[node * 2 + 1].minim); // updatam scandura minima

  if (segment_tree[node].minim ==
      segment_tree[node * 2]
          .minim) // verificam daca scandura minima vine din fiul stang
    segment_tree[node].position = segment_tree[node * 2].position;
  else
    segment_tree[node].position = segment_tree[node * 2 + 1].position;
}

void build(int node, int left, int right) {
  if (left == right) { // interval de lungime 1
    segment_tree[node].minim = height[left];
    segment_tree[node].position = left;
  } else {
    int middle = (left + right) / 2;

    build(node * 2, left, middle);
    build(node * 2 + 1, middle + 1, right);

    update_node(node); // updatam nodul curent
  }
}

void update(int node, int left, int right, int query_left, int query_right,
            long long increase) {
  // primul pas este sa vedem daca nodul are de executat vreo
  // actiune pe care a amanat-o (ne uitam la lazy)
  update_lazy(node, left, right);

  if (query_left <= left and
      right <= query_right) { // intervalul curent e complet inclus in
                              // intervalul de query
    segment_tree[node].lazy += increase; // toate scandurile cresc cu aceeasi
                                         // valoare, asa ca ne folosim de lazy
    update_lazy(node, left, right);
  } else {
    int middle = (left + right) / 2;

    if (query_left <= middle)
      update(node * 2, left, middle, query_left, query_right, increase);
    if (middle + 1 <= query_right)
      update(node * 2 + 1, middle + 1, right, query_left, query_right,
             increase);

    // indiferent de care fiu este updatat, noi trebuie sa recalculam valoarea
    // din nodul curent si pentru asta avem nevoie de inaltimile curente ale
    // celor 2 fii, asa ca ii 'fortam' sa isi execute actiunile (updatam fortat
    // lazy-urile lor)
    update_lazy(node * 2, left, middle);
    update_lazy(node * 2 + 1, middle + 1, right);

    update_node(node); // updatam nodul curent
  }
}

int main(int argc, const char *argv[]) {
  std::ifstream in("biscuiti.in");
  std::ofstream out("biscuiti.out");

  int n;
  in >> n;

  long long initial_total_height = 0;

  for (int i = 1; i <= n; ++i) {
    in >> height[i];
    initial_total_height += height[i];
  }

  build(1, 1, n);

  long long final_total_height = 0;

  for (int day = 1; day <= n; ++day) {
    int position = segment_tree[1].position; // gasim pozitia scandurii minime
    final_total_height += segment_tree[1].minim; // crestem suma finala

    std::cout << segment_tree[1].position << ": " << segment_tree[1].minim
              << '\n';
    // eliminam scandura (cu alte cuvinte, ii crestem inaltimea cu
    // infinit)
    update(1, 1, n, position, position, INF);

    // crestem si restul scandurilor din intervalul [1, position-1]
    if (position != 1)
      update(1, 1, n, 1, position - 1, day);
  }

  out << final_total_height - initial_total_height << std::endl;

  return 0;
}
