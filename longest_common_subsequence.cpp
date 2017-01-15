#include <iostream>
using namespace std;


int lcs(const string& s1, int id_s1, const string& s2, int id_s2)
{
	if((id_s1 >= s1.length()) || (id_s2 >= s2.length()))
	{
		return 0;
	}

	if(s1[id_s1] == s2[id_s2])
	{
		int ret = 1 + lcs(s1, id_s1 + 1, s2, id_s2 + 1);   
		return ret;
	}
	else
	{
		return max(lcs(s1, id_s1, s2, id_s2 + 1), lcs(s1, id_s1 + 1, s2, id_s2));
	}
}

int main()
{
	string s1 = "abcdaf";
	string s2 = "acbcf";

	int l = lcs(s1, 0, s2, 0);

	cout << "l = " << l << endl;
}