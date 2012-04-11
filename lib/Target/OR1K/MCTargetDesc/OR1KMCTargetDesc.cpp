//===-- OR1KMCTargetDesc.cpp - OR1K Target Descriptions -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides OR1K specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "OR1KMCTargetDesc.h"
#include "OR1KMCAsmInfo.h"
#include "llvm/MC/MCCodeGenInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "OR1KGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "OR1KGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "OR1KGenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createOR1KMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitOR1KMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createOR1KMCRegisterInfo(StringRef TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitOR1KMCRegisterInfo(X, OR1K::R9);
  return X;
}

static MCSubtargetInfo *createOR1KMCSubtargetInfo(StringRef TT, StringRef CPU,
                                                   StringRef FS) {
  MCSubtargetInfo *X = new MCSubtargetInfo();
  InitOR1KMCSubtargetInfo(X, TT, CPU, FS);
  return X;
}

static MCCodeGenInfo *createOR1KMCCodeGenInfo(StringRef TT, Reloc::Model RM,
                                               CodeModel::Model CM,
                                               CodeGenOpt::Level OL) {
  MCCodeGenInfo *X = new MCCodeGenInfo();
  X->InitMCCodeGenInfo(RM, CM, OL);
  return X;
}

extern "C" void LLVMInitializeOR1KTargetMC() {
  // Register the MC asm info.
  RegisterMCAsmInfo<OR1KMCAsmInfo> X(TheOR1KTarget);

  // Register the MC codegen info.
  TargetRegistry::RegisterMCCodeGenInfo(TheOR1KTarget,
                                       createOR1KMCCodeGenInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheOR1KTarget, createOR1KMCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheOR1KTarget, createOR1KMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheOR1KTarget,
                                          createOR1KMCSubtargetInfo);
}
