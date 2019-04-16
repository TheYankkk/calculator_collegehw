#include "stdafx.h"
#include<iostream>
#include<cstring>
#include<stack>
#include<cmath>

using namespace std;

char n[6666];
int g_pos;

double trans(int &pos) {
	double zhengshu = 0.0;
	double remainder = 0.0;
	while (n[pos] >= '0'&&n[pos] <= '9')
	{
		zhengshu = zhengshu * 10;
		zhengshu += (n[pos] - '0');
		pos++;
	}

	if (n[pos] == '.') {
		pos++;
		int c = 1;
		while (n[pos] >= '0'&&n[pos] <= '9') {
			double t = n[pos] - '0';
			t = t * pow(0.1, c);
			c++;
			remainder += t;
			pos++;
		}
	}
	return zhengshu + remainder;
}

int level(char ch) {
	switch (ch)
	{
	case'+':
	case'-':
		return 1;
	case'*':
	case'/':
		return 2;
	case'^':
		return 3;
	case'(':
		return 0;
	case'#':
		return -1;
	};
}

double operate(double a, char op, double b) {
	switch (op) {
	case'+':
		return a + b;
	case'-':
		return a - b;
	case'*':
		return a * b;
	case'/':
		return a / b;
	case'^':
		return pow(a, b);
	}
}

double compute() {
	stack<char>ope;
	stack<double>num;

	ope.push('#');
	int len = strlen(n);
	bool is_minus = true;

	for (g_pos = 0; g_pos < len;) {
		if (n[g_pos] == '-'&&is_minus)//负号
		{
			num.push(0);
			ope.push('-');
			g_pos++;
		}
		else if (n[g_pos] == '(') {
			is_minus = true;
			ope.push(n[g_pos]);
			g_pos++;
		}
		else if (n[g_pos] == ')') {
			is_minus = false;
			g_pos++;
			while (ope.top() != '(')
			{
				double b = num.top();
				num.pop();
				double a = num.top();
				num.pop();
				char op = ope.top();
				ope.pop();
				double result = operate(a, op, b);
				num.push(result);
			}
			ope.pop();
		}
		else if (n[g_pos] >= '0'&&n[g_pos] <= '9') {//数字
			is_minus = false;
			num.push(trans(g_pos));
		}
		else
		{
			while (level(n[g_pos]) <= level(ope.top())) {
				double b = num.top();
				num.pop();
				double a = num.top();
				num.pop();
				char op = ope.top();
				ope.pop();

				double result = operate(a, op, b);
				num.push(result);
			}
			ope.push(n[g_pos]);
			g_pos++;
		}
	}
	while (ope.top() != '#')
	{
		double b = num.top();
		num.pop();
		double a = num.top();
		num.pop();
		char op = ope.top();
		ope.pop();

		double result = operate(a, op, b);
		num.push(result);
	}
	return num.top();
}

void in_to_post(char *post) {
	stack<char>S;
	int k = 0, i = 0;
	S.push('#');
	int len = strlen(n);
	bool is_minus = true;
	for (g_pos = 0; g_pos < len;) {
		if (n[g_pos] == '-'&&is_minus)//负号
		{
			post[k] = '-';
			k++;
			g_pos++;
		}
		else if (n[g_pos] == '(') {
			is_minus = true;
			S.push(n[g_pos]);
			g_pos++;
		}
		else if (n[g_pos] == ')') {
			is_minus = false;
			g_pos++;
			while (S.top() != '(')
			{
				post[k] = S.top();
				S.pop();
				k++;
			}
			S.pop();
		}
		else if (n[g_pos] >= '0'&&n[g_pos] <= '9') {//数字
			is_minus = false;
			post[k] = n[g_pos];
			g_pos++;
			k++;
		}
		else if (n[g_pos] == '.') {
			is_minus = false;
			post[k] = n[g_pos];
			g_pos++;
			k++;
		}
		else if (S.empty()) {
			S.push(n[g_pos]);
			g_pos++;
		}
		else
		{
			while (level(n[g_pos]) <= level(S.top())) {
				post[k] = S.top();
				S.pop();
				k++;
			}
			S.push(n[g_pos]);
			post[k] = ' ';
			k++;
			g_pos++;
		}
	}
	while (S.top() != '#')
	{
		post[k] = S.top();
		S.pop();
		k++;
	}
	for (int j = 0; j <k; j++) {
		cout << post[j];
	}
}


int main()
{
	while (cin >> n)
	{
		char *post = new char;
		in_to_post(post);
		cout << "结果为：" << compute() << endl;
	}
	return 0;
}

