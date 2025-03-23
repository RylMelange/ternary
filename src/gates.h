#include <array>
#include <assert.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

typedef array<int16_t, 2> Port;
typedef int8_t Packet;

struct UpdatePort {
  Port port;
  int8_t value;
};

class BaseComponent {
public:
  BaseComponent(string name = "base component",
                array<int32_t, 2> position = {0, 0}, vector<Packet> inputs = {},
                vector<Port> output_targets = {})
      : name(name), position(position), inputs(inputs),
        output_targets(output_targets) {
    printf("setting up a base component!\n");
  }

  string name;
  array<int32_t, 2> position;

  vector<Packet> inputs;
  vector<Port> output_targets;

  virtual void update_outputs() {
    printf("This is from base component (%s)\n", name.c_str());
    for (size_t i = 0; i < inputs.size(); i++) {
      printf("input %zu is %d\n", i, inputs[i]);
    }
  }
};

// Declare global variables
extern unordered_map<int32_t, BaseComponent> circuit;
extern set<int16_t> components_to_update;
extern vector<UpdatePort> ports_to_update;

class InputGate : public BaseComponent {
public:
  InputGate(string name = "input", array<int32_t, 2> position = {0, 0},
            vector<Packet> inputs = {}, vector<Port> output_targets = {})
      : BaseComponent(name, position, inputs, output_targets) {}

  void update_outputs() override {
    for (size_t i = 0; i < inputs.size(); i++) {
      printf("updating from InputGate class (%s)\n", name.c_str());
      ports_to_update.push_back({output_targets[i], inputs[i]});
    }
  }
};

class OutputGate : public BaseComponent {
public:
  OutputGate(string name = "input", array<int32_t, 2> position = {0, 0},
             vector<Packet> inputs = {}, vector<Port> output_targets = {})
      : BaseComponent(name, position, inputs, output_targets) {}

  void update_outputs() override { printf("TODO: OutputGate"); }
};
class NegGate : public BaseComponent {
public:
  NegGate(string name = "input", array<int32_t, 2> position = {0, 0},
          vector<Packet> inputs = {}, vector<Port> output_targets = {})
      : BaseComponent() {}

  void update_outputs() override { printf("TODO: NegGate"); }
};
