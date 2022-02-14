# EURDL
(Extended URDL) Improved version of URDL cipher software implementaion with new UI using Qt. Fixed several problems with the original version

## _Algorithm improvements_

Original algorithm is described here: https://github.com/MaxSaganyuk/URDL-Cipher

New version of the algorithm includes different patterns instead of only Up Right Down Left pattern. 
EURDL encodes the pattern with the information in the key itself. 

Example key: "hn1rj!4i9da27gpzyolexcfk0bs3$t~5w68qvum@"

The key includes 4 "other" characters. Their position is what determines the pattern of movement on the grid. The position of "other" character - n. n mod 4 = {0 - U, 1 - R, 2 - D, 3 - L}. For this key, in form of the grid it looks like this:

<img src="readMeImages\1.png"></img>

So the pattern for this key is RUDL.

The patter can repeat the direction depending on the key like UURD or DDDL etc.

## _Program_

<img src="readMeImages\2.png"></img>
