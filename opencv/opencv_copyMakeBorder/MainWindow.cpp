/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include <OpenCVUtility.hpp>
#include "CopyMakeBorderDialog.hpp"

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

namespace {

class ImageWidget;
class ScalarLineEdit :public QLineEdit{
    QString old_value;
    cv::Scalar value;
    ImageWidget * super;
public:
    ScalarLineEdit(ImageWidget * arg):super(arg) {
        old_value="100,150,200,200";
        this->setText(old_value);
        connect(this,&QLineEdit::editingFinished,
            this,&ScalarLineEdit::onEditingFinished);
    }

    bool directOnEditingFinished() {
        const auto varText=this->text();
        if (old_value==varText) { return false; }
        old_value=varText;
        const auto varValues=varText.split(',',QString::SkipEmptyParts);
        value=cv::Scalar::all(0);
        
        auto varBegin=varValues.constBegin();
        const auto varEnd=varValues.constEnd();
        const auto varSize=std::min(5,varValues.size());
        for (int i=0; i<varSize;++i,++varBegin) {
            value[i]=varBegin->toDouble();
        }
        return true;
    }

    inline void onEditingFinished();

    cv::Scalar getValue()  { 
        directOnEditingFinished();
        return value;
    }

private:
    CPLUSPLUS_OBJECT(ScalarLineEdit)
};

class ImageWidget :public ImageShowWidget {
    CopyMakeBorderDialog * _p_dialog;
    ScalarLineEdit * _p_ScalarLineEdit;
public:
    ImageWidget(const QImage &arg) {

        /*转型为rgba*/
        QImage rgbaImage=
            arg.convertToFormat(QImage::Format_RGBA8888);

        /*设置原始图片*/
        this->setImage(rgbaImage);

        auto && widget=memory::makeStackPointer<CopyMakeBorderDialog>();
        this->addImageWidget(widget.release(),
            Qt::RightDockWidgetArea,
            QString::fromUtf8(u8R"(控制面板)"));
        connect(widget.pointer(),&CopyMakeBorderDialog::valueChanged,
            this,&ImageWidget::valueChanged);

        auto && scalarLineEdit=
            memory::makeStackPointer<ScalarLineEdit>(this);
        widget->getMainLayout()->addWidget(
            scalarLineEdit.release());
        _p_dialog=widget.pointer();
        _p_ScalarLineEdit=scalarLineEdit.pointer();

        /*update values*/
        widget->emitValueChanged();
    }

    void emitValueChanged() {
        _p_dialog->emitValueChanged();
    }

    void valueChanged(
        int top,
        int bottom,
        int left,
        int right,
        int borderType) {

        this->setAlgorithm(
        [=](const QImage & inputImage)->QImage {
            try {
                cv::Mat inputMat(inputImage.height(),
                    inputImage.width(),
                    CV_8UC4,
                    const_cast<uchar*>(inputImage.constBits()),
                    inputImage.bytesPerLine());

                QImage outputImage(inputImage.width()+left+right,
                    inputImage.height()+top+bottom,
                    QImage::Format_RGBA8888);

                cv::Mat outputMat(outputImage.height(),
                    outputImage.width(),
                    CV_8UC4,
                    const_cast<uchar*>(outputImage.constBits()),
                    outputImage.bytesPerLine());

                cv::copyMakeBorder(inputMat,outputMat,
                    top,bottom,left,right,borderType,
                    _p_ScalarLineEdit->getValue());

                return std::move(outputImage);
            }
            catch (...) {
                CPLUSPLUS_EXCEPTION(false);
                return inputImage;
            }
        });


    }
private:
    CPLUSPLUS_OBJECT(ImageWidget)
};

void ScalarLineEdit::onEditingFinished() {
    if (false==this->directOnEditingFinished()) {
        return; 
    }
    super->emitValueChanged();
}

}/*namespace*/


/*write your code here*/
QWidget* MainWindow::addImage(const QImage &arg) {
    if (addImageIndex()<0) { return nullptr; }
    if (arg.isNull()) { return nullptr; }

    using namespace memory;
    auto && widget=makeStackPointer<ImageWidget>(arg);
    this->addWidget(widget.release());
    return widget;
}

void MainWindow::openLua() {
    return _Super::openLua();
}

/*End of the file.*/

