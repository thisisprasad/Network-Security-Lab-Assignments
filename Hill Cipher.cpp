#include<bits/stdc++.h>
using namespace std;

const int mod = 65;
int n;
vector< vector<int> > keyMatrix;
//string gfg_key = "GYBNQKURP";
void initializeKeyMatrix(vector<vector<int>> &keyMatrix, int sz = 1){
//	int cnt = 0;
	for(int i = 0; i < keyMatrix.size(); i++){
		for(int j = 0; j < keyMatrix[i].size(); j++){
			keyMatrix[i][j] = rand()%mod;
//			keyMatrix[i][j] = gfg_key[cnt]%mod;
//			cnt += 1;
		}
	}
}

vector<int> encrypt(vector<int> msgMatrix, vector<vector<int>> keyMatrix){
	vector<int> cipherMsg(n);

	for(int i = 0; i < n; i++){
		cipherMsg[i] = 0;
		for(int x = 0; x < n; x++){
			cipherMsg[i] += keyMatrix[i][x] * msgMatrix[x];
		}
		cipherMsg[i] = cipherMsg[i]%26;
	}

	return cipherMsg;
}

int main(){
	string msg;
	cout<<"Enter message: ";
	cin>>msg;

	::n = msg.size();
	keyMatrix = vector<vector<int>>(n, vector<int>(n));
	initializeKeyMatrix(keyMatrix, n);

	vector<int> msgMatrix(msg.begin(), msg.end());
	for(int i = 0; i < msgMatrix.size(); i++) msgMatrix[i] = msgMatrix[i]%mod;
	vector<int> encryptedMatrix = encrypt(msgMatrix, keyMatrix);
	string encryptedMsg;
	for(int i = 0; i < encryptedMatrix.size(); i++) encryptedMsg += encryptedMatrix[i]+'A';
	cout<<"Encrypted msg: "<<encryptedMsg<<endl;
	cout<<endl;

	//	Decryption remaining...

	return 0;
}
