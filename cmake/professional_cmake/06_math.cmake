set(x 3)
set(y 7)

math(EXPR zDec "(${x}+${y}) * 2")
message("decimal = ${zDec}")

math(EXPR zHex "(${x}+${y}) * 2" OUTPUT_FORMAT HEXADECIMAL)
message("hexadecimal = ${zHex}")