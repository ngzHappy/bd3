#ifndef IMAGESHOWWIDGET_HPP
#define IMAGESHOWWIDGET_HPP

#include "OpenCVBasic.hpp"
#include <Qtwidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include "AbstractImageShift.hpp"

class QImage;
class ImageChart;
class PlainImageView;
class ImageChartView;

class OPENCV3_BASICHARED_EXPORT ImageShowWidget : public QMainWindow {
    Q_OBJECT

private:
    using Super=QMainWindow;
    class _PrivateImageShowWidget;
    _PrivateImageShowWidget * _pm_this_data;
    template<typename ...>using _void_t=void;
public:
    ImageShowWidget(QWidget * /*parent*/=nullptr,Qt::WindowFlags /*flags*/=Qt::WindowFlags());
    virtual ~ImageShowWidget();
public:
    PlainImageView * setImage(const QImage &,bool is_copy_=true);
    ImageChart * setChartImage(const QImage &,bool is_copy_=true);
    const QImage &getImage() const;
    QDockWidget* addImageWidget(QWidget*,const QString&/*title*/=QString{});
    const std::shared_ptr<AbstractImageShift>&getAlgorithm()const;
    template<typename _A_,typename=_void_t<
        decltype(std::declval<_A_&&>()(std::declval<const QImage&>()))>/**/>
        inline void setAlgorithm(_A_&&);

    template<typename _A_,typename=_void_t<
        decltype(std::declval<_A_&&>()->run(std::declval<const QImage&>()))>,
        typename=double*>
        inline void setAlgorithm(_A_&&arg) {
        _p_setAlgorithm(std::forward<_A_>(arg));
    }
public:
    ImageShowWidget(const ImageShowWidget &)=delete;
    ImageShowWidget(ImageShowWidget&&)=delete;
    ImageShowWidget&operator=(const ImageShowWidget &)=delete;
    ImageShowWidget&operator=(ImageShowWidget&&)=delete;
private:
    void _p_setAlgorithm(const std::shared_ptr<AbstractImageShift>&);
    void _p_setAlgorithm(std::shared_ptr<AbstractImageShift>&&);
private:
    CPLUSPLUS_OBJECT(ImageShowWidget)
};

template<typename _A_,typename>
inline void ImageShowWidget::setAlgorithm(_A_&&arg) {
    using _A0_=std::remove_reference_t<_A_>;
    class _Alg_A0_ :public AbstractImageShift {
        _A0_ _pm;
    public:
        QImage run(const QImage& arg) const override {
            return _pm(arg);
        }
        _Alg_A0_(_A_&&_arg):_pm(std::forward<_A_>(_arg)) {}
    };
    this->_p_setAlgorithm(
        memory::make_shared<_Alg_A0_>(std::forward<_A_>(arg)));
}

#endif // IMAGESHOWWIDGET_HPP
