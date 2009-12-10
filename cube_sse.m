function d = cube_sse(cube)
%Calculates the sum of squared values for a colour cube. The way
%that this function will most likely be used is cube_sse(c1 - c2)
%or similar.

d = sum(sum(sum(cube.^2)));

