#ifndef __HPP_APPROXPOLYDPDIALOG0x21003
#define __HPP_APPROXPOLYDPDIALOG0x21003

#include <cplusplus_basic.hpp>
#include <QtWidgets/qwidget.h>
class QVBoxLayout;

class ApproxPolyDPDialog : public QWidget {
    Q_OBJECT

private:
    using _Super=QWidget;
    class _PrivateApproxPolyDPDialog;
    _PrivateApproxPolyDPDialog *thisp=nullptr;
public:
    explicit ApproxPolyDPDialog(QWidget * /**/=nullptr);
    virtual ~ApproxPolyDPDialog();
    QVBoxLayout * getMainLayout() const;
public:
    Q_SIGNAL void valueChanged(double /* epsilon */);
    Q_SLOT void emitValueChanged();
    QSize sizeHint() const override;
private:
    ApproxPolyDPDialog(const ApproxPolyDPDialog&)=delete;
    ApproxPolyDPDialog(ApproxPolyDPDialog&&)=delete;
    ApproxPolyDPDialog&operator=(const ApproxPolyDPDialog&)=delete;
    ApproxPolyDPDialog&operator=(ApproxPolyDPDialog&&)=delete;
private:
    CPLUSPLUS_OBJECT(ApproxPolyDPDialog)
};

 #endif /**/

