#include<stdlib.h>
#include<stdio.h>
#include<sstream>
#include<iostream>
#include<vector>
#include<time.h>
#include<windows.h>

using namespace std;
#define ll long long
const int maxn = 5e7 + 5;
const int maxm = 5e7 + 5;
char s1[maxn], s2[maxn];
const double PI = acos(-1);

//�����ṹ��
struct Complex {
    double x, y;
    Complex(double _x = 0, double _y = 0) :x(_x), y(_y) {}
    Complex operator -(const Complex& b)const {
        return Complex(x - b.x, y - b.y);
    }
    Complex operator +(const Complex& b)const {
        return Complex(x + b.x, y + b.y);
    }
    Complex operator *(const Complex& b)const {
        return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
    }
};
Complex com1[maxm], com2[maxm]; // ����X1��X2

//��λ�㷨
void change(Complex y[], int len) {
    for (int i = 1, j = len / 2; i < len - 1; i++) {
        if (i < j) swap(y[i], y[j]);
        int k = len / 2;
        while (j >= k) {
            j -= k;
            k /= 2;
        }
        if (j < k) j += k;
    }
}

// FFT�㷨
void FFT(Complex y[], int len, int on) {
    change(y, len);
    for (int h = 2; h <= len; h <<= 1) {
        Complex wn(cos(-on * 2 * PI / h), sin(-on * 2 * PI / h));
        for (int j = 0; j < len; j += h) {
            Complex w(1, 0);
            for (int k = j; k < j + h / 2; k++) {
                Complex u = y[k];
                Complex t = w * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u - t;
                w = w * wn;
            }
        }
    }
    if (on == -1) { for (int i = 0; i < len; i++)   y[i].x /= len; }
}

//��������ɺ���
int generate(vector<int>& vec, int len) {
    srand((unsigned long)time(NULL));
    cout << "\n\n��������������£�" << endl;
    Sleep(1000);
    vec[0] = rand() % 9;//��һλ��Ϊ0
    vec[0]++;
    printf("%d", vec[0]);
    for (int i = 1; i <len; ++i) {
        vec[i] = rand() % 10;
        printf("%d", vec[i]);
    }
    return 0;
}

int main() {
    int len;
    while (true) {
        cout << "������λ����" << endl;
        cin >> len;
        vector<int> vec1(len, 0);
        vector<int> vec2(len, 0);
        generate(vec1, len);//���������1
        generate(vec2, len);//���������2
        cout << "\n\n��Ϊ��" << endl;

        int len1 = vec1.size();
        int len2 = vec2.size();
        memset(com1, 0, sizeof(com1));
        memset(com2, 0, sizeof(com2));
        int rlen = 1;
        while (rlen < (len1 + len2 - 1)) rlen <<= 1;//ǿ�����䵽2��n����

        clock_t start = clock();//��ʱ��ʼ

        for (int i = 0; i < len1; i++) com1[i] = Complex((double)(vec1[i]), 0);
        for (int i = len1; i < rlen; i++) com1[i] = Complex(0, 0);
        for (int i = 0; i < len2; i++) com2[i] = Complex((double)(vec2[i]), 0);
        for (int i = len2; i < rlen; i++) com2[i] = Complex(0, 0);

        FFT(com1, rlen, 1);//����ʽת���ɵ�ֵ���ʽ�����ٸ���Ҷ�任FFT��
        FFT(com2, rlen, 1);
        for (int i = 0; i < rlen; i++) com1[i] = com1[i] * com2[i];//��ֵ�˷�
        FFT(com1, rlen, -1);//�������տ��ٲ�ֵ��

        vector<int> res(len1 + len2 - 1, 0);//���������

        for (int i = len1 + len2 - 2; i >= 0; i--) {//�𰸱任
            res[i] += (int)(com1[i].x + 0.5);
            if (i != 0) {
                res[i - 1] += res[i] / 10;
                res[i] %= 10;
            }
            else {
                int temp = res[0] / 10;
                if (temp != 0) {
                    res[0] %= 10;
                    res.insert(res.begin(), temp);
                }
            }
        }
        int pos = 0;
        for (int i = 0; i < len1 + len2 - 1; i++) {
            pos = i;
            if (res[i] != 0) break;
        }
        start = clock() - start;//��ʱ����
        for (int i = pos; i < res.size(); i++) {
            printf("%d", res[i]);
        }
        printf("\n");
        memset(s1, '\0', sizeof(s1));
        memset(s2, '\0', sizeof(s2));

        cout << "\n�˷���ʱ: " << (double)(start)/CLOCKS_PER_SEC << " s\n\n" << endl;//����˷�ʱ��
    }
    return 0;
}
