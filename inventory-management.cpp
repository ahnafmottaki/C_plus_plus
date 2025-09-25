#include <iostream>
#include <limits>
#include <string>
#include <fstream>
using namespace std;

// enum classes
enum class OPTIONS
{
  ADD_ITEM = 1,
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
template <class T>
T get_and_validate_number(string m, T max, T min);
string get_and_validate_string_length(string m, int max_length, int min_length);

//  classes
class Product
{
private:
  string title, description, category, brand;
  string *tags = nullptr;
  float price = 0.0f;
  int stock = 0, tags_count = 0;

public:
  Product();
  Product(string _nothing);
  string get_title() { return title; }
  string get_description() { return description; }
  string get_category() { return category; }
  string get_brand() { return brand; }
  int get_stock() { return stock; }
  float get_Price() { return price; }
  void show_details() const;
  void update_product();
  friend ofstream &operator<<(ofstream &out, const Product &p);
  friend ifstream &operator>>(ifstream &in, Product &p);
};

// Inventory class
class Inventory
{
private:
  int total_products = 0;
  Product **products = nullptr;
  string file_name;

public:
  Inventory()
  {
    products = new Product *[0];
    file_name = name + ".txt";
    load_from_file();
  }
  static string name, address, helpline_number, website;
  string get_name() const { return name; }
  string get_helpline_number() const { return helpline_number; }
  string get_website_url() const { return website; }
  int get_total_products() const { return total_products; }
  void add_item();
  void view_all_items() const;
  void search_item() const;
  void update_item();
  void save_to_file() const;
  void load_from_file();
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

    cout << "[1] ADD ITEM\n[2] VIEW ITEMS\n[3] SEARCH ITEM\n[4] UPDATE ITEM\n[5] DELETE ITEM\n[6] EXIT";
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
    case OPTIONS::VIEW_ITEMS:
      amazon->view_all_items();
      break;
    case OPTIONS::SEARCH_ITEMS:
      amazon->search_item();
      break;
    case OPTIONS::UPDATE_ITEMS:
      amazon->update_item();
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
  show_message_with_borders("ADDING ITEMS TO INVENTORY", BORDER_POSITION::BOTH);
  Product *temp_product = new Product();
  Product **new_products = new Product *[total_products + 1];
  for (int i = 0; i < total_products; ++i)
  {
    new_products[i] = products[i];
  }
  new_products[total_products] = temp_product;
  delete[] products;
  products = new_products;
  total_products++;
  show_message_with_borders("Product added to inventory", BORDER_POSITION::BOTH);
  save_to_file();
  products[total_products - 1]->show_details();
}
void Inventory::view_all_items() const
{
  show_message_with_borders("VIEWING ALL ITEMS IN INVENTORY", BORDER_POSITION::BOTH);
  for (int i = 0; i < total_products; ++i)
  {
    products[i]->show_details();
  }
}

void Inventory::save_to_file() const
{
  ofstream outFile(file_name, ios::out | ios::trunc);
  for (int i = 0; i < total_products; ++i)
  {
    outFile << *products[i];
  }
  outFile.close();
  show_message_with_borders("File saved to Memory", BORDER_POSITION::BOTH);
}

void Inventory::load_from_file()
{
  ifstream in(file_name, ios::in);
  if (!in.is_open())
  {
    cout << "File doesn't exist. You must have accidentally deleted it!\n";
    return;
  }
  while (true)
  {
    Product *new_product = new Product("_nothing");
    if (!(in >> *new_product))
    {
      delete new_product;
      break;
    }
    Product **new_products = new Product *[total_products + 1];
    for (int i = 0; i < total_products; ++i)
    {
      new_products[i] = products[i];
    }
    new_products[total_products] = new_product;
    delete[] products;
    products = new_products;
    total_products++;
  }
  in.close();
  cout << "Loaded from file (total_products = " << total_products << ")" << endl;
}

void Inventory::search_item() const
{
  string temp_title;
  cout << "Enter product title: ";
  clear_input();
  getline(cin, temp_title);
  for (int i = 0; i < total_products; ++i)
  {
    if (temp_title == products[i]->get_title())
    {
      show_message_with_borders("Here is the Product with title " + temp_title, BORDER_POSITION::BOTH);
      products[i]->show_details();
      break;
    }
  }
}

void Inventory::update_item()
{
  clear_input();
  show_message_with_borders("UPDATE ITEM", BORDER_POSITION::BOTH);
  cout << "Enter product title: ";
  string temp_title;
  getline(cin, temp_title);
  Product *found_product = nullptr;
  for (int i = 0; i < total_products; ++i)
  {
    if (temp_title == products[i]->get_title())
    {
      show_message_with_borders("PRODUCT FOUND", BORDER_POSITION::BOTH);
      found_product = products[i];
      break;
    }
  }
  if (found_product == nullptr)
  {
    show_message_with_borders("PRODUCT IS NOT IN THE INVENTORY", BORDER_POSITION::BOTH);
    return;
  }
  found_product->show_details();
  found_product->update_product();
  found_product = nullptr;
  save_to_file();
  show_message_with_borders("PRODUCT UPDATED SUCCESSFULLY", BORDER_POSITION::BOTH);
}

// * product class members and functions
Product::Product()
{
  update_product();
}

Product::Product(string _nothing)
{
  title = "";
  description = "";
  category = "";
  brand = "";
  tags = nullptr;
  price = 0.0f;
  stock = 0;
  tags_count = 0;
}

void Product::update_product()
{
  clear_input();
  title = get_and_validate_string_length("title", 30, 3);
  description = get_and_validate_string_length("description", 80, 10);
  category = get_and_validate_string_length("category", 15, 3);
  brand = get_and_validate_string_length("brand", 15, 3);
  price = get_and_validate_number<float>("price", 1000, 1);
  stock = get_and_validate_number<int>("stock", 1000, 1);
  tags_count = get_and_validate_number<int>("number of tags", 10, 1);
  if (tags != nullptr)
  {
    delete[] tags;
  }
  tags = new string[tags_count];
  char bef[8] = "tag [";
  bef[6] = ']';
  char tag_num = '1';
  for (int i = 0; i < tags_count; ++i)
  {
    bef[5] = tag_num;
    tags[i] = get_and_validate_string_length(bef, 15, 3);
    tag_num++;
  }
}

void Product::show_details() const
{
  cout << "Product Name: " << title << endl;
  cout << "Product Description: " << description << endl;
  cout << "Product Category: " << category << endl;
  cout << "Product Brand: " << brand << endl;
  cout << "Product Stock: " << stock << endl;
  cout << "Product Price: " << price << endl;
  cout << "Product tags: {";
  for (int i = 0; i < tags_count; ++i)
  {
    cout << " '" << tags[i] << "'";
    if (i != tags_count - 1)
    {
      cout << ", ";
    }
  }
  cout << "}";
  show_border();
}

// * Product class Operator overloading
ofstream &operator<<(ofstream &out, const Product &p)
{
  out << p.title << "%"
      << p.description << "%"
      << p.category << "%"
      << p.brand << "%"
      << p.price << "%"
      << p.stock << "%"
      << p.tags_count << "%";

  for (int i = 0; i < p.tags_count; ++i)
  {
    out << p.tags[i] << "%";
  }
  return out;
}
ifstream &operator>>(ifstream &in, Product &p)
{
  string priceStr, stockStr, tagCountStr;

  getline(in, p.title, '%');
  getline(in, p.description, '%');
  getline(in, p.category, '%');
  getline(in, p.brand, '%');

  getline(in, priceStr, '%');
  getline(in, stockStr, '%');
  getline(in, tagCountStr, '%');

  p.price = atof(priceStr.c_str());
  p.stock = atoi(stockStr.c_str());
  p.tags_count = atoi(tagCountStr.c_str());

  delete[] p.tags; // avoid memory leak if already allocated
  p.tags = new string[p.tags_count];

  for (int i = 0; i < p.tags_count; ++i)
  {
    getline(in, p.tags[i], '%');
  }
  return in;
}

// utility functions
template <class T>
T get_and_validate_number(string property, T max, T min)
{
  T temp;
  while (true)
  {
    cout << "Enter " << property << ": ";
    cin >> temp;
    if (cin.fail())
    {
      clear_input();
      cout << "Invalid input! Please enter a number.\n";
      continue;
    }
    if (temp < min || temp > max)
    {
      clear_input();
      cout << property << " must be between " << min << " and " << max << " " << endl;
      continue;
    }
    clear_input();
    break;
  }
  return temp;
}

string get_and_validate_string_length(string property, int max_length, int min_length)
{
  string temp;
  while (true)
  {
    cout << "Enter " << property << ": ";
    getline(cin, temp);
    if (temp.length() < min_length || temp.length() > max_length)
    {
      cout << property << " must be between " << min_length << " to " << max_length << " characters" << endl;
      continue;
    }
    break;
  }
  return temp;
}

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
