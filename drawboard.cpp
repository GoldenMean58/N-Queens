#include "drawboard.h"

DrawBoard::DrawBoard(int n, QWidget *parent) : QWidget(parent), data(nullptr), n(n)
{

}

void DrawBoard::paintEvent(QPaintEvent*) {
    if(!data) return;
    QPainter qp(this);
    for(int i = 0 ; i < n + 1; ++i) {
        qp.drawLine(0, 30 * i, 30 * n, 30 * i);
        qp.drawLine(30 * i, 0, 30 * i, 30 * n);
    }
    for(int i = 0; i < n; ++i) {
        int x = data[i] * 30;
        int y = i * 30;
        qp.drawEllipse(x, y, 30, 30);
    }
}

void DrawBoard::set_data(int *res) {
    if(this->data) {
        delete[] this->data;
        this->data = nullptr;
    }
    this->data = new int[n];
    for(int i = 0; i < n; ++i) {
        this->data[i] = res[i];
    }
}

void DrawBoard::set_n(int n) {
    this->data = nullptr;
    this->n = n;
}

DrawBoard::~DrawBoard(){
    if(data)
        delete[] data;
}
