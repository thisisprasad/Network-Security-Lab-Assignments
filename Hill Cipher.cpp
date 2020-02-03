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

void createCofactor(const vector<vector<int>> &matrix, int cr, int cc, vector<vector<int>> &cofactor){
	int i = 0, j = 0;
	int n = matrix.size();
	for(int row = 0; row < matrix.size(); row++){
		for(int col = 0; col < matrix[0].size(); col++){
			if(row!=cr and col!=cc){
				cofactor[i][j++] = matrix[row][col];
				if(j == n-1){
					j = 0;
					i++;
				}
			}
		}
	}
}

int determinant(vector<vector<int>> &matrix, int n){
	int det = 0;
	if(n == 1) return matrix[0][0];

	vector<vector<int>> cofactor(n, vector<int>(n));
	int sign = 1;
	for(int x = 0; x < matrix.size(); x++){
		createCofactor(matrix, 0, x, cofactor);
		det += sign * matrix[0][x] * determinant(cofactor, n-1);
		sign *= (-1);
	}

	return det;
}

vector<vector<int> > matrixInverse(vector<vector<int>> &matrix){
	vector<vector<int> > inverseMatrix(matrix.size(), vector<int>(keyMatrix[0].size()));

	//	calculate determinant
	int det = determinant(matrix, matrix.size());
	cout<<"det: "<<det<<endl;

	//	calculate adjoint

	//	find the inverse

	return vector<vector<int>>();
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
	vector<vector<int> > inverseKeyMatrix(keyMatrix.size(), vector<int>(keyMatrix[0].size()));
	inverseKeyMatrix = matrixInverse(keyMatrix);
	return 0;
}
