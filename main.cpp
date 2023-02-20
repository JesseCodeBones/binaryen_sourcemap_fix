#include "binaryen-c.h"
#include "pass.h"
#include "wasm-io.h"
#include "wasm.h"
#include <fstream>
#include <iostream>

#define TARGET_FILE "target.wasm"
#define TARGET_SOURCEMAP_FILE "target.wasm.map"

struct SimpleExpressionWalker
    : public wasm::PostWalker<
          SimpleExpressionWalker,
          wasm::UnifiedExpressionVisitor<SimpleExpressionWalker>> {

  void visitExpression(BinaryenExpressionRef curr) {
    if (curr->is<wasm::Call>()) {
      auto currFun = getFunction();
      wasm::Call *callExpr = static_cast<wasm::Call *>(curr);
      wasm::Function::DebugLocation callLocation, param1Location,
          param2Location;
      callLocation.fileIndex = 0;
      callLocation.columnNumber = 5;
      callLocation.lineNumber = 24;
      currFun->debugLocations[curr] = callLocation;

      param1Location.fileIndex = 0;
      param1Location.columnNumber = 6;
      param1Location.lineNumber = 25;
      currFun->debugLocations[callExpr->operands[0]] = param1Location;

      param2Location.fileIndex = 0;
      param2Location.columnNumber = 6;
      param2Location.lineNumber = 26;
      currFun->debugLocations[callExpr->operands[1]] = param2Location;
    }
  }
};

int main(int, char **) {
  SimpleExpressionWalker walker;
  BinaryenModuleRef ref = BinaryenModuleCreate();
  std::ifstream file("../testobjs/test.wat");
  std::string contents((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
  auto module = BinaryenModuleParse(contents.c_str());
  module->debugInfoFileNames.push_back("testobjs/test.wat");
  walker.walkModule(module);

  BinaryenModulePrint(module); //  print correct value

  std::cout << "---------below will print incorrect value-------- \n";

  auto result = BinaryenModuleAllocateAndWrite(module, "testurl");
  std::ofstream oFile(TARGET_FILE);
  oFile.write(static_cast<char *>(result.binary), result.binaryBytes);
  oFile.flush();
  oFile.close();

  std::ofstream oDebugFile(TARGET_SOURCEMAP_FILE);
  oDebugFile << result.sourceMap;
  oDebugFile.flush();
  oDebugFile.close();

  wasm::ModuleReader reader;
  wasm::Module reloadModule;
  reader.read(TARGET_FILE, reloadModule, TARGET_SOURCEMAP_FILE);
  BinaryenModulePrint(&reloadModule); //  print in-correct value

  std::cout << "end test!\n";
}
