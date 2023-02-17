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
                    this->append(item.filePath().toStdString());
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

}



} // namespace Assets
