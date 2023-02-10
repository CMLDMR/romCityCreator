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
        if( polygonItem.pointList().size() ){
            auto list = polygonItem.pointList();
            auto polygonItem = mScene->addPolygon(QPolygonF(list));
        }
    }


}

GraphicsScene::GraphicsScene(QObject *parent)
    :QGraphicsScene(parent)
{

}

QList<QPointF> Polygon::pointList() const
{
    return mPList;
}

} // namespace Widget


void Widget::GraphicsView::mouseMoveEvent(QMouseEvent *event)
{

    qDebug() << " MouseMove Event: " << event->pos().x() << event->pos().y();

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
    qDebug() << " Mouse Release: " << event->pos().x() << event->pos().y();


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
    mPolygonList.push_back(mPolygon);
    this->setCurrentDrawingElement(ElementItem::null);
    this->renderScene();
}
