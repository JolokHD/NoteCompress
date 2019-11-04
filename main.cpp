#include <array>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <stdexcept>

std::array<char, 64> Base64LookUpTable{ {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '/'} };
std::array<char, 32> LetterLockUpTable{ {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '.'} }; // 0-3 are reserved
template <std::size_t T> uint32_t bitArrayToInt(std::array<bool, T> arrayin){
    int returnval = 0;
    int temp;
    for (unsigned long long i = 0; i < T; i++) {
        temp = arrayin[i];
        returnval |= temp << (T - i - 1);
    }
    return returnval;
}
template <std::size_t T> std::array<bool, T> intToBitArray(uint32_t in){
    std::array<bool, T> returnarr;
    auto inval = in;
    for (unsigned int i = 0; i != T; ++i){
        returnarr[T - i - 1] = inval & 1;
        inval /= 2;
    }
    return returnarr;
}
char encodeBase64Char(std::array<bool, 6> inarr){
    return Base64LookUpTable[bitArrayToInt(inarr)];
}
char decodeLetterChar(std::array<bool, 5> inarr){
    return LetterLockUpTable[bitArrayToInt(inarr)];
}
std::array<bool, 6> decodeBase64Char(char inchar){
    auto pos = (std::find(std::begin(Base64LookUpTable), std::end(Base64LookUpTable), inchar));
    int dis;
    if(pos == std::end(Base64LookUpTable)){
      dis = 0;
    } else {
        dis = pos - Base64LookUpTable.begin();
    }
    return intToBitArray<6>(dis);
}
std::array<bool, 5> encodeLetterChar(char inchar){
    auto pos = (std::find(std::begin(LetterLockUpTable), std::end(LetterLockUpTable), inchar));
    int dis;
    if(pos == std::end(LetterLockUpTable)){
      dis = 0;
    } else {
        dis = pos - LetterLockUpTable.begin();
    }
    return intToBitArray<5>(dis);
}
int main(){
    while(true){
        std::cout << '>';
        std::string cmdin;
        std::getline (std::cin,cmdin);
        std::vector<std::string> args;
        if(cmdin.size() != 0){
            std::istringstream iss(cmdin);
            for(std::string s; iss >> s; ){
                args.push_back(s);
            }
        } else {
            args.push_back("Invalid");
        }
        if(args.at(0) == "exit"){
            exit(0);
        } else
        if(args.at(0) == "help"){
            std::cout << "<exit>: Exit this programm."                               << std::endl
                      << "<encode>: Encodes a String"                                << std::endl
                      << "<decode>: Decodes a encoded String"                        << std::endl
                      << "You can only use Capital Letters for a String to encode" << std::endl;
        } else
        if(args.at(0) == "encode"){
            std::cout << "Enter a String to encode: " << std::endl;
            //ENCODE
            std::string in;
            std::getline (std::cin,in);
            std::transform(in.begin(), in.end(),in.begin(), ::toupper);
            int bitlen = in.length() * 5;
            int addbits = 6 - (bitlen % 6);
            std::vector<bool> chararr(addbits);
            for(int i=0; i<(in.length()); i++){
                std::array<bool, 5> temp = (encodeLetterChar(in.at(i)));
                chararr.insert(chararr.begin()+(i*5), temp.begin(), temp.end());
            }
            std::string out;
            std::array<bool, 6> arr;
            for(int i=0; i<((bitlen+addbits)/6); i++){
                std::copy(chararr.begin()+(i*6), chararr.begin()+((i+1)*6), arr.data());
                out += encodeBase64Char(arr);
            }
            if(addbits == 5){out += '=';}
            std::cout << "Encoded String: " << out << std::endl;
        } else
        if(args.at(0) == "decode"){
            std::cout << "Enter a String to decode: " << std::endl;
            std::string in;
            std::getline (std::cin,in);
            //DECODE
            bool removelast5Bits(false);
            if (in.back() == '='){
                removelast5Bits = true;
                in.pop_back();
            }
            std::vector<bool> baseVec(in.size()*6);
            std::array<bool, 6> tempBase;
            for(int i=0; i<in.size(); i++){
                tempBase = decodeBase64Char(in.at(i));
                std::copy(tempBase.begin(), tempBase.end(), baseVec.begin()+(i*6));
            }
            if(5-baseVec.size()%5 == 5){
                if(baseVec.size() != 0){
                    if(removelast5Bits){
                        baseVec.resize(baseVec.size()-5);
                    }
                }
            } else {
                baseVec.resize(baseVec.size()-baseVec.size()%5);
            }
            std::string out;
            for(int i=0; i<(baseVec.size()/5); i++){
                std::array<bool, 5> temp;
                std::copy(baseVec.begin()+(i*5), baseVec.begin()+((i+1)*5), temp.begin());
                out += decodeLetterChar(temp);
            }
            std::cout << "Decoded String: " << out << std::endl;
        } else {
            std::cout << "Invalid Command"    << std::endl
                      << "For help type <help>" << std::endl;
        }
    }
}
