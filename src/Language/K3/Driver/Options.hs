{-# LANGUAGE TupleSections #-}

-- | Options for the K3 Driver
module Language.K3.Driver.Options where

import Control.Applicative
import Options.Applicative

import System.FilePath
import System.Log

import Language.K3.Runtime.Common ( SystemEnvironment )
import Language.K3.Runtime.Options
import Language.K3.Utils.Logger.Config

import Language.K3.Driver.Common

import Language.K3.Utils.Pretty (
    Pretty(..), PrintConfig(..),
    indent, defaultPrintConfig, tersePrintConfig, simplePrintConfig
  )

-- | Program Options.
data Options = Options {
      mode      :: Mode
    , inform    :: InfoSpec
    , paths     :: PathOptions
    , input     :: FilePath
    , noFeed    :: Bool
    , transform :: [AnalyzeMode]
    }
  deriving (Eq, Read, Show)

-- | Modes of Operation.
data Mode
    = Compile   CompileOptions
    | Interpret InterpretOptions
    | Print     PrintOptions
    | Typecheck TypecheckOptions
    | Analyze   AnalyzeOptions
  deriving (Eq, Read, Show)

-- | Compilation options datatype.
data CompileOptions = CompileOptions
                      { outLanguage  :: String
                      , programName  :: String
                      , outputFile   :: Maybe FilePath
                      , buildDir     :: Maybe FilePath
                      , ccCmd        :: CPPCompiler
                      , cppOptions   :: String
                      }
  deriving (Eq, Read, Show)

data CPPCompiler = GCC | Clang | Source deriving (Eq, Read, Show)

-- | Interpretation options.
data InterpretOptions
    = Batch { network     :: Bool
            , sysEnv      :: SystemEnvironment
            , asExpr      :: Bool
            , isPar       :: Bool
            , printConfig :: PrintConfig
            , noConsole   :: Bool }
    | Interactive
  deriving (Eq, Read, Show)

-- | Pretty-printing options.
data PrintOptions
    = PrintOptions { printMode  :: PrintMode }
  deriving (Eq, Read, Show)

data PrintMode
    = PrintAST
    | PrintSyntax
  deriving (Eq, Read, Show)

-- | Typechecking options
data TypecheckOptions
    = TypecheckOptions
  deriving (Eq, Read, Show)

-- | Analyze Options.
data AnalyzeOptions
    = AnalyzeOptions { analyzeMode       :: AnalyzeMode
                     , analyzeOutputMode :: PrintMode   }
  deriving (Eq, Read, Show)

data AnalyzeMode
    = Conflicts
    | Tasks
    | ProgramTasks
    | ProxyPaths
    | AnnotationProvidesGraph
    | FlatAnnotations
    | Effects
    | EffectNormalization
    | FoldConstants
    | Simplify
    | Profiling
  deriving (Eq, Read, Show)

-- | Logging and information output options.
data InfoSpec = InfoSpec { logging   :: LoggerOptions
                         , verbosity :: Verbosity }
                  deriving (Eq, Read, Show)

-- | Logging directives, passed through to K3.Logger.Config .
type LoggerInstruction = (String,Priority)
type LoggerOptions     = [LoggerInstruction]

-- | Path related options
data PathOptions = PathOptions { includes :: [FilePath] }
  deriving (Eq, Read, Show)

-- | Verbosity levels.
data Verbosity
    = NullV
    | SoftV
    | LoudV
  deriving (Enum, Eq, Read, Show)


-- | Mode Options Parsing.
modeOptions :: Parser Mode
modeOptions = subparser (
         command "compile"   (info compileOptions   $ progDesc compileDesc)
      <> command "interpret" (info interpretOptions $ progDesc interpretDesc)
      <> command "print"     (info printOptions     $ progDesc printDesc)
      <> command "typecheck" (info typecheckOptions $ progDesc typeDesc)
      <> command "analyze"   (info analyzeOptions   $ progDesc analyzeDesc)
    )
  where compileDesc   = "Compile a K3 binary"
        interpretDesc = "Interpret a K3 program"
        printDesc     = "Print a K3 program"
        typeDesc      = "Typecheck a K3 program"
        analyzeDesc   = "Analyze a K3 program"

-- | Transformation options
transformOptions :: Parser [AnalyzeMode]
transformOptions = many (analysisMode "f")

-- | Compiler options
compileOptions :: Parser Mode
compileOptions = fmap Compile $ CompileOptions
                            <$> outLanguageOpt
                            <*> progNameOpt
                            <*> outputFileOpt
                            <*> buildDirOpt
                            <*> ccCmdOpt
                            <*> cppOpt
  -- where mkCompile l n o b c incs libs = Compile $ CompileOptions l n o b c incs libs

outLanguageOpt :: Parser String
outLanguageOpt = option ( short   'l'
                      <> long    "language"
                      <> value   defaultOutLanguage
                      <> reader  str
                      <> help    "Specify compiler target language"
                      <> metavar "LANG" )

progNameOpt :: Parser String
progNameOpt = option (   short   'n'
                      <> long    "name"
                      <> value   defaultProgramName
                      <> reader  str
                      <> help    "Program name"
                      <> metavar "PROGNAME" )

outputFileOpt :: Parser (Maybe FilePath)
outputFileOpt = validatePath <$> option (
                       short   'o'
                    <> long    "output"
                    <> value   defaultOutputFile
                    <> reader (\s -> str s >>= return . Just)
                    <> help    "Specify output file"
                    <> metavar "OUTPUT" )
  where validatePath Nothing  = Nothing
        validatePath (Just p) = if isValid p then Just p else Nothing

buildDirOpt :: Parser (Maybe FilePath)
buildDirOpt = validatePath <$> option (
                       short   'b'
                    <> long    "build"
                    <> value   defaultBuildDir
                    <> reader (\s -> str s >>= return . Just)
                    <> help    "Temporary build directory"
                    <> metavar "BUILDDIR" )
  where validatePath Nothing  = Nothing
        validatePath (Just p) = if isValid p then Just p else Nothing

ccCmdOpt :: Parser CPPCompiler
ccCmdOpt = gccFlag <|> clangFlag <|> sourceFlag

gccFlag :: Parser CPPCompiler
gccFlag = flag' GCC (
        long "gcc"
     <> help "Use the g++ toolchain for C++ compilation"
    )

clangFlag :: Parser CPPCompiler
clangFlag = flag' Clang (
        long "clang"
     <> help "Use the clang++ and LLVM toolchain for C++ compilation"
    )

sourceFlag :: Parser CPPCompiler
sourceFlag = flag' Source (long "source" <> help "No second-stage compilation.")

cppOpt :: Parser String
cppOpt = strOption $ long "cpp-flags" <> help "Specify CPP Flags" <> metavar "CPPFLAGS"

includeOpt :: Parser FilePath
includeOpt = strOption (
                long "CI"
             <> help "Specifies a C++ compiler include directory."
             <> metavar "DIRECTORY"
           )

libraryOpt :: Parser (Bool, FilePath)
libraryOpt = linkerDirOpt <|> libraryFileOpt

linkerDirOpt :: Parser (Bool, FilePath)
linkerDirOpt = (True,) <$> strOption (
                  long "CL"
               <> help "Specifies a C++ linker directory."
               <> metavar "DIRECTORY"
             )

libraryFileOpt :: Parser (Bool, FilePath)
libraryFileOpt = (False,) <$> strOption (
                    long "Cl"
                 <> help "Specifies a C++ library file."
                 <> metavar "FILE"
               )

-- | Interpretation options.
interpretOptions :: Parser Mode
interpretOptions = Interpret <$> (batchOptions <|> interactiveOptions)

-- | Options for Interactive Mode.
interactiveOptions :: Parser InterpretOptions
interactiveOptions = flag' Interactive (
        short 'i'
     <> long "interactive"
     <> help "Run in Interactive Mode"
    )

-- | Options for Batch Mode.
batchOptions :: Parser InterpretOptions
batchOptions = flag' Batch (
            short 'b'
         <> long "batch"
         <> help "Run in Batch Mode (default)"
        ) *> batchOpts
  where batchOpts = pure Batch <*> networkOpt
                               <*> sysEnvOptions
                               <*> elvlOpt
                               <*> parOpt
                               <*> printConfigOpt
                               <*> consoleOpt

-- | Expression-Level flag.
elvlOpt :: Parser Bool
elvlOpt = switch (
        short 'e'
     <> long "expression"
     <> help "Run in top-level expression mode."
    )

-- | Network mode flag.
networkOpt :: Parser Bool
networkOpt = switch (
	short 'n'
     <> long "network"
     <> help "Run in Network Mode"
    )

-- | Parallel mode flag.
parOpt :: Parser Bool
parOpt = switch (
        long "parallel"
     <> help "Run the Parallel Engine"
    )

consoleOpt :: Parser Bool
consoleOpt = switch (
         long "console"
      <> help "Toggle the interpreter console"
    )

data InterpPrintVerbosity = PrintVerbose | PrintTerse | PrintTerseSimple

-- | Print options for interpreter
printConfigOpt :: Parser PrintConfig
printConfigOpt = choosePC <$> verbosePrintFlag <*> simplePrintFlag
  where choosePC _ PrintTerseSimple = simplePrintConfig
        choosePC PrintTerse _       = tersePrintConfig
        choosePC _     _            = defaultPrintConfig

        verbosePrintFlag = flag
                       PrintTerse
                       PrintVerbose
                       (long "verbose"
                       <> short 'v'
                       <> help "Verbose interpreter printout")

        -- | Simple logging for interpreter
        simplePrintFlag = flag
                            PrintVerbose
                            PrintTerseSimple
                            (long "simple"
                            <> help "Use simple printing format for logging")



-- | Printing options
printOptions :: Parser Mode
printOptions = mkPrint <$> (astPrintOpt <|> syntaxPrintOpt)
  where mkPrint m = Print $ PrintOptions m

astPrintOpt :: Parser PrintMode
astPrintOpt = flag' PrintAST (   long "ast"
                              <> help "Print AST output" )

syntaxPrintOpt :: Parser PrintMode
syntaxPrintOpt = flag' PrintSyntax (   long "syntax"
                                    <> help "Print syntax output" )

-- | Typecheck options
typecheckOptions :: Parser Mode
typecheckOptions = pure $ Typecheck TypecheckOptions

-- | Analyze options
analyzeOptions :: Parser Mode
analyzeOptions = (\a b -> Analyze $ AnalyzeOptions a b)
                  <$> analysisMode "" <*> ( astPrintOpt <|> syntaxPrintOpt )

-- Accept a precursor string
analysisMode :: String -> Parser AnalyzeMode
analysisMode s =    conflictsOpt s
              <|> tasksOpt s
              <|> programTasksOpt s
              <|> proxyPathsOpt s
              <|> annProvOpt s
              <|> flatAnnOpt s
              <|> effectOpt s
              <|> normalizationOpt s
              <|> foldConstantsOpt s
              <|> simplifyOpt s
              <|> profilingOpt s

conflictsOpt :: String -> Parser AnalyzeMode
conflictsOpt s = flag' Conflicts (   long (s++"conflicts")
                                <> help "Print Conflicting Data Accesses for a K3 Program" )

tasksOpt :: String -> Parser AnalyzeMode
tasksOpt s = flag' Tasks (   long (s++"tasks")
                        <> help "Split Triggers into smaller tasks for parallelization" )

programTasksOpt :: String -> Parser AnalyzeMode
programTasksOpt s = flag' ProgramTasks (   long (s++"programtasks")
                                      <> help "Find program-level tasks to be run in parallel " )

proxyPathsOpt :: String -> Parser AnalyzeMode
proxyPathsOpt s = flag' ProxyPaths (   long (s++"proxypaths")
                                  <> help "Print bind paths for bind expressions" )

annProvOpt :: String -> Parser AnalyzeMode
annProvOpt s = flag' AnnotationProvidesGraph (   long (s++"provides-graph")
                                            <> help "Print bind paths for bind expressions" )

flatAnnOpt :: String -> Parser AnalyzeMode
flatAnnOpt s = flag' FlatAnnotations (   long (s++"flat-annotations")
                                    <> help "Print bind paths for bind expressions" )

effectOpt :: String -> Parser AnalyzeMode
effectOpt s = flag' Effects (   long (s++"effects")
                           <> help "Print program effects")

normalizationOpt :: String -> Parser AnalyzeMode
normalizationOpt s = flag' EffectNormalization
                      (   long (s++"normalize")
                       <> help "Print an effect-normalized program.")

foldConstantsOpt :: String -> Parser AnalyzeMode
foldConstantsOpt s = flag' FoldConstants
                      (   long (s++"fold-constants")
                       <> help "Print a program after constant folding.")

simplifyOpt :: String -> Parser AnalyzeMode
simplifyOpt s = flag' Simplify
                (   long (s++"simplify")
                 <> (help $ "Print a program after running all simplification phases " ++
                            "(i.e., constant folding, DCE, CSE, etc)" ))

profilingOpt :: String -> Parser AnalyzeMode
profilingOpt s = flag' Profiling
                (   long (s++"profile")
                 <> (help $ "Print a program after adding profiling points"))

-- | Information printing options.
informOptions :: Parser InfoSpec
informOptions = InfoSpec <$> loggingOptions <*> verbosityOptions


{- Top-level options -}

-- | Logging options.
loggingOptions :: Parser LoggerOptions
loggingOptions = many $ option (
                       long "log"
                    <> help "Enable logging on TAG"
                    <> metavar "TAG"
                    <> eitherReader parseInstruction
                 )

-- | Path options.
pathOptions :: Parser PathOptions
pathOptions = PathOptions <$> many ( strOption (
                     short 'I'
                  <> long "include"
                  <> help "Includes a directory on the source code search path"
                  <> metavar "DIRECTORY"
                ))

-- | Verbosity options.
verbosityOptions :: Parser Verbosity
verbosityOptions = toEnum . roundVerbosity <$> option (
        short 'v'
     <> long "verbosity"
     <> help "Verbosity of Output. [0..2]"
     <> showDefault
     <> value 0
     <> metavar "LEVEL"
    )
  where
    roundVerbosity n
        | n < 0 = 0
        | n > 2 = 2
        | otherwise = n

noFeedOpt :: Parser Bool
noFeedOpt = switch (
       long "nofeed"
    <> help "Process a program, ignoring data feeds." )

inputOptions :: Parser [FilePath]
inputOptions = fileOrStdin <$> (many $ argument str (
        metavar "FILE"
     <> help "K3 program file."
    ) )
  where fileOrStdin [] = ["-"]
        fileOrStdin x  = x

-- | Program Options Parsing.
programOptions :: Parser Options
programOptions = mkOptions <$> transformOptions
                           <*> modeOptions
                           <*> informOptions
                           <*> pathOptions
                           <*> noFeedOpt
                           <*> inputOptions
    where mkOptions tr m i p nf is = Options m i p (last is) nf tr

{- Instance definitions -}

instance Pretty Mode where
  prettyLines (Compile   cOpts) = ["Compile " ++ show cOpts]
  prettyLines (Interpret iOpts) = ["Interpret"] ++ (indent 2 $ prettyLines iOpts)
  prettyLines (Print     pOpts) = ["Print " ++ show pOpts]
  prettyLines (Typecheck tOpts) = ["Typecheck" ++ show tOpts]
  prettyLines (Analyze   aOpts) = ["Analyze" ++ show aOpts]

instance Pretty InterpretOptions where
  prettyLines (Batch net env expr par printOpts console) =
    ["Batch"] ++ (indent 3 $ ["Network: " ++ show net]
                          ++ prettySysEnv env
                          ++ ["Expression: " ++ show expr]
                          ++ ["Parallel: "   ++ show par]
                          ++ ["Print: "      ++ show printOpts]
                          ++ ["Console: "    ++ show console])

  prettyLines v = [show v]
