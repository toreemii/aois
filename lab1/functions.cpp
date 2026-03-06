#include "header.h"

std::vector<int> signMagnitude(int number)
{
    std::vector<int> resultReversed;
    std::vector<int> result;
    bool isNegative = false;

    if (number < 0)
    {
        isNegative = true;
        number = abs(number);
    }

    do
    {
        resultReversed.push_back(number % 2);
        number /= 2;
    } while (number > 0);

    for (int i = 0; i < 32 - resultReversed.size(); i++)
    {
        if (isNegative && i == 0)
        {
            result.push_back(1);
            continue;
        }
        result.push_back(0);
    }

    for (int i = resultReversed.size() - 1; i >= 0; i--)
    {
        result.push_back(resultReversed[i]);
    }
    return result;
}

std::vector<int> onesComplement(int number)
{
    std::vector<int> resultReversed;
    std::vector<int> result;
    bool isNegative = false;

    if (number < 0)
    {
        isNegative = true;
        number = abs(number);
    }
    else
    {
        return signMagnitude(number);
    }

    do
    {
        resultReversed.push_back(number % 2 == 0 ? 1 : 0);
        number /= 2;
    } while (number > 0);

    for (int i = 0; i < 32 - resultReversed.size(); i++)
    {
        if (isNegative && i == 0)
        {
            result.push_back(1);
            continue;
        }
        result.push_back(1);
    }

    for (int i = resultReversed.size() - 1; i >= 0; i--)
    {
        result.push_back(resultReversed[i]);
    }
    return result;
}

std::vector<int> sum(std::vector<int> num1, std::vector<int> num2)
{
    int size = std::max(num1.size(), num2.size());
    if (size < 5) size = 5;
    
    while (num1.size() < size) num1.insert(num1.begin(), 0);
    while (num2.size() < size) num2.insert(num2.begin(), 0);
    
    std::vector<int> result(size, 0);
    int carry = 0;

    for (int i = size - 1; i >= 0; i--)
    {
        int s = num1[i] + num2[i] + carry;

        result[i] = s % 2;
        carry = s / 2;
    }

    return result;

}

std::vector<int> twosComplement(int number)
{
    if (number < 0)
    {
        std::vector<int> onesComplementNumber = onesComplement(number);
        std::vector<int> oneBiteCode = onesComplement(1);
        return sum(onesComplementNumber, oneBiteCode);
    }
    return signMagnitude(number);
}

void printVector(std::vector<int> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i];
    }
    std::cout << std::endl;
}

int twosToTen(std::vector<int> vec) {
    int result = 0;
    
    if (vec[0] == 1) {
        result = -2147483648;
    }

    for (int i = 1; i < 32; i++) {
        if (vec[i] == 1) {
            result += (1 << (31 - i));
        }
    }
    return result;
}

std::vector<int> multiply(int number1, int number2)
{
    std::vector<int> num1 = signMagnitude(number1);
    std::vector<int> num2 = signMagnitude(number2);
    std::vector<int> result(32, 0);
    for (int i = num2.size() - 1, j = 0; i >= 0; i--, j++)
    {
        if (num2[i] == 1)
        {
            result = sum(result, shift(num1, j)); 
        }
    }
    return result;
}

std::vector<int> shift(std::vector<int> num, int n)
{
    std::vector<int> res(32, 0);

    for (int i = num.size() - 1; i >= 0; i--)
    {
        if(i - n >= 0) {
            res[i - n] = num[i];
        }
    }
    return res;
}

std::vector<int> toBCD(int num) {
    std::vector<int> result(32, 0);
    int shiftIndex = 0;
    while(num > 9) {
        int number = num % 10;
        num /= 10;
        std::vector<int> numberBinary = signMagnitude(number);
        result = sum(result, shift(numberBinary, shiftIndex * 4));
        shiftIndex++;
    }
    std::vector<int> numberBinary = signMagnitude(num);
    result = sum(result, shift(numberBinary, shiftIndex * 4));
    return result;
}

std::vector<int> minusTen(std::vector<int> num1) 
{
    std::vector<int> tempResult(5, 0);
    std::vector<int> result(4, 0);
    std::vector<int> num2Negative = {0, 1, 1, 0};
    tempResult = sum(num1, num2Negative);
    for(int i = 3; i >= 0; i--) {
        result[i] = tempResult[i + 1];
    }
    return result;
}

std::vector<int> sumBCD(std::vector<int> num1, std::vector<int> num2) {
    std::vector<int> result(32, 0);
    int carry = 0;

    for(int i = num1.size()- 1; i >= 0; i -= 4) {
        std::vector<int> tetrada1(5, 0);
        std::vector<int> tetrada2(5, 0);
        for(int g = 4; g >= 1; g--) {
            tetrada1[g] = num1.back();
            num1.pop_back();
            tetrada2[g] = num2.back();
            num2.pop_back();
        }
        std::vector<int> carryBinary = signMagnitude(carry);
        std::vector<int> newCarryBinary(5, 0);
        for(int g = carryBinary.size() - 1, j = 4; j >= 0; j--, g--) {
            newCarryBinary[j] = carryBinary[g];
        }
        carryBinary = newCarryBinary;
        std::vector<int> tempRes = sum(sum(tetrada1, carryBinary), tetrada2);
        if(tempRes[0] == 1) {
            carry += 1;
        } else {
            if(carry == 2) {
                carry -= 1;
            } else {
                carry = 0;
            }
            
        }
        
        std::vector<int> tempFourth(4, 0);
        for(int g = 3; g >= 0; g--) {
            tempFourth[g] = tempRes[g + 1];
        }
        tempRes = tempFourth;
        if(tempRes[0] && (tempRes[1] || tempRes[2])) {
            tempRes = minusTen(tempRes);
            carry += 1;
        }
        for(int g = i, h = 3; h >= 0; g--, h--) {
            result[g] = tempRes[h];
        }
    }

    return result;
}

std::vector<int> subtract(std::vector<int> num1, std::vector<int> num2) {
    std::vector<int> res(32, 0);
    int carry = 0;
    for (int i = 31; i >= 0; i--) {
        int sub = num1[i] - num2[i] - carry;
        if (sub < 0) {
            sub += 2;
            carry = 1;
        } else {
            carry = 0;
        }
        res[i] = sub;
    }
    return res;
}

int compareAbs(const std::vector<int>& num1, const std::vector<int>& num2) {
    for (int i = 0; i < 32; i++) {
        if (num1[i] > num2[i]) return 1;
        if (num1[i] < num2[i]) return 0;
    }
    return 1;
}

std::vector<int> getNegativeCode(std::vector<int> num) {
    std::vector<int> res(32, 0);
    for (int i = 0; i < 32; i++) {
        res[i] = (num[i] == 0) ? 1 : 0; 
    }
    std::vector<int> one(32, 0);
    one[31] = 1;
    return sum(res, one); 
}

void binaryDivision(int number1, int number2) {
    if (number2 == 0) {
        std::cout << "Ошибка: деление на ноль!" << std::endl;
        return;
    }

    std::vector<int> dividentVec = signMagnitude(number1);
    std::vector<int> divisorVec = signMagnitude(number2);

    std::vector<int> negDivisorVec = getNegativeCode(divisorVec);

    std::vector<int> quotient(32, 0);
    std::vector<int> remainder(32, 0);

    for (int i = 0; i < 32; i++) {
        remainder = shift(remainder, 1);
        remainder[31] = dividentVec[i];

        std::vector<int> diff = sum(remainder, negDivisorVec);

        if (diff[0] == 0) {
            remainder = diff;
            quotient[i] = 1;
        } else {
            quotient[i] = 0;
        }
    }

    std::cout << "Целая часть: ";
    printVector(quotient);
    std::cout << std::endl;
    
    std::cout << "Остаток : ";
    printVector(remainder);
    std::cout << std::endl;
}


std::vector<int> floatToIEEE754(double value) {
    std::vector<int> bits(32, 0);

    if (value == 0.0) {
        return bits;
    }
    if (std::isnan(value)) {
        bits[0] = 0;
        bits[1] = 1; bits[2] = 1; bits[3] = 1; bits[4] = 1;
        bits[5] = 1; bits[6] = 1; bits[7] = 1; bits[8] = 1; 
        bits[9] = 1;
        return bits;
    }
    if (std::isinf(value)) {
        bits[0] = (value < 0) ? 1 : 0;
        for (int i = 1; i <= 8; ++i) bits[i] = 1;
        return bits;
    }

    bool negative = (value < 0);
    if (negative) {
        value = -value;
    }
    bits[0] = negative ? 1 : 0;

    int exponent = 0;
    double mant = value;

    while (mant >= 2.0) {
        mant /= 2.0;
        exponent++;
    }
    while (mant < 1.0 && mant > 0.0) {
        mant *= 2.0;
        exponent--;
    }

    int biased_exp = exponent + 127;

    if (biased_exp >= 255) {
        for (int i = 1; i <= 8; ++i) {
            bits[i] = 1;
        }
        return bits;
    }
    if (biased_exp <= 0) {
        return bits;
    }

    for (int i = 0; i < 8; ++i) {
        bits[1 + i] = (biased_exp >> (7 - i)) & 1;
    }

    mant -= 1.0;

    for (int i = 0; i < 23; ++i) {
        mant *= 2.0;
        bits[9 + i] = (mant >= 1.0) ? 1 : 0;
        if (mant >= 1.0) {
            mant -= 1.0;
        }
    }

    return bits;
}

double IEEE754ToFloat(const std::vector<int>& bits) {
    if (bits.size() != 32) return 0.0;

    bool sign = bits[0];

    int biased_exp = 0;
    for (int i = 0; i < 8; ++i) {
        biased_exp = (biased_exp << 1) | bits[1 + i];
    }
    int exponent = biased_exp - 127;

    if (biased_exp == 0) {
        return 0.0;
    }
    if (biased_exp == 255) {
        bool mantissa_zero = true;
        for (int i = 9; i < 32; ++i) {
            if (bits[i] != 0) {
                mantissa_zero = false;
                break;
            }
        }
        if (mantissa_zero) {
            return INFINITY;
        } else {
            return NAN;
        }
    }

    double mantissa = 1.0;
    for (int i = 0; i < 23; ++i) {
        if (bits[9 + i]) {
            mantissa += std::pow(2.0, -(i + 1));
        }
    }

    double value = mantissa * std::pow(2.0, exponent);
    return sign ? -value : value;
}

std::vector<int> floatAddIEEE(const std::vector<int>& a, const std::vector<int>& b, bool isSub = false)
{
    if (a.size() != 32 || b.size() != 32) {
        return std::vector<int>(32, 0);
    }

    bool signA = a[0];
    bool signB = b[0];
    if (isSub) {
        signB = !signB;
    }

    bool effectiveSub = (signA != signB);

    int expA = 0, expB = 0;
    for (int i = 0; i < 8; ++i) {
        expA = (expA << 1) | a[1 + i];
        expB = (expB << 1) | b[1 + i];
    }

    if (expA == 255 || expB == 255) {
        std::vector<int> res(32, 0);
        res[0] = signA ^ signB;
        for (int i = 1; i <= 8; ++i) {
            res[i] = 1;
        }
        if (res[0] == 0) {
            res[9] = 1; 
        }
        return res;
    }

    std::vector<int> mantA(24, 0);
    std::vector<int> mantB(24, 0);
    mantA[0] = (expA != 0) ? 1 : 0;  
    mantB[0] = (expB != 0) ? 1 : 0;

    for (int i = 0; i < 23; ++i) {
        mantA[1 + i] = a[9 + i];
        mantB[1 + i] = b[9 + i];
    }

    int shift = expA - expB;
    if (shift > 0) {
        for (int i = 23; i >= shift; --i) {
            mantB[i] = mantB[i - shift];
        }
        for (int i = 0; i < shift; ++i) mantB[i] = 0;
        expB = expA;
    } else if (shift < 0) {
        int rshift = -shift;
        for (int i = 23; i >= rshift; --i) {
            mantA[i] = mantA[i - rshift];
        }
        for (int i = 0; i < rshift; ++i) {
            mantA[i] = 0;
        }
        expA = expB;
    }

    std::vector<int> sum(25, 0);
    int c = effectiveSub ? 1 : 0;

    for (int i = 24; i >= 0; --i) {
        int ba = mantA[i];
        int bb = mantB[i];

        if (effectiveSub) {
            bb = 1 - bb;
        }

        int s = ba + bb + c;
        sum[i] = s & 1;
        c = s >> 1;
    }

    int exponent = expA;  

    if (c && !effectiveSub) {
        for (int i = 24; i >= 1; --i) {
            sum[i] = sum[i-1];
        }
        sum[0] = 1;
        exponent++;
    }

    bool resultNegative = false;

    if (effectiveSub) {
        if (c == 0) {
            resultNegative = true;
            c = 1;
            for (int i = 24; i >= 0; --i) {
                int inv = 1 - sum[i];
                int s = inv + c;
                sum[i] = s & 1;
                c = s >> 1;
            }
        }
    } else {
        resultNegative = signA;
    }

    int lead = -1;
    for (int i = 0; i < 25; ++i) {
        if (sum[i]) {
            lead = i;
            break;
        }
    }

    if (lead == -1) {
        return std::vector<int>(32, 0);
    }

    exponent -= lead;

    std::vector<int> result(32, 0);
    result[0] = resultNegative ? 1 : 0;

    if (exponent >= 255) {
        exponent = 255;
    } else if (exponent <= 0) {
        exponent = 0;
    }

    for (int i = 0; i < 8; ++i) {
        result[1 + i] = (exponent >> (7 - i)) & 1;
    }

    for (int i = 0; i < 23; ++i) {
        int pos = lead + 1 + i;
        result[9 + i] = (pos < 25) ? sum[pos] : 0;
    }

    return result;
}


std::vector<int> floatMultiplyIEEE(const std::vector<int>& a, const std::vector<int>& b)
{
    if (a.size() != 32 || b.size() != 32) {
        return std::vector<int>(32, 0);
    }

    bool sign = a[0] ^ b[0];

    int expA = 0, expB = 0;
    for (int i = 0; i < 8; ++i) {
        expA = (expA << 1) | a[1 + i];
        expB = (expB << 1) | b[1 + i];
    }

    if (expA == 255 || expB == 255) {
        bool isNaN = (expA == 255 && expB == 0) || (expA == 0 && expB == 255);
        std::vector<int> res(32, 0);
        res[0] = sign;
        for (int i = 1; i <= 8; ++i) {
            res[i] = 1;
        }
        if (isNaN) {
            res[9] = 1; 
        }
        return res;
    }
    if (expA == 0 || expB == 0) {
        return std::vector<int>(32, 0);
    }

    unsigned long long mantA = 1ULL << 23;
    unsigned long long mantB = 1ULL << 23;
    for (int i = 0; i < 23; ++i) {
        if (a[9 + i]) mantA |= (1ULL << (22 - i));
        if (b[9 + i]) mantB |= (1ULL << (22 - i));
    }

    unsigned long long product = mantA * mantB;

    int exponent = (expA - 127) + (expB - 127) + 127;

    int shift = 0;
    if (product & (1ULL << 47)) {
        shift = 24;
    } else if (product & (1ULL << 46)) {
        shift = 23;
    } else {
        return std::vector<int>(32, 0);
    }

    unsigned long long shifted = product >> (shift - 1);
    unsigned long long mantResult = (shifted >> 1) & ((1ULL << 23) - 1);

    bool roundUp = (shifted & 1) != 0;
    if (roundUp) {
        mantResult += 1;
        if (mantResult >= (1ULL << 23)) {
            mantResult >>= 1;
            exponent += 1;
        }
    }

    exponent += (shift - 23);

    std::vector<int> result(32, 0);
    result[0] = sign ? 1 : 0;

    if (exponent >= 255) {
        exponent = 255;
    } else if (exponent <= 0) {
        exponent = 0;
    }

    for (int i = 0; i < 8; ++i) {
        result[1 + i] = (exponent >> (7 - i)) & 1;
    }

    for (int i = 0; i < 23; ++i) {
        result[9 + i] = (mantResult >> (22 - i)) & 1;
    }

    return result;
}


std::vector<int> floatDivideIEEE(const std::vector<int>& num, const std::vector<int>& den)
{
    if (num.size() != 32 || den.size() != 32) {
        return std::vector<int>(32, 0);
    }

    bool sign = num[0] ^ den[0];

    int expN = 0, expD = 0;
    for (int i = 0; i < 8; ++i) {
        expN = (expN << 1) | num[1 + i];
        expD = (expD << 1) | den[1 + i];
    }

    if (expD == 255 || expD == 0 || expN == 255 || expN == 0) {
        std::vector<int> res(32, 0);
        res[0] = sign ? 1 : 0;

        if (expD == 0) {
            for (int i = 1; i <= 8; ++i) res[i] = 1;
        } else if (expN == 255 && expD != 255) {
            for (int i = 1; i <= 8; ++i) res[i] = 1;
        } else if (expN == 0) { 
        } else if (expN == 255 && expD == 255) {
            for (int i = 1; i <= 8; ++i) res[i] = 1;
            res[9] = 1;
        }
        return res;
    }

    unsigned long long mantN = 1ULL << 23;
    unsigned long long mantD = 1ULL << 23;
    for (int i = 0; i < 23; ++i) {
        mantN |= static_cast<unsigned long long>(num[9 + i]) << (22 - i);
        mantD |= static_cast<unsigned long long>(den[9 + i]) << (22 - i);
    }

    int exponent = expN - expD + 127;

    unsigned long long scaled = mantN << 25;
    unsigned long long quot = scaled / mantD;

    if (quot == 0) {
        return std::vector<int>(32, 0);
    }

    bool guard = false;
    if (quot >= (1ULL << 25)) {
        guard = (quot & 2) != 0;
        quot >>= 2;
    } else {
        guard = (quot & 1) != 0;
        quot >>= 1;
        exponent--;
    }

    if (guard) {
        quot++;
        if (quot >= (1ULL << 24)) {
            quot >>= 1;
            exponent++;
        }
    }

    if (exponent >= 255) {
        exponent = 255;
        quot = 0;
    }
    if (exponent <= 0) {
        exponent = 0;
        quot = 0;
    }

    std::vector<int> result(32, 0);
    result[0] = sign ? 1 : 0;

    for (int i = 0; i < 8; ++i) {
        result[1 + i] = (exponent >> (7 - i)) & 1;
    }

    for (int i = 0; i < 23; ++i) {
        result[9 + i] = (quot >> (22 - i)) & 1;
    }

    return result;
}

int bcdToInt(const std::vector<int>& vec) {
    int result = 0;
    int multiplier = 1;

    for (int i = vec.size() - 4; i >= 0; i -= 4) {
        int digit = 0;
        int powerOfTwo = 1;

        for (int j = 3; j >= 0; j--) {
            if (vec[i + j] == 1) {
                digit += powerOfTwo;
            }
            powerOfTwo *= 2;
        }

        result += digit * multiplier;
        multiplier *= 10;
    }

    return result;
}

bool getInt(int& value) {
    std::cin >> value;
    
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    char nextChar;
    if (std::cin.get(nextChar) && nextChar != '\n') {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    
    return true;
}

bool getDouble(double& value) {
    std::cin >> value;
    
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    char nextChar;
    if (std::cin.get(nextChar) && nextChar != '\n') {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    
    return true;
}