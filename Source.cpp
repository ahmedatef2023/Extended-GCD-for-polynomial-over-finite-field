#include<iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <string>
using namespace std;

bool check(float f) //check to see if the number is float return false and if integar returns true
{

	if (abs(f - int(f)) > 0)
		return false;

	else
		return true;

}
int multi_inverse(float a, int z)
{
	float temp;
	int result;
	int temp2;
	for (int i = 1; i < 10000; i++)
	{
		temp = i*(1 / a);
		if (check(temp))
		{
			temp2 = temp;
			if (temp2 % z == 1)
			{
				result = i;
				break;
			}

		}
	}
	if (result > z)
		result = result %z;
	return result;
}
vector<int> FF_Longdiv(vector<int> a, vector<int> b,int z)
{
	vector <int> temp;
	float m;
	int c;

	if (b.size() >= a.size())
	{
		temp = a;
		a = b;
		b = temp;
		temp.clear();
	}


	//applying long division untill the reminder is at lower power than b equation
	temp = b;
	while (a.size()>=b.size())
	{
		for (int i = 0; i < (a.size() - b.size()); i++)
			temp.insert(temp.begin(), 0);


		m = (float) a.back() / temp.back();
		if (!check(m))
			 c = multi_inverse(m, z);

		if (check(m))
			c = (int) m;

		for (int k = 0; k < temp.size(); k++)
		{
			temp[k] *= c;
			if (temp[k] > z)
				temp[k] %= z;
		}

		for (int i = 0; i < a.size(); i++)
		{
			a[i] = a[i] - temp[i];
			//if (a[i] > 0 && a[i] > z)
				//a[i] = a[i] % z;
			if(a[i]<0)
				a[i] = a[i] + ceil(abs(a[i]) / (float)z)*z;
		}
		if (a.size() > 1)
		{
			while (a[a.size() - 1] == 0)
			{
				a.pop_back();
				if (a.size() == 1)
					return a;
			}
		}
		if (a.size() == 1 || a.size() == 0)
			return a;
		temp = b;
	}

	return a;

}

vector<int>eq_ready(vector<float> a,int z)
{
	vector<int> b;
	for (int i = 0; i < a.size(); i++)
		b.push_back((int)a[i]);

	for (int i = 0; i < a.size(); i++)
	{

		if (check(a[i])) // number is integar, checks if it is negative or greater than z
		{
			if (a[i] > 0 && a[i] > z)
				b[i]=(int)a[i] % z;
			if(a[i]<0)
				b[i]= a[i] + ceil(abs(a[i]) / (float)z)*z;
		}
		if(!check(a[i]))
			b[i]=multi_inverse(a[i],z);
	}
	return b;
}
void Display(vector <int> a)
{
	if (a.size() == 1)
	{
		cout << a[0];
		return;
	}
	for (int i = a.size() - 1; i >= 0; i--)
	{
		if (a[i] != 0 && i != a.size() - 1)
		{
			if (a[i] == 1)
			{
				if (i == 0)
					cout << "+" << a[i]<<" ";
				else
					cout << "+";
			}
			if (a[i] != 1)
				cout << "+" << a[i];
			if (i == 1)
				cout << "X" << " ";
			if(i!=1 && i != 0)
				cout << "X^" << i << " ";

		}
		if (a[i] != 0 && i == a.size() - 1)
		{
			if (a[i] != 1 && i!=0)
				cout << a[i];
			if (a[i] != 1 && i==0)
				cout << a[i]<<" ";
			if (i == 1)
				cout << "X" <<" ";
			if (i != 1 && i !=0)
				cout << "X^" << i << " ";
		}
	}
}
void GCD(vector <int> b, vector <int> a, int z,int flag)
{
	vector <int> temp;
	float m ,kl;
	int pl;
	if (b.size() >= a.size())
	{
		temp = a;
		a = b;
		b = temp;
	}
	temp.clear();
	if (flag == 1)
	{
		cout << "GCD(";
		Display(b);
		cout << ", ";
		Display(a);
		cout << ")" << endl;
	}
	while (a.size() != 1)
	{
		if (flag == 1)
		{
			cout << "GCD(";
			Display(b);
			cout << ", ";
			Display(a);
			cout << " Mod(";
			Display(b);
			cout << "))" << endl;
		}

		a=FF_Longdiv(a, b,z);
		if (flag == 1 && a.size() == 1)
		{
			cout << "GCD(";
			Display(b);
			cout << ", ";
			if (a.size() == 1 && b.size() == 1)
				a[0] = 0;
			Display(a);
			cout << ")" << endl;
		}

		if (b.size() >= a.size())
		{
			if (a.size() == 1 && a[0] == 0)
				break;
			temp = a;
			a = b;
			b = temp;
			temp.clear();
			if (flag == 1 && a.size() !=1)
			{
				cout << "GCD(";
				Display(b);
				cout << ", ";
				Display(a);
				cout << ")" << endl;
			}
		}
	}
	if(flag==1)
		cout << endl;
	cout << "GCD Is ";
	if (b.size() == 1 && a.size() == 1)
		b[0] = 1;
	if (b.back() != 1)
	{
		m = b.back();
		for (int i = 0; i < b.size(); i++)
		{
			kl = b[i] / m;
			if (!check(kl))
				pl = multi_inverse(kl, z);
			if (check(kl))
				pl = kl;

			b[i] = pl;

		}
	}
	Display(b);
}
vector<int> Spaces(string s)
{
	vector <int> k;
	for (int i = 0; i < s.size(); i++)
		if (s[i] == ' ')
			k.push_back(i);
	return k;
}
float stf(string st)
{
	float v;
	v = atof(st.c_str());
	return v;
}
int main() {
	
	vector<float> a, b;
	vector <int> k ,af,bf;
	int z, flag ,c;
	string s;
	cout << "Enter 2 Coeffs Arrays in this form [xxx x x x x],[x x x x x x x]:";
	getline(cin, s);
	cout << endl;
	cout << "Over Finate Field of :";
	cin >> z;
	cout << endl;
	//parsing the String and get values
	if (s.find("SS") < s.size())
		flag = 1;
	else
		flag = 0;
	c = s.find(",");
	k = Spaces( s.substr(0,c) );
	for (int i = 0; i < k.size(); i++)
	{
		if (i == 0)
		{
			a.insert(a.begin(), stf(s.substr(1, k[0] - 1)));
			a.insert(a.begin(), stf(s.substr(k[0] + 1, k[1] - k[0])));
		}
		if(i>0 && i<k.size()-1)
		a.insert(a.begin(), stf(s.substr(k[i] + 1, k[i + 1] - k[i])));
		if(i==k.size() - 1)
		{
			string r = s.substr(k[i] + 1,s.find(']')-k[i]);
			r.pop_back();
			a.insert(a.begin(), stf(r));
		}
			
	}
	s = s.substr(c + 1);
	k = Spaces(s);
	for (int i = 0; i < k.size(); i++)
	{
		if (i == 0)
		{
			b.insert(b.begin(), stf(s.substr(1, k[0] - 1)));
			b.insert(b.begin(), stf(s.substr(k[0] + 1, k[1] - k[0])));
		}
		if (i>0 && i<k.size() - 1)
			b.insert(b.begin(), stf(s.substr(k[i] + 1, k[i + 1] - k[i])));
		if (i == k.size() - 1)
		{
			string r = s.substr(k[i] + 1);
			r.pop_back();
			if (flag == 1)
			{
				r.pop_back();
				r.pop_back();
			}
			b.insert(b.begin(), stf(r));
		}
	}
	
	af = eq_ready(a, z);
	bf = eq_ready(b, z);
	GCD(af, bf, z, flag);

	cout << endl << endl;


	system("pause");
	return 0;
}