#include <iostream>
#include <string>
#include <cmath>
#include <vector>

class ComplexNumber
{
    private:

    double real_;
    double img_;
    
    public:
    //Еще один способ создать конструктор:
    ComplexNumber(double r = 0, double i = 0)
    {
        real_ = r; 
        img_ = i;
    };

    //Конструктор копирования реализуется для копирования объектов
    ComplexNumber(const ComplexNumber& to_copy) //Он принимает ссылку на объект
    {
        real_ = to_copy.real_;
        img_ = to_copy.img_;
    }

    //Деструктор вызывается при удалении объекта (здесь он максимально прост)
    //На следующей паре рассмотрим примеры, где надо его реально реализовывать
    ~ComplexNumber(){} //Объявление деструктора: ~имя_класса()

    //Заметьте, что real и img -- перегружены
    double real() const
    {
        return real_;
    }
    double img() const
    {
        return img_;
    }

    //Версии методов для изменения значений (lvalue)
    double& real()
    {
        return real_;
    }
    double& img()
    {
        return img_;
    }
    
    //Оперция сопряжения
    void conj()
    {
        img_*=-1;
    }

    //Переопределяем операторы
    ComplexNumber operator=(const ComplexNumber& rightNumb)
    {
        real_ = rightNumb.real_;
        img_ = rightNumb.img_;

        return *this; // указатель на текущий объект
    }

    ComplexNumber operator+=(const ComplexNumber& rightNumb) 
    {
        real_ += rightNumb.real_;
        img_ += rightNumb.img_;
        return *this;
    }

    ComplexNumber operator-=(const ComplexNumber& rightNumb)
    {
        real_ -= rightNumb.real_;
        img_ -= rightNumb.img_;
        return *this;
    }


    ComplexNumber operator*=(const ComplexNumber& rightNumb)
    {
        real_ = real_*rightNumb.real_ - img_*rightNumb.img();
        img_ = img_*rightNumb.real() + rightNumb.img()*real_;
        return *this;
    }
    
    double abs() const
    {
        return std::sqrt(real_*real_ + img_*img_);
    }
    double arg() const
    {
        //Потенциально деление на 0!
        return std::atan(img_/real_);
    }

};

ComplexNumber operator+(const ComplexNumber& ln, const ComplexNumber& rn)
{
    // Оператор + должен вернуть новый объект с результатом сложения
    double real_res = ln.real() + rn.real();
    double img_res = ln.img() + rn.img();

    ComplexNumber res(real_res, img_res);
        
    return res;
}

ComplexNumber operator-(const ComplexNumber& ln, const ComplexNumber& rn)
{
    double real_res = ln.real() - rn.real();
    double img_res = ln.img() - rn.img();
        
    return ComplexNumber(real_res, img_res);
}

ComplexNumber operator*(const ComplexNumber& ln, const ComplexNumber& rn)
{
    double real_res = ln.real()*rn.real() - ln.img()*rn.img();
    double img_res = ln.real()*rn.img() + ln.img()*rn.real();

    return {real_res, img_res};
}

// Определяем операторы сравнения
bool operator==(const ComplexNumber& la, const ComplexNumber& ra)
{
    return (la.real() == la.real()) && (la.img() == ra.img());
}

bool operator!=(const ComplexNumber& la, const ComplexNumber& ra)
{
    return (la.real() != la.real()) && (la.img() != ra.img());
}

bool operator>(const ComplexNumber& la, const ComplexNumber& ra)
{
    return la.abs() > ra.abs();
}

bool operator<(const ComplexNumber& la, const ComplexNumber& ra)
{
    return la.abs() < ra.abs();
}

bool operator>=(const ComplexNumber& la, const ComplexNumber& ra)
{
    return !(la.abs() < ra.abs());
}

bool operator<=(const ComplexNumber& la, const ComplexNumber& ra)
{
    return !(la.abs() > ra.abs());
}

std::ostream& operator<<(std::ostream& os, const ComplexNumber& cn) {
    os << cn.real() << (cn.img() < 0 ? " + " : " - ") << cn.img() << "i";
    return os;
}

std::istream& operator>>(std::istream& is, ComplexNumber& cn) {
    std::string sign, i;
    is >> cn.real() >> sign >> cn.img() >> i;
    if(sign == "-")
        cn.img()*=-1;
    return is;
}

class Date
{
    private:
    int day_;
    int month_;
    int year_;

    public:
    Date(int day, int month, int year): day_(day), month_(month),  year_(year)
    {
        if(month > 12)
            month_ = 12;
        // На самом деле не самое удачное решение
        // Здесь лучше создать исключение с сообщением об ошибке
        // Но про это на одном из следующих занятий
    }
    Date(const Date& to_copy): day_(to_copy.day_), month_(to_copy.month_),  year_(to_copy.year_)
    {
        
    }

};

class Student
{
    private:
    std::string fio;
    Date birth_date;
    unsigned edu_year;

    float gpa;
    int passed_courses;

    bool is_expelled;

    public:
    Student(std::string name, Date dob, int year): birth_date(dob)
    {
        fio = name;
        edu_year =  year; 

        is_expelled = false;
        gpa = 0;
        passed_courses = 0;
    }

    void promote()
    {
        edu_year++;
        if(edu_year > 4)
            is_expelled = true;
    }
    void expell()
    {
        is_expelled = true;

        // надо поменять остальные поля, чтобы состояние объекта было согласованным
        edu_year = 0;
        gpa = 0;
        passed_courses = 0;
    }

    void takeExam(int mark)
    {
        if(mark > 5)
            mark = 5;

        if(mark < 3)
            return;
        
        gpa = (gpa*passed_courses + mark)/++passed_courses;
    }
    std::string get_name() const
    {
        return fio;
    }

    unsigned get_year() const
    {
        return edu_year;
    }
    
};


std::ostream& operator<<(std::ostream& os, const Student& student) 
{
    os << "Student " << student.get_name() << " is a " << student.get_year() << " year student\n" ;
    return os;
}

int main()
{
    // Сегодня начнем знакомство с ООП
    // Эта концепция программирования, в которой программа
    // состоит из взамиодействующих объектов
    // В C++ объекты появились, как развитие идеи структур из С++
    // Объекты, как и структуры, умеют хранить в себе набор данных (поля)
    // но также обладают набором функций, которые используются, 
    // чтобы менять эти данные
    // такие функции называются методами. 

    // основная идея: мы не даем пользователю прямого доступа к внутрянними
    // переменным, но взамен даем методы, которые могут эти переменные изменять,
    // возвращать пользователю их текущее значение и т.п.
    // иными словами создаем пользователю интерфейс
    // невозможность пользователю самостоятельно трогать поля класса, 
    // делает невозможным его сломать
    // (если он все таки справился то это наша вина, как разработчиков класса)

    // Рассмотрим на классе студента

    // При создании экзепляра класса (объекта) 
    // вызвается специальная функция: конструктор
    // в ней прописывается логика создания объекта (как проиницилизировать поля с данными)

    Student Vitalya("Keks Vitalii Ivanovich", Date(21, 10, 2001), 1);
    Student Valera("Duhov Valeriy Ivanovich", Date(6, 7, 2003), 3);
    
    // у нашего класса есть методы "get"'еры. Они нужны для доступа к полям

    std::cout << "Student " << Vitalya.get_name() << " is a " << Vitalya.get_year() << " year student\n";
    
    // можно перегрузить оператор вывода, чтобы легко печатать наши объекты в консоль
    std::cout << Valera;

    // внутрянее состяние (значение полей) наших объектов можно менять 
    // при помощи методов, которые мы (разработчики класса) написали
    
    // сдал матан
    Valera.takeExam(5);
    // сдал механику
    Valera.takeExam(4);
    // не сдал линал
    Valera.takeExam(2);

    // Отчислен
    Valera.expell();

    // А вот Виталя все сдал, его переводим на сл курс
    Vitalya.takeExam(5);
    Vitalya.takeExam(5);
    Vitalya.takeExam(5);

    Vitalya.promote();

    std::cout << Valera << Vitalya;
    // Мы могли бы и дальше создавать чудесный мир Валеры и Витали:
    // дописать им операцию сравнения, дополнительные поля (есть ли степендия и т.п.)
    // но мы переключимся на более релевантный нам, физикам, пример

    //Давайте создадим класс комплексных чисел (есть готовый класс в библиотеке complex)
    ComplexNumber c1; //Наш конструктор позволяет создавать комплексный числа по разному
    ComplexNumber c2(1);
    ComplexNumber c3(4, -4);

    //Можно создавать путем копирования
    ComplexNumber copied(c3);
    //Что будет, если приравняем int?
    ComplexNumber from_int = ComplexNumber(10);

    //Реализовали разные методы
    //Сопряжение
    c3.conj();
    
    std::cout << "Реальная часть: " << c3.real() << ", мнимая часть: " << c3.img() << std::endl;
    //Модуль и фаза
    std::cout<< "Модуль: " << c3.abs()  << ", Фаза: " << c3.arg() << std::endl;

    //Переопределили для нашего класса арифметические операторы
    ComplexNumber sum = c2 + c3;
    sum *= c2 - c3;

    //Для комплексных чисел определена оперция сравнения на равенство
    //Мы тоже ее определили:
    bool is_equal = (c2 == sum);

    //Можно определить правила, по которым вводится из/выводятся в стандартный поток
    //наши комплексные числа 
    std::cin >> c1;
    std::cout << c1; 

    //Объекты ComplexNumber можно хранить в vector
    std::vector<ComplexNumber> cvec = {{-5, 10}, c1, c2, c3};
    //т.о. мы таким образом определили наш класс, что работать с ним также удобно,
    // как и со встроенными типами


    return 0;
}