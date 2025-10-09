#include "raylib.h"
#include "Circuit.h"
#include "GateTypes.h"

int main() {
  const int screenWidth = 800;
  const int screenHeight = 600;
  
  InitWindow(screenWidth, screenHeight, "Ternary");
  SetTargetFPS(60);

  Circuit circuit;

  // default gates
  auto inputGate = std::make_unique<InputGate>(Vector2{100,100});
  auto notGate = std::make_unique<NotGate>(Vector2{200,100});
  auto outputGate = std::make_unique<OutputGate>(Vector2{300,100});

  BaseGate* inputPtr = inputGate.get();
  BaseGate* notPtr = notGate.get();
  BaseGate* outputPtr = outputGate.get();

  circuit.addGate(std::move(inputGate));
  circuit.addGate(std::move(notGate));
  circuit.addGate(std::move(outputGate));

  circuit.connectGates(inputPtr, notPtr);
  circuit.connectGates(notPtr, outputPtr);
}
