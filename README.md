# EURDL
(Extended URDL) Improved version of URDL cipher software implementaion with new UI using Qt. Fixed several problems with the original version

## _Algorithm improvements_

Original algorithm is described here: https://github.com/MaxSaganyuk/URDL-Cipher

New version of the algorithm includes different patterns instead of only Up Right Down Left pattern. 
EURDL encodes the pattern with the information in the key itself. This makes the closed text more difficult to cryptoanalise

Example key: "hn1rj!4i9da27gpzyolexcfk0bs3$t~5w68qvum@"

The key includes 4 "other" characters. Their position is what determines the pattern of movement on the grid. The position of "other" character - n. n mod 4 = {0 - U, 1 - R, 2 - D, 3 - L}. For this key, in form of the grid it looks like this:

<img src="readMeImages\1.png"></img>

So the pattern for this key is RUDL.

The patter can repeat the direction depending on the key like UURD or DDDL etc.

## _Program_

UI looks like this:

<img src="readMeImages\2.png"></img>

Encipher/decipher example:

<img src="readMeImages\3.png"></img>

If, for example, we change the key. Move @ form the end to the start of the key @hn1rj!4i9da27gpzyolexcfk0bs3$t~5w68qvum - the pattern changes from RUDL to UDRL (also changes the grid itself). Resulting enciphering looks like this:

<img src="readMeImages\4.png"></img>

Meaning, a small change in the key makes deciphering closed text harder. As an example - heres an attempt to decipher text that was enciphered with 
second key with 
first key

<img src="readMeImages\5.png"></img>



