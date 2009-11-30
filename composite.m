function Im = composite(bg,fg,amask)
% Composite the fg image with associate alpha mask onto bg image.
% Note that the parts of fg which are supposed to be transparent MUST
% be black or else everything in this won't work...

%check images are the same size
if ~(im_same_size(bg,fg) && im_same_size(bg,amask)),
  error('images:composite:imagesWrongSize', ...
        'background, foreground and alpha mask must have the same size!');
end

%check if the alpha mask is one channel only, if it is then
%replicate it.
if size(amask,3) == 1,
  amask = repmat(amask,[1 1 3]);
end


% this is ad-hoc as fuck. maybe a bad idea. but for now, let's say
% if we have any values over 1 then assume this is a 0-255 image so
% we should scale it down, and convert to double
if max(max(max(amask))) > 1.0,
  amask = double(amask) ./ 255;
end

% We don't need to multiply foreground by alpha because assuming
% the outside is black then it should already have that taken into
% account. Multiplying by alpha would just make it even smaller again.
Im = uint8((1-amask).*double(bg) + double(fg));



