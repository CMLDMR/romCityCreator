#include "forestitem.h"
#include <QPainter>
#include <QTextItem>
#include "Asset/tree.h"

#include <QRgb>

namespace Widget {

ForestItem::ForestItem()
{

}

} // namespace Widget


QRectF Widget::ForestItem::boundingRect() const
{
    return QRectF(-totalWidth/2,-totalHeight,this->AreaWidth()+totalWidth,this->AreaHeight()+totalHeight);
}

void Widget::ForestItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->drawPixmap(0,0,getForestFloor());

    for( const auto &[point,asset] : this->getPopulation() ){
        painter->drawPixmap(point.x()-asset.assetWidth()/2,point.y()-asset.assetHeight(),QPixmap(asset.assetPath().c_str()));
        totalWidth = totalWidth < asset.assetWidth() ? asset.assetWidth() : totalWidth;
        totalHeight = totalHeight < asset.assetHeight() ? asset.assetHeight() : totalHeight;
    }

    //    painter->drawPolygon(this->getArea());
}




QPixmap Widget::ForestItem::getForestFloor()
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

    return QPixmap::fromImage(pixmap);
}

