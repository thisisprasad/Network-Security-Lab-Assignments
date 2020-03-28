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
	int cnt = 1;
	for(int i = 0; i < keyMatrix.size(); i++){
		for(int j = 0; j < keyMatrix[i].size(); j++){
			keyMatrix[i][j] = rand()%mod;
//			keyMatrix[i][j] = cnt++;
//			keyMatrix[i][j] = gfg_key[cnt]%mod;
//			cnt += 1;
		}
	}
}

void createCofactor(const vector<vector<int>> &matrix, int cr, int cc, vector<vector<int>> &cofactor){
	int i = 0, j = 0;
	int sz = matrix.size();
	for(int row = 0; row < sz; row++){
		for(int col = 0; col < sz; col++){
			if(row!=cr and col!=cc){
				cofactor[i][j++] = matrix[row][col];
				if(j == sz-1){
					j = 0;
					i++;
				}
			}
		}
	}
}

int determinant(vector<vector<int>> &matrix, int sz){
	int det = 0;
	if(sz == 1) return matrix[0][0];

	vector<vector<int>> cofactor(sz, vector<int>(sz));
	int sign = 1;
	for(int x = 0; x < matrix.size(); x++){
		createCofactor(matrix, 0, x, cofactor);
		det += sign * matrix[0][x] * determinant(cofactor, sz-1);
		sign *= (-1);
	}

	return det;
}

int getModuloMultiplicativeInverse(int a, int modulo){
	int m0 = modulo;
	int y = 0, x = 1;
	if(modulo == 1) return 0;

	while(a > 1){
		int q = a / modulo;
		int t = modulo;

		modulo = a%modulo; a = t;
		t = y;

		y = x - q*y;
		x = t;
	}

	if(x < 0) x += m0;

	return x;
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
			sign = ((i+j)&1) ? -1 : 1;
			adjointMatrix[j][i] = sign * determinant(cofactor, n-1);
		}
	}

	return adjointMatrix;
}


vector<vector<int> > matrixInverse(vector<vector<int>> &matrix){
	vector<vector<int>> inverseMatrix(matrix.size(), vector<int>(matrix[0].size()));

	int det = determinant(matrix, matrix.size());
	vector<vector<int>> adjointMatrix = getAdjointMatrix(matrix);
	cout<<"Adjoint Matrix: "<<endl; printMatrix(adjointMatrix);
	int moduloInverse;
	if(__gcd(det, 26) == 1){
		cout<<"Modular Inverse exists"<<endl;
		moduloInverse = getModuloMultiplicativeInverse(det, 26);
	}
	else{
		cout<<"Modular invcerse does not exist!!"<<endl;
		cout<<"Cannot be decrypted"<<endl;
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			inverseMatrix[i][j] = 1.0*(adjointMatrix[i][j])/(float)(det);
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

vector<int> decrypt(vector<int> &encryptedMatrix,
								vector<vector<int>> &inverseMatrix){
	int sz = encryptedMatrix.size();
	vector<int> decryptedMatrix(sz);
	for(int i = 0; i < sz; i++){
		for(int x = 0; x < sz; x++){
			decryptedMatrix[i] += inverseMatrix[i][x] * (float)encryptedMatrix[x];
		}
//		decryptedMatrix[i] = (char)(fmod(decryptedMatrix[i], 26) + 'A');
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
	vector<vector<int> > inverseKeyMatrix = matrixInverse(keyMatrix);
//	printMatrix(inverseKeyMatrix);
	vector<vector<int>> adjointMatrix(keyMatrix);
	vector<int> decryptedMatrix = decrypt(encryptedMatrix, adjointMatrix);
	vector<float> decryptedMatrixFloat(n);
	cout<<"Decrypted string: ";
	for(auto it: decryptedMatrix) cout<<(char)it;
	for(int i = 0; i < decryptedMatrix.size(); i++)
		decryptedMatrixFloat[i] = decryptedMatrix[i];
	int det = determinant(keyMatrix, keyMatrix.size());
	for(int i = 0; i < decryptedMatrixFloat.size(); i++){
		decryptedMatrixFloat[i] /= det;
		decryptedMatrixFloat[i] = fmod(decryptedMatrixFloat[i], (float)1.0*26);
		decryptedMatrixFloat[i] += 26;
		decryptedMatrixFloat[i] = fmod(decryptedMatrixFloat[i], (float)26);
		decryptedMatrix[i] += 'A';
	}
	for(auto it: decryptedMatrixFloat) cout<<(char)it<<" ";

	return 0;
}
