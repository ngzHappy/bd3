#include <QtNetwork>
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

namespace {

class BaiDuImageState final :
    public baiduimage::DownLoadCallBack,
    public std::enable_shared_from_this<BaiDuImageState> {
    class StaticDataType {
    public:
        QNetworkAccessManager networkAccessManager;
        StaticDataType() {}
    };
    static memory::StaticData<StaticDataType> _p_staticData;
    static StaticDataType * _p_StaticData() {
        static memory::StaticPoionter<StaticDataType> ans{ _p_staticData };
        return ans.pointer();
    }
public:
    BaiDuImageState() {}
    virtual ~BaiDuImageState() {}

    QString keyWord;
    QString errorString;
    QString ansString;
    enum step_index_type :int {
        i_start,
        i_wait,
        i_finished,
        i_error,
    };

    step_index_type current_state=i_error;
    step_index_type next_state=i_error;

    class StateMachine {
        BaiDuImageState * _pm_State;
    public:
        StateMachine(BaiDuImageState * arg,step_index_type argc):
            _pm_State(arg) {
            _pm_State->current_state=argc;
            _pm_State->next_state=i_error;
        }

        void next(step_index_type arg) {
            _pm_State->next_state=arg;
        }

        ~StateMachine() {
            _pm_State->next();
        }

    };

    inline void next();
    inline void downLoad();

    inline void startDownLoad();
    inline void finishedDownLoad();
    inline void errorDownLoad();
private:
    CPLUSPLUS_OBJECT(BaiDuImageState)
};

memory::StaticData<BaiDuImageState::StaticDataType> BaiDuImageState::_p_staticData;

inline void BaiDuImageState::downLoad() {
    if (keyWord.isEmpty()) { return; }
    startDownLoad();
}

inline void BaiDuImageState::startDownLoad() {
    StateMachine s(this,i_start);

}

inline void BaiDuImageState::finishedDownLoad(){
    this->finished(ansString);
}

inline void BaiDuImageState::errorDownLoad() {
    this->finished(errorString);
}

inline void BaiDuImageState::next() {
    switch (next_state) {
        case i_start:return startDownLoad(); 
        case i_wait:return;
        case i_finished:return finishedDownLoad();
        case i_error:return errorDownLoad();
    }
}

}/*namespace*/

void MainWindow::setText(QString arg) {
    _pm_IsDownLoad=false;
    ui->urlView->setPlainText(std::move(arg));
}

void MainWindow::on_doButton_clicked() {

    if (_pm_IsDownLoad) { return; }
    _pm_IsDownLoad=true;

    auto state=
        memory::make_shared<BaiDuImageState>();

    state->keyWord=ui->keyWord->text().trimmed();

    connect(
        state.get(),&BaiDuImageState::finished,
        this,&MainWindow::setText,
        Qt::QueuedConnection);

    state->downLoad();

}



