#include <bits/stdc++.h>
#include <assert.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <numeric>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

typedef array<int16_t, 2> Port;
typedef int8_t Packet;
typedef array<int32_t, 2> Position;
struct UpdatePort {
  Port port;
  int8_t value;
};

// Declare global variables
extern set<int16_t> components_to_update;
extern vector<UpdatePort> ports_to_update;

class BaseComponent {
public:
  BaseComponent(string name = "base component",
                Position position = {0, 0}, vector<Packet> inputs = {},
                vector<Port> output_targets = {})
      : name(name), position(position), inputs(inputs),
        output_targets(output_targets) {}

  string name;
  Position position;

  vector<Packet> inputs;
  vector<Port> output_targets;

  virtual void update_outputs() {
    for (size_t i = 0; i < inputs.size(); i++) {
      printf("input %zu is %d\n", i, inputs[i]);
    }
  }
};

class InputGate : public BaseComponent {
public:
  InputGate(string name = "input", Position position = {0, 0},
            vector<Packet> inputs = {}, vector<Port> output_targets = {})
      : BaseComponent(name, position, inputs, output_targets) {}

  void update_outputs() override {
    for (size_t i = 0; i < inputs.size(); i++) {
      ports_to_update.push_back({output_targets[i], inputs[i]});
    }
  }
};

class OutputGate : public BaseComponent {
public:
  OutputGate(string name = "input", Position position = {0, 0},
             vector<Packet> inputs = {}, vector<Port> output_targets = {})
      : BaseComponent(name, position, inputs, output_targets) {}

  void update_outputs() override {
    for (size_t i = 0; i < inputs.size(); i++) {
      printf("OUTPUT %zu: %d\n", i, inputs[i]);
    }
  }
};

class SplitGate : public BaseComponent {
public:
  SplitGate(string name = "split", Position position = {0, 0},
            vector<Packet> inputs = {0}, vector<Port> output_targets = {})
      : BaseComponent(name, position, inputs, output_targets) {}

  void update_outputs() override {
    for (size_t i = 0; i < output_targets.size(); i++) {
      ports_to_update.push_back({output_targets[i], inputs[0]});
    }
  }
};

class NegGate : public BaseComponent {
public:
  NegGate(string name = "input", Position position = {0, 0},
          vector<Packet> inputs = {}, vector<Port> output_targets = {})
      : BaseComponent(name, position, inputs, output_targets) {}

  void update_outputs() override {
    for (size_t i = 0; i < inputs.size(); i++) {
      ports_to_update.push_back(
          {output_targets[i], static_cast<int8_t>(-inputs[i])});
    }
  }
};

class AddGate : public BaseComponent {
public:
  AddGate(string name = "input", Position position = {0, 0},
          vector<Packet> inputs = {}, vector<Port> output_targets = {})
      : BaseComponent(name, position, inputs, output_targets) {}

  void update_outputs() override {
    ports_to_update.push_back(
        {output_targets[0],
         static_cast<int8_t>(accumulate(inputs.begin(), inputs.end(), 0))});
  }
};

class MaxGate : public BaseComponent {
public:
  MaxGate(string name = "input", Position position = {0, 0},
          vector<Packet> inputs = {}, vector<Port> output_targets = {})
      : BaseComponent(name, position, inputs, output_targets) {}

  void update_outputs() override {
    ports_to_update.push_back(
        {output_targets[0],
         static_cast<int8_t>(*max_element(inputs.begin(), inputs.end()))});
  }
};

class MinGate : public BaseComponent {
public:
  MinGate(string name = "input", Position position = {0, 0},
          vector<Packet> inputs = {}, vector<Port> output_targets = {})
      : BaseComponent(name, position, inputs, output_targets) {}

  void update_outputs() override {
    ports_to_update.push_back(
        {output_targets[0],
         static_cast<int8_t>(*min_element(inputs.begin(), inputs.end()))});
  }
};

// max, min
