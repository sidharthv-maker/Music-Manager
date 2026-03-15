#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../headerfiles/music.h"
bool song_in_master_library(const char *song, const char *artist, const char *filename) {
    FILE *fp = fopen(filename, "r");
    char line[1200];
    char file_song[1000], file_artist[1000];
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';
        char *sep = strstr(line, ", by ");
        if (sep != NULL) {
            *sep = '\0';  
            strcpy(file_song, line); 
            strcpy(file_artist, sep + 5);
            if (strcmp(file_song, song) == 0 && strcmp(file_artist, artist) == 0) {
                fclose(fp);
                return true;
            }
        }
    }
    fclose(fp);
    return false;
}
void command_log(const int command) {
    FILE* logfile = fopen("command.txt", "a");
    fprintf(logfile, "Command: %d\n", command);
    fclose(logfile);
}
void print_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    char line[1000];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    fclose(fp);
}
void clear_file(const char* filename) {
    FILE *fp = fopen(filename, "w");
    if (fp) fclose(fp);
    extern masterll *phead;
    masterll *a = phead;
    while (a != NULL) {
        album *s = a->songs;
        while (s != NULL) {
            album *tmpS = s->next;
            free(s);
            s = tmpS;
        }
        masterll *tempA = a->next;
        free(a);
        a = tempA;
    }
    phead = NULL;
}
void library_log(const char* text) {
    FILE *fp = fopen(text, "w");
    masterll *alb = phead;
    while(alb != NULL) {
        fprintf(fp, "ALBUM:%s\n", alb->planame);
        album* s = alb->songs;
        while(s != NULL) {
            fprintf(fp, "SONG:%s|%s\n", s->song, s->artist);
            s=s->next;
        }
        fprintf(fp, "--------------------\n");
        alb = alb->next;
    }
    fclose(fp);
}
void load_from_playlist(const char *filename) {
    FILE *fp = fopen(filename, "r");
    char line[512];
    masterll *current_album = NULL;
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';
        if (strncmp(line, "ALBUM:", 6) == 0) {
            char *p = line + 6;
            while (*p == ' ') p++;
            char album_name[256];
            strncpy(album_name, p, sizeof(album_name));
            album_name[sizeof(album_name)-1] = '\0';
            masterll *found = playsea(album_name);
            if (found == NULL) {
                add_album(album_name);
                found = playsea(album_name);
            }
            current_album = found;
        }
        else if (strncmp(line, "SONG:", 5) == 0) {
            if (!current_album) {
                continue;
            }
            char *p = line + 5;
            char *divider = NULL;
            for (char *q = p; *q != '\0'; q++) {
                if (*q == '|') { divider = q; break; }
            }
            if (!divider) {
                continue;
            }
            *divider = '\0';
            divider++;
            char song_name[256], artist_name[256];
            strncpy(song_name, p, sizeof(song_name));
            song_name[sizeof(song_name)-1] = '\0';
            song_name[strcspn(song_name, "\n")] = '\0';
            strncpy(artist_name, divider, sizeof(artist_name));
            artist_name[sizeof(artist_name)-1] = '\0';
            artist_name[strcspn(artist_name, "\n")] = '\0';
            add_song_to_album(song_name, artist_name, current_album);
        }
        else if (strncmp(line, "-----", 5) == 0) {
            current_album = NULL;
        }
    }
    fclose(fp);
}
