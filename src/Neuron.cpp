#include "Neuron.hpp"

double Neuron::eta =  0.15;
double Neuron::alpha = 0.5;

Neuron::Neuron( unsigned numOutputs, unsigned weightIndex )
{
    for( unsigned c = 0; c < numOutputs; ++c )
    {
        _outputWeights.push_back( Connection() );
        _outputWeights.back().setWeight( randomWeight() );
    }

    _weightIndex = weightIndex;
}

void Neuron::feedForward( const Layer &prevLayer )
{
    double sum = 0.0;

    // Sum the previous layer's output (which are our inputs)
    // Include the bias node from the previous layer
    for( unsigned n = 0; n < prevLayer.size(); ++n )
    {
        sum += prevLayer[ n ].getOutputVal() *
                prevLayer[ n ]._outputWeights[ _weightIndex ].getWeight();
    }

    setOutputVal( Neuron::transfertFunction( sum ) );

}

double Neuron::transfertFunction( double x )
{
    // tanh => output range [ -1.0 .. 1.0 ]
    return tanh( x );
}

double Neuron::transfertFunctionDerivative( double x )
{
    // derivative tanh approximation
    return 1.0 - x * x;
}

void Neuron::calcOutputGradients( const double targetVal )
{
    double delta = targetVal - _outputVal;
    _gradient = delta * Neuron::transfertFunctionDerivative( _outputVal );
}

void Neuron::calcHiddenGradients( const Layer &nextLayer )
{
    double dow = sumDOW( nextLayer );
    _gradient = dow * Neuron::transfertFunctionDerivative( _outputVal );
}

void Neuron::updateInputWeights( Layer &prevLayer )
{
    // The weights to be updated are in the Connection container
    // in the neuron in hte preceding layer
    for( unsigned n = 0; n < prevLayer.size(); ++n )
    {
        Neuron &neuron = prevLayer[ n ];
        double oldDeltaWeight = neuron._outputWeights[ _weightIndex ].getDeltaWeight();

        double newDeltaWeight =
                // Individual input, magnified by the gradient and train rate
                eta // overall net learning rate :
                    // 0.0 - slow learner / 0.2 - medium learner / 1.0 - reckless learner
                * neuron.getOutputVal()
                * _gradient
                // Also add momentum =  a fraction of the previous delta weight
                + alpha // Momentum : 0.0 - no momentum / 0.5 - moderate momentum
                * oldDeltaWeight;

        neuron._outputWeights[ _weightIndex ].setDeltaWeight( newDeltaWeight );
        neuron._outputWeights[ _weightIndex ].setWeight(
                neuron._outputWeights[ _weightIndex ].getWeight() +
                newDeltaWeight );
    }
}

double Neuron::sumDOW( const Layer &nextLayer ) const
{
    double sum = 0.0;

    // Sum our contributions of the errors at the nodes we feed
    for( unsigned n = 0; n < nextLayer.size() - 1; ++n )
    {
        sum += _outputWeights[ n ].getWeight() * nextLayer[ n ]._gradient;
    }
    return sum;
}

