#include "forest.h"
#include <QDebug>

#include <QRandomGenerator>
#include <QtMath>
#include <QtAlgorithms>
#include <QThread>
#include <QImage>
#include <QPainter>
#include <QRandomGenerator>

#include <algorithm>
#include <functional>


#include <globalVar.h>
#include "Asset/tree.h"
#include "Geometry/concavehull.h"
#include <Geometry/fastnoiselite.h>

//TODO: Düzgün Bir Yere QPOintF operator taşınacak

static bool compare( const QPointF &a , const QPointF &b){
    return a.y() < b.y();
}

namespace Assets {
namespace Plant {

Forest::Forest()
    :Assets::Plant::PlantManager(GlobalVariable::mMongoDB)
{
    if( GlobalVariable::mMongoDB ){
        this->setLimit(10000);
        this->UpdateList(Assets::Tree::Tree());
    }else{
        qDebug() << "Driver Does not pointed";
    }

    mThread = new QThread();

    QObject::connect(mThread,&QThread::started,[=](){
        this->forestBuilder();
    });

}

void Forest::populateForest()
{
//    Ecosystem::Populator::instance()->Generate<Assets::Tree::Tree>(Assets::Tree::TreeTypeList::instance(),*this);
}

//TODO: Padding Forest Eklenecek
void Forest::populateRandomArea(const int maxWidth, const int maxHeight)
{


    QList<QPointF> list;
    QList<QPointF> list2;

    QList<QPolygonF> squareList;

    int modd = QRandomGenerator::global()->generate()%200;


    const int w = 30;
    const int h = 30;
    const int offset = 200;

    //TODO: Düşük Polygon Sayısı ile Metre Kare Başına Ağaç Hesaplanacak
    for( int i = 0 ; i < 100/*qSqrt(maxHeight*maxWidth)/4*/ ; i++ ){

        if( i % 10 == 0 ){
            modd = QRandomGenerator::global()->generate()%offset;
        }


        auto x = QRandomGenerator::global()->generate()%(maxWidth-offset)+modd;
        auto y = QRandomGenerator::global()->generate()%(maxHeight-offset)+modd;
        list2.push_back({static_cast<qreal>(x),static_cast<qreal>(y)});

        if( squareList.isEmpty() ){
            QPolygonF poly;
            poly.append(QPointF(x-w/2,y-h/2));//topleft
            poly.append(QPointF(x-w/2,y+h/2));//bottomleft
            poly.append(QPointF(x+w/2,y+h/2));//bottomright

            poly.append(QPointF(x+w/2,y-h/2));//topright
            poly.append(QPointF(x-w/2,y-h/2));//topleft

            squareList.append(poly);
            list.push_back(QPointF(x,y));

        }else{

            bool appendable = true;

            for( const auto &item : squareList ){
                if( item.containsPoint(QPointF(x,y),Qt::FillRule::WindingFill ) ){
                    appendable = false;
                    break;
                }
            }

            QPolygonF poly;
            poly.append(QPointF(x-w/2,y-h/2));//topleft
            poly.append(QPointF(x-w/2,y+h/2));//bottomleft
            poly.append(QPointF(x+w/2,y+h/2));//bottomright

            poly.append(QPointF(x+w/2,y-h/2));//topright
            poly.append(QPointF(x-w/2,y-h/2));//topleft

            squareList.append(poly);

            if( appendable ){
                list.push_back(QPointF(x,y));
            }

        }

    }

    auto __list = Geometry::ConcaveHull::instance()->concavehull(list,0.5);
    this->setArea(__list);

    if( !this->List().size() ){
        qDebug() << "No Tree in List";
        return;
    }

    if( this->getPopulation().size() ) return;



    this->generateNoise();


    int index = 0;
    this->getPopulation().clear();
    for( int j = 0 ; j < this->AreaHeight() ; j++ ){

        for( int i = 0 ; i < this->AreaWidth() ; i++ ){

            auto _xPos = i;
            auto _yPos = j;

            if( this->polygonArea().containsPoint(QPointF(_xPos,_yPos),Qt::FillRule::OddEvenFill ) && mNoiseData[index] > 126){
                auto modY = LandScape::randomGenerator(-5,5);
                auto modX = LandScape::randomGenerator(-5,5);
                if( i%15 == 0 && j%15 == 0 ){
                    auto _random = LandScape::randomGenerator(0,this->List().size()-1);
                    auto asset = this->List().at(_random);
                    this->getPopulation().push_back(std::make_tuple(QPointF(i+modX,j+modY),asset));
                }
            }
            index++;
        }
    }

    mThread->start();
}

const std::vector<float> &Forest::noiseData() const
{
    return mNoiseData;
}

void Forest::startBuilding()
{
    mThread->start();
}

void Forest::generateNoise()
{
    Geometry::Noise::FastNoiseLite noiseGen;
    noiseGen.SetNoiseType(Geometry::Noise::FastNoiseLite::NoiseType_Value);
    noiseGen.SetFrequency(0.02);
    noiseGen.SetSeed(QRandomGenerator::global()->generate()%10000);

    mNoiseData.clear();
    int index = 0;
    for( int i = 0 ; i < this->AreaWidth() ; i++ ){
        for( int j = 0 ; j < this->AreaHeight() ; j++ ){
            mNoiseData.push_back((noiseGen.GetNoise((float)i, (float)j)+1)*255);
        }
    }

    auto [min,max] = std::ranges::minmax(mNoiseData);

    index = 0;
    for( int i = 0 ; i < this->AreaWidth() ; i++ ){
        for( int j = 0 ; j < this->AreaHeight() ; j++ ){
            mNoiseData[index] = (mNoiseData[index]-min)/(max-min)*255.0;
            index++;
        }
    }

}

void Forest::forestBuilder()
{


    QImage blur(this->AreaWidth(),this->AreaHeight(),QImage::Format_RGB888);


    for( int i = 0 ; i < this->AreaWidth() ; i++ ){
        for( int j = 0 ; j < this->AreaHeight() ; j++ ){
            if( this->polygonArea().containsPoint(QPointF(i,j),Qt::FillRule::WindingFill)
                    && i > 100
                    && j > 100
                    && i < this->AreaWidth() - 100
                    && j < this->AreaHeight() - 100){
                blur.setPixel(i,j,qRgb(0,0,0));
            }else{
                blur.setPixel(i,j,qRgb(255,255,255));
            }
        }
    }

    blur = blur.scaledToWidth(15,Qt::TransformationMode::SmoothTransformation);
    blur = blur.scaledToWidth(this->AreaWidth(),Qt::TransformationMode::SmoothTransformation);


    QImage pixmap(this->AreaWidth(),this->AreaHeight(),QImage::Format_ARGB32);
    QImage soil("bin/asset/soil.png");

    int index = 0;
    for( int i = 0 ; i < this->AreaWidth() ; i++ ){
        for( int j = 0 ; j < this->AreaHeight() ; j++ ){
            auto color = this->noiseData()[index++];
            auto pix = soil.pixel(i%soil.width(),j%soil.height());
            auto pixAlpha = blur.pixel(i%blur.width(),j%blur.height());
            auto alphaSmooth = static_cast<float>(qRed(pixAlpha)+qGreen(pixAlpha)+qBlue(pixAlpha))/(3.0*255.0);
            color *= (1-alphaSmooth);
            pixmap.setPixel(i,j,qRgba(qRed(pix),qGreen(pix),qBlue(pix),color));
        }
    }



    if( !mForestImage ){
        mForestImage = new QImage(this->AreaWidth()+50,this->AreaHeight()+50,QImage::Format_RGBA8888);
        mForestImage->fill(QColor(255,255,255,0));
    }
    QPainter painter;
    painter.begin(mForestImage);
    painter.drawImage(0,0,pixmap);
    for( const auto &[point,asset] : this->getPopulation() ){
        painter.drawPixmap(point.x()-asset.assetWidth()/2+25,point.y()-asset.assetHeight()+40,QPixmap(asset.assetPath().c_str()));
    }
    painter.drawPolygon(this->getArea());
    painter.end();

    this->updated();
}

QImage *Forest::forestImage() const
{
    return mForestImage;
}



} // namespace Plant
} // namespace Assets
