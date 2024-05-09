message("string(FIND inputString subString outVar [REVERSE])")
string(FIND abcdefabcdef def fwdIndex)
string(FIND abcdefabcdef def revIndex REVERSE)
message("fwdIndex = ${fwdIndex}\n" "revIndex = ${revIndex}")

message("string(REPLACE matchString replaceWith outVar input...)")
string(REPLACE abc * replaceStr abcabcabcdef)
message("replaceStr = ${replaceStr}")

string(SUBSTRING abcdefgh 0 3 substringStr)
string(LENGTH abcdef lenghtNum)
string(TOLOWER ABC tolowerStr)
string(TOUPPER abc toupperStr)
string(STRIP "  abc  " stripStr)

message(
  "substringStr = ${substringStr}" "\n"
  "lenghtNum = ${lenghtNum}" "\n"
  "tolowerStr = ${tolowerStr}" "\n"
  "toupperStr = ${toupperStr}" "\n"
  "stripStr = ${stripStr}"
)