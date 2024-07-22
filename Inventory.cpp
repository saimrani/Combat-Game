#include "Inventory.hpp"


/**
 * @param : A Pointer to the Item object to be added to the inventory.
 * @post  : The Item is added to the inventory, preserving the BST structure. The BST property is based on (ascending) alphabetical order of the item's name.
 *          If the item is type UNKNOWN, WEAPON, or ARMOR and is already in the inventory, it is not added.
      However, if another instance of an Item of type CONSUMABLE is being added (an item with the same name), its quantity is updated to the sum of the quantities of the two objects, and the time_picked_up_ variable is updated to that of the latest instance of the item being added.
 * @return true if the item was added to the inventory or updated, false otherwise.
 */
bool Inventory::addItem(Item *Addthisitem)
{
    if (!Addthisitem)
    {
        return false;
    }
    std::shared_ptr<BinaryNode<Item *>> existingNode = findNode(this->getRoot(), Addthisitem);

    if (!existingNode || Addthisitem->getType() == "CONSUMABLE")
    {
        if (existingNode)
        {
            Item *existingItem = existingNode->getItem();
            existingItem->setQuantity(existingItem->getQuantity() + Addthisitem->getQuantity());
            existingItem->setTimePickedUp(Addthisitem->getTimePickedUp());
        }
        else
        {
            this->add(Addthisitem);
        }
        return true;
    }

    return false;
}

/**
 * @param   : A reference to string name of the item to be found.
 * @return  : An Item pointer to the found item, or nullptr if the item is not in the inventory.
 */
Item *Inventory::findItem(const std::string &Findthisitem)
{
    for (std::shared_ptr<BinaryNode<Item *>> getNode = getRoot(); getNode != nullptr;)
    {
        std::string FthisItem = getNode->getItem()->getName();

        if (FthisItem == Findthisitem)
        {
            return getNode->getItem();
        }
        else if (FthisItem < Findthisitem)
        {
            getNode = getNode->getRightChildPtr();
        }
        else
        {
            getNode = getNode->getLeftChildPtr();
        }
    }

    return nullptr;
}

/**
 * @param   : A reference to string name of the item to be removed from the inventory.
 * @return  : True if the item was found and removed or updated successfully, false otherwise.
 * @post    : If the item is found in the inventory, it is removed while preserving the BST structure.
              If a CONSUMABLE is removed, its quantity is decremented by one, but its time_picked_up_
              remains the same. However, if it is the last item (it's quantity is 1 and is being removed),
              the item should be removed. Non-CONSUMABLE items should always be removed when they are found.
 */
bool Inventory::removeItem(const std::string &removethisItem)
{
    Item temporaryItem(removethisItem);
    Item *tempItem_Ptr = &temporaryItem;

    if (!contains(tempItem_Ptr))
        return false;

    std::shared_ptr<BinaryNode<Item *>> pointerToItem = getPointerTo(tempItem_Ptr);
    Item *foundtheItem = pointerToItem->getItem();

    if (!foundtheItem)
        return false;

    if (foundtheItem->getType() == "CONSUMABLE")
    {

        if (foundtheItem->getQuantity() <= 1)
        {
            return remove(foundtheItem);
        }

        foundtheItem->setQuantity(foundtheItem->getQuantity() - 1);
        return true;
    }

    return remove(foundtheItem);
}

/**
 * @return    : The total sum of gold values of all items in the inventory.
                Note: consumable items may have quantity >1 and gold value must be
                      added for each item
 */


/**
 * @post    : The names of all items in the Inventory are printed in ascending order.
 *            This function performs an in-order traversal of the binary search tree and prints the details of each item in the following format.
        NOTE: QUANTITY ONLY NEEDS TO BE DISPLAYED FOR CONSUMABLE ITEMS.

 *            [NAME] ([TYPE])
              Level: [LEVEL]
              Value: [VALUE]
              Quantity: [QUANTITY]

              Example:
              TIRED GAUNTLETS (ARMOR)
              Level: 3
              Value: 25

              SMALL HEALTH POTION (CONSUMABLE)
              Level: 1
              Value: 10
              Quantity: 2
 *
 */

int Inventory::getTotalGoldValue() const
{
    int totalGoldValue = 0;

    // Perform in-order traversal and sum up gold values
    std::stack<std::shared_ptr<BinaryNode<Item *>>> stack;
    std::shared_ptr<BinaryNode<Item *>> current = getRoot();

    while (current != nullptr || !stack.empty())
    {
        while (current != nullptr)
        {
            stack.push(current);
            current = current->getLeftChildPtr();
        }

        current = stack.top();
        stack.pop();

        // Accumulate gold values
        totalGoldValue += (current->getItem()->getQuantity() > 0) ? current->getItem()->getQuantity() * current->getItem()->getGoldValue() : current->getItem()->getGoldValue();

        current = current->getRightChildPtr();
    }

    return totalGoldValue;
}

void Inventory::printInventoryInOrder() const {
    printInOrderHelper(getRoot());
}

void Inventory::printInOrderHelper(std::shared_ptr<BinaryNode<Item *>> node) const {
    if (node != nullptr) {
        // Traverse left subtree
        printInOrderHelper(node->getLeftChildPtr());

        // Print details of the current item
        std::cout << node->getItem()->getName() << " (" << node->getItem()->getType() << ")\n";
        std::cout << "Level: " << node->getItem()->getLevel() << "\n";
        std::cout << "Value: " << node->getItem()->getGoldValue() << "\n";

        // Display quantity for consumable items
        if (node->getItem()->getType() == "CONSUMABLE") {
            std::cout << "Quantity: " << node->getItem()->getQuantity() << "\n";
        }

        std::cout << "\n";

        // Traverse right subtree
        printInOrderHelper(node->getRightChildPtr());
    }
}



/**
    * This is for Above
    * @param   : A pointer to an item contained within the BST.
    * @post    : All of the information forn the items.
        NOTE: QUANTITY ONLY NEEDS TO BE DISPLAYED FOR CONSUMABLE ITEMS:

        NOODLES (CONSUMABLE)
        Level: 0
        Value: 120
        Quantity: 5
    */

/**
 * @param   : a reference to bool if the items are to be printed in ascending order. 
 * @param   : a reference to string attribute which defines the order by which the items are to be printed. You may assume that the given parameter will be in one of the following forms: ["NAME"/"TYPE"/"LEVEL"/"VALUE"/"TIME"]
 * @post    : All items in the Inventory are printed in the order specified by the parameter.
 *          Example usage: inventory.printInventory(false, "LEVEL");
            NOTE: QUANTITY ONLY NEEDS TO BE DISPLAYED FOR CONSUMABLE ITEMS:

            FEATHER DUSTER (WEAPON)
            Level: 5
            Value: 100

            TIRED GAUNTLETS (ARMOR)
            Level: 3
            Value: 50

            SMALL HEALTH POTION (CONSUMABLE)
            Level: 1
            Value: 10
            Quantity: 2

            NOODLES (CONSUMABLE)
            Level: 0
            Value: 120
            Quantity: 5
 */



#include <queue>

void Inventory::printInventory(bool ascendingOrder, const std::string &attribute) {
    // Create a comparator function based on the attribute
    auto comparator = [ascendingOrder, attribute](const Item *item1, const Item *item2) {
        if (attribute == "NAME") {
            return ascendingOrder ? item1->getName() > item2->getName() : item1->getName() < item2->getName();
        } else if (attribute == "TYPE") {
            return ascendingOrder ? item1->getType() > item2->getType() : item1->getType() < item2->getType();
        } else if (attribute == "LEVEL") {
            return ascendingOrder ? item1->getLevel() > item2->getLevel() : item1->getLevel() < item2->getLevel();
        } else if (attribute == "VALUE") {
            return ascendingOrder ? item1->getGoldValue() > item2->getGoldValue() : item1->getGoldValue() < item2->getGoldValue();
        } else if (attribute == "TIME") {
            return ascendingOrder ? item1->getTimePickedUp() > item2->getTimePickedUp() : item1->getTimePickedUp() < item2->getTimePickedUp();
        }
        return false; // Default case
    };

    // Create a priority queue of items
    std::priority_queue<Item *, std::vector<Item *>, decltype(comparator)> itemQueue(comparator);

    // Perform in-order traversal and add items to the priority queue
    std::stack<std::shared_ptr<BinaryNode<Item *>>> stack;
    std::shared_ptr<BinaryNode<Item *>> current = getRoot();

    while (current != nullptr || !stack.empty()) {
        while (current != nullptr) {
            stack.push(current);
            current = current->getLeftChildPtr();
        }

        current = stack.top();
        stack.pop();

        itemQueue.push(current->getItem());

        current = current->getRightChildPtr();
    }

    // Print items from the priority queue
    while (!itemQueue.empty()) {
        Item *currentItem = itemQueue.top();
        itemQueue.pop();

        // Print details of the current item
        std::cout << currentItem->getName() << " (" << currentItem->getType() << ")\n";
        std::cout << "Level: " << currentItem->getLevel() << "\n";
        std::cout << "Value: " << currentItem->getGoldValue() << "\n";

        // Display quantity for consumable items
        if (currentItem->getType() == "CONSUMABLE") {
            std::cout << "Quantity: " << currentItem->getQuantity() << "\n";
        }

        std::cout << "\n";
    }
}
