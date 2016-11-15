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
public:
    ImageChart(QGraphicsItem *parent=nullptr,Qt::WindowFlags wFlags=Qt::WindowFlags());
    ~ImageChart();
public:
    void setImage(const QImage &);
    const QImage &getImage()const;
    const QImage &getAlgorithmImage()const;
     
    const std::shared_ptr<AbstractImageShift>&getAlgorithm()const;
    inline void setAlgorithm(const std::shared_ptr<AbstractImageShift> &arg) {
        _p_set_alg(arg);
    }
    inline void setAlgorithm(std::shared_ptr<AbstractImageShift> &&arg) {
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

#endif // IMAGECHART_HPP




