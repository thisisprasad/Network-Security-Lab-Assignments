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

template<typename T>
void printMatrix(vector<vector<T>> matrix){
	cout<<"=============Printing Matrix====================="<<endl;
	for(int i = 0; i < matrix.size(); i++){
		for(int j = 0; j < matrix[0].size(); j++){
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"================================================="<<endl;
}


class SimplifiedDES{
private:
	vector<int> p4;
	vector<int> p8;
	vector<int> p10;
	vector<int> initialPermutation;
	vector<int> inversePermutation;
	vector<int> expansionPermutation;
	vector<vector<int>> s0;
	vector<vector<int>> s1;
	string key;
	string key1;
	string key2;

	void stringToArray(string &, vector<int> &, int );
	void stringToMartrix(string &, vector<vector<int>> &, int , int );
	void readFile(string &);
	string applyPermutation(string &, vector<int> &);
	void generateIntermediateKeys();
	void circularLeftShift(string &, int );
	void circularRightShift(string &, int );
	string FK(string &, string &, string &);
	string XOR(string &, string &);

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
		else if(keyValue[0] == "P4"){
			stringToArray(keyValue[1], this->p4, 4);
			for(auto& it: this->p4) cout<<it<<" ";
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
		else if(keyValue[0] == "E/P"){
			stringToArray(keyValue[1], this->expansionPermutation, DEF_PERMUTATION_SIZE);
			for(auto& it: this->expansionPermutation) cout<<it<<" ";
			cout<<endl;
		}
		else if(keyValue[0] == "S0"){
			stringToMartrix(keyValue[1], this->s0, 4, 4);
			printMatrix(this->s0);
			cout<<endl;
		}
		else if(keyValue[0] == "S1"){
			stringToMartrix(keyValue[1], this->s1, 4,4);
			printMatrix(this->s1);
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

void SimplifiedDES::stringToMartrix(string &s, vector<vector<int>> &matrix, int row_size, int col_size){
	stringstream stream(s);
	matrix = vector<vector<int>>(row_size, vector<int>(col_size));
	for(int i = 0; i < row_size; i++){
		for(int j = 0; j < col_size; j++){
			stream>>matrix[i][j];
		}
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

string SimplifiedDES::FK(string &leftHalf, string &rightHalf, string &key){
	string epBits = applyPermutation(rightHalf, this->expansionPermutation);
	string XORBits = XOR(epBits, key);

	string leftnibble = XORBits.substr(0, 4);
	string rightnibble = XORBits.substr(4);
	int row0 = (leftnibble[3] - '0') + (leftnibble[0] - '0')*2;
	int col0 = (leftnibble[2] - '0') + (leftnibble[1] - '0')*2;
	int row1 = (rightnibble[3] - '0') + (rightnibble[0] - '0')*2;
	int col1 = (rightnibble[2] - '0') + (rightnibble[1] - '0')*2;

	int val1 = this->s0[row0][col0];
	int val2 = this->s1[row1][col1];
	string i1, i2;
	while(i1.size() != 2){
		char ch = val1%2 + '0';
		i1 = ch + i1;
		val1 /= 2;
	}
	while(i2.size() != 2){
		char ch = val2%2 + '0';
		i2 = ch + i2;
		val2 /= 2;
	}
	string istr = i1 + i2;
	string p4Text = this->applyPermutation(istr, this->p4);
	XORBits = XOR(leftHalf, p4Text);
	string combinedKey = XORBits + rightHalf;

	return combinedKey;
}

string SimplifiedDES::XOR(string &op1, string &op2){
	//	Make both strings equal
	int sz = max(op1.size(), op2.size());
	string &small = (op1.size() < op2.size()) ? op1 : op2;
	while(small.size() != sz) small = '0' + small;

	string res = "";
	for(int i = 0; i < sz; i++){
		if(op1[i] == op2[i]) res += '0';
		else res += '1';
	}

	return res;
}

string SimplifiedDES::encrypt(const string &plainText){
	string ipBits = this->applyPermutation((string &)plainText, this->initialPermutation);
	string leftHalf = ipBits.substr(0, 4);
	string rightHalf = ipBits.substr(4);

	string fkBits = this->FK(leftHalf, rightHalf, this->key1);
	cout<<"First FK: "<<fkBits<<endl;

	rightHalf = fkBits.substr(0, 4);
	leftHalf = fkBits.substr(4);
	fkBits = this->FK(leftHalf, rightHalf, this->key2);
	cout<<"Applied fk2: "<<fkBits<<endl;

	string cipherText = this->applyPermutation(fkBits, this->inversePermutation);
	return cipherText;
}

int main(){
	string plainText;
	cout<<"Enter plainText: "; cin>>plainText;

	SimplifiedDES des("des_input.txt");
	cout<<endl;
	string encryptedText = des.encrypt("10100101");
	cout<<"encrypted text: "<<encryptedText<<endl;

}
