A small **unfinished** toy interpreter in C++

it just support :
- simple call stack (still lacking some instructions)
- simple arithmetic
- function

No memory allocation (malloc/free/deref)

Check out `cpu.cpp` at line 33 for the giant macro `VM_SWITCH` that expend in 4 738 lines of code in debug mode x)

## Prefix :

- `w` stand for word (a serie of bit, can only do bit operation on them)
- `i` for for signed integer
- `u` for for unsigned integer


## Postfix :
- `8`, `16`, `32`, `64` stand for the bit precision (like `u8`, `i64`)
- `max` for the maximun precision available

## Instruction Set

```
  0 0x00 > stop
  1 0x01 > nop
  2 0x02 > if_zero_goto
  3 0x03 > if_non_zero_goto        
  4 0x04 > dbg
  5 0x05 > wmax_and
  6 0x06 > wmax_or
  7 0x07 > wmax_xor
  8 0x08 > wmax_rshift
  9 0x09 > wmax_lshift
 10 0x0a > wmax_bitwise
 11 0x0b > wmax_not
 12 0x0c > wmax_dup    
 13 0x0d > wmax_push_1B
 14 0x0e > wmax_push_2B
 15 0x0f > wmax_push_4B            
 16 0x10 > wmax_push_8B
 17 0x11 > u8_add
 18 0x12 > u8_sub        
 19 0x13 > u8_mul
 20 0x14 > u8_neg
 21 0x15 > u8_eq      
 22 0x16 > u8_neq
 23 0x17 > u8_greater
 24 0x18 > u8_smaller
 25 0x19 > u8_greater_or_eq        
 26 0x1a > u8_smaller_or_eq        
 27 0x1b > u8_push_0
 28 0x1c > u8_push_1
 29 0x1d > u8_push_2
 30 0x1e > u8_push_4
 31 0x1f > u8_push_8
 32 0x20 > u8_div                  
 33 0x21 > u8_mod
 34 0x22 > u16_add
 35 0x23 > u16_sub
 36 0x24 > u16_mul       
 37 0x25 > u16_neg
 38 0x26 > u16_eq
 39 0x27 > u16_neq
 40 0x28 > u16_greater
 41 0x29 > u16_smaller
 42 0x2a > u16_greater_or_eq       
 43 0x2b > u16_smaller_or_eq       
 44 0x2c > u16_push_0
 45 0x2d > u16_push_1
 46 0x2e > u16_push_2
 47 0x2f > u16_push_4
 48 0x30 > u16_push_8
 49 0x31 > u16_div
 50 0x32 > u16_mod
 51 0x33 > u32_add 
 52 0x34 > u32_sub
 53 0x35 > u32_mul
 54 0x36 > u32_neg                 
 55 0x37 > u32_eq
 56 0x38 > u32_neq
 57 0x39 > u32_greater
 58 0x3a > u32_smaller
 59 0x3b > u32_greater_or_eq       
 60 0x3c > u32_smaller_or_eq       
 61 0x3d > u32_push_0
 62 0x3e > u32_push_1
 63 0x3f > u32_push_2
 64 0x40 > u32_push_4
 65 0x41 > u32_push_8
 66 0x42 > u32_div
 67 0x43 > u32_mod
 68 0x44 > u64_add
 69 0x45 > u64_sub
 70 0x46 > u64_mul
 71 0x47 > u64_neg 
 72 0x48 > u64_eq
 73 0x49 > u64_neq
 74 0x4a > u64_greater
 75 0x4b > u64_smaller
 76 0x4c > u64_greater_or_eq       
 77 0x4d > u64_smaller_or_eq       
 78 0x4e > u64_push_0              
 79 0x4f > u64_push_1
 80 0x50 > u64_push_2
 81 0x51 > u64_push_4
 82 0x52 > u64_push_8
 83 0x53 > u64_div     
 84 0x54 > u64_mod
 85 0x55 > i8_add
 86 0x56 > i8_sub                  
 87 0x57 > i8_mul
 88 0x58 > i8_neg
 89 0x59 > i8_eq
 90 0x5a > i8_neq
 91 0x5b > i8_greater
 92 0x5c > i8_smaller
 93 0x5d > i8_greater_or_eq        
 94 0x5e > i8_smaller_or_eq        
 95 0x5f > i8_push_0
 96 0x60 > i8_push_1
 97 0x61 > i8_push_2
 98 0x62 > i8_push_4
 99 0x63 > i8_push_8               
100 0x64 > i8_div
101 0x65 > i8_mod
102 0x66 > i16_add   
103 0x67 > i16_sub
104 0x68 > i16_mul
105 0x69 > i16_neg
106 0x6a > i16_eq
107 0x6b > i16_neq
108 0x6c > i16_greater
109 0x6d > i16_smaller
110 0x6e > i16_greater_or_eq       
111 0x6f > i16_smaller_or_eq       
112 0x70 > i16_push_0
113 0x71 > i16_push_1
114 0x72 > i16_push_2
115 0x73 > i16_push_4    
116 0x74 > i16_push_8
117 0x75 > i16_div
118 0x76 > i16_mod
119 0x77 > i32_add
120 0x78 > i32_sub
121 0x79 > i32_mul
122 0x7a > i32_neg
123 0x7b > i32_eq
124 0x7c > i32_neq
125 0x7d > i32_greater
126 0x7e > i32_smaller
127 0x7f > i32_greater_or_eq       
128 0x80 > i32_smaller_or_eq       
129 0x81 > i32_push_0
130 0x82 > i32_push_1
131 0x83 > i32_push_2
132 0x84 > i32_push_4
133 0x85 > i32_push_8
134 0x86 > i32_div
135 0x87 > i32_mod
136 0x88 > i64_add
137 0x89 > i64_sub
138 0x8a > i64_mul                 
139 0x8b > i64_neg
140 0x8c > i64_eq
141 0x8d > i64_neq
142 0x8e > i64_greater
143 0x8f > i64_smaller
144 0x90 > i64_greater_or_eq       
145 0x91 > i64_smaller_or_eq       
146 0x92 > i64_push_0
147 0x93 > i64_push_1
148 0x94 > i64_push_2
149 0x95 > i64_push_4              
150 0x96 > i64_push_8
151 0x97 > i64_div
152 0x98 > i64_mod
153 0x99 > f32_add
154 0x9a > f32_sub
155 0x9b > f32_mul
156 0x9c > f32_neg
157 0x9d > f32_eq
158 0x9e > f32_neq
159 0x9f > f32_greater
160 0xa0 > f32_smaller
161 0xa1 > f32_greater_or_eq       
162 0xa2 > f32_smaller_or_eq       
163 0xa3 > f32_push_0
164 0xa4 > f32_push_1
165 0xa5 > f32_push_2
166 0xa6 > f32_push_4
167 0xa7 > f32_push_8
168 0xa8 > f32_div
169 0xa9 > f32_mod
170 0xaa > f64_add
171 0xab > f64_sub
172 0xac > f64_mul
173 0xad > f64_neg
174 0xae > f64_eq
175 0xaf > f64_neq
176 0xb0 > f64_greater
177 0xb1 > f64_smaller
178 0xb2 > f64_greater_or_eq       
179 0xb3 > f64_smaller_or_eq       
180 0xb4 > f64_push_0
181 0xb5 > f64_push_1              
182 0xb6 > f64_push_2
183 0xb7 > f64_push_4
184 0xb8 > f64_push_8
185 0xb9 > f64_div
186 0xba > f64_mod
```


This project use my CPP default template/code base "betterCPP" : https://github.com/Thomas-Mewily/betterCPP

## Compilation commands :

- Place yourself at the parent folder of `src`
- Don't forget to create a `bin` directory in the same folder as `src`

- Fast Compilation :

```shell
gcc -O0 -g -DIS_IN_DEBUG=1 -DTRACK_MEMORY=1 ./src/_libs/primitives/*.c* ./src/_libs/betterC/*.c* src/_libs/low_level/*.c* ./src/extenC/*.c*  ./src/*.c* -o ./bin/test.exe -Wall -Wextra -Wcomment -Wno-unknown-pragmas -lstdc++ -Wno-register -std=c++17
```

- Optimized Compilation :

```shell
gcc -O3 ./src/_libs/primitives/*.c* ./src/_libs/betterC/*.c* src/_libs/low_level/*.c* ./src/extenC/*.c*  ./src/*.c* -o ./bin/test.exe -Wall -Wextra -Wcomment -Wno-unknown-pragmas -lstdc++ -Wno-register -std=c++17
```

Run :

```shell
./bin/test.exe
```

## Licence

This is under the Unlicense (see `license.md` ), aka : do what you want with it