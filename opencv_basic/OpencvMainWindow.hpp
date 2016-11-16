#ifndef OPENCVMAINWINDOW_HPP
#define OPENCVMAINWINDOW_HPP

#include "OpenCVBasic.hpp"
#include <QtWidgets/qwidget.h>
class ImageShowWidget;
class QMdiSubWindow;

class OPENCV3_BASICHARED_EXPORT OpencvMainWindow : public QWidget
{
    Q_OBJECT

private:
    using _Super=QWidget;
    class _PrivateOpencvMainWindow;
    _PrivateOpencvMainWindow * _mp;
public:
    ~OpencvMainWindow();
    OpencvMainWindow(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());

    QMdiSubWindow * addWidget(ImageShowWidget*);
    virtual void addImage(const QImage &);
private:
    CPLUSPLUS_OBJECT(OpencvMainWindow)
};

#endif // OPENCVMAINWINDOW_HPP
