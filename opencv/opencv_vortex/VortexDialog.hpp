#ifndef __HPP_VORTEXDIALOG0x21003
#define __HPP_VORTEXDIALOG0x21003

#include <cplusplus_basic.hpp>
#include <QtWidgets/qwidget.h>
class QVBoxLayout;

class VortexDialog : public QWidget {
    Q_OBJECT

private:
    using _Super=QWidget;
    class _PrivateVortexDialog;
    _PrivateVortexDialog *thisp=nullptr;
public:
    explicit VortexDialog(QWidget * /**/=nullptr);
    virtual ~VortexDialog();
    QVBoxLayout * getMainLayout() const;
public:
    Q_SIGNAL void valueChanged(int /* changeCount */);
    Q_SLOT void emitValueChanged();
    QSize sizeHint() const override;
private:
    VortexDialog(const VortexDialog&)=delete;
    VortexDialog(VortexDialog&&)=delete;
    VortexDialog&operator=(const VortexDialog&)=delete;
    VortexDialog&operator=(VortexDialog&&)=delete;
private:
    CPLUSPLUS_OBJECT(VortexDialog)
};

 #endif /**/

