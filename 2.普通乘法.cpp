#include<iostream>
#include<sstream>
#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<time.h>
#include<windows.h>

using namespace std;
int testnum = 1;//���Դ���

//�������ֵ����
void printout(const std::vector<long long>& res, long long len) {
	long long i = len - 1;
	while (res[i] == 0) --i;
	for (i; i >= 0; --i) {
		cout << res[i];
	}
}

//��׼��10���ƺ���
void stand(vector<long long>& vec) {
	long long len = vec.size();
	long long addflag = 0;//��λ���
	long long temp = 0;
	for (long long i = 0; i < len; ++i) {
		temp = vec[i] + addflag;
		while (temp < 0 && i + 1 < len) {
			temp += 10;
			vec[i + 1]--;
		}
		vec[i] = temp % 10;
		addflag = temp / 10;
	}
}

//��ͨ�˷�111111
vector<long long>  ordinaryNMTP(const vector< long long>& vec1, const vector<long long>& vec2, long long len) {
	vector<long long> vec(len * 2);
	for (int i = len - 1; i >= 0; i--) {
		if (vec1[i] == 0) continue; // 0����
		for (int j = len - 1; j >= 0; j--) {
			vec[i + j] += vec1[i] * vec2[j];
		}
	}
	return vec;
}

//��������ɺ���
int generate(vector<long long>& vec, long long len) {
	srand((unsigned long)time(NULL));
	cout << "\n\n��������������£�" << endl;
	Sleep(1000);
	vec[len - 1] = rand() % 9; // ��һλ��Ϊ0
	vec[len - 1]++;
	cout << vec[len - 1];
	for (int i = len - 2; i >= 0; --i) {
		vec[i] = rand() % 10;
		cout << vec[i];
	}
	return 0;
}

int agent(long long len) {
	
	double duration;
	
	vector<long long> vec1(len);
	vector<long long> vec2(len);
	vector<long long> res(2 * len);
	generate(vec1, len);//���������1
	generate(vec2, len);//���������2
	clock_t start, end;    
	start = clock();//��ʼ��ʱ
	
	res = ordinaryNMTP(vec1, vec2, len);

	end = clock();//������ʱ
	stand(res);   //��׼��
	printout(res,2*len);//���
	duration = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "\n�˷���ʱ:" << duration << "S" << endl;//����˷���ʱ
	
	return 0;
}


int main() {
	long long len;
	while (true) {
		cout << "������λ����" << endl;
		cin >> len;
		agent(len);
	}
	return 0;
}