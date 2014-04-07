#include "llvm/IRReader/IRReader.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/PassManager.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Transforms/IPO.h"
#include <string>
#include <vector>

using namespace llvm;


static cl::opt<std::string>
InputFilename(cl::Positional, cl::desc("<input bitcode file>"),
    cl::init("-"), cl::value_desc("filename"));

static cl::opt<std::string>
OutputFilename("o", cl::desc("Override output filename"),
    cl::init(""), cl::value_desc("filename"));

int main(int argc, char** argv)
{
    cl::ParseCommandLineOptions(argc, argv, "LLVM hack\n");
    
    if (!llvm::sys::fs::exists(InputFilename))
    {
        errs() << InputFilename << " does not exist\n";
        return -1;
    }

    Module* m = 0;
    SMDiagnostic Err; 
    m = ParseIRFile(InputFilename, Err, llvm::getGlobalContext());
    if (!m)
    {
        errs() << "Failed to parsing " << InputFilename << "\n";
        Err.print(argv[0], errs());
        return 1;
    }

    m->dump();
    PassManager* PM = new PassManager();

    // inline functions with always_inline attribute
    PM->add(createAlwaysInlinerPass());

    std::vector<const char*> SymbolsToKeep;
    SymbolsToKeep.push_back("main");

    // Internalise everything except main
    PM->add(createInternalizePass(SymbolsToKeep));

    PM->add(createGlobalDCEPass());

    PM->run(*m);
    errs().changeColor(raw_ostream::Colors::RED, /*Bold=*/true, /*BG=*/false);
    errs() << "\n\n\nresult:\n";
    errs().resetColor();
    m->dump();



    return 0;
}
