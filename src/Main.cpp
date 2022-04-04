#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <sstream>
#include <string>
#include <openssl/sha.h>
#include <unordered_map>
using namespace std;

string sha256(const string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

string random32str() {
	string str("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~");

	random_device rd;
	mt19937 generator(rd());

	shuffle(str.begin(), str.end(), generator);
	return(str.substr(0, 32));
}

void newUser() {
	string username;
	cout << "Enter username: ";
	cin >> username;

	string password;
	cout << "Enter password: ";
	cin >> password;

	string salt = random32str();
	string toHash = password + salt;

	ofstream users;
	users.open("users.txt", ios::app);

	users << username << endl;
	users << salt << endl;
	users << sha256(toHash) << endl;

	users.close();
}

void login() {
	string username;
	cout << "Enter username: ";
	cin >> username;

	string password;
	cout << "Enter password: ";
	cin >> password;



	ifstream users;
	users.open("users.txt");
	if (users.fail()) {
		cout << "ERROR: COULD NOT OPEN \"users.txt\"!";
		exit(1);
	}

	string name;
	string salt;
	string hash;

	unordered_map<string, string> nameToHash;
	unordered_map<string, string> nameToSalt;

	string data;
	int line = 0;
	while (getline(users, data)) {
		switch (line) {
			case 0:
				name = data;
				break;
			case 1:
				salt = data;
				break;
			case 2:
				hash = data;
				break;
		}


		line++;
		if (line == 3) {
			nameToHash[name] = hash;
			nameToSalt[name] = salt;

			line = 0;
		}
	}

	string hashTest;
	hashTest = sha256(password + nameToSalt[username]);

	if (hashTest == nameToHash[username]) {
		cout << "SUCCESS!" << endl;
	}
	else {
		cout << "FAIL" << endl;
	}

	users.close();

	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	(void) getchar();
}

int main() {
	int selection;
	cout << "SHA-256 SALTED LOGIN SYSTEM\n========================\n(1) New user\n(2) Login Check" << endl;
	cin >> selection;

	switch (selection) {
		case 1:
			newUser();
			break;
		case 2:
			login();
			break;
	}
}