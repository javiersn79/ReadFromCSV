#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>


using namespace std;
using namespace boost::numeric::ublas;

int main(int argc, char *argv[])
{

    ifstream marketData;
    const string path="/Users/javier/Desktop/prueba US market visual/";;
    const string fileName="AAPLMarket6May2010.csv";
    string fullName=path+fileName;


    marketData.open (fullName.c_str());
            if(!marketData){
                cout << "ERROR: THE MARKET DATA COULD NOT BE FOUND"<<endl;

             }
            else{

                string line;
                matrix<double> m (1000, 50);
                unsigned int i=1;

                getline (marketData,line); //To ignore Header

                while ( getline (marketData,line) ){

                    line.append("\n");



                        string comp;
                        stringstream lineS(line);

                        //capture date hour, right now just ignoring everything
                        for (unsigned k = 0; k < 4; ++ k) getline(lineS,comp,',');

                        // capture LOB info

                            unsigned int j=1;
                            while (getline(lineS,comp,',')){
                                m(i++,j++)=stod(comp.c_str());
                                cout<<comp.c_str()<<endl;
                                }
                }

                marketData.close();
            }

    return 0;
}

