#include <iostream>
#include <limits>
using namespace std;
class Inventory
{
private:
  Product **p = new Product *[3];
  string title, address, helpline_number, website;
  int totalProducts;

public:
  void add_item();
  void view_all_items();
  void search_item();
  void update_item();
  void save_to_file();
  void load_from_file();
};

class Product
{
private:
  string title, description, category, brand;
  string *tags;
  float price;
  int stock;

  void show_details()
  {
    cout << "showing product details";
  }
};
int main()
{
  return 0;
}
