#include <iostream> // string, cout, cin
#include <math.h> // pow
#include <cstdlib> // rand, srand
#include <time.h> // time
#include <iomanip> // setw
#include <cstdlib> // system(cls)

using namespace std;

int getRngRangeStringLength(int rangeMin, int rangeMax);

int main()
{
    srand(time(0));
    bool running = 1;

    while (running) {
        int rangeRngMin = 1,
            rangeRngMax,
            rangeQuantityMin = 1,
            rangeQuantityMax,
            randomNumber;
        int rangeOneMin,
            rangeOneMax,
            rangeTwoMin,
            rangeTwoMax,
            rangeThreeMin,
            rangeThreeMax,
            rangeFourMin,
            rangeFourMax,
            rangeFiveMin,
            rangeFiveMax,
            rangeSixMin,
            rangeSixMax,
            rangeSevenMin,
            rangeSevenMax,
            rangeEightMin,
            rangeEightMax,
            rangeNineMin,
            rangeNineMax,
            rangeTenMin,
            rangeTenMax;
        int rangeCount[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        string histogramSymbol;
        int histogramSymbolOccurance,
            histogramSpacing = 15,
            histogramTotalSpacing = 33;
        string runAgain;
        locale loc;

        cout << "Welcome to the random number generator.\n" << endl;

        /*
         * BUG: sometimes when a range is given with a starting value
         * greater than 0 (eg. 100-1000), 1 or more of the output ranges
         * will have no occurances.
        */

        /* disabling until bug is fixed
        cout << "Enter a MINIMUM range for the random number generator. \nSUGGESTED: 1." << endl;
        for (;;) {
            cin >> rangeRngMin;
            if (!cin.good() || rangeRngMin < 0 || rangeRngMin > 31999) {
                cout << "Invalid number! Minimum range must be between 0 and 31999." << endl;
                cin.clear();
                cin.ignore
                (128, '\n');
            } else {
                cout << endl;
                break;
            }
        }
        */

        cout << "Enter a MAXIMUM range for the random number generator. (min is " << rangeRngMin << ") \nSUGGESTED: 100." << endl;
        for (;;) {
            cin >> rangeRngMax;
            if (!cin.good() || rangeRngMax < 10 || rangeRngMax > 32000 || rangeRngMax <= rangeRngMin || (rangeRngMax - rangeRngMin) < 99) {
                cout << "Invalid number! Maximum range must be between 100 and 32000." << endl; // AND at least 100 more than the minimum
                cin.clear();
                cin.ignore
                (128, '\n');
            } else {
                cout << endl;
                break;
            }
        }

        /*
         * BUG: if a value entered is less than 200, a crash will occur when the graph is drawn when
         * calculating how many occurances a symbol should have. this can be resolved with a fixed
         * value of occurances per line, but this wouldn't allow the graph to be as dynamic with
         * different ranges of quantities.
         * Another solution is to create an exception for when an input is < 200 and resort to a
         * value which will not crash the program.
        */
        cout << "How many values would you like to generate? \nSUGGESTED: 10000." << endl;
        for (;;) {
            cin >> rangeQuantityMax;
            if (!cin.good() || rangeQuantityMax < 200) {
                cout << "Invalid number! Range must be 200 or greater." << endl;
                cin.clear();
                cin.ignore
                (128, '\n');
            } else {
                cout << endl;
                break;
            }
        }

        cout << "Which character would you like to represent the data? \nDEFAULT: | (pipe). enter 'd' to use default." << endl;
        for (;;) {
            cin >> histogramSymbol;
            if (!cin.good() || histogramSymbol.length() > 1) {
                cout << "Invalid symbol! Must only be one character." << endl;
                cin.clear();
                cin.ignore
                (128, '\n');
            } else {
                if (histogramSymbol == "d") {
                    histogramSymbol = "|";
                }
                cout << endl;
                break;
            }
        }

        // added + 0.1 to each multiplication because of something that has to do with floating points arithmetic.
        // some values were rounding down towards 0 (ie. 29 instead of 30 when doing 100 * 0.3) without this fix
        rangeOneMin = rangeRngMin;
        rangeOneMax = (rangeOneMin + (rangeRngMax * 0.1) - 1);
        rangeTwoMin = rangeOneMax + 1;
        rangeTwoMax = rangeRngMax * 0.2 + 0.1;
        rangeThreeMin = rangeTwoMax + 1;
        rangeThreeMax = rangeRngMax * 0.3 + 0.1;
        rangeFourMin = rangeThreeMax + 1;
        rangeFourMax = rangeRngMax * 0.4 + 0.1;
        rangeFiveMin = rangeFourMax + 1;
        rangeFiveMax = rangeRngMax * 0.5 + 0.1;
        rangeSixMin = rangeFiveMax + 1;
        rangeSixMax = rangeRngMax * 0.6 + 0.1;
        rangeSevenMin = rangeSixMax + 1;
        rangeSevenMax = rangeRngMax * 0.7 + 0.1;
        rangeEightMin = rangeSevenMax + 1;
        rangeEightMax = rangeRngMax * 0.8 + 0.1;
        rangeNineMin = rangeEightMax + 1;
        rangeNineMax = rangeRngMax * 0.9 + 0.1;
        rangeTenMin = rangeNineMax + 1;
        rangeTenMax = rangeRngMax;

        /* debug test
        cout << "range one is " << rangeOneMin << " to " << rangeOneMax << endl;
        cout << "range two is " << rangeTwoMin << " to " << rangeTwoMax << endl;
        cout << "range 3 is " << rangeThreeMin << " to " << rangeThreeMax << endl;
        cout << "range 4 is " << rangeFourMin << " to " << rangeFourMax << endl;
        cout << "range 5 is " << rangeFiveMin << " to " << rangeFiveMax << endl;
        cout << "range 6 is " << rangeSixMin << " to " << rangeSixMax << endl;
        cout << "range 7 is " << rangeSevenMin << " to " << rangeSevenMax << endl;
        cout << "range 8 is " << rangeEightMin << " to " << rangeEightMax << endl;
        cout << "range 9 is " << rangeNineMin << " to " << rangeNineMax << endl;
        cout << "range 10 is " << rangeTenMin << " to " << rangeTenMax << endl;
        */

        // START of number generation and range sorting
        for (int i = 0; i < rangeQuantityMax; i++) {
            randomNumber = rand() % (rangeRngMax - rangeRngMin + 1) + rangeRngMin;

            // cout << "the rng is " << randomNumber << endl;
            if ( (randomNumber >= rangeOneMin) && (randomNumber <= rangeOneMax) ) {
                rangeCount[0]++;
            } else if ( (randomNumber >= rangeTwoMin) && (randomNumber <= rangeTwoMax) ) {
                rangeCount[1]++;
            } else if ( (randomNumber >= rangeThreeMin) && (randomNumber <= rangeThreeMax) ) {
                rangeCount[2]++;
            } else if ( (randomNumber >= rangeFourMin) && (randomNumber <= rangeFourMax) ) {
                rangeCount[3]++;
            } else if ( (randomNumber >= rangeFiveMin) && (randomNumber <= rangeFiveMax) ) {
                rangeCount[4]++;
            } else if ( (randomNumber >= rangeSixMin) && (randomNumber <= rangeSixMax) ) {
                rangeCount[5]++;
            } else if ( (randomNumber >= rangeSevenMin) && (randomNumber <= rangeSevenMax) ) {
                rangeCount[6]++;
            } else if ( (randomNumber >= rangeEightMin) && (randomNumber <= rangeEightMax) ) {
                rangeCount[7]++;
            } else if ( (randomNumber >= rangeNineMin) && (randomNumber <= rangeNineMax) ) {
                rangeCount[8]++;
            } else if ( (randomNumber >= rangeTenMin) && (randomNumber <= rangeTenMax) ) {
                rangeCount[9]++;
            }

            /* // debug: output array
            for (int iarray = 0; iarray < 10; iarray++) {
                cout << rangeCount[iarray] << " ";
            }
            cout << endl;
            */
        }
        // END of number generation and range sorting

        // int at the end determines frequency of occurances for the symbol on the histogram. default is 100
        // if changed, remember to update input check
        histogramSymbolOccurance = (rangeQuantityMax / 200);

        cout << "Range:"
            << setw(9) << "" << "Frequency: (1 symbol = " << histogramSymbolOccurance << " occurences)" << endl;

        // BEGIN range 1
        cout << rangeOneMin << "-" << rangeOneMax << setw(histogramSpacing - getRngRangeStringLength(rangeOneMin, rangeOneMax)) << "";
        // write symbol for each occurance
        for (int i = 0; i < (rangeCount[0] / histogramSymbolOccurance); i++) {
            cout << histogramSymbol;
        }
        // display actual occurance count on the same line
        cout << setw(histogramTotalSpacing - (rangeCount[0] / histogramSymbolOccurance)) << "  " << rangeCount[0] << endl;
        // END range 1

        // BEGIN range 2
        cout << rangeTwoMin << "-" << rangeTwoMax << setw(histogramSpacing - getRngRangeStringLength(rangeTwoMin, rangeTwoMax)) << "";
        for (int i = 0; i < (rangeCount[1] / histogramSymbolOccurance); i++) {
            cout << histogramSymbol;
        }
        cout << setw(histogramTotalSpacing - (rangeCount[1] / histogramSymbolOccurance)) << "  " << rangeCount[1] << endl;
        // END range 2

        // BEGIN range 3
        cout << rangeThreeMin << "-" << rangeThreeMax << setw(histogramSpacing - getRngRangeStringLength(rangeThreeMin, rangeThreeMax)) << "";
        for (int i = 0; i < (rangeCount[2] / histogramSymbolOccurance); i++) {
            cout << histogramSymbol;
        }
        cout << setw(histogramTotalSpacing - (rangeCount[2] / histogramSymbolOccurance)) << "  " << rangeCount[2] << endl;
        // END range 3

        // BEGIN range 4
        cout << rangeFourMin << "-" << rangeFourMax << setw(histogramSpacing - getRngRangeStringLength(rangeFourMin, rangeFourMax)) << "";
        for (int i = 0; i < (rangeCount[3] / histogramSymbolOccurance); i++) {
            cout << histogramSymbol;
        }
        cout << setw(histogramTotalSpacing - (rangeCount[3] / histogramSymbolOccurance)) << "  " << rangeCount[3] << endl;
        // END range 4

        // BEGIN range 5
        cout << rangeFiveMin << "-" << rangeFiveMax << setw(histogramSpacing - getRngRangeStringLength(rangeFiveMin, rangeFiveMax)) << "";
        for (int i = 0; i < (rangeCount[4] / histogramSymbolOccurance); i++) {
            cout << histogramSymbol;
        }
        cout << setw(histogramTotalSpacing - (rangeCount[4] / histogramSymbolOccurance)) << "  " << rangeCount[4] << endl;
        // END range 5

        // BEGIN range 6
        cout << rangeSixMin << "-" << rangeSixMax << setw(histogramSpacing - getRngRangeStringLength(rangeSixMin, rangeSixMax)) << "";
        for (int i = 0; i < (rangeCount[5] / histogramSymbolOccurance); i++) {
            cout << histogramSymbol;
        }
        cout << setw(histogramTotalSpacing - (rangeCount[5] / histogramSymbolOccurance)) << "  " << rangeCount[5] << endl;
        // END range 6

        // BEGIN range 7
        cout << rangeSevenMin << "-" << rangeSevenMax << setw(histogramSpacing - getRngRangeStringLength(rangeSevenMin, rangeSevenMax)) << "";
        for (int i = 0; i < (rangeCount[6] / histogramSymbolOccurance); i++) {
            cout << histogramSymbol;
        }
        cout << setw(histogramTotalSpacing - (rangeCount[6] / histogramSymbolOccurance)) << "  " << rangeCount[6] << endl;
        // END range 7

        // BEGIN range 8
        cout << rangeEightMin << "-" << rangeEightMax << setw(histogramSpacing - getRngRangeStringLength(rangeEightMin, rangeEightMax)) << "";
        for (int i = 0; i < (rangeCount[7] / histogramSymbolOccurance); i++) {
            cout << histogramSymbol;
        }
        cout << setw(histogramTotalSpacing - (rangeCount[7] / histogramSymbolOccurance)) << "  " << rangeCount[7] << endl;
        // END range 8

        // BEGIN range 9
        cout << rangeNineMin << "-" << rangeNineMax << setw(histogramSpacing - getRngRangeStringLength(rangeNineMin, rangeNineMax)) << "";
        for (int i = 0; i < (rangeCount[8] / histogramSymbolOccurance); i++) {
            cout << histogramSymbol;
        }
        cout << setw(histogramTotalSpacing - (rangeCount[8] / histogramSymbolOccurance)) << "  " << rangeCount[8] << endl;
        // END range 9

        // BEGIN range 10
        cout << rangeTenMin << "-" << rangeTenMax << setw(histogramSpacing - getRngRangeStringLength(rangeTenMin, rangeTenMax)) << "";
        for (int i = 0; i < (rangeCount[9] / histogramSymbolOccurance); i++) {
            cout << histogramSymbol;
        }
        cout << setw(histogramTotalSpacing - (rangeCount[9] / histogramSymbolOccurance)) << "  " << rangeCount[9] << endl;
        // END range 10


        // ask to restart
        cout << "\nWould you like to run the random number generator again? (Y/N)" << endl;

        for (;;) {
        cin >> runAgain;

        // convert answer to lower case
        for (string::size_type i=0; i < runAgain.length(); i++)
            runAgain[i] = tolower(runAgain[i],loc);

            if (!cin.good() || (runAgain != "y" && runAgain != "n")) {
                cout << "\nThat is not a valid option. Y or N?" << endl;
                cin.clear();
                cin.ignore
                (128, '\n');
            } else {
                if (runAgain == "n") {
                    running = 0;
                } else {
                    running = 1;
                    cout << endl;
                    if (system("CLS")) system("clear");
                }
                break;
            }
        }
    }

    return 0;
}

int getRngRangeStringLength(int rangeMin, int rangeMax) {
    // usage: input rangeRngMin and rangeRngMax. returns length of string for histogram (eg. "1-10" = (1, 10))
    int rangeMinPower = 1,
        rangeMaxPower = 1;

    // calculates length of int. checks if rangeMinPower to the power of 10 is < rangeMin
    while (pow(10, rangeMinPower) <= rangeMin)
        rangeMinPower++;
    while (pow(10, rangeMaxPower) <= rangeMax)
        rangeMaxPower++;

    // + 1 represents the "-" in the string
    int rangeLength = rangeMinPower + rangeMaxPower + 1;
    return rangeLength;
}
