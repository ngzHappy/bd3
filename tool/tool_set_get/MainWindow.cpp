/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->resize(1024,768);
}

MainWindow::~MainWindow() {
    delete ui;
}



void MainWindow::on_doButton_clicked() {

    auto & varViewWidget=ui->view;
    auto & varNameSpaceWidget=ui->nameSpace;
    auto & varTypeWidget=ui->type;
    auto & varNameWidget=ui->name;

    auto varName=varNameWidget->text().trimmed();
    auto varType=varTypeWidget->text().trimmed();
    auto varNameSpace=varNameSpaceWidget->text().trimmed();

    auto varFirstUpperName=varName;
    {
        auto varFistChar=varFirstUpperName.begin() ;
        *varFistChar=varFistChar->toUpper();
    }
    auto varElementName=u8R"(/*⒨*/\u24A8)"+varFirstUpperName;

    QString varAns;

    varAns+=varType+" "+varElementName+";\n";

    /*********************************************************/
    varAns+="/*********************************************************/\n";
    /*********************************************************/
    varAns+="inline auto & get"+varFirstUpperName+
        "(){return "+varNameSpace+varElementName+";}\n";
    varAns+="inline void set"+varFirstUpperName+"(const "
        +varType +"& arg) { "
        +varNameSpace+varElementName+"=arg;}\n";
    varAns+="inline void set"+varFirstUpperName+"("
        +varType +"&& arg) { "
        +varNameSpace+varElementName+"=std::move(arg);}\n";
    varAns+="inline void set"+varFirstUpperName+"(const "
        +varType +"&& arg) { set"
        +varFirstUpperName+"( static_cast<const "+varType+"&>(arg));}\n";
    varAns+="inline void set"+varFirstUpperName+"("
        +varType +"& arg) { set"
        +varFirstUpperName+"( static_cast<const "+varType+"&>(arg));}\n";
    varAns+="inline const auto & get"+varFirstUpperName+
        "() const {return "+varNameSpace+varElementName+";}\n";
    /*********************************************************/
    varAns+="/*********************************************************/\n";
    /*********************************************************/
    varAns+="inline auto get"+varFirstUpperName+
        "()->"+varType+"&;\n";
    varAns+="inline auto set"+varFirstUpperName+"(const "
        +varType+"& arg)->void;\n";
    varAns+="inline auto set"+varFirstUpperName+"("
        +varType+"&& arg)->void;\n";
    varAns+="inline auto set"+varFirstUpperName+"(const "
        +varType +"&& arg)->void { set"
        +varFirstUpperName+"( static_cast<const "+varType+"&>(arg));}\n";
    varAns+="inline auto set"+varFirstUpperName+"("
        +varType +"& arg)->void { set"
        +varFirstUpperName+"( static_cast<const "+varType+"&>(arg));}\n";
    varAns+="inline auto get"+varFirstUpperName+
        "() const -> const "+varType+"&;\n";
    /*********************************************************/
    varAns+="/*********************************************************/\n";
    /*********************************************************/
    varAns+="inline auto /*????*/get"+varFirstUpperName+
        "()->"+varType+"&{return /*!!!!*/get"+varFirstUpperName+"();}\n";
    varAns+="inline auto /*????*/set"+varFirstUpperName+"(const "
        +varType+"& arg)->void{/*!!!!*/set"+varFirstUpperName+"(arg);}\n";
    varAns+="inline auto /*????*/set"+varFirstUpperName+"("
        +varType+"&& arg)->void{/*!!!!*/set"+varFirstUpperName+"(std::move(arg));}\n";
    varAns+="inline auto /*????*/get"+varFirstUpperName+
        "() const -> const "+varType+"&{return /*!!!!*/get"+varFirstUpperName+"();}\n";
    varViewWidget->setText(varAns);

}


