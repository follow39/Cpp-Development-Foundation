#include <string>
#include <vector>
using namespace std;

#define UNIQ_ID_2(lineno) uniq_##lineno
#define UNIQ_ID_1(lineno) UNIQ_ID_2(lineno)
#define UNIQ_ID UNIQ_ID_1(__LINE__)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}
