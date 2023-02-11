#include "graphicsview.h"

#include <QMouseEvent>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QPixmap>
#include <QLine>

#include <QDebug>

#include "treeitem.h"


namespace Widget {

GraphicsView::GraphicsView(QWidget *parent)
    :QGraphicsView(parent)
{

    this->setMouseTracking(true);

    mScene = new GraphicsScene(this);

    this->setScene(mScene);

    this->renderScene();



//    this->setViewportUpdateMode(ViewportUpdateMode::FullViewportUpdate);

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

    auto floorItem = mScene->addPixmap(QPixmap("://bin/asset/floor.jpg"));
    floorItem->setPos(0,0);

    for( const auto &forestItem : mForestItemList ){
        mScene->addItem(forestItem);
        forestItem->setPos(forestItem->getPosition());
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
//            mScene->update();
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

        ForestItem* MmForestItem = new ForestItem();

        MmForestItem->setArea(mPolygon.pointList());

        mForestItemList.push_back(MmForestItem);

        mPolygon.clear();

//        mPolygonList.push_back(mPolygon);

        mScene->addItem(MmForestItem);
        MmForestItem->setPos(MmForestItem->getPosition());
        mScene->removeItem(mDrawingLineItem);
        mDrawingLineItem = nullptr;

    }

    this->setCurrentDrawingElement(ElementItem::null);
//    this->renderScene();
}
