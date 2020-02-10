//#include<iostream>
//#include<fstream>
//#include<string>
//#include<vector>
#include<bits/stdc++.h>
using namespace std;

#define DEF_PERMUTATION_SIZE 8

vector<string> split(string &s, char sym){
	vector<string> keyValue;
	string t = "";
	int i = 0;
	while(i < s.size()){
		if(s[i] != sym){
			t += s[i];
		}
		else{
			keyValue.push_back(t);
			t = "";
		}
		i++;
	}
	keyValue.push_back(t);
	return keyValue;
}

class SimplifiedDES{
private:
	vector<int> p8;
	vector<int> p10;
	vector<int> initialPermutation;
	vector<int> inversePermutation;
	string key;
	string key1;
	string key2;

	void stringToArray(string &, vector<int> &, int );
	void readFile(string &);
	string applyPermutation(string &, vector<int> &);
	void generateIntermediateKeys();

public:
	SimplifiedDES(string fileName){
		readFile(fileName);
		generateIntermediateKeys();
	}

	string encrypt(const string &);
	string decrypt(const string &);
};

void SimplifiedDES::readFile(string &fileName){
	ifstream file;
	file.open(fileName, ios::in);
	if(!file){
		cout<<"Error opening file"<<endl;
	}
	string line;

	while(getline(file, line)){
		vector<string> keyValue = split(line, ':');
		cout<<"line: "<<line<<endl;
		if(keyValue[0] == "key"){
			this->key = keyValue[1];
			cout<<"key: "<<key<<endl;
		}
		else if(keyValue[0] == "P10"){
			stringToArray(keyValue[1], this->p10, 10);
			for(auto& it: this->p10) cout<<it<<" ";
			cout<<endl;
		}
		else if(keyValue[0] == "P8"){
			stringToArray(keyValue[1], this->p8, DEF_PERMUTATION_SIZE);
			for(auto& it: this->p8) cout<<it<<" ";
			cout<<endl;
		}
		else if(keyValue[0] == "IP"){
			stringToArray(keyValue[1], this->initialPermutation, DEF_PERMUTATION_SIZE);
			for(auto& it: this->initialPermutation) cout<<it<<" ";
			cout<<endl;
		}
		else if(keyValue[0] == "IP-1"){
			stringToArray(keyValue[1], this->inversePermutation, DEF_PERMUTATION_SIZE);
			for(auto& it: this->inversePermutation) cout<<it<<" ";
			cout<<endl;
		}
	}
}

void SimplifiedDES::stringToArray(string &s, vector<int> &arr, int n){
	stringstream sStream(s);
	for(int i = 0; i < n; i++){
		int x; sStream>>x;
		arr.push_back(x);
	}
}

string SimplifiedDES::applyPermutation(string& text, vector<int>& permutation){
	string res = "";
	for(int i = 0; i < permutation.size(); i++){
		char ch = text[permutation[i]-1];
		res += ch;
	}

	cout<<"permuted string: "<<res<<endl;
	return res;
}

void SimplifiedDES::generateIntermediateKeys(){
	string p10Key = applyPermutation(this->key, this->p10);
	string l0 = p10Key.substr(0,5);
	string r0 = p10Key.substr(5);

	cout<<"l0: "<<l0<<", r0: "<<r0<<endl;
}

string SimplifiedDES::encrypt(const string &plainText){

	return "Not yet!!";
}

int main(){
	string plainText;
	cout<<"Enter plainText: "; cin>>plainText;

	SimplifiedDES des("des_input.txt");
	cout<<endl;
	string encryptedText = des.encrypt(plainText);
	cout<<"encrypted text: "<<encryptedText<<endl;

}
