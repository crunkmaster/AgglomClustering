# Agglomerative Clustering with Group-Average Distance 
A set of algorithms and Classes for clustering points in n-dimensional space
using group-average Euclidian distance.

## Building 
`make` produces an executable called 'main'

`make test` will run main with the test file listed in the project
specification, generating two clusters using the command `./main < input.txt 2`.

## Running 
`cat [file] | ./main [number of clusters] > [outfile]`


or


`./main < [file] [number of clusters] > [outfile]`

## Documentation 
Inside the html and latex subdirectories there exist
Doxygen-generated documentaion files at 'index.html' and 'refman.pdf'
respectively. 

## Utilities 
In the root directory there exists a useful perl script called
'gen_points.pl' which can generate points and output them to stdout.  By default
it will generate 100 5-dimensional points and output them to stdout. 

usage:

`perl gen_points.pl > points_file`

`perl gen_points.pl | ./main 2 > out_file`
