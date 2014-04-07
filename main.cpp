//#include "llvm/Bitcode/ReaderWriter.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/SourceMgr.h"
#include <string>

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
    m = llvm::ParseIRFile(InputFilename, Err, llvm::getGlobalContext());
    errs() << "xxx\n";


    m->dump();
    return 0;
}
