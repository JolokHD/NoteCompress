#include <vector>
#include <array>
#include <string>
#include <iostream>

std::array<char, 64> Base64LookUpTable{ {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '/'} };
template <std::size_t T> uint32_t bitArrayToInt(std::array<bool, T> arr){
    int ret = 0;
    int tmp;
    for (unsigned long long i = 0; i < T; i++) {
        tmp = arr[i];
        ret |= tmp << (T - i - 1);
    }
    return ret;
}
template <std::size_t T> std::array<bool, T> intToBitArray(uint32_t in){
    std::array<bool, T> returnarr;
    auto inval = in;
    for (unsigned int i = 0; i != T; ++i){
        returnarr[i] = inval & 1;
        inval /= 2;
    }
    return returnarr;
}
template <std::size_t T> std::string encodeBase64(std::array<bool, T> inarr){
    auto addLength = 6-(T%6);
    std::string returnstr;
    
    if(addLength == 5){
        returnstr+=" ";
    }
}
int main(){
    std::array<bool, 3> test{{false, false, true}};
    std::array<bool, 3> test2 = intToBitArray<3>(5);
    std::cout << bitArrayToInt(test);
    std::cout << bitArrayToInt(test2);
}