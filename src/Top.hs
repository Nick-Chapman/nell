
module Top where

import Data.List (intercalate)

main :: IO ()
main = do
  putStrLn "*nell*"
  writeFile  "gen/fib.ll" (unlines (pp example))

----------------------------------------------------------------------
-- example

example :: [Def]
example = [fibDef,mainDef]
  where
    fibDef =
      Def I32 (G"fib") [Formal I32 "arg"]
      [ Assign "x2" $ ICmp_ult I32 (Var (L"arg")) (LitI (2))
      , Br (L"x2") (L"T") (L"F")
      , Lab "T"
      , Ret I32 (L"arg")
      , Lab "F"
      , Assign "x4" $ Add I32 (Var (L"arg")) (LitI (-1))
      , Assign "x5" $ Call I32 (G"fib") [ (I32,(Var (L"x4"))) ]
      , Assign "x6" $ Add I32 (Var (L"arg")) (LitI (-2))
      , Assign "x7" $ Call I32 (G"fib") [ (I32,(Var (L"x6"))) ]
      , Assign "x8" $ Add I32 (Var (L"x7")) (Var (L"x5"))
      , Ret I32 (L"x8")
      ]

    mainDef =
      Def I32 (G"main") []
      [ Assign "res" $ Call I32 (G"fib") [ (I32,LitI 11) ]
      , Ret I32 (L"res")
      ]

----------------------------------------------------------------------
-- LLVM defs,ops etc

data Def = Def { ty :: Ty, name :: Id, formals :: [Formal], body :: [Op] }

data BB = BB { optLab :: Id, code :: [Op] }

data Op
  = Lab String
  | Br Id Id Id
  | Assign String Exp
  | Ret Ty Id

data Exp
  = Add Ty Arg Arg
  | ICmp_ult Ty Arg Arg
  | Call Ty Id [(Ty,Arg)]

data Formal = Formal Ty String

data Arg = Var Id | LitI Int

data Ty = I32 | I1

data Id = L String | G String

----------------------------------------------------------------------
-- pp/show

class PP a where
  pp :: a -> [String]

instance PP [Def] where
  pp xs = intercalate [""] (map pp xs)

instance PP Def where
  pp Def{ty,name,formals,body} =
    [ "define " ++ show ty ++ " " ++ show name
      ++ "(" ++ intercalate "," (map show formals) ++ ") {"
    ] ++ pp body ++ [
     "}"
    ]

instance Show Formal where
  show (Formal ty name) = show ty ++ " " ++ show (L name)

instance PP [Op] where
  pp xs = [ tab x ++ show x | x <- xs ]
    where tab = \case Lab{} -> ""; _ -> "  "

instance Show Op where
  show = \case
    Lab x -> x ++ ":"
    Br i t e -> "br i1 " ++ show i ++ ", label " ++ show t ++ ", label " ++ show e
    Assign name exp -> show (L name) ++ " = " ++ show exp
    Ret ty exp -> "ret" ++ " " ++ show ty ++ " " ++ show exp

instance Show Exp where
  show = \case
    Add ty arg1 arg2  ->
      "add " ++ show ty ++ " " ++ show arg1 ++ ", " ++ show arg2
    ICmp_ult ty arg1 arg2  ->
      "icmp ult " ++ show ty ++ " " ++ show arg1 ++ ", " ++ show arg2
    Call ty name args ->
      "call " ++ show ty ++ " " ++ show name ++ "("
      ++ intercalate "," [ show ty ++ " " ++ show exp | (ty,exp) <- args ]
      ++ ")"

instance Show Arg where
  show = \case
    Var x -> show x
    LitI i -> show i

instance Show Ty where show = \case I32 -> "i32"; I1 -> "i1"
instance Show Id where show = \case L s -> "%"++s; G s -> "@"++s;
