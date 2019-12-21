#include "simulated_anneal.h"
unique_ptr<int[]> simulated_anneal(int n, int max_move_times) {
  unique_ptr<int[]> best_solution{new int[n]};
  float T = 50000;
  float r = 0.98;
  int initial_state[n];
  int f1, f2;
  for (int i = 0; i < n; ++i) {
    initial_state[i] = rand() % n;
  }
  while (max_move_times > 0) {
    memcpy(best_solution.get(), initial_state, n * sizeof(int));
    f2 = analy_solution(best_solution.get(), n);
    int i = rand() % n;
    // int bak = initial_state[i];
    initial_state[i] = (initial_state[i] + 1) % n;
    f1 = analy_solution(initial_state, n);
    if (f1 <= f2 ||
        (exp(-(f1 - f2) / T) > ((double)rand() / (double)RAND_MAX))) {
      // accept
      memcpy(best_solution.get(), initial_state, n * sizeof(int));
      if (f1 * f2 == 0)
        return best_solution;
    } /*else {
      initial_state[i] = bak;
    }*/
    T *= r;
    max_move_times--;
  }
  return nullptr;
}
/*
int main(void) {
  srand((unsigned int)time(nullptr));
  int n = 0;
  cout << "Queen count = ";
  cin >> n;
  auto res = simulated_anneal(n, 999999);
  if (res) {
    print_solution(res.get(), n);
  } else {
    cout << "No solution found!" << endl;
  }
  return 0;
}
*/
