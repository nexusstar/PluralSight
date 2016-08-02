#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

using namespace std;

//forward declaration
struct HTMLBuilder;

struct HTMLElement
{
  string name;
  string text;
  vector<HTMLElement> elements;
  const size_t indent_size = 2; //fixed size of indentation

  HTMLElement(){}
  HTMLElement(string& name, string& text):
    name{name},
    text{text}
  {}

  string str(int indent = 0) const
  {
    ostringstream oss;
    string i(indent_size * indent, ' ');
    oss << i << "<" << name << ">" << endl;

    if(text.size() > 0)
      oss << string(indent_size * (indent + 1), ' ') << text << endl;

    for (const auto& e : elements)
      oss << e.str(indent + 1);

    oss << i << "</" << name << ">" << endl;

    return oss.str();
  }

  static HTMLBuilder build(string root_name);
  static unique_ptr<HTMLBuilder> build_ptr(string root_name);
};


struct HTMLBuilder
{
  HTMLBuilder(string root_name)
  {
    root.name = root_name;
  }
  // Make the builder fluent return *this reference
  // and now we can chain that function
  HTMLBuilder& add_child(string child_name, string child_text)
  {
    HTMLElement e (child_name, child_text);
    root.elements.emplace_back(e);
    return *this;
  }

  //instead of reference return a ptr
  HTMLBuilder* add_child_ptr(string child_name, string child_text)
  {
    HTMLElement e (child_name, child_text);
    root.elements.emplace_back(e);
    return this;
  }

  string str() const { return root.str(); }

  // create automatic conversion
  operator HTMLElement() { return root; };

  HTMLElement root;
};


HTMLBuilder HTMLElement::build(string root_name)
{
  return HTMLBuilder{root_name};
}

unique_ptr<HTMLBuilder> HTMLElement::build_ptr(string root_name)
{
  return make_unique<HTMLBuilder>(root_name); // need to compile with -std=c++14
}

int main()
{
  HTMLBuilder builder{ "ul" };
  builder.add_child("li", "hello").add_child("li", "world");
  cout << builder.str() << endl;

  HTMLElement e = HTMLElement::build("ul").add_child("li", "hello");


  cout << e.str() << endl;

  return 0;
}
