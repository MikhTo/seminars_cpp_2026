#include <iostream>
#include <numbers>
#include <string>
#include <cmath>
#include <fstream>
#include <cstdlib>

#include <memory>

#include "smart_pointer.hpp"


void sp_present_func()
{
    int* p = new int;
    *p = 10;
    sp_int pointer(p); 
    std::cout << "Значение нашего указателя: " << *(pointer) << std::endl; 
}

sp_int pow(sp_int base, sp_int exponent)
{
    return sp_int(new int(pow(*base, *exponent)));
}




class Oscilloscope
{
    private:
    double* trace_;    // буфер под отсчёты сигнала. Будем хранить в обычном дин. массиве
    size_t capacity_;  // размер буфера
    size_t recorded_;  // сколько уже записали
    std::string name_; // имя прибора

    public:

    // Конструктор
    Oscilloscope(std::string name, size_t buf_size = 1024)
    {
        name_ = name;
        capacity_ = buf_size;
        recorded_ = 0;

        trace_ = new double[capacity_];

        std::cout << "Осциллограф \"" << name_ << "\" включён, память на "
                  << capacity_ << " отсчётов выделена\n";
    }

    // Раскомментируй код ниже, чтобы все починить
    Oscilloscope(const Oscilloscope& to_copy)
    {   
        capacity_ = to_copy.capacity_;  
        recorded_ = to_copy.recorded_;  
        name_ = to_copy.name_; 
        // Ниже начинаются отличие от того,
        // что делал бы конструктор копирования по умолчанию
        // надо не просто скопировать адреса, а выделить новую память и перенести значения

        trace_ = new double [capacity_]; 
        for(int i = 0; i < capacity_; i++)
            trace_[i] = to_copy.trace_[i];
    }

    // Деструктор -- метод, который вызывается для "уничтожения" объекта
    // В него надо прописать, что делать, чтобы корректно отправить объект в мир иной

    // В нашем случае нужно освободить память, которую выделили в конструкторе
    // Вызывается САМ, когда объект умирает (конец области видимости и т.п.)
    ~Oscilloscope()
    {
        delete[] trace_; // <- по большей части, все ради этой строки

        std::cout << "Осциллограф \"" << name_ << "\" выключен, память освобождена\n";
    }

    // Записать сигнал: синус частотой freq Гц, амплитудой ampl В + шум
    void record(double freq, double ampl, double noise = 0.0)
    {
        double dt = 1e-4; // шаг дискретизации: 0.1 мс (частота дискретизации 10 кГц)

        recorded_ = 0;
        for (size_t i = 0; i < capacity_; ++i)
        {
            double t = i * dt;
            double signal = ampl * std::sin(2 * std::numbers::pi * freq * t);
            double jitter = noise * (2.0 * rand() / RAND_MAX - 1.0); // шум в [-noise, noise]

            trace_[i] = signal + jitter;
            ++recorded_;
        }

        std::cout << "В \"" << name_ << "\" Записано " << recorded_ << " отсчётов\n";
    }

    // Размах сигнала: max - min
    double ptp() const
    {
        if (recorded_ == 0)
            return 0;

        double lo = trace_[0], hi = trace_[0];
        for (size_t i = 1; i < recorded_; ++i)
        {
            if (trace_[i] < lo) lo = trace_[i];
            if (trace_[i] > hi) hi = trace_[i];
        }
        return hi - lo;
    }

    // Среднее значение
    double mean() const
    {
        if (recorded_ == 0)
            return 0;

        double s = 0;
        for (size_t i = 0; i < recorded_; ++i)
            s += trace_[i];
        return s / recorded_;
    }

    // Действующее значение (RMS)
    double rms() const
    {
        if (recorded_ == 0)
            return 0;

        double s = 0;
        for (size_t i = 0; i < recorded_; ++i)
            s += trace_[i] * trace_[i];
        return std::sqrt(s / recorded_);
    }

    // Сохранить осциллограмму в файл в csv (время,напряжение)
    void save(const std::string& filename) const
    {
        std::ofstream out(filename);
        double dt = 1e-4;
        for (size_t i = 0; i < recorded_; ++i)
            out << i * dt << "," << trace_[i] << "\n";

        std::cout << "\"" << name_ << "\" осциллограмма сохранена в " << filename << "\n";
        // Обратите внимание, что файл мы руками НЕ закрываем
        // У ofstream есть свой деструктор, он закроет файл сам,
        // когда out выйдет из области видимости. 
        // Та же идея, что и у нас.
    }

    // Геттеры для оператора вывода
    std::string name() const { return name_; }
    size_t recorded() const { return recorded_; }
};

std::ostream& operator<<(std::ostream& os, const Oscilloscope& scope)
{
    os << "Осциллограф \"" << scope.name() << "\": "
       << scope.recorded() << " отсчётов, размах " << scope.ptp()/2
       << " В, RMS " << scope.rms() << " В";
    return os;
}

// Ээксперимент
void run_experiment()
{
    Oscilloscope scope("Tektronix TBS1072", 2048);

    scope.record(50.0, 2.0, 0.05); // синус 50 Гц, амплитуда 2 В, плюс шум

    std::cout << scope << "\n";

    scope.save("trace.txt");

    std::cout << "U_RMS = " << scope.rms() << ", U_mean = " << scope.mean() << 
    ", U_ptp = " << scope.ptp()/2 << std::endl;

    // Здесь функция заканчивается и деструктор вызовется сам,
    // нам не надо об этом думать (не думать приятно)
    Oscilloscope another_scope = scope;
    std::cout << another_scope; 
}




int main()
{
    run_experiment();

    // Давайте познакомимся с концепцией "умного указателя"
    // Проблема обычных указателях -- ручной контроль выделенной памяти
    // К чему это может привести?

    // Мы уже рассмотрели несколько способов, которые позволяют избежать этих проблем:
    // использование ссылок вместо указателей 
    // и контейнеров стандартной библиотеки вместо C-style массивов

    
    // Если же по какой-то причине приходится использовать указатели,
    // то лучше заменить их на т.н. "умные указатели"

    // Умный указатель -- это класс-обертка над обычным указателем
    // Правильная реализация основных методов (особенно деструктора)
    // позволяет не беспокоится об утечках памяти

    // Давайте сами реализуем простенький "умный указатель", чтобы понять, как он устроен
    
    sp_present_func();

    // На самом деле мы реализовали т.н. unique_ptr -- у него нет конструктора копирования
    // Это нужно для того при удалении одного объекта sp_int другие не инвалидировались
    // Давайте в этом убедимся (см. smart_pointer.hpp)



    // Какая может при этом возникнуть проблема

    // Копирование может потребоваться, 
    // если хочется передать наш умный указатель в функцию в качестве аргумента
    // Как это сделать, если копирование запрещено?

    // Можно воспользоваться std::move
    // При этом будет вызван перемещаюший конструктор
    sp_int p1(new int(5));
    sp_int p2(new int(10));

    sp_int res = pow(std::move(p2), std::move(p1));
    // Обратите внимание: p1 и p2 теряют свои значения!

    // Есть также перемещающее присваивание
    p1 = sp_int(new int(50));
    p2 = sp_int(new int(50));

    // В С++ все сущности можно разделить на две категории:
    // rvalue и lvalue

    // lvalue представляет именованное значение
    // например, переменные, параметры, константы. 
    // lvalue имеет свой адрес в памяти, 
    // к которому можно обратиться и узнать/изменить лежащее в нем значение

    // А rvalue - это то, что можно только присваивать, 
    // например, литералы или результаты выражений.
    
    // например в выражении
    // p1 = sp_int(new int(50));
    // p1 - это lvalue -- в него можно что-то записать
    // а sp_int(new int(50)) возвращает rvalue -- результат функции исчезнет на следующем шагу,
    // если его никуда не записать, а выражение
    // sp_int(new int(50)) = new int (20) вызовет ошибку 
    std::cout << "Равны ли указатели: " << (p1 == p2) << std::endl;

    // Умные указатели уже есть std (нет необходимости писать свою реализацию)
    // Для доступа к ним нужно подключить заголовочный файл <memory>
    std::unique_ptr<double> std_up(new double(1.00500));
    // Есть еще shared_ptr -- его можно копировать
    // Проблема досрочного освобождения памяти решается подсчетом числа копий
}