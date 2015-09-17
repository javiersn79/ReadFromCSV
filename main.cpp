#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<math.h>
#include<time.h>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>


using namespace std;
using namespace boost::numeric::ublas;

int main(int argc, char *argv[])
{
    const clock_t begin_time = clock();

    ifstream marketData;
    const string path="/Users/javier/Desktop/prueba US market visual/";
    const string fileName="AAPLMarket6May2010.csv";
    string fullName=path+fileName;


    marketData.open (fullName.c_str());
    if(!marketData){
        cout << "ERROR: THE MARKET DATA COULD NOT BE FOUND"<<endl;
        cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC;
    }
    else{

        string line;
        matrix<double> m (3000000, 50);
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
                try{
                    m(i,j++)=stod(comp.c_str());
                    //cout<<comp.c_str()<<endl;
                }
                catch(exception &err){
                    m(i,j++)=NAN;
                }
            }
            i++;
        }

        marketData.close();
        cout << "MSG: THE FILE WAS LOADED SUCCESSFULLY IN A MATRIX"<<endl;
        cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC<<endl;
    }

    return 0;
}

