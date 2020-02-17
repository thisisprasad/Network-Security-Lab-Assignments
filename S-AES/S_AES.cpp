#include<bits/stdc++.h>
using namespace std;

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

class SimplifiedAES{
private:
	string key;
	string w0;
	string w1;
	string w2;
	string w3;
	string w4;
	string w5;
	vector<vector<int>> mixColumnMatrix;
	vector<vector<int>> inverseMixColumnMatrix;
	vector<vector<string>> sBoxEncryption;
	vector<vector<string>> sBoxDecryption;

	void readFile(string &);
	void generateIntermediateKeys();
	string XOR(string , string );
	string substituteNibble(string );
	string rotateNibble(string );
	template<typename T> void stringToMatrix(string &, vector<vector<T>> &, int , int );

public:
	SimplifiedAES(string fileName){
		readFile(fileName);
		generateIntermediateKeys();
	}

	string encrypt(const string& );
	string decrypt(const string& );
};

template<typename T> void SimplifiedAES::stringToMatrix(string & s,
													vector<vector<T>> &matrix,
													int row_size, int col_size)
{
    stringstream strStream(s);
    matrix = vector<vector<T>>(row_size, vector<T>(col_size));	//	this->'matrix'
    for(int i = 0; i < row_size; i++){
		for(int j = 0; j < col_size; j++){
			strStream>>matrix[i][j];
		}
    }
}

void SimplifiedAES::readFile(string& fileName){
	ifstream file;
	file.open(fileName, ios::in);
	if(!file){
		cout<<"Error opening file"<<endl;
		return ;
	}

	string line;
	while(getline(file, line)){
		vector<string> keyValue = split(line, ':');
		if(keyValue[0] == "key"){
			this->key = keyValue[1];
		}
		else if(keyValue[0] == "sBoxEncryption"){
			stringToMatrix(keyValue[1], this->sBoxEncryption, 4, 4);
		}
		else if(keyValue[0] == "sBoxDecryption"){
			stringToMatrix(keyValue[1], this->sBoxDecryption, 4, 4);
		}
		else if(keyValue[0] == "mixColumnMatrix"){
			stringToMatrix(keyValue[1], this->mixColumnMatrix, 2, 2);
		}
		else if(keyValue[0] == "inverseMixColumnMatrix"){
			stringToMatrix(keyValue[1], this->inverseMixColumnMatrix, 2, 2);
		}
	}
}

void SimplifiedAES::generateIntermediateKeys(){
	this->w0 = key.substr(0, key.size()/2);
	this->w1 = key.substr(key.size()/2);

	string temp = "10000000";
	this->w2 = XOR(XOR(this->w0, temp),
					substituteNibble(rotateNibble(this->w1)));

	cout<<"w2: "<<this->w2<<endl;
}

string SimplifiedAES::substituteNibble(string w){
	int pos = 0;
	int row0 = (w[pos]-'0')*2 + (w[pos+1]-'0'); pos += 2;
	int col0 = (w[pos]-'0')*2 + (w[pos+1]-'0'); pos += 2;
	int row1 = (w[pos]-'0')*2 + (w[pos+1]-'0'); pos += 2;
	int col1 = (w[pos]-'0')*2 + (w[pos+1]-'0');

	string res = this->sBoxEncryption[row0][col0] + this->sBoxEncryption[row1][col1];
	return res;
}

string SimplifiedAES::rotateNibble(string w){
	string leftNibble = w.substr(0, w.size()/2);
	string rightNibble = w.substr(w.size()/2);

	return (rightNibble + leftNibble);
}

string SimplifiedAES::XOR(string op1, string op2){
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

int main(){
	SimplifiedAES cipher("aes_input.txt");
	cout<<"The algorithm is not yet ready!"<<endl;

	return 0;
}

