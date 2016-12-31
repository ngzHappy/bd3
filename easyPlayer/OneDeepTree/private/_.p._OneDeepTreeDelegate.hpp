#ifndef _Private_ONEDEEPTREEDELEGATE_HPP
#define _Private_ONEDEEPTREEDELEGATE_HPP

#include "../OneDeepTreeView.hpp"
#include "../OneDeepTreeDelegate.hpp"
#include "../OneDeepTreeItemWidget.hpp"

class _PrivateOneDeepTreeDelegate {
public:
    virtual ~_PrivateOneDeepTreeDelegate();
     OneDeepTreeView *$m$view=nullptr;
private:
    CPLUSPLUS_OBJECT(_PrivateOneDeepTreeDelegate)
};

#endif // ONEDEEPTREEDELEGATE_HPP
