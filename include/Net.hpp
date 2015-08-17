#ifndef NET_HPP_
#define NET_HPP_

#include <cassert>
#include <iostream>
#include <vector>

#include "Neuron.hpp"

using namespace std;

class Net
{
    typedef vector<Neuron> Layer;

    public:
        Net( const vector<unsigned> &topology );
        void feedForward( const vector<double> &inputVals );
        void backProp( const vector<double> &targetVals );
        void getResults( vector<double> &resultVals ) const;
        double getRecentAverageError( void ) const { return _recentAverageError; }

    private:
        double _error;
        double _recentAverageError;
        double _recentAverageSmoothingFactor;
        vector<Layer> _layers; // _layers[ layerNum ][ neuronNum ]

};

#endif // NET_HPP_
