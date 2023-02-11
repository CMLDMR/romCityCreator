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

    QObject::connect(ui->pushButton_Mountain,&QPushButton::clicked,[=](){
        mGraphicsView->setCurrentDrawingElement(Widget::ElementItem::mountain);
    });


    QObject::connect(ui->pushButton_zoomin,&QPushButton::clicked,[=](){
        mGraphicsView->scale(1.25,1.25);
    });

    QObject::connect(ui->pushButton_zoomout,&QPushButton::clicked,[=](){
        mGraphicsView->scale(0.8,0.8);
    });

    QObject::connect(ui->pushButton_fitwindow,&QPushButton::clicked,[=](){
        mGraphicsView->resetTransform();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

