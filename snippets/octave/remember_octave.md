octave:1> pkg load control
octave:2> num=[1 2]
num =

   1   2

octave:3> den=[1 3 2]
den =

   1   3   2

octave:4> G = tf(num,den)

Transfer function 'G' from input 'u1' to output ...

          s + 2    
 y1:  -------------
      s^2 + 3 s + 2

Continuous-time model.
octave:5> rlocus(G)
octave:6> 
