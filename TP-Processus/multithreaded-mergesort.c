typedef unsigned int index ;
typedef unsigned int length ;
void merge ( int array [] , index start , index middle , index final );
void merge_sort ( int array [] , index start , index final );
void merge_sort ( int array [] , index start , index final ) {
if ( start < final ) {
index middle = floor (( start + final ) / 2);
merge_sort ( array , start , middle );
merge_sort ( array , middle +1 , final );
merge ( array , start , middle , final );
}
}
void merge ( int array [] , index start , index middle , index final ) {
length countL = middle - start + 1;
int * arrayL = malloc ( countL * sizeof ( int ));
index currentL , currentR ;
for ( currentL = 0; currentL < countL ; currentL ++)
arrayL [ currentL ] = array [ start + currentL ];
length countR = final - middle ;
int * arrayR = malloc ( countR * sizeof ( int ));
for ( currentR = 0; currentR < countR ; currentR ++)
arrayR [ currentR ] = array [ middle + 1 + currentR ];
currentL = 0;
currentR = 0;
index current ;
for ( current = start ; current <= final && currentL < countL && currentR < countR ; current ++) {
if ( arrayL [ currentL ] <= arrayR [ currentR ]) {
array [ current ] = arrayL [ currentL ];
currentL ++;
} else { // arrayL [ currentL ] > arrayR [ currentR ]
array [ current ] = arrayR [ currentR ];
currentR ++;
}
}
// I f <arrayL> was completely consumed , copy the remainder o f <arrayR> over the remainder o f <array>
if ( currentL >= countL )
while ( currentR < countR ) {
array [ current ] = arrayR [ currentR ];
current ++;
currentR ++;
}
// I f <arrayR> was completely consumed , copy the remainder o f <arrayL> over the remainder o f <array>
if ( currentR >= countR )
while ( currentL < countL ) {
array [ current ] = arrayL [ currentL ];
current ++;
currentL ++;
}
free ( arrayL );
free ( arrayR );
}