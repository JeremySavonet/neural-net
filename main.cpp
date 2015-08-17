#include <cassert>
#include <iostream>
#include <vector>

#include "Net.hpp"
#include "Neuron.hpp"
#include "TrainingData.hpp"

void showVectorVals( string label, vector<double> &v )
{
    cout << label << " " ;
    for( unsigned i = 0; i < v.size(); ++i )
    {
        cout << v[ i ] << " ";
    }

    cout << endl;
}

int main( void )
{
    TrainingData trainData("tmp/trainingData.dat");
    vector<unsigned> topology;
    trainData.getTopology( topology );
    Net myNet( topology );

    vector<double> inputVals;
    vector<double> targetVals;
    vector<double> resultVals;
    int trainingPass = 0;

    while( !trainData.isEof() )
    {
        ++trainingPass;
        cout << endl << "PASS " << trainingPass;

        // Get new input data and feed it forward
        if( trainData.getNextInputs( inputVals ) != topology[ 0 ] )
        {
            break;
        }
        showVectorVals( ": Inputs: ", inputVals );
        myNet.feedForward( inputVals );

        // Collect the net's actual results
        myNet.getResults( resultVals );
        showVectorVals( "Ouputs: ", resultVals );

        // Train the net what the output should have been
        trainData.getTargetOutputs( targetVals );
        showVectorVals( "Targets: ", targetVals );
        assert( targetVals.size() == topology.back() );

        myNet.backProp( targetVals );

        // Report how well the training is workin, averaged over recent
        cout << "Net recent average error:"
                << myNet.getRecentAverageError() << endl;
        cout << endl << "Done" << endl;
    }



    myNet.getResults( resultVals);
    return 0;
}

