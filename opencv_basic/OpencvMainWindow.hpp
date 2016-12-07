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

    /*加载图片回调函数*/
    virtual QWidget* addImage(const QImage &);
    /*打开lua回调函数*/
    virtual void openLua();

    template<typename _Tb,typename _Te>
    void addImage(_Tb b,const _Te&e);
    void addImage(const QPair<const QString *,const QString *>&arg);
    /*
    begin add image it will return 1
    ++1 on add a image
    end add image it will return -1
    just add a image return 0
    */
    int addImageIndex()const;
private:
    void _p_open_image();
    void _p_open_lua();
    void _p_begin_add_image();
    void _p_end_add_image();
    void _p_finished_add_a_image();
    class _AddImageState {
        OpencvMainWindow *const _p_m;
    public:
        _AddImageState(OpencvMainWindow *a):_p_m(a) { a->_p_begin_add_image(); }
        ~_AddImageState() { _p_m->_p_end_add_image(); }
    };
    void paintEvent(QPaintEvent *)override;
private:
    CPLUSPLUS_OBJECT(OpencvMainWindow)
};

template<typename _Tb,typename _Te>
void  OpencvMainWindow::addImage(_Tb b,const _Te&e) {
    _AddImageState _{this};
    for (; b!=e;++b) {
        this->addImage(*b);
        _p_finished_add_a_image();
    }
}

#endif // OPENCVMAINWINDOW_HPP
