#include <iostream>
#include <limits>
using namespace std;

enum class Options
{
  ADD_ITEM = 1,
  VIEW_ITEMS,
  SEARCH_ITEM,
  UPDATE_ITEM,
  DELETE_ITEM,
  EXIT_INVENTORY,
};

string Amazon::name = "Amazon Inventory";
string Amazon::address = "410 Terry Avenue North, Seattle, Washington, 98109";
string Amazon::country = "United States of America";
string Amazon::phone_number = "+1 206 2661000";
string Amazon::website_url = "www.amazon.com";

class Amazon
{
  class Product
  {
  private:
    string title;
  };

public:
  static string name, address, country, phone_number, website_url;
  void add_item();
  void view_all_items();
  void search_item_by_name();
  void update_item();
  void delete_item();
  void save_to_file();
  void load_from_file();
};

void addItem()
{
  cout << "Add item";
}

void searchItem()
{
  cout << "{Search item}";
}

void viewItems()
{
  cout << "{view item}";
}

void updateItem()
{
  cout << "{update item}";
}

void deleteItem()
{
  cout << "delete item";
}

int main()
{
  int choice;
  while (true)
  {
    cout << "Welcome to " << Amazon::name << endl;
    cout << "[1] Add item" << endl;
    cout << "[2] View items" << endl;
    cout << "[3] Search item" << endl;
    cout << "[4] Update item" << endl;
    cout << "[5] Delete item" << endl;
    cout << "[6] Exit Inventory" << endl;
    cout << "Choose one: ";
    cin >> choice;
    if (choice < 1 || choice > 6)
    {
      continue;
    }
    if (static_cast<Options>(choice) == Options::EXIT_INVENTORY)
    {
      cout << "Inventory exited! Thanks for visiting." << endl;
      break;
    }
    Options option = static_cast<Options>(choice);
    switch (option)
    {
    case Options::ADD_ITEM:
      addItem();
      break;
    case Options::VIEW_ITEMS:
      viewItems();
      break;
    case Options::SEARCH_ITEM:
      searchItem();
      break;
    case Options::UPDATE_ITEM:
      updateItem();
      break;
    case Options::DELETE_ITEM:
      deleteItem();
      break;
    default:
      continue;
    }
  }
  return 0;
}
