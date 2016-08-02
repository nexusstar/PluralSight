#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <memory>

using namespace std;

int main()
{
  // <p> hello </p>
  auto text = "hello";
  string output;

  // naive approach is just to concatenate
  output += "<p>";
  output += text;
  output += "</p>";
  cout << output << endl;

  // simple builder pattern is to use printf
  printf("<p>%s</p>", text);

  // <ul><li>hello</li><li>world</li></ul>
  //
  string words[] = {"hello" , "world"};
  ostringstream oss;
  oss << "<ul>\n";

  for(auto w : words)
    oss << " <li>" << w << "</li>\n";
  oss << "</ul>";

  printf(oss.str().c_str());



  return 0;
}
