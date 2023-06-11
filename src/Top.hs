
module Top where

main :: IO ()
main = do
  putStrLn "*nell*"
  writeFile  "gen/fib.ll" (unlines prog)

prog :: [String]
prog =
  [ "define i32 @fib(i32 %arg) {"
  , "  %x2 = icmp ult i32 %arg, 2"
  , "  br i1 %x2, label %T, label %F"
  , "T:"
  , "  ret i32 %arg"
  , "F:"
  , "  %x4 = add i32 %arg, -1"
  , "  %x5 = call i32 @fib(i32 %x4)"
  , "  %x6 = add i32 %arg, -2"
  , "  %x7 = call i32 @fib(i32 %x6)"
  , "  %x8 = add i32 %x7, %x5"
  , "  ret i32 %x8"
  , "}"
  , ""
  , "define i32 @main() {"
  , "  %res = call i32 @fib(i32 11)"
  , "  ret i32 %res"
  , "}"
  ]
