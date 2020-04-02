#include<bits/stdc++.h>
using namespace std;

int generator = 9;
int prime = 23;

int getPublicKey(int private_key){
	int public_key = 1;
	//	power operation
	for(int i = 0 ; i < private_key; i++){
		public_key *= generator;
		public_key %= prime;
	}

	return public_key;
}

int generateKey(int public_key, int private_key){
	int key = 1;
	for(int i = 0; i < private_key; i++){
		key *= public_key;
		key %= prime;
	}

	return key;
}

int main(){
	cout<<"Consider Alice and Bob are exchanging information"<<endl;

	int alice_private_key, bob_private_key;
	cout<<"Enter private key of Alice: ";
	cin>>alice_private_key;

	cout<<"Enter private key for bob: ";
	cin>>bob_private_key;

	int alice_public_key = getPublicKey(alice_private_key);
	int bob_public_key = getPublicKey(bob_private_key);

	int alice_key = generateKey(bob_public_key, alice_private_key);
	int bob_key = generateKey(alice_public_key, bob_private_key);

	if(alice_key == bob_key) cout<<"Both keys are same"<<endl;
	else cout<<"Both keys are not same!!"<<endl;

	cout<<"Alice key: "<<alice_key<<endl;
	cout<<"Bob key: "<<bob_key<<endl;
}
