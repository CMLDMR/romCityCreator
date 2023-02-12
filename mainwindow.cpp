#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Asset/tree.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto list = Assets::Tree::TreeTypeList::instance().list();

    qDebug()  << "Asset" << list.size();
    for( const auto &asset : list ){
        qDebug() << static_cast<int>(asset.assetType()) << asset.assetPath().c_str() << asset.assetWidth() << asset.assetHeight();
    }

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

