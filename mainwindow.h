#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Widget/graphicsview.h"

#include <mongocxx/client.hpp>
#include <mongocxx/database.hpp>
#include <mongocore/db.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


namespace Qt{
class PlantModel;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_pushButton_clicked();

    void on_pushButton_addFolder_clicked();

    void on_pushButton_updatePlantList_clicked();

    void on_pushButton_deletePlant_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;


    Widget::GraphicsView* mGraphicsView;
    mongocxx::client* mClient;
    mongocxx::database mDB;
    MongoCore::DB *mMongoDB;


    Qt::PlantModel* mModel;

};
#endif // MAINWINDOW_H
