#ifndef LOOK_BACK_H
#define LOOK_BACK_H
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

class LookBack {
public:
  vector<int *> solutions;
  int get_n();
  void set_n(int n);
  int get_solution_count();
  LookBack(int n);
  ~LookBack();
  void look_back_queen(int index);
  void print();

private:
  int n;
  int *queen_pos;
  int solution_count;
  bool check_pos_valid(int loop, int value);
};
#endif
