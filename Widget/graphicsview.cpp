#include "graphicsview.h"

#include <QMouseEvent>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QPixmap>
#include <QLine>

#include <QDebug>


namespace Widget {

GraphicsView::GraphicsView(QWidget *parent)
    :QGraphicsView(parent)
{

    this->setMouseTracking(true);

    mScene = new GraphicsScene(this);

    this->setScene(mScene);

    this->renderScene();



    this->setViewportUpdateMode(ViewportUpdateMode::FullViewportUpdate);

    mDrawingLineItem = nullptr;


}

void GraphicsView::setCurrentDrawingElement(const ElementItem &itemType)
{
    mCurrentElementType = itemType;
    switch (mCurrentElementType) {
    case ElementItem::null:
        this->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        break;

    case ElementItem::tree:
    {
        QPixmap cursorPix(":/icon/bin/icon/icons8-arrow-cursor-91.png");
        QCursor cursor(cursorPix,0,0);
        this->setCursor(cursor);
    }
        break;
    default:
        break;
    }
}

void GraphicsView::renderScene()
{

    this->mScene->clear();
    mDrawingLineItem = nullptr;

    mScene->addRect(0,0,3000,3000,QPen(QColor(Qt::black)));

    for( const auto &polygonItem : mPolygonList ){
        double meanx{0};
        double meany{0};
        QPolygonF PolygonArea;

        if( polygonItem.pointList().size() ){
            auto list = polygonItem.pointList();
            auto polygonItem = mScene->addPolygon(QPolygonF(list));
            for( const auto &point : list ){
                meanx += static_cast<double>(point.x());
                meany += static_cast<double>(point.y());
                PolygonArea.append(point);
            }
        }
        PolygonArea.append(polygonItem.pointList().first());



        std::uint64_t treeCount{0};
        std::uint64_t areaCount{0};
        std::uint64_t outsideAreaCount{0};
        std::uint64_t totalAreaCount{0};

        auto boundingRect = PolygonArea.boundingRect();
        QList<QPointF> areaPointList;


        for( int j = 0 ; j < boundingRect.height() ; j++ ){

            for( int i = 0 ; i < boundingRect.width() ; i++ ){
                auto _xPos = boundingRect.x()+i;
                auto _yPos = boundingRect.y()+j;

                if( PolygonArea.containsPoint(QPointF(_xPos,_yPos),Qt::FillRule::OddEvenFill ) ){
                    areaCount++;
                    auto modY = randomGenerator(0,30);
                    auto modX = randomGenerator(0,30);

                    if( i%20 == 0 && j%30 == 0 ){
                        auto treePixMap = QPixmap("://bin/asset/tree/tree1.png");
                        auto treeItem = mScene->addPixmap(QPixmap("://bin/asset/tree/tree1.png"));
                        treeItem->setPos(boundingRect.x()+i-treePixMap.width()/2+modX,boundingRect.y()+j-treePixMap.height()+modY);
                        treeCount++;
                    }


                    //                    areaPointList.push_back(QPointF(boundingRect.x()+i,boundingRect.y()+j));

                }else{
                    outsideAreaCount++;
                }
                totalAreaCount++;
            }
        }


        meanx = meanx/static_cast<double>(polygonItem.pointList().size());
        meany = meany/static_cast<double>(polygonItem.pointList().size());
        auto textItem = mScene->addText(QString("Ağaç Alanı %1 Ağaç Sayısı: %2  Polygon Closed: %3  OutSide: %4 Total %5  w*h %6")
                                        .arg(areaCount)
                                        .arg(treeCount)
                                        .arg(PolygonArea.isClosed())
                                        .arg(outsideAreaCount)
                                        .arg(totalAreaCount)
                                        .arg(boundingRect.width()*boundingRect.height()));
        textItem->setPos(meanx,meany+200);
    }

}

GraphicsScene::GraphicsScene(QObject *parent)
    :QGraphicsScene(parent)
{

}

QList<QPointF> TreeArea::pointList() const
{
    return mPList;
}

} // namespace Widget


void Widget::GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if( mCurrentElementType == ElementItem::tree ){
        if( mDrawingLineItem ){
            mLineF.setP2(QPointF(event->pos().x(),event->pos().y()));
            mDrawingLineItem->setLine(mLineF);
            mScene->update();
        }
    }
}


void Widget::GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if( mCurrentElementType == ElementItem::tree ){
        if( !mDrawingLineItem ){
            mPolygon.clear();

            mLineF.setP1(QPointF(event->pos().x(),event->pos().y()));
            mLineF.setP2(QPointF(event->pos().x(),event->pos().y()));
            mDrawingLineItem = mScene->addLine(mLineF);

            mPolygon.append(QPoint(event->pos().x(),event->pos().y()));

        }else{
            mLineF.setP1(QPointF(event->pos().x(),event->pos().y()));
            mLineF.setP2(QPointF(event->pos().x(),event->pos().y()));
            mDrawingLineItem = mScene->addLine(mLineF);
            mPolygon.append(QPoint(event->pos().x(),event->pos().y()));
        }
    }
}


void Widget::GraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if( mCurrentElementType == ElementItem::tree ){
        mPolygonList.push_back(mPolygon);
    }

    this->setCurrentDrawingElement(ElementItem::null);
    this->renderScene();
}
