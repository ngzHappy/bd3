#ifndef PLAINIMAGEVIEW_HPP
#define PLAINIMAGEVIEW_HPP

#include "OpenCVBasic.hpp"
#include "AbstractImageShift.hpp"
#include <QtWidgets/qwidget.h>
class QImage;

class OPENCV3_BASICHARED_EXPORT PlainImageView : public QWidget {
    Q_OBJECT

private:
    class _PrivatePlainImageView;
    _PrivatePlainImageView * _pm;
    template<typename ...>using _void_t=void;
public:
    PlainImageView();
    virtual ~PlainImageView();

    void setImage(const QImage &,bool/*copy*/=true);
    const QImage & getImage()const;
    const QImage & getAlgorithmImage()const;
    QImage getPaintedAlgorithmImage()const;

    const std::shared_ptr<AbstractImageShift> & getAlgorithm()const;

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
    Q_SIGNAL void imageChanged();
    Q_SIGNAL void algorithmChanged();
protected:
    void paintEvent(QPaintEvent *event)override;
public:
    PlainImageView(PlainImageView &&)=delete;
    PlainImageView&operator=(PlainImageView &&)=delete;
    PlainImageView(const PlainImageView &)=delete;
    PlainImageView&operator=(const PlainImageView &)=delete;
    QSize sizeHint() const override;
private:
    void _alg_or_img_change();
    void _p_setAlgorithm(std::shared_ptr<AbstractImageShift>);
private:
    CPLUSPLUS_OBJECT(PlainImageView)
};

template<typename _A_,typename>
inline void PlainImageView::setAlgorithm(_A_&&arg) {
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

#endif // PLAINIMAGEVIEW_HPP
