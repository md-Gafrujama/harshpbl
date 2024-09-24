#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Song {
    char title[50];
    char artist[50];
    struct Song* next;
};

struct Song* createSong(char* title, char* artist) {
    struct Song* newSong = (struct Song*)malloc(sizeof(struct Song));
    strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    newSong->next = NULL;
    return newSong;
}

void addSong(struct Song** head, char* title, char* artist) {
    struct Song* newSong = createSong(title, artist);
    if (*head == NULL) {
        *head = newSong;
    } else {
        struct Song* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newSong;
    }
    printf("Song \"%s\" by %s added to the playlist.\n", title, artist);
}

void deleteSong(struct Song** head, char* title) {
    struct Song* temp = *head;
    struct Song* prev = NULL;
    if (temp != NULL && strcmp(temp->title, title) == 0) {
        *head = temp->next;
        free(temp);
        printf("Song \"%s\" deleted from the playlist.\n", title);
        return;
    }
    while (temp != NULL && strcmp(temp->title, title) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Song \"%s\" not found in the playlist.\n", title);
        return;
    }
    prev->next = temp->next;
    free(temp);
    printf("Song \"%s\" deleted from the playlist.\n", title);
}

void displayPlaylist(struct Song* head) {
    if (head == NULL) {
        printf("The playlist is empty.\n");
        return;
    }
    struct Song* temp = head;
    printf("\nMusic Playlist:\n");
    while (temp != NULL) {
        printf("Title: %s, Artist: %s\n", temp->title, temp->artist);
        temp = temp->next;
    }
}

int countSongs(struct Song* head) {
    int count = 0;
    struct Song* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void displayShuffledPlaylist(struct Song* head, struct Song* currentSong) {
    if (head == NULL) {
        printf("The playlist is empty.\n");
        return;
    }
    struct Song* temp = head;
    printf("\nShuffled Playlist:\n");
    while (temp != NULL) {
        if (temp == currentSong) {
            printf("-> Now Playing: \"%s\" by %s\n", temp->title, temp->artist); // Highlight current song
        } else {
            printf("   Title: %s, Artist: %s\n", temp->title, temp->artist);
        }
        temp = temp->next;
    }
}

void shufflePlaylist(struct Song** head, struct Song** currentSong) {
    int count = countSongs(*head);
    if (count < 2) {
        printf("Not enough songs to shuffle.\n");
        return;
    }

    srand(time(NULL));
    struct Song* temp = *head;
    struct Song* prev = NULL;
    for (int i = 0; i < count * 3; i++) {
        int r = rand() % count;
        temp = *head;
        prev = NULL;
        for (int j = 0; j < r; j++) {
            prev = temp;
            temp = temp->next;
        }
        if (prev != NULL) {
            prev->next = temp->next;
            temp->next = *head;
            *head = temp;
        }
    }
    *currentSong = *head;  // Update current playing song after shuffle
    printf("Playlist shuffled.\n");

    // Display shuffled playlist with current song highlighted
    displayShuffledPlaylist(*head, *currentSong);
}

void playCurrentSong(struct Song* currentSong) {
    if (currentSong == NULL) {
        printf("No song is currently playing.\n");
    } else {
        printf("\nNow Playing: \"%s\" by %s\n", currentSong->title, currentSong->artist);
    }
}

void freePlaylist(struct Song* head) {
    struct Song* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Song* playlist = NULL;
    struct Song* currentSong = NULL;
    int choice;
    char title[50];
    char artist[50];

    while (1) {
        printf("\n--- Music Playlist Manager ---\n");
        printf("1. Add Song\n");
        printf("2. Delete Song\n");
        printf("3. Display Playlist\n");
        printf("4. Shuffle Playlist\n");
        printf("5. Play Current Song\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter song title: ");
                scanf(" %[^\n]s", title);
                printf("Enter artist name: ");
                scanf(" %[^\n]s", artist);
                addSong(&playlist, title, artist);
                break;
            case 2:
                printf("Enter song title to delete: ");
                scanf(" %[^\n]s", title);
                deleteSong(&playlist, title);
                if (currentSong != NULL && strcmp(currentSong->title, title) == 0) {
                    currentSong = playlist;  // Reset current song if deleted
                }
                break;
            case 3:
                displayPlaylist(playlist);
                break;
            case 4:
                shufflePlaylist(&playlist, &currentSong);
                break;
            case 5:
                playCurrentSong(currentSong);
                break;
            case 6:
                freePlaylist(playlist);
                printf("Exiting Playlist Manager.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
