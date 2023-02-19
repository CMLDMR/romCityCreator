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

    if( ElementItem::randomAreaTree == mCurrentElementType )
    {

        this->clear();
        addRect(0,0,3000,3000,QPen(QColor(Qt::black)));

        auto floorItem = addPixmap(QPixmap("://bin/asset/floor.jpg"));
        floorItem->setPos(0,0);

        {
            ForestItem* MmForestItem = new ForestItem();



            auto _width = LandScape::randomGenerator(100,2800);
            auto _heigth = LandScape::randomGenerator(100,2800);

            MmForestItem->setXPos(2900-_width);
            MmForestItem->setYPos(2900-_heigth);

            MmForestItem->populateRandomArea(_width,_heigth);

            mEcosystem->append(*MmForestItem);

            mForestRandomAreaItemList.push_back(MmForestItem);

            this->addItem(MmForestItem);
            MmForestItem->setPos(MmForestItem->getPosition());

//            qDebug() << MmForestItem->getPopulation().size() << MmForestItem->boundingRect().width()*MmForestItem->boundingRect().height();
        }

        {
            ForestItem* MmForestItem = new ForestItem();

            MmForestItem->setXPos(50);
            MmForestItem->setYPos(50);

            MmForestItem->populateRandomArea(LandScape::randomGenerator(750,1000),LandScape::randomGenerator(750,1000));

            mEcosystem->append(*MmForestItem);

            mForestRandomAreaItemList.push_back(MmForestItem);

            this->addItem(MmForestItem);
            MmForestItem->setPos(MmForestItem->getPosition());
        }

    }
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

    for( const auto &forestItem : mForestRandomAreaItemList ){
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

    this->setViewportUpdateMode(ViewportUpdateMode::FullViewportUpdate);

    this->setDragMode(QGraphicsView::DragMode::ScrollHandDrag);

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
    case ElementItem::mountain:
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
    mEcosystem = std::make_unique<Ecosystem::Ecosystem>();

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

    if( mCurrentElementType == ElementItem::mountain ){
        if( mMountainItem ){
            mMountainItem->setPos(QPointF(event->scenePos().x(),event->scenePos().y()));
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
            mDrawingLineItemList.push_back(mDrawingLineItem);

            mPolygon.append(QPoint(event->scenePos().x(),event->scenePos().y()));

        }else{
            mLineF.setP1(QPointF(event->scenePos().x(),event->scenePos().y()));
            mLineF.setP2(QPointF(event->scenePos().x(),event->scenePos().y()));
            mDrawingLineItem = this->addLine(mLineF);
                        mDrawingLineItemList.push_back(mDrawingLineItem);
            mPolygon.append(QPoint(event->scenePos().x(),event->scenePos().y()));
        }
    }

    if( mCurrentElementType == ElementItem::mountain ){
        if( !mMountainItem ){

            mMountainItem = new MountainItem();
            this->addItem(mMountainItem);
            mMountainItem->setPos(QPointF(event->scenePos().x(),event->scenePos().y()));

        }else{
            mMountainItem->setPos(QPointF(event->scenePos().x(),event->scenePos().y()));
        }
    }
}

void Widget::GraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if( mCurrentElementType == ElementItem::tree ){


        ForestItem* MmForestItem = new ForestItem();

        MmForestItem->setArea(mPolygon);

        int minx = INT32_MAX;
        int miny = INT32_MAX;

        for( const auto &item : mPolygon ){
            minx = minx > item.x() ? item.x() : minx;
            miny = miny > item.y() ? item.y() : miny;
        }


        MmForestItem->setXPos(minx);
        MmForestItem->setYPos(miny);

        MmForestItem->populateForest();

        mEcosystem->append(*MmForestItem);

        mForestItemList.push_back(MmForestItem);

        mPolygon.clear();

        this->addItem(MmForestItem);
        MmForestItem->setPos(MmForestItem->getPosition());
        for( auto item : mDrawingLineItemList ){
            this->removeItem(item);
        }
        mDrawingLineItem = nullptr;
    }

    if( mCurrentElementType == ElementItem::randomAreaTree ){

        ForestItem* MmForestItem = new ForestItem();


        MmForestItem->setXPos(event->scenePos().x()-500);
        MmForestItem->setYPos(event->scenePos().y()-500);

        MmForestItem->populateRandomArea(1000,1000);
//        MmForestItem->setX(event->scenePos().x());
//        MmForestItem->setY(event->scenePos().y());

        mEcosystem->append(*MmForestItem);

        mForestRandomAreaItemList.push_back(MmForestItem);

        mPolygon.clear();

        this->addItem(MmForestItem);
        MmForestItem->setPos(MmForestItem->getPosition());

    }


    if( mCurrentElementType == ElementItem::mountain ){
        mMountainItem = nullptr;
    }
    this->setCurrentElementType(ElementItem::null);
}



