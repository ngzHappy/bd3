/*MainWindow.cpp*/
#include <vector>
#include "MainWindow.hpp"
#include <OpenCVUtility.hpp>

class MainWindow::_PrivateMainWindow{
public:
private:
    CPLUSPLUS_OBJECT(_PrivateMainWindow)
};

MainWindow::MainWindow(QWidget *parent) :
    _Super(parent){
    _thisp=new _PrivateMainWindow;
}

MainWindow::~MainWindow(){
     delete _thisp;
}

/*write your code here*/
QWidget* MainWindow::addImage(const QImage &arg) {
    return _Super::addImage(arg);
}

namespace  {
template<typename T>
using vector=std::vector<T,memory::Allocator<T>>;
}

#include <cmath>
#include <cstdlib>

void MainWindow::openLua(){
    //return _Super::openLua();

    constexpr auto rows=1024;
    constexpr auto cols=1024;
    constexpr double step_y=4./rows;
    constexpr double step_x=4./cols;

    vector<vector<int>> hist;
    hist.resize(rows);
    for(auto &i:hist){
        i.resize(cols);
        
    }
      
  //    auto a=-10.7;
  // auto b=-1.09;
  //   auto c=-.8156;
  //auto d=-21.12;

  
   auto a=-12.7;
   auto b=-1.09;
   auto c=-.816;
   auto d=-2.12;
 

    auto posx_max=cols-1;
    auto posy_max=rows-1;
    auto count_max=1.;

    std::ofstream ofs("xxx.txt");


    auto x=20.1111242432;
    auto y=564.447152;

    for(int k=0;k<10240;++k)
    for (int i=0; i<(1024*1024);++i) {
        
        auto xn=std::sin(a*y)-std::cos(b*x);
        auto yn=std::sin(c*x)-std::cos(d*y);

 /*       if ((i&255)==0) {
            a+=(std::rand()&4095)/4096.;
            c+=(std::rand()&4095)/4096.;
            d+=(std::rand()&4095)/4096.;
            b+=(std::rand()&4095)/4096.;
        }*/

        auto posx=static_cast<int>( std::max(0.0, (xn+2)/step_x) );
        auto posy=static_cast<int>( std::max(0.0, (yn+2)/step_y ) );

       // ofs<<xn<<","<<yn<<std::endl;

        posx=std::min(posx,posx_max);
        posy=std::min(posy,posy_max);

        auto &currentHist=hist[posy][posx];
        ++currentHist;

        count_max=std::max<decltype(1.)>(count_max,currentHist);

        x=xn ;
        y=yn ;

    }

    count_max = 255.6/count_max;

    cv::Mat mat(rows,cols,CV_8UC1);

    auto datai= mat.data;
    auto step=mat.step[0];
    for (auto i=0; i<rows;++i,datai+=step) {
        auto dataj=datai;
        for (auto j=0; j<cols;++j,++dataj) {
            auto &currentHist=hist[i][j];
            *dataj=(unsigned char)(static_cast<int>(
                currentHist*count_max));
             
        }
    }

    {
        QOpencvImage image;
        image.fromOpencvMat(mat);
        this->addImage(image);
    }

    cv::equalizeHist(mat,mat);

    {
        QOpencvImage image;
        image.fromOpencvMat(mat);
        this->addImage(image);
    }

}

/*End of the file.*/

