#ifndef IMAGECHART_HPP
#define IMAGECHART_HPP

#include "ChartBasic.hpp"
#include "AbstractImageShift.hpp"

class OPENCV3_BASICHARED_EXPORT ImageChart : public ChartBasic {
    Q_OBJECT

private:
    using _Super=ChartBasic;
    class _PrivateImageChart;
    _PrivateImageChart *_mp;
    template<typename ...>using _void_t=void;
public:
    ImageChart(QGraphicsItem *parent=nullptr,Qt::WindowFlags wFlags=Qt::WindowFlags());
    ~ImageChart();
public:
    void setImage(const QImage &,bool _copy=true);
    const QImage &getImage()const;
    const QImage &getAlgorithmImage()const;
     
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
private:
    inline void _p_setAlgorithm(const std::shared_ptr<AbstractImageShift> &arg) {
        _p_set_alg(arg);
    }
    inline void _p_setAlgorithm(std::shared_ptr<AbstractImageShift> &&arg) {
        _p_set_alg(std::move(arg));
    }
public:
    Q_SIGNAL void imageChanged();
    Q_SIGNAL void algorithmChanged();
protected:
    virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *,QWidget *)override;
private:
    bool _p_update_axis();
    void _p_set_alg(std::shared_ptr<AbstractImageShift>);
    void _p_alg_or_img_changed();
public:
    ImageChart(ImageChart&&);
    ImageChart(const ImageChart&);
    ImageChart&operator=(ImageChart&&)=delete;
    ImageChart&operator=(const ImageChart&)=delete;
private:
    CPLUSPLUS_OBJECT(ImageChart)
};

template<typename _A_,typename>
inline void ImageChart::setAlgorithm(_A_&&arg) {
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

#endif // IMAGECHART_HPP




