#include<bits/stdc++.h>
using namespace std;

#define DIM_SIZE 5

template<typename T>
void printMatrix(vector<vector<T>> matrix){
	cout<<"=============Printing Matrix====================="<<endl;
	for(int i = 0; i < matrix.size(); i++){
		for(int j = 0; j < matrix[0].size(); j++){
			cout<<(char)(matrix[i][j]+'a')<<" ";
		}
		cout<<endl;
	}
	cout<<"================================================="<<endl;
}

class PlayfairCipher{
private:
	string key;
	vector<vector<int>> keyMatrix;

	void preprocessInput();
	void generateKeyMatrix();
	vector<pair<int, int>> createDigraph(const string &);
	pair<int, int> getPos(int );

public:
	PlayfairCipher(string key){
		this->key = key;
		generateKeyMatrix();
	}

	string encrypt(const string &);
	string decrypt(const string &);

	void setKey(string key){
		this->key = key;
		generateKeyMatrix();
	}
};

/**
	Currently the key matrix skips 'j' as it is traditionally followed.
*/
void PlayfairCipher::generateKeyMatrix(){
	vector<int> hsh(26, 0);
	preprocessInput();
	keyMatrix = vector<vector<int>>(DIM_SIZE, vector<int>(DIM_SIZE));
	int row = 0, col = 0;
	for(auto& it: key){
		if(hsh[it-'a'] == 0){
			keyMatrix[row][col++] = it-'a';
			hsh[it-'a']++;
			if(col == DIM_SIZE){
				col = 0;
				row++;
			}
		}
	}
	for(char c = 'a'; c <= 'z'; c++){
		if(c=='j' and !hsh[c-'a']) continue;
		else if(c=='i' and hsh['j'-'a']) continue;
		if(hsh[c-'a'] == 0){
			keyMatrix[row][col++] = c - 'a';
			if(col == DIM_SIZE){
				col = 0;
				row++;
				if(row == DIM_SIZE) break;
			}
		}
	}
	printMatrix(keyMatrix);
}

/**
	Preprocessing of the input strings plainText and key.
	1. if length of plainText is odd, then it is made even by appending 'z' at the end.
	2. Converting uppercase letters to lowercase.
*/
void PlayfairCipher::preprocessInput(){

	for(auto& it: key){
		if(it>='A' and it<='Z'){
			it += ('a' - 'A');
		}
	}
}

vector<pair<int, int>> PlayfairCipher::createDigraph(const string &plainText){
	string textCache(plainText.begin(), plainText.end());
	if(textCache.size() & 1) textCache += 'z';
	vector<pair<int, int>> digraphList;
	for(int i = 0; i < plainText.size(); i += 2){
		digraphList.push_back({textCache[i], textCache[i+1]});
	}

	return digraphList;
}

pair<int, int> PlayfairCipher::getPos(int c){
	for(int i = 0; i < DIM_SIZE; i++){
		for(int j = 0; j < DIM_SIZE; j++){
			if(keyMatrix[i][j] == c){
				return {i, j};
			}
		}
	}

	return {-1, -1};
}

/**
	Encryption routine of Playfair algorithm
*/
string PlayfairCipher::encrypt(const string &plainText){
	vector<pair<int, int>> digraphList = createDigraph(plainText);
	char enc1, enc2;
	string encryptedText = "";

	for(auto& digraph: digraphList){
		pair<int, int> pos1 = getPos(digraph.first - 'a');
		pair<int, int> pos2 = getPos(digraph.second - 'a');

		if(pos1.first==pos2.first){
			//same row
			enc1 = keyMatrix[pos1.first][(pos1.second+1)%DIM_SIZE];
			enc2 = keyMatrix[pos2.first][(pos2.second+1)%DIM_SIZE];
		}
		else if(pos1.second == pos2.second){
			//same column
			enc1 = keyMatrix[(pos1.first+1)%DIM_SIZE][pos1.second];
			enc2 = keyMatrix[(pos2.first+1)%DIM_SIZE][pos2.second];
		}
		else{
			enc1 = keyMatrix[pos1.first][pos2.second];
			enc2 = keyMatrix[pos2.first][pos1.second];
		}

		encryptedText += (enc1 + 'a'); encryptedText += (enc2+'a');
	}

	return encryptedText;
}

string PlayfairCipher::decrypt(const string &encryptedText){
	vector<pair<int, int>> digraphList = createDigraph(encryptedText);
	char dec1, dec2;
	string decryptedText = "";

	for(auto& digraph: digraphList){
		pair<int, int> pos1 = getPos(digraph.first - 'a');
		pair<int, int> pos2 = getPos(digraph.second - 'a');

		if(pos1.first == pos2.first){
			dec1 = keyMatrix[pos1.first][(pos1.second-1+DIM_SIZE)%DIM_SIZE];
			dec2 = keyMatrix[pos2.first][(pos2.second-1+DIM_SIZE)%DIM_SIZE];
		}
		else if(pos1.second == pos2.second){
			dec1 = keyMatrix[(pos1.first-1+DIM_SIZE)%DIM_SIZE][pos1.second];
			dec2 = keyMatrix[(pos2.first-1+DIM_SIZE)%DIM_SIZE][pos2.second];
		}
		else{
			dec1 = keyMatrix[pos1.first][pos2.second];
			dec2 = keyMatrix[pos2.first][pos1.second];
		}

		decryptedText += (dec1 + 'a'); decryptedText += (dec2 + 'a');
	}

	return decryptedText;
}

int main(){
	string plainText, key;
	cout<<"Enter plainText: ";
	cin>>plainText;
	cout<<"Enter key: ";
	cin>>key;

	bool isOdd = (plainText.size() & 1);

	PlayfairCipher cipher(key);
	string encryptedText = cipher.encrypt(plainText);
	cout<<"ecrypted text: "<<encryptedText<<endl;
	string decryptedText = cipher.decrypt(encryptedText);
	if(isOdd) decryptedText.pop_back();
	cout<<"Decrypted Text: "<<decryptedText<<endl;

	return 0;
}
