#include<iostream>
#include<sstream>
#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<time.h>
#include<windows.h>

using namespace std;
long long test_size = 64;//128��һ���ȽϺ��ʵ�ֵ

//������ȷ��
long long check(const vector< long long>& vec1, const vector<long long>& vec2) {
	long long len = vec1.size();
	for (long long i = 0; i < len; ++i) {
		if (vec1[i] != vec2[i]) {
			cout << "������󣡣���" << endl;
			return 0;
		}
	}
	cout << "�����ȷ��������~~~" << endl;
	return 0;
}

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

//�м��˷�
vector<long long> betterNMTP(const vector<long long>& x, const vector<long long>& y, long long len) {
	if (len <= test_size) return ordinaryNMTP(x, y, len);
	long long k = len / 2;

	if (2 * k == len) { // ż��
		vector<long long> res(2 * len, 0);

		vector<long long> XA{ x.begin(), x.begin() + k };//����A��D��C��D
		vector<long long> XB{ x.begin() + k, x.end() };
		vector<long long> YC{ y.begin(), y.begin() + k };
		vector<long long> YD{ y.begin() + k, y.end() };

		vector<long long> AC = betterNMTP(XA, YC, k);//ACǰͷ���㣡�������������������������ݹ�
		vector<long long> BD = betterNMTP(XB, YD, k);//BDβ�ͼ��㣡�������������������������ݹ�

		vector<long long> XA_B(k);
		vector<long long> YD_C(k);

		for (long long i = k - 1; i >= 0; --i) {//���㣨A+B���ͣ�D+C��
			XA_B[i] = XA[i] + XB[i];
			YD_C[i] = YD[i] + YC[i];
		}

		vector<long long> A_B_D_C = betterNMTP(XA_B, YD_C, k);  //(A+B)(D+C)���������������������������ݹ�	

		for (long long i = 0; i < len; ++i) {
			A_B_D_C[i] -= (AC[i] + BD[i]);//��(A+B)(D+C)-AC-BD��
		}
		for (long long i = 0; i < len; ++i) {
			res[i] = AC[i];//ͷͷ��AC
		}
		for (long long i = len; i < 2 * len; ++i) {
			res[i] = BD[i - len];//ĩβ��BD
		}
		for (long long i = k; i < len + k; ++i) {
			res[i] += A_B_D_C[i - k];//�м���м�
		}
		return res;
	}
	else { // ����
		k++; // k��1
		len++; // len��1
		vector<long long> res(2 * len, 0);

		vector<long long> vec1 = x;
		vector<long long> vec2 = y;
		vec1.push_back(0);
		vec2.push_back(0);//���һλ��0

		vector<long long> XA{ vec1.begin(), vec1.begin() + k };//����A��D��C��D
		vector<long long> XB{ vec1.begin() + k, vec1.end() };
		vector<long long> YC{ vec2.begin(), vec2.begin() + k };
		vector<long long> YD{ vec2.begin() + k, vec2.end() };

		vector<long long> AC = betterNMTP(XA, YC, k);//ACǰͷ���㣡�������������������������ݹ�
		vector<long long> BD = betterNMTP(XB, YD, k);//BDβ�ͼ��㣡�������������������������ݹ�

		vector<long long> XA_B(k);
		vector<long long> YD_C(k);

		for (long long i = k - 1; i >= 0; --i) {//���㣨A+B���ͣ�D+C��
			XA_B[i] = XA[i] + XB[i];
			YD_C[i] = YD[i] + YC[i];
		}

		vector<long long> A_B_D_C = betterNMTP(XA_B, YD_C, k);  //(A+B)(D+C)���������������������������ݹ�	

		for (long long i = 0; i < len; ++i) {
			A_B_D_C[i] -= (AC[i] + BD[i]);//��(A+B)(D+C)-AC-BD��
		}
		for (long long i = 0; i < len; ++i) {
			res[i] = AC[i];//ͷͷ��AC
		}
		for (long long i = len; i < 2 * len; ++i) {
			res[i] = BD[i - len];//ĩβ��BD
		}
		for (long long i = k; i < len + k; ++i) {
			res[i] += A_B_D_C[i - k];//�м���м�
		}
		res.pop_back();
		res.pop_back();
		return res;
	}
}

//��������ɺ���
int generate(vector<long long>& vec, long long len) {
	srand((unsigned long)time(NULL));
	cout << "\n\n��������������£�" << endl;
	Sleep(1000);
	vec[len - 1] = rand() % 9;//��һλ��Ϊ0
	vec[len - 1]++;
	cout << vec[len - 1];
	for (int i = len - 2; i >= 0; --i) {
		vec[i] = rand() % 10;
		cout << vec[i];
	}
	return 0;
}

//������
int main() {
	long long len = 0;
	double duration1 = 0;
	double duration2 = 0;
	cout << "������λ����" << endl;
	cin >> len;
	vector<long long> vec1(len, 0);
	vector<long long> vec2(len, 0);
	vector<long long> res1(2 * len, 0);
	vector<long long> res2(2 * len, 0);

	generate(vec1, len);//���������1
	generate(vec2, len);//���������2
	clock_t start, end;


	cout << "\n\n���γ˷������" << endl;
	start = clock();//��ʼ��ʱ
	res1 = betterNMTP(vec1, vec2, len);
	end = clock();//������ʱ
	stand(res1);//��׼��
	printout(res1, 2 * len);//���
	duration1 = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "\n���γ˷���ʱ: " << duration1 << " s" << endl;//����˷�ʱ��


	cout << "\n��ͨ�˷������" << endl;
	start = clock();//��ʼ��ʱ
	res2 = ordinaryNMTP(vec1, vec2, len);
	end = clock();//������ʱ
	stand(res2);
	printout(res2, 2 * len);
	duration2 = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "\n��ͨ�˷���ʱ: " << duration2 << " s" << endl;//����˷�ʱ��


	cout << "\n������ʱ��" << duration1 << " s" << endl;
	cout << "��ͨ��ʱ��" << duration2 << " s\n" << endl;

	check(res1, res2);
	system("pause");
	return 0;
}