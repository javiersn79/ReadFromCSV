#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<math.h>
#include<map>
#include<time.h>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>


using namespace std;
using namespace boost::numeric::ublas;

int main(int argc, char *argv[])
{
    const clock_t begin_time = clock();

    time_t rawtime;
    struct tm * timeinfo;
    map<string, int> months
        {
            { "JAN", 1 },
            { "FEB", 2 },
            { "MAR", 3 },
            { "APR", 4 },
            { "MAY", 5 },
            { "JUN", 6 },
            { "JUL", 7 },
            { "AUG", 8 },
            { "SEP", 9 },
            { "OCT", 10 },
            { "NOV", 11 },
            { "DEC", 12 }
        };


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
        matrix<double> mData (3000000, 50);
        matrix<long> timeStamp (3000000, 2);
        unsigned int i=1;

        getline (marketData,line); //To ignore Header

        while ( getline (marketData,line) ){

            line.append("\n");

            string comp;
            stringstream lineS(line);

            //to move forward two fields
            for (unsigned k = 0; k < 2; ++ k) getline(lineS,comp,',');

            //capture date
            //extracting important values
            int year     =stod(comp.substr(7,4).c_str());

            const auto iter = months.find(comp.substr(3,3).c_str());
            int month    =iter->second;

            int day      =stod(comp.substr(0,2).c_str());

            //move forward to get time
            getline(lineS,comp,',');

            //capture time
            int hour     =stod(comp.substr(0,2).c_str());
            int min      =stod(comp.substr(3,2).c_str());
            int sec      =stod(comp.substr(6,2).c_str());
            int millsec  =stod(comp.substr(9,6).c_str());

            rawtime = time(0);
            /* convert to struct: */
            timeinfo = localtime ( &rawtime );

            /* now modify the timeinfo to the given date: */
            timeinfo->tm_year   = year - 1900;
            timeinfo->tm_mon    = month - 1;    //months since January - [0,11]
            timeinfo->tm_mday   = day;          //day of the month - [1,31]
            timeinfo->tm_hour   = hour;         //hours since midnight - [0,23]
            timeinfo->tm_min    = min;          //minutes after the hour - [0,59]
            timeinfo->tm_sec    = sec;          //seconds after the minute - [0,59]

            /* call mktime: create unix time stamp from timeinfo struct */
            time_t date = mktime ( timeinfo );

            // Saving info from timeStamps
            timeStamp(i,0)=date;
            timeStamp(i,1)=(long)millsec;

            // advance the market maker label
            getline(lineS,comp,',');

            // capture LOB info

            unsigned int j=1;
            while (getline(lineS,comp,',')){
                try{
                    mData(i,j++)=stod(comp.c_str());
                    //cout<<comp.c_str()<<endl;
                }
                catch(exception &err){
                    mData(i,j++)=NAN;
                }
            }
            i++;
        }

        marketData.close();
        cout << "MSG: THE FILE WAS LOADED SUCCESSFULLY IN A MATRIX"<<endl;
        cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC<<endl;
    }

    /* Output so far is mData and timeStamp */ !!!!

    return 0;
}

