/*MainWindow.cpp*/
#include "MainWindow.hpp"
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

namespace {

QList<QPointF> genEllipse(
    const cv::RotatedRect & argRect,
    bool argNeedClose=false) {
    enum  {SIZE=100};
    typedef double eval_type;
    auto varSize= argRect.size;
    if (varSize.width<=0) { return{}; }
    if (varSize.height<=0) { return{}; }
    QList<QPointF> varAns;
    varAns.reserve(SIZE+argNeedClose);
    const eval_type varA=varSize.width/2;
    const eval_type varB=varSize.height/2;
    constexpr const eval_type varStep=(3.141592654/SIZE)*2;
    eval_type varAngle=0;
    for (std::int_fast32_t i=0; i<SIZE;++i) {
        varAns.push_back({
            varA*std::cos(varAngle),
            varB*std::sin(varAngle) });
        varAngle+=varStep;
    }
    varAngle=argRect.angle/180*3.141592654;
    const eval_type a00=std::cos(varAngle);
    const eval_type a10=std::sin(varAngle);
    const eval_type a01=-a10;
    const eval_type a11=a00;
    const auto &varCenter=argRect.center;
    for (auto & i:varAns) {
        const eval_type varX=i.x()*a00+i.y()*a01+varCenter.x;
        const eval_type varY=i.x()*a10+i.y()*a11+varCenter.y;
        i.setX(varX); i.setY(varY);
    }
    if(argNeedClose){
        varAns.push_back(varAns.first());
    }
    return std::move(varAns);
}

}

void MainWindow::openLua() {
    using namespace memory;
    /*获得数据*/
    auto points2d=qApp()->getPoint2d();
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
        series->setPen(QPen(QColor(233,6,2),0));
        series->setBrush(QColor(233,6,2));
    }      

    addWidget(mainView.release())->resize(600,600);

    /*opencv 曲线拟合*/
    try {
        std::vector<cv::Point2f,memory::Allocator<cv::Point2f>>
            input_data;
        input_data.reserve(rows);
        for (auto i=points2d.first;i!=points2d.second;++i) {
            input_data.emplace_back(
                static_cast<cv::Point2f::value_type>(i->x()),
                static_cast<cv::Point2f::value_type>(i->y())
            );
        }
        cv::Mat data(
            rows,
            cols/*2*/,
            cv::DataType<cv::Point2f::value_type>::type,
            input_data.data()
        );
        auto rect=cv::fitEllipse(data);

        {
            addLineSeries(chart,genEllipse(rect,true))
                ->setPen(QPen(QColor(2,215,4),1.6));
        }
    }
    catch (...) {
        CPLUSPLUS_EXCEPTION(false);
    }
}

/*End of the file.*/

