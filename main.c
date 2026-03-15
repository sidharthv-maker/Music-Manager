#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headerfiles/music.h"
int main() {
    load_from_playlist("playlist.txt");
    printf("Welcome to C Unplugged!\n");
    printf("This is your own music manager application.\n");
    printf("Here are the list of all the commands you can implement.\n");
    printf("Note: The codes corresponding to each function are the serial numbers associated with them\n");
    printf("1.Adding a new album to your music library.\n");
    printf("2.Adding a new song to an existing album.\n");
    printf("3.Removing a song from an album.\n");
    printf("4.Displaying all albums in your music library.\n");
    printf("5.Displaying all songs inside a selected album.\n");
    printf("6.Adding a song to the current play queue.\n");
    printf("7.Removing a song from the current play queue.\n");
    printf("8.Calculating the total number of songs in the play queue.\n");
    printf("9.Playing a specific song chosen from the queue.\n");
    printf("10.Displaying which song is currently playing.\n");
    printf("11.Playing all songs in the queue sequentially.(Note that since this is a text-driven music manager, you have to command previous or next for the queue to continue moving)\n");
    printf("12.Skipping to the next song in the queue.\n");
    printf("13.Going back to the previous song in the queue.\n");
    printf("14.Printing all the songs currently in queue\n");
    printf("15.Pausing the currently playing song.\n");
    printf("16.Resuming playback of the paused song.\n");
    printf("17.Showing the overall playback status\n");
    printf("18.Print out the Command Log\n");
    printf("19.Print out the list of all the albums and songs in the albums already existing\n");
    printf("20.Clear the Command Log\n");
    printf("21.Clear the Library of already existing Albums and songs\n");
    printf("22. Print all the songs in the masterfile\n");
    printf("0. To exit the music manager\n");
    printf("Enter your command here:\n");
    printf("(Enter a number from 0 to 22)\n");
    printf("For adding the song A, by a, there might be an error saying that the given song is not in the libary.\n");
    printf("Its an error which occurs when you are trying to run this program on Linux, please try adding other song!\n");
    int l = 1;
    while(l>0) {
        int n;
        scanf("%d%*c", &n);
        command_log(n);
        if(n != 0) {
            l++;
        }
        if(n==0) {
            printf("Thank you for using C Unplugged. See you again!\n");
        } else if(n==1) {
            char planame[200];
            printf("Enter the name of the album you want to create\n");
            fgets(planame,sizeof(planame),stdin);
            planame[strcspn(planame,"\n")] = '\0';
            add_album(planame);
            library_log("playlist.txt");
            printf("An empty album of your given choice has been created. Feel free to add songs to your album!\n");
        } else if(n==2) {
            printf("Enter the name of the song you want to add\n");
            char song[1000];
            fgets(song,sizeof(song),stdin);
            song[strcspn(song,"\n")] = '\0';
            printf("Enter the name of the artist of the song\n");
            char artist[1000];
            fgets(artist,sizeof(artist),stdin);
            artist[strcspn(artist,"\n")] = '\0';
            if (song_in_master_library(song, artist, "masterfile.txt") == false) {
                printf("The song %s by %s is not present in the master song library. Please choose a valid song.\n",
                       song, artist);
            } else {
                printf("Enter the name of the album you want to add the song into\n");
                char planame[200];
                fgets(planame,sizeof(planame),stdin);
                planame[strcspn(planame,"\n")] = '\0';
                masterll *x = playsea(planame);
                if(x == NULL) {
                    printf("Such an album does not exist\n");
                } else {
                    add_song_to_album(song,artist,x);
                    library_log("playlist.txt");
                    printf("The song %s by %s has been added to the album %s.\n", song, artist, planame);
                }
            }
        } else if(n==3) {
            printf("Enter the name of the song you want to remove\n");
            char song[1000];
            fgets(song,sizeof(song),stdin);
            song[strcspn(song,"\n")] = '\0';

            printf("Enter the name of the artist of the song\n");
            char artist[1000];
            fgets(artist,sizeof(artist),stdin);
            artist[strcspn(artist,"\n")] = '\0';

            printf("Enter the name of the album you want to remove the song from\n");
            char planame[200];
            fgets(planame,sizeof(planame),stdin);
            planame[strcspn(planame,"\n")] = '\0';

            masterll *x = playsea(planame);
            if(x == NULL) {
                printf("Such an album does not exist\n");
            } else {
                album *y = songsea(song,artist,x);
                if(y == NULL) {
                    printf("The given song doesn't exist in the given album\n");
                } else {
                    remove_song_from_album(song,artist,x);
                    library_log("playlist.txt");
                    printf("The song %s by %s has been removed from the album %s.\n", song, artist, planame);
                }
            }
        } else if(n==4) {
            printf("Here are a list of all the albums you have saved in C Unplugged:\n");
            print_albums();
        } else if(n==5) {
            printf("Enter the name of the album you want to display\n");
            char planame[200];
            fgets(planame,sizeof(planame),stdin);
            planame[strcspn(planame,"\n")] = '\0';

            masterll *x = playsea(planame);
            if(x == NULL) {
                printf("Such an album does not exist\n");
            } else {
                printf("Here is the list of all the songs in %s\n", planame);
                print_songs(x);
            }
        } else if(n==6) {
            printf("Enter the name of the song you want to add to queue\n");
            char song[1000];
            fgets(song,sizeof(song),stdin);
            song[strcspn(song,"\n")] = '\0';

            printf("Enter the name of the artist of the song\n");
            char artist[1000];
            fgets(artist,sizeof(artist),stdin);
            artist[strcspn(artist,"\n")] = '\0';

            add_song_to_queue(song,artist);
        } else if(n==7) {
            printf("Enter the name of the song you want to remove from the queue\n");
            char song[1000];
            fgets(song,sizeof(song),stdin);
            song[strcspn(song,"\n")] = '\0';

            printf("Enter the name of the artist of the song\n");
            char artist[1000];
            fgets(artist,sizeof(artist),stdin);
            artist[strcspn(artist,"\n")] = '\0';

            remove_song_from_queue(song,artist);
        } else if(n==8) {
            int x = queue_length();
            printf("The length of the current queue is %d\n", x);
        } else if(n==9) {
            printf("Enter the name of the song you want to play\n");
            char song[1000];
            fgets(song,sizeof(song),stdin);
            song[strcspn(song,"\n")] = '\0';

            printf("Enter the name of the artist of the song\n");
            char artist[1000];
            fgets(artist,sizeof(artist),stdin);
            artist[strcspn(artist,"\n")] = '\0';

            play_song_from_queue(song,artist);
            printf("\n");
        } else if(n==10) {
            curr_song();
            printf("\n");
        } else if(n==11) {
            play_queue();
            printf("\n");
        } else if(n==12) {
            play_next();
            printf("\n");
        } else if(n==13) {
            play_prev();
            printf("\n");
        } else if(n==14) {
            print_queue();
        } else if(n==15) {
            pause_playback();
            printf("\n");
        } else if(n==16) {
            resume_playback();
            printf("\n");
        } else if(n==17) {
            status();
            printf("\n");
        } else if(n==18) {
            print_file("command.txt");
        } else if(n==19) {
            print_file("playlist.txt");
        } else if(n==20) {
            clear_file("command.txt");
        } else if(n==21) {
            clear_file("playlist.txt");
        } else if(n==22) {
            print_all();
        } else {
            printf("Please enter a number between 0 and 22\n");
        }
        l--;
    }
    return 0;
}
