function same = im_same_size(bg,fg)
%Returns whether the two images are the same size. does NOT take
%into account number of channels, so a 640x480 rgb image will
%appear to be the same size as a 640x480 grayscale image.

same = true;

if size(bg,1) ~= size(fg,1),
  same = false;
end

if size(bg,2) ~= size(bg,2),
  same = false;
end

