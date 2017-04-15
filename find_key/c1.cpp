#include <bits/stdc++.h>

using namespace std;

vector<string>att;
vector<pair<vector<string>,vector<string> > >fd;
vector<pair<vector<string>,int> >keys;

int main(){
	int n,m;
	cout<<"Enter the number of attributes in the relation"<<endl;
	cin>>n;
	cout<<"Enter the names of attributes"<<endl;
	for(int i=0;i<n;i++){
		string temp;
		cin>>temp;
		att.push_back(temp);
	}
	cout<<"Enter the number of FDs"<<endl;
	cin>>m;
	for(int i=0;i<m;i++){
		vector<string>a;
		vector<string>b;
		int p,q;
		cout<<"How many attributes are on the LHS of FD number "<<i+1<<endl;
		cin>>p;
		cout<<"Enter the LHS"<<endl;
		for(int j=0;j<p;j++){
			string temp;
			cin>>temp;
			a.push_back(temp);
		}
		cout<<"How many attributes are on the RHS of FD number "<<i+1<<endl;
		cin>>q;
		cout<<"Enter the RHS"<<endl;
		for(int j=0;j<q;j++){
			string temp;
			cin>>temp;
			b.push_back(temp);
		}
		fd.push_back(make_pair(a,b));
	}
	
	for(int i=(int)pow(2,n)-1;i>=0;i--){
		int keysize;
		vector<string>news;
		set<string>neww;
		set<string>::iterator it;
		for(int j=0;j<n;j++){
			if(i&(1<<j)){
				neww.insert(att[j]);
				news.push_back(att[j]);
			}
		}
		keysize=neww.size();
		int prevsize=neww.size();
		for(int k=0;k<m;k++){
			//if(fd[k].first is subset of neww)
			int sz=fd[k].first.size();
			int flag=1;
			for(int l=0;l<sz;l++){
				bool found=false;
				for(it=neww.begin();it!=neww.end();it++){
					if((*it)==fd[k].first.at(l)){
						found=true;
						break;
					}
				}
				if(!found){
					flag=0;
					break;
				}
			}
			if(flag){
				sz=fd[k].second.size();
				for(int l=0;l<sz;l++){
					neww.insert(fd[k].second.at(l));
				}
				if(neww.size()>prevsize)
					k=-1;
				prevsize=neww.size();
			}
		}
		if(n==neww.size()){
			keys.push_back(make_pair(news,keysize));
		}
	}
	int maxm=1000;
	for(int i=0;i<keys.size();i++){
		if(keys[i].second<maxm){
			maxm=keys[i].second;
		}
	}
	cout<<"The following are the keys of the relation"<<endl;
	for(int i=0;i<keys.size();i++){
		if(keys[i].second==maxm){
			cout<<"Key:"<<endl;
			int te=keys[i].first.size();
			for(int j=0;j<te;j++){
				cout<<keys[i].first.at(j)<<" ";
			}
			cout<<endl;
		}
	}
	return 0;
}