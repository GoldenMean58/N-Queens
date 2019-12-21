#ifndef GENETIC_H
#define GENETIC_H
#include <algorithm>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <utility>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::unique_ptr;
using std::vector;

// constexpr float CROSS_RATE = 0.6;
class Individuality {
private:
  int N;
  int *_dna;
  void _copy_dna(int *dst, int *src);
  bool _occur_mutate();
  double _mutate_rate;

public:
  unique_ptr<int> get_dna(int *seq_length);
  void set_dna(int *new_dna);
  int mutate();
  Individuality(int N, double T);
};

class Population {
private:
  vector<Individuality *> _individualities;
  int _selection();
  void _mating(pair<Individuality *, Individuality *> parents);
  int M;
  int N;
  double T;

public:
  void make_next_gen();
  unique_ptr<int> get_best_value();
  Population(int M, int N, double T);
};

class Nature {
private:
  int M;
  int N;
  int G;
  double T;
  Population *_population;

public:
  unique_ptr<int> evolve_population(int *seq_length);
  Nature(int M, int N, int G, double T);
  void print();
};

#endif
