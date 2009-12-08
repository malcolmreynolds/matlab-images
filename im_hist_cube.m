function cube = im_hist_cube(Im,A)

if size(Im,3) ~= 3,
  error('im_hist_cube:numberOfSamples','Input image must be RGB');
elseif length(size(A)) ~= 2,
  error('im_hist_cube:alphaMaskNotAMask',['Alpha mask must be 2 ' ...
                      'dimensional']);
elseif size(A,1) ~= size(Im,1) || size(A,2) ~= size(Im,2),
  error('im_hist_cube:amaskSize','Alpha mask size must match');
elseif max(max(A)) > 1,
  warning('im_hist_cube:amaskValuesTooLarge',['alpha mask contains ' ...
                      'values greater than 1!']);
end

%create the cube
cube = zeros(256,256,256);

for y = 1:size(Im,1),
  for x = 1:size(Im,2),
    r = Im(y,x,1)+1;
    g = Im(y,x,2)+1;
    b = Im(y,x,3)+1;
    cube(r,g,b) = cube(r,g,b) + A(y,x);
  end
end
