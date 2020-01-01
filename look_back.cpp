#include "look_back.h"
#include "genetic.h"

int LookBack::get_n() { return this->n; }
void LookBack::set_n(int n) { this->n = n; }
int LookBack::get_solution_count() { return this->solution_count; }
LookBack::LookBack(int n) : n(n), queen_pos(new int[n]), solution_count(0) {}
LookBack::~LookBack() {
  delete[] queen_pos;
  for (auto solution : solutions) {
    delete[] solution;
  }
}
void LookBack::look_back_queen(int index) {
  for (int loop = 0; loop < n; loop++) {
    if (check_pos_valid(index, loop)) {
      queen_pos[index] = loop;
      if (n - 1 == index) {
        solution_count++;
        int *solution = new int[n];
        memcpy(solution, queen_pos, n * sizeof(int));
        solutions.push_back(solution);
        queen_pos[index] = 0;
        return;
      }
      look_back_queen(index + 1);
      queen_pos[index] = 0;
    }
    if (solutions.size() > 0)
      return;
  }
}
void LookBack::print() {
  for (auto solution : solutions) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < solution[i]; ++j) {
        cout << "0";
      }
      cout << "#";
      for (int j = solution[i] + 1; j < n; ++j) {
        cout << "0";
      }
      cout << endl;
    }
    cout << "--------------------------------" << endl;
  }
}

bool LookBack::check_pos_valid(int loop, int value) {
  int index;
  int data;
  for (index = 0; index < loop; index++) {
    data = queen_pos[index];
    if (value == data)
      return false;
    if ((index + data) == (loop + value))
      return false;
    if ((index - data) == (loop - value))
      return false;
  }
  return true;
}
/*
int main() {
  int n = 0;
  cout << "Queens count = ";
  cin >> n;
  LookBack lb(n);
  lb.look_back_queen(0);
  lb.print();
  cout << "total=" << lb.get_solution_count() << endl;
  return 0;
}
*/
