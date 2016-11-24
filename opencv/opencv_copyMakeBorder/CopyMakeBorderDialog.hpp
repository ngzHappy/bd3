#ifndef __HPP_COPYMAKEBORDERDIALOG0x21003
#define __HPP_COPYMAKEBORDERDIALOG0x21003

#include <cplusplus_basic.hpp>
#include <QtWidgets/qwidget.h>

class CopyMakeBorderDialog : public QWidget {
    Q_OBJECT

private:
    using _Super=QWidget;
    class _PrivateCopyMakeBorderDialog;
    _PrivateCopyMakeBorderDialog *thisp=nullptr;
public:
    explicit CopyMakeBorderDialog(QWidget * /**/=nullptr);
    virtual ~CopyMakeBorderDialog();
public:
    Q_SIGNAL void valueChanged(int /* top */ , int /* bottom */ , int /* left */ , int /* right */ , int /*enum: borderType */);
    Q_SLOT void emitValueChanged();
    QSize sizeHint() const override;
private:
    CopyMakeBorderDialog(const CopyMakeBorderDialog&)=delete;
    CopyMakeBorderDialog(CopyMakeBorderDialog&&)=delete;
    CopyMakeBorderDialog&operator=(const CopyMakeBorderDialog&)=delete;
    CopyMakeBorderDialog&operator=(CopyMakeBorderDialog&&)=delete;
private:
    CPLUSPLUS_OBJECT(CopyMakeBorderDialog)
};

 #endif /**/

