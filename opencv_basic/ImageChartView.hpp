﻿#ifndef IMAGECHARTVIEW_HPP
#define IMAGECHARTVIEW_HPP

#include "ChartView.hpp"
#include "AbstractImageShift.hpp"
class ImageChart;

class OPENCV3_BASICHARED_EXPORT ImageChartView :
    public ChartView,
    public AbstractGetImage {
    Q_OBJECT

private:
    using _Super=ChartView;
    ImageChart * _mp_image_chart;
    template<typename ...>using _void_t=void;
public:
    Q_SIGNAL void imageChanged();
    Q_SIGNAL void algorithmChanged();
protected:
    ImageChartView(QtCharts::QChart *chart,QWidget *parent=nullptr);
public:
    ImageChartView(QWidget *parent=nullptr);
    ~ImageChartView();
    ImageChart * imageChart()const { return _mp_image_chart; }

    ImageChart * setImage(const QImage &,bool _copy=true);
    const QImage &getImage()const;
    const QImage &getAlgorithmImage()const;
    QImage getPaintedAlgorithmImage()const;
    const std::shared_ptr<AbstractImageShift>&getAlgorithm()const;

    template<typename _A_,typename=_void_t<
        decltype(std::declval<_A_&&>()(std::declval<const QImage&>()))>/**/>
        inline void setAlgorithm(_A_&&);

    template<typename _A_,typename=_void_t<
        decltype((std::declval<_A_&&>())->run(std::declval<const QImage&>()))>,
        typename=double*>
        inline void setAlgorithm(_A_&&arg) {
        _p_setAlgorithm(std::forward<_A_>(arg));
    }
    QSize sizeHint() const override;
protected:
    void _p_setAlgorithm(const std::shared_ptr<AbstractImageShift>&);
    void _p_setAlgorithm(std::shared_ptr<AbstractImageShift>&&);
private:
    CPLUSPLUS_OBJECT(ImageChartView)
};

template<typename _A_,typename>
inline void ImageChartView::setAlgorithm(_A_&&arg) {
    using _A0_=std::remove_cv_t<std::remove_reference_t<_A_>>;
    class _Alg_A0_ :public AbstractImageShift {
        _A0_ _pm;
    public:
        QImage run(const QImage& arg) override {
            return _pm(arg);
        }
        _Alg_A0_(_A_&&_arg):_pm(std::forward<_A_>(_arg)) {}
    };
    this->_p_setAlgorithm(
        memory::make_shared<_Alg_A0_>(std::forward<_A_>(arg)));
}

#endif // IMAGECHARTVIEW_HPP
