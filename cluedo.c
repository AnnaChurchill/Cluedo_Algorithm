#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN (20)
#define TOTAL_CARDS (9+6+6)
#define CARDS_IN_ENV (3)
#define CARDS_IN_ENQU (3)
#define NUM_WEAPONS (6)
#define NUM_ROOMS (9)
#define NUM_CHARACTERS (6)


enum card_type{character, weapon, room};
char weapons[NUM_WEAPONS][NAME_LEN] = {"candlestick", "dagger", "leadpipe", "revolver", "rope", "wrench"};
char rooms[NUM_ROOMS][NAME_LEN] = {"kitchen", "ballroom", "conservatory", "diningroom", "billiardroom", "library", "lounge", "hall", "study"};
char characters[NUM_CHARACTERS][NAME_LEN] = {"scarlett", "green", "mustard", "plum", "peacock", "white"};

struct player {
    char name[NAME_LEN];
    int num_cards;
    int num_cards_found;
    struct card ** cards_found;
    int num_cards_not_owned;
    struct card ** cards_not_owned;
    
    // struct player ** possible_owners; //this is for not_envelope to use
    // int num_possible_owners;
};

struct card {
    enum card_type type;
    struct player * owner;
    char name[NAME_LEN];
};

// struct tri_rule {
//     struct player * p;
//     // struct card * card1;
//     // struct card * card2;
//     // struct card * card3;
//     struct card ** cards;
//     int num_cards = 3;
// };

// struct bi_rule {
//     struct player * p;
//     // struct card * card1;
//     // struct card * card2;
//     struct card ** cards;
//     int num_cards = 2;
// };

struct rule {
    struct player * player;
    struct card ** cards;
    int num_cards;
};

struct game {
    // struct tri_rule ** tri_rules;
    // int num_tri_rules;
    // struct bi_rule ** bi_rules;
    // int num_bi_rules;
    struct card ** cards;
    struct rule ** rules;
    int num_rules;
    struct card ** cards_unknown;
    int num_cards_unknown;
    struct player ** players;
    int num_players;
    struct player * envelope;
    // struct player ** not_envelope; // for cards that you know they are not in the envelope but someone owns them
    // int num_not_envelope;
};


void card_setup(struct game * g) {

    g->num_cards_unknown = TOTAL_CARDS;
    g->cards = (struct card **) malloc(sizeof(struct car *)*TOTAL_CARDS);
    g->cards_unknown = (struct card **) malloc(sizeof(struct car *)*TOTAL_CARDS);

    for (int i = 0; i < NUM_WEAPONS; i++) {

        g->cards_unknown[i] = (struct card *) malloc(sizeof(struct card));
        g->cards_unknown[i]->type = weapon;
        g->cards_unknown[i]->owner = NULL;
        strcpy(g->cards_unknown[i]->name, weapons[i]);
        g->cards[i] = g->cards_unknown[i];
    }

    for (int i = 0; i < NUM_ROOMS; i++) {

        g->cards_unknown[NUM_WEAPONS+i] = (struct card *) malloc(sizeof(struct card));
        g->cards_unknown[NUM_WEAPONS+i]->type = room;
        g->cards_unknown[NUM_WEAPONS+i]->owner = NULL;
        strcpy(g->cards_unknown[NUM_WEAPONS+i]->name, rooms[i]);
        g->cards[NUM_WEAPONS+i] = g->cards_unknown[NUM_WEAPONS+i];
    }

    for (int i = 0; i < NUM_CHARACTERS; i++) {

        g->cards_unknown[NUM_WEAPONS+NUM_ROOMS+i] = (struct card *) malloc(sizeof(struct card));
        g->cards_unknown[NUM_WEAPONS+NUM_ROOMS+i]->type = character;
        g->cards_unknown[NUM_WEAPONS+NUM_ROOMS+i]->owner = NULL;
        strcpy(g->cards_unknown[NUM_WEAPONS+NUM_ROOMS+i]->name, characters[i]);
        g->cards[NUM_WEAPONS+NUM_ROOMS+i] = g->cards_unknown[NUM_WEAPONS+NUM_ROOMS+i];
    }


    return;

}


void deal(struct game * g) {

    int cards_left = TOTAL_CARDS-CARDS_IN_ENV;

    int cards_per_person = cards_left/g->num_players;
    
    for (int i = 0; i < g->num_players; i++) {
        g->players[i]->num_cards = cards_per_person;
        g->players[i]->num_cards_found = 0;
    }

    for (int i = 0; i < cards_left%g->num_players; i++) {
        g->players[i]->num_cards++;
    }

    return;
}

struct card * get_card(char name[NAME_LEN], struct game * g) {

    
    for (int i = 0; i < TOTAL_CARDS; i++) {
        // printf("5 : %s, %s\n", name, g->cards_unknown[i]->name);
        if (strcmp(name, g->cards[i]->name) == 0) {
            // printf("6\n");
            return g->cards[i];
        }
    }

    printf("not found!\n");
    printf("|");
    printf("%s",name);
    printf("|\n");
    return NULL;
}

void owner_found(struct game * g, struct card * c, struct player * p) {


    c->owner = p;

    if (p->num_cards_found == 0) {
        p->cards_found = (struct card **) malloc(sizeof(struct card *));
    }
    else {
        p->cards_found = (struct card **) realloc(p->cards_found, sizeof(struct card *)*(p->num_cards_found+1));
    }
    p->cards_found[p->num_cards_found] = c;
    p->num_cards_found++;

    struct card ** new_unknown = (struct card **) malloc(sizeof(struct card *)*(g->num_cards_unknown-1));
    int found = 0;
    for (int i = 0; i < g->num_cards_unknown-1; i++) {
        if (strcmp(c->name, g->cards_unknown[i]->name) == 0) {
            found = 1;
        }
        new_unknown[i] = g->cards_unknown[i+found];

    }
    
    free(g->cards_unknown);
    g->cards_unknown = new_unknown;
    g->num_cards_unknown--;

    return;
}

void my_cards(struct game * g, struct player * me) {

    printf("Please enter all the cards you have:\n");

    char new_card[NAME_LEN];
    struct card * focus_card;

    for (int i = 0; i < me->num_cards; i++) {

        // printf("4\n");
        fscanf(stdin, "%s", new_card);
        focus_card = get_card(new_card, g);

        focus_card->owner = me;

        owner_found(g, focus_card, me);

    }
}


void print_info(struct game * g) {

    printf("\n____________________________\n\n");

    for (int i = 0; i < g->num_players; i++) {
        printf("%s:\n",g->players[i]->name);
        for (int ii = 0; ii < g->players[i]->num_cards_found; ii++) {
            printf("%s\t",g->players[i]->cards_found[ii]->name);
        }
        for (int ii = 0; ii < g->players[i]->num_cards-g->players[i]->num_cards_found; ii++) {
            printf("?\t");
        }
        printf("\n\n");
    }


    printf("____________________________\n\n");

    printf("ENVELOPE:\n");
    for (int i = 0; i < g->envelope->num_cards_found; i++) {
        // if (g->envelope->cards_found[i] == NULL) {
        //     printf("?\t");
        // }
        // else {
        printf("%s\t",g->envelope->cards_found[i]->name);
        // }
    }
    for (int i = 0; i < CARDS_IN_ENV - g->envelope->num_cards_found; i++) {
        printf("?\t");
    }


    printf("\n\n____________________________\n\n");



    return;
}


struct player * get_player(char name[NAME_LEN], struct game * g) {

    for (int i = 0; i < g->num_players; i++) {
        if (strcmp(name, g->players[i]->name) == 0) {
            return g->players[i];
        }
    }

    printf("That is not a player in this game. Please input again: ");
    return get_player(fgets(name, NAME_LEN, stdin), g);

}

// checks if player has cards in their "not owned list"
int not_owned(struct player * p, struct card * c) {
    for (int i = 0; i < p->num_cards_not_owned; i++) {
        if (strcmp(c->name, p->cards_not_owned[i]->name) == 0) {
            return 1;
        }
    }
    return 0;
}


void create_rule(struct game * g, struct player * p, struct card ** cards, int num_cards) {
    
    // printf("1\n");
    int cards_unassigned = num_cards;
    for (int i = 0; i < num_cards; i++) {
        if (cards[i]->owner != NULL || not_owned(p, cards[i])) {
            if (strcmp(cards[i]->owner->name, p->name) == 0) {
                return;
            }
            else {
                cards_unassigned--;
            }
        }
    }
    // printf("2\n");
    if (cards_unassigned == 1) {
        for (int i = 0; i < num_cards; i++) {
            if (cards[i]->owner == NULL) {
                owner_found(g, cards[i], p);
            }
        }
    }
    // printf("3\n");
    else {
        struct rule * new_rule = (struct rule *) malloc(sizeof(struct rule));
    new_rule->player = p;
    new_rule->cards = (struct card **) malloc(sizeof(struct card *)*cards_unassigned);
    new_rule->num_cards = cards_unassigned;
    // printf("4\n");
    int one_found = 0;
    for (int i = 0; i < cards_unassigned; i++) {
        if (cards[i]->owner != NULL) {
            one_found = 1;
        }
        new_rule->cards[i] = cards[i+one_found];
    }
    // printf("5\n");
    if (g->num_rules == 0) {
        g->rules = (struct rule **) malloc(sizeof(struct rule *));
    }
    else {
        g->rules = (struct rule **) realloc(g->rules, sizeof(struct rule *)*(g->num_rules+1));
    }
    g->rules[g->num_rules] = new_rule;
    g->num_rules++;
    }
    
    // printf("6\n");
    return;
    
}

// void has_none(struct game * g, struct player * p, struct card ** cards, int num_cards) {
//     for (int i = 0; i < num_cards; i++) {
//         if (p->num_cards_not_owned == 0) {
//             p->cards_not_owned = (struct card **) malloc(sizeof(struct card *));
//         }
//         else {
//             p->cards_not_owned = (struct card **) realloc(p->cards_not_owned, sizeof(struct card *)*(p->num_cards_not_owned+1));
//         }
//         p->cards_not_owned[p->num_cards_not_owned] = cards[i];
//         p->num_cards_not_owned++;
//     }

//     return;
// }

void enact_rules(struct game * g) {

    int i = 0;
    int rule_eliminated;
    int ii;
    while (i < g->num_rules) {
        printf("a\n");
        rule_eliminated = 0;
        ii = 0;
        while (ii < g->rules[i]->num_cards) {
            printf("b\n");
            if ((g->rules[i]->cards[ii]->owner != NULL && strcmp(g->rules[i]->cards[ii]->owner->name, g->rules[i]->player->name) != 0) || not_owned(g->rules[i]->player, g->rules[i]->cards[ii])) { // if we know player does not own card
                printf("o, num cards = %d\n",g->rules[i]->num_cards);
                if (g->rules[i]->num_cards == 3) { // have to check who owner is
                    printf("w\n");
                    struct card ** new_cards = (struct card **) malloc(sizeof(struct card *)*2);
                    int found = 0;
                    for (int iii = 0; iii < 2; iii++) {
                        printf("y\n");
                        if (ii == iii) {
                            printf("p\n");
                            found = 1;
                        }
                        new_cards[iii] = g->rules[i]->cards[iii+found];
                    }
                    free(g->rules[i]->cards);
                    g->rules[i]->cards = new_cards;
                    g->rules[i]->num_cards--;
                    printf("m\n");
                }

                else if (g->rules[i]->num_cards == 2) {
                    printf("s\n");
                    // if (strcmp(g->rules[i]->cards[ii]->owner->name, g->rules[i]->player->name) != 0) {
                    owner_found(g, g->rules[i]->cards[(ii+1)%2], g->rules[i]->player);
                    // }

                    rule_eliminated = 1;
                    break;
                }

                else {
                    printf("problem! nunmber of cards is %d\n", g->rules[i]->num_cards);
                    return;
                }

                printf("d\n");
            }
            
            else if (g->rules[i]->cards[ii]->owner != NULL && strcmp(g->rules[i]->cards[ii]->owner->name, g->rules[i]->player->name) == 0){
                rule_eliminated = 1;
                break;
                printf("z\n");
            }

            else {
                ii++;
                printf("x\n");
            }
        }
        printf("e\n");
        if (rule_eliminated) {
                    struct rule ** new_rules = (struct rule **) malloc(sizeof(struct rule *)*(g->num_rules-1));
                    int found = 0;
                    for (int iii = 0; iii < g->num_rules; iii++) {
                        if (i == iii) {
                            found = 1;
                        }
                    new_rules[iii] = g->rules[iii+found];
                    }
                    free(g->rules);
                    g->rules = new_rules;
                    g->num_rules--;
                }

        else {
            i++;
        }
        printf("f\n");
    }
}



void clean_game(struct game * g) {
    // free each player
    free(g->players);
    free(g);
}

int main() {

    struct game * g = (struct game *) malloc(sizeof(struct game));
    g->envelope = (struct player *) malloc(sizeof(struct player));
    g->envelope->num_cards = CARDS_IN_ENV;
    g->envelope->num_cards_found = 0;
    // g->num_not_envelope = 0;
    g->num_cards_unknown = TOTAL_CARDS;
    // g->num_bi_rules = 0;
    // g->num_tri_rules = 0;
    g->num_rules = 0;

    card_setup(g);

    printf("\n\nWelcome to Cluedo!\n\n");

    printf("Number of players: ");
    scanf("%d", &(g->num_players));
    g->players = (struct player **) malloc(sizeof(struct player *)*g->num_players);


    printf("Please enter their names in the order they were dealt the cards: \n");
    for (int i = 0; i < g->num_players; i++) {
        g->players[i] = (struct player *) malloc(sizeof(struct player));
        fscanf(stdin, "%s", g->players[i]->name);
        g->players[i]->num_cards_found = 0;
        g->players[i]->num_cards_not_owned = 0;
    }

    deal(g);


    struct player * focus_player;
    char focus_player_name[NAME_LEN];

    print_info(g);

    printf("Please enter your name: ");
    fscanf(stdin, "%s", focus_player_name);
    focus_player = get_player(focus_player_name, g);

    my_cards(g, focus_player);

    print_info(g);

    // struct card * char_card;
    // struct card * weap_card;
    // struct card * room_card;
    char char_name[NAME_LEN];
    char weap_name[NAME_LEN];
    char room_name[NAME_LEN];
    struct card ** cards = (struct card **) malloc(sizeof(struct card *)*CARDS_IN_ENQU);


    printf("Please input the first inquiry:\n");
    printf("Player asked: ");
    fscanf(stdin, "%s", focus_player_name);
    focus_player = get_player(focus_player_name, g);

    printf("Character: ");
    fscanf(stdin, "%s", char_name);
    cards[0] = get_card(char_name, g);

    printf("Weapon: ");
    fscanf(stdin, "%s", weap_name);
    cards[1] = get_card(weap_name, g);

    printf("Room: ");
    fscanf(stdin, "%s", room_name);
    cards[2] = get_card(room_name, g);

    

    create_rule(g, focus_player, cards, CARDS_IN_ENQU);
    enact_rules(g);
    print_info(g);

    // char pass_through[NAME_LEN];
    // printf("Did the rule pass through anyone? (y/n) ");
    // fscanf(stdin, "%s", pass_through);
    // if (strcmp(pass_through, "y") == 0) {

    // }









    return 0;
}








