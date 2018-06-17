#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Interface
{
public:
    virtual ~Interface() {};
    Interface() = default;
    virtual void write(string &) = 0;
};
class Core : public Interface
{
public :
    Core() = default;
    virtual ~Core()
    {
        cout << "~Core()" << endl;
    }
    virtual void write(string &text) {}
};
class Decorator : public Interface
{
protected:
    unique_ptr<Interface> interface;
public:
    Decorator(unique_ptr<Interface> c)
    {
        interface = std::move(c);
    }
    virtual void write(string &text)
    {
        interface->write(text);
    }
};
class MessengerWithDecorator : public Decorator
{
protected:
    string hello;
public:
    MessengerWithDecorator() = default;
    MessengerWithDecorator(unique_ptr<Interface> c, const string &txt) : Decorator(std::move(c)), hello(txt) {}
    virtual ~MessengerWithDecorator()
    {
        cout << "~MessengerWithDecorator()" << endl;
    }
    virtual void write(string &text) override
    {
        text = hello + "\n" + text;
        Decorator::write(text);
    }
};
class MessengerWithValediction : public Decorator
{
protected:
    string valediction;
public:
    MessengerWithValediction() = default;
    MessengerWithValediction(unique_ptr<Decorator> c, string txt) : Decorator(std::move(c)), valediction(txt) {}
    virtual ~MessengerWithValediction()
    {
        cout << "~MessengerWithValediction" << endl;
    }
    virtual void write(string &text) override
    {
        Decorator::write(text);
        text = text + "\n" + valediction;
    }
};

int main() {
    return 0;
}