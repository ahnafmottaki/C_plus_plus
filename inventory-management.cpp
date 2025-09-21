#include <iostream>
#include <limits>
#include <string.h>
#include <fstream>
using namespace std;

void clear_input_buffer()
{
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

template <class T>
T get_input(string message, string error_message)
{
  T x;
  while (true)
  {
    cout << message << ": ";
    if (cin >> x)
    {
      return x;
    }
    else
    {
      cout << error_message << endl;
      clear_input_buffer();
    }
  }
}
enum class IN_WHERE
{
  STARTING,
  ENDING,
  BOTH,
  NONE,
};
void display_message(string title, IN_WHERE w)
{
  if (w == IN_WHERE::STARTING || w == IN_WHERE::BOTH)
  {
    for (int i = 0; i < 30; i++)
    {
      cout << "-";
    }
    cout << endl;
  }
  cout << title << endl;
  if (w == IN_WHERE::ENDING || w == IN_WHERE::BOTH)
  {
    for (int i = 0; i < 30; i++)
    {
      cout << "-";
    }
    cout << endl;
  }
}

enum class Options
{
  ADD_ITEM = 1,
  VIEW_ITEMS,
  SEARCH_ITEM,
  UPDATE_ITEM,
  DELETE_ITEM,
  EXIT_INVENTORY,
};

class Product
{
private:
  string title;
  int quantity;
  float price;

public:
  Product(string t = "", int q = 0, float p = 0) : title(t), quantity(q), price(p)
  {
  }
  void show_details() const;
  string get_title() const
  {
    return title;
  }
  int get_quantity() const
  {
    return quantity;
  }

  float get_price() const
  {
    return price;
  }
  friend ofstream &operator<<(ofstream &out, const Product &p);
  friend ifstream &operator>>(ifstream &fin, Product &p);
};

void Product::show_details() const
{
  {
    cout << "Product Title: " << title << endl;
    cout << "Product quantity: " << quantity << endl;
    cout << "Product price: " << price << endl;
  }
}

ofstream &operator<<(ofstream &out, const Product &p)
{
  out << p.title << endl
      << p.quantity << endl
      << p.price << endl;
  return out;
}

ifstream &operator>>(ifstream &fin, Product &p)
{
  fin >> p.title >> p.quantity >> p.price;
  return fin;
}

class Amazon
{
private:
  int total_products = 0;
  Product **products = new Product *[0];

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

string Amazon::name = "Amazon Inventory";
string Amazon::address = "410 Terry Avenue North, Seattle, Washington, 98109";
string Amazon::country = "United States of America";
string Amazon::phone_number = "+1 206 2661000";
string Amazon::website_url = "www.amazon.com";

void Amazon::load_from_file()
{
  ifstream fin(name + ".txt");
  if (!fin)
  {
    cout << "No file found. Starting with empty inventory.\n";
    return;
  }

  for (int i = 0; i < total_products; ++i)
  {
    delete products[i];
  }
  delete[] products;
  products = new Product *[0];
  total_products = 0;
  Product temp;
  while (fin >> temp)
  {
    Product *p = new Product(temp.get_title(), temp.get_quantity(), temp.get_price());
    Product **new_products = new Product *[total_products + 1];
    for (int i = 0; i < total_products; ++i)
    {
      new_products[i] = products[i];
    }
    new_products[total_products] = p;
    delete[] products;
    products = new_products;
    total_products++;
  }
  fin.close();
  display_message(total_products + " products loaded from file\n", IN_WHERE::BOTH);
}
void Amazon::save_to_file()
{
  ofstream outFile(Amazon::name + ".txt");
  for (int i = 0; i < total_products; ++i)
  {
    outFile << *products[i];
  }
  outFile.close();
}
void Amazon::add_item()
{
  display_message("ADD_ITEM TO INVENTORY", IN_WHERE::BOTH);
  string title;
  int quantity;
  float price;
  while (true)
  {
    cout << "Enter title: ";
    getline(cin, title);
    if (title.length() <= 3)
    {
      display_message("Title must be at least 3 characters long", IN_WHERE::NONE);
      clear_input_buffer();
      continue;
    }
    break;
  }
  quantity = get_input<int>("Enter quantity", "Enter a valid quantity");
  price = get_input<float>("Enter price", "Please Enter a valid price");
  Product *new_product = new Product(title, quantity, price);
  Product **new_products = new Product *[total_products + 1];
  for (int i = 0; i < total_products; ++i)
  {
    new_products[i] = products[i];
  }
  new_products[total_products] = new_product;
  delete[] products;
  products = new_products;
  display_message("Product Details", IN_WHERE::ENDING);
  products[total_products]->show_details();
  total_products++;
  save_to_file();
  display_message("Product added to Inventory", IN_WHERE::BOTH);
}

void searchItem()
{
  cout << "{Search item}";
}

void Amazon::view_all_items()
{
  display_message("All Products", IN_WHERE::ENDING);
  for (int n = 0; n < total_products; ++n)
  {
    products[n]->show_details();
    cout << "-----------------------------" << endl;
  }
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
  Amazon *my_inventory = new Amazon();
  my_inventory->load_from_file();
  display_message("Welcome to " + Amazon::name, IN_WHERE::ENDING);

  while (true)
  {

    cout << "[1] Add item" << endl;
    cout << "[2] View items" << endl;
    cout << "[3] Search item" << endl;
    cout << "[4] Update item" << endl;
    cout << "[5] Delete item" << endl;
    cout << "[6] Exit Inventory" << endl;
    cout << "Choose one: ";
    if (!(cin >> choice))
    {
      clear_input_buffer();
      cout << "Invalid input! Please enter a number between 1-6." << endl;
      continue;
    }
    clear_input_buffer();
    if (choice < 1 || choice > 6)
    {
      cout << "Please enter a number between 1-6." << endl;
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
    case Options::ADD_ITEM:;
      my_inventory->add_item();
      break;
    case Options::VIEW_ITEMS:
      my_inventory->view_all_items();
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
    }
  }
  delete my_inventory;
  return 0;
}
