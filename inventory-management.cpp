#include <iostream>
#include <limits>
#include <string>
using namespace std;

// enum classes
enum class OPTIONS
{
  ADD_ITEM,
  VIEW_ITEMS,
  SEARCH_ITEMS,
  UPDATE_ITEMS,
  DELETE_ITEMS
};

enum class BORDER_POSITION
{
  TOP,
  BOTTOM,
  BOTH,
  NO_BORDER,
};

// utility functions
void show_border();
void clear_input();
void show_message_with_borders(string m, BORDER_POSITION b);

//  classes
class Product
{
private:
  string title, description, category, brand;
  string *tags = new string[total_tags];
  int total_tags = 0;
  float price;
  int stock;

public:
  Product();
  void show_details() const;
};

// Inventory class
class Inventory
{
private:
  Product *products = new Product[totalProducts];
  int totalProducts = 0;

public:
  static string name, address, helpline_number, website;
  string get_name() const { return name; }
  string get_helpline_number() const { return helpline_number; }
  string get_website_url() const { return website; }
  int get_total_products() const { return totalProducts; }
  void add_item();
  void view_all_items() const;
  void search_item() const;
  void update_item();
  void save_to_file() const;
  void load_from_file() const;
  void show_inventory_details() const;
};

int main()
{
  Inventory *amazon = new Inventory();
  show_border();
  cout << "Welcome to " << Inventory::name;
  show_border();
  int choice;
  while (true)
  {

    cout << "[1] add_item\n[2] view_items\n[3] search_item\n[4] update_item\n[5] delete_item\n[6] exit";
    show_message_with_borders("What can I do for you?: ", BORDER_POSITION::TOP);
    cin >> choice;
    if (choice < 1 || choice > 6)
    {
      cout << "Invalid choice\n";
      clear_input();
      continue;
    }
    if (choice == 6)
    {
      show_message_with_borders("Thanks for visiting " + Inventory::name, BORDER_POSITION::BOTH);
      break;
    }

    switch (static_cast<OPTIONS>(choice))
    {
    case OPTIONS::ADD_ITEM:
      amazon->add_item();
      break;
    default:
      break;
    }
  }
  return 0;
}

// static class variables
string Inventory::name = "Amazon Inventory", Inventory::address = "410 Terry Avenue North, Seattle, Washington, 98109";
string Inventory::helpline_number = "+1 206 2661000", Inventory::website = "https://www.amazon.com";

// Inventory class member functions
void Inventory::add_item()
{
  Product temp_product;
  Product *newProducts = new Product[totalProducts + 1];
  for (int i = 0; i < totalProducts; ++i)
  {
    newProducts[i] = products[i];
  }
}

// product class members and functions
void Product::show_details() const
{
  cout << "showing product details";
}

// utility functions
void show_border()
{
  cout << endl;
  for (int i = 0; i < 40; ++i)
  {
    cout << '-';
  }
  cout << endl;
}

void show_message_with_borders(string message, BORDER_POSITION b)
{
  if (b == BORDER_POSITION::TOP || b == BORDER_POSITION::BOTH)
  {
    show_border();
  }
  cout << message;
  if (b == BORDER_POSITION::BOTTOM || b == BORDER_POSITION::BOTH)
  {
    show_border();
  }
}

void clear_input()
{
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
