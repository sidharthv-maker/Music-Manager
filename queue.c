#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headerfiles/music.h"
queue *qhead = NULL;
queue *qsea(char* song, char* artist) {
    queue *q = qhead;
    while(q != NULL) {
        if(strcmp(q->song,song) == 0 && strcmp(q->artist,artist) == 0) {
            return q;
        }
        q = q->next;
    }
    return NULL;
}
void add_song_to_queue(char* song, char* artist) {
    masterll *dummy = phead;
    while(dummy != NULL) {
        album *x = songsea(song,artist,dummy);
        if(x != NULL) {
            queue *temp = malloc(sizeof(queue));
            strcpy(temp->song,song);
            strcpy(temp->artist,artist);
            temp->current = false;
            temp->playing = false;
            temp->next = NULL;

            if(qhead == NULL) {
                qhead = temp;
            } else {
                queue *temp1 = qhead;
                while(temp1->next != NULL) {
                    temp1 = temp1->next;
                }
                temp1->next = temp; 
            }
            printf("The song %s by %s is added to the Queue.\n", song, artist);
            return;
        }
        dummy = dummy->next;
    } 
    printf("The given song by the given artist doesn't exist in any of the albums.\n");
}

void remove_song_from_queue(char* song, char* artist) {
    queue *curr = qhead;
    queue *prev = NULL;
    while(curr != NULL) {
        if(strcmp(curr->song, song) == 0 && strcmp(curr->artist, artist) == 0) {
            if(prev == NULL) {
                qhead = qhead->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            printf("The song %s by %s has been removed from the queue.\n", song, artist);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("The song %s by %s is not in the queue.\n", song, artist);
}

int queue_length() {
    queue *temp = qhead;
    int count = 0;
    while(temp!=NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}
void play_song_from_queue(char* song, char* artist) {
    queue *a = qsea(song,artist);
    if(a == NULL) {
        printf("Song not in queue. Please add it to queue to play it.\n");
    } else {
        queue *t = qhead;
        while (t) {
            t->current = false;
            t->playing = false;
            t = t->next;
        }
        printf("Now playing %s by %s.\n", a->song, a->artist);
        a->current = true;
        a->playing = true;
    }
}
void print_queue() {
    queue *q = qhead;
    while(q != NULL) {
        printf("%s by %s\n", q->song, q->artist);
        q = q->next;
    }
}
void curr_song() {
    queue *q = qhead;
    while(q!=NULL) {
        if(q->current == true) {
            printf("Current song is %s by %s\n", q->song, q->artist);
            return;
        }
        q = q->next;
    }
    printf("No song is currently being played. Please play a song from the queue.\n");
}
void play_queue() {
    queue *q = qhead;
    if (q == NULL) {
        printf("Queue is empty. Add songs to the queue first.\n");
        return;
    }
    queue *t = qhead;
    while (t) {
        t->current = false;
        t->playing = false;
        t = t->next;
    }
    q->current = true;
    q->playing = true;
    printf("Now playing: %s by %s", q->song, q->artist);
}
void play_next() {
    if(qhead == NULL) {
        printf("Nothing in the queue yet. Please add songs to the queue.\n");
        return;
    }
    queue *tail = qhead;
    while(tail->next != NULL) {
        tail = tail->next;
    }
    if(qhead->current == true) {
        if(qhead->next == NULL) {
            qhead->current = true;
            qhead->playing = true;
            printf("The current song playing is %s by %s", qhead->song, qhead->artist);
            return;
        }
        qhead->next->current = true;
        qhead->next->playing = true;
        qhead->current = false;
        qhead->playing = false;
        printf("The current song playing is %s by %s", qhead->next->song, qhead->next->artist);
        return;
    } 
    else if(tail->current == true) {
        qhead->current = true;
        qhead->playing = true;
        tail->current = false;
        tail->playing = false;
        printf("The current song playing is %s by %s", qhead->song, qhead->artist);
        return;
    } else {
        queue *dummy = qhead;
        queue *prev = NULL;
        queue *q = NULL;
        while(dummy->next != NULL) {
            if(dummy->next->current == true) {
                q = dummy->next;
                prev = dummy;
                break;
            }
            dummy = dummy->next;
        }
        if (!q) {
            printf("No current song set.Please play a song first.\n");
            return;
        }
        q->next->current = true;
        q->next->playing = true;
        q->current = false;
        q->playing = false;
        printf("The current song playing is %s by %s", q->next->song, q->next->artist);
    }
}
void play_prev() {
    if(qhead == NULL) {
        printf("Nothing in the queue yet. Please add songs to the queue.\n");
        return;
    }
    queue *q = qhead;
    queue *dummy = qhead;
    queue *prev = NULL;
    queue *tail = qhead;
    while(tail->next != NULL) {
        tail = tail->next;
    }
    if(tail->current == true) {
        queue *second_last = qhead;
        if (second_last->next == NULL) {
            printf("The current song playing is %s by %s", tail->song, tail->artist);
            return;
        }
        while(second_last->next != tail) {
            second_last = second_last->next;
        }
        second_last->current = true;
        second_last->playing = true;
        tail->current = false;
        tail->playing = false;
        printf("The current song playing is %s by %s", second_last->song, second_last->artist);
        return;
    }
    if(qhead->current == true) {
        qhead->current = false;
        qhead->playing = false;
        tail->current = true;
        tail->playing = true;
        printf("The current song playing is %s by %s", tail->song, tail->artist);
        return;
    }
    while(dummy->next != NULL) {
        if(dummy->next->current == true) {
            q = dummy->next;
            prev = dummy;
            break;
        }
        dummy = dummy->next;
    }
    q->current = false;
    q->playing = false;
    prev->current = true;
    prev->playing = true;
    printf("The current song playing is %s by %s", prev->song, prev->artist);
}
void pause_playback() {
    if(qhead == NULL) {
        printf("No songs in the queue.\n");
        return;
    }
    queue *q = qhead;
    while(q != NULL && !q->current) {
        q = q->next;
    }
    if(q == NULL) {
        printf("No song is currently selected.\n");
        return;
    }
    if(q->playing == false) {
        printf("The song is already paused\n");
    } else {
        q->playing = false;
        printf("The song %s by %s is paused\n", q->song, q->artist);
    }
}
void resume_playback() {
    if(qhead == NULL) {
        printf("No songs in the queue.\n");
        return;
    }
    queue *q = qhead;
    while(q != NULL && !q->current) {
        q = q->next;
    }
    if(q == NULL) {
        printf("No song is currently selected.\n");
        return;
    }
    if(q->playing == true) {
        printf("The song is already resumed\n");
    } else {
        q->playing = true;
        printf("The song %s by %s is resumed\n", q->song, q->artist);
    }
}
void status() {
    if(qhead == NULL) {
        printf("No songs in the queue.\n");
        return;
    }
    queue *q = qhead;
    while(q != NULL && !q->current) {
        q = q->next;
    }
    if(q == NULL) {
        printf("No song is currently selected.\n");
        return;
    }
    if(q->playing == false) {
        printf("The song %s by %s is paused\n", q->song, q->artist);
    } else {
        printf("The song %s by %s is playing\n", q->song, q->artist);
    }
}
