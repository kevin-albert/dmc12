#ifndef TDD_H
#define TDD_H

#include <atomic>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <tuple>
#include <functional>
#include <algorithm>

struct test_result {
  test_result() {}
  test_result(std::string msg): success(false), msg(msg) {}
  operator bool() const { return success; }
  bool success {true};
  std::string msg;
};

test_result ok() { return test_result(); }

using test_callback = std::function<void(const test_result&)>;
using test_fn = std::function<void(test_callback)>;
using test_case = std::pair<std::string, test_fn>;

class tdd {
public:  
  tdd(std::string name, test_fn test) {
    tests.push_back(test_case(name, test));
  }
  
  static void run() {
    std::cout << "Running tests...\n";
    std::vector<test_result> results(tests.size());
    
    std::atomic<int> pass(0);
    std::atomic<int> fail(0);

    auto done = [&]() {
      for (int i = 0; i < tests.size(); ++i) {
        auto name = tests[i].first;
        auto result = results[i];
        std::cout << std::setw(26) << name;
        if (result) {
          std::cout << ": ok\n";
        } else {
          std::cout << ": fail - " << result.msg << "\n";
        }
      }
      std::cout << "\n"
                << "pass: " << pass << "\n"
                << "fail: " << fail << "\n";
      exit(fail > 0 ? 1 : 0);
    };

    for (int i = 0; i < tests.size(); ++i) {
      auto name = tests[i].first;
      auto fn = tests[i].second;
      try {
        fn([i, &results, &pass, &fail, &done](const test_result &result) {
          results[i] = result;
          
          int total;
          if (result) {
            total = ++pass + fail;
          } else {
            total = pass + ++fail;
          }

          if (total == tests.size()) {
            done();
          }
        });
      } catch (std::exception &e) {
        std::string msg = e.what();
        results[i] = test_result("exception thrown - " + msg); 
        
        // TODO atomic
        if (pass + ++fail == tests.size())
          done();
      }
    }
  }
private: 
  static std::vector<test_case> tests;
  static std::vector<test_result> results;
};

#define unit_test(name, cb) void name(test_callback);\
tdd __test_ ## name (#name, name);\
void name (test_callback cb)

#define assert_true_(val, cb, msg) if (!(val)) cb(test_result(msg))
#define assert_true(val, cb) assert_true_((val), cb, "expected (" #val ") to be true")
#define assert_eq(x, y, cb) assert_true_((x == y), cb, "expected " #x " to equal " #y)
#define assert_false(val, cb) assert_true(!(val), cb, "expected (" #val ") to be false")
#define assert_neq(x, y, cb) assert_true_((x != y), cb, "expected " #x " not to equal " #y)

#endif