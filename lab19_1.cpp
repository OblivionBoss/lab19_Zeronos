#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstring>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned int i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source;
    source.open(filename);
    string textline;
    char word[100];
    int a,b,c,s;
    while(getline(source,textline)){
        string row = textline;
        char *hword = new char[row.size()+1];
        char format[] = "%[^:]: %d %d %d";
        strcpy(hword,row.c_str());
        sscanf(hword,format,word,&a,&b,&c);
        s = a+b+c;
        names.push_back(word);
        scores.push_back(s);
        grades.push_back(score2grade(s));
    }
}

void getCommand(string &command,string &key){
    cout << "Please input your command: ";
    cin >> command;
    if(toUpperStr(command) == "NAME" or toUpperStr(command) == "GRADE"){
        cin.ignore();
        getline(cin,key);
    }
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
    bool check = false;
    for (int i = 0; i < 33; i++) {
        cout << "-";
    }
    cout << "\n";

    for (unsigned int i = 0; i < names.size(); i++) {
        if(toUpperStr(key) == toUpperStr(names.at(i))){
            check = true;
            cout << names.at(i) << "'s score = " << scores.at(i) << "\n";
            cout << names.at(i) << "'s grade = " << grades.at(i) << "\n";
        }
    }
    if(check == false){
        cout << "Cannot found.\n";
    }

    for (int i = 0; i < 33; i++) {
        cout << "-";
    }
    cout << "\n";
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){
    bool check = false;
    const char *p = toUpperStr(key).c_str();
    for (int i = 0; i < 33; i++) {
        cout << "-";
    }
    cout << "\n";

    for (unsigned int i = 0; i < grades.size(); i++) {
        if(*p == grades.at(i)){
            check = true;
            cout << names.at(i) << " (" << scores.at(i) << ")\n";
        }
    }
    if(check == false){
        cout << "Cannot found.\n";
    }

    for (int i = 0; i < 33; i++) {
        cout << "-";
    }
    cout << "\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}