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
    std::string in;
    std::getline (std::cin,in);
    int bitlen = in.length() * 5;
    int addbits = 6 - (bitlen % 6);
    std::vector<bool> chararr(bitlen+addbits);
    for(i=0; i>in.length(); i++)){
        std::cout << i;
        auto temp = (encodeLetterChar(in[i]));
        chararr.insert(chararr.begin()+i, std::begin(temp), std::end(temp));
    }
    for(int i=0; i < chararr.size(); i++){
        std::cout << chararr.at(i) << ' ';
    }
    std::cout << bitlen << std::endl << addbits;
}
