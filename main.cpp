#include <iostream>
#include <fstream>
#include <map>

std::map <size_t, std::map<size_t, std::string>> results;

void PrintHelp(){
    std::cout << "mtfind v1.0.0" << std::endl;
    std::cout << std::endl;
    std::cout << "to use mtfind: " << std::endl;
    std::cout << std::endl;
    std::cout << "mtfind Filename \"mask to find\"  " << std::endl;
    std::cout << "hwere mask alphabet symbols and ? any symbol" << std::endl;
    std::cout << "Example: \n mtfind inputfile.txt \"??put\"" << std::endl;
    std::cout << std::endl;
}
/*
bool compareStrWithMask(const std::string &str, const std::string &maskedStr){
    if (str.length() != maskedStr.length()) return false;

    for (int i = 0; i < str.length(); ++i){
        if (maskedStr[i] == '?' || maskedStr[i] == str[i]) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}
*/

std::string compareStrWithMask(const std::string &str, const std::string &maskedStr){
    std::string resultString;
    if (str.length() != maskedStr.length()) return "";

    for (int i = 0; i < str.length(); ++i){
        if (maskedStr[i] == '?' || maskedStr[i] == str[i]) {
            resultString += str[i];
            continue;
        } else {
            return "";
        }
    }
    return resultString;
}

size_t findWithMask(const std::string &inputString, std::string &maskForFind, size_t pos = 0){
    int lengthMask = maskForFind.length();
    int lengthString = inputString.length();
    int startToFind = 0, stopToFind = lengthString;

    for  ( int iStrCounter = pos; iStrCounter <= lengthString - lengthMask; ++iStrCounter){
        std::string strWithoutMask = compareStrWithMask(inputString.substr(iStrCounter,lengthMask), maskForFind);
        if (!strWithoutMask.empty()){
            maskForFind = strWithoutMask;
            return iStrCounter;
        }
    }
    return std::string::npos;
}

std::map <size_t, std::string> countSubstrInString (const std::string &inputStr, const std::string &findMask){

    std::map <size_t, std::string> posSubstr;
    std::string maskFind = findMask;
    size_t pos = findWithMask(inputStr, maskFind);
    while (pos != std::string::npos){
        posSubstr[pos] = maskFind;
        pos += findMask.length();
        maskFind = findMask;
        pos = findWithMask(inputStr, maskFind, pos);
    }
    return posSubstr;
}

int main(int argc, char* argv[]) {
std::string fileName = "input.txt";
std::string maskForFind = "?ad";
/*
    if (argc == 1 || argc != 3) {
        PrintHelp();
    } else {
        fileName = argv[1];
        maskForFind = argv[2];
        //extract from " " ;
        maskForFind = "extraction need";
    }
*/
    std::cout << fileName << std::endl;
    std::cout << maskForFind << std::endl;

    auto res = countSubstrInString("kjaddsf afjhfad jkfdsag hjad kjfsdaad ajkshv", "?ad");

    for (const auto &item:res){
        std::cout << item.first << " " << item.second << std::endl;
    }

 //   std::cout << findWithMask("kjaddsf afjhfad jkfdsag hjad kjfsdaad ajkshv", "ad");
    //std::cout << std::boolalpha << compareStrWithMask("asdfghj", "?sdfgh?");


    }
