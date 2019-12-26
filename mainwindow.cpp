#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), n(8)
{
    srand((unsigned int)time(nullptr));
    ui->setupUi(this);
    db = new DrawBoard(n);
    setCentralWidget(db);
    auto action_look_back = ui->menuBar->addAction("回溯法");
    connect(action_look_back, SIGNAL(triggered()), SLOT(look_back()));
    auto action_hill_climbing = ui->menuBar->addAction("重启爬山法");
    connect(action_hill_climbing, SIGNAL(triggered()), SLOT(hill_climbing()));
    auto action_simulated_anneal = ui->menuBar->addAction("模拟退火算法");
    connect(action_simulated_anneal, SIGNAL(triggered()), SLOT(simulated_anneal()));
    auto action_genetic = ui->menuBar->addAction("遗传算法");
    connect(action_genetic, SIGNAL(triggered()), SLOT(genetic()));
    auto action_set_n = ui->menuBar->addAction("参数设置");
    connect(action_set_n, SIGNAL(triggered()), SLOT(set_arg()));
}

void MainWindow::look_back() {
    LookBack lb(n);
    lb.look_back_queen(0);
    db->set_data(lb.solutions[1]);
    db->update();
}
void MainWindow::hill_climbing(){
  auto res = ::hill_climbing(n, 100000);
  if (res) {
      db->set_data(res.get());
      db->update();
  } else {
      QMessageBox::information(this, "Fail", "未能找到解");
  }
}
void MainWindow::simulated_anneal(){
  auto res = ::simulated_anneal(n, 999999);
  if (res) {
      db->set_data(res.get());
      db->update();
  } else {
      QMessageBox::information(this, "Fail", "未能找到解");
  }
}
void MainWindow::genetic(){
  Nature nature(indi_count, n, max_gen, mutate_rate);
  auto res = nature.evolve_population(nullptr);
  if (res) {
      db->set_data(res.get());
      db->update();
  } else {
      QMessageBox::information(this, "Fail", "未能找到解");
  }
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::set_arg() {
    Dialog dlg(n);
    dlg.exec();
    n = dlg.n;
    db->set_n(n);
}
