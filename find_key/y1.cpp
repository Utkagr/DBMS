// a1.cpp
// Compile using g++ -std=c++11 a1.cpp
#include <bits/stdc++.h>
using namespace std;
#define LOOP(a,b,c) for (int (a)=(b);(a)<(c);++(a))
#define LOOPN(a,b,c) for (int (a)=(b);(a)<=(c);++(a))
#define LOOPD(a,b,c) for (int (a)=(b);(a)>=(c);--(a))
#define LOOPSQ(a,b,c) for (int (a)=(b);(a)*(a)<=(c);++(a))
#define LOOPC(a,b,c) for (char (a)=(b);(a)<=(c);++(a))
#define LOOPEACH(a,b) for (auto &(a) : (b))
#define LOOPIT(a,b) for (auto (a)=(b).begin();(a)!=(b).end(); (a)++)
#define LOOPITR(a,b) for (auto (a)=(b).rbegin();(a)!=(b).rend(); (a)++)
#define REP(i,n) LOOP(i,0,n)
#define REPN(i,n) LOOPN(i,1,n)
#define ALL(v) v.begin(),v.end()

typedef set<string> cset;
cset attrs;
char buffer1[50];
int n;
cset fd[50];
cset lhs[50];
cset rhs[50];
cset c[50];
cset temp1, temp2;
vector<cset> skeys;
set<cset> ukeys;

string conv_to_str(cset s){
	string ans=" ";
	LOOPEACH (c, s){
		ans += c + " ";
	}
	return ans;
}

bool check_subset(cset main, cset subset){
	cset temp;
	set_difference(ALL(subset), ALL(main), inserter(temp, temp.begin()));
	return temp.empty();
}

cset find_closure(cset s){
	cset res = s;
	bool changed = false;
	REP(i, n){
		if (check_subset(s, lhs[i]) && !check_subset(s, rhs[i])){
			s.insert(ALL(rhs[i]));
			changed = true;
		}
	}
	if (changed) return find_closure(s);
	return s;
}
int main(){
	while(scanf(" %[a-zA-Z]", buffer1)){
		attrs.insert(buffer1);
	}
	scanf(" %d", &n);
	REP(j, n){
		lhs[j].clear(); rhs[j].clear();
		while(scanf(" %[a-zA-Z]", buffer1)) {
				lhs[j].insert(buffer1);
		}
		scanf(" -> ");
		while(scanf("%[a-zA-Z]", buffer1)) {
				if (lhs[j].find(buffer1)==lhs[j].end())
					rhs[j].insert(buffer1);
				scanf("%*[ ]");
		}
		if (rhs[j].empty()) {n--,j--; continue;}

	}
	// Insert the all attributes
	if (skeys.size()==0){
		skeys.push_back(attrs);
		ukeys.insert(attrs);
	}
	REP(i, skeys.size()){
		cset key = skeys[i];
		REP(i, n){
			if (check_subset(key, lhs[i]) && check_subset(key, rhs[i])){
				cset temp;
				set_difference(ALL(key), ALL(rhs[i]), inserter(temp, temp.begin()));
				if (ukeys.find(temp) == ukeys.end()) {
					skeys.push_back(temp);
					ukeys.insert(temp);
				}
				vector<string> rem; rem.clear();
				set_difference(ALL(attrs), ALL(temp), inserter(rem, rem.begin()));

				int rn = rem.size();

				// Select j at time
				for(int j=1; j<rn; j++){
					vector<bool> v(rem.size());
					fill(v.begin(), v.begin() + j , true);
					// Combinations
					do {
						cset s = temp;
						for (int i = 0; i < rn; ++i) {
							if (v[i]) {
								s.insert(rem[i]);
							}
						}
						if (ukeys.find(s) == ukeys.end()) {
							skeys.push_back(s);
							ukeys.insert(s);
						}
					} while (prev_permutation(v.begin(), v.end()));
				}
			}
		}
	}

	cout<<"Super Keys: \n";
	LOOPEACH(key, ukeys){
		cout<<"    "<<conv_to_str(key)<<endl;
	}
	cout<<endl;

	cout<<"Primary / Candidate Keys\n";
	LOOPEACH(key, ukeys){
		REP(i, n){
			int r = key.size();
			// select j at a time
			for(int j=1; j<r; j++){
				vector<bool> v(r);
				fill(v.begin(), v.begin() + j , true);
				// Combinations
				do {
					cset s;
					auto it = key.begin();
					for (int i = 0; i < r; ++i) {
						if (v[i]) {
							s.insert(*it);
						}
						it++;
					}
					if (find_closure(s)==attrs) {

						goto skip;
					}
				} while (prev_permutation(v.begin(), v.end()));
			}
		}
		cout<<"    "<<conv_to_str(key)<<endl;

		skip:;
	}
	return 0;
}