#ifndef ONEDEEPTREEDELEGATE_HPP
#define ONEDEEPTREEDELEGATE_HPP

#include <cplusplus_basic.hpp>
#include <QtWidgets/qstyleditemdelegate.h>

#ifndef $m$ONEDEEPTREEDELEGATE_PROTECTED /*模拟java包组织权限*/
#define $m$ONEDEEPTREEDELEGATE_PROTECTED protected
#endif

class OneDeepTreeView;
class _PrivateOneDeepTreeDelegate;
class OneDeepTreeDelegate : public QStyledItemDelegate {
    Q_OBJECT
private:
    using Super=QStyledItemDelegate;
    friend class _PrivateOneDeepTreeDelegate;
public:
    OneDeepTreeDelegate(OneDeepTreeView *);
    ~OneDeepTreeDelegate();
$m$ONEDEEPTREEDELEGATE_PROTECTED:
    _PrivateOneDeepTreeDelegate *$m$thisp=nullptr;
private:
    CPLUSPLUS_OBJECT(OneDeepTreeDelegate)
};

#endif // ONEDEEPTREEDELEGATE_HPP
