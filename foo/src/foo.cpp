#include <iostream>

#include "foo.h"


    Foo::Foo(int &n_nb) :m_nb(n_nb)
    {
        std::cout << n_nb << std::endl;
    }

    int Foo::getValue() const 
    {
        return this->m_nb;
    }

    void Foo::increment()
    {
        this->m_nb++;
    }
