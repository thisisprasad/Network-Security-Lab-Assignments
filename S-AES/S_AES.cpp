#include<bits/stdc++.h>
using namespace std;

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

void printBinaryString(string bin_str, string msg = ""){
    cout<<msg;
    for(int i = 0; i < bin_str.size(); ){
        for(int j = 0; j < 4; j++){
            cout<<bin_str[i+j];
        }
        cout<<" ";
        i += 4;
    }
    cout<<endl;
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
	string getBinaryString(int , int );
	int toDecimal(string );
	string polynomialReduction(string , string );	//	returns remainder
	string XOR(string , string );
	string substituteNibble(string , vector<vector<string>> &);
	string rotateNibble(string );
	string shiftRow(string );
	string applyMixColumn(string );
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
					substituteNibble(rotateNibble(this->w1), this->sBoxEncryption));

	this->w3 = XOR(this->w2, this->w1);

	temp = "00110000";
	this->w4 = XOR(XOR(this->w2, temp),
                    substituteNibble(rotateNibble(this->w3), this->sBoxEncryption));
    //  cout<<"w4: "<<this->w4<<endl;
    this->w5 = XOR(this->w4, this->w3);
    cout<<"w5: "<<this->w5<<endl;
}

string SimplifiedAES::getBinaryString(int num, int len = 4){
	int x = num;
	string res = "";
	while(x and res.size()<len){
		res = (char)(x%2 + '0') + res;
		x /= 2;
	}
	while(res.size() < len) res = '0' + res;

	return res;
}

int SimplifiedAES::toDecimal(string binaryString){
	int res = 0;
	reverse(binaryString.begin(), binaryString.end());
	for(int i = 0; i < binaryString.size(); i++){
		res += (binaryString[i]-'0')*pow(2, i);
	}

	return res;
}

string SimplifiedAES::polynomialReduction(string divisor, string dividend){
	int divisorLen = divisor.size();
	int dividendLen = dividend.size();
	int pos = divisorLen;
	string remainder = dividend.substr(0, divisorLen);
	cout<<"remainder dividend substr: "<<remainder<<endl;
	cout<<"divisor: "<<divisor<<endl;

	while(pos < dividendLen){
		remainder = XOR(divisor, remainder);
		cout<<"remainder after XOR: "<<remainder<<endl;
//		int i = 0;
		remainder += dividend[pos++];
		while(remainder[0]=='0' and remainder.size()>divisorLen){
			remainder = remainder.substr(1);
		}
	}
	remainder = XOR(divisor, remainder);
	while(remainder[0]=='0' and remainder.size()>divisorLen){
		remainder = remainder.substr(1);
	}

	return remainder;
}

string SimplifiedAES::substituteNibble(string w, vector<vector<string>> &sBox){
	string res = "";
	for(int i = 0; i < w.size(); ){
        int row = (w[i]-'0')*2 + (w[i+1]-'0'); i += 2;
        int col = (w[i]-'0')*2 + (w[i+1]-'0'); i += 2;
        res += sBox[row][col];
	}

	//int row0 = (w[pos]-'0')*2 + (w[pos+1]-'0'); pos += 2;
	//int col0 = (w[pos]-'0')*2 + (w[pos+1]-'0'); pos += 2;
	//int row1 = (w[pos]-'0')*2 + (w[pos+1]-'0'); pos += 2;
	//int col1 = (w[pos]-'0')*2 + (w[pos+1]-'0');

	//  string res = this->sBoxEncryption[row0][col0] + this->sBoxEncryption[row1][col1];
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

string SimplifiedAES::shiftRow(string s){
    string nibble1 = s.substr(4, 4);
    string nibble2 = s.substr(12, 4);
    string res = s.substr(0, 4) + nibble2 + s.substr(8, 4) + nibble1;

    return res;
}

string SimplifiedAES::applyMixColumn(string s){
	string res = "";
	int sz = s.size();
	int pos = 0;
	vector<vector<string> > strMatrix(sz/8, vector<string>(sz/8));
	for(int i = 0; i < sz/8; i++){
		for(int j = 0; j < sz/8; j++){
			strMatrix[i][j] = s.substr(pos, 4);
			pos += 4;
		}
	}

	string binaryMul;
	vector<vector<string> > tempMatrix(2, vector<string>(2));
	//	Multiplication
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			binaryMul = "";
			for(int k = 0; k < 2; k++){
				int num1 = this->mixColumnMatrix[i][k];
				int num2 = toDecimal(strMatrix[k][j]);
				if(num1*num2 > 15){
					//	Do polynomial reduction
					string reducedPolynomial = polynomialReduction("10011", getBinaryString(num1*num2, (log2(num1*num2))+1));
					while(reducedPolynomial[0]=='0' and reducedPolynomial.size()>4)
						reducedPolynomial = reducedPolynomial.substr(1);

					if(binaryMul == "") binaryMul = reducedPolynomial;
					else binaryMul = XOR(binaryMul, reducedPolynomial);
				}
				else {
					if(binaryMul == "") binaryMul = getBinaryString(num1*num2);
					else binaryMul = XOR(binaryMul, getBinaryString(num1*num2));
				}
			}
			tempMatrix[i][j] = binaryMul;
		}
	}

	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			res += tempMatrix[j][i];
		}
	}

	return res;
}

string SimplifiedAES::encrypt(const string &plainText){
    //  add round key0
    string ark0key = XOR(plainText, this->w0+this->w1);
    string subKey = substituteNibble(ark0key, this->sBoxEncryption);
    string shiftKey = shiftRow(subKey);
    printBinaryString(shiftKey, "shifted key: ");

    string mixColumnStr = applyMixColumn(shiftKey);

	string ark1key = XOR(mixColumnStr, this->w2+this->w3);
	subKey = substituteNibble(ark1key, this->sBoxEncryption);
	shiftKey = shiftRow(subKey);
	printBinaryString(shiftKey, "substituteNibble shift done: ");

	string ark2key = XOR(shiftKey, this->w4+this->w5);
	printBinaryString(ark2key, "cipher text is: ");

	return ark2key;
}

string SimplifiedAES::decrypt(const string &encryptedText){
	string ark2key = XOR(encryptedText, this->w4+this->w5);
	printBinaryString(ark2key, "ARK2 key: ");
	string shiftKey = shiftRow(ark2key);
	string subKey = substituteNibble(shiftKey, this->sBoxDecryption);
	printBinaryString(subKey, "Inverse nibble substitution: ");

	string ark1key = XOR(subKey, this->w2+this->w3);
	printBinaryString(ark1key, "ARK1 key: ");

	return "";
}

int main(){
    string plainText = "1101011100101000";
	//  cout<<"Enter plainText: ";
	//  cin>>plainText;

	SimplifiedAES cipher("aes_input.txt");
	string encryptedText = cipher.encrypt(plainText);
	printBinaryString(encryptedText, "Encryption text: ");

	string decyptedText = cipher.decrypt(encryptedText);
	printBinaryString(decyptedText, "Decrypted Text: ");

	return 0;
}

