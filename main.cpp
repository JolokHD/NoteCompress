#include <array>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <iterator>
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


    //ENCODE
    std::string in;
    std::getline (std::cin,in);
    int bitlen = in.length() * 5;
    int addbits = 6 - (bitlen % 6);
    std::vector<bool> chararr(addbits);
    for(int i=0; i<(in.length()); i++){
        std::cout << i;
        std::array<bool, 5> temp = (encodeLetterChar(in.at(i)));
        chararr.insert(chararr.begin()+(i*5), temp.begin(), temp.end());
    }
    std::string returnstring;
    std::array<bool, 6> arr;
    for(int i=0; i<((bitlen+addbits)/6); i++){
        std::copy(chararr.begin()+(i*6), chararr.begin()+((i+1)*6), arr.data());
        returnstring += encodeBase64Char(arr);
    }
    if(addbits == 5){returnstring += '=';}
    std::cout << std::endl << "Data: ";
    for(int i=0; i < chararr.size(); i++){
        if( chararr.at(i) == false){std::cout << '0';} else {std::cout << '1';}
    }
    std::cout << std::endl << "Data: ";
    for(int i=0; i < arr.size(); i++){
        if( arr.at(i) == false){std::cout << '0';} else {std::cout << '1';}
    }
    std::cout << std::endl << returnstring;

    //DECODE
    bool removelast5Bits(false);
    if (returnstring.back() == '='){
        removelast5Bits = true;
        returnstring.pop_back();
    }
    std::vector<bool> baseVec(returnstring.size()*6);
    std::array<bool, 6> tempBase;
    for(int i=0; i<returnstring.size(); i++){
        tempBase = decodeBase64Char(returnstring.at(i));
        std::copy(tempBase.begin(), tempBase.end(), baseVec.begin()+(i*6));
    }
    std::cout << std::endl << "DataAfterBase64: ";
    for(int i=0; i < baseVec.size(); i++){
        if( baseVec.at(i) == false){std::cout << '0';} else {std::cout << '1';}
    }
    if(5-baseVec.size()%5 == 5){
        if(baseVec.size() != 0){
            if(removelast5Bits){
                baseVec.resize(baseVec.size()-5);
            }
        }
    }
    std::cout << std::endl << "Short: ";
    for(int i=0; i < baseVec.size(); i++){
        if( baseVec.at(i) == false){std::cout << '0';} else {std::cout << '1';}
    }
    std::cout << std::endl << returnstring;
}
