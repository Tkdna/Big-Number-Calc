#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculate.h"
#include "ui.h"

//대소비교 함수
//rData가 더 크면 -1, lData가 더 크면 1, 같으면 0
int getCompare(const char* lData, const char* rData) {
    int len1 = strlen(lData);
    int len2 = strlen(rData);

    //문자열 길이로 비교
    if (len1 > len2) {
        return 1;
    }
    else if (len1 < len2) {
        return -1;
    }

    //문자열 길이가 같으면 각 요소의 숫자 하나씩 비교
    //대소비교가 목적이므로 정수 변환 X
    for (int i = 0; i < len1; ++i) {
        if (lData[i] > rData[i]) {
            return 1;
        }
        else if (lData[i] < rData[i]) {
            return -1;
        }
    }
    return 0;
}

//덧셈 함수
char* getAdd(const char* lData, const char* rData) {
    int len1 = strlen(lData);
    int len2 = strlen(rData);
    int maxLen = (len1 > len2) ? len1 : len2;

    char* result = (char*)calloc(maxLen + 2, sizeof(char)); // 널, 자리올림 고려

    result[maxLen + 1] = '\0';

    int sum, carry = 0;

    for (int i = 0; i < maxLen; ++i) {
        int ltmp = 0, rtmp = 0;

        //문자배열 요소들을 정수로 변환하여 하나씩 계산
        //마지막자리의 널 이후 부터 계산하기 위해 -1
        if (len1 - 1 - i >= 0) {
            ltmp = lData[len1 - 1 - i] - '0';
        }
        if (len2 - 1 - i >= 0) {
            rtmp = rData[len2 - 1 - i] - '0';
        }

        sum = ltmp + rtmp + carry;
        if (sum >= 10) {
            carry = 1;
            result[maxLen - i] = (sum - 10) + '0';
        }
        else {
            carry = 0;
            result[maxLen - i] = sum + '0';
        }
    }

    //최종 자리올림이 있는 경우
    if (carry == 1) {
        result[0] = '1';
    }
    else {
        result[0] = '0';
    }

    return result;
}


//뺄셈 함수
char* getSubstract(const char* lData, const char* rData) {
    int len1 = strlen(lData);
    int len2 = strlen(rData);
    int maxLen = (len1 > len2) ? len1 : len2;

    char* result = (char*)malloc(maxLen + 2);   //널, 부호 고려

    result[maxLen + 1] = '\0';

    int diff, carry = 0;

    //대소 비교하여 음수일 경우를 고려
    switch (getCompare(lData, rData)) {
    case 1:
        result[0] = '+';
        break;
    //결과 값이 음수인 경우
    case -1: {
        for (int i = 0; i < maxLen; ++i) {
            int ltmp = 0, rtmp = 0;
            
            //rData - lData가 되도록 로직 변경
            if (len2 - 1 - i >= 0) {
                ltmp = rData[len2 - 1 - i] - '0' - carry;
            }
            if (len1 - 1 - i >= 0) {
                rtmp = lData[len1 - 1 - i] - '0';
            }
            
            if (ltmp < rtmp) {
                int tmp = 10 - rtmp;
                diff = ltmp + tmp;
                result[maxLen - i] = diff + '0';
                carry = 1;
            }
            else {
                diff = ltmp - rtmp;
                result[maxLen - i] = diff + '0';
                carry = 0;
            }
        }
        result[0] = '-';
        return result;
    }
    case 0:
        break;
    }

    //결과가 음수가 아닌경우
    for (int i = 0; i < maxLen; ++i) {
        int ltmp = 0, rtmp = 0;
        
        if (len1 - 1 - i >= 0) {
            ltmp = lData[len1 - 1 - i] - '0' - carry;
        }
        if (len2 - 1 - i >= 0) {
            rtmp = rData[len2 - 1 - i] - '0';
        }

        if (ltmp < rtmp) {
            int tmp = 10 - rtmp;
            diff = ltmp + tmp;
            result[maxLen - i] = diff + '0';
            carry = 1;
        }
        else {
            diff = ltmp - rtmp;
            result[maxLen - i] = diff + '0';
            carry = 0;
        }
    }

    return result;
}