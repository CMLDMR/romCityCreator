#ifndef WIDGET_GRAPHICSVIEW_H
#define WIDGET_GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include <QPolygon>
#include <random>
#include <memory>


#include "forestitem.h"
#include "mountainitem.h"
#include "Ecosystem/ecosystem.h"


class QGraphicsLineItem;

namespace Widget {

class GraphicsScene;

enum class ElementItem{
    null = 0,
    tree,
    randomAreaTree,
    mountain
};


class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QWidget* parent = nullptr );
    void setCurrentDrawingElement( const ElementItem &itemType );

private:
    GraphicsScene* mScene;
    ElementItem mCurrentElementType;
};



class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene(QObject* parent = nullptr );

    // QGraphicsScene interface
    void setCurrentElementType( ElementItem newCurrentElementType );

    void renderScene();


protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QList<QPointF> mPolygon;

    ElementItem mCurrentElementType;

    ForestItem* mForestItem{nullptr};
    QList<ForestItem*> mForestItemList;
    QList<ForestItem*> mForestRandomAreaItemList;

    std::unique_ptr<Ecosystem::Ecosystem> mEcosystem;

    QGraphicsLineItem* mDrawingLineItem;
    QLineF mLineF;
    QList<QGraphicsLineItem*> mDrawingLineItemList;


    MountainItem* mMountainItem{nullptr};
};

} // namespace Widget

#endif // WIDGET_GRAPHICSVIEW_H
