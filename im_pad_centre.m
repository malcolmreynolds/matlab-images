function I = im_pad_centre(Im,nw,nh)
% Pads image Im to be of the size nw x nh, with the original
% contents still centred.

% Probably need some better (any!) sanity checking on the parameter
% settings here.

[oh ow depth] = size(Im);

if abs((nw/nh) - (ow/oh)) > 0.001,
  error(['im_pad_centre: aspect ratio: converting (%dx%d) image to ' ...
         '(%dx%d)'],ow,oh,nw,nh);
end

%indices in the new larger image
start_x = ((nw - ow) / 2)+1;
start_y = ((nh - oh) / 2)+1;
  
I = uint8(zeros(nw,nh,depth));

% Create and fill in the new image
I(start_y:(start_y+oh-1), ...
  start_x:(start_x+ow-1),:) = Im;
  