#include "utils.h"

void print_solution(int *dna, int seq_length) {
  for (int i = 0; i < seq_length; ++i) {
    for (int j = 0; j < dna[i]; ++j) {
      cout << "0";
    }
    cout << "#";
    for (int j = dna[i] + 1; j < seq_length; ++j) {
      cout << "0";
    }
    cout << endl;
  }
}

int analy_solution(int *dna, int seq_length) {
  int pair_num = 0;
  for (int i = 0; i < seq_length - 1; ++i) {
    for (int j = i + 1; j < seq_length; ++j) {
      if (dna[i] == dna[j] || (dna[i] + j == dna[j] + i) ||
          (dna[i] - j == dna[j] - i))
        pair_num++;
    }
  }
  return pair_num;
}
