#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculate.h"
#include "ui.h"

//��Һ� �Լ�
//rData�� �� ũ�� -1, lData�� �� ũ�� 1, ������ 0
int getCompare(const char* lData, const char* rData) {
    int len1 = strlen(lData);
    int len2 = strlen(rData);

    //���ڿ� ���̷� ��
    if (len1 > len2) {
        return 1;
    }
    else if (len1 < len2) {
        return -1;
    }

    //���ڿ� ���̰� ������ �� ����� ���� �ϳ��� ��
    //��Һ񱳰� �����̹Ƿ� ���� ��ȯ X
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

//���� �Լ�
char* getAdd(const char* lData, const char* rData) {
    int len1 = strlen(lData);
    int len2 = strlen(rData);
    int maxLen = (len1 > len2) ? len1 : len2;

    char* result = (char*)calloc(maxLen + 2, sizeof(char)); // ��, �ڸ��ø� ���

    result[maxLen + 1] = '\0';

    int sum, carry = 0;

    for (int i = 0; i < maxLen; ++i) {
        int ltmp = 0, rtmp = 0;

        //���ڹ迭 ��ҵ��� ������ ��ȯ�Ͽ� �ϳ��� ���
        //�������ڸ��� �� ���� ���� ����ϱ� ���� -1
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

    //���� �ڸ��ø��� �ִ� ���
    if (carry == 1) {
        result[0] = '1';
    }
    else {
        result[0] = '0';
    }

    return result;
}


//���� �Լ�
char* getSubstract(const char* lData, const char* rData) {
    int len1 = strlen(lData);
    int len2 = strlen(rData);
    int maxLen = (len1 > len2) ? len1 : len2;

    char* result = (char*)malloc(maxLen + 2);   //��, ��ȣ ���

    result[maxLen + 1] = '\0';

    int diff, carry = 0;

    //��� ���Ͽ� ������ ��츦 ���
    switch (getCompare(lData, rData)) {
    case 1:
        result[0] = '+';
        break;
    //��� ���� ������ ���
    case -1: {
        for (int i = 0; i < maxLen; ++i) {
            int ltmp = 0, rtmp = 0;
            
            //rData - lData�� �ǵ��� ���� ����
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

    //����� ������ �ƴѰ��
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