#ifndef LINESITERATOR_HPP_0x000001
#define LINESITERATOR_HPP_0x000001

#include <cplusplus_basic.hpp>

namespace _pns_private {
namespace _pns_opencv_utility {

template<bool> class BasicLinesIterator;

template<>
class BasicLinesIterator<false> {
protected:
    typedef unsigned char *_p_data_t;
    typedef const unsigned char *_p_cdata_t;
    typedef int _p_int_t;
    _p_data_t _mp_begin_pointer;
    _p_data_t _mp_current_pointer;
    _p_data_t _mp_end_pointer;
    _p_int_t _mp_step;
public:
    typedef float float32_type;
    typedef double float64_type;
    static_assert(sizeof(float64_type)==8,"");
    static_assert(sizeof(float32_type)==4,"");

    BasicLinesIterator():
        _mp_begin_pointer(nullptr),
        _mp_current_pointer(nullptr),
        _mp_end_pointer(nullptr),
        _mp_step(0) {
    }

    BasicLinesIterator(_p_cdata_t begin_arg,
            _p_int_t line_size_arg,
            _p_int_t step_arg):
        _mp_begin_pointer(const_cast<_p_data_t>(begin_arg)),
        _mp_current_pointer(const_cast<_p_data_t>(begin_arg)),
        _mp_end_pointer(const_cast<_p_data_t>(begin_arg)
                        +(line_size_arg*step_arg)),
        _mp_step(step_arg) {
    }


    BasicLinesIterator(_p_data_t begin_arg,
        _p_int_t line_size_arg,
        _p_int_t step_arg):
        _mp_begin_pointer(begin_arg),
        _mp_current_pointer(begin_arg),
        _mp_end_pointer(begin_arg+(line_size_arg*step_arg)),
        _mp_step(step_arg) {
    }

    void goNext() {
        _mp_current_pointer+=_mp_step;
    }

    void goPrevious() {
        _mp_current_pointer-=_mp_step;
    }

    void goNext(_p_int_t arg) {
        _mp_current_pointer+=_mp_step*arg;
    }

    void goPrevious(_p_int_t arg) {
        _mp_current_pointer-=_mp_step*arg;
    }

    void goFirst() {
        _mp_current_pointer=_mp_begin_pointer;
    }

    void goLast() {
        _mp_current_pointer=_mp_end_pointer;
    }

};

template<>
class BasicLinesIterator<true> :public BasicLinesIterator<false> {
    using _Super=BasicLinesIterator<false>;
protected:
    _p_int_t _mp_current_line;
    _p_int_t _mp_lines_count;
public:

    BasicLinesIterator():
        _mp_current_line(0),
        _mp_lines_count(0) {
    }

    BasicLinesIterator(_p_cdata_t begin_arg,
                       _p_int_t line_size_arg,
                       _p_int_t step_arg):
        _Super(begin_arg,line_size_arg,step_arg),
        _mp_current_line(0),
        _mp_lines_count(line_size_arg) {
    }

    BasicLinesIterator(_p_data_t begin_arg,
        _p_int_t line_size_arg,
        _p_int_t step_arg):
        _Super(begin_arg,line_size_arg,step_arg),
        _mp_current_line(0),
        _mp_lines_count(line_size_arg) {
    }

    _p_int_t lineCount() const { return this->_mp_lines_count; }
    _p_int_t currentLineNumber() const { return this->_mp_current_line; }

    void goNext() {
        _mp_current_pointer+=_mp_step;
        ++_mp_current_line;
    }

    void goPrevious() {
        _mp_current_pointer-=_mp_step;
        --_mp_current_line;
    }

    void goNext(_p_int_t arg) {
        _mp_current_pointer+=_mp_step*arg;
        _mp_current_line+=arg;
    }

    void goPrevious(_p_int_t arg) {
        _mp_current_pointer-=_mp_step*arg;
        _mp_current_line-=arg;
    }

    void goFirst() {
        _mp_current_pointer=_mp_begin_pointer;
        _mp_current_line=0;
    }

    void goLast() {
        _mp_current_pointer=_mp_end_pointer;
        _mp_current_line=_mp_lines_count;
    }

};

template<bool _HasLineNumber_=false>
class LinesIterator : public BasicLinesIterator<_HasLineNumber_> {
    using _Super=BasicLinesIterator<_HasLineNumber_>;
    using typename _Super::_p_data_t;
    using typename _Super::_p_int_t;
    using typename _Super::_p_cdata_t;
public:

    LinesIterator()=default;
    LinesIterator(const void * begin_arg,
                  _p_int_t line_size_arg,
                  _p_int_t step_arg)
        :_Super(reinterpret_cast<_p_cdata_t>(begin_arg),
            line_size_arg,step_arg) {
    }

    LinesIterator(void * begin_arg,
        _p_int_t line_size_arg,
        _p_int_t step_arg)
        :_Super(reinterpret_cast<_p_data_t>(begin_arg),
            line_size_arg,step_arg) {
    }

    _p_int_t step()const { return this->_mp_step; }

    template<typename _T_>
    _T_ * firstLine() {
        return reinterpret_cast<_T_ *>(this->_mp_begin_pointer);
    }

    template<typename _T_>
    const _T_ * firstLine()const {
        return reinterpret_cast<const _T_ *>(this->_mp_begin_pointer);
    }

    template<typename _T_>
    _T_ * lastLine() {
        return reinterpret_cast<_T_ *>(this->_mp_end_pointer);
    }

    template<typename _T_>
    const _T_ * lastLine()const {
        return reinterpret_cast<const _T_ *>(this->_mp_end_pointer);
    }

    template<typename _T_>
    _T_* currentLine() {
        return reinterpret_cast<_T_*>(this->_mp_current_pointer);
    }

    template<typename _T_>
    const _T_* currentLine() const {
        return reinterpret_cast<const _T_*>(this->_mp_current_pointer);
    }

    template<typename _T_>
    _T_* nextLine() {
        return reinterpret_cast<_T_*>(this->_mp_current_pointer+this->_mp_step);
    }

    template<typename _T_>
    const _T_* nextLine()const {
        return reinterpret_cast<const _T_*>(this->_mp_current_pointer+this->_mp_step);
    }

    template<typename _T_>
    _T_* previousLine() {
        return reinterpret_cast<_T_*>(this->_mp_current_pointer-this->_mp_step);
    }

    template<typename _T_>
    const _T_* previousLine()const {
        return reinterpret_cast<const _T_*>(this->_mp_current_pointer-this->_mp_step);
    }

    template<typename _T_>
    _T_* nextLine(_p_int_t arg) {
        return reinterpret_cast<_T_*>(this->_mp_current_pointer+arg*this->_mp_step);
    }

    template<typename _T_>
    const _T_* nextLine(_p_int_t arg)const {
        return reinterpret_cast<const _T_*>(this->_mp_current_pointer+arg*this->_mp_step);
    }

    template<typename _T_>
    _T_* previousLine(_p_int_t arg) {
        return reinterpret_cast<_T_*>(this->_mp_current_pointer-arg*this->_mp_step);
    }

    template<typename _T_>
    const _T_* previousLine(int arg)const {
        return reinterpret_cast<const _T_*>(this->_mp_current_pointer-arg*this->_mp_step);
    }

    bool isFinePointer(const void *arg) const {
        return (arg<static_cast<const void *>(this->_mp_end_pointer))&&
            (static_cast<const void*>(this->_mp_begin_pointer)<=arg);
    }

    operator bool() const {
        return this->_mp_current_pointer<this->_mp_end_pointer;
    }

    bool isFinePointer() const {
        return (this->_mp_current_pointer<this->_mp_end_pointer)&&
            (this->_mp_begin_pointer<=this->_mp_current_pointer);
    }

private:
    CPLUSPLUS_OBJECT(LinesIterator)
};

extern template class LinesIterator<true>;
extern template class LinesIterator<false>;

}/*_pns_opencv_utility*/
}/*_pns_private*/

using _pns_private::_pns_opencv_utility::LinesIterator;

#endif // LINESITERATOR_HPP
