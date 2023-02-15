#include "tree.h"

#include <QDebug>

#include <QDir>

namespace Assets {

Tree::Tree::Tree()
    :Assets::Plant::Plant(Assets::AssetType::tree)
{



}

Tree::Tree &Tree::Tree::operator=(const Tree &other)
{
    this->setAssetPath(other.assetPath()); return *this;
}

Tree::Tree::Tree(const std::string &path)
    :Assets::Plant::Plant(Assets::AssetType::tree)
{
    this->setAssetPath(path);
}

void Tree::TreeTypeList::initSingleton()
{
    mPtr = new TreeTypeList();
}

Tree::TreeTypeList::TreeTypeList()
{


    QDir dir;

    qDebug() << dir.currentPath();

    if( dir.exists("bin") ){
        dir.cd("bin");
        if( dir.exists("asset") ){
            dir.cd("asset");
            if( dir.exists("tree") ){
                dir.cd("tree");
                for( const auto &item : dir.entryInfoList(QDir::Filter::Files) ){
                    qDebug() << item.filePath();
//                    this->append(item.filePath().toStdString());
                }
            }else{
                qDebug() << dir.absolutePath();
            }
        }else{
            qDebug() << dir.absolutePath();
        }
        qDebug() << "bin Exist";
    }else{
        qDebug() << dir.absolutePath() << "bin";
    }

    for( int i = 0 ; i < 15 ; i++ ){
        this->append(std::string("bin/asset/tree/tree001.png"));
    }
    for( int i = 0 ; i < 10 ; i++ ){
        this->append(std::string("bin/asset/tree/tree002.png"));
    }
    for( int i = 0 ; i < 10 ; i++ ){
        this->append(std::string("bin/asset/tree/tree004.png"));
    }
    for( int i = 0 ; i < 8 ; i++ ){
        this->append(std::string("bin/asset/tree/tree003.png"));
    }
    for( int i = 0 ; i < 5 ; i++ ){
        this->append(std::string("bin/asset/tree/tree005.png"));
    }
    for( int i = 0 ; i < 3 ; i++ ){
        this->append(std::string("bin/asset/tree/tree006.png"));
    }


    for( int i = 0 ; i < 3 ; i++ ){
        this->append(std::string("bin/asset/tree/tree012.png"));
    }
    for( int i = 0 ; i < 3 ; i++ ){
        this->append(std::string("bin/asset/tree/tree011.png"));
    }


    for( int i = 0 ; i < 3 ; i++ ){
        this->append(std::string("bin/asset/tree/tree014.png"));
        this->append(std::string("bin/asset/tree/tree015.png"));

    }

//    this->append(std::string("bin/asset/tree/shadow.png"));


}



} // namespace Assets
