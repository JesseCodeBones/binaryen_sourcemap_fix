# binaryen_sourcemap_fix
## build and run
* `cmake -B build`
* `cd build`
* `make binaryen_sourcemap_fix`  //if you are using unix make generator
* `./binaryen_sourcemap_fix`
## result check
it will print twice of the wasm module:
* the first one: the debug info is directly write by code, the output is correct
* the second one: it load debug info from generated map file, and it dismissed the debug info for call instruction.
