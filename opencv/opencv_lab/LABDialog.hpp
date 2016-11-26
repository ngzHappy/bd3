#ifndef __HPP_LABDIALOG0x21003
#define __HPP_LABDIALOG0x21003

#include <cplusplus_basic.hpp>
#include <QtWidgets/qwidget.h>
class QVBoxLayout;

class LABDialog : public QWidget {
    Q_OBJECT

private:
    using _Super=QWidget;
    class _PrivateLABDialog;
    _PrivateLABDialog *thisp=nullptr;
public:
    explicit LABDialog(QWidget * /**/=nullptr);
    virtual ~LABDialog();
    QVBoxLayout * getMainLayout() const;
public:
    Q_SIGNAL void valueChanged(double /* LAlpha */ , double /* LBeta */ , double /* AAlpha */ , double /* ABeta */ , double /* BAlpha */ , double /* BBeta */);
    Q_SLOT void emitValueChanged();
    QSize sizeHint() const override;
private:
    LABDialog(const LABDialog&)=delete;
    LABDialog(LABDialog&&)=delete;
    LABDialog&operator=(const LABDialog&)=delete;
    LABDialog&operator=(LABDialog&&)=delete;
private:
    CPLUSPLUS_OBJECT(LABDialog)
};

 #endif /**/

