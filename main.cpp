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
    virtual void write(string &text)
    {
        cout << "Core::write " << text << endl;
    }
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
    MessengerWithValediction(unique_ptr<Interface> c, const string &txt) : Decorator(std::move(c)), valediction(txt) {}
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
    string hello = "Hello baby, ";
    string valediction = "Sincerly, Hehe";
    string mess1 = "Message is not decorated";
    string mess2 = "Message is decorated with Hello";
    string mess3 = "Message is decorated with Valediction";
    string mess4 = "Message is decorated with Hello and Valediction";

    unique_ptr<Interface> messenger1 = make_unique<Core>();
    unique_ptr<Interface> messenger2 = make_unique<MessengerWithDecorator>(make_unique<Core>(), hello);
    unique_ptr<Interface> messenger3 = make_unique<MessengerWithValediction>(make_unique<Core>(), valediction);
    unique_ptr<Interface> messenger4 = make_unique<MessengerWithValediction>(
            make_unique<MessengerWithDecorator>(make_unique<Core>(), hello), valediction);

    cout << "Message 1" << endl;
    messenger1->write(mess1);
    cout << "Message 2" << endl;
    messenger2->write(mess2);
    cout << "Message 3" << endl;
    messenger3->write(mess3);
    cout << "Message 4" << endl;
    messenger4->write(mess4);

    return 0;
}