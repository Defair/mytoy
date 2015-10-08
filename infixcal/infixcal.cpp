#include<iostream>
#include<map>
#include<stack>
#include<vector>

using namespace std;

bool priortable[6][6] = { { 1, 1, 0, 0, 1, 1 }, { 1, 1, 0, 0, 1, 1 }, { 1, 1, 1, 1, 1, 1 },
{ 1, 1, 1, 1, 1, 1 }, { 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 1 } };

map<char, int> opra = { { '+', 0 }, { '-', 1 }, { '*', 2 }, { '/', 3 }, { '#', 4 }, { '(', 5 } };

bool prior(char a1, char a2);

int postcal(const deque<string>& a);

deque<string> intopost(vector<string> a);

void main(){
	vector<string> a = { "(", "12", "+", "1", "*", "3", ")", "*", "21" };
	deque<string> te = intopost(a);
	int res = postcal(te);
	cout << res;
	system("pause");
}

bool prior(char a1, char a2){
	return priortable[opra.find(a1)->second][opra.find(a2)->second];
}

int postcal(const deque<string>& a){
	stack<int> res;
	auto it = a.begin();
	while (it != a.end()){
		int temp1, temp2;
		while (!opra.count((*it)[0])){
			res.push(atoi((*it).c_str()));
			it++;
		}
		if (opra.count((*it)[0])){
			temp2 = res.top();
			res.pop();
			temp1 = res.top();
			res.pop();
			switch ((*it)[0]){
			case '+':res.push(temp1 + temp2); break;
			case '-':res.push(temp1 - temp2); break;
			case '*':res.push(temp1 * temp2); break;
			case '/':res.push(temp1 / temp2); break;
			}
			it++;
		}
	}
	return res.top();
}

deque<string> intopost(vector<string> a){
	auto it = a.begin();
	stack<string> s1, s2;
	s1.push(string{ '#' });
	while (it != a.end()){
		if ((*it)[0] == '('){
			s1.push(*it);
			it++;
		}
		else if ((*it)[0] == ')'){
			while (s1.top()[0] != '('){
				s2.push(s1.top());
				s1.pop();
			}
			s1.pop();
			it++;
		}
		else if (!opra.count((*it)[0])){
			s2.push(*it);
			it++;
		}
		else{
			if (prior((*it)[0], s1.top()[0]) && it != a.end()){
				s1.push(*it);
				it++;
			}
			else if (s1.top()[0] != '#'){
				s2.push(s1.top());
				s1.pop();
			}
		}
	}
	while (s1.top()[0] != '#'){
		s2.push(s1.top());
		s1.pop();
	}
	deque<string> res;
	while (!s2.empty()){
		res.push_front(s2.top());
		s2.pop();
	}
	return res;
}