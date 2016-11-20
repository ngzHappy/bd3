/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include <vector>
#include <algorithm>
#include <OpenCVUtility.hpp>
#include <QtWidgets/qdialog.h>

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
    if (addImageIndex()<0) { return nullptr; }
    if (arg.isNull()) { return nullptr; }
    QString saveFileName=QFileDialog::getSaveFileName(nullptr);
    if (saveFileName.isEmpty()) { return nullptr; } {
        QFileInfo info(saveFileName);
        if (info.suffix().trimmed().isEmpty()) {
            saveFileName+=".lua";
        }
    }
    try {
        QOpencvImage img=arg.convertToFormat(QImage::Format_Grayscale8);
        auto inputImage=img.toOpencvRef();
        std::vector<std::vector<cv::Point>> ans;
        cv::findContours(inputImage,ans,
                                  cv::RETR_EXTERNAL,
                                  cv::CHAIN_APPROX_SIMPLE);
        if (ans.empty()) { return nullptr; }
        std::sort(ans.begin(),ans.end(),
            [](const auto &a,const auto &b) {
            return a.size()>b.size();
        });

        double xmax=0; double ymax=0;
        for (const auto &i:ans[0]) {
            if (i.x>xmax) { xmax=i.x; }
            if (i.y>ymax) { ymax=i.y; }
        }

        if (xmax==0) { return nullptr; }
        if (ymax==0) { return nullptr; }

        std::vector<QPointF,memory::Allocator<QPointF>> varData;
        varData.reserve(ans[0].size());

        for (const auto &i:ans[0]) {
            varData.emplace_back(
                i.x/xmax,i.y/ymax
            );
        }

        QFile varFile(saveFileName);
        if (varFile.open(QIODevice::WriteOnly)) {
            QTextStream stream(&varFile);
            stream.setCodec("UTF-8");
            stream<<bom;
            stream<<u8R"~=:;:=~(

local application={
input_data_2d={
)~=:;:=~";
            int j=-1;
            for (const auto &i:varData) {
                stream<<QLatin1Literal("--[[",4);
                {
                    ++j; j&=7;
                    stream<<(j);
                }
                stream<<QLatin1Literal("--]]",4);
                stream<<QLatin1Literal("{",1);
                stream<<i.x();
                stream<<QLatin1Literal(",",1);
                stream<<i.y();
                stream<<QLatin1Literal("},\n",3);
            }

            stream<<u8R"~=:;:=~(

}--[[-input_data_2d--]]
}--[[-application--]]

return application;

)~=:;:=~";
        }
        return nullptr;
    }
    catch (...) {
        CPLUSPLUS_EXCEPTION(false);
    }
    return nullptr;
}

void MainWindow::openLua() {
    return _Super::openLua();
}

/*End of the file.*/

