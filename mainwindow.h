#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialog.h"
#include "drawboard.h"
#include "genetic.h"
#include "hill_climbing.h"
#include "look_back.h"
#include "simulated_anneal.h"
#include <QMainWindow>
#include <QMessageBox>
#include <time.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  int n;
  DrawBoard *db;
  int indi_count = 40, max_gen = 50000;
  float mutate_rate = 0.2;
  ~MainWindow();
private slots:
  void set_arg();
  void look_back();
  void hill_climbing();
  void simulated_anneal();
  void genetic();

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
