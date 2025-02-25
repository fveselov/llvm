; RUN:  llvm-dis -opaque-pointers < %s.bc| FileCheck %s
; RUN:  verify-uselistorder < %s.bc

; The 2-field form @llvm.global_ctors will be upgraded when reading bitcode.
; CHECK: @llvm.global_ctors = appending global [0 x { i32, ptr, ptr }] zeroinitializer
