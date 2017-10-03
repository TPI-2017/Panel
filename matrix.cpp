#include "matrix.h"
#include "ui_matrix.h"
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>

using namespace std;

Matrix::Matrix(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Matrix)
{
    ui->setupUi(this);

    QCheckBox* vecB[ROW][COL];

    QGridLayout *layoutMatrix = new QGridLayout(this);

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            vecB[i][j] = new QCheckBox(this);
            layoutMatrix->addWidget(vecB[i][j],i, j, 6, 6);
        }
    }

    QPushButton * applyButton = new QPushButton(this);
    applyButton->setText("Ok");

    setLayout(layoutMatrix);
}

Matrix::~Matrix()
{
    delete ui;
}
