#ifndef __HPP_RESIZEDIALOG0x21003
#define __HPP_RESIZEDIALOG0x21003

#include <cplusplus_basic.hpp>
#include <QtWidgets/qwidget.h>
class QVBoxLayout;

class ResizeDialog : public QWidget {
    Q_OBJECT

private:
    using _Super=QWidget;
    class _PrivateResizeDialog;
    _PrivateResizeDialog *thisp=nullptr;
public:
    explicit ResizeDialog(QWidget * /**/=nullptr);
    virtual ~ResizeDialog();
    QVBoxLayout * getMainLayout() const;
public:
    Q_SIGNAL void valueChanged(int /* width */ , int /* height */ , double /* fx */ , double /* fy */ , int /*enum: interpolation */);
    Q_SLOT void emitValueChanged();
    QSize sizeHint() const override;
private:
    ResizeDialog(const ResizeDialog&)=delete;
    ResizeDialog(ResizeDialog&&)=delete;
    ResizeDialog&operator=(const ResizeDialog&)=delete;
    ResizeDialog&operator=(ResizeDialog&&)=delete;
private:
    CPLUSPLUS_OBJECT(ResizeDialog)
};

 #endif /**/

