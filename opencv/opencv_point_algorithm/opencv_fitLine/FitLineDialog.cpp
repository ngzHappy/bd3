#include "FitLineDialog.hpp"
#include "ui_FitLineDialog.h"

namespace Ui {

class WrapFitLineDialog :public FitLineDialog {
public:
    static constexpr double default_step() { return 0.05; }
    static constexpr double default_param() { return 0.0; }
    static constexpr double default_reps() { return 0.01; }
    static constexpr double default_aeps() { return 0.01; }
    int distType;
    double param=default_param();
    double reps=default_reps();
    double aeps=default_aeps();
    int old_distType;
    double old_param=default_param();
    double old_reps=default_reps();
    double old_aeps=default_aeps();
    double param_step=default_step();
    double reps_step=default_step();
    double aeps_step=default_step();
    WrapFitLineDialog() {}
    void setupUi(QWidget *arg) {
        FitLineDialog::setupUi(arg);
        paramValue->setText(QString::number(default_param()));
        repsValue->setText(QString::number(default_reps()));
        aepsValue->setText(QString::number(default_aeps()));
        paramStep->setText(QString::number(default_step()));
        repsStep->setText(QString::number(default_step()));
        aepsStep->setText(QString::number(default_step()));
    }

    bool isChanged() {
        bool ans=false;
        if (old_distType!=distType) { 
            ans=true;
            old_distType=distType;
        }
    }

private:
    CPLUSPLUS_OBJECT(WrapFitLineDialog)
};

}

FitLineDialog::FitLineDialog(QWidget *parent):
    QWidget(parent),
    ui(new Ui::WrapFitLineDialog) {
    ui->setupUi(this);
}

FitLineDialog::~FitLineDialog() {
    delete ui;
}

QSize FitLineDialog::sizeHint() const {
    return{ 256,128 };
}

void FitLineDialog::on_paramStepAdd_clicked() {
    ui->param_step=ui->paramStep->text().toDouble();
    ui->param=ui->paramValue->text().toDouble();
    ui->param+=ui->param_step;
    ui->paramValue->setText(QString::number(ui->param));
    on_doButton_clicked();
}

void FitLineDialog::on_paramStepSub_clicked() {
    ui->param_step=ui->paramStep->text().toDouble();
    ui->param=ui->paramValue->text().toDouble();
    ui->param-=ui->param_step;
    ui->paramValue->setText(QString::number(ui->param));
    on_doButton_clicked();
}

void FitLineDialog::on_repsStepAdd_clicked() {
   
    on_doButton_clicked();
}

void FitLineDialog::on_repsStepSub_clicked() {
    on_doButton_clicked();
}

void FitLineDialog::on_aepsStepAdd_clicked() {
    on_doButton_clicked();
}

void FitLineDialog::on_aepsStepSub_clicked() {
    on_doButton_clicked();
}

void FitLineDialog::on_doButton_clicked() {

}
