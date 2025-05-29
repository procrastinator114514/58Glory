#pragma once

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

namespace loginfo{
	std::string s_time() {
	    auto now = std::chrono::system_clock::now();
	    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
	    std::tm now_tm = *std::localtime(&now_time_t);
	    std::ostringstream oss;
	    oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
	    return oss.str();
}
	
	void loginfo(const vector<string> &s, string case_t = "INFO"){
		ifstream file("log.txt");
		if (!file){
			ofstream outFile("log.txt");
			if (!outFile){
				cerr<<"No such file or dictory!"<<endl;
			}
			for(string i : s){
				outFile<<s_time()<<" "<<case_t<<": "<<i<<std::endl;
			}
			outFile<<s_time()<<" INFO: succesfully write a log!"<<std::endl;
			outFile.close();
			return;
		}
		else{
			ofstream outFile("log.txt",ios::app);
			for(string i : s){
				outFile<<s_time()<<" "<<case_t<<": "<<i<<std::endl;
			}
			outFile<<s_time()<<" INFO: succesfully write a log!"<<std::endl;
			outFile.close();
			return;
		}
	}
	
	void loginfo(const string &s, string case_t = "INFO"){
		ifstream file("log.txt");
		if (!file){
			ofstream outFile("log.txt");
			if (!outFile){
				cerr<<"No such file or dictory!"<<endl;
			}
			
			outFile<<s_time()<<" "<<case_t<<": "<<s<<std::endl;
			
			outFile<<s_time()<<" INFO: succesfully write a log!"<<std::endl;
			outFile.close();
			return;
		}
		else{
			ofstream appFile("log.txt",ios::app);
			
			appFile<<s_time()<<" "<<case_t<<": "<<s<<std::endl;
			
			appFile<<s_time()<<" INFO: succesfully write a log!"<<std::endl;
			appFile.close();
			return;
		}
	}
	
}