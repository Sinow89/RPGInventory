typedef struct item_t{
    char name[MAX_NAME];
    int gold;
    int rarity;
    float kilo;
    int received_order;
    int in_inventory;
} item_t;

item_t items[400];

int get_hash(char *name) {
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++){
        hash_value += name[i];
    }
    return hash_value % 400;
}

// O (1)
bool check_if_item_in_inventory(char *name) {
    if (items[get_hash(name)].in_inventory > 0) {
        return true;
    }
}

// O (n)
bool check_if_item_in_inventory(char *name) {
    for (int i = 0; i < 10000; i++) {
        if (items[i].in_inventory > 0) {
            if (strcmp(items[i].name, name) == 0) {
                return true;
            }
        }
    }
}