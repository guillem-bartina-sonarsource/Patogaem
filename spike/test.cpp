
#include <iostream>

class Fact
{
    public:

    static const int num = 0;

    template<typename T>
    static bool extract()
    {
        return num == T::num;
    }
};

class Res : public Fact
{
    public:

    static const int num = 1;
};

int main()
{
    Fact* f = new Res();
    std::cout << f->extract<Fact>() << std::endl;
    delete f;
}