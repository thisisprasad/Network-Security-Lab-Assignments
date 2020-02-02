#include<iostream>
using namespace std;
const int mod = 26;

string encrypt(string s, int shift){
	string encryptedString = "";
	char ch;

	for(int i = 0; i < s.size(); i++){
		if(s[i]>='A' and s[i]<='Z'){
			ch = (s[i] - 'A' + shift)%mod + 'A';
			encryptedString += ch;
		}
		else {
			ch = (s[i] - 'a' + shift)%mod + 'a';
			encryptedString += ch;
		}
	}

	return encryptedString;
}

string decrypt(string s, int shift){
	string decryptedString = "";
	char ch;

	for(int i = 0; i < s.size(); i++){
		if(s[i]>='A' and s[i]<='Z'){
			ch = (s[i] - 'A' - shift)%mod + 'A';
			decryptedString += ch;
		}
		else{
			ch = (s[i] - 'a' - shift)%mod + 'a';
			decryptedString += ch;
		}
	}

	return decryptedString;
}

int main(){

    string s;
    int shift;
    cout<<"Enter string: ";
	cin>>s;
	cout<<"Enter shift(0-25): ";
	cin>>shift;

    string encryptedString = encrypt(s, shift);
    cout<<"Encrypted string: "<<encryptedString<<endl;

    string decryptedString = decrypt(encryptedString, shift);
    cout<<"Decrypted string: "<<decryptedString<<endl;

	return 0;
}
