#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QImage>
#include <QByteArray>



#include "qtModel/plantmodel.h"
#include "qtModel/mountainmodel.h"

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


    mMountainModel = new Qt::MountainModel(GlobalVariable::mMongoDB);
    ui->tableView_MountainModelView->setModel(mMountainModel);
    QObject::connect(mMountainModel,&QStandardItemModel::itemChanged,[=](){
        ui->tableView_MountainModelView->resizeRowsToContents();
    });

    QObject::connect(mMountainModel,&QStandardItemModel::rowsAboutToBeInserted,[=](){
        ui->tableView_MountainModelView->resizeRowsToContents();
    });

    QObject::connect(ui->pushButton_MountainAdd,&QPushButton::clicked,this,&MainWindow::addMountain);



}

MainWindow::~MainWindow()
{
    delete ui;
}

///
/// \brief MainWindow::on_pushButton_clicked
/// Add tree to Database
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

#include <Geometry/fastnoiselite.h>
#include <QRandomGenerator>
#include <QLabel>

void MainWindow::on_pushButton_2_clicked()
{
    QImage *img = new QImage(512,512,QImage::Format_RGB888);


    Geometry::Noise::FastNoiseLite noiseGen;
    noiseGen.SetNoiseType(Geometry::Noise::FastNoiseLite::NoiseType_Value);
    noiseGen.SetFrequency(ui->doubleSpinBox_frequency->value());
    noiseGen.SetSeed(QRandomGenerator::global()->generate()%10000);

    std::vector<float> noiseData(512*512);
    int index = 0;

    for( int i = 0 ; i < 512 ; i++ ){
        for( int j = 0 ; j < 512 ; j++ ){
            noiseData[index++] = (noiseGen.GetNoise((float)i, (float)j)+1)*255;
        }
    }

    float min = 9999;
    float max = -9999;

    index = 0;
    for( int i = 0 ; i < 512 ; i++ ){
        for( int j = 0 ; j < 512 ; j++ ){
            auto data_ = noiseData[index++];
            min = min > data_ ? data_ : min;
            max = max < data_ ? data_ : max;
        }
    }

    index = 0;
    for( int i = 0 ; i < 512 ; i++ ){
        for( int j = 0 ; j < 512 ; j++ ){
            auto data_ = (noiseData[index++]-min)/(max-min)*255.0;

            img->setPixel(i,j,qRgb(data_,data_,data_));
        }
    }


    ui->label->setPixmap(QPixmap::fromImage(*img));

    qDebug() << min << max;
}

void MainWindow::addMountain()
{

    auto fileName = QFileDialog::getOpenFileName(this,"Resim");

    QFileInfo info(fileName);
    if( info.suffix() != "png" ){
        qDebug() << "No PNG Image Selected";
        return;
    }


    QImage img(fileName);

    Assets::Terrain::Mountain mountainItem;
    mountainItem.setAssetHeight(img.height());
    mountainItem.setAssetWidth(img.width());
    mountainItem.setAssetName(info.completeBaseName().toStdString());

    auto fileOid = this->mModel->uploadfile(fileName.toStdString());

    mountainItem.setFileOid(fileOid);


    this->mMountainModel->InsertItem(mountainItem);

    this->mMountainModel->updateMountainModel();

}

