#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_

class Connection
{
    public:
        Connection();
        double getWeight( void ) const {return _weight;};
        void setWeight( double weight );
        double getDeltaWeight( void ) const {return _deltaWeight;};
        void setDeltaWeight( double deltaWeight );
    private:
        double _weight;
        double _deltaWeight;
};

#endif // CONNNECTION_HPP_
