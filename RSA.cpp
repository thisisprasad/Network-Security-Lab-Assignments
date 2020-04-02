#include<bits/stdc++.h>
using namespace std;

typedef struct RSA_Crypto{
	double p;
	double q;
	double e;
	double phi;
	double d;
}rsa;

int gcd(int a,int b){
	if(a==0) return b;
	return gcd(b%a, a);
}

rsa cryptor;

void init(){
	cryptor = {3, 7, 2};
	cryptor.phi = (cryptor.p - 1) * (cryptor.q - 1);

	while(cryptor.e < cryptor.phi){
		if(gcd(cryptor.e, cryptor.phi) == 1) break;
		else cryptor.e++;
	}

	int k = 2;
	cryptor.d = (1 + (k*cryptor.phi))/cryptor.e;
}

double RSAEncrypt(double message){
	int k = 2;
	double n = cryptor.p * cryptor.q;
	double cipherText = pow(message, cryptor.e);
	cipherText = fmod(cipherText, n);

	return cipherText;
}

double RSADecrypt(double encryptedMessage){
	double n = cryptor.p * cryptor.q;
	double plainText = pow(encryptedMessage, cryptor.d);
	plainText = fmod(plainText, n);

	return plainText;
}

int main(){
	init();

	double message = 17;
	cout<<"Message: "<<message<<endl;
	double encryptedMessage = RSAEncrypt(message);
	cout<<"Encrypted message: "<<encryptedMessage<<endl;

	double decryptedMessage = RSADecrypt(encryptedMessage);

	if(decryptedMessage == message){
		cout<<"Decryption successful!!"<<endl;
	}
	else{
		cout<<"Decryption failed!!"<<endl;
	}

	return 0;

}
