/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include <OpenCVUtility.hpp>

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
/*绘制箭头*/
inline void draw_axis_array(
    QPainter * painter,
    double dx1,double dy1,
    double dx2,double dy2,
    double axix_len=100/*数轴长度*/,
    double array_len=30/*箭头长度*/,
    double array_weight=15/*箭头宽度*/
) {
    array_weight/=2;
    double len1=std::sqrt(dx1*dx1+dy1*dy1);
    double len2=std::sqrt(dy2*dy2+dx2*dx2);
    dx1/=len1; dy1/=len1;
    dx2/=len2; dy2/=len2;

    const double pox1_x=dx1*axix_len;
    const double pox1_y=dy1*axix_len;
    const double pox2_x=dx2*axix_len;
    const double pox2_y=dy2*axix_len;

    QPainterPath path_;
    path_.moveTo(0,0);
    path_.lineTo(pox1_x,pox1_y);
    path_.lineTo(pox1_x-dy1*array_weight,pox1_y+dx1*array_weight);
    path_.lineTo(pox1_x+dx1*array_len,pox1_y+dy1*array_len);
    path_.lineTo(pox1_x+dy1*array_weight,pox1_y-dx1*array_weight);
    path_.lineTo(pox1_x,pox1_y);

    path_.moveTo(0,0);
    path_.lineTo(pox2_x,pox2_y);
    path_.lineTo(pox2_x-dy2*array_weight,pox2_y+dx2*array_weight);
    path_.lineTo(pox2_x+dx2*array_len,pox2_y+dy2*array_len);
    path_.lineTo(pox2_x+dy2*array_weight,pox2_y-dx2*array_weight);
    path_.lineTo(pox2_x,pox2_y);

    painter->setPen(CosmeticQPen(QColor(222,52,152,222),3.2));
    painter->setBrush(QColor(255,62,132,232));
    painter->drawPath(path_);

}

}/*namespace*/

void MainWindow::openLua() {

    /*获得数据*/
    auto varInputData=qApp->getPoint2d();
    auto rows=varInputData.second-varInputData.first;

    static_assert(sizeof(*varInputData.first)
        ==sizeof(cv::Point2d),"");

    if (rows<2) { return; }

    cv::Mat dataWrap(rows,2,CV_64FC1,
        (cv::Point2d *)(varInputData.first));

    cv::PCA varPCA(dataWrap,{ /*mean*/ },
        cv::PCA::DATA_AS_ROW,
        2/*降阶后的维度*/);

    //varPCA.eigenvectors;特征向量，按行存储
    //varPCA.eigenvalues;特征值
    //varPCA.mean;平均值

    using namespace memory;
    auto && view=makeStackPointer<ImageShowWidget>();
    this->addWidget(view.release())->resize(800,600);

    auto && dataView=makeStackPointer<DataChartView>();
    view->setChartView(dataView.release());

    auto varSeries=addScatterSeries(dataView->dataChart(),
        varInputData.first,varInputData.second);
    varSeries->setPen(Qt::NoPen);
    varSeries->setBrush(QBrush(QColor(1,122,3,150)));
    fitChartAxisRange(dataView->dataChart(),
        varInputData.first,varInputData.second);

    dataView->setDrawFunction([mean=varPCA.mean,
        eigenvectors=varPCA.eigenvectors,
        xAxis=dataView->dataChart()->imageXAxis(),
        yAxis=dataView->dataChart()->imageYAxis()
    ](QPainter * painter,const QSizeF&) {
        auto distance=std::min(xAxis->max()-xAxis->min(),
            yAxis->max()-yAxis->min());
        distance*=.333;
        painter->save();
        painter->translate(mean.at<double>(0),mean.at<double>(1));
        /*绘制箭头*/
        draw_axis_array(painter,
            eigenvectors.at<double>(0,0),eigenvectors.at<double>(0,1),
            eigenvectors.at<double>(1,0),eigenvectors.at<double>(1,1),
            distance,distance*.15,distance*.05);
        painter->restore();
    });

}

/*End of the file.*/

