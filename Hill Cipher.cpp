#include<bits/stdc++.h>
using namespace std;

const int mod = 65;
int n;
vector< vector<int> > keyMatrix;
//string gfg_key = "ABCDEFGHI";

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

void initializeKeyMatrix(vector<vector<int>> &keyMatrix, int sz = 1){
	int cnt = 0;
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

vector<vector<int>> getAdjointMatrix(vector<vector<int>> &matrix){
	int n = matrix.size();
	vector<vector<int>> adjointMatrix(n, vector<int>(n));
	if(n == 1){
		adjointMatrix[0][0] = 1;
		return adjointMatrix;
	}

	int sign = 1;
	vector<vector<int>> cofactor(n, vector<int>(n));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			createCofactor(matrix, i, j, cofactor);
			sign = ((i+j)&1 ? -1 : 1);
			adjointMatrix[i][j] = sign * determinant(cofactor, n-1);
		}
	}

	return adjointMatrix;
}

vector<vector<float> > matrixInverse(vector<vector<int>> &matrix){
//	vector<vector<int> > inverseMatrix(matrix.size(), vector<int>(keyMatrix[0].size()));

	int det = determinant(matrix, matrix.size());

	vector<vector<int>> adjointMatrix = getAdjointMatrix(matrix);

	vector<vector<float>> inverseMatrix(matrix.size(), vector<float>(matrix[0].size()));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			inverseMatrix[i][j] = (float)(adjointMatrix[i][j])/(float)(det);
		}
	}

	return inverseMatrix;
}

vector<int> encrypt(vector<int> msgMatrix, vector<vector<int>> keyMatrix){
	vector<int> cipherMatrix(n);

	for(int i = 0; i < n; i++){
		cipherMatrix[i] = 0;
		for(int x = 0; x < n; x++){
			cipherMatrix[i] += keyMatrix[i][x] * msgMatrix[x];
		}
		cipherMatrix[i] = cipherMatrix[i]%26;
	}

	return cipherMatrix;
}

vector<float> decrypt(vector<int> &encryptedMatrix,
								vector<vector<float>> &inverseMatrix){
	int sz = encryptedMatrix.size();
	vector<float> decryptedMatrix(sz);
	for(int i = 0; i < sz; i++){
		for(int x = 0; x < sz; x++){
			decryptedMatrix[i] += inverseMatrix[i][x] * (float)encryptedMatrix[x];
		}
		decryptedMatrix[i] = (char)(fmod(decryptedMatrix[i], 26) + 'A');
		cout<<"decryp[i]: "<<decryptedMatrix[i]<<endl;
	}

	return decryptedMatrix;
}

int main(){
	string msg;
	cout<<"Enter message: ";
	cin>>msg;

	::n = msg.size();
	keyMatrix = vector<vector<int>>(n, vector<int>(n));
	initializeKeyMatrix(keyMatrix, n);

	//	Encryption
	vector<int> msgMatrix(msg.begin(), msg.end());
	for(int i = 0; i < msgMatrix.size(); i++) msgMatrix[i] = msgMatrix[i]%mod;
	vector<int> encryptedMatrix = encrypt(msgMatrix, keyMatrix);
	string encryptedMsg;
	for(int i = 0; i < encryptedMatrix.size(); i++) encryptedMsg += encryptedMatrix[i]+'A';
	cout<<"Encrypted msg: "<<encryptedMsg<<endl;
	cout<<endl;

	//	Decryption
	vector<vector<float> > inverseKeyMatrix = matrixInverse(keyMatrix);
	printMatrix(inverseKeyMatrix);
	vector<float> decryptedMatrix = decrypt(encryptedMatrix, inverseKeyMatrix);
	cout<<"Decrypted string: ";
	for(auto it: decryptedMatrix) cout<<(char)it;


	return 0;
}
