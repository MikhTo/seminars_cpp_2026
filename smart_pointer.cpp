#include "smart_pointer.hpp"

//В этом файле происходит реализация всех методов класса и функций, объявленных в .hpp

sp_int::sp_int(int* pointer)
{
    pointer_ = pointer;
}

sp_int::sp_int(sp_int&& to_move)
{
    pointer_ = to_move.pointer_;
    to_move.pointer_ = nullptr;
}
sp_int::~sp_int()
{
    //Деструктор отвечает за удаление объекта
    //он должен освободить выделенную память
    delete pointer_;
    pointer_ = nullptr; 
}

sp_int& sp_int::operator=(sp_int&& to_move)
{
    std::swap(pointer_, to_move.pointer_);
    return *this;
}

int& sp_int::operator*() const
{
    return *pointer_;
}
int* sp_int::get() const
{
    return pointer_;
}

bool operator==(sp_int const& la, sp_int const& ra)
{
    return la.get() == ra.get();
}