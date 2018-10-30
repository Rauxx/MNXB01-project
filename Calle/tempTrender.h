#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string>
#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

#include <TH1.h>
#include <TCanvas.h>

class tempTrender {
	public:
	string helpString;
	
	tempTrender(string pathToFile); //Construct using the specified file
	~tempTrender() {} //Destructor
	
	void readFile(string pathToFile) {pathToFile_ = pathToFile;}
	
	void tempOnDay(int monthToCalculate, int dayToCalculate, double specTemp = std::numeric_limits<double>::quiet_NaN()) {
		ifstream file(pathToFile_);
		TH1I* hist = new TH1I("temperature", "Temperature;Temperature[#circC];Entries", 300, -20, 40);
		hist->SetFillColor(kRed + 1);
		
		int month = -1, day = -1;
		double temp = -1;
		while(file >> helpString) {
			file >> month >> day >> helpString >> temp >> helpString;
			if(month == monthToCalculate and day == dayToCalculate) {
				hist->Fill(temp);
			}
		}
		
		if(specTemp == specTemp){
			int binNum = hist->FindBin(specTemp);
			double binEntries = hist->GetEntries();
			double specBinEntries = hist->GetBinContent(binNum);
			double tempProb = specBinEntries/binEntries;
			cout << "Probability of temp being " << specTemp << " degrees: " << tempProb*100 << " %" << endl;
		}

		double mean = hist->GetMean(); //The mean of the distribution
		double stdev = hist->GetRMS(); //The standard deviation
		TCanvas* can = new TCanvas();
		hist->Draw();
			
		cout << "Mean temp: " << mean << endl;
		cout << "Std Dev : " << stdev << endl;
		
	;} //Make a histogram of the temperature on this day
	//void tempOnDay(int dateToCalculate); //Make a histogram of the temperature on this date
	//void tempPerDay(); //Make a histogram of the average temperature of each day of the year
	//void hotCold(); //Make a histogram of the hottest and coldest day of the year
	//void tempPerYear(int yearToExtrapolate); //Make a histogram of average temperature per year, then fit and extrapolate to the given year

	private:
	string pathToFile_;
};

#endif
