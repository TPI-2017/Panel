#ifndef MATRIX_H
#define MATRIX_H

#include <QWidget>

#define ROW 8
#define COL 8

namespace Ui {
class Matrix;
}

class Matrix : public QWidget
{
    Q_OBJECT

public:
    explicit Matrix(QWidget *parent = 0);
    ~Matrix();

private:
    Ui::Matrix *ui;
};

#endif // MATRIX_H
