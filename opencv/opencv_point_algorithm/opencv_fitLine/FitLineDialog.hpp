#ifndef FITLINEDIALOG_HPP
#define FITLINEDIALOG_HPP

#include <cplusplus_basic.hpp>
#include <QtWidgets/QWidget>

namespace Ui {
class FitLineDialog;
class WrapFitLineDialog;
}

class FitLineDialog : public QWidget
{
    Q_OBJECT

public:
    explicit FitLineDialog(QWidget *parent = 0);
    ~FitLineDialog();

    QSize sizeHint() const override;
private:
    Q_SLOT void on_paramStepAdd_clicked();
    Q_SLOT void on_repsStepAdd_clicked();
    Q_SLOT void on_aepsStepAdd_clicked();
    Q_SLOT void on_paramStepSub_clicked();
    Q_SLOT void on_repsStepSub_clicked();
    Q_SLOT void on_aepsStepSub_clicked();
    Q_SLOT void on_doButton_clicked();

private:
    Ui::WrapFitLineDialog *ui;
private:
    CPLUSPLUS_OBJECT(FitLineDialog)
};

#endif // FITLINEDIALOG_HPP
