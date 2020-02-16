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
			stringToMatrix(keyValue[1], this->sBoxDecryption, 4, 4);
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

int main(){
	cout<<"The algorithm is not yet ready!"<<endl;

	return 0;
}

