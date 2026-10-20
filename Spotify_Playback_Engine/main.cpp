#include <iostream>
#include<windows.h>
#include<list>
#include<unordered_map>
#include<fstream>
#include<string>
#include<thread>
#include<chrono>

using namespace std;

class Playback_Engine{
public:
    struct Song {
        public:
        string singer;
        string song_name;
    };
    class Node{
    public:
        Song sd; //song details
        Node* next;
        Node* prev;
        string key;
        Node(string s , string song){
            sd.singer = s;
            sd.song_name = song;
        }
    };

    Node* head = new Node("0","0");
    Node* tail = new Node("0","0");

    Node* currentTrack = head->next;

    int limit = 5;                    //Max 5 songs in a playlist for now

    Playback_Engine(){
        head->next = tail;
        tail->prev = head;
    }

    unordered_map<string,Node*> m;

    string generatekey(string singer, string song){
        return singer + "_" + song;
    }

    void addsong(string singer , string songname){
        string key = generatekey(singer,songname);
        if(m.find(key) != m.end()){
            cout << "✅ Song Already added!" << endl;
            return;
        }
        else{
            if(m.size() == limit){
                m.erase(tail->prev->key);
                //deleting the last song played till now --> LRU
                Node* oldsong = tail->prev;
                oldsong->prev->next = tail;
                tail->prev = oldsong->prev;
            }
            Node* newsong = new Node(singer, songname);
            m[key] = newsong;
            Node* oldsong = head->next;
            head->next = newsong;
            newsong->next = oldsong;
            oldsong->prev = newsong;
            newsong->prev = head;
            currentTrack = newsong;
        }
    }

    void deletesong(string singer, string songname){
        string key = generatekey(singer,songname);
        if(m.find(key) == m.end()){
            cout << "❌ Song does not exist" << endl;
            return;
        }
        Node* oldsong = m[key];
        if(oldsong == currentTrack){
            if(oldsong->next == tail){
                currentTrack = head->next;
            }
            currentTrack = oldsong->next;
        }
        m.erase(key);
        Node* oldprev = oldsong->prev;
        Node* oldnext = oldsong->next;
        oldnext->prev = oldprev;
        oldprev->next = oldnext;
    }

    void nextsong(){
        if(m.empty()){
            cout << "❌ No songs on playlist" << endl;
        }
        else if(currentTrack->next == tail){
            currentTrack = head->next;
        }
        else{
            currentTrack = currentTrack->next;
        }
    }

    void prevsong(){
        if(m.empty()){
            cout << "❌ No songs on playlist" << endl;
        }
        else if(currentTrack->prev == head){
            currentTrack = tail->prev;
        }
        else {
            currentTrack = currentTrack->prev;
        }
    }

    void createplaylist(){
        ofstream file("MyPlaylist.txt");
        cout << "✅ Playlist created successfully!\n" << "Playlist name - MyPlaylist" << endl;
    }

    void saveplaylist(){
        ofstream file("MyPlaylist.txt");
        Node* curr = head->next;
        while(curr != tail){
            file << curr->sd.singer << " | " << curr->sd.song_name << endl;
            curr = curr->next;
        }
        cout << "✅ Playlist saved successfully!" << endl;
        file.close(); // C++ in default closes the file
    }

    void openplaylist(){
        ifstream file("MyPlaylist.txt");
        string singer,songname;
        if(!file){
            cout << "❌ No playlist found" << endl;
        }
        else if(file.eof()){
            cout << "❌ No saved songs on playlist" << endl;
        }
        else{
            while(getline(file,singer,'|') && getline(file,songname)){
                addsong(singer,songname);
            }
            cout << "✅ Playlist Opened Successfully" << endl;
        }
        file.close(); // C++ in default closes the file
    }

    void searchsong(string query){
        Node* curr = head->next;
        bool found = false;
        if(m.empty()){
            cout << "❌ No song in the playlist" << endl;
        }
        while(curr != tail){
            if(curr->sd.singer.find(query) != string::npos || curr->sd.song_name.find(query) != string::npos){
                cout << "---------------------------------" << endl;
                cout << "✅ Song Found!" << endl;
                cout << "🎧 Singer: " << curr->sd.singer << endl;
                cout << "🎧 Song: " << curr->sd.song_name << endl;
                cout << "---------------------------------" << endl;
                found = true;
            }
            curr = curr->next;
        }
        if(!found){
            cout << "❌ Song not found!" << endl;
        }

        return;
    }

    void display(){
        cout << "=================================================" << endl;
        if(m.empty()){
            cout << " " << endl;
        }
        if(!m.empty()){
            cout << "🎵 Playlist -->" << endl;
        }
        Node* curr = head->next;
        while(curr != tail){
            cout << "---------------------------------" << endl;
            cout << "🎧 Singer: " << curr->sd.singer << endl;
            cout << "🎧 Song: " << curr->sd.song_name << endl;
            cout << "---------------------------------" << endl;
            curr = curr->next;
        }


        cout << "=================================================" << endl;
        if(!m.empty()){
            cout << "🎤 Current Song Playing--> " << "\nSinger: " << currentTrack->sd.singer << "\nSong: " << currentTrack->sd.song_name << endl;
        }
        cout << "=================================================" << endl;
    }

};

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    cout << "=================================================" << endl;
    cout << "🟢 Spotify" << endl;
    cout << "=================================================" << endl;
    cout << "Options->" << endl;
    cout << "Type 1 to create playlist.\nType 2 to add new song.\nType 3 to delete a song.\nType 4 to jump to next song.\nType 5 to play previous song.\nType 6 to save the playlist.\nType 7 to open the playlist.\nType 8 to search a song.\nType 9 to exit." << endl;
    cout << "=================================================" << endl;

    int option;
    string singer,songname;

    string query;

    int songplayed = 0;

    Playback_Engine* music = new Playback_Engine(); // or simply Playback_Engine music and use '.' before methods instead of ->
    while(true){
        music->display();
        cout << "Select an option" << endl;
        cin >> option;
        cin.ignore(); //getline reads till next line is encountered. now as we type option and press enter, getline thinks its an end and skips the singer input
        if(option == 1){
                music->createplaylist();
        }
        else if(option == 2){
            cout << "Enter the singer name: " << endl;
            getline(cin,singer);
            cout << "Enter the song name: " << endl;
            getline(cin,songname);
            music->addsong(singer, songname);

        }
        else if(option == 3){
            cout << "Enter the singer name: " << endl;
            getline(cin,singer);
            cout << "Enter the song name: " << endl;
            getline(cin,songname);
            music->deletesong(singer, songname);
        }
        else if(option == 4){
            music->nextsong();
            songplayed++;
            if(songplayed%3 == 0){
                cout << "=================================================" << endl;
                cout << "📢 Upgrade to get ad-less music.\nYour song will be back in 3s." << endl;
                cout << "=================================================" << endl;
                Sleep(3000);
                //songplayed = 0;
            }
        }
        else if(option == 5){
            music->prevsong();
            songplayed++;
            if(songplayed%3 == 0){
                cout << "=================================================" << endl;
                cout << "📢 Upgrade to get ad-less music.\nYour song will be back in 3s." << endl;
                cout << "=================================================" << endl;
                Sleep(3000);
                //songplayed = 0;
            }
        }
        else if(option == 6){
            music->saveplaylist();
        }
        else if(option == 7){
            music->openplaylist();
        }
        else if(option == 8){
            cout << "Enter the singer or song name: " << endl;
            getline(cin,query);
            music->searchsong(query);
        }
        else if(option == 9){
            cout << "Exited Successfully!" << endl;
            break;
        }
        else{
            cout <<"Invalid option selected" << endl;
            break;
        }

    }
}
