/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include <OpenCVUtility.hpp>
#include <vector>
#include <algorithm>

class MainWindow::_PrivateMainWindow {
public:
private:
    CPLUSPLUS_OBJECT(_PrivateMainWindow)
};

MainWindow::MainWindow(QWidget *parent):
    _Super(parent) {
    _thisp=new _PrivateMainWindow;
}

MainWindow::~MainWindow() {
    delete _thisp;
}

/*write your code here*/
QWidget* MainWindow::addImage(const QImage &arg) {
    return _Super::addImage(arg);
}

void MainWindow::openLua() {
    using namespace memory;
    /*获得数据*/
    auto points2d=qApp->getPoint2d();
    /*检查数据*/
    auto rows=(points2d.second-points2d.first);
    constexpr auto cols=2;
    if (rows<0) {
        return;
    }
    /*设置视图*/
    auto&& mainView=makeStackPointer<ImageShowWidget>();
    auto&& view=makeStackPointer<DataChartView>();

    mainView->setChartView(view.release());
    auto chart=view->dataChart();
    /*调整坐标轴*/
    fitChartAxisRange(chart,points2d.first,points2d.second);

    {
        auto series=
            addScatterSeries(chart,points2d.first,points2d.second);
        series->setPen(QPen(QColor(203,6,2,200),1));
        series->setBrush(QColor(233,6,2,198/2));
    }

    addWidget(mainView.release())->resize(800,600);

    /*opencv 曲线拟合*/
    try {
        auto input_data=
            toCVFloat32Point2Vector(points2d.first,points2d.second);
        cv::Mat data(
            rows,
            cols/*2*/,
            cv::DataType<cv::Point2f::value_type>::type,
            input_data.data()
        );

        auto rect=cv::fitEllipse(data);

        view->setDrawFunction([cx=static_cast<qreal>(rect.center.x),
        cy=static_cast<qreal>(rect.center.y),
        angle=static_cast<qreal>(rect.angle),
        ewidth=rect.size.width/2.0,
        eheight=rect.size.height/2.0](
            QPainter * painter,const QSizeF&) {
            painter->translate(cx,cy);
            painter->rotate(angle/*deg*/);
            painter->setPen(CosmeticQPen(QColor(55,113,100),2));
            painter->drawEllipse({ 0,0 },ewidth,eheight);
        });

    }
    catch (...) {
        CPLUSPLUS_EXCEPTION(false);
    }
}

/*End of the file.*/

