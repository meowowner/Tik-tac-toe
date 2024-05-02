#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class player{
public:
int Id;
string Sign;
player(int id, string sign){
	this->Id = id;
	this->Sign = sign;
}
int Wins = 0;
int Draws = 0;
int Loses = 0;
int Points = 0;
void show(){
cout << Id << "   " << Sign << "    " << Wins << "    " << Draws << "     " << Loses << "     " << Points << endl;
}
};

int menu(){
cout << "1 - show table" << endl;
cout << "2 - show results" << endl;
cout << "3 - show player stats" << endl;
cout << "4 - exit" << endl;
cout << "Choose option:" << endl;
int option;
cin >> option;
return option;
}

void results(){
ifstream tictactoe;
tictactoe.open("tictactoe.txt");
if (!tictactoe.is_open()){
	cout << "Failed to open the file" << endl;
	return;
} else {
	string line;
	while(getline(tictactoe, line)){
		cout << line << endl;
}
tictactoe.close();
}
return;
}

int load(vector<player> *vec){
ifstream players;
players.open("players.txt");
if (!players.is_open()){
	cout << "Failed to open the file" << endl;
	return -1;
} else {
	string line;
	string idstr;
	int id;
	string sign;
	while(getline(players, line)){
		if (line.length() != 0){
			idstr = line.substr(0,6);
			id = stoi(idstr);
			//cout << id << endl;
			sign = line.substr(7,1);
			//cout << sign << endl;
		}
		player n(id,sign);
		vec->emplace_back(n);
	}
players.close();
}
return 0;
}

int is_winner(vector<int> vec){
for(int i = 0; i < vec.size(); i++){
switch(vec[i]){
	case 1:	
	if (( find(vec.begin(), vec.end(), 2) != vec.end()) && ( find(vec.begin(), vec.end(), 3) != vec.end()))
	return 0;
	if (( find(vec.begin(), vec.end(), 5) != vec.end()) && ( find(vec.begin(), vec.end(), 9) != vec.end()))
	return 0;
	if (( find(vec.begin(), vec.end(), 4) != vec.end()) && ( find(vec.begin(), vec.end(), 7) != vec.end()))
	return 0;
	break;

	case 2:
	if (( find(vec.begin(), vec.end(), 5) != vec.end()) && ( find(vec.begin(), vec.end(), 8) != vec.end()))
	return 0;
	break;
	
	case 3:
	if (( find(vec.begin(), vec.end(), 6) != vec.end()) && ( find(vec.begin(), vec.end(), 9) != vec.end()))
	return 0;
	if (( find(vec.begin(), vec.end(), 5) != vec.end()) && ( find(vec.begin(), vec.end(), 7) != vec.end()))
	return 0;
	break;
	
	case 4:
	if (( find(vec.begin(), vec.end(), 5) != vec.end()) && ( find(vec.begin(), vec.end(), 6) != vec.end()))
	return 0;
	break;
	
	case 7:
	if (( find(vec.begin(), vec.end(), 8) != vec.end()) && ( find(vec.begin(), vec.end(), 9) != vec.end()))
	return 0;
	break;
}
}

/*
cout << "Winner";
for(int i = 0; i < vec.size(); i++)
cout << vec[i];
cout << endl;
*/


return 1;
}

void validate(vector<player> *vec, string line1, string line2, string line3){
	char char1 = '.';
	char char2 = '.';
	string line[3];
	
	/*
	cout << line1 << endl;
	cout << line2 << endl;
	cout << line3 << endl;
	*/

	line[0] = line1;
	line[1] = line2;
	line[2] = line3;
	vector<int> pos1;
	vector<int> pos2;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(line[i][j] != '.'){
				if((char1 != '.')&&(char1 != line[i][j])){
					char2 = line[i][j];
				} else {
					char1 = line[i][j];
				}
				if(line[i][j] == char1){
					pos1.emplace_back(3*i+j+1);
				}
				if(line[i][j] == char2){
					pos2.emplace_back(3*i+j+1);
				}
			}
		}
	}
	
	/*
	for(int i = 0; i < pos1.size(); i++)
	cout << pos1[i];
	cout << endl;
	for(int i = 0; i < pos2.size(); i++)
	cout << pos2[i];
	cout << endl;
	*/


	if((is_winner(pos1) == 1)&&(is_winner(pos2) == 1)){
		for(int i = 0; i < vec->size(); i++){
			if(vec[0][i].Sign[0] == char1){
				vec[0][i].Draws++;
			}
			if(vec[0][i].Sign[0] == char2){
				vec[0][i].Draws++;
			}
		}
	} else if (is_winner(pos1) == 0){
		for(int i = 0; i < vec->size(); i++){
			if(vec[0][i].Sign[0] == char1){
				vec[0][i].Wins++;
			}
			if(vec[0][i].Sign[0] == char2){
				vec[0][i].Loses++;
			}
		}
	} else if (is_winner(pos2) == 0){
		for(int i = 0; i < vec->size(); i++){
			if(vec[0][i].Sign[0] == char2){
				vec[0][i].Wins++;
			}
			if(vec[0][i].Sign[0] == char1){
				vec[0][i].Loses++;
			}
		}
	}
return;
}

int load_results(vector<player> *players){
ifstream tictactoe;
tictactoe.open("tictactoe.txt");
if (!tictactoe.is_open()){
	cout << "Failed to open the file" << endl;
	return -1;
} else {
	string line;
	string line1, line2, line3;
	for(int i=1; getline(tictactoe, line);i++){
	i = i%4;
	if(line.length() != 0){
		switch (i){
			case 1: line1 = line;
			break;
			case 2: line2 = line;
			break;
			case 3: line3 = line;
			validate(players, line1, line2, line3);			
			break;
			default: cout << "Error: issue with file tictactoe.txt" << endl;
			break;
		}
	}
	}

}
tictactoe.close();
return 0;	
}

int main(){
vector<player> players;
int res = load(&players);
if (res != 0){
cout << "Couldn't open file" << endl;
return 0;
}
load_results(&players);

int loop = 1;
while (loop == 1){
int option = menu();
switch (option){
	case 1:
		cout << "  Id   Sign Wins Draws Loses Points" << endl;
		for(int i = 0; i < players.size();i++){
			players[i].show();
		}
		break;
	case 2:
		results();
		break;
	case 3:
		int input_id;
		cout << "Enter player id: ";
		cin >> input_id;
		for(int i = 0; i < players.size();i++){
			if(input_id == players[i].Id){
				players[i].show();
			}
		}
		
		break;
	case 4:
	loop = 0;
		break;
	default:
	loop = 0;
		break;
}
//cout << option << endl;
}
return 0;
}
