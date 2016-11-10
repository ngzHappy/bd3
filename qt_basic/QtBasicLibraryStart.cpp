/*this function will run on app start up*/
#include <ctime>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <QtGui/qimage.h>
#include <cplusplus_basic.hpp>
#include <QtCore/qcoreapplication.h>

using namespace std::chrono_literals;

namespace {
static void _var() {

    /*init memory*/
    for (int i=0; i<(6*1024); ++i) {
        memory::free(memory::malloc(i));
    }

    std::this_thread::sleep_for(8ms);
    {/*load image plugin*/
        QImage _image_{ "__________qt__.png" };
    }

};
}

static void _on_qt_start_up_0x99812() {

    std::srand(static_cast<int>(std::time(nullptr)));
    std::thread(&_var).detach();

}

Q_COREAPP_STARTUP_FUNCTION(_on_qt_start_up_0x99812)
