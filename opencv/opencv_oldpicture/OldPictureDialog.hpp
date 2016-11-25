#ifndef __HPP_OLDPICTUREDIALOG0x21003
#define __HPP_OLDPICTUREDIALOG0x21003

#include <cplusplus_basic.hpp>
#include <QtWidgets/qwidget.h>
class QVBoxLayout;

class OldPictureDialog : public QWidget {
    Q_OBJECT

private:
    using _Super=QWidget;
    class _PrivateOldPictureDialog;
    _PrivateOldPictureDialog *thisp=nullptr;
public:
    explicit OldPictureDialog(QWidget * /**/=nullptr);
    virtual ~OldPictureDialog();
    QVBoxLayout * getMainLayout() const;
public:
    Q_SIGNAL void valueChanged(double /* blendValue */);
    Q_SLOT void emitValueChanged();
    QSize sizeHint() const override;
private:
    OldPictureDialog(const OldPictureDialog&)=delete;
    OldPictureDialog(OldPictureDialog&&)=delete;
    OldPictureDialog&operator=(const OldPictureDialog&)=delete;
    OldPictureDialog&operator=(OldPictureDialog&&)=delete;
private:
    CPLUSPLUS_OBJECT(OldPictureDialog)
};

 #endif /**/

