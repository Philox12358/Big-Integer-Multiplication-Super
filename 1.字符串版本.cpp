#include<iostream>
#include<deque>
#include<sstream>
#include <stdlib.h>
#include <time.h>
#include<stdlib.h>

using namespace std;     //ʹ�������ռ�

string ordinaryNMTP(const string s1, const string s2) {
    string res = "";//���շ��ص��ַ���
    int num = 0;
    deque <int> vec(s1.size() + s2.size() - 1, 0); //ʹ��deque����Ϊ���ֽ�λʱ�����ڶ���ǰ�������ݣ�Ч�ʱ�vector�ߣ���С��Ϊ��С
    //int nums[ s1.size() ];
    for (int i = 0; i < s1.size(); ++i) {
        for (int j = 0; j < s2.size(); ++j) {
            vec[i + j] += (s1[i] - '0') * (s2[j] - '0');//�˷�
        }
    }
    //��ʽ��10����
    int addflag = 0;//��λ���
    for (int i = vec.size() - 1; i >= 0; --i) {
        int temp = vec[i] + addflag;
        vec[i] = temp % 10;
        addflag = temp / 10;
    }
    if (addflag != 0)  vec.push_front(addflag);     //�ж��Ƿ������λ��
    //����ת�����ַ���
    for (auto elem : vec) {
        ostringstream ss;
        ss << elem;
        res = res + ss.str();
    }
    return res;
}

//����������ĺ���
string generate(int len) {
    srand((unsigned int)time(0));
    string str = "";
    for (int i = 0; i < len; ++i) {
        ostringstream SS;
        SS << rand() % 10;
        str = str + SS.str();
    }
    //str[++i] = '\0';
    return str;
}



int main() {
    int len;
    cout << "��������Ҫ����������λ��С��" << endl;
    cin >> len;
    string str1, str2;                 //����Ĭ��Ϊ�յ��ַ���

    double duration;
    str1 = generate(len);                   //����������ַ���
    str2 = generate(len);
    cout << str1 << "\n*\n" << str2 << "\n=\n" << endl;
    clock_t start, end;                  //��ʱ��ʼ
    start = clock();
    cout << ordinaryNMTP(str1, str2) << endl;
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;    //�����ʱ��
    cout << duration << "s" << endl;
    system("pause");

    /*
    while (std::cin >> str1 >> str2)                //ѭ������
    {
        cout << str1 << "*" << str2 << "=" << endl;
        cout << ordinaryNMTP(str1, str2) << endl;
    }*/

    return 0;
}