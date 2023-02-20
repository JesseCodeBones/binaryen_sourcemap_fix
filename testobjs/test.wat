(module
 (type $i32_i32_=>_i32 (func (param i32 i32) (result i32)))
 (type $none_=>_i32 (func (result i32)))
 (global $~lib/memory/__data_end i32 (i32.const 8))
 (global $~lib/memory/__stack_pointer (mut i32) (i32.const 32776))
 (global $~lib/memory/__heap_base i32 (i32.const 32776))
 (memory $0 0)
 (table $0 1 1 funcref)
 (elem $0 (i32.const 1))
 (export "add" (func $asc-constants/add))
 (export "main" (func $asc-constants/main))
 (export "memory" (memory $0))
 (func $asc-constants/add (param $a i32) (param $b i32) (result i32)
  (return
   (i32.add
    (local.get $a)
    (local.get $b)
   )
  )
 )
 (func $asc-constants/main (result i32)
  (local $c i32)
  (drop
   (call $asc-constants/add
    (i32.const 1)
    (i32.const 2)
   )
  )
  (local.set $c
   (i32.const 12)
  )
  (return
   (local.get $c)
  )
 )
)