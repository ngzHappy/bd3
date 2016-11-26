#ifndef __HPP_RGBADIALOG0x21003
#define __HPP_RGBADIALOG0x21003

#include <cplusplus_basic.hpp>
#include <QtWidgets/qwidget.h>
class QVBoxLayout;

class RGBADialog : public QWidget {
    Q_OBJECT

private:
    using _Super=QWidget;
    class _PrivateRGBADialog;
    _PrivateRGBADialog *thisp=nullptr;
public:
    explicit RGBADialog(QWidget * /**/=nullptr);
    virtual ~RGBADialog();
    QVBoxLayout * getMainLayout() const;
public:
    Q_SIGNAL void valueChanged(double /* RAlpha */ , double /* RBeta */ , double /* GAlpha */ , double /* GBeta */ , double /* BAlpha */ , double /* BBeta */ , double /* AAlpha */ , double /* ABeta */);
    Q_SLOT void emitValueChanged();
    QSize sizeHint() const override;
private:
    RGBADialog(const RGBADialog&)=delete;
    RGBADialog(RGBADialog&&)=delete;
    RGBADialog&operator=(const RGBADialog&)=delete;
    RGBADialog&operator=(RGBADialog&&)=delete;
private:
    CPLUSPLUS_OBJECT(RGBADialog)
};

 #endif /**/

