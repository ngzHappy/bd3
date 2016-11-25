#ifndef __HPP_JPEGNDIALOG0x21003
#define __HPP_JPEGNDIALOG0x21003

#include <cplusplus_basic.hpp>
#include <QtWidgets/qwidget.h>
class QVBoxLayout;

class JpegNDialog : public QWidget {
    Q_OBJECT

private:
    using _Super=QWidget;
    class _PrivateJpegNDialog;
    _PrivateJpegNDialog *thisp=nullptr;
public:
    explicit JpegNDialog(QWidget * /**/=nullptr);
    virtual ~JpegNDialog();
    QVBoxLayout * getMainLayout() const;
public:
    Q_SIGNAL void valueChanged(int /* changeCount */);
    Q_SLOT void emitValueChanged();
    QSize sizeHint() const override;
private:
    JpegNDialog(const JpegNDialog&)=delete;
    JpegNDialog(JpegNDialog&&)=delete;
    JpegNDialog&operator=(const JpegNDialog&)=delete;
    JpegNDialog&operator=(JpegNDialog&&)=delete;
private:
    CPLUSPLUS_OBJECT(JpegNDialog)
};

 #endif /**/

