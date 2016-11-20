#ifndef MAINWINDOW_HPP_0x12778
#define MAINWINDOW_HPP_0x12778

#include <cplusplus_basic.hpp>
#include <ImageShowUtility.hpp>

class MainWindow final : public OpencvMainWindow {
    Q_OBJECT

private:
    using _Super=OpencvMainWindow;
    class _PrivateMainWindow;
    _PrivateMainWindow * _thisp=nullptr;
public:
    explicit MainWindow(QWidget *parent=nullptr);
    ~MainWindow();

    using _Super::addImage;
    QWidget* addImage(const QImage &) override;
    void openLua() override;
    
public:
    MainWindow(const MainWindow&)=delete;
    MainWindow(MainWindow&&)=delete;
    MainWindow&operator=(const MainWindow&)=delete;
    MainWindow&operator=(MainWindow&&)=delete;
private:
    CPLUSPLUS_OBJECT(MainWindow)
};

#endif // MAINWINDOW_HPP

/*End of the file.*/

