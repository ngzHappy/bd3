#ifndef OPENCVMAINWINDOW_HPP
#define OPENCVMAINWINDOW_HPP

#include "OpenCVBasic.hpp"
#include <QtWidgets/qmainwindow.h>
class ImageShowWidget;
class QMdiSubWindow;

class OPENCV3_BASICHARED_EXPORT OpencvMainWindow : public QMainWindow
{
    Q_OBJECT

private:
    using _Super=QMainWindow;
    class _PrivateOpencvMainWindow;
    _PrivateOpencvMainWindow * _mp;
public:
    ~OpencvMainWindow();
    OpencvMainWindow(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());

    QMdiSubWindow * addWidget(ImageShowWidget*);
    virtual QWidget* addImage(const QImage &);

    template<typename _Tb,typename _Te>
    void addImage(_Tb b,const _Te&e);
    void addImage(const QPair<const QString *,const QString *>&arg);
private:
    void _p_open_image();
private:
    CPLUSPLUS_OBJECT(OpencvMainWindow)
};

template<typename _Tb,typename _Te>
void  OpencvMainWindow::addImage(_Tb b,const _Te&e) {
    for (; b!=e;++b) {
        this->addImage(*b);
    }
}

#endif // OPENCVMAINWINDOW_HPP
