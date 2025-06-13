# Type system

 Type naming are stolen from Rust, but with some improvements.

 - Signed numbers:
   - `i8`  (signed 8  bit integer < -128 .. 127> )
   - `i16` (signed 16 bit integer < -32768 .. 32767> )
   - `i32` (signed 32 bit integer < -2147483648 .. 2147483647> )
   - `i64` (signed 64 bit integer < -9223372036854775808 .. 9223372036854775808> )
 - Unsigned numbers:
   - `u8`  (unsigned 8  bit integer <0 .. 256>)
   - `u16` (unsigned 16 bit integer <0 .. 65565>)
   - `u32` (unsigned 32 bit integer <0 .. 4294967295>)
   - `u64` (unsigned 64 bit integer <0 .. 18446744073709551615>)
 - Floating point numbers
   - `f32` (unsigned 32 bit integer <1.17549e-38 .. 3.40282e+38> )
   - `f64` (unsigned 64 bit integer <2.22507e-308 .. 1.79769e+308> )
 - Fundamental types:
   - `bool` (can be only `true` or `false`)
   - `char` (used for storing characters: 'A', '-', etc...)
   - `str` (used for strings: "Hello", "This is a text")
 - Containers types:
   - `arr<T,n>` (static array with type T, and size of n)
   - `vec<T>` (dynamic array with type T, and it can expand or shrink )
   - `map<K,V>` (hashmap with key type K and value type V, stores only unique key-value pairs)
   - `set<T>` (hashset with type T, stores only unique values)

