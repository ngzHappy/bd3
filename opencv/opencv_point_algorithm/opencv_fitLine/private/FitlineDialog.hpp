#ifndef __HPP_FITLINEDIALOG0x21003
#define __HPP_FITLINEDIALOG0x21003

#include <cplusplus_basic.hpp>
#include <QtWidgets/qwidget.h>

class FitlineDialog : public QWidget {
    Q_OBJECT

private:
    using _Super=QWidget;
    class _PrivateFitlineDialog;
    _PrivateFitlineDialog *thisp=nullptr;
public:
    explicit FitlineDialog(QWidget * /**/=nullptr);
    virtual ~FitlineDialog();
public:
    Q_SIGNAL void valueChanged(int /*enum: distType */ , double /* param */ , double /* reps */ , double /* aeps */);
    Q_SLOT void emitValueChanged();
    QSize sizeHint() const override;
private:
    FitlineDialog(const FitlineDialog&)=delete;
    FitlineDialog(FitlineDialog&&)=delete;
    FitlineDialog&operator=(const FitlineDialog&)=delete;
    FitlineDialog&operator=(FitlineDialog&&)=delete;
private:
    CPLUSPLUS_OBJECT(FitlineDialog)
};

 #endif /**/

