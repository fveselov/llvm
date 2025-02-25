; NOTE: Assertions have been autogenerated by utils/update_test_checks.py UTC_ARGS: --function-signature --check-attributes --check-globals
; RUN: opt -aa-pipeline=basic-aa -passes=attributor -attributor-manifest-internal  -attributor-max-iterations-verify -attributor-annotate-decl-cs -attributor-max-iterations=2 -S < %s | FileCheck %s --check-prefixes=CHECK,TUNIT
; RUN: opt -aa-pipeline=basic-aa -passes=attributor-cgscc -attributor-manifest-internal  -attributor-annotate-decl-cs -S < %s | FileCheck %s --check-prefixes=CHECK,CGSCC

%"a" = type { i64 }
%"b" = type { i8 }

define hidden i64 @f1() align 2 {
; TUNIT: Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none)
; TUNIT-LABEL: define {{[^@]+}}@f1
; TUNIT-SAME: () #[[ATTR0:[0-9]+]] align 2 {
; TUNIT-NEXT:  entry:
; TUNIT-NEXT:    ret i64 undef
;
; CGSCC: Function Attrs: mustprogress nofree nosync nounwind willreturn memory(none)
; CGSCC-LABEL: define {{[^@]+}}@f1
; CGSCC-SAME: () #[[ATTR0:[0-9]+]] align 2 {
; CGSCC-NEXT:  entry:
; CGSCC-NEXT:    [[REF_TMP:%.*]] = alloca [[A:%.*]], align 8
; CGSCC-NEXT:    [[CALL2:%.*]] = call i64 @f2() #[[ATTR2:[0-9]+]]
; CGSCC-NEXT:    ret i64 [[CALL2]]
;
entry:
  %ref.tmp = alloca %"a", align 8
  %call2 = call i64 @f2(ptr %ref.tmp)
  ret i64 %call2
}

define internal i64 @f2(ptr %this) align 2 {
; CGSCC: Function Attrs: mustprogress nofree nosync nounwind willreturn memory(none)
; CGSCC-LABEL: define {{[^@]+}}@f2
; CGSCC-SAME: () #[[ATTR0]] align 2 {
; CGSCC-NEXT:  entry:
; CGSCC-NEXT:    ret i64 undef
;
entry:
  %this.addr = alloca ptr, align 8
  store ptr %this, ptr %this.addr, align 8
  %this1 = load ptr, ptr %this.addr, align 8
  call void @f3(ptr %this1)
  ret i64 undef
}

define internal void @f3(ptr %this) align 2 {
; CGSCC: Function Attrs: mustprogress nofree nosync nounwind willreturn memory(none)
; CGSCC-LABEL: define {{[^@]+}}@f3
; CGSCC-SAME: () #[[ATTR0]] align 2 {
; CGSCC-NEXT:  entry:
; CGSCC-NEXT:    ret void
;
entry:
  %this.addr = alloca ptr, align 8
  store ptr %this, ptr %this.addr, align 8
  %this1 = load ptr, ptr %this.addr, align 8
  %call = call i1 @f4(ptr %this1)
  ret void
}

define internal i1 @f4(ptr %this) align 2 {
; CGSCC: Function Attrs: mustprogress nofree nosync nounwind willreturn memory(none)
; CGSCC-LABEL: define {{[^@]+}}@f4
; CGSCC-SAME: () #[[ATTR0]] align 2 {
; CGSCC-NEXT:  entry:
; CGSCC-NEXT:    ret i1 undef
;
entry:
  %this.addr = alloca ptr, align 8
  store ptr %this, ptr %this.addr, align 8
  %this1 = load ptr, ptr %this.addr, align 8
  %call = call ptr @f5(ptr %this1)
  ret i1 undef
}

define internal ptr @f5(ptr %this) align 2 {
; CGSCC: Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none)
; CGSCC-LABEL: define {{[^@]+}}@f5
; CGSCC-SAME: () #[[ATTR1:[0-9]+]] align 2 {
; CGSCC-NEXT:  entry:
; CGSCC-NEXT:    ret ptr undef
;
entry:
  %this.addr = alloca ptr, align 8
  store ptr %this, ptr %this.addr, align 8
  %this1 = load ptr, ptr %this.addr, align 8
  ret ptr %this1
}
;.
; TUNIT: attributes #[[ATTR0]] = { mustprogress nofree norecurse nosync nounwind willreturn memory(none) }
;.
; CGSCC: attributes #[[ATTR0]] = { mustprogress nofree nosync nounwind willreturn memory(none) }
; CGSCC: attributes #[[ATTR1]] = { mustprogress nofree norecurse nosync nounwind willreturn memory(none) }
; CGSCC: attributes #[[ATTR2]] = { willreturn }
;.
;; NOTE: These prefixes are unused and the list is autogenerated. Do not add tests below this line:
; CHECK: {{.*}}
