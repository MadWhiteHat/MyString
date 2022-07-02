#include <iostream>
#include <cstring>

int32_t main(int32_t argc, char** argv) {
  int32_t line = 76;
  for(int32_t idx = 0; idx < argc; ++idx) {
    std::string output((line - strlen(argv[idx])) >> 1, '-');
    output.insert(0, "//");
    output += argv[idx];
    output.append(
      ((line - strlen(argv[idx])) >> 1) + (strlen(argv[idx]) % 2 == 0 ? 0 : 1),
      '-');
    output += "//";
    std::cout << output << std::endl;

  }
  return 0;
}
