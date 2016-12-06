#ifndef __HPP_GRAYDIALOG0x21003
#define __HPP_GRAYDIALOG0x21003

#include <cplusplus_basic.hpp>
#include <QtWidgets/qwidget.h>
class QVBoxLayout;

class GrayDialog : public QWidget {
    Q_OBJECT

private:
    using _Super=QWidget;
    class _PrivateGrayDialog;
    _PrivateGrayDialog *thisp=nullptr;
public:
    explicit GrayDialog(QWidget * /**/=nullptr);
    virtual ~GrayDialog();
    QVBoxLayout * getMainLayout() const;
public:
    Q_SIGNAL void valueChanged(double /* RAlpha */ , double /* GAlpha */ , double /* BAlpha */ , double /* Beta */);
    Q_SLOT void emitValueChanged();
    QSize sizeHint() const override;
private:
    GrayDialog(const GrayDialog&)=delete;
    GrayDialog(GrayDialog&&)=delete;
    GrayDialog&operator=(const GrayDialog&)=delete;
    GrayDialog&operator=(GrayDialog&&)=delete;
private:
    CPLUSPLUS_OBJECT(GrayDialog)
};

 #endif /**/

