#ifndef CLASS_H
#define CLASS_H

class Foo {

private:
    int m_nb;

public:
    Foo(int &n_nb);
    int getValue() const;
    void increment();

};

#endif
