#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QImage>
#include <QByteArray>



#include "qtModel/plantmodel.h"
#include "Asset/tree.h"


#include "../url.h"

#include <iostream>
#include "globalVar.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    try {
        mClient = new mongocxx::client(mongocxx::uri(_url));
    } catch (mongocxx::exception &e) {
        std::cout << "Error Connection: " << e.what() << "\n";
        return;
    }


    mDB = mClient->database("App");

    mMongoDB = new MongoCore::DB(&mDB);

    GlobalVariable::mMongoDB = new MongoCore::DB(mMongoDB);

    mGraphicsView = new Widget::GraphicsView(this);

    ui->verticalLayout->addWidget(mGraphicsView);

    QObject::connect(ui->pushButton_TreeArea,&QPushButton::clicked,[=](){
        mGraphicsView->setCurrentDrawingElement(Widget::ElementItem::tree);
    });

    QObject::connect(ui->pushButton_TreeArea_Random,&QPushButton::clicked,[=](){
        mGraphicsView->setCurrentDrawingElement(Widget::ElementItem::randomAreaTree);
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


    mModel = new Qt::PlantModel(this->mMongoDB);

    ui->tableView_PlantView->setModel(mModel);
    QObject::connect(mModel,&QStandardItemModel::itemChanged,[=](){
        ui->tableView_PlantView->resizeRowsToContents();
    });

    QObject::connect(mModel,&QStandardItemModel::rowsAboutToBeInserted,[=](){
        ui->tableView_PlantView->resizeRowsToContents();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    auto fileName = QFileDialog::getOpenFileName(this,"Resim");

    QFileInfo info(fileName);
    if( info.suffix() != "png" ){
        qDebug() << "No PNG Image Selected";
        return;
    }


    QImage img(fileName);

    Assets::Tree::Tree treeItem;
    treeItem.setAssetHeight(img.height());
    treeItem.setAssetWidth(img.width());
    treeItem.setAssetName(info.completeBaseName().toStdString());

    auto fileOid = this->mModel->uploadfile(fileName.toStdString());

    treeItem.setFileOid(fileOid);


    this->mModel->InsertItem(treeItem);

    this->mModel->updatePlantModel();


}


void MainWindow::on_pushButton_addFolder_clicked()
{
    auto list = QFileDialog::getOpenFileNames(this,"Assets",QDir::currentPath(),"*.png");


    for( const auto &fileName : list ){

        QFileInfo info(fileName);
        if( info.suffix() != "png" ){
            qDebug() << "No PNG Image Selected";
            return;
        }


        QImage img(fileName);

        Assets::Tree::Tree treeItem;
        treeItem.setAssetHeight(img.height());
        treeItem.setAssetWidth(img.width());
        treeItem.setAssetName(info.completeBaseName().toStdString());
        auto fileOid = this->mModel->uploadfile(fileName.toStdString());
        treeItem.setFileOid(fileOid);
        this->mModel->InsertItem(treeItem);
    }


    this->mModel->updatePlantModel();


}


void MainWindow::on_pushButton_updatePlantList_clicked()
{
    this->mModel->updatePlantModel();

}


void MainWindow::on_pushButton_deletePlant_clicked()
{
    auto row = this->ui->tableView_PlantView->currentIndex().row();

    if( row < 0 || row >= this->mModel->rowCount() ){
        //TODO: Row Seçili Değilse Uyarı Dialoğu
        qDebug() << "Select Row";
        return;
    }

    auto item = static_cast<Qt::PlantStandartItem*>(mModel->item(row,1));

    if( !this->mModel->deleteGridFS(item->fileOid()) ){
        //TODO: GridFS Silinmediyse Uyarı Dialoğu
        qDebug() << "Can Not Delete GridFS file";
        return;
    }


    if( !this->mModel->DeleteItem(*item) ){
        //TODO: PlantItem Silinmediyse Uyarı Dialoğu
        qDebug() << "Can Not Delete PlantItem ";
        return;
    }

    this->mModel->updatePlantModel();

}

