#include<iostream>
using namespace std;
const int mod = 26;

void createKey(string &key, const string &msg){
	int posCnt = 0;

	while(key.size() < msg.size()){
		key += key[posCnt];
		posCnt = (posCnt + 1)%msg.size();
	}
}

string encrypt(string msg, string key){
	string encryptedMsg = "";

	for(int i = 0; i < msg.size(); i++){
		int ch = (msg[i] + key[i])%mod;
//		if(msg[i]>='A' and msg[i]<='Z') ch += 'A';
		ch += 'A';

		encryptedMsg += ch;
	}

	return encryptedMsg;
}

string decrypt(string encryptedMsg, string key){
	string decryptedText = "";

	for(int i = 0; i < encryptedMsg.size(); i++){
		int ch = (encryptedMsg[i] - key[i] + mod)%mod;
//		if(encryptedMsg[i]>='A' and encryptedMsg[i]<='Z') ch += 'A';
		ch += 'A';

		decryptedText += ch;
	}

	return decryptedText;
}

int main(){
	string msg, key;
	cout<<"Enter string: ";
	cin>>msg;
	cout<<"Enter key: ";
	cin>>key;
	createKey(key, msg);

	string encryptedMsg = encrypt(msg, key);
	cout<<"Encrypted string: "<<encryptedMsg<<endl;

	string decryptedMsg = decrypt(encryptedMsg, key);
	cout<<"Decrypted string: "<<decryptedMsg<<endl;

	return 0;
}
