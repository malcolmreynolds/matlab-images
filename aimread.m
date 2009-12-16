function [im map mask] = aimread(filename);
% Wrapper to avoid having to normalise the alpha mask
[im map mask] = imread(filename);
mask = double(mask) ./ 255;