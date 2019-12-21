#include "genetic.h"

void print_dna(int *dna, int seq_length) {
  // for (int i = 0; i < seq_length; ++i) {
  //   cout << dna[i] << " ";
  // }
  // cout << endl;
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

int analy_dna(int *dna, int seq_length) {
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

void Individuality::_copy_dna(int *dst, int *src) {
  memcpy(dst, src, N * sizeof(int));
}
unique_ptr<int> Individuality::get_dna(int *seq_length) {
  auto ret = unique_ptr<int>{new int[N]};
  _copy_dna(ret.get(), this->_dna);
  if (seq_length != nullptr)
    *seq_length = N;
  return ret;
}
void Individuality::set_dna(int *new_dna) { _copy_dna(this->_dna, new_dna); }
bool Individuality::_occur_mutate() {
  return ((double)rand() / (double)RAND_MAX) <= this->_mutate_rate;
}
int Individuality::mutate() {
  if (this->_occur_mutate()) {
    // single point mutate
    int point = rand() % N;
    this->_dna[point] = rand() % N;
    return 0;
  }
  return 1;
}

unique_ptr<int> Population::get_best_value() {
  for (int i = 0; i < M; ++i) {
    auto dna = _individualities[i]->get_dna(nullptr);
    int value = analy_dna(dna.get(), N);
    // cout << value << endl;
    if (value == 0) {
      return dna;
    }
  }
  return nullptr;
}
int Population::_selection() {
  std::sort(_individualities.begin(), _individualities.end(),
            [&](Individuality *&a, Individuality *&b) {
              auto a_dna = a->get_dna(nullptr);
              auto b_dna = b->get_dna(nullptr);
              return analy_dna(a_dna.get(), N) < analy_dna(b_dna.get(), N);
            });
  for (int i = M / 4; (size_t)i < _individualities.size(); ++i)
    delete _individualities[i];
  _individualities.resize(M / 4);
  return _individualities.size();
}
void Population::_mating(pair<Individuality *, Individuality *> parents) {
  if (_individualities.size() >= (size_t)M)
    return;
  int index = _individualities.size();
  int new_dna[N];
  int cross_point = rand() % N;
  auto father_dna = parents.first->get_dna(nullptr);
  auto monther_dna = parents.second->get_dna(nullptr);
  int *parent = father_dna.get();
  for (int i = 0; i < cross_point; ++i) {
    new_dna[i] = parent[i];
  }
  parent = monther_dna.get();
  for (int i = cross_point; i < N; ++i) {
    new_dna[i] = parent[i];
  }
  this->_individualities.push_back(new Individuality(N, T));
  this->_individualities[index]->set_dna(new_dna); // ok
  this->_individualities[index]->mutate();
}
void Population::make_next_gen() {
  vector<pair<Individuality *, Individuality *>> parents_arr;
  int remain = _selection();
  for (int i = 0; i < remain; i += 2) {
    parents_arr.push_back(
        std::make_pair(_individualities[i % M], _individualities[(i + 1) % M]));
  }
  while (this->_individualities.size() < (size_t)M) {
    for (auto parents : parents_arr) {
      _mating(parents);
    }
  }
}

unique_ptr<int> Nature::evolve_population(int *seq_length) {
  if (seq_length)
    *seq_length = N;
  for (int gen = 0; gen < G; ++gen) {
    this->_population->make_next_gen();
    for (int i = 0; i < M; ++i) {
      auto res = _population->get_best_value();
      if (res) {
        return res;
      }
    }
  }
  return nullptr;
}

Nature::Nature(int M, int N, int G, double T)
    : M(M), N(N), G(G), T(T), _population(new Population(M, N, T)) {
  srand((unsigned int)time(nullptr));
}

Population::Population(int M, int N, double T) : M(M), N(N), T(T) {
  for (int i = 0; i < M; ++i) {
    int dna[N];
    for (int j = 0; j < N; ++j) {
      dna[j] = rand() % N;
    }
    _individualities.push_back(new Individuality(N, T));
    _individualities[i]->set_dna(dna);
  }
}

Individuality::Individuality(int N, double T)
    : N(N), _dna(new int[N]), _mutate_rate(T) {}

int main(void) {
  srand((unsigned int)time(nullptr));
  int queen_count = 0;
  int indi_count, max_gen;
  cout << "Queens count = ";
  cin >> queen_count;
  cout << "Individuality count = ";
  cin >> indi_count; // 40
  cout << "Max gen = ";
  cin >> max_gen;           // 10000
  cout << "Mutate rate = "; // 0.08
  float mutate_rate;
  cin >> mutate_rate;
  Nature nature(indi_count, queen_count, max_gen, mutate_rate);
  auto solution = nature.evolve_population(nullptr);
  if (solution)
    print_dna(solution.get(), queen_count);
  else
    cout << "Solution not found!" << endl;
}
