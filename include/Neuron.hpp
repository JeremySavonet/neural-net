#ifndef NEURON_HPP_
#define NEURON_HPP_

#include <cmath>
#include <cstdlib>
#include <vector>

#include "Connection.hpp"

using namespace std;

class Neuron
{
    typedef vector<Neuron> Layer;

    public:
        Neuron( unsigned numOutputs, unsigned weightIndex );
        void feedForward( const Layer &prevLayer );
        double getOutputVal( void ) const { return _outputVal; }
        void setOutputVal( double val ) { _outputVal = val; }
        void calcOutputGradients( const double targetVal );
        void calcHiddenGradients( const Layer &nextLayer );
        void updateInputWeights( Layer &prevLayer );


    private:
        static double eta; // [0.0 .. 1.0] overall net training rate
        static double alpha;
        double _outputVal;
        unsigned _weightIndex;
        double _gradient;
        vector<Connection> _outputWeights;
        static double transfertFunction( double x );
        static double transfertFunctionDerivative( double x );
        static double randomWeight( void ) { return rand() / double( RAND_MAX ); }
        double sumDOW( const Layer &nextLayer ) const;
};


#endif // NEURON_HPP_
