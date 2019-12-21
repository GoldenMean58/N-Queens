#include "hill_climbing.h"
unique_ptr<int[]> hill_climbing(int n, int max_move_times) {
  unique_ptr<int[]> best_solution{new int[n]};
  int initial_state[n];
  int f1, f2;
  while (max_move_times > 0) {
    for (int i = 0; i < n; ++i) {
      initial_state[i] = rand() % n;
    }
    memcpy(best_solution.get(), initial_state, n * sizeof(int));
    f2 = analy_solution(best_solution.get(), n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (initial_state[i] == j)
          continue;
        int bak = initial_state[i];
        initial_state[i] = j;
        f1 = analy_solution(initial_state, n);
        if (f1 <= f2) {
          // accept
          memcpy(best_solution.get(), initial_state, n * sizeof(int));
          if (f1 * f2 == 0)
            return best_solution;
        }
        initial_state[i] = bak;
      }
    }
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
  auto res = hill_climbing(n, 100000);
  if (res) {
    print_solution(res.get(), n);
  } else {
    cout << "No solution found!" << endl;
  }
  return 0;
}
*/
