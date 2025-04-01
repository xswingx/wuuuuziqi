#include "mainwindow.h"
#include "ui_mainwindow.h"

/*垂直布局*/
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*设置窗口标题*/
    setWindowTitle("五子棋");

    /*设置窗口固定大小*/
    setFixedSize(800,680);

    /*创建棋盘对象*/
    m_qipan= new QiPan(this);

    /*设置布局*/
    QWidget * centerWidget = new QWidget(this);
    setCentralWidget(centerWidget);
    QVBoxLayout * layout = new QVBoxLayout(centerWidget);
    layout->addWidget(m_qipan);
}

MainWindow::~MainWindow()
{
    delete ui;
}

