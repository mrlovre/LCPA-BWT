module Main where

import Data.List

main :: IO ()
main = do
    l <- getLine >> getContents
    let sortedPrefixes = tail $ sort $ tails $ filter (/= '\n') $ l ++ "$"
        lcps = (-1) : zipWith (\ a b -> length . takeWhile id $ zipWith (==) a b) sortedPrefixes (tail sortedPrefixes) ++ [-1]
    --putStrLn $ unlines sortedPrefixes
    print lcps

