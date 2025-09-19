#include <iostream>
#include <limits>
using namespace std;

enum class Options
{
  ADD_ITEM = 1,
  VIEW_ITEM,
  SEARCH_ITEM,
  UPDATE_ITEM,
  DELETE_ITEM,
};

class Amazon
{
  class Item
  {
  };

public:
  static string name;
  void add_item();
  void view_all_items();
  void search_item_by_name();
  void update_item();
  void delete_item();
  void save_to_file();
  void load_from_file();
};

string Amazon::name = "Amazon Inventory";
int main()
{
  const string welcome_msg = "**Welcome to " + Amazon::name + "**\n";
  int choice;
  Options option;
  cout << welcome_msg;
  while (true)
  {
    cout << "1.ADD ITEM\n2.VIEW_ITEM\n3.SEARCH_ITEM\n4.UPDATE_ITEM\n5.DELETE_ITEM\nChoose one option: ";
    if (cin >> choice)
    {

      if (choice >= static_cast<int>(Options::ADD_ITEM) && choice <= static_cast<int>(Options::DELETE_ITEM))
      {
        option = static_cast<Options>(choice);
        break;
      }
      else
      {
        cout << "Invalid choice. Please enter a number between 1 and 5.\n";
      }
    }
    else
    {
      cout << "Invalid input. Please enter a number.\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
  if (option == Options::ADD_ITEM)
  {
    cout << "Add item";
  }
  else if (option == Options::VIEW_ITEM)
  {
    cout << "View item";
  }
  else if (option == Options::SEARCH_ITEM)
  {
    cout << "Search item";
  }
  else if (option == Options::UPDATE_ITEM)
  {
    cout << "Update item";
  }
  else if (option == Options::DELETE_ITEM)
  {
    cout << "Delete item";
  }
  return 0;
}
