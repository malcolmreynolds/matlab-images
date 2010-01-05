function bg = composite(bg,fg,amask,offsetx,offsety)
% Composite the fg image with associate alpha mask onto bg image.
% Note that the parts of fg which are supposed to be transparent MUST
% be black or else everything in this won't work... offset must
% contain width and height fields, which will be how many blank
% pixels to add above / to the left of the image

%check if the alpha mask is one channel only, if it is then
%replicate it.
if size(amask,3) == 1,
  amask = repmat(amask,[1 1 3]);
end

if nargin == 3,
  offsetx = 0;
  offsety = 0;
elseif nargin ~= 5,
  error('composite:WrongNumberOfArgs','Need 3 or 5 arguments');
end
% this is ad-hoc as fuck. maybe a bad idea. but for now, let's say
% if we have any values over 1 then assume this is a 0-255 image so
% we should scale it down, and convert to double
if max(max(max(amask))) > 1.0,
  error('images:composite:alphaMaskWrongFormat',...
        'Alpha mask contains values greater than 1!');
end

%check fg and mask are the same size
if ~im_same_size(fg,amask),
  error('images:composite:imagesWrongSize', ...
        'foreground and alpha mask must have the same size!');
end

%add 



% We don't need to multiply foreground by alpha because assuming
% the outside is black then it should already have that taken into
% account. Multiplying by alpha would just make it even smaller
% again. - APPROVED by Gabe.
regionx = (offsetx+1):(offsetx + size(fg,2));
regiony = (offsety+1):(offsety + size(fg,1)); 
bg_for_composite = double(bg(regiony,regionx,:));
bg(regiony,regionx,:) = uint8((1-amask).*bg_for_composite + double(fg));



