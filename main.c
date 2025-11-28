#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    const char *title;
    const char *industry;
    const char *type;
    const char *genre;
    const char *rating;
} Item;

void typeText(const char *text, int delay_ms) {
    int i = 0;
    while (text[i] != '\0') {
        putchar(text[i]);
        fflush(stdout);
        usleep(delay_ms * 1000);
        i++;
    }
}

void toLowerStr(char *s) {
    int i = 0;
    while (s[i] != '\0') {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = s[i] - 'A' + 'a';
        }
        i++;
    }
}

void normalizeGenre(char *g) {
    toLowerStr(g);
    if (strcmp(g, "romantic") == 0) strcpy(g, "romance");
    else if (strcmp(g, "scifi") == 0 || strcmp(g, "sci") == 0) strcpy(g, "sci-fi");
    else if (strcmp(g, "animation") == 0) strcpy(g, "animated");
}

const char* getGenreCodes(const char *genre) {
    if (strcmp(genre, "action") == 0) return "43048, 7442, 9584";
    if (strcmp(genre, "romance") == 0) return "8883, 502675, 99184";
    if (strcmp(genre, "horror") == 0) return "89585, 10695, 8711";
    if (strcmp(genre, "comedy") == 0) return "9302, 869, 1402";
    if (strcmp(genre, "thriller") == 0) return "43048, 46588, 9147";
    if (strcmp(genre, "sci-fi") == 0) return "1568, 47147, 2729";
    if (strcmp(genre, "drama") == 0) return "5763, 11714, 384";
    if (strcmp(genre, "fantasy") == 0) return "1568, 47147, 67903";
    if (strcmp(genre, "mystery") == 0) return "9994, 8646, 1039";
    if (strcmp(genre, "crime") == 0) return "9584, 5824, 26146";
    if (strcmp(genre, "animated") == 0) return "11881, 2653, 452";
    if (strcmp(genre, "adventure") == 0) return "7442, 10702, 2125";
    return "N/A";
}

#define MOVIE_COUNT 24
#define SERIES_COUNT 24

Item movieSuggestions[MOVIE_COUNT] = {
    {"An Action Hero", "Bollywood", "Movie", "action", "7.0/10"},
    {"John Wick", "Hollywood", "Movie", "action", "7.4/10"},
    {"Sita Ramam", "Bollywood", "Movie", "romance", "8.6/10"},
    {"Jerry Maguire", "Hollywood", "Movie", "romance", "7.3/10"},
    {"Stree", "Bollywood", "Movie", "horror", "7.5/10"},
    {"The Conjuring", "Hollywood", "Movie", "horror", "7.5/10"},
    {"Ready", "Bollywood", "Movie", "comedy", "5.6/10"},
    {"This Is the End", "Hollywood", "Movie", "comedy", "6.6/10"},
    {"Drishyam", "Bollywood", "Movie", "thriller", "8.2/10"},
    {"Shutter Island", "Hollywood", "Movie", "thriller", "8.2/10"},
    {"Krrish", "Bollywood", "Movie", "sci-fi", "6.8/10"},
    {"Interstellar", "Hollywood", "Movie", "sci-fi", "8.6/10"},
    {"Dil Se", "Bollywood", "Movie", "drama", "7.6/10"},
    {"The Green Mile", "Hollywood", "Movie", "drama", "8.6/10"},
    {"Brahmastra", "Bollywood", "Movie", "fantasy", "5.5/10"},
    {"Harry Potter and the Philosopher's Stone", "Hollywood", "Movie", "fantasy", "7.6/10"},
    {"Kahaani", "Bollywood", "Movie", "mystery", "8.1/10"},
    {"Knives Out", "Hollywood", "Movie", "mystery", "7.9/10"},
    {"Gangs of Wasseypur", "Bollywood", "Movie", "crime", "8.2/10"},
    {"The Dark Knight", "Hollywood", "Movie", "crime", "9.0/10"},
    {"Hanuman", "Bollywood", "Movie", "animated", "7.0/10"},
    {"Spider-Man: Into the Spider-Verse", "Hollywood", "Movie", "animated", "8.4/10"},
    {"Karwaan", "Bollywood", "Movie", "adventure", "7.5/10"},
    {"Zathura", "Hollywood", "Movie", "adventure", "6.2/10"}
};

Item seriesSuggestions[SERIES_COUNT] = {
    {"Special OPS", "Bollywood", "Series", "action", "8.5/10"},
    {"The Boys", "Hollywood", "Series", "action", "8.7/10"},
    {"Little Things", "Bollywood", "Series", "romance", "8.2/10"},
    {"Bridgerton", "Hollywood", "Series", "romance", "7.4/10"},
    {"Ghoul", "Bollywood", "Series", "horror", "7.0/10"},
    {"The Haunting of Hill House", "Hollywood", "Series", "horror", "8.6/10"},
    {"Panchayat", "Bollywood", "Series", "comedy", "8.9/10"},
    {"Brooklyn Nine-Nine", "Hollywood", "Series", "comedy", "8.4/10"},
    {"Delhi Crime", "Bollywood", "Series", "thriller", "8.4/10"},
    {"Money Heist", "Hollywood", "Series", "thriller", "8.2/10"},
    {"OK Computer", "Bollywood", "Series", "sci-fi", "6.0/10"},
    {"Stranger Things", "Hollywood", "Series", "sci-fi", "8.7/10"},
    {"Made in Heaven", "Bollywood", "Series", "drama", "8.0/10"},
    {"Breaking Bad", "Hollywood", "Series", "drama", "9.5/10"},
    {"The Legend of Hanuman", "Bollywood", "Series", "fantasy", "8.5/10"},
    {"Game of Thrones", "Hollywood", "Series", "fantasy", "9.2/10"},
    {"Asur", "Bollywood", "Series", "mystery", "8.4/10"},
    {"Sherlock", "Hollywood", "Series", "mystery", "9.1/10"},
    {"Sacred Games", "Bollywood", "Series", "crime", "8.5/10"},
    {"Narcos", "Hollywood", "Series", "crime", "8.8/10"},
    {"Motu Patlu", "Bollywood", "Series", "animated", "7.1/10"},
    {"Arcane", "Hollywood", "Series", "animated", "9.0/10"},
    {"The Forgotten Army", "Bollywood", "Series", "adventure", "7.5/10"},
    {"The Witcher", "Hollywood", "Series", "adventure", "8.1/10"}
};

void printItemWithCodes(const Item *it) {
    const char *codes = getGenreCodes(it->genre);
    typeText("\nDr. Z: Here is a suggestion for you...\n", 40);
    printf("Title   : %s\n", it->title);
    printf("Industry: %s\n", it->industry);
    printf("Type    : %s\n", it->type);
    printf("Genre   : %s\n", it->genre);
    printf("Rating  : %s\n", it->rating);
    printf("Netflix code for genre \"%s\" : %s\n\n", it->genre, codes);
}

void randomSuggestions(const char *type) {
    const Item *arr;
    int size;
    if (strcmp(type, "movie") == 0) {
        arr = movieSuggestions;
        size = MOVIE_COUNT;
    } else {
        arr = seriesSuggestions;
        size = SERIES_COUNT;
    }

    int used[32] = {0};
    int shown = 0;
    char again;

    typeText("\nDr. Z: Random, hmm?\n", 40);
    typeText("Dr. Z: Wow. Taking the easy shortcut because your indecisiveness is truly impressive.\n", 40);
    typeText("Dr. Z: Fine. I’ll do the thinking since you clearly refuse to.\n", 40);

    while (1) {
        if (shown == size) {
            typeText("Dr. Z: You have seen every suggestion I can offer.\n", 40);
            typeText("Dr. Z: Do something else now, you have other important work to attend.\n", 40);
            typeText("Dr. Z: Visit the library again soon.\n", 40);
            return;
        }

        int idx;
        do {
            idx = rand() % size;
        } while (used[idx]);

        used[idx] = 1;
        shown++;

        printItemWithCodes(&arr[idx]);

        printf("Do you want another suggestion? (y/n): ");
        scanf(" %c", &again);

        if (again != 'y' && again != 'Y') {
            typeText("\nDr. Z: Very well. Enough recommendations for today.\n", 40);
            typeText("Dr. Z: Visit the library again soon.\n", 40);
            return;
        }
    }
}

void showSpecificSuggestions(const char *type, const char *genre) {
    const Item *arr;
    int size;
    if (strcmp(type, "movie") == 0) {
        arr = movieSuggestions;
        size = MOVIE_COUNT;
    } else {
        arr = seriesSuggestions;
        size = SERIES_COUNT;
    }

    const Item *bol = NULL;
    const Item *hol = NULL;

    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i].genre, genre) == 0) {
            if (strcmp(arr[i].industry, "Bollywood") == 0) bol = &arr[i];
            else if (strcmp(arr[i].industry, "Hollywood") == 0) hol = &arr[i];
        }
    }

    if (bol == NULL && hol == NULL) {
        typeText("Dr. Z: I have nothing in that genre yet. Tragic.\n", 40);
        return;
    }

    const char *codes = getGenreCodes(genre);

    typeText("\nDr. Z: Here is what I found for your refined taste...\n", 40);

    if (bol != NULL) {
        printf("\n[Bollywood]\n");
        printf("Title   : %s\n", bol->title);
        printf("Industry: %s\n", bol->industry);
        printf("Type    : %s\n", bol->type);
        printf("Genre   : %s\n", bol->genre);
        printf("Rating  : %s\n", bol->rating);
    }

    if (hol != NULL) {
        printf("\n[Hollywood]\n");
        printf("Title   : %s\n", hol->title);
        printf("Industry: %s\n", hol->industry);
        printf("Type    : %s\n", hol->type);
        printf("Genre   : %s\n", hol->genre);
        printf("Rating  : %s\n", hol->rating);
    }

    printf("\nNetflix code for genre \"%s\" : %s\n\n", genre, codes);
    typeText("Dr. Z: Visit the library again soon.\n", 40);
}

int main() {
    char type[20];
    char genre[30];
    char choiceType[20];
    int attempts = 0;

    srand(time(NULL));

    printf("=====================================\n");
    printf("   WELCOME TO \"WATCH OR NOT\" LIBRARY\n");
    printf("=====================================\n");

    typeText("Dr. Z: Ah, a new soul has entered my domain...\n", 40);
    typeText("Dr. Z: I am Dr. Z, the keeper of the Entertainment Library.\n", 40);

    while (1) {
        typeText("Dr. Z: Tell me, wanderer... what would you like to watch today?\n", 40);
        printf("Type 'movie' or 'series': ");
        if (scanf("%19s", type) != 1) return 0;
        toLowerStr(type);

        if (strcmp(type, "movie") == 0) {
            typeText("\nDr. Z: A movie, hmm? Short, intense... like a strong espresso shot.\n", 40);
            break;
        } 
        else if (strcmp(type, "series") == 0) {
            typeText("\nDr. Z: A series? Oh... so you have a lot more time to waste, I see.\n", 40);
            break;
        }

        attempts++;

        if (attempts == 1) {
            char buffer[120];
            snprintf(buffer, sizeof(buffer), "\nDr. Z: '%s'? Curious choice...\n", type);
            typeText(buffer, 40);
            typeText("Dr. Z: You are in the wrong library, Padawan. Try again.\n\n", 40);
        }
        else if (attempts == 2) {
            typeText("\nDr. Z: Again wrong.\n", 40);
            typeText("Dr. Z: My patience is thinning… Choose correctly: MOVIE or SERIES.\n\n", 40);
        }
        else {
            typeText("\nDr. Z: That’s it.\n", 40);
            typeText("Dr. Z: I warned you, wanderer.\n", 40);
            typeText("Dr. Z uses FORCE to eliminate you from the library.\n", 40);
            typeText("You get thrown out of Watch or Not.\n", 40);
            return 0;
        }
    }

    typeText("\nDr. Z: Now tell me...\n", 40);
    typeText("Dr. Z: Do you desire a RANDOM suggestion?\n", 40);
    typeText("Dr. Z: Or are you seeking something SPECIFIC?\n", 40);

    printf("Type 'random' or 'specific': ");
    if (scanf("%19s", choiceType) != 1) return 0;
    toLowerStr(choiceType);

    if (strcmp(choiceType, "random") == 0) {
        randomSuggestions(type);
        return 0;
    }

    if (strcmp(choiceType, "specific") != 0) {
        typeText("\nDr. Z: That is neither RANDOM nor SPECIFIC.\n", 40);
        typeText("Dr. Z: Your communication skills are... concerning.\n", 40);
        typeText("Dr. Z: I refuse to continue.\n", 40);
        return 0;
    }

    typeText("\nDr. Z: Very well... a picky traveler.\n", 40);
    typeText("Dr. Z: Choose your poison from the shelf.\n", 40);
    typeText("Dr. Z: You may type:\n", 40);
    typeText("       action, romance, horror, comedy, thriller,\n", 40);
    typeText("       sci-fi, drama, fantasy, mystery, crime,\n", 40);
    typeText("       animated, adventure.\n", 40);

    printf("Genre: ");
    if (scanf("%29s", genre) != 1) return 0;
    normalizeGenre(genre);

    typeText("\n", 40);

    if (strcmp(genre, "action") == 0)
        typeText("Dr. Z: Action? Explosions and chaos to avoid thinking. Respectable choice.\n", 40);
    else if (strcmp(genre, "romance") == 0)
        typeText("Dr. Z: Romance? Looking for love in fiction because reality is… uncooperative? Understandable.\n", 40);
    else if (strcmp(genre, "horror") == 0)
        typeText("Dr. Z: Horror? You enjoy being scared while knowing you can still sleep with the lights on.\n", 40);
    else if (strcmp(genre, "comedy") == 0)
        typeText("Dr. Z: Comedy? Laughing your stress away. Temporary fix, but I approve.\n", 40);
    else if (strcmp(genre, "thriller") == 0)
        typeText("Dr. Z: Thriller? You like your heart rate high and your trust issues higher.\n", 40);
    else if (strcmp(genre, "sci-fi") == 0)
        typeText("Dr. Z: Sci-fi? Future tech and alternate timelines to escape this one. Wise.\n", 40);
    else if (strcmp(genre, "drama") == 0)
        typeText("Dr. Z: Drama? Emotional chaos that isn’t yours for once. Therapeutic.\n", 40);
    else if (strcmp(genre, "fantasy") == 0)
        typeText("Dr. Z: Fantasy? Dragons and magic instead of emails and deadlines. Good choice.\n", 40);
    else if (strcmp(genre, "mystery") == 0)
        typeText("Dr. Z: Mystery? You want to feel clever connecting dots everyone else misses.\n", 40);
    else if (strcmp(genre, "crime") == 0)
        typeText("Dr. Z: Crime? Watching bad decisions so you don’t have to make them. Efficient.\n", 40);
    else if (strcmp(genre, "animated") == 0)
        typeText("Dr. Z: Animated? Colorful pictures carrying heavier emotions than your real life. Impressive.\n", 40);
    else if (strcmp(genre, "adventure") == 0)
        typeText("Dr. Z: Adventure? You crave quests, but also your bed. Relatable energy.\n", 40);
    else {
        char buf[200];
        snprintf(buf, sizeof(buf), "Dr. Z: '%s'? Not in the official collection, but your chaos is noted.\n", genre);
        typeText(buf, 40);
        typeText("Dr. Z: I have no formal recommendations for that… yet.\n", 40);
        return 0;
    }

    showSpecificSuggestions(type, genre);

    return 0;
}

