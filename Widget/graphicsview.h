#ifndef WIDGET_GRAPHICSVIEW_H
#define WIDGET_GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include <QPolygon>
#include <random>


class QGraphicsLineItem;

namespace Widget {

class GraphicsScene;





enum class ElementItem{
    null = 0,
    tree
};


class TreeArea
{
public:
    TreeArea(){}


    QList<QPointF> pointList() const;

    void append( const QPointF &point){
        mPList.append(point);
    }

    void clear(){
        mPList.clear();
    }

private:
    QList<QPointF> mPList;


};



static int randomGenerator( const int &min, const int &max ){

    // Seed with a real random value, if available
    std::random_device r;

    // Choose a random mean between 1 and 6
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(min, max);
    int mean = uniform_dist(e1);
    return mean;

}






class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget* parent = nullptr );

    void setCurrentDrawingElement(const ElementItem &itemType);


private:
    GraphicsScene* mScene;
    ElementItem mCurrentElementType;

    TreeArea mPolygon;
    QList<TreeArea> mPolygonList;



    void renderScene();

    QGraphicsLineItem* mDrawingLineItem;
    QLineF mLineF;




    // QWidget interface
protected:
    virtual void mouseMoveEvent(QMouseEvent *event) override;


    virtual void mouseReleaseEvent(QMouseEvent *event) override;

    // QWidget interface
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
};



class GraphicsScene : public QGraphicsScene
{
public:
    GraphicsScene(QObject* parent = nullptr );
};

} // namespace Widget

#endif // WIDGET_GRAPHICSVIEW_H
