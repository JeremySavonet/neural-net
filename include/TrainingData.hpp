#ifndef TRAININGDATA_HPP_
#define TRAININGDATA_HPP_

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class TrainingData
{
    public:
    TrainingData( const string fileName );
    bool isEof( void ) { return _trainingDataFile.eof(); }
    void getTopology( vector<unsigned> &topology );

    // Returns the number of input values read from the file
    unsigned getNextInputs( vector<double> &inputVals );
    unsigned getTargetOutputs( vector<double> &targetOutputVals );

    private:
        ifstream _trainingDataFile;

};

#endif // TRAININGDATA_HPP_
