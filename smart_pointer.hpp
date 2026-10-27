#pragma once
#include <algorithm>
//Очень часто класс реализуется в отдельном файле и включается проект с помощью #include
//При этом объявление класса и реализация тоже разносятся по разным файлом
//Файлы .hpp служат для объявления класса (заголовочные файлы в c++ -- аналог .h из с)

//Дальше идет реализация нашего класса (умного указателя на int)
class sp_int
{
    private:
    int* pointer_;
    //Второй способ удалить метод:
    sp_int& operator=(sp_int const& to_copy)=default;
    //sp_int x = y;// y <-- sp_in 

    public:
    sp_int(int* pointer);
    sp_int(sp_int&& to_move);
    ~sp_int();

    //Есть два способа удалить метод
    //Первый способ:
    sp_int(sp_int& other) = delete;
    sp_int& operator=(sp_int&& to_move);
    int& operator*() const;
    int* get() const; 
    

};

bool operator==(sp_int const& la, sp_int const& ra);