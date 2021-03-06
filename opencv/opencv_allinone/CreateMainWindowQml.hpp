﻿#ifndef CREATEMAINWINDOWQML_HPP
#define CREATEMAINWINDOWQML_HPP

#include <map>
#include <QString>
#include <memory>
#include <cplusplus_basic.hpp>


class CreateMainWindowQml
{
    std::map<QString,QString>data_;
public:
    CreateMainWindowQml();
    static std::shared_ptr<CreateMainWindowQml> instance();
    void createAllInOneItemQml();
    void createAllInOneMainWindowQml();
protected:
    virtual ~CreateMainWindowQml();
private:
    CPLUSPLUS_OBJECT(CreateMainWindowQml)
};

#endif // CREATEMAINWINDOWQML_HPP
