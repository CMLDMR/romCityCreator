#include "graphicsview.h"

#include <QMouseEvent>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QPixmap>
#include <QLine>

#include <QDebug>

#include <QGraphicsSceneMouseEvent>



namespace Widget {

void GraphicsScene::setCurrentElementType(ElementItem newCurrentElementType)
{
    mCurrentElementType = newCurrentElementType;

}

void GraphicsScene::renderScene()
{
    this->clear();
    mDrawingLineItem = nullptr;

    addRect(0,0,3000,3000,QPen(QColor(Qt::black)));

    auto floorItem = addPixmap(QPixmap("://bin/asset/floor.jpg"));
    floorItem->setPos(0,0);

    for( const auto &forestItem : mForestItemList ){
        addItem(forestItem);
        forestItem->setPos(forestItem->getPosition());
    }
}



GraphicsView::GraphicsView(QWidget *parent)
    :QGraphicsView(parent)
{

    this->setMouseTracking(true);

    mScene = new GraphicsScene(this);

    mScene->installEventFilter(this);

    this->setScene(mScene);
}

void GraphicsView::setCurrentDrawingElement(const ElementItem &itemType)
{
    mScene->setCurrentElementType(itemType);
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



GraphicsScene::GraphicsScene(QObject *parent)
    :QGraphicsScene(parent)
{
    renderScene();
}



} // namespace Widget

void Widget::GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if( mCurrentElementType == ElementItem::tree ){
        if( mDrawingLineItem ){
            mLineF.setP2(QPointF(event->scenePos().x(),event->scenePos().y()));
            mDrawingLineItem->setLine(mLineF);
        }
    }
}

void Widget::GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if( mCurrentElementType == ElementItem::tree ){
        if( !mDrawingLineItem ){
            mPolygon.clear();

            mLineF.setP1(QPointF(event->scenePos().x(),event->scenePos().y()));
            mLineF.setP2(QPointF(event->scenePos().x(),event->scenePos().y()));
            mDrawingLineItem = this->addLine(mLineF);

            mPolygon.append(QPoint(event->scenePos().x(),event->scenePos().y()));

        }else{
            mLineF.setP1(QPointF(event->scenePos().x(),event->scenePos().y()));
            mLineF.setP2(QPointF(event->scenePos().x(),event->scenePos().y()));
            mDrawingLineItem = this->addLine(mLineF);
            mPolygon.append(QPoint(event->scenePos().x(),event->scenePos().y()));
        }
    }
}

void Widget::GraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if( mCurrentElementType == ElementItem::tree ){

        ForestItem* MmForestItem = new ForestItem();

        MmForestItem->setArea(mPolygon);

        mForestItemList.push_back(MmForestItem);

        mPolygon.clear();

        this->addItem(MmForestItem);
        MmForestItem->setPos(MmForestItem->getPosition());
        this->removeItem(mDrawingLineItem);
        mDrawingLineItem = nullptr;
    }
    this->setCurrentElementType(ElementItem::null);
}



