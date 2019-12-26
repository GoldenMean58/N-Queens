#ifndef DRAWBOARD_H
#define DRAWBOARD_H

#include <QWidget>
#include <QPainter>
#include <QPen>

class DrawBoard : public QWidget
{
    Q_OBJECT
public:
    explicit DrawBoard(int n, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    int *data;
    void set_data(int *data);
    void set_n(int n);
    ~DrawBoard();
    int n;
signals:

public slots:
};

#endif // DRAWBOARD_H
