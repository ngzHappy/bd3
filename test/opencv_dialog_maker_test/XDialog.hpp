#ifndef __HPP_XDIALOG0x21003
#define __HPP_XDIALOG0x21003


#include <cplusplus_basic.hpp>
#include <QtWidgets/qwidget.h>

class XDialog : public QWidget {
    Q_OBJECT

private:
    using _Super=QWidget;
    class _PrivateXDialog;
    _PrivateXDialog *thisp=nullptr;
public:
    explicit XDialog(QWidget * /**/=nullptr);
    virtual ~XDialog();
public:
    Q_SIGNAL void valueChanged(int /* XDialogtest0 */,double /* XDialogtest1 */,int /*enum: XDialogtest2 */);
    Q_SLOT void emitValueChanged();
private:
    XDialog(const XDialog&)=delete;
    XDialog(XDialog&&)=delete;
    XDialog&operator=(const XDialog&)=delete;
    XDialog&operator=(XDialog&&)=delete;
private:
    CPLUSPLUS_OBJECT(XDialog)
};

#endif /**/
