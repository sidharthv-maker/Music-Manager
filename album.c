#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headerfiles/music.h"
masterll *phead = NULL;
album *songsea(char* song, char* artist, masterll *p) {
    album *s = p->songs;
    while(s != NULL) {
        if(strcmp(s->song,song) == 0 && strcmp(s->artist,artist) == 0) {
            return s;
        }
        s = s->next;
    }
    return NULL;
}
masterll *playsea(char* planame) {
    masterll *dummy = phead;
    while(dummy != NULL) {
        if(strcmp(dummy->planame, planame) == 0) {
            return dummy;
        }
        dummy = dummy->next;
    }
    return NULL;
}
void add_album(char* planame) {
    masterll *alb = malloc(sizeof(masterll));
    strcpy(alb->planame,planame);
    alb->songs = NULL;
    alb->next = NULL;
    if(phead == NULL) {
        phead = alb;
    } else {
        masterll *temp = phead;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = alb;
    }
}
void add_song_to_album(char* song, char* artist, masterll *p) {
    album *s = malloc(sizeof(album));
    strcpy(s->song, song);
    strcpy(s->artist,artist);
    s->next = NULL;
    if(p->songs==NULL) {
        p->songs = s;
    } else {
        album* temp = p->songs;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = s;
    }
}
void remove_song_from_album(char* song, char* artist, masterll *p) {
    album *curr = p->songs;
    album *prev = NULL;
    while(curr != NULL) {
        if(strcmp(curr->song, song) == 0 && strcmp(curr->artist, artist) == 0) {
            if(prev == NULL) {
                p->songs = p->songs->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}
void print_albums() {
    masterll *temp = phead;
    while(temp != NULL) {
        printf("%s\n", temp->planame);
        temp = temp->next;
    }
}
void print_songs(masterll *p) {
    album *s = p->songs;
    while(s != NULL) {
        printf("%s,by %s\n", s->song, s->artist);
        s=s->next;
    }
}
void print_all() {
    FILE *fp = fopen("masterfile.txt", "r");
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}
