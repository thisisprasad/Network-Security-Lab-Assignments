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
	void circularLeftShift(string &, int );
	void circularRightShift(string &, int );

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
		return ;
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

	return res;
}

void SimplifiedDES::generateIntermediateKeys(){
	string p10Key = applyPermutation(this->key, this->p10);
	string leftHalf = p10Key.substr(0,5);
	string rightHalf = p10Key.substr(5);
	circularLeftShift(leftHalf, 1);
	circularLeftShift(rightHalf, 1);
	string combinedKey = leftHalf + rightHalf;
	this->key1 = applyPermutation(combinedKey, this->p8);

	leftHalf = combinedKey.substr(0, 5);
	rightHalf = combinedKey.substr(5);
	circularLeftShift(leftHalf, 2);
	circularLeftShift(rightHalf, 2);
	combinedKey = leftHalf + rightHalf;
	this->key2 = applyPermutation(combinedKey, this->p8);

	cout<<"l0: "<<leftHalf<<", r0: "<<rightHalf<<endl;
	cout<<"Key2: "<<key2<<endl;
}

void SimplifiedDES::circularLeftShift(string& s, int shiftBy){
	shiftBy %= s.size();
	int pos = 0;
	vector<char> temp;
	for(int i = 0; i < shiftBy; i++){
		temp.push_back(s[pos]);
		pos++;
	}
	for(int i = shiftBy; i < s.size(); i++){
		s[i-shiftBy] = s[i];
	}
	pos = 0;
	for(int i = s.size()-shiftBy; i < s.size(); i++) s[i] = temp[pos++];
}

void SimplifiedDES::circularRightShift(string& s, int shiftBy){
	shiftBy %= s.size();
	int pos = s.size()-1;
	vector<char> temp;
	for(int i = 0; i < shiftBy; i++){
		temp.push_back(s[pos]);
		pos--;
	}
	for(int i = s.size()-1-shiftBy; i >= 0; i--){
		s[i+shiftBy] = s[i];
	}
	for(int i = 0; i < shiftBy; i++) s[i] = temp[i];
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
