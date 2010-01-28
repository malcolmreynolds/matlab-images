function [im map mask] = aimread(filename);
% Wrapper to avoid having to normalise the alpha mask and also fix the
% ridiculous problem that sometimes at randomly determined points, i end up
% with a png that will always be loaded with white in its transparent bits
% instead of black. That doesn't work out that well.
[im map mask] = imread(filename);

%the hack below is now removed - to make proper transparent images
%use GIMP!!!
%%maybe one day this bullshit won't be necessary
%find places where all three channels are white
r_black = (im(:,:,1) == 255);
g_black = (im(:,:,2) == 255);
b_black = (im(:,:,3) == 255);
all_black = r_black & g_black & b_black;
all_black_full = repmat(all_black,[1 1 3]);
im(all_black_full) = 0;


mask = double(mask) ./ 255;