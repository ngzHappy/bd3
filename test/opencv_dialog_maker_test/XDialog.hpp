#ifndef __HPP_XDIALOG0x21003
#define __HPP_XDIALOG0x21003

#include <cplusplus_basic.hpp>
#include <QtWidgets/qwidget.h>

class XDialog : public QWidget
{
    Q_OBJECT

private:
    using _Super=QWidget;
    class _PrivateXDialog;
    _PrivateXDialog *thisp=nullptr;
public:
    explicit XDialog(QWidget * /**/=nullptr);
    virtual ~XDialog();
public:
    Q_SIGNAL valueChanged(int /* _x_Dialogtest0 */ , double /* _x_Dialogtest1 */);
private:
    XDialog(const XDialog&)=delete;
    XDialog(XDialog&&)=delete;
    XDialog&operator=(const XDialog&)=delete;
    XDialog&operator=(XDialog&&)=delete;
private:
    CPLUSPLUS_OBJECT(XDialog)
};

 #endif /**/

