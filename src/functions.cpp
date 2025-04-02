#include "functions.hpp"
#include "gates.hpp"
extern unordered_map<int32_t, unique_ptr<BaseComponent>> circuit;

void setup_default_MUL_circuit() {
  circuit.insert(
      {0, make_unique<InputGate>("input", Vector2{0, 0}, vector<Packet>{-1, -1},
                                 vector<Port>{{1, 0}, {2, 0}})});
  circuit.insert(
      {1, make_unique<SplitGate>("split1", Vector2{100, 0}, vector<Packet>{0},
                                 vector<Port>{{3, 0}, {4, 0}})});
  circuit.insert(
      {2, make_unique<SplitGate>("split2", Vector2{0, 100}, vector<Packet>{0},
                                 vector<Port>{{3, 1}, {4, 1}})});
  circuit.insert(
      {3, make_unique<MaxGate>("max1", Vector2{200, 0}, vector<Packet>{0, 0},
                               vector<Port>{{5, 0}})});
  circuit.insert(
      {4, make_unique<MinGate>("min1", Vector2{0, 200}, vector<Packet>{0, 0},
                               vector<Port>{{6, 1}})});
  circuit.insert(
      {5, make_unique<NegGate>("neg", Vector2{200, 200}, vector<Packet>{0},
                               vector<Port>{{6, 0}})});
  circuit.insert(
      {6, make_unique<MaxGate>("max2", Vector2{300, 300}, vector<Packet>{0, 0},
                               vector<Port>{{-1, 0}})});
  circuit.insert(
      {-1, make_unique<OutputGate>("output", Vector2{700, 700},
                                   vector<Packet>{0}, vector<Port>{})});
  components_to_update.insert(0);
}
