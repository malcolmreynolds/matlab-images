function [im map mask] = aimread(filename);
% Wrapper to avoid having to normalise the alpha mask and also fix the
% ridiculous problem that sometimes at randomly determined points, i end up
% with a png that will always be loaded with white in its transparent bits
% instead of black. That doesn't work out that well.
[im map mask] = imread(filename);
%maybe one day this bullshit won't be necessary
im(im == 255) = 0;
mask = double(mask) ./ 255;