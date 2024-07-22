#include <iostream>
#include "Inventory.cpp"

int main() {
    // Creating an inventory
    Inventory inventory;

    // Creating items
    Item sword("Sword", WEAPON, 5, 50, 1);
    Item potion("Health Potion", CONSUMABLE, 1, 10, 3);
    Item armor("Steel Armor", ARMOR, 3, 75, 1);
    Item bread("Bread", CONSUMABLE, 1, 5, 5);

    // Adding items to the inventory
    inventory.addItem(&sword);
    inventory.addItem(&potion);
    inventory.addItem(&armor);
    inventory.addItem(&bread);

    // Printing the inventory in ascending order
    std::cout << "Inventory in ascending order:\n";
    inventory.printInventoryInOrder();

    return 0;
}
