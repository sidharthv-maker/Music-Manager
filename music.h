#ifndef MUSIC_H
#define MUSIC_H
#include <stdbool.h>
typedef struct album {
    char song[1000];
    char artist[1000];
    struct album* next;
} album;
typedef struct masterll {
    char planame[200];
    album *songs;
    struct masterll* next;
} masterll;
typedef struct queue {
    char song[1000];
    char artist[1000];
    bool current;
    bool playing;
    struct queue* next;
} queue;
extern masterll *phead;
extern queue *qhead;
album *songsea(char* song, char* artist, masterll *p);
masterll *playsea(char* planame);
void add_album(char* planame);
void add_song_to_album(char* song, char* artist, masterll *p);
void remove_song_from_album(char* song, char* artist, masterll *p);
void print_albums();
void print_songs(masterll *p);
void print_all();
void library_log(const char* text);
void add_song_to_queue(char* song, char* artist);
void remove_song_from_queue(char* song, char* artist);
int  queue_length();
queue *qsea(char* song, char* artist);
void play_song_from_queue(char* song, char* artist);
void print_queue();
void curr_song();
void play_queue();
void play_next();
void play_prev();
void pause_playback();
void resume_playback();
void status();
bool song_in_master_library(const char *song, const char *artist, const char *filename);
void command_log(const int command);
void print_file(const char *filename);
void clear_file(const char* filename);
void load_from_playlist(const char *filename);
#endif
