﻿#ifndef IMAGESHOWWIDGET_HPP
#define IMAGESHOWWIDGET_HPP

#include <Qtwidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include "OpenCVBasic.hpp"
class QImage;

class OPENCV3_BASICHARED_EXPORT ImageShowWidget : public QMainWindow
{
    Q_OBJECT

private:
    using Super=QMainWindow;
    class _PrivateImageShowWidget;
    _PrivateImageShowWidget * _pm_this_data;
public:
    ImageShowWidget(QWidget * /*parent*/=nullptr, Qt::WindowFlags /*flags*/=Qt::WindowFlags());
    virtual ~ImageShowWidget();
public:
    void setImage(const QImage &);
    const QImage &getImage();
public:
    ImageShowWidget(const ImageShowWidget &)=delete;
    ImageShowWidget(ImageShowWidget&&)=delete;
    ImageShowWidget&operator=(const ImageShowWidget &)=delete;
    ImageShowWidget&operator=(ImageShowWidget&&)=delete;
private:
    CPLUSPLUS_OBJECT(ImageShowWidget)
};

#endif // IMAGESHOWWIDGET_HPP
