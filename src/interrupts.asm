[BITS 32]

%macro PUSHER 1
[GLOBAL vector_pusher_%1]
vector_pusher_%1:
  push 0
  push %1
  jmp context_collector
%endmacro

%macro PUSHER_ERR 1
[GLOBAL vector_pusher_%1]
vector_pusher_%1:
  push %1
  jmp context_collector
%endmacro

PUSHER      0
PUSHER      1
PUSHER      2
PUSHER      3
PUSHER      4
PUSHER      5
PUSHER      6
PUSHER      7
PUSHER_ERR  8
PUSHER      9
PUSHER_ERR  10
PUSHER_ERR  11
PUSHER_ERR  12
PUSHER_ERR  13
PUSHER_ERR  14
PUSHER      15
PUSHER      16
PUSHER_ERR  17
PUSHER      18
PUSHER      19
PUSHER      20
PUSHER_ERR  21
PUSHER      22
PUSHER      23
PUSHER      24
PUSHER      25
PUSHER      26
PUSHER      27
PUSHER      28
PUSHER      29
PUSHER      30
PUSHER      31
PUSHER      32
PUSHER      33
PUSHER      34
PUSHER      35
PUSHER      36
PUSHER      37
PUSHER      38
PUSHER      39
PUSHER      40
PUSHER      41
PUSHER      42
PUSHER      43
PUSHER      44
PUSHER      45
PUSHER      46
PUSHER      47
PUSHER      48
PUSHER      49
PUSHER      50
PUSHER      51
PUSHER      52
PUSHER      53
PUSHER      54
PUSHER      55
PUSHER      56
PUSHER      57
PUSHER      58
PUSHER      59
PUSHER      60
PUSHER      61
PUSHER      62
PUSHER      63
PUSHER      64
PUSHER      65
PUSHER      66
PUSHER      67
PUSHER      68
PUSHER      69
PUSHER      70
PUSHER      71
PUSHER      72
PUSHER      73
PUSHER      74
PUSHER      75
PUSHER      76
PUSHER      77
PUSHER      78
PUSHER      79
PUSHER      80
PUSHER      81
PUSHER      82
PUSHER      83
PUSHER      84
PUSHER      85
PUSHER      86
PUSHER      87
PUSHER      88
PUSHER      89
PUSHER      90
PUSHER      91
PUSHER      92
PUSHER      93
PUSHER      94
PUSHER      95
PUSHER      96
PUSHER      97
PUSHER      98
PUSHER      99
PUSHER      100
PUSHER      101
PUSHER      102
PUSHER      103
PUSHER      104
PUSHER      105
PUSHER      106
PUSHER      107
PUSHER      108
PUSHER      109
PUSHER      110
PUSHER      111
PUSHER      112
PUSHER      113
PUSHER      114
PUSHER      115
PUSHER      116
PUSHER      117
PUSHER      118
PUSHER      119
PUSHER      120
PUSHER      121
PUSHER      122
PUSHER      123
PUSHER      124
PUSHER      125
PUSHER      126
PUSHER      127
PUSHER      128
PUSHER      129
PUSHER      130
PUSHER      131
PUSHER      132
PUSHER      133
PUSHER      134
PUSHER      135
PUSHER      136
PUSHER      137
PUSHER      138
PUSHER      139
PUSHER      140
PUSHER      141
PUSHER      142
PUSHER      143
PUSHER      144
PUSHER      145
PUSHER      146
PUSHER      147
PUSHER      148
PUSHER      149
PUSHER      150
PUSHER      151
PUSHER      152
PUSHER      153
PUSHER      154
PUSHER      155
PUSHER      156
PUSHER      157
PUSHER      158
PUSHER      159
PUSHER      160
PUSHER      161
PUSHER      162
PUSHER      163
PUSHER      164
PUSHER      165
PUSHER      166
PUSHER      167
PUSHER      168
PUSHER      169
PUSHER      170
PUSHER      171
PUSHER      172
PUSHER      173
PUSHER      174
PUSHER      175
PUSHER      176
PUSHER      177
PUSHER      178
PUSHER      179
PUSHER      180
PUSHER      181
PUSHER      182
PUSHER      183
PUSHER      184
PUSHER      185
PUSHER      186
PUSHER      187
PUSHER      188
PUSHER      189
PUSHER      190
PUSHER      191
PUSHER      192
PUSHER      193
PUSHER      194
PUSHER      195
PUSHER      196
PUSHER      197
PUSHER      198
PUSHER      199
PUSHER      200
PUSHER      201
PUSHER      202
PUSHER      203
PUSHER      204
PUSHER      205
PUSHER      206
PUSHER      207
PUSHER      208
PUSHER      209
PUSHER      210
PUSHER      211
PUSHER      212
PUSHER      213
PUSHER      214
PUSHER      215
PUSHER      216
PUSHER      217
PUSHER      218
PUSHER      219
PUSHER      220
PUSHER      221
PUSHER      222
PUSHER      223
PUSHER      224
PUSHER      225
PUSHER      226
PUSHER      227
PUSHER      228
PUSHER      229
PUSHER      230
PUSHER      231
PUSHER      232
PUSHER      233
PUSHER      234
PUSHER      235
PUSHER      236
PUSHER      237
PUSHER      238
PUSHER      239
PUSHER      240
PUSHER      241
PUSHER      242
PUSHER      243
PUSHER      244
PUSHER      245
PUSHER      246
PUSHER      247
PUSHER      248
PUSHER      249
PUSHER      250
PUSHER      251
PUSHER      252
PUSHER      253
PUSHER      254
PUSHER      255

context_collector:
  push DS
  push ES
  push FS
  push GS
  pusha

  cld
  mov AX, DATA_SELECTOR
  mov DS, AX
  mov ES, AX
  mov FS, AX
  mov GS, AX

  mov EBX, ESP
  sub ESP, 4
  and ESP, -16
  mov dword[ESP], EBX

  [EXTERN interrupt_handler]
  ; void interrupt_handler(Context* ctx)
  call interrupt_handler

  mov ESP, EBX
  popa
  pop GS
  pop FS
  pop ES
  pop DS
  add ESP, 8
  iret

[GLOBAL lidt]
; void lidt(IDTR* ptr)
lidt:
  mov   EAX, dword[ESP + 4]
  lidt [EAX]
  ret
