#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <iostream>
#include <string>

using namespace std;

class Logger
{
    public:
        Logger( string name );

    private:
        string _name;
};

#endif // LOGGER_HPP_
