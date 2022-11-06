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
        posSubstr[pos+1] = maskFind; //нумерация в string с 0, а обычные люди считают от 1.
        pos += findMask.length();
        maskFind = findMask;
        pos = findWithMask(inputStr, maskFind, pos);
    }
    return posSubstr;
}


int main(int argc, char* argv[]) {
std::string fileName = "input.txt";
std::string maskForFind = "?ad";
//    std::string maskForFind = "An";
size_t amountInsertion = 0;

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


    std::fstream textFile;

    textFile.open(fileName, std::ios::in);
    if (!textFile.is_open()){
        std::cout << "Unable to open file " + fileName << std::endl;
    } else
    {
        // построчное чтение файла
        std::string readString;
        size_t numberReadingString = 1;
        while (!textFile.eof()){
            std::getline(textFile, readString);

            //std::map <size_t, std::string>
            auto res = countSubstrInString(readString, maskForFind);
            results.insert(std::pair<size_t, std::map <size_t, std::string>>(numberReadingString, res));
            amountInsertion += res.size();
            numberReadingString++;
        }
    }
// вывод полученных результатов
std::cout << amountInsertion << std::endl;
    for (const auto &itemByString:results){
        for (const auto &item:itemByString.second){
            std::cout << itemByString.first << " "; //номер строки
            std::cout << item.first << " "; // позиция вхождения
            std::cout << item.second << std::endl; // строка вхождения и перевод строки.
        }
    }


    /*
    for (const auto &item:res){
        std::cout << item.first << " " << item.second << std::endl;
    }
*/
 //   std::cout << findWithMask("kjaddsf afjhfad jkfdsag hjad kjfsdaad ajkshv", "ad");
    //std::cout << std::boolalpha << compareStrWithMask("asdfghj", "?sdfgh?");


    }
