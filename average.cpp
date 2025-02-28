#include <iostream>
#include <vector>
using namespace std;

int main(int argc,char* argv[]){
    if(argc < 2){
        cout << "Please input numbers to find average." << endl;
        return 1;
    }

    vector<double> number;
    double sum = 0;

    for(int i = 1; i < argc; i++){
        double num = atof(argv[i]);
        number.push_back(num);
        sum += num;
    }

    double average = sum/number.size();

    cout << "---------------------------------" << endl;
    cout << "Average of " << number.size() << " numbers = " << average << endl;
    cout << "---------------------------------" << endl;

    return 0;
}