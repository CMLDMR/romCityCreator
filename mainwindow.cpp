#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    mGraphicsView = new Widget::GraphicsView(this);

    ui->verticalLayout->addWidget(mGraphicsView);

    QObject::connect(ui->pushButton_TreeArea,&QPushButton::clicked,[=](){
        mGraphicsView->setCurrentDrawingElement(Widget::ElementItem::tree);

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

