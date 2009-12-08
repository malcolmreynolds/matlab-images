function I = im_crop_centre(Im,nw,nh)
%Crops image to be the size nw x nh, with original contents
%centred.

[oh ow depth] = size(Im);

% if abs((nw/nh) - (ow/oh)) > 0.05,
%   error(['im_pad_centre: aspect ratio: converting (%dx%d) image to ' ...
%          '(%dx%d)'],ow,oh,nw,nh);
% end

%indices to cut from in the smaller image
start_x = round(((ow-nw)/2)+1);
start_y = round(((oh-nh)/2)+1);

%this should work for both 3 and 1 channels
I = Im(start_y:(start_y+nh-1), ...
       start_x:(start_x+nw-1),:);
